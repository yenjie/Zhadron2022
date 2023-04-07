#include <cstdlib>
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
int FindFirstAbove(vector<EventIndex> &Indices, double X);
double GetHFSum(PFTreeMessenger *M);

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
   double MinZPT                 = CL.GetDouble("MinZPT", 20.00);
   bool IsData                   = CL.GetBool("IsData", false);
   bool IsPP                     = CL.GetBool("IsPP", false);
   bool DoGenCorrelation         = CL.GetBool("DoGenCorrelation", false);
   bool DoBackground             = CL.GetBool("DoBackground", false);
   bool DoSumET                  = CL.GetBool("DoSumET", true);
   double MuonVeto               = CL.GetDouble("MuonVeto", 0.01);

   string PFTreeName             = IsPP ? "pfcandAnalyzer/pfTree" : "particleFlowAnalyser/pftree";
   PFTreeName                    = CL.Get("PFTree", PFTreeName);

   Assert(!(IsPP == true && IsData == true), "Data selections for pp not implemented yet");
   Assert(!(DoGenCorrelation == true && DoGenLevel == false), "You need to turn on gen level to do gen correlation!");

   vector<string> BackgroundFileNames;
   int NBackground = 0;
   double HFShift = 0;
   double HFTolerance = 0;
   double HFToleranceFraction = 0;
   int Oversample = 1;
   if(DoBackground == true)
   {
      BackgroundFileNames         = CL.GetStringVector("Background");
      HFShift                     = CL.GetDouble("HFShift");
      HFTolerance                 = CL.GetDouble("Tolerance");
      HFToleranceFraction         = CL.GetDouble("ToleranceFraction");
      NBackground                 = BackgroundFileNames.size();
      Oversample                  = CL.GetInteger("Oversample", 1);
   }

   // Do some pre-caching if we read background files.
   // Later on if speed is an issue we can do some optimizations
   vector<TFile *>                    BackgroundFiles;
   vector<HiEventTreeMessenger *>     MBackgroundEvent;
   vector<GenParticleTreeMessenger *> MBackgroundGen;
   vector<TrackTreeMessenger *>       MBackgroundTrackPP;
   vector<PbPbTrackTreeMessenger *>   MBackgroundTrack;
   vector<PFTreeMessenger *>          MBackgroundPF;
   vector<EventIndex>                 BackgroundIndices;
   if(DoBackground == true)
   {
      for(int iB = 0; iB < NBackground; iB++)
      {
         BackgroundFiles.push_back(new TFile(BackgroundFileNames[iB].c_str()));
         MBackgroundEvent.push_back(new HiEventTreeMessenger(BackgroundFiles[iB]));
         MBackgroundGen.push_back(new GenParticleTreeMessenger(BackgroundFiles[iB]));
         MBackgroundTrackPP.push_back(new TrackTreeMessenger(BackgroundFiles[iB]));
         MBackgroundTrack.push_back(new PbPbTrackTreeMessenger(BackgroundFiles[iB]));
         MBackgroundPF.push_back(new PFTreeMessenger(BackgroundFiles[iB], PFTreeName.c_str()));

         int EntryCount = MBackgroundEvent[iB]->GetEntries();
         for(int iE = 0; iE < EntryCount; iE++)
         {
            MBackgroundEvent[iB]->GetEntry(iE);
            MBackgroundPF[iB]->GetEntry(iE);
            EventIndex E;
            E.HF = DoSumET ? MBackgroundEvent[iB]->hiHF : GetHFSum(MBackgroundPF[iB]);
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
      HiEventTreeMessenger     MSignalEvent(InputFile);
      TrackTreeMessenger       MSignalTrackPP(InputFile);
      PbPbTrackTreeMessenger   MSignalTrack(InputFile);
      GenParticleTreeMessenger MSignalGen(InputFile);
      PFTreeMessenger          MSignalPF(InputFile, PFTreeName.c_str());
      MuTreeMessenger          MSignalMu(InputFile);
      SkimTreeMessenger        MSignalSkim(InputFile);
      TriggerTreeMessenger     MSignalTrigger(InputFile);

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
         MSignalGen.GetEntry(iE);
         if(IsPP == true)
            MSignalTrackPP.GetEntry(iE);
         else
            MSignalTrack.GetEntry(iE);
         MSignalMu.GetEntry(iE);
         MSignalSkim.GetEntry(iE);
         MSignalTrigger.GetEntry(iE);
         MSignalPF.GetEntry(iE);

         MZHadron.Run   = MSignalEvent.Run;
         MZHadron.Lumi  = MSignalEvent.Lumi;
         MZHadron.Event = MSignalEvent.Event;
         MZHadron.hiBin = MSignalEvent.hiBin;
         MZHadron.hiHF  = MSignalEvent.hiHF;

         // Do event selection and triggers
         if(IsPP == true)
         {
            // cerr << "Warning!  pp mode not implemented yet!" << endl;
         }
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

         // Oversample if needed
         for(int iS = 0; iS < Oversample; iS++)
         {
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

            MZHadron.SignalHF = DoSumET ? MSignalEvent.hiHF : GetHFSum(&MSignalPF);

            // Z-track correlation
            bool GoodGenZ = MZHadron.genZPt->size() > 0 && (MZHadron.genZPt->at(0) > MinZPT);
            bool GoodRecoZ = MZHadron.zPt->size() > 0 && (MZHadron.zPt->at(0) > MinZPT);
            if((DoGenCorrelation == true && GoodGenZ == true) || (DoGenCorrelation == false && GoodRecoZ == true))
            {
               // Decide whether to use signal or background for tracks
               EventIndex Location;
               if(DoBackground == true)
               {
                  // find the background event location based on HF
                  double SignalHF = MZHadron.SignalHF;
                  double LowerHF = min(SignalHF - HFTolerance, SignalHF * (1 - HFToleranceFraction)) - HFShift;
                  double HigherHF = max(SignalHF + HFTolerance, SignalHF * (1 + HFToleranceFraction)) - HFShift;

                  if(SignalHF < HFShift)
                     continue;

                  // cout << endl;
                  // cout << SignalHF << " " << LowerHF << " " << HigherHF << " " << HFShift << endl;

                  // cout << MSignalEvent.hiHF << " " << SignalHF << endl;

                  int LowerIndex = FindFirstAbove(BackgroundIndices, LowerHF);
                  int HigherIndex = FindFirstAbove(BackgroundIndices, HigherHF);

                  Assert(HigherIndex > LowerIndex,
                     Form("Warning!  Too few events matched.  Please enlarge tolerance or add more background files.  %f < %f - %f < %f",
                        LowerHF, SignalHF, HFShift, HigherHF));

                  int Index = LowerIndex + rand() % (HigherIndex - LowerIndex);

                  Location = BackgroundIndices[Index];

                  // cout << "Index inside the array" << Index << endl;
                  // cout << "From index " << Location.File << " " << Location.Event << " " << Location.HF << endl;
                  // cout << "Track tree pointer " << MBackgroundTrack[Location.File]->Tree << endl;
                  // MBackgroundEvent[Location.File]->GetEntry(Location.Event);
                  // cout << "From background event HF = " << MBackgroundEvent[Location.File]->hiHF << endl;

                  MZHadron.BackgroundHF = Location.HF;

                  // cout << Location.HF << endl;

                  if(DoGenCorrelation == true)
                     MBackgroundGen[Location.File]->GetEntry(Location.Event);
                  else
                  {
                     if(IsPP == true)
                        MBackgroundTrackPP[Location.File]->GetEntry(Location.Event);
                     else
                        MBackgroundTrack[Location.File]->GetEntry(Location.Event);
                  }
                  
                  // MBackgroundPF[Location.File]->GetEntry(Location.Event);
               }
               PbPbTrackTreeMessenger *MTrack = DoBackground ? MBackgroundTrack[Location.File] : &MSignalTrack;
               TrackTreeMessenger *MTrackPP   = DoBackground ? MBackgroundTrackPP[Location.File] : &MSignalTrackPP;
               GenParticleTreeMessenger *MGen = DoBackground ? MBackgroundGen[Location.File] : &MSignalGen;
               PFTreeMessenger *MPF           = &MSignalPF;

               // Loop over tracks and build the correlation function
               int NTrack = DoGenCorrelation ? MGen->Mult : (IsPP ? MTrackPP->nTrk : MTrack->TrackPT->size());
               for(int itrack = 0; itrack < NTrack; itrack++)
               {
                  if(DoGenCorrelation == false)
                  {
                     bool HP = IsPP ? MTrackPP->highPurity[itrack] : MTrack->TrackHighPurity->at(itrack);
                     if(HP == false)
                        continue;
                  }

                  if(DoGenCorrelation == true)
                  {
                     if(MGen->PT->at(itrack) < 0.4)
                        continue;
                     if(MGen->Eta->at(itrack) < -2.4)
                        continue;
                     if(MGen->Eta->at(itrack) > +2.4)
                        continue;
                  }
              
                  double TrackEta = DoGenCorrelation ? MGen->Eta->at(itrack) : (IsPP ? MTrackPP->trkEta[itrack] : MTrack->TrackEta->at(itrack));
                  double TrackPhi = DoGenCorrelation ? MGen->Phi->at(itrack) : (IsPP ? MTrackPP->trkPhi[itrack] : MTrack->TrackPhi->at(itrack));
                  double TrackPT  = DoGenCorrelation ? MGen->PT->at(itrack) : (IsPP ? MTrackPP->trkPt[itrack] : MTrack->TrackPT->at(itrack));

                  double Mu1Eta = DoGenCorrelation ? MZHadron.genMuEta1->at(0) : MZHadron.muEta1->at(0);
                  double Mu1Phi = DoGenCorrelation ? MZHadron.genMuPhi1->at(0) : MZHadron.muPhi1->at(0);
                  double Mu2Eta = DoGenCorrelation ? MZHadron.genMuEta2->at(0) : MZHadron.muEta2->at(0);
                  double Mu2Phi = DoGenCorrelation ? MZHadron.genMuPhi2->at(0) : MZHadron.muPhi2->at(0);

                  double DeltaEtaMu1 = TrackEta - Mu1Eta;
                  double DeltaEtaMu2 = TrackEta - Mu2Eta;
                  double DeltaPhiMu1 = DeltaPhi(TrackPhi, Mu1Phi);
                  double DeltaPhiMu2 = DeltaPhi(TrackPhi, Mu2Phi);

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  bool MuTagged = false;
                  if(DeltaRMu1 < MuonVeto)   MuTagged = true;
                  if(DeltaRMu2 < MuonVeto)   MuTagged = true;

                  double ZEta = DoGenCorrelation ? MZHadron.genZEta->at(0) : MZHadron.zEta->at(0);
                  double ZPhi = DoGenCorrelation ? MZHadron.genZPhi->at(0) : MZHadron.zPhi->at(0);

                  double deltaEta = TrackEta - ZEta;
                  double deltaPhi = DeltaPhi(TrackPhi, ZPhi);

                  H2D.Fill(+deltaEta, +deltaPhi, 0.25);
                  H2D.Fill(-deltaEta, +deltaPhi, 0.25);
                  H2D.Fill(-deltaEta, -deltaPhi, 0.25);
                  H2D.Fill(+deltaEta, -deltaPhi, 0.25);

                  MZHadron.trackDphi->push_back(deltaPhi);
                  MZHadron.trackDeta->push_back(deltaEta);
                  MZHadron.trackPt->push_back(TrackPT);
                  MZHadron.trackMuTagged->push_back(MuTagged);
               }
            }

            if(GoodRecoZ == true)
            {
               PFTreeMessenger *MPF = &MSignalPF;

               int MaxOppositeIndex = -1;
               double MaxOppositeDEta = 0;
               double MaxOppositeDPhi = 0;
               int MaxIndex = -1;
               double MaxDEta = 0;
               double MaxDPhi = 0;
               
               // Loop over PF candidates to find WTA
               vector<double> OppositePFEta;
               vector<double> OppositePFPhi;
               vector<double> OppositePFPT;
               vector<double> MoreOppositePFEta;
               vector<double> MoreOppositePFPhi;
               vector<double> MoreOppositePFPT;
               for(int iPF = 0; iPF < MPF->ID->size(); iPF++)
               {
                  if(MPF->Eta->at(iPF) < -2.4 || MPF->Eta->at(iPF) > +2.4)   // don't use forward region
                     continue;

                  // cout << iPF << " " << MPF->ID->size() << endl;

                  double DeltaEtaMu1 = MPF->Eta->at(iPF) - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = MPF->Eta->at(iPF) - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(MPF->Phi->at(iPF), MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(MPF->Phi->at(iPF), MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(MPF->Phi->at(iPF), MZHadron.zPhi->at(0));
                  double deltaEta = MPF->Eta->at(iPF) - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     if(MaxOppositeIndex < 0 || MPF->PT->at(iPF) > MPF->PT->at(MaxOppositeIndex))
                     {
                        MaxOppositeIndex = iPF;
                        MaxOppositeDEta = deltaEta;
                        MaxOppositeDPhi = deltaPhi;
                     }
                  }

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     OppositePFEta.push_back(deltaEta);
                     OppositePFPhi.push_back(deltaPhi);
                     OppositePFPT.push_back(MPF->PT->at(iPF));
                  }
                     
                  if(fabs(deltaPhi) > 3 * M_PI / 4)
                  {
                     MoreOppositePFEta.push_back(deltaEta);
                     MoreOppositePFPhi.push_back(deltaPhi);
                     MoreOppositePFPT.push_back(MPF->PT->at(iPF));
                  }
                     
                  if(MaxIndex < 0 || MPF->PT->at(iPF) > MPF->PT->at(MaxIndex))
                  {
                     MaxIndex = iPF;
                     MaxDEta = deltaEta;
                     MaxDPhi = deltaPhi;
                  }
               }

               pair<double, double> WTA        = WTAAxis(OppositePFEta, OppositePFPhi, OppositePFPT);
               pair<double, double> WTAMore    = WTAAxis(MoreOppositePFEta, MoreOppositePFPhi, MoreOppositePFPT);

               MZHadron.maxOppositeDEta        = MaxOppositeDEta;
               MZHadron.maxOppositeDPhi        = MaxOppositeDPhi;
               MZHadron.maxDEta                = MaxDEta;
               MZHadron.maxDPhi                = MaxDPhi;
               MZHadron.maxOppositeWTADEta     = WTA.first;
               MZHadron.maxOppositeWTADPhi     = WTA.second;
               MZHadron.maxMoreOppositeWTADEta = WTAMore.first;
               MZHadron.maxMoreOppositeWTADPhi = WTAMore.second;
            }

            MZHadron.FillEntry();
         }
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

   if(DoBackground == true)
   {
      for(TFile *F : BackgroundFiles)
      {
         if(F == nullptr)
            continue;
         F->Close();
         delete F;
      }
      
      for(HiEventTreeMessenger *M : MBackgroundEvent)
         if(M != nullptr)
            delete M;
      
      for(PbPbTrackTreeMessenger *M : MBackgroundTrack)
         if(M != nullptr)
            delete M;
      
      for(PFTreeMessenger *M : MBackgroundPF)
         if(M != nullptr)
            delete M;
   }

   return 0;
}

int FindFirstAbove(vector<EventIndex> &Indices, double X)
{
   if(X < Indices[0].HF)
      return 0;

   if(X >= Indices[Indices.size()-1].HF)
      return Indices.size();

   int Low = 0;
   int High = Indices.size();

   while(High - Low > 1)
   {
      int Middle = (High + Low) / 2;
      if(X < Indices[Middle].HF)
         High = Middle;
      else
         Low = Middle;
   }

   return Low;
}

double GetHFSum(PFTreeMessenger *M)
{
   if(M == nullptr)
      return -1;
   if(M->Tree == nullptr)
      return -1;

   double Sum = 0;
   for(int iPF = 0; iPF < M->ID->size(); iPF++)
      if(fabs(M->Eta->at(iPF)) > 3 && fabs(M->Eta->at(iPF)) < 5)
         Sum = Sum + M->E->at(iPF);

   // cout << Sum << endl;

   return Sum;
}


