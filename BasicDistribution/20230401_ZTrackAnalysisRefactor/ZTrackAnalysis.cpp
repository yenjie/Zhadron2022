#include <cmath>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TNamed.h"
#include "TTree.h"
#include "TH1D.h"
#include "TDirectory.h"
#include "TH2D.h"
#include "TChain.h"

#include "CommonFunctions.h"
#include "CommandLine.h"
#include "ProgressBar.h"

struct Configuration;
int main(int argc, char *argv[]);

struct Configuration
{
public:
   int BinCount;
   double ZPTMin;
   double ZPTMax;
   double CentMin;
   double CentMax;
   double TrackPTMin;
   double TrackPTMax;
public:
   Configuration() {}
   Configuration(int bincount, double zptl, double zpth, double centl, double centh, double trackptl, double trackpth)
   {
      BinCount = bincount;
      ZPTMin = zptl;
      ZPTMax = zpth;
      CentMin = centl;
      CentMax = centh;
      TrackPTMin = trackptl;
      TrackPTMax = trackpth;
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputBase      = CL.Get("InputBase", "/eos/cms/store/group/phys_heavyions_ops/pchou/OutputMC_old/");
   string OutputFileName = CL.Get("Output", "Plots.root");
   double Fraction       = CL.GetDouble("Fraction", 1.00);
   
   // Note: fields are bin count, Z min, Z max, Cent. min, Cent. max, Track min, Track max
   vector<Configuration> C;
   C.push_back(Configuration(40,  0, 2000,  0, 90,  0, 1000));
   C.push_back(Configuration(40, 30,   40,  0, 90,  0, 1000));
   C.push_back(Configuration(40, 40,   60,  0, 90,  0, 1000));
   C.push_back(Configuration(40, 60,   80,  0, 90,  0, 1000));
   C.push_back(Configuration(40, 80,  100,  0, 90,  0, 1000));
   C.push_back(Configuration(40,  0, 2000,  0, 10,  0, 1000));
   C.push_back(Configuration(40,  0, 2000, 10, 30,  0, 1000));
   C.push_back(Configuration(40,  0, 2000, 30, 50,  0, 1000));
   C.push_back(Configuration(40,  0, 2000, 50, 90,  0, 1000));
   C.push_back(Configuration(40,  0, 2000,  0, 90,  1,    2));
   C.push_back(Configuration(40,  0, 2000,  0, 90,  2,    5));
   C.push_back(Configuration(40,  0, 2000,  0, 90,  5,   10));
   C.push_back(Configuration(40,  0, 2000,  0, 90, 10,   20));
   C.push_back(Configuration(40,  0, 2000,  0, 90, 20,   50));
   C.push_back(Configuration(40,  0, 2000,  0, 90, 50,  100));
   //C.push_back(Configuration(40, 20, 2000, 50, 90,  0, 1000));
   //C.push_back(Configuration(40, 40, 2000, 50, 90,  0, 1000));
   //C.push_back(Configuration(40, 20, 2000, 50, 90,  5,   10));
   //C.push_back(Configuration(40, 40, 2000, 50, 90,  5,   10));
   //C.push_back(Configuration(40, 20, 2000, 50, 90, 20,   50));
   //C.push_back(Configuration(40, 40, 2000, 50, 90, 20,   50));
   //C.push_back(Configuration(40, 20, 2000, 50, 90, 50,  100));
   //C.push_back(Configuration(40, 40, 2000, 50, 90, 50,  100));

   vector<TDirectory *>     Folder;
   vector<double>           EventCount;
   vector<TH1D *>           HEventCount;
   vector<TH1D *>           HZPT;
   vector<TH1D *>           HZEta;
   vector<TH1D *>           HZPhi;
   vector<TH1D *>           HZMass;
   vector<TH1D *>           HTrackPT;
   vector<TH1D *>           HTrackEta;
   vector<TH1D *>           HTrackPhi;
   vector<TH1D *>           HEta;
   vector<TH1D *>           HPhi;
   vector<TH2D *>           HEtaPhi;
   vector<TH1D *>           HMaxHadronEta;
   vector<TH1D *>           HMaxHadronPhi;
   vector<TH2D *>           HMaxHadronEtaPhi;
   vector<TH2D *>           HZMaxHadronEtaPhi;
   vector<TH1D *>           HMaxOppositeHadronEta;
   vector<TH1D *>           HMaxOppositeHadronPhi;
   vector<TH2D *>           HMaxOppositeHadronEtaPhi;
   vector<TH2D *>           HZMaxOppositeHadronEtaPhi;
   vector<TH1D *>           HWTAEta;
   vector<TH1D *>           HWTAPhi;
   vector<TH2D *>           HWTAEtaPhi;
   vector<TH2D *>           HZWTAEtaPhi;
   vector<TH1D *>           HWTAMoreEta;
   vector<TH1D *>           HWTAMorePhi;
   vector<TH2D *>           HWTAMoreEtaPhi;
   vector<TH2D *>           HZWTAMoreEtaPhi;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   for(int iC = 0; iC < C.size(); iC++)
   {
      string FolderName =
         Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",
            C[iC].ZPTMin, C[iC].ZPTMax,
            C[iC].CentMin, C[iC].CentMax,
            C[iC].TrackPTMin, C[iC].TrackPTMax);
      replace(FolderName.begin(), FolderName.end(), '.', 'p');

      Folder.push_back(OutputFile.mkdir(FolderName.c_str()));
      
      Folder[iC]->cd();
      EventCount.push_back(0);
      HEventCount.push_back(new TH1D("HEventCount", "", 1, 0, 1));
      
      HZPT.push_back(new TH1D("HZPT", "Z candidate PT", 100, 0, 200));
      HZEta.push_back(new TH1D("HZEta", "Z candidate eta", 100, -3.2, 3.2));
      HZPhi.push_back(new TH1D("HZPhi", "Z candidate phi", 100, -M_PI, M_PI));
      HZMass.push_back(new TH1D("HZMass", "Z candidate mass", 100, 0, 150));
      HTrackPT.push_back(new TH1D("HTrackPT", "Track PT", 100, 0, 200));
      HTrackEta.push_back(new TH1D("HTrackEta", "Track eta", 100, -3.2, 3.2));
      HTrackPhi.push_back(new TH1D("HTrackPhi", "Track phi", 100, -M_PI, M_PI));
      
      HEta.push_back(new TH1D("HEta", "", C[iC].BinCount, 0, 6.3));
      HPhi.push_back(new TH1D("HPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HEtaPhi.push_back(new TH2D("HEtaPhi", "", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HMaxHadronEta.push_back(new TH1D("HMaxHadronEta", "", C[iC].BinCount, 0, 6.3));
      HMaxHadronPhi.push_back(new TH1D("HMaxHadronPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HMaxHadronEtaPhi.push_back(new TH2D("HMaxHadronEtaPhi", "", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      HZMaxHadronEtaPhi.push_back(new TH2D("HZMaxHadronEtaPhi", "Z-axis correlation", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HMaxOppositeHadronEta.push_back(new TH1D("HMaxOppositeHadronEta", "", C[iC].BinCount, 0, 6.3));
      HMaxOppositeHadronPhi.push_back(new TH1D("HMaxOppositeHadronPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HMaxOppositeHadronEtaPhi.push_back(new TH2D("HMaxOppositeHadronEtaPhi", "", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      HZMaxOppositeHadronEtaPhi.push_back(new TH2D("HZMaxOppositeHadronEtaPhi", "Z-axis correlation", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HWTAEta.push_back(new TH1D("HWTAEta", "", C[iC].BinCount, 0, 6.3));
      HWTAPhi.push_back(new TH1D("HWTAPhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HWTAEtaPhi.push_back(new TH2D("HWTAEtaPhi", "", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      HZWTAEtaPhi.push_back(new TH2D("HZWTAEtaPhi", "Z-axis correlation", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      
      HWTAMoreEta.push_back(new TH1D("HWTAMoreEta", "", C[iC].BinCount, 0, 6.3));
      HWTAMorePhi.push_back(new TH1D("HWTAMorePhi", "", C[iC].BinCount, -M_PI * 0.5, M_PI * 1.5));
      HWTAMoreEtaPhi.push_back(new TH2D("HWTAMoreEtaPhi", "", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
      HZWTAMoreEtaPhi.push_back(new TH2D("HZWTAMoreEtaPhi", "Z-axis correlation", 150, -6.4, 6.4, 150, -M_PI * 0.5, M_PI * 1.5));
   }
  
   TChain *Tree = new TChain("Tree");
   Tree->Add((InputBase + "/*.root?#Tree").c_str());
 
   int HiBin;
   vector<double> *ZMass     = nullptr;
   vector<double> *ZPT       = nullptr;
   vector<double> *ZEta      = nullptr;
   vector<double> *ZPhi      = nullptr;
   vector<double> *TrackPT   = nullptr;
   vector<double> *TrackDPhi = nullptr;
   vector<double> *TrackDEta = nullptr;
   double maxOppositeDEta;
   double maxOppositeDPhi;
   double maxDEta;
   double maxDPhi;
   double maxOppositeWTADEta;
   double maxOppositeWTADPhi;
   double maxMoreOppositeWTADEta;
   double maxMoreOppositeWTADPhi;

   Tree->SetBranchAddress("hiBin",                  &HiBin);
   Tree->SetBranchAddress("zMass",                  &ZMass);
   Tree->SetBranchAddress("zPt",                    &ZPT);
   Tree->SetBranchAddress("zEta",                   &ZEta);
   Tree->SetBranchAddress("zPhi",                   &ZPhi);
   Tree->SetBranchAddress("trackPt",                &TrackPT);
   Tree->SetBranchAddress("trackDeta",              &TrackDEta);
   Tree->SetBranchAddress("trackDphi",              &TrackDPhi);
   if(Tree->GetBranch("maxOppositeDEta"))        Tree->SetBranchAddress("maxOppositeDEta",        &maxOppositeDEta);
   if(Tree->GetBranch("maxOppositeDPhi"))        Tree->SetBranchAddress("maxOppositeDPhi",        &maxOppositeDPhi);
   if(Tree->GetBranch("maxDEta"))                Tree->SetBranchAddress("maxDEta",                &maxDEta);
   if(Tree->GetBranch("maxDPhi"))                Tree->SetBranchAddress("maxDPhi",                &maxDPhi);
   if(Tree->GetBranch("maxOppositeWTADEta"))     Tree->SetBranchAddress("maxOppositeWTADEta",     &maxOppositeWTADEta);
   if(Tree->GetBranch("maxOppositeWTADPhi"))     Tree->SetBranchAddress("maxOppositeWTADPhi",     &maxOppositeWTADPhi);
   if(Tree->GetBranch("maxMoreOppositeWTADEta")) Tree->SetBranchAddress("maxMoreOppositeWTADEta", &maxMoreOppositeWTADEta);
   if(Tree->GetBranch("maxMoreOppositeWTADPhi")) Tree->SetBranchAddress("maxMoreOppositeWTADPhi", &maxMoreOppositeWTADPhi);

   int EntryCount = Tree->GetEntries() * Fraction;
   ProgressBar Bar(cout, EntryCount);
   Bar.SetStyle(-1);
   for(int iE = 0; iE < EntryCount; iE++)
   {
      if(EntryCount < 500 || (iE % (EntryCount / 300)) == 0)
      {
         Bar.Update(iE);
         Bar.Print();
      }

      Tree->GetEntry(iE);

      for(int iC = 0; iC < (int)C.size(); iC++)
      {
         bool ZMassRange = false;
         if(ZMass != nullptr && ZMass->size() > 0 && ZMass->at(0) > 60)
            ZMassRange = true;

         bool ZPTRange = false;
         if(ZPT != nullptr && ZPT->size() > 0 && ZPT->at(0) > C[iC].ZPTMin && ZPT->at(0) <= C[iC].ZPTMax)
            ZPTRange = true;

         bool CentRange = false;
         if(HiBin >= C[iC].CentMin * 2 && HiBin < C[iC].CentMax * 2)
            CentRange = true;

         // If we know that the Z candidate is not in range, no need to loop over tracks!
         // Saves a tiny bit of time
         if(!(ZMassRange && ZPTRange && CentRange))
            continue;

         bool SomethingPassed = false;

         int NTrack = 0;
         if(TrackPT != nullptr)
            NTrack = TrackPT->size();
         for(int iT = 0; iT < NTrack; iT++)
         {
            bool TrackPTRange = false;
            if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) < C[iC].TrackPTMax)
               TrackPTRange = true;

            bool PassEvent = ZMassRange && ZPTRange && CentRange;
            bool PassEverything = PassEvent && TrackPTRange;

            double DEtaToMax             = TrackDEta->at(iT) - maxDEta;
            double DPhiToMax             = DeltaPhi(TrackDPhi->at(iT), maxDPhi);
            double DEtaToMaxOpposite     = TrackDEta->at(iT) - maxOppositeDEta;
            double DPhiToMaxOpposite     = DeltaPhi(TrackDPhi->at(iT), maxOppositeDPhi);
            double DEtaToOppositeWTA     = TrackDEta->at(iT) - maxOppositeWTADEta;
            double DPhiToOppositeWTA     = DeltaPhi(TrackDPhi->at(iT), maxOppositeWTADPhi);
            double DEtaToMoreOppositeWTA = TrackDEta->at(iT) - maxMoreOppositeWTADEta;
            double DPhiToMoreOppositeWTA = DeltaPhi(TrackDPhi->at(iT), maxMoreOppositeWTADPhi);

            if(PassEvent)
               SomethingPassed = true;
            if(PassEverything)
            {
               HTrackPT[iC]->Fill(TrackPT->at(iT));
               HTrackEta[iC]->Fill(TrackDEta->at(iT) + ZEta->at(0));
               HTrackPhi[iC]->Fill(PhiRangeSymmetric(TrackDPhi->at(iT) + ZPhi->at(0)));
               
               HEta[iC]->Fill(TrackDEta->at(iT));
               HPhi[iC]->Fill(PhiRangeCorrelation(+TrackDPhi->at(iT)), 0.5);
               HPhi[iC]->Fill(PhiRangeCorrelation(-TrackDPhi->at(iT)), 0.5);

               HEtaPhi[iC]->Fill(+TrackDEta->at(iT), PhiRangeCorrelation(+TrackDPhi->at(iT)), 0.25);
               HEtaPhi[iC]->Fill(+TrackDEta->at(iT), PhiRangeCorrelation(-TrackDPhi->at(iT)), 0.25);
               HEtaPhi[iC]->Fill(-TrackDEta->at(iT), PhiRangeCorrelation(+TrackDPhi->at(iT)), 0.25);
               HEtaPhi[iC]->Fill(-TrackDEta->at(iT), PhiRangeCorrelation(-TrackDPhi->at(iT)), 0.25);
               
               HMaxHadronEta[iC]->Fill(DEtaToMax);
               HMaxHadronPhi[iC]->Fill(PhiRangeCorrelation(+DPhiToMax), 0.5);
               HMaxHadronPhi[iC]->Fill(PhiRangeCorrelation(-DPhiToMax), 0.5);

               HMaxHadronEtaPhi[iC]->Fill(+DEtaToMax, PhiRangeCorrelation(+DPhiToMax), 0.25);
               HMaxHadronEtaPhi[iC]->Fill(+DEtaToMax, PhiRangeCorrelation(-DPhiToMax), 0.25);
               HMaxHadronEtaPhi[iC]->Fill(-DEtaToMax, PhiRangeCorrelation(+DPhiToMax), 0.25);
               HMaxHadronEtaPhi[iC]->Fill(-DEtaToMax, PhiRangeCorrelation(-DPhiToMax), 0.25);
               
               HMaxOppositeHadronEta[iC]->Fill(DEtaToMaxOpposite);
               HMaxOppositeHadronPhi[iC]->Fill(PhiRangeCorrelation(+DPhiToMaxOpposite), 0.5);
               HMaxOppositeHadronPhi[iC]->Fill(PhiRangeCorrelation(-DPhiToMaxOpposite), 0.5);

               HMaxOppositeHadronEtaPhi[iC]->Fill(+DEtaToMaxOpposite, PhiRangeCorrelation(+DPhiToMaxOpposite), 0.25);
               HMaxOppositeHadronEtaPhi[iC]->Fill(+DEtaToMaxOpposite, PhiRangeCorrelation(-DPhiToMaxOpposite), 0.25);
               HMaxOppositeHadronEtaPhi[iC]->Fill(-DEtaToMaxOpposite, PhiRangeCorrelation(+DPhiToMaxOpposite), 0.25);
               HMaxOppositeHadronEtaPhi[iC]->Fill(-DEtaToMaxOpposite, PhiRangeCorrelation(-DPhiToMaxOpposite), 0.25);
               
               HWTAEta[iC]->Fill(DEtaToOppositeWTA);
               HWTAPhi[iC]->Fill(PhiRangeCorrelation(+DPhiToOppositeWTA), 0.5);
               HWTAPhi[iC]->Fill(PhiRangeCorrelation(-DPhiToOppositeWTA), 0.5);

               HWTAEtaPhi[iC]->Fill(+DEtaToOppositeWTA, PhiRangeCorrelation(+DPhiToOppositeWTA), 0.25);
               HWTAEtaPhi[iC]->Fill(+DEtaToOppositeWTA, PhiRangeCorrelation(-DPhiToOppositeWTA), 0.25);
               HWTAEtaPhi[iC]->Fill(-DEtaToOppositeWTA, PhiRangeCorrelation(+DPhiToOppositeWTA), 0.25);
               HWTAEtaPhi[iC]->Fill(-DEtaToOppositeWTA, PhiRangeCorrelation(-DPhiToOppositeWTA), 0.25);
               
               HWTAMoreEta[iC]->Fill(DEtaToMoreOppositeWTA);
               HWTAMorePhi[iC]->Fill(PhiRangeCorrelation(+DPhiToMoreOppositeWTA), 0.5);
               HWTAMorePhi[iC]->Fill(PhiRangeCorrelation(-DPhiToMoreOppositeWTA), 0.5);

               HWTAMoreEtaPhi[iC]->Fill(+DEtaToMoreOppositeWTA, PhiRangeCorrelation(+DPhiToMoreOppositeWTA), 0.25);
               HWTAMoreEtaPhi[iC]->Fill(+DEtaToMoreOppositeWTA, PhiRangeCorrelation(-DPhiToMoreOppositeWTA), 0.25);
               HWTAMoreEtaPhi[iC]->Fill(-DEtaToMoreOppositeWTA, PhiRangeCorrelation(+DPhiToMoreOppositeWTA), 0.25);
               HWTAMoreEtaPhi[iC]->Fill(-DEtaToMoreOppositeWTA, PhiRangeCorrelation(-DPhiToMoreOppositeWTA), 0.25);
            }
         }

         if(SomethingPassed == true)
         {
            EventCount[iC] = EventCount[iC] + 1;
            HEventCount[iC]->Fill(0);
            
            HZPT[iC]->Fill(ZPT->at(0));
            HZEta[iC]->Fill(ZEta->at(0));
            HZPhi[iC]->Fill(ZPhi->at(0));
            HZMass[iC]->Fill(ZMass->at(0));

            HZMaxHadronEtaPhi[iC]->Fill(maxDEta - ZEta->at(0), PhiRangeCorrelation(DeltaPhi(maxDPhi, ZPhi->at(0))));
            HZMaxOppositeHadronEtaPhi[iC]->Fill(maxOppositeDEta - ZEta->at(0), PhiRangeCorrelation(DeltaPhi(maxOppositeDPhi, ZPhi->at(0))));
            HZWTAEtaPhi[iC]->Fill(maxOppositeWTADEta - ZEta->at(0), PhiRangeCorrelation(DeltaPhi(maxOppositeWTADPhi, ZPhi->at(0))));
            HZWTAMoreEtaPhi[iC]->Fill(maxMoreOppositeWTADEta - ZEta->at(0), PhiRangeCorrelation(DeltaPhi(maxMoreOppositeWTADPhi, ZPhi->at(0))));
         }
      }
   }
   Bar.Update(EntryCount);
   Bar.Print();
   Bar.PrintLine();

   for(int iC = 0; iC < (int)C.size(); iC++)
   {
      Folder[iC]->cd();
      TNamed N("EntryCount", Form("%f", EventCount[iC]));
      N.Write();
      HEventCount[iC]->Write();
      HZPT[iC]->Write();
      HZEta[iC]->Write();
      HZPhi[iC]->Write();
      HZMass[iC]->Write();
      HTrackPT[iC]->Write();
      HTrackEta[iC]->Write();
      HTrackPhi[iC]->Write();
      HEta[iC]->Write();
      HPhi[iC]->Write();
      HEtaPhi[iC]->Write();
      HMaxHadronEta[iC]->Write();
      HMaxHadronPhi[iC]->Write();
      HMaxHadronEtaPhi[iC]->Write();
      HZMaxHadronEtaPhi[iC]->Write();
      HMaxOppositeHadronEta[iC]->Write();
      HMaxOppositeHadronPhi[iC]->Write();
      HMaxOppositeHadronEtaPhi[iC]->Write();
      HZMaxOppositeHadronEtaPhi[iC]->Write();
      HWTAEta[iC]->Write();
      HWTAPhi[iC]->Write();
      HWTAEtaPhi[iC]->Write();
      HZWTAEtaPhi[iC]->Write();
      HWTAMoreEta[iC]->Write();
      HWTAMorePhi[iC]->Write();
      HWTAMoreEtaPhi[iC]->Write();
      HZWTAMoreEtaPhi[iC]->Write();
   }

   OutputFile.Close();

   return 0;
}


