#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TH1D.h"
#include "TH2D.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string SignalFileName     = CL.Get("SignalFile");
   string BackgroundFileName = CL.Get("BackgroundFile");
   string Folder             = CL.Get("Folder");
   string Histogram          = CL.Get("Histogram");
   string OutputFileName     = CL.Get("Output", "Plots.pdf");

   TFile SignalFile(SignalFileName.c_str());
   TFile BackgroundFile(BackgroundFileName.c_str());

   TH2D *HSignal          = (TH2D *)SignalFile.Get(Form("%s/%s", Folder.c_str(), Histogram.c_str()));
   TH2D *HBackground      = (TH2D *)BackgroundFile.Get(Form("%s/%s", Folder.c_str(), Histogram.c_str()));

   TH1D *HSignalCount     = (TH1D *)SignalFile.Get(Form("%s/HEventCount", Folder.c_str()));
   TH1D *HBackgroundCount = (TH1D *)BackgroundFile.Get(Form("%s/HEventCount", Folder.c_str()));

   HSignal->SetStats(0);
   HBackground->SetStats(0);

   HSignal->Rebin2D(3, 3);
   HBackground->Rebin2D(3, 3);

   PdfFileHelper PdfFile(OutputFileName);

   PdfFile.AddTextPage("Z-hadron correlation plots");
   PdfFile.AddTextPage(vector<string>{
      "Running with these inputs:",
      "      Signal: " + SignalFileName,
      "      Background: " + BackgroundFileName,
      "      " + Folder,
      "      Histogram: " + Histogram});

   PdfFile.AddTextPage("Original signal");
   PdfFile.AddPlot(HSignal, "colz");
   // PdfFile.AddPlot(HSignal, "lego20z");
   
   PdfFile.AddTextPage("Original background");
   PdfFile.AddPlot(HBackground, "colz");
   // PdfFile.AddPlot(HBackground, "lego20z");

   HSignal->Scale(1 / HSignalCount->GetBinContent(1));
   HBackground->Scale(1 / HBackgroundCount->GetBinContent(1));

   PdfFile.AddTextPage("Scaled signal & background");
   PdfFile.AddPlot(HSignal, "colz");
   PdfFile.AddPlot(HBackground, "colz");

   TH2D *HDiff = (TH2D *)HSignal->Clone("HDiff");
   HDiff->Add(HBackground, -1);
   
   TH2D *HRatio = (TH2D *)HSignal->Clone("HRatio");
   HRatio->Divide(HBackground);
   HRatio->GetXaxis()->SetRangeUser(-3, 3);

   PdfFile.AddTextPage("Subtracted result");
   PdfFile.AddPlot(HDiff, "colz");
   // PdfFile.AddPlot(HDiff, "lego20z");
   
   PdfFile.AddTextPage("Ratio");
   PdfFile.AddPlot(HRatio, "colz");
   // PdfFile.AddPlot(HRatio, "lego20z");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   BackgroundFile.Close();
   SignalFile.Close();

   return 0;
}




