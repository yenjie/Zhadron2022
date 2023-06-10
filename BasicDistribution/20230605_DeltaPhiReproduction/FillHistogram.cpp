#include <iostream>
#include <map>
#include <cmath>
#include <vector>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"

#include "CommonFunctions.h"
#include "CommandLine.h"
#include "Messenger.h"

struct Configuration;
int main(int argc, char *argv[]);

struct Configuration
{
   double CMin, CMax;
   double ZPTMin, ZPTMax;
   double PTMin, PTMax;
   int NPVMin, NPVMax;
   string Tag;
   Configuration(double cmin, double cmax, double zptmin, double zptmax, double ptmin, double ptmax, int npvmin, int npvmax)
      : CMin(cmin), CMax(cmax), ZPTMin(zptmin), ZPTMax(zptmax), PTMin(ptmin), PTMax(ptmax), NPVMin(npvmin), NPVMax(npvmax)
   {
      Tag = Form("Centrality_%.0f_%.0f_ZPT_%.0f_%.0f_TrackPT_%.0f_%.0f_PV_%d_%d",
         CMin, CMax, ZPTMin, ZPTMax, PTMin * 10, PTMax * 10, NPVMin, NPVMax);
   }
};

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   bool DoGenZ                   = CL.GetBool("DoGenZ", false);
   bool IsMC                     = CL.GetBool("IsMC", false);
   bool IsPP                     = CL.GetBool("IsPP", false);
   double Fraction               = CL.GetDouble("Fraction", 1.00);

   vector<Configuration> Cs;

   Cs.push_back(Configuration(0,  30,  5,  20, 1, 4, 0, 10));
   Cs.push_back(Configuration(0,  30,  5,  20, 1, 2, 0, 10));

   vector<pair<int, int>> NPV{pair<int, int>(0, 10), pair<int, int>(0, 1), pair<int, int>(2, 10)};
   vector<pair<int, int>> Centrality{pair<int, int>(0, 10), pair<int, int>(10, 30), pair<int, int>(30, 50), pair<int, int>(50, 90), pair<int, int>(0, 30), pair<int, int>(30, 90)};
   vector<pair<double, double>> TrackPT{pair<double, double>(1, 4), pair<double, double>(1, 2), pair<double, double>(2, 5), pair<double, double>(5,10), pair<double, double>(10, 100)};
   vector<double> ZPTMin{30, 40, 60};
   
   for(double ZPT : ZPTMin)
      for(pair<int, int> PV : NPV)
         for(pair<double, double> Track : TrackPT)
            for(pair<int, int> C : Centrality)
               Cs.push_back(Configuration(C.first, C.second, ZPT, 200, Track.first, Track.second, PV.first, PV.second));

   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   vector<TH1D *> HDeltaPhi;
   vector<TH1D *> HDeltaEta;
   vector<TH1D *> HDeltaEtaZSide;
   vector<TH1D *> HDeltaEtaJetSide;
   vector<TH1D *> HN;
   
   for(Configuration &C : Cs)
   {
      HDeltaPhi.push_back(new TH1D(Form("HDeltaPhi_%s", C.Tag.c_str()), ";#Delta#phi;", 10, 0, M_PI));
      HDeltaEta.push_back(new TH1D(Form("HDeltaEta_%s", C.Tag.c_str()), ";#Delta#eta;", 10, 0, 5));
      HDeltaEtaZSide.push_back(new TH1D(Form("HDeltaEtaZSide_%s", C.Tag.c_str()), ";#Delta#eta;", 10, 0, 5));
      HDeltaEtaJetSide.push_back(new TH1D(Form("HDeltaEtaJetSide_%s", C.Tag.c_str()), ";#Delta#eta;", 10, 0, 5));
      HN.push_back(new TH1D(Form("HN_%s", C.Tag.c_str()), ";;", 1, 0, 1));
   }

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing input file " << InputFileName << "..." << endl;

      TFile InputFile(InputFileName.c_str());

      TTree *Tree = (TTree *)InputFile.Get("Tree");
      ZHadronMessenger M(Tree);

      if(Tree == nullptr)
      {
         InputFile.Close();
         continue;
      }

      int EntryCount = M.Tree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         M.GetEntry(iE);

         if(M.zPt->size() == 0)   // no identified Z in this event
            continue;

         double ZPT = M.zPt->at(0);
         double ZEta = M.zEta->at(0);
         double ZPhi = M.zPhi->at(0);

         double EventWeight = M.NCollWeight * M.ZWeight * M.VZWeight;
         // if(IsMC == true && IsPP == false)
         //    EventWeight = M.NCollWeight * M.ZWeight;
         // if(IsMC == true && IsPP == true)
         //    EventWeight = M.ZWeight;

         for(int iC = 0; iC < (int)Cs.size(); iC++)
         {
            if(IsPP == false && M.hiBin * 0.5 < Cs[iC].CMin)    continue;
            if(IsPP == false && M.hiBin * 0.5 >= Cs[iC].CMax)   continue;
            if(ZPT < Cs[iC].ZPTMin)                             continue;
            if(ZPT >= Cs[iC].ZPTMax)                            continue;
            if(M.NVertex < Cs[iC].NPVMin)                       continue;
            if(M.NVertex > Cs[iC].NPVMax)                       continue;
            
            HN[iC]->Fill(0.0, EventWeight);
         }
         
         int TrackCount = M.trackPt->size();
         for(int iT = 0; iT < TrackCount; iT++)
         {
            if(M.trackMuTagged->at(iT) == true)
               continue;

            double TrackEta = M.trackDeta->at(iT) + M.zEta->at(0);
            double TrackPhi = M.trackDphi->at(iT) + M.zPhi->at(0);

            double TrackDEta = TrackEta - ZEta;
            double TrackDPhi = DeltaPhi(TrackPhi, ZPhi);

            double TrackWeight = M.trackWeight->at(iT) * M.trackResidualWeight->at(iT) * EventWeight;

            for(int iC = 0; iC < (int)Cs.size(); iC++)
            {
               if(IsPP == false && M.hiBin * 0.5 < Cs[iC].CMin)    continue;
               if(IsPP == false && M.hiBin * 0.5 >= Cs[iC].CMax)   continue;
               if(ZPT < Cs[iC].ZPTMin)                             continue;
               if(ZPT >= Cs[iC].ZPTMax)                            continue;
               if(M.trackPt->at(iT) < Cs[iC].PTMin)                continue;
               if(M.trackPt->at(iT) >= Cs[iC].PTMax)               continue;
               if(M.NVertex < Cs[iC].NPVMin)                       continue;
               if(M.NVertex > Cs[iC].NPVMax)                       continue;

               HDeltaPhi[iC]->Fill(fabs(TrackDPhi), TrackWeight);
               HDeltaEta[iC]->Fill(fabs(TrackDEta), TrackWeight);
               if(fabs(TrackDPhi) < M_PI / 2)
                  HDeltaEtaZSide[iC]->Fill(fabs(TrackDEta), TrackWeight);
               else
                  HDeltaEtaJetSide[iC]->Fill(fabs(TrackDEta), TrackWeight);
            }   
         }
      }

      InputFile.Close();
   }

   OutputFile.cd();

   for(int i = 0; i < (int)Cs.size(); i++)
   {
      HDeltaPhi[i]->Write();
      HDeltaEta[i]->Write();
      HDeltaEtaZSide[i]->Write();
      HDeltaEtaJetSide[i]->Write();
      HN[i]->Write();
   }

   OutputFile.Close();

   return 0;
}



