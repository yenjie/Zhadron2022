#include <iostream>
using namespace std;

#include "TF1.h"
#include "TH1D.h"
#include "TFile.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TLatex.h"

#include "SetStyle.h"
#include "CommandLine.h"
#include "PlotHelper4.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string MCFileName = CL.Get("MC");
   string DataFileName = CL.Get("Data");
   string OutputFileName = CL.Get("Output");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("VZ weights");

   TFile MCFile(MCFileName.c_str());
   TFile DataFile(DataFileName.c_str());
   
   TTree *MCTree = (TTree *)MCFile.Get("Tree");
   TTree *DataTree = (TTree *)DataFile.Get("Tree");

   TH1D HMC("HMC", ";v_{Z};", 100, -15, 15);
   TH1D HData("HData", ";v_{Z};", 100, -15, 15);

   MCTree->Draw("VZ>>HMC", "", "");
   DataTree->Draw("VZ>>HData", "", "same");

   HMC.Scale(1 / HMC.Integral());
   HData.Scale(1 / HData.Integral());

   HMC.SetStats(0);
   HData.SetStats(0);

   HMC.SetMarkerColor(kRed);
   HMC.SetLineColor(kRed);
   HData.SetMarkerColor(kBlue);
   HData.SetLineColor(kBlue);

   PdfFile.AddPlot(HMC);
   PdfFile.AddPlot(HData);

   TCanvas Canvas;
   HMC.Draw();
   HData.Draw("same");
   PdfFile.AddCanvas(Canvas);

   HMC.Divide(&HData);

   PdfFile.AddPlot(HMC);

   TCanvas Canvas2;

   TF1 F("F", "pol4", -15, 15);

   HMC.Fit(&F);
   HMC.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.035);
   Latex.SetNDC();
   Latex.SetTextAlign(32);

   Latex.DrawLatex(0.80, 0.35, Form("P0 = %.6f", F.GetParameter(0)));
   Latex.DrawLatex(0.80, 0.30, Form("P1 = %.6f", F.GetParameter(1)));
   Latex.DrawLatex(0.80, 0.25, Form("P2 = %.6f", F.GetParameter(2)));
   Latex.DrawLatex(0.80, 0.20, Form("P3 = %.6f", F.GetParameter(3)));
   Latex.DrawLatex(0.80, 0.15, Form("P4 = %.6f", F.GetParameter(4)));

   PdfFile.AddCanvas(Canvas2);

   DataFile.Close();
   MCFile.Close();

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}



