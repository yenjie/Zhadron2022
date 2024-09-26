#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLatex.h"
#include "TLegend.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
TH1D *GetHistogram(TFile &F, string Type, string Tag, int Color);
void HistogramSelfSubtract(TH1D *H);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   vector<int> Colors = GetPrimaryColors();

   CommandLine CL(argc, argv);
   string Tag = CL.Get("Tag", "Centrality_0_30_ZPT_40_200_TrackPT_10_20");
   string OutputFileName = CL.Get("Output", "Plots.pdf");

   TFile FPbPbData("Data.root");
   TFile FPbPbDataMix("DataMix.root");
   TFile FPbPbMC("MC.root");
   TFile FPbPbMCMix("MCMix.root");
   TFile FPPData("PPData.root");
   TFile FPPMC("PPMC.root");

   vector<string> Types{"DeltaPhi", "DeltaEta", "DeltaEtaZSide", "DeltaEtaJetSide"};

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Plots");

   for(string Type : Types)
   {
      TH1D *HPbPbData    = GetHistogram(FPbPbData,    Type, Tag, Colors[0]);
      TH1D *HPbPbMC      = GetHistogram(FPbPbMC,      Type, Tag, Colors[1]);
      TH1D *HPPData      = GetHistogram(FPPData,      Type, Tag, Colors[2]);
      TH1D *HPPMC        = GetHistogram(FPPMC,        Type, Tag, Colors[3]);
      TH1D *HPbPbDataMix = GetHistogram(FPbPbDataMix, Type, Tag, Colors[0]);
      TH1D *HPbPbMCMix   = GetHistogram(FPbPbMCMix,   Type, Tag, Colors[1]);

      if(HPbPbData == nullptr)
      {
         cout << Type << endl;
         continue;
      }

      TLatex Latex;
      Latex.SetTextFont(42);
      Latex.SetTextSize(0.035);
      Latex.SetNDC();

      TCanvas Canvas;

      HistogramSelfSubtract(HPbPbData);
      HistogramSelfSubtract(HPbPbMC);
      HistogramSelfSubtract(HPPData);
      HistogramSelfSubtract(HPPMC);
      HistogramSelfSubtract(HPbPbDataMix);
      HistogramSelfSubtract(HPbPbMCMix);

      HPbPbData->Draw();
      HPbPbMC->Draw("same");
      HPPData->Draw("same");
      HPPMC->Draw("same");

      Latex.DrawLatex(0.10, 0.91, Type.c_str());

      TLegend Legend(0.4, 0.6, 0.7, 0.8);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(HPbPbData, "PbPb data", "pl");
      Legend.AddEntry(HPbPbMC, "PbPb MC", "pl");
      Legend.AddEntry(HPPData, "pp data", "pl");
      Legend.AddEntry(HPPMC, "pp MC", "pl");
      Legend.Draw();

      PdfFile.AddCanvas(Canvas);

      if(HPbPbDataMix != nullptr)   HPbPbData->Add(HPbPbDataMix, -1);
      if(HPbPbMCMix != nullptr)     HPbPbMC->Add(HPbPbMCMix, -1);
      
      HPbPbData->Draw();
      HPbPbMC->Draw("same");
      HPPData->Draw("same");
      HPPMC->Draw("same");

      Latex.DrawLatex(0.10, 0.92, (Type + " subtract").c_str());

      Legend.Draw();

      PdfFile.AddCanvas(Canvas);
   }

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   FPPMC.Close();
   FPPData.Close();
   FPbPbMCMix.Close();
   FPbPbMC.Close();
   FPbPbDataMix.Close();
   FPbPbData.Close();

   return 0;
}

TH1D *GetHistogram(TFile &F, string Type, string Tag, int Color)
{
   TH1D *H  = (TH1D *)F.Get(Form("H%s_%s", Type.c_str(), Tag.c_str()));
   TH1D *HN = (TH1D *)F.Get(Form("HN_%s", Tag.c_str()));

   if(H == nullptr || HN == nullptr)
      return nullptr;

   double Integral = HN->GetBinContent(1);

   H->Scale(1 / Integral);
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double XMin = H->GetXaxis()->GetBinLowEdge(i);
      double XMax = H->GetXaxis()->GetBinUpEdge(i);

      H->SetBinContent(i, H->GetBinContent(i) / (XMax - XMin));
      H->SetBinError(i, H->GetBinError(i) / (XMax - XMin));
   }

   H->SetStats(0);
   H->SetMarkerStyle(20);
   H->SetMarkerColor(Color);
   H->SetLineWidth(2);
   H->SetLineColor(Color);
   // H->SetMinimum(0);

   return H;
}

void HistogramSelfSubtract(TH1D *H)
{
   if(H == nullptr)
      return;

   double SumX = 0;
   double SumXY = 0;
   for(int i = 1; i <= H->GetNbinsX(); i++)
   {
      double XMin = H->GetXaxis()->GetBinLowEdge(i);
      double XMax = H->GetXaxis()->GetBinUpEdge(i);
      double Y = H->GetBinContent(i);

      SumX = SumX + (XMax - XMin);
      SumXY = SumXY + (XMax - XMin) * Y;
   }

   double Mean = SumXY / SumX;
   for(int i = 1; i <= H->GetNbinsX(); i++)
      H->SetBinContent(i, H->GetBinContent(i) - Mean);
}


