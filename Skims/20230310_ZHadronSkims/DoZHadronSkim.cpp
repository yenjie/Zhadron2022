#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH2D.h"
#include "TMath.h"
#include "TSystem.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TLorentzVector.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "CommonFunctions.h"
#include "ProgressBar.h"
#include "CustomAssert.h"

struct EventIndex;
int main(int argc, char *argv[]);

struct EventIndex
{
public:
   double HF;
   int File;
   int Event;
public:
   bool operator <(const EventIndex &other) const
   {
      if(HF < other.HF)         return true;
      if(HF > other.HF)         return false;
      if(File < other.File)     return true;
      if(File > other.File)     return false;
      if(Event < other.Event)   return true;
      if(Event > other.Event)   return false;
      return false;
   }
};


int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool DoGenLevel               = CL.GetBool("DoGenLevel", true);
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   bool IsData                   = CL.GetBool("IsData", false);
   bool IsPP                     = CL.GetBool("IsPP", false);
   bool DoBackground             = CL.GetBool("DoBackground", false);

   Assert(IsPP == false,         "PP mode not implemented yet");
   Assert(DoBackground == false, "Background mode not fully implemented yet");

   vector<string> BackgroundFileNames;
   int NBackground = 0;
   if(DoBackground == true)
   {
      BackgroundFileNames = CL.GetStringVector("Background");
      NBackground = BackgroundFileNames.size();
   }

   // Do some pre-caching if we read background files.
   // Later on if speed is an issue we can do some optimizations
   vector<TFile *>                BackgroundFiles;
   vector<HiEventTreeMessenger>   MBackgroundEvent;
   vector<PbPbTrackTreeMessenger> MBackgroundTrack;
   vector<EventIndex>             BackgroundIndices;
   if(DoBackground == true)
   {
      for(int iB = 0; iB < NBackground; iB++)
      {
         BackgroundFiles.emplace_back(new TFile(BackgroundFileNames[iB].c_str()));
         MBackgroundEvent.emplace_back(HiEventTreeMessenger(BackgroundFiles[iB]));
         MBackgroundTrack.emplace_back(PbPbTrackTreeMessenger(BackgroundFiles[iB]));

         int EntryCount = MBackgroundEvent[iB].GetEntries();
         for(int iE = 0; iE < EntryCount; iE++)
         {
            MBackgroundEvent[iB].GetEntry(iE);
            EventIndex E;
            E.HF = MBackgroundEvent[iB].hiHF;
            E.File = iB;
            E.Event = iE;
            BackgroundIndices.push_back(E);
         }
      }
   }
   sort(BackgroundIndices.begin(), BackgroundIndices.end());

   // Declare output files
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TNtuple NTuple("NTuple", "Z tree", "mass:pt:eta:phi");
   TTree Tree("Tree", "Tree for ZHadron analysis");

   TH2D H2D("H2D", "", 100, -6, 6, 100, -M_PI, M_PI);

   ZHadronMessenger MZHadron;
   MZHadron.SetBranch(&Tree);

   // Loop over signal files
   for(string InputFileName : InputFileNames)
   {
      MZHadron.Clear();

      // Get the input file
      TFile InputFile(InputFileName.c_str());

      // Setup all the messengers.  In the future we'll add more for triggers etc.
      HiEventTreeMessenger   MSignalEvent(InputFile);
      PbPbTrackTreeMessenger MSignalTrack(InputFile);
      MuTreeMessenger        MSignalMu(InputFile);
      SkimTreeMessenger      MSignalSkim(InputFile);
      TriggerTreeMessenger   MSignalTrigger(InputFile);

      // Start looping over events
      int EntryCount = MSignalEvent.GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         // Progress bar stuff
         if(EntryCount < 300 || (iE % (EntryCount / 250)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }

         TLorentzVector VGenZ, VGenMu1, VGenMu2;

         MSignalEvent.GetEntry(iE);
         MSignalTrack.GetEntry(iE);
         MSignalMu.GetEntry(iE);
         MSignalSkim.GetEntry(iE);
         MSignalTrigger.GetEntry(iE);

         MZHadron.Run   = MSignalEvent.Run;
         MZHadron.Lumi  = MSignalEvent.Lumi;
         MZHadron.Event = MSignalEvent.Event;
         MZHadron.hiBin = MSignalEvent.hiBin;
         MZHadron.hiHF  = MSignalEvent.hiHF;

         // Do event selection and triggers
         if(IsPP == true)
            cerr << "Warning!  pp mode not implemented yet!" << endl;
         else
         {
            if(IsData == true)
            {
               int pprimaryVertexFilter = MSignalSkim.PVFilter;
               int phfCoincFilter2Th4 = MSignalSkim.HFCoincidenceFilter2Th4;
               int pclusterCompatibilityFilter = MSignalSkim.ClusterCompatibilityFilter;
      
               // Event selection criteria
               //    see https://twiki.cern.ch/twiki/bin/viewauth/CMS/HIPhotonJe5TeVpp2017PbPb2018
               if(pprimaryVertexFilter == 0 || phfCoincFilter2Th4 == 0 || pclusterCompatibilityFilter == 0)
                  continue;
      
               //HLT trigger to select dimuon events, see Kaya's note: AN2019_143_v12, p.5
               int HLT_HIL3Mu12 = MSignalTrigger.CheckTriggerStartWith("HLT_HIL3Mu12");
               if(HLT_HIL3Mu12 == 0)
                  continue;
               MZHadron.NCollWeight = 1;
            }
            else
               MZHadron.NCollWeight = FindNColl(MSignalEvent.hiBin);
         }

         // Loop over gen muons
         if(DoGenLevel == true && MSignalMu.NGen > 1)
         {
            for(int igen1 = 0; igen1 < MSignalMu.NGen; igen1++)
            {
               // We only want muon from Z's
               if(MSignalMu.GenMom[igen1] != 23)
                  continue;

               VGenMu1.SetPtEtaPhiM(MSignalMu.GenPT[igen1],
                     MSignalMu.GenEta[igen1],
                     MSignalMu.GenPhi[igen1],
                     M_MU);

               for(int igen2 = igen1 + 1; igen2 < MSignalMu.NGen; igen2++)
               {
                  // We only want muon from Z's
                  if(MSignalMu.GenMom[igen2] != 23)
                     continue;

                  VGenMu2.SetPtEtaPhiM(MSignalMu.GenPT[igen2],
                        MSignalMu.GenEta[igen2],
                        MSignalMu.GenPhi[igen2],
                        M_MU);

                  VGenZ = VGenMu1 + VGenMu2;
                  MZHadron.genZMass->push_back(VGenZ.M());
                  MZHadron.genZPt->push_back  (VGenZ.Pt());
                  MZHadron.genZPhi->push_back (VGenZ.Phi());
                  MZHadron.genZEta->push_back (VGenZ.Eta());

                  MZHadron.genMuPt1->push_back(MSignalMu.GenPT[igen1]);
                  MZHadron.genMuPt2->push_back(MSignalMu.GenPT[igen2]);
                  MZHadron.genMuEta1->push_back(MSignalMu.GenEta[igen1]);
                  MZHadron.genMuEta2->push_back(MSignalMu.GenEta[igen2]);
                  MZHadron.genMuPhi1->push_back(MSignalMu.GenPhi[igen1]);
                  MZHadron.genMuPhi2->push_back(MSignalMu.GenPhi[igen2]);

                  double genDeltaMuEta = MSignalMu.GenEta[igen1] - MSignalMu.GenEta[igen2];
                  double genDeltaMuPhi = PhiRangePositive(DeltaPhi(MSignalMu.GenPhi[igen1], MSignalMu.GenPhi[igen2]));

                  MZHadron.genMuDeta->push_back(genDeltaMuEta);
                  MZHadron.genMuDphi->push_back(genDeltaMuPhi);
                  MZHadron.genMuDR->push_back(sqrt(genDeltaMuEta * genDeltaMuEta + genDeltaMuPhi * genDeltaMuPhi));

                  double genDeltaPhiStar = tan((M_PI - genDeltaMuPhi) / 2)
                     * sqrt(1 - tanh(genDeltaMuEta / 2) * tanh(genDeltaMuEta / 2));
                  MZHadron.genMuDphiS->push_back(genDeltaPhiStar);
               }
            }
         }

         // Loop over reco dimuon pairs
         for(int ipair = 0; ipair < MSignalMu.NDi; ipair++)
         {
            // We want opposite-charge muons with some basic kinematic cuts
            if(MSignalMu.DiCharge1[ipair] == MSignalMu.DiCharge2[ipair])   continue;
            if(fabs(MSignalMu.DiEta1[ipair]) > 2.4)                        continue;
            if(fabs(MSignalMu.DiEta2[ipair]) > 2.4)                        continue;
            if(fabs(MSignalMu.DiPT1[ipair]) < 20)                          continue;
            if(fabs(MSignalMu.DiPT2[ipair]) < 20)                          continue;
            if(MSignalMu.DimuonPassTightCut(ipair) == false)               continue;
            
            MZHadron.zMass->push_back(MSignalMu.DiMass[ipair]);
            MZHadron.zEta->push_back(MSignalMu.DiEta[ipair]);
            MZHadron.zPhi->push_back(MSignalMu.DiPhi[ipair]);
            MZHadron.zPt->push_back(MSignalMu.DiPT[ipair]);

            MZHadron.muEta1->push_back(MSignalMu.DiEta1[ipair]);
            MZHadron.muEta2->push_back(MSignalMu.DiEta2[ipair]);
            MZHadron.muPhi1->push_back(MSignalMu.DiPhi1[ipair]);
            MZHadron.muPhi2->push_back(MSignalMu.DiPhi2[ipair]);

            MZHadron.muPt1->push_back(MSignalMu.DiPT1[ipair]);
            MZHadron.muPt2->push_back(MSignalMu.DiPT2[ipair]);

            double deltaMuEta = MSignalMu.DiEta1[ipair] - MSignalMu.DiEta2[ipair];
            double deltaMuPhi = PhiRangePositive(DeltaPhi(MSignalMu.DiPhi1[ipair], MSignalMu.DiPhi2[ipair]));

            MZHadron.muDeta->push_back(deltaMuEta);
            MZHadron.muDphi->push_back(deltaMuPhi);
            MZHadron.muDR->push_back(sqrt(deltaMuEta * deltaMuEta + deltaMuPhi * deltaMuPhi));

            double deltaPhiStar = tan((M_PI - deltaMuPhi) / 2) * sqrt(1 - tanh(deltaMuEta / 2) * tanh(deltaMuEta / 2));

            MZHadron.muDphiS->push_back(deltaPhiStar);

            NTuple.Fill(MSignalMu.DiMass[ipair], MSignalMu.DiPT[ipair], MSignalMu.DiEta[ipair], MSignalMu.DiPhi[ipair]);
         }

         // Z-track correlation
         if(MZHadron.zMass->size() > 0 && MZHadron.zPt->at(0) > 30)
         {
            // Decide whether to use signal or background for tracks
            EventIndex Location;
            if(DoBackground == true)
            {
               // TODO: find the background event location based on HF.  For now use a dummy one
               Location = BackgroundIndices[0];

               MBackgroundTrack[Location.File].GetEntry(Location.Event);
            }
            PbPbTrackTreeMessenger &MTrack = DoBackground ? MBackgroundTrack[Location.File] : MSignalTrack;

            // Loop over tracks and build the correlation function
            for(int itrack = 0; itrack < MTrack.TrackPT->size(); itrack++)
            {
               if(MTrack.TrackHighPurity->at(itrack) == false)
                  continue;

               double deltaPhi = DeltaPhi(MZHadron.zPhi->at(0), MTrack.TrackPhi->at(itrack) - M_PI);
               double deltaEta = MZHadron.zEta->at(0) - MTrack.TrackEta->at(itrack);

               H2D.Fill(deltaEta, deltaPhi, 0.25);
               H2D.Fill(-deltaEta, deltaPhi, 0.25);
               H2D.Fill(-deltaEta, -deltaPhi, 0.25);
               H2D.Fill(deltaEta, -deltaPhi, 0.25);

               MZHadron.trackDphi->push_back(deltaPhi);
               MZHadron.trackDeta->push_back(deltaEta);
               MZHadron.trackPt->push_back(MTrack.TrackPT->at(itrack));
            }
         }

         MZHadron.FillEntry();
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   OutputFile.cd();
   H2D.Write();
   NTuple.Write();
   Tree.Write();

   // gROOT->GetListOfFiles()->Remove(&OutputFile);
   OutputFile.Close();

   return 0;
}


