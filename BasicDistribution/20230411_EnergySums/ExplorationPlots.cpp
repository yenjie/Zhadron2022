#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TGraph.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TProfile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

#define MAX 1000

int main(int argc, char *argv[]);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   vector<int> Colors = GetCVDColors6();

   CommandLine CL(argc, argv);

   string InputEmbedded    = CL.Get("Embedded");
   string InputHydjet      = CL.Get("Hydjet");
   string InputNonembedded = CL.Get("Nonembedded");
   string OutputFileName   = CL.Get("Output");

   double NominalHFShift   = CL.GetDouble("HFShift", 660);
   double AutoFactor       = CL.GetDouble("AutoFactor", 1.00);

   TProfile PEmbedded("PEmbedded", ";HF;Central", 100, 0, 10000);
   TProfile PHydjet("PHydjet", ";HF;Central", 100, 0, 10000);
   TProfile PEmbeddedShift("PEmbeddedShift", ";Shifted HF;Central", 100, 0, 10000);
   TProfile PHydjetShift("PHydjetShift", ";HF;Shifted central", 100, 0, 10000);
   TH1D HDifference("HDifference", ";Shifted HF;Difference", 100, 0, 10000);
   TH1D HNonembeddedCentral("HNonembeddedCentral", ";;", 100, 0, 3000);
   TH1D HNonembeddedHF("HNonembeddedHF", ";;", 100, 0, 5000);

   TFile FEmbedded(InputEmbedded.c_str());
   TFile FHydjet(InputHydjet.c_str());
   TFile FNonembedded(InputNonembedded.c_str());

   TTree *TEmbedded    = (TTree *)FEmbedded.Get("Tree");
   TTree *THydjet      = (TTree *)FHydjet.Get("Tree");
   TTree *TNonembedded = (TTree *)FNonembedded.Get("Tree");

   int NPU;
   int NEta;
   double ESum[MAX];

   TNonembedded->SetBranchAddress("NEta", &NEta);
   TNonembedded->SetBranchAddress("ESum", &ESum);
   TNonembedded->SetBranchAddress("NPU", &NPU);
   int EntryCount = TNonembedded->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      TNonembedded->GetEntry(i);
      if(NPU >= 1)
         continue;
      double HF = ESum[0] + ESum[1] + ESum[8] + ESum[9];
      double Central = ESum[10] + ESum[11];
      HNonembeddedCentral.Fill(Central);
      HNonembeddedHF.Fill(HF);
   }

   if(NominalHFShift < -999)
      NominalHFShift = HNonembeddedHF.GetMean() * AutoFactor;
   double CentralShift = HNonembeddedCentral.GetMean();

   TEmbedded->SetBranchAddress("NEta", &NEta);
   TEmbedded->SetBranchAddress("ESum", &ESum);
   EntryCount = TEmbedded->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      TEmbedded->GetEntry(i);
      double HF = ESum[0] + ESum[1] + ESum[8] + ESum[9];
      double Central = ESum[10] + ESum[11];
      PEmbedded.Fill(HF, Central);
      PEmbeddedShift.Fill(HF - NominalHFShift, Central);
   }

   THydjet->SetBranchAddress("NEta", &NEta);
   THydjet->SetBranchAddress("ESum", &ESum);
   EntryCount = THydjet->GetEntries();
   for(int i = 0; i < EntryCount; i++)
   {
      THydjet->GetEntry(i);
      double HF = ESum[0] + ESum[1] + ESum[8] + ESum[9];
      double Central = ESum[10] + ESum[11];
      PHydjet.Fill(HF, Central);
      PHydjetShift.Fill(HF, Central + CentralShift);
   }
   
   FNonembedded.Close();
   FHydjet.Close();
   FEmbedded.Close();

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("HF shift investigations");

   PdfFile.AddPlot(PEmbedded);
   PdfFile.AddPlot(PEmbeddedShift);
   PdfFile.AddPlot(PHydjet);
   PdfFile.AddPlot(HNonembeddedCentral);
   PdfFile.AddPlot(HNonembeddedHF);

   TCanvas Canvas;

   TH2D HWorld("HWorld", ";SumE (3 < |#eta| < 5);SumE (-2.4 < |#eta| < 2.4)", 100, 0, 10000, 100, 0, 1500);
   HWorld.SetStats(0);

   PEmbedded.SetStats(0);
   PEmbeddedShift.SetStats(0);
   PHydjet.SetStats(0);

   PEmbedded.SetLineColor(Colors[0]);
   PEmbedded.SetMarkerColor(Colors[0]);
   PEmbeddedShift.SetLineColor(Colors[1]);
   PEmbeddedShift.SetMarkerColor(Colors[1]);
   PHydjet.SetLineColor(Colors[2]);
   PHydjet.SetMarkerColor(Colors[2]);
   PHydjetShift.SetLineColor(Colors[3]);
   PHydjetShift.SetMarkerColor(Colors[3]);

   HWorld.Draw("axis");
   PEmbedded.Draw("same");
   PEmbeddedShift.Draw("same");
   PHydjet.Draw("same");
   PHydjetShift.Draw("same");

   TLegend Legend(0.2, 0.6, 0.5, 0.8);
   Legend.SetTextFont(42);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&PEmbedded, "Embedded", "pl");
   Legend.AddEntry(&PEmbeddedShift, "Embedded + shift left", "pl");
   Legend.AddEntry(&PHydjet, "Hydjet", "pl");
   Legend.AddEntry(&PHydjetShift, "Hydjet + shift up", "pl");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   HDifference.Sumw2();
   for(int i = 1; i <= 100; i++)
   {
      HDifference.SetBinContent(i, PEmbeddedShift.GetBinContent(i) - PHydjet.GetBinContent(i));
      HDifference.SetBinError(i, 0);
   }

   PdfFile.AddPlot(HDifference);
   PdfFile.AddPlot(HNonembeddedHF);
   PdfFile.AddPlot(HNonembeddedCentral);

   TH2D HWorld2("HWorld2", ";SumE (3 < |#eta| < 5);#Delta SumE (-2.4 < |#eta| < 2.4)", 100, 0, 10000, 100, 0, 400);
   HWorld2.SetStats(0);
   HDifference.SetStats(0);

   HWorld2.Draw("axis");
   HDifference.Draw("same");

   TGraph G;
   G.SetPoint(0, 0, HNonembeddedCentral.GetMean());
   G.SetPoint(1, 10000, HNonembeddedCentral.GetMean());
   G.Draw("l");

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}




