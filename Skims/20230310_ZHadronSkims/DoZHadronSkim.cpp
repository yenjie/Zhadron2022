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
#include "JetCorrector.h"

#include "trackingEfficiency2017pp.h"
#include "trackingEfficiency2018PbPb.h"

struct EventIndex;
struct JetRecord;
int main(int argc, char *argv[]);
int FindFirstAbove(vector<EventIndex> &Indices, double X);
double GetHFSum(PFTreeMessenger *M);
double GetGenHFSum(GenParticleTreeMessenger *M);

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

struct JetRecord
{
public:
   double JetPT;
   double JetRawPT;
   double JetDEta;
   double JetDPhi;
   bool JetMuTagged;
public:
   JetRecord(double pt = -1, double rawpt = -1, double deta = -1, double dphi = -1, bool mutagged = false)
      : JetPT(pt), JetRawPT(rawpt), JetDEta(deta), JetDPhi(dphi), JetMuTagged(mutagged)
   {
   }
   bool operator <(const JetRecord &other) const
   {
      if(JetPT < other.JetPT)   return true;
      if(JetPT > other.JetPT)   return false;
      if(JetRawPT < other.JetRawPT)   return true;
      if(JetRawPT > other.JetRawPT)   return false;
      if(JetDEta < other.JetDEta)   return true;
      if(JetDEta > other.JetDEta)   return false;
      if(JetDPhi < other.JetDPhi)   return true;
      if(JetDPhi > other.JetDPhi)   return false;
      if(JetMuTagged < other.JetMuTagged)   return true;
      if(JetMuTagged > other.JetMuTagged)   return false;
      return false;
   }
   bool operator >(const JetRecord &other) const
   {
      return (other < *this);
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
   double MinTrackPT             = CL.GetDouble("MinTrackPT", 1.00);
   bool IsData                   = CL.GetBool("IsData", false);
   bool IsPP                     = CL.GetBool("IsPP", false);
   bool DoGenCorrelation         = CL.GetBool("DoGenCorrelation", false);
   bool DoBackground             = CL.GetBool("DoBackground", false);
   bool DoSumET                  = CL.GetBool("DoSumET", true);
   bool DoExtraAxes              = CL.GetBool("DoExtraAxes", true);
   double MuonVeto               = CL.GetDouble("MuonVeto", 0.01);
   bool DoJet                    = CL.GetBool("DoJet", true);
   vector<string> JECFiles       = CL.GetStringVector("JEC", "");
   string JetTreeName            = CL.Get("Jet", "");
   double MinJetPT               = CL.GetDouble("MinJetPT", 15);

   if(JetTreeName == "")
      DoJet = false;

   bool DoTrackEfficiency        = CL.GetBool("DoTrackEfficiency", true);
   string TrackEfficiencyPath    = (DoTrackEfficiency == true) ? CL.Get("TrackEfficiencyPath") : "";

   string PFTreeName             = IsPP ? "pfcandAnalyzer/pfTree" : "particleFlowAnalyser/pftree";
   PFTreeName                    = CL.Get("PFTree", PFTreeName);

   Assert(!(IsPP == true && IsData == true), "Data selections for pp not implemented yet");
   Assert(!(DoGenCorrelation == true && DoGenLevel == false), "You need to turn on gen level to do gen correlation!");

   JetCorrector JEC(JECFiles);

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

   TrkEff2017pp *TrackEfficiencyPP = nullptr;
   TrkEff2018PbPb *TrackEfficiencyPbPb = nullptr;
   if(DoTrackEfficiency == true)
   {
      if(IsPP == true)
         TrackEfficiencyPP = new TrkEff2017pp(false, TrackEfficiencyPath);
      else
         TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "", false, TrackEfficiencyPath);
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
         MBackgroundPF.push_back(new PFTreeMessenger(BackgroundFiles[iB], PFTreeName));

         int EntryCount = MBackgroundEvent[iB]->GetEntries();
         for(int iE = 0; iE < EntryCount; iE++)
         {
            MBackgroundEvent[iB]->GetEntry(iE);
            MBackgroundPF[iB]->GetEntry(iE);
            EventIndex E;
            E.HF = DoGenCorrelation ? GetGenHFSum(MBackgroundGen[iB]) : (DoSumET ? MBackgroundEvent[iB]->hiHF : GetHFSum(MBackgroundPF[iB]));
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
      PFTreeMessenger          MSignalPF(InputFile, PFTreeName);
      MuTreeMessenger          MSignalMu(InputFile);
      SkimTreeMessenger        MSignalSkim(InputFile);
      TriggerTreeMessenger     MSignalTrigger(InputFile);
      JetTreeMessenger         MSignalJet(InputFile, JetTreeName);

      // Start looping over events
      int EntryCount = MSignalEvent.GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);
      // Bar.SetStyle(6);

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
         if(DoJet == true)
            MSignalJet.GetEntry(iE);

         MZHadron.Run   = MSignalEvent.Run;
         MZHadron.Lumi  = MSignalEvent.Lumi;
         MZHadron.Event = MSignalEvent.Event;
         MZHadron.hiBin = MSignalEvent.hiBin;
         MZHadron.hiHF  = MSignalEvent.hiHF;
         MZHadron.NPU   = 0;
         if(MSignalEvent.npus->size() == 9)
            MZHadron.NPU = MSignalEvent.npus->at(5);
         else if(MSignalEvent.npus->size() > 1)
            MZHadron.NPU = MSignalEvent.npus->at(0);
         else
            MZHadron.NPU = 0;

         // Fill vertex information
         MZHadron.NVertex = 0;
         int BestVertex = -1;
         for(int i = 0; i < (IsPP ? MSignalTrackPP.nVtx : MSignalTrack.VX->size()); i++)
         {
            // TODO: Add vertex selections here

            if(IsPP == true && (BestVertex < 0 || MSignalTrackPP.sumPtVtx[i] > MSignalTrackPP.sumPtVtx[BestVertex]))
               BestVertex = i;
            if(IsPP == false && (BestVertex < 0 || MSignalTrack.VPTSum->at(i) > MSignalTrack.VPTSum->at(BestVertex)))
               BestVertex = i;

            MZHadron.NVertex = MZHadron.NVertex + 1;
         }
         
         if(BestVertex >= 0)
         {
            MZHadron.VX      = IsPP ? MSignalTrackPP.xVtx[BestVertex] : MSignalTrack.VX->at(BestVertex);
            MZHadron.VY      = IsPP ? MSignalTrackPP.yVtx[BestVertex] : MSignalTrack.VY->at(BestVertex);
            MZHadron.VZ      = IsPP ? MSignalTrackPP.zVtx[BestVertex] : MSignalTrack.VZ->at(BestVertex);
            MZHadron.VXError = IsPP ? MSignalTrackPP.xVtxErr[BestVertex] : MSignalTrack.VXError->at(BestVertex);
            MZHadron.VYError = IsPP ? MSignalTrackPP.yVtxErr[BestVertex] : MSignalTrack.VYError->at(BestVertex);
            MZHadron.VZError = IsPP ? MSignalTrackPP.zVtxErr[BestVertex] : MSignalTrack.VZError->at(BestVertex);
         }

         // Do event selection and triggers
         if(IsPP == true)
         {
            if(IsData == true)
               cerr << "Warning!  pp data mode not implemented yet!" << endl;
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

            MZHadron.SignalHF = DoGenCorrelation ? GetGenHFSum(&MSignalGen) : (DoSumET ? MSignalEvent.hiHF : GetHFSum(&MSignalPF));

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
                  if(DoGenCorrelation == false)   // track selection on reco
                  {
                     if(IsPP == true && MTrackPP->PassZHadron2022Cut(itrack) == false)
                        continue;
                     if(IsPP == false && MTrack->PassZHadron2022Cut(itrack) == false)
                        continue;
                     if((IsPP ? MTrackPP->trkPt[itrack] : MTrack->TrackPT->at(itrack)) < MinTrackPT)
                        continue;
                  }

                  if(DoGenCorrelation == true)
                  {
                     if(MGen->PT->at(itrack) < MinTrackPT)
                        continue;
                     if(MGen->Eta->at(itrack) < -2.4)
                        continue;
                     if(MGen->Eta->at(itrack) > +2.4)
                        continue;
                     if(MGen->DaughterCount->at(itrack) > 0)
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

                  double TrackCorrection = 1;
                  if(DoTrackEfficiency == true)
                  {
                     if(IsPP == true)
                        TrackCorrection = TrackEfficiencyPP->getCorrection(TrackPT, TrackEta);
                     else
                        TrackCorrection = TrackEfficiencyPbPb->getCorrection(TrackPT, TrackEta, MZHadron.hiBin);
                  }
                  MZHadron.trackWeight->push_back(TrackCorrection);
               }
            }

            if(GoodRecoZ == true && DoJet == true)
            {
               JetRecord MaxJet12, MaxJet34, MaxJet56, MaxJet78;

               vector<JetRecord> Jets;
               for(int iJ = 0; iJ < MSignalJet.JetCount; iJ++)
               {
                  JEC.SetJetEta(MSignalJet.JetEta[iJ]);
                  JEC.SetJetPhi(MSignalJet.JetPhi[iJ]);
                  JEC.SetJetPT(MSignalJet.JetRawPT[iJ]);
                  JEC.SetJetArea(0.5);
                  JEC.SetRho(0);
                  
                  double JetEta = MSignalJet.JetEta[iJ];
                  double JetPhi = MSignalJet.JetPhi[iJ];
                  double JetPT  = JEC.GetCorrectedPT();

                  if(JetEta < -2 || JetEta > 2)
                     continue;
                  if(JetPT < MinJetPT)   // Skip small jets
                     continue;

                  double Mu1Eta = MZHadron.muEta1->at(0);
                  double Mu1Phi = MZHadron.muPhi1->at(0);
                  double Mu2Eta = MZHadron.muEta2->at(0);
                  double Mu2Phi = MZHadron.muPhi2->at(0);

                  double DeltaEtaMu1 = JetEta - Mu1Eta;
                  double DeltaEtaMu2 = JetEta - Mu2Eta;
                  double DeltaPhiMu1 = DeltaPhi(JetPhi, Mu1Phi);
                  double DeltaPhiMu2 = DeltaPhi(JetPhi, Mu2Phi);

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  bool MuTagged = false;
                  if(DeltaRMu1 < MuonVeto)   MuTagged = true;
                  if(DeltaRMu2 < MuonVeto)   MuTagged = true;

                  double ZEta = MZHadron.zEta->at(0);
                  double ZPhi = MZHadron.zPhi->at(0);

                  double deltaEta = JetEta - ZEta;
                  double deltaPhi = DeltaPhi(JetPhi, ZPhi);

                  JetRecord ThisJet(JetPT, MSignalJet.JetRawPT[iJ], deltaEta, deltaPhi, MuTagged);

                  Jets.push_back(ThisJet);

                  if(fabs(deltaPhi) > M_PI * 1 / 2 && ThisJet > MaxJet12)   MaxJet12 = ThisJet;
                  if(fabs(deltaPhi) > M_PI * 3 / 4 && ThisJet > MaxJet34)   MaxJet34 = ThisJet;
                  if(fabs(deltaPhi) > M_PI * 5 / 6 && ThisJet > MaxJet56)   MaxJet56 = ThisJet;
                  if(fabs(deltaPhi) > M_PI * 7 / 8 && ThisJet > MaxJet78)   MaxJet78 = ThisJet;
               }
               sort(Jets.begin(), Jets.end(), greater<JetRecord>());

               for(int iJ = 0; iJ < (int)Jets.size(); iJ++)
               {
                  MZHadron.jetPt->push_back(Jets[iJ].JetPT);
                  MZHadron.jetDeta->push_back(Jets[iJ].JetDEta);
                  MZHadron.jetDphi->push_back(Jets[iJ].JetDPhi);
                  MZHadron.jetMuTagged->push_back(Jets[iJ].JetMuTagged);
               }

               MZHadron.maxOppositeJet12Pt   = MaxJet12.JetPT;
               MZHadron.maxOppositeJet12DEta = MaxJet12.JetDEta;
               MZHadron.maxOppositeJet12DPhi = MaxJet12.JetDPhi;
               MZHadron.maxOppositeJet34Pt   = MaxJet34.JetPT;
               MZHadron.maxOppositeJet34DEta = MaxJet34.JetDEta;
               MZHadron.maxOppositeJet34DPhi = MaxJet34.JetDPhi;
               MZHadron.maxOppositeJet56Pt   = MaxJet56.JetPT;
               MZHadron.maxOppositeJet56DEta = MaxJet56.JetDEta;
               MZHadron.maxOppositeJet56DPhi = MaxJet56.JetDPhi;
               MZHadron.maxOppositeJet78Pt   = MaxJet78.JetPT;
               MZHadron.maxOppositeJet78DEta = MaxJet78.JetDEta;
               MZHadron.maxOppositeJet78DPhi = MaxJet78.JetDPhi;
            }

            if(GoodRecoZ == true && DoExtraAxes == true)
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

               // Loop over tracks to find Charged WTA
               vector<double> OppositeTrackEta;
               vector<double> OppositeTrackPhi;
               vector<double> OppositeTrackPT;
               vector<double> MoreOppositeTrackEta;
               vector<double> MoreOppositeTrackPhi;
               vector<double> MoreOppositeTrackPT;
               
               int NTrack = IsPP ? MSignalTrackPP.nTrk : MSignalTrack.TrackPT->size();
               for(int iTrack = 0; iTrack < NTrack; iTrack++)
               {
                  if(IsPP == true && MSignalTrackPP.PassZHadron2022Cut(iTrack) == false)
                     continue;
                  if(IsPP == false && MSignalTrack.PassZHadron2022Cut(iTrack) == false)
                     continue;
                 
                  double TrackPT = IsPP ? MSignalTrackPP.trkPt[iTrack] : MSignalTrack.TrackPT->at(iTrack);
                  double TrackEta = IsPP ? MSignalTrackPP.trkEta[iTrack] : MSignalTrack.TrackEta->at(iTrack);
                  double TrackPhi = IsPP ? MSignalTrackPP.trkPhi[iTrack] : MSignalTrack.TrackPhi->at(iTrack);

                  double DeltaEtaMu1 = TrackEta - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = TrackEta - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(TrackPhi, MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(TrackPhi, MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(TrackPhi, MZHadron.zPhi->at(0));
                  double deltaEta = TrackEta - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     OppositeTrackEta.push_back(deltaEta);
                     OppositeTrackPhi.push_back(deltaPhi);
                     OppositeTrackPT.push_back(TrackPT);
                  }

                  if(fabs(deltaPhi) > 3 * M_PI / 4)
                  {
                     MoreOppositeTrackEta.push_back(deltaEta);
                     MoreOppositeTrackPhi.push_back(deltaPhi);
                     MoreOppositeTrackPT.push_back(TrackPT);
                  }
               }

               pair<double, double> WTA            = WTAAxis(OppositePFEta, OppositePFPhi, OppositePFPT);
               pair<double, double> WTAMore        = WTAAxis(MoreOppositePFEta, MoreOppositePFPhi, MoreOppositePFPT);
               pair<double, double> ChargedWTA     = WTAAxis(OppositeTrackEta, OppositeTrackPhi, OppositeTrackPT);
               pair<double, double> ChargedWTAMore = WTAAxis(MoreOppositeTrackEta, MoreOppositeTrackPhi, MoreOppositeTrackPT);

               MZHadron.maxOppositeDEta               = MaxOppositeDEta;
               MZHadron.maxOppositeDPhi               = MaxOppositeDPhi;
               MZHadron.maxDEta                       = MaxDEta;
               MZHadron.maxDPhi                       = MaxDPhi;
               MZHadron.maxOppositeWTADEta            = WTA.first;
               MZHadron.maxOppositeWTADPhi            = WTA.second;
               MZHadron.maxMoreOppositeWTADEta        = WTAMore.first;
               MZHadron.maxMoreOppositeWTADPhi        = WTAMore.second;
               MZHadron.maxOppositeChargedWTADEta     = ChargedWTA.first;
               MZHadron.maxOppositeChargedWTADPhi     = ChargedWTA.second;
               MZHadron.maxMoreOppositeChargedWTADEta = ChargedWTAMore.first;
               MZHadron.maxMoreOppositeChargedWTADPhi = ChargedWTAMore.second;
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

   if(DoTrackEfficiency == true)
   {
      if(TrackEfficiencyPP != nullptr)
         delete TrackEfficiencyPP;
      if(TrackEfficiencyPbPb != nullptr)
         delete TrackEfficiencyPbPb;
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

double GetGenHFSum(GenParticleTreeMessenger *M)
{
   if(M == nullptr)
      return -1;
   if(M->Tree == nullptr)
      return -1;

   double Sum = 0;
   for(int iGen = 0; iGen < M->Mult; iGen++)
   {
      if(fabs(M->Eta->at(iGen)) < 3)
         continue;
      if(fabs(M->Eta->at(iGen)) > 5)
         continue;
      if(M->DaughterCount->at(iGen) > 0)
         continue;
      Sum = Sum + M->PT->at(iGen) * cosh(M->Eta->at(iGen));
   }

   return Sum;
}


