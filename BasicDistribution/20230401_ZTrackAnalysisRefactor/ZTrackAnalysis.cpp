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
   C.push_back(Configuration(40,  0, 2000,  0, 90,  2,    5));
   C.push_back(Configuration(40,  0, 2000,  0, 90,  5,   10));
   C.push_back(Configuration(40,  0, 2000,  0, 90, 10,   20));
   C.push_back(Configuration(40,  0, 2000,  0, 90, 20,   50));
   C.push_back(Configuration(40,  0, 2000,  0, 90, 50,  100));
   C.push_back(Configuration(40, 20, 2000, 50, 90,  0, 1000));
   C.push_back(Configuration(40, 40, 2000, 50, 90,  0, 1000));
   C.push_back(Configuration(40, 20, 2000, 50, 90,  5,   10));
   C.push_back(Configuration(40, 40, 2000, 50, 90,  5,   10));
   C.push_back(Configuration(40, 20, 2000, 50, 90, 20,   50));
   C.push_back(Configuration(40, 40, 2000, 50, 90, 20,   50));
   C.push_back(Configuration(40, 20, 2000, 50, 90, 50,  100));
   C.push_back(Configuration(40, 40, 2000, 50, 90, 50,  100));

   vector<TDirectory *>     Folder;
   vector<double>           EventCount;
   vector<TH1D *>           HEta;
   vector<TH1D *>           HPhi;
   vector<TH2D *>           HEtaPhi;

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   for(int iC = 0; iC < C.size(); iC++)
   {
      string FolderName =
         Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.1f_%.1f",
            C[iC].ZPTMin, C[iC].ZPTMax,
            C[iC].CentMin, C[iC].CentMax,
            C[iC].TrackPTMin, C[iC].TrackPTMax);

      Folder.push_back(OutputFile.mkdir(FolderName.c_str()));
      
      Folder[iC]->cd();
      EventCount.push_back(0);
      HEta.push_back(new TH1D("HEta", "", C[iC].BinCount, 0, 6.3));
      HPhi.push_back(new TH1D("HPhi", "", C[iC].BinCount, -M_PI, M_PI));
      HEtaPhi.push_back(new TH2D("HEtaPhi", "", 150, -3.2, 3.2, 150, -M_PI, M_PI));
   }
  
   TChain *Tree = new TChain("Tree");
   Tree->Add((InputBase + "/*.root?#Tree").c_str());
 
   int HiBin;
   vector<double> *ZMass     = nullptr;
   vector<double> *ZPT       = nullptr;
   vector<double> *TrackPT   = nullptr;
   vector<double> *TrackDPhi = nullptr;
   vector<double> *TrackDEta = nullptr;

   Tree->SetBranchAddress("hiBin",     &HiBin);
   Tree->SetBranchAddress("zMass",     &ZMass);
   Tree->SetBranchAddress("zPt",       &ZPT);
   Tree->SetBranchAddress("trackPt",   &TrackPT);
   Tree->SetBranchAddress("trackDeta", &TrackDEta);
   Tree->SetBranchAddress("trackDphi", &TrackDPhi);

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

         bool SomethingPassed = false;

         int NTrack = 0;
         if(TrackPT != nullptr)
            NTrack = TrackPT->size();
         for(int iT = 0; iT < NTrack; iT++)
         {
            bool TrackPTRange = false;
            if(TrackPT->at(iT) > C[iC].TrackPTMin && TrackPT->at(iT) > C[iC].TrackPTMax)
               TrackPTRange = true;

            bool PassEvent = ZMassRange && ZPTRange && CentRange;
            bool PassEverything = PassEvent && TrackPTRange;

            if(PassEvent)
               SomethingPassed = true;
            if(PassEverything)
            {
               HEta[iC]->Fill(TrackDEta->at(iT));
               HPhi[iC]->Fill(TrackDPhi->at(iT));

               HEtaPhi[iC]->Fill(+TrackDEta->at(iT), +TrackDPhi->at(iT), 0.25);
               HEtaPhi[iC]->Fill(+TrackDEta->at(iT), -TrackDPhi->at(iT), 0.25);
               HEtaPhi[iC]->Fill(-TrackDEta->at(iT), +TrackDPhi->at(iT), 0.25);
               HEtaPhi[iC]->Fill(-TrackDEta->at(iT), -TrackDPhi->at(iT), 0.25);
            }
         }

         if(SomethingPassed == true)
            EventCount[iC] = EventCount[iC] + 1;
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
      HEta[iC]->Write();
      HPhi[iC]->Write();
      HEtaPhi[iC]->Write();
   }

   OutputFile.Close();

   return 0;
}


