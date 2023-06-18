#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TGraph.h"

#include "SetStyle.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();

   SetThesisStyle();

   PdfFileHelper PdfFile("Meow.pdf");

   TFile F1("MCV15_Result1X.root");
   TFile F2("PPMCV15_Result11.root");
   TFile F3("MB.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");
   TTree *T3 = (TTree *)F3.Get("Tree");

   TH1D H1("H1", "", 100, 0, 100);
   T2->Draw("Sum$((trackPt>1&&trackPt<2)*trackWeight*trackResidualWeight*(trackMuTagged==0))>>H1", "zPt[0]>30", "");
   double Mean = H1.GetMean();

   PdfFile.AddPlot(H1);

   const static int NBin = 20;
   double XMin = 100;
   double XMax = 140000;
   double Bins[NBin+1];
   for(int i = 0; i <= NBin; i++)
      Bins[i] = exp(log(XMin) + (log(XMax) - log(XMin)) / NBin * i);

   TProfile P1("P1", ";HFSum;NTrack/event (1-2 GeV)", NBin, Bins);
   TProfile P3("P3", ";HFSum;NTrack/event (1-2 GeV)", NBin, Bins);
   T1->Draw("Sum$((trackPt>1&&trackPt<2)*trackWeight*trackResidualWeight):SignalHF>>P1", "zPt[0]>30", "prof");
   T3->Draw("Sum$((TrackPT>1&&TrackPT<2)*TrackWeight*TrackResidualWeight):SumHF+682>>P3", "", "prof same");
   // T1->Draw("Sum$((trackPt>1&&trackPt<2)):SignalHF>>P1", "zPt[0]>30", "prof");
   // T3->Draw("Sum$((TrackPT>1&&TrackPT<2)):SumHF+660>>P3", "", "prof same");

   P1.SetStats(0);
   P3.SetStats(0);

   P1.SetMarkerColor(Colors[0]);
   P1.SetLineColor(Colors[0]);
   P3.SetMarkerColor(Colors[1]);
   P3.SetLineColor(Colors[1]);

   TCanvas Canvas;
   Canvas.SetLogx();
   Canvas.SetLogy();
   P1.Draw();
   P3.Draw("same");
   PdfFile.AddCanvas(Canvas);

   TH1D HD("HD", ";HFSum;", NBin, Bins);
   HD.SetStats(0);
   for(int i = 1; i <= NBin; i++)
   {
      HD.SetBinContent(i, P1.GetBinContent(i) - P3.GetBinContent(i));
      double E1 = P1.GetBinError(i);
      double E3 = P3.GetBinError(i);
      HD.SetBinError(i, sqrt(E1 * E1 + E3 * E3));
   }

   TGraph G;
   G.SetPoint(0, XMin, Mean);
   G.SetPoint(1, XMax, Mean);

   Canvas.SetLogy(false);
   HD.Draw();
   G.Draw("l");
   PdfFile.AddCanvas(Canvas);

   TH2D HCent("HCent", ";HFSum;hiBin", NBin, Bins, 200, 0, 200);
   HCent.SetStats(0);

   T1->Draw("hiBin:SignalHF>>HCent", "", "colz");
   PdfFile.AddPlot(HCent, "colz", false, false, false, true);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}


