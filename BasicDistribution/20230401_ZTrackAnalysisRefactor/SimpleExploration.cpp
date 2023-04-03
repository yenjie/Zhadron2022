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

   PdfFileHelper PdfFile(OutputFileName);

   PdfFile.AddTextPage(vector<string>{
      "Running with these inputs:",
      "      Signal: " + SignalFileName,
      "      Background: " + BackgroundFileName,
      "      Folder:" + Folder,
      "      Histogram: " + Histogram});

   PdfFile.AddTextPage("Original signal");
   PdfFile.AddPlot(HSignal, "colz");
   PdfFile.AddPlot(HSignal, "lego20z");
   
   PdfFile.AddTextPage("Original background");
   PdfFile.AddPlot(HBackground, "colz");
   PdfFile.AddPlot(HBackground, "lego20z");

   HSignal->Scale(1 / HSignalCount->GetBinContent(1));
   HBackground->Scale(1 / HBackgroundCount->GetBinContent(1));

   PdfFile.AddTextPage("Scaled signal & background");
   PdfFile.AddPlot(HSignal, "lego20z");
   PdfFile.AddPlot(HBackground, "lego20z");

   HSignal->Add(HBackground, -1);

   PdfFile.AddTextPage("Subtracted result");
   PdfFile.AddPlot(HSignal, "lego20z");

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   BackgroundFile.Close();
   SignalFile.Close();

   return 0;
}




