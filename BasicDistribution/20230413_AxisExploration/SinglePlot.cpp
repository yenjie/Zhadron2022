#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string File1 = CL.Get("File1", "AllData.root");
   string File2 = CL.Get("File2", File1);

   string EventCut1 = CL.Get("EventCut1", "NCollWeight * (zMass[0] > 60 && zPt[0] > 60 && hiBin < 20)");
   string EventCut2 = CL.Get("EventCut2", "NCollWeight * (zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 20)");

   string TrackCut1 = CL.Get("TrackCut1", "(trackMuTagged == 0 && abs(DPhi) > 2) * trackWeight");
   string TrackCut2 = CL.Get("TrackCut2", TrackCut1);

   string Label1 = CL.Get("Label1", "p_{T}^{Z} > 60 GeV");
   string Label2 = CL.Get("Label2", "p_{T}^{Z} = 5-20 GeV");

   string Title = CL.Get("Title", ";#Delta#eta;N_{ch} / event");
   int Bin      = CL.GetInteger("Bin", 40);
   double Min   = CL.GetDouble("Min", 0);
   double Max   = CL.GetDouble("Max", 5);

   string OutputFileName = CL.Get("Output", "Plots.pdf");

   PdfFileHelper PdfFile(OutputFileName);
   PdfFile.AddTextPage("Meow");

   PdfFile.AddTextPage({"Files", File1, File2, "Event cuts", EventCut1, EventCut2, "Track cuts", TrackCut1, TrackCut2});

   TH1D H1("H1", Title.c_str(), Bin, Min, Max);
   TH1D H2("H2", Title.c_str(), Bin, Min, Max);

   TTree *Tree = nullptr;

   TFile F1(File1.c_str());
   Tree = (TTree *)F1.Get("Tree");
   Tree->SetAlias("rawDPhi", "(trackDphi-maxOppositeWTADPhi)");
   Tree->SetAlias("DPhi", "(rawDPhi+2*3.1415926535*(rawDPhi<-3.1415926535)-2*3.1415926535*(rawDPhi>3.1415926535))");
   Tree->SetAlias("DPhiCorr", "(rawDPhi+2*3.14159*(rawDPhi<-1.57159)-2*3.14159*(rawDPhi>4.71239))/3.14159");
   Tree->SetAlias("DEta", "(trackDeta-maxOppositeWTADEta)");
   Tree->Draw("abs(DEta)>>H1", Form("(%s) * (%s)", EventCut1.c_str(), TrackCut1.c_str()), "");
   double N1 = Tree->GetEntries(EventCut1.c_str());
   F1.Close();
   
   TFile F2(File2.c_str());
   Tree = (TTree *)F2.Get("Tree");
   Tree->SetAlias("rawDPhi", "(trackDphi-maxOppositeWTADPhi)");
   Tree->SetAlias("DPhi", "(rawDPhi+2*3.1415926535*(rawDPhi<-3.1415926535)-2*3.1415926535*(rawDPhi>3.1415926535))");
   Tree->SetAlias("DPhiCorr", "(rawDPhi+2*3.14159*(rawDPhi<-1.57159)-2*3.14159*(rawDPhi>4.71239))/3.14159");
   Tree->SetAlias("DEta", "(trackDeta-maxOppositeWTADEta)");
   Tree->Draw("abs(DEta)>>H2", Form("(%s) * (%s)", EventCut2.c_str(), TrackCut2.c_str()), "");
   double N2 = Tree->GetEntries(EventCut2.c_str());
   F2.Close();

   H1.Scale(1 / N1);
   H2.Scale(1 / N2);

   H1.SetStats(0);
   H2.SetStats(0);

   H1.SetMarkerStyle(20);
   H1.SetMarkerColor(kRed);
   H1.SetLineWidth(2);
   H1.SetLineColor(kRed);
   
   H2.SetMarkerStyle(20);
   H2.SetMarkerColor(kBlue);
   H2.SetLineWidth(2);
   H2.SetLineColor(kBlue);

   TCanvas Canvas;

   if(H1.GetMaximum() > H2.GetMaximum())
   {
      H1.Draw("");
      H2.Draw("same");
   }
   else
   {
      H2.Draw("");
      H1.Draw("same");
   }

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, Label1.c_str(), "pl");
   Legend.AddEntry(&H2, Label2.c_str(), "pl");
   Legend.Draw();

   PdfFile.AddCanvas(Canvas);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   return 0;
}
