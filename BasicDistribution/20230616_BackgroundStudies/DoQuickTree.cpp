#include <iostream>
using namespace std;

#include "TTree.h"
#include "TFile.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "ProgressBar.h"

#include "trackingEfficiency2018PbPb.h"
#include "TrackResidualCorrector.h"

#define MAX 100000

int main(int argc, char *argv[]);
double GetHFSum(PFTreeMessenger *M);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName = CL.Get("Input");
   string OutputFileName = CL.Get("Output");

   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("Tree", "The one tree to rule them all");

   int NTrack;
   double TrackPT[MAX];
   double TrackEta[MAX];
   double TrackPhi[MAX];
   double TrackWeight[MAX];
   double TrackResidualWeight[MAX];
   double SumHF;
   double hiHF;

   Tree.Branch("NTrack", &NTrack, "NTrack/I");
   Tree.Branch("TrackPT", &TrackPT, "TrackPT[NTrack]/D");
   Tree.Branch("TrackEta", &TrackEta, "TrackEta[NTrack]/D");
   Tree.Branch("TrackPhi", &TrackPhi, "TrackPhi[NTrack]/D");
   Tree.Branch("TrackWeight", &TrackWeight, "TrackWeight[NTrack]/D");
   Tree.Branch("TrackResidualWeight", &TrackResidualWeight, "TrackResidualWeight[NTrack]/D");
   Tree.Branch("SumHF", &SumHF, "SumHF/D");
   Tree.Branch("hiHF", &hiHF, "HiHF/D");

   HiEventTreeMessenger MEvent(InputFile);
   PbPbTrackTreeMessenger MTrack(InputFile);
   PFTreeMessenger MPF(InputFile, "particleFlowAnalyser/pftree");

   TrkEff2018PbPb TrackEfficiency("general", "", false, "Efficiency/");
   TrackResidualCentralityCorrector TrackResidual(vector<string>{"Efficiency/20230522_TrackResidualCorrection_V9_0_20.root","Efficiency/20230522_TrackResidualCorrection_V9_20_60.root","Efficiency/20230522_TrackResidualCorrection_V9_60_100.root","Efficiency/20230522_TrackResidualCorrection_V9_100_200.root"});

   int EntryCount = MEvent.GetEntries();
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 250 || (iE % (EntryCount / 200)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      MEvent.GetEntry(iE);
      MTrack.GetEntry(iE);
      MPF.GetEntry(iE);

      SumHF = GetHFSum(&MPF);
      hiHF = MEvent.hiHF;

      int NTrack = 0;
      int NInputTrack = MTrack.TrackPT->size();
      for(int iT = 0; iT < NInputTrack; iT++)
      {
         if(MTrack.PassZHadron2022Cut(iT) == false)
            continue;

         double PT = MTrack.TrackPT->at(iT);
         double Eta = MTrack.TrackEta->at(iT);
         double Phi = MTrack.TrackPhi->at(iT);

         TrackPT[NTrack]             = PT;
         TrackEta[NTrack]            = Eta;
         TrackPhi[NTrack]            = Phi;
         TrackWeight[NTrack]         = TrackEfficiency.getCorrection(PT, Eta, MEvent.hiBin);
         TrackResidualWeight[NTrack] = TrackResidual.GetCorrectionFactor(PT, Eta, Phi, MEvent.hiBin);
         
         NTrack = NTrack + 1;
      }

      Tree.Fill();
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   OutputFile.cd();
   Tree.Write();

   OutputFile.Close();
   InputFile.Close();

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

