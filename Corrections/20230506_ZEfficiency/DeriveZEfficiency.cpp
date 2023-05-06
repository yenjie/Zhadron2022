#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TLorentzVector.h"
#include "TTree.h"

#include "CommandLine.h"
#include "ProgressBar.h"
#include "PlotHelper4.h"
#include "Messenger.h"
#include "CommonFunctions.h"
#include "SetStyle.h"

#define MAX 10000

int main(int argc, char *argv[]);
int FindBin(double Value, vector<double> &Bins);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output", "EfficiencyPlots.pdf");
   string RootOutputFileName     = CL.Get("RootOutput", "ZEfficiency.root");
   vector<double> Ys             = CL.GetDoubleVector("Y", vector<double>{-10, -2.4, -1.6, -0.8, 0, 0.8, 1.6, 2.4, 10});
   vector<double> PTs            = CL.GetDoubleVector("PT", vector<double>{0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50, 60, 70, 80, 90, 100, 125, 150, 1000});
   double Fraction               = CL.GetDouble("Fraction", 1.00);

   sort(Ys.begin(), Ys.end());
   sort(PTs.begin(), PTs.end());

   TFile OutputFile(RootOutputFileName.c_str(), "RECREATE");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Z efficiency derivation");

   TTree Tree("Tree", "Z efficiency tree");
   double TreeZPT, TreeZY, TreeZPhi, TreeZMass;   bool TreeZHasReco;   double TreeHiBin;
   Tree.Branch("PT", &TreeZPT, "PT/D");
   Tree.Branch("Y", &TreeZY, "Y/D");
   Tree.Branch("Phi", &TreeZPhi, "Phi/D");
   Tree.Branch("Mass", &TreeZMass, "Mass/D");
   Tree.Branch("HasReco", &TreeZHasReco, "Y/O");
   Tree.Branch("HiBin", &TreeHiBin, "HiBin/D");

   int NY = Ys.size() - 1;
   int NPT = PTs.size() - 1;
   double YBins[MAX], PTBins[MAX];
   for(int i = 0; i <= NY; i++)
      YBins[i] = Ys[i];
   for(int i = 0; i <= NPT; i++)
      PTBins[i] = PTs[i];
   YBins[0] = YBins[1] - 2;
   YBins[NY] = YBins[NY-1] + 2;
   PTBins[0] = PTBins[1] * 0.5;
   PTBins[NPT] = PTBins[NPT-1] * 1.25;

   TH1D HNGen("HNGen", ";Number of Gen Z found;", 25, 0, 25);
   TH1D HNReco("HNReco", ";Number of Reco Z found;", 25, 0, 25);
   TH2D HGenZ("HGenZ", ";y;p_{T}", NY, YBins, NPT, PTBins);
   TH2D HRecoZ("HRecoZ", ";y;p_{T}", NY, YBins, NPT, PTBins);
   TH1D HMatchDR("HMatchDR", ";#DeltaR(y-$phi);", 100, 0, 10);
   TH2D HMatchZ("HMatchZ", ";y;p_{T}", NY, YBins, NPT, PTBins);
   TH2D HGenZHasReco("HGenZHasReco", ";y;p_{T}", NY, YBins, NPT, PTBins);
   TH2D HEfficiency("HEfficiency", ";y;p_{T}", NY, YBins, NPT, PTBins);

   HNGen.SetStats(0);
   HNReco.SetStats(0);
   HGenZ.SetStats(0);
   HRecoZ.SetStats(0);
   HMatchDR.SetStats(0);
   HMatchZ.SetStats(0);
   HGenZHasReco.SetStats(0);
   HEfficiency.SetStats(0);

   for(string InputFileName : InputFileNames)
   {
      cout << "Processing file " << InputFileName << endl;

      TFile InputFile(InputFileName.c_str());

      HiEventTreeMessenger MEvent(InputFile);
      MuTreeMessenger MMu(InputFile);

      int EntryCount = MEvent.GetEntries() * Fraction;
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);
      for(int iE = 0; iE < EntryCount; iE++)
      {
         if(EntryCount < 200 || (iE % (EntryCount / 200)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }

         MEvent.GetEntry(iE);
         MMu.GetEntry(iE);

         if(MMu.NGen == 0)
            continue;

         // First find all the Zs in the event
         vector<TLorentzVector> PGenZ, PGenMu1, PGenMu2;
         for(int iMu1 = 0; iMu1 < MMu.NGen; iMu1++)
         {
            if(MMu.GenMom[iMu1] != 23)
               continue;
            if(MMu.GenPT[iMu1] < 20)
               continue;
            if(fabs(MMu.GenEta[iMu1]) > 2.4)
               continue;

            TLorentzVector Mu1;
            Mu1.SetPtEtaPhiM(MMu.GenPT[iMu1], MMu.GenEta[iMu1], MMu.GenPhi[iMu1], M_MU);

            for(int iMu2 = iMu1 + 1; iMu2 < MMu.NGen; iMu2++)
            {
               if(MMu.GenMom[iMu2] != 23)
                  continue;
               if(MMu.GenPT[iMu2] < 20)
                  continue;
               if(fabs(MMu.GenEta[iMu2]) > 2.4)
                  continue;

               TLorentzVector Mu2;
               Mu2.SetPtEtaPhiM(MMu.GenPT[iMu2], MMu.GenEta[iMu2], MMu.GenPhi[iMu2], M_MU);

               if((Mu1 + Mu2).M() < 60)
                  continue;

               PGenZ.push_back(Mu1 + Mu2);
               PGenMu1.push_back(Mu1);
               PGenMu2.push_back(Mu2);
            }
         }

         int NGen = PGenZ.size();
         HNGen.Fill(NGen);
         for(int i = 0; i < NGen; i++)
         {
            int iY = FindBin(PGenZ[i].Y(), Ys);
            int iPT = FindBin(PGenZ[i].Pt(), PTs);
            HGenZ.SetBinContent(iY + 1, iPT + 1, HGenZ.GetBinContent(iY + 1, iPT + 1) + 1);
         }

         if(NGen == 0)   // no need to continue without a gen Z
            continue;

			// Then find all the reco Zs			
         vector<TLorentzVector> PRecoZ, PRecoMu1, PRecoMu2;
			for(int ipair = 0; ipair < MMu.NDi; ipair++)
			{
				// We want opposite-charge muons with some basic kinematic cuts
				if(MMu.DiCharge1[ipair] == MMu.DiCharge2[ipair])   continue;
				if(fabs(MMu.DiEta1[ipair]) > 2.4)                  continue;
				if(fabs(MMu.DiEta2[ipair]) > 2.4)                  continue;
				if(MMu.DiPT1[ipair] < 20)                          continue;
				if(MMu.DiPT2[ipair] < 20)                          continue;
				if(MMu.DimuonPassTightCut(ipair) == false)         continue;
            if(MMu.DiMass[ipair] < 60)                         continue;
            
            TLorentzVector Z, Mu1, Mu2;
            Z.SetPtEtaPhiM(MMu.DiPT[ipair], MMu.DiEta[ipair], MMu.DiPhi[ipair], MMu.DiMass[ipair]);
            Mu1.SetPtEtaPhiM(MMu.DiPT1[ipair], MMu.DiEta1[ipair], MMu.DiPhi1[ipair], M_MU);
            Mu2.SetPtEtaPhiM(MMu.DiPT2[ipair], MMu.DiEta2[ipair], MMu.DiPhi2[ipair], M_MU);

            PRecoZ.push_back(Z);
            PRecoMu1.push_back(Mu1);
            PRecoMu2.push_back(Mu2);
			}
         
         int NReco = PRecoZ.size();
         HNReco.Fill(NReco);
         for(int i = 0; i < NReco; i++)
         {
            int iY = FindBin(PRecoZ[i].Y(), Ys);
            int iPT = FindBin(PRecoZ[i].Pt(), PTs);
            HRecoZ.SetBinContent(iY + 1, iPT + 1, HRecoZ.GetBinContent(iY + 1, iPT + 1) + 1);
         }
         
         if(NReco > 0)
         {
            for(int i = 0; i < NGen; i++)
            {
               int iY = FindBin(PGenZ[i].Y(), Ys);
               int iPT = FindBin(PGenZ[i].Pt(), PTs);
               HGenZHasReco.SetBinContent(iY + 1, iPT + 1, HGenZHasReco.GetBinContent(iY + 1, iPT + 1) + 1);
            }
         }
 
         // Now we match
         for(int i = 0; i < NGen; i++)
         {
            double BestDR = -1;

            for(int j = 0; j < NReco; j++)
            {
               double DY = PGenZ[i].Y() - PRecoZ[j].Y();
               double DPhi = DeltaPhi(PGenZ[i].Phi(), PRecoZ[j].Phi());
               double DR = sqrt(DY * DY + DPhi * DPhi);

               if(BestDR < 0 || DR < BestDR)
                  BestDR = DR;
            }

            HMatchDR.Fill(BestDR);
            if(BestDR < 5)   // Matched!
            {
               int iY = FindBin(PGenZ[i].Y(), Ys);
               int iPT = FindBin(PGenZ[i].Pt(), PTs);
               HMatchZ.SetBinContent(iY + 1, iPT + 1, HMatchZ.GetBinContent(iY + 1, iPT + 1) + 1);
            }
         }

         // Finally fill trees
         for(int i = 0; i < NGen; i++)
         {
            TreeZPT = PGenZ[i].Pt();
            TreeZY = PGenZ[i].Y();
            TreeZPhi = PGenZ[i].Phi();
            TreeZMass = PGenZ[i].M();
            TreeZHasReco = (NReco > 0);
            TreeHiBin = MEvent.hiBin;
            Tree.Fill();
         }
      }
      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   }

   for(int iY = 1; iY <= NY; iY++)
   {
      for(int iPT = 1; iPT <= NPT; iPT++)
      {
         double All = HGenZ.GetBinContent(iY, iPT);
         double Pass = HGenZHasReco.GetBinContent(iY, iPT);
         if(All == 0)
            continue;
         HEfficiency.SetBinContent(iY, iPT, Pass / All);
      }
   }

   PdfFile.AddPlot(HNGen, "hist text00", true);
   PdfFile.AddPlot(HNReco, "hist text00", true);
   PdfFile.AddTextPage("Gen vs reco vs matched");
   PdfFile.AddPlot(HGenZ, "colz text00", true);
   PdfFile.AddPlot(HRecoZ, "colz text00", true);
   PdfFile.AddPlot(HMatchDR, "", true);
   PdfFile.AddPlot(HMatchZ, "colz text00", true);
   PdfFile.AddTextPage("Gen vs has reco");
   PdfFile.AddPlot(HGenZ, "colz text00", true);
   PdfFile.AddPlot(HGenZHasReco, "colz text00", true);
   PdfFile.AddPlot(HEfficiency, "colz, text00", true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   OutputFile.cd();
   HNGen.Write();
   HNReco.Write();
   HGenZ.Write();
   HRecoZ.Write();
   HMatchDR.Write();
   HMatchZ.Write();
   HGenZHasReco.Write();
   Tree.Write();
   OutputFile.Close();

   return 0;
}

int FindBin(double Value, vector<double> &Bins)
{
   for(int i = 0; i < (int)Bins.size() - 1; i++)
      if(Value >= Bins[i] && Value < Bins[i+1])
         return i;
   return -1;
}


