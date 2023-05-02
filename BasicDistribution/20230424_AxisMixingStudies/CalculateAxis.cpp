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

#include "UseFJ.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "CommonFunctions.h"
#include "ProgressBar.h"
#include "CustomAssert.h"
#include "JetCorrector.h"

#include "trackingEfficiency2017pp.h"
#include "trackingEfficiency2018PbPb.h"

int main(int argc, char *argv[]);
double GetHFSum(PFTreeMessenger *M);
double Sum(vector<double> &V);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   double MinZPT                 = CL.GetDouble("MinZPT", 20.00);
   bool IsData                   = CL.GetBool("IsData", false);
   bool IsPP                     = CL.GetBool("IsPP", true);
   bool DoSumET                  = CL.GetBool("DoSumET", true);
   double MuonVeto               = CL.GetDouble("MuonVeto", 0.01);

   string PFTreeName             = IsPP ? "pfcandAnalyzer/pfTree" : "particleFlowAnalyser/pftree";
   PFTreeName                    = CL.Get("PFTree", PFTreeName);

   Assert(!(IsPP == true && IsData == true), "Data selections for pp not implemented yet");

   vector<string> BackgroundFileNames = CL.GetStringVector("Background");
   int NBackground                    = BackgroundFileNames.size();
   int Oversample                     = CL.GetInteger("Oversample", 1);

   // Do some pre-caching if we read background files.
   // Later on if speed is an issue we can do some optimizations
   vector<TFile *>                    BackgroundFiles;
   vector<HiEventTreeMessenger *>     MBackgroundEvent;
   vector<PbPbTrackTreeMessenger *>   MBackgroundTrack;
   vector<PFTreeMessenger *>          MBackgroundPF;
   vector<RhoTreeMessenger *>         MBackgroundRho;
   for(int iB = 0; iB < NBackground; iB++)
   {
      BackgroundFiles.push_back(new TFile(BackgroundFileNames[iB].c_str()));
      MBackgroundEvent.push_back(new HiEventTreeMessenger(BackgroundFiles[iB]));
      MBackgroundTrack.push_back(new PbPbTrackTreeMessenger(BackgroundFiles[iB]));
      MBackgroundPF.push_back(new PFTreeMessenger(BackgroundFiles[iB], "particleFlowAnalyser/pftree"));
      MBackgroundRho.push_back(new RhoTreeMessenger(BackgroundFiles[iB], "hiPuRhoAnalyzer/t"));
   }

   int iBF = 0, iBE = 0;

   // Declare output files
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("Tree", "Tree for ZHadron analysis");
   TTree AxisTree("AxisTree", "axis");

   TH2D H2D("H2D", "", 100, -6, 6, 100, -M_PI, M_PI);

   ZHadronMessenger MZHadron;
   MZHadron.SetBranch(&Tree);

   bool AxisFilled;
   int BackgroundHiBin;
   double BackgroundHiHF;
   double SignalPFSum;
   double MixedPFSum;
   double CSPFSum;
   double PFWTA[4];
   double CSPFWTA[4];
   double TrackWTA[4];
   double HardTrackWTA[4];
   double Track34WTA[4];
   AxisTree.Branch("AxisFilled", &AxisFilled, "AxisFilled/O");
   AxisTree.Branch("BackgroundHiBin", &BackgroundHiBin, "BackgroundHiBin/I");
   AxisTree.Branch("BackgroundHiHF", &BackgroundHiHF, "BackgroundHiHF/D");
   AxisTree.Branch("SignalPFSum", &SignalPFSum, "SignalPFSum/D");
   AxisTree.Branch("MixedPFSum", &MixedPFSum, "MixedPFSum/D");
   AxisTree.Branch("CSPFSum", &CSPFSum, "CSPFSum/D");
   AxisTree.Branch("SignalPFEta", &PFWTA[0], "SignalPFEta/D");
   AxisTree.Branch("SignalPFPhi", &PFWTA[1], "SignalPFPhi/D");
   AxisTree.Branch("MixedPFEta",  &PFWTA[2], "MixedPFEta/D");
   AxisTree.Branch("MixedPFPhi",  &PFWTA[3], "MixedPFPhi/D");
   AxisTree.Branch("SignalCSPFEta", &CSPFWTA[0], "SignalCSPFEta/D");
   AxisTree.Branch("SignalCSPFPhi", &CSPFWTA[1], "SignalCSPFPhi/D");
   AxisTree.Branch("MixedCSPFEta",  &CSPFWTA[2], "MixedCSPFEta/D");
   AxisTree.Branch("MixedCSPFPhi",  &CSPFWTA[3], "MixedCSPFPhi/D");
   AxisTree.Branch("SignalTrackEta", &TrackWTA[0], "SignalTrackEta/D");
   AxisTree.Branch("SignalTrackPhi", &TrackWTA[1], "SignalTrackPhi/D");
   AxisTree.Branch("MixedTrackEta",  &TrackWTA[2], "MixedTrackEta/D");
   AxisTree.Branch("MixedTrackPhi",  &TrackWTA[3], "MixedTrackPhi/D");
   AxisTree.Branch("SignalHardTrackEta", &HardTrackWTA[0], "SignalHardTrackEta/D");
   AxisTree.Branch("SignalHardTrackPhi", &HardTrackWTA[1], "SignalHardTrackPhi/D");
   AxisTree.Branch("MixedHardTrackEta",  &HardTrackWTA[2], "MixedHardTrackEta/D");
   AxisTree.Branch("MixedHardTrackPhi",  &HardTrackWTA[3], "MixedHardTrackPhi/D");
   AxisTree.Branch("SignalTrack34Eta", &Track34WTA[0], "SignalTrack34Eta/D");
   AxisTree.Branch("SignalTrack34Phi", &Track34WTA[1], "SignalTrack34Phi/D");
   AxisTree.Branch("MixedTrack34Eta",  &Track34WTA[2], "MixedTrack34Eta/D");
   AxisTree.Branch("MixedTrack34Phi",  &Track34WTA[3], "MixedTrack34Phi/D");

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
      PFTreeMessenger          MSignalPF(InputFile, PFTreeName);
      MuTreeMessenger          MSignalMu(InputFile);
      SkimTreeMessenger        MSignalSkim(InputFile);
      TriggerTreeMessenger     MSignalTrigger(InputFile);

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

         MSignalEvent.GetEntry(iE);
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
         MZHadron.NPU   = 0;
         if(MSignalEvent.npus->size() == 9)
            MZHadron.NPU = MSignalEvent.npus->at(5);
         else if(MSignalEvent.npus->size() > 1)
            MZHadron.NPU = MSignalEvent.npus->at(0);
         else
            MZHadron.NPU = 0;

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
            }

            MZHadron.SignalHF = DoSumET ? MSignalEvent.hiHF : GetHFSum(&MSignalPF);
            MZHadron.SignalVZ = MSignalEvent.vz;

            AxisFilled = false;
            BackgroundHiBin = -1;
            BackgroundHiHF = -1;
            for(int i = 0; i < 4; i++)   PFWTA[i] = 0;
            for(int i = 0; i < 4; i++)   CSPFWTA[i] = 0;
            for(int i = 0; i < 4; i++)   TrackWTA[i] = 0;
            for(int i = 0; i < 4; i++)   HardTrackWTA[i] = 0;
            
            // Axis studies
            bool GoodRecoZ = MZHadron.zPt->size() > 0 && (MZHadron.zPt->at(0) > MinZPT);
            if(GoodRecoZ == true)
            {
               MBackgroundEvent[iBF]->GetEntry(iBE);
               MBackgroundPF[iBF]->GetEntry(iBE);
               MBackgroundTrack[iBF]->GetEntry(iBE);
               MBackgroundRho[iBF]->GetEntry(iBE);

               BackgroundHiBin = MBackgroundEvent[iBF]->hiBin;
               BackgroundHiHF = DoSumET ? MBackgroundEvent[iBF]->hiHF : GetHFSum(MBackgroundPF[iBF]);

               iBE = iBE + 1;
               if(iBE >= MBackgroundEvent[iBF]->GetEntries())
               {
                  iBF = (iBF + 1) % NBackground;
                  iBE = 0;
               }

               PFTreeMessenger *MPF = &MSignalPF;

               int MaxOppositeIndex = -1;
               double MaxOppositeDEta = 0;
               double MaxOppositeDPhi = 0;
               int MaxIndex = -1;
               double MaxDEta = 0;
               double MaxDPhi = 0;

               // Loop over PF candidates to find WTA
               vector<double> SignalPFEta;
               vector<double> SignalPFPhi;
               vector<double> SignalPFPT;
               vector<double> MixedPFEta;
               vector<double> MixedPFPhi;
               vector<double> MixedPFPT;
               for(int iPF = 0; iPF < MSignalPF.ID->size(); iPF++)
               {
                  if(MSignalPF.Eta->at(iPF) < -2.4 || MSignalPF.Eta->at(iPF) > +2.4)   // don't use forward region
                     continue;

                  double DeltaEtaMu1 = MSignalPF.Eta->at(iPF) - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = MSignalPF.Eta->at(iPF) - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(MSignalPF.Phi->at(iPF), MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(MSignalPF.Phi->at(iPF), MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(MSignalPF.Phi->at(iPF), MZHadron.zPhi->at(0));
                  double deltaEta = MSignalPF.Eta->at(iPF) - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     SignalPFEta.push_back(deltaEta);
                     SignalPFPhi.push_back(deltaPhi);
                     SignalPFPT.push_back(MSignalPF.PT->at(iPF));
                     MixedPFEta.push_back(deltaEta);
                     MixedPFPhi.push_back(deltaPhi);
                     MixedPFPT.push_back(MSignalPF.PT->at(iPF));
                  }
               }
               for(int iPF = 0; iPF < MBackgroundPF[iBF]->ID->size(); iPF++)
               {
                  if(MBackgroundPF[iBF]->Eta->at(iPF) < -2.4 || MBackgroundPF[iBF]->Eta->at(iPF) > +2.4)   // don't use forward region
                     continue;

                  double DeltaEtaMu1 = MBackgroundPF[iBF]->Eta->at(iPF) - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = MBackgroundPF[iBF]->Eta->at(iPF) - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(MBackgroundPF[iBF]->Phi->at(iPF), MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(MBackgroundPF[iBF]->Phi->at(iPF), MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(MBackgroundPF[iBF]->Phi->at(iPF), MZHadron.zPhi->at(0));
                  double deltaEta = MBackgroundPF[iBF]->Eta->at(iPF) - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     MixedPFEta.push_back(deltaEta);
                     MixedPFPhi.push_back(deltaPhi);
                     MixedPFPT.push_back(MBackgroundPF[iBF]->PT->at(iPF));
                  }
               }

               // Now we do the constituent subtraction for the mixed case
               vector<double> CSPFEta;
               vector<double> CSPFPhi;
               vector<double> CSPFPT;
               for(int iPF = 0; iPF < MSignalPF.ID->size(); iPF++)
               {
                  if(MSignalPF.Eta->at(iPF) < -3 || MSignalPF.Eta->at(iPF) > 3)
                     continue;
                  CSPFEta.push_back(MSignalPF.Eta->at(iPF));
                  CSPFPhi.push_back(MSignalPF.Phi->at(iPF));
                  CSPFPT.push_back(MSignalPF.PT->at(iPF));
               }
               SignalPFSum = Sum(CSPFPT);
               for(int iPF = 0; iPF < MBackgroundPF[iBF]->ID->size(); iPF++)
               {
                  if(MBackgroundPF[iBF]->Eta->at(iPF) < -3 || MBackgroundPF[iBF]->Eta->at(iPF) > 3)
                     continue;
                  CSPFEta.push_back(MBackgroundPF[iBF]->Eta->at(iPF));
                  CSPFPhi.push_back(MBackgroundPF[iBF]->Phi->at(iPF));
                  CSPFPT.push_back(MBackgroundPF[iBF]->PT->at(iPF));
               }
               MixedPFSum = Sum(CSPFPT);
               if(MZHadron.zPt->at(0) > 60)
               {
                  cout << "Before " << MixedPFSum << endl;
                  ConstituentSubtraction(CSPFEta, CSPFPhi, CSPFPT,
                     MBackgroundRho[iBF]->EtaMin, MBackgroundRho[iBF]->EtaMax, MBackgroundRho[iBF]->Rho, 0.5, 3.0);
                  cout << "After " << Sum(CSPFPT) << endl;
                  cout << "Signal " << SignalPFSum << endl;
               }
               CSPFSum = Sum(CSPFPT);
               
               vector<double> &SignalCSPFEta = SignalPFEta;
               vector<double> &SignalCSPFPhi = SignalPFPhi;
               vector<double> &SignalCSPFPT = SignalPFPT;
               vector<double> MixedCSPFEta;
               vector<double> MixedCSPFPhi;
               vector<double> MixedCSPFPT;
               for(int iPF = 0; iPF < CSPFEta.size(); iPF++)
               {
                  if(CSPFEta[iPF] < -2.4 || CSPFEta[iPF] > +2.4)   // don't use forward region
                     continue;

                  double DeltaEtaMu1 = CSPFEta[iPF] - MZHadron.muEta1->at(0);
                  double DeltaEtaMu2 = CSPFEta[iPF] - MZHadron.muEta2->at(0);
                  double DeltaPhiMu1 = DeltaPhi(CSPFPhi[iPF], MZHadron.muPhi1->at(0));
                  double DeltaPhiMu2 = DeltaPhi(CSPFPhi[iPF], MZHadron.muPhi2->at(0));

                  double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
                  double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

                  if(DeltaRMu1 < MuonVeto)   continue;
                  if(DeltaRMu2 < MuonVeto)   continue;

                  double deltaPhi = DeltaPhi(CSPFPhi[iPF], MZHadron.zPhi->at(0));
                  double deltaEta = CSPFEta[iPF] - MZHadron.zEta->at(0);

                  if(fabs(deltaPhi) > M_PI / 2)
                  {
                     MixedCSPFEta.push_back(deltaEta);
                     MixedCSPFPhi.push_back(deltaPhi);
                     MixedCSPFPT.push_back(CSPFPT[iPF]);
                  }
               }
               
               // Loop over tracks to find Charged WTA
               vector<double> SignalTrackEta;
               vector<double> SignalTrackPhi;
               vector<double> SignalTrackPT;
               vector<double> MixedTrackEta;
               vector<double> MixedTrackPhi;
               vector<double> MixedTrackPT;
               vector<double> SignalHardTrackEta;
               vector<double> SignalHardTrackPhi;
               vector<double> SignalHardTrackPT;
               vector<double> MixedHardTrackEta;
               vector<double> MixedHardTrackPhi;
               vector<double> MixedHardTrackPT;
               vector<double> SignalTrack34Eta;
               vector<double> SignalTrack34Phi;
               vector<double> SignalTrack34PT;
               vector<double> MixedTrack34Eta;
               vector<double> MixedTrack34Phi;
               vector<double> MixedTrack34PT;
               
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
                     SignalTrackEta.push_back(deltaEta);
                     SignalTrackPhi.push_back(deltaPhi);
                     SignalTrackPT.push_back(TrackPT);
                     MixedTrackEta.push_back(deltaEta);
                     MixedTrackPhi.push_back(deltaPhi);
                     MixedTrackPT.push_back(TrackPT);
                  }

                  if(fabs(deltaPhi) > M_PI / 2 && TrackPT > 4)
                  {
                     SignalHardTrackEta.push_back(deltaEta);
                     SignalHardTrackPhi.push_back(deltaPhi);
                     SignalHardTrackPT.push_back(TrackPT);
                     MixedHardTrackEta.push_back(deltaEta);
                     MixedHardTrackPhi.push_back(deltaPhi);
                     MixedHardTrackPT.push_back(TrackPT);
                  }
                  
                  if(fabs(deltaPhi) > 3 * M_PI / 4)
                  {
                     SignalTrack34Eta.push_back(deltaEta);
                     SignalTrack34Phi.push_back(deltaPhi);
                     SignalTrack34PT.push_back(TrackPT);
                     MixedTrack34Eta.push_back(deltaEta);
                     MixedTrack34Phi.push_back(deltaPhi);
                     MixedTrack34PT.push_back(TrackPT);
                  }
               }
               NTrack = MBackgroundTrack[iBF]->TrackPT->size();
               for(int iTrack = 0; iTrack < NTrack; iTrack++)
               {
                  if(MBackgroundTrack[iBF]->PassZHadron2022Cut(iTrack) == false)
                     continue;
                 
                  double TrackPT  = MBackgroundTrack[iBF]->TrackPT->at(iTrack);
                  double TrackEta = MBackgroundTrack[iBF]->TrackEta->at(iTrack);
                  double TrackPhi = MBackgroundTrack[iBF]->TrackPhi->at(iTrack);

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
                     MixedTrackEta.push_back(deltaEta);
                     MixedTrackPhi.push_back(deltaPhi);
                     MixedTrackPT.push_back(TrackPT);
                  }

                  if(fabs(deltaPhi) > M_PI / 2 && TrackPT > 4)
                  {
                     MixedHardTrackEta.push_back(deltaEta);
                     MixedHardTrackPhi.push_back(deltaPhi);
                     MixedHardTrackPT.push_back(TrackPT);
                  }

                  if(fabs(deltaPhi) > 3 * M_PI / 4)
                  {
                     MixedTrack34Eta.push_back(deltaEta);
                     MixedTrack34Phi.push_back(deltaPhi);
                     MixedTrack34PT.push_back(TrackPT);
                  }
               }

               pair<double, double> SignalPFWTA        = WTAAxis(SignalPFEta, SignalPFPhi, SignalPFPT);
               pair<double, double> MixedPFWTA         = WTAAxis(MixedPFEta, MixedPFPhi, MixedPFPT);
               pair<double, double> SignalCSPFWTA      = WTAAxis(SignalCSPFEta, SignalCSPFPhi, SignalCSPFPT);
               pair<double, double> MixedCSPFWTA       = WTAAxis(MixedCSPFEta, MixedCSPFPhi, MixedCSPFPT);
               pair<double, double> SignalTrackWTA     = WTAAxis(SignalTrackEta, SignalTrackPhi, SignalTrackPT);
               pair<double, double> MixedTrackWTA      = WTAAxis(MixedTrackEta, MixedTrackPhi, MixedTrackPT);
               pair<double, double> SignalHardTrackWTA = WTAAxis(SignalHardTrackEta, SignalHardTrackPhi, SignalHardTrackPT);
               pair<double, double> MixedHardTrackWTA  = WTAAxis(MixedHardTrackEta, MixedHardTrackPhi, MixedHardTrackPT);
               pair<double, double> SignalTrack34WTA   = WTAAxis(SignalTrack34Eta, SignalTrack34Phi, SignalTrack34PT);
               pair<double, double> MixedTrack34WTA    = WTAAxis(MixedTrack34Eta, MixedTrack34Phi, MixedTrack34PT);
            
               AxisFilled = true;
               PFWTA[0] = SignalPFWTA.first;
               PFWTA[1] = SignalPFWTA.second;
               PFWTA[2] = MixedPFWTA.first;
               PFWTA[3] = MixedPFWTA.second;
               CSPFWTA[0] = SignalCSPFWTA.first;
               CSPFWTA[1] = SignalCSPFWTA.second;
               CSPFWTA[2] = MixedCSPFWTA.first;
               CSPFWTA[3] = MixedCSPFWTA.second;
               TrackWTA[0] = SignalTrackWTA.first;
               TrackWTA[1] = SignalTrackWTA.second;
               TrackWTA[2] = MixedTrackWTA.first;
               TrackWTA[3] = MixedTrackWTA.second;
               HardTrackWTA[0] = SignalHardTrackWTA.first;
               HardTrackWTA[1] = SignalHardTrackWTA.second;
               HardTrackWTA[2] = MixedHardTrackWTA.first;
               HardTrackWTA[3] = MixedHardTrackWTA.second;
               Track34WTA[0] = SignalTrack34WTA.first;
               Track34WTA[1] = SignalTrack34WTA.second;
               Track34WTA[2] = MixedTrack34WTA.first;
               Track34WTA[3] = MixedTrack34WTA.second;

               // now, jets on the opposite side
               // actually we can't do this, there is no clustering for mixed event
            }

            AxisTree.Fill();
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
   AxisTree.Write();
   Tree.Write();

   // gROOT->GetListOfFiles()->Remove(&OutputFile);
   OutputFile.Close();

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

   return 0;
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

double Sum(vector<double> &V)
{
   double Result = 0;
   for(double v : V)
      Result = Result + v;
   return Result;
}


