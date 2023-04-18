#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TLegend.h"
#include "TLatex.h"
#include "TCanvas.h"

#include "CommandLine.h"
#include "PlotHelper4.h"
#include "SetStyle.h"

int main(int argc, char *argv[]);
void SetAlias(TTree *Tree);

int main(int argc, char *argv[])
{
   SetThesisStyle();

   CommandLine CL(argc, argv);

   string File1 = CL.Get("File1", "AllData.root");
   string File2 = CL.Get("File2", File1);
   if(File2 == "same")
      File2 = File1;

   string EventCut1 = CL.Get("EventCut1", "(zMass[0] > 60 && zPt[0] > 60 && hiBin < 20)");
   string EventCut2 = CL.Get("EventCut2", "(zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 20)");
   if(EventCut2 == "same")
      EventCut2 = EventCut1;

   string TrackCut1 = CL.Get("TrackCut1", "(trackMuTagged == 0 && abs(DPhi) > 2)");
   string TrackCut2 = CL.Get("TrackCut2", TrackCut1);
   if(TrackCut2 == "same")
      TrackCut2 = TrackCut1;

   double Fraction1 = CL.GetDouble("Fraction1", 1.00);
   double Fraction2 = CL.GetDouble("Fraction2", 1.00);

   string Label1 = CL.Get("Label1", "p_{T}^{Z} > 60 GeV");
   string Label2 = CL.Get("Label2", "p_{T}^{Z} = 5-20 GeV");

   string ToPlot = CL.Get("ToPlot", "abs(DEta)");

   string Title = CL.Get("Title", ";#Delta#eta;N_{ch} / event");
   int Bin      = CL.GetInteger("Bin", 40);
   double Min   = CL.GetDouble("Min", 0);
   double Max   = CL.GetDouble("Max", 5);

   string Caption = CL.Get("Caption", "Meow");

   string OutputFileName = CL.Get("Output", "Plots.pdf");

   PdfFileHelper PdfFile(OutputFileName);
   
   TFile F1(File1.c_str());
   TFile F2(File2.c_str());

   TH1D H1("H1", Title.c_str(), Bin, Min, Max);
   TH1D H2("H2", Title.c_str(), Bin, Min, Max);
   
   TH1D HN1("HN1", "", 2, 0, 2);
   TH1D HN2("HN2", "", 2, 0, 2);

   TTree *Tree = nullptr;

   int N = 0;

   Tree = (TTree *)F1.Get("Tree");
   SetAlias(Tree);
   N = Tree->GetEntries() * Fraction1;
   Tree->Draw(Form("%s>>H1", ToPlot.c_str()), Form("NCollWeight * (%s) * trackWeight * (%s)", EventCut1.c_str(), TrackCut1.c_str()), "", N);
   Tree->Draw(Form("(Sum$(%s)>0)>>HN1", TrackCut1.c_str()), Form("NCollWeight * (%s)", EventCut1.c_str()), "", N);
   
   Tree = (TTree *)F2.Get("Tree");
   SetAlias(Tree);
   N = Tree->GetEntries() * Fraction2;
   Tree->Draw(Form("%s>>H2", ToPlot.c_str()), Form("NCollWeight * (%s) * trackWeight * (%s)", EventCut2.c_str(), TrackCut2.c_str()), "", N);
   Tree->Draw(Form("(Sum$(%s)>0)>>HN2", TrackCut2.c_str()), Form("NCollWeight * (%s)", EventCut2.c_str()), "", N);

   H1.Scale(1 / HN1.GetBinContent(2) / ((Max - Min) / Bin));
   H2.Scale(1 / HN2.GetBinContent(2) / ((Max - Min) / Bin));

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
      H1.Draw("same hist");
      H2.Draw("same");
      H2.Draw("same hist");
   }
   else
   {
      H2.Draw("");
      H2.Draw("same hist");
      H1.Draw("same");
      H1.Draw("same hist");
   }

   H1.SetMinimum(0);
   H2.SetMinimum(0);

   TLegend Legend(0.15, 0.30, 0.45, 0.15);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   Legend.AddEntry(&H1, Label1.c_str(), "pl");
   Legend.AddEntry(&H2, Label2.c_str(), "pl");
   Legend.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.025);
   Latex.SetTextAlign(11);
   Latex.SetNDC();
   Latex.DrawLatex(0.1, 0.905, Caption.c_str());

   PdfFile.AddCanvas(Canvas);
   
   PdfFile.AddTextPage({"=== Files ===", File1 + " (red)", File2 + " (blue)",
         "=== Fractions ===", Form("%f", Fraction1), Form("%f", Fraction2),
         "=== Event cuts ===", EventCut1, EventCut2,
         "=== Track cuts ===", TrackCut1, TrackCut2,
         "=== To plot ===", ToPlot}, 0.1, 0.9, 0.025);

   PdfFile.AddTimeStampPage();
   PdfFile.Close();

   F2.Close();
   F1.Close();
   
   return 0;
}

void SetAlias(TTree *Tree)
{
   if(Tree == nullptr)
      return;
   
   Tree->SetAlias("EtaWTA", "(maxOppositeWTADEta+zEta[0])");
   Tree->SetAlias("RawPhiWTA", "(maxOppositeWTADPhi+zPhi[0])");
   Tree->SetAlias("PhiWTA", "(RawPhiWTA+2*3.1415926535*(RawPhiWTA<-3.1415926535)-2*3.1415926535*(RawPhiWTA>3.1415926535))");
   Tree->SetAlias("DEtaWTA", "(trackDeta-maxOppositeWTADEta)");
   Tree->SetAlias("RawDPhiWTA", "(trackDphi-maxOppositeWTADPhi)");
   Tree->SetAlias("DPhiWTA", "(RawDPhiWTA+2*3.1415926535*(RawDPhiWTA<-3.1415926535)-2*3.1415926535*(RawDPhiWTA>3.1415926535))");
   Tree->SetAlias("DPhiWTACorr", "(DPhiWTA+2*3.14159*(DPhiWTA<-1.57159))/3.14159");
   
   Tree->SetAlias("EtaWTAMore", "(maxMoreOppositeWTADEta+zEta[0])");
   Tree->SetAlias("RawPhiWTAMore", "(maxMoreOppositeWTADPhi+zPhi[0])");
   Tree->SetAlias("PhiWTAMore", "(RawPhiWTAMore+2*3.1415926535*(RawPhiWTAMore<-3.1415926535)-2*3.1415926535*(RawPhiWTAMore>3.1415926535))");
   Tree->SetAlias("DEtaWTAMore", "(trackDeta-maxMoreOppositeWTADEta)");
   Tree->SetAlias("RawDPhiWTAMore", "(trackDphi-maxMoreOppositeWTADPhi)");
   Tree->SetAlias("DPhiWTAMore", "(RawDPhiWTAMore+2*3.1415926535*(RawDPhiWTAMore<-3.1415926535)-2*3.1415926535*(RawDPhiWTAMore>3.1415926535))");
   Tree->SetAlias("DPhiWTAMoreCorr", "(DPhiWTAMore+2*3.14159*(DPhiWTAMore<-1.57159))/3.14159");
   
   Tree->SetAlias("EtaMax", "(maxOppositeDEta+zEta[0])");
   Tree->SetAlias("RawPhiMax", "(maxOppositeDPhi+zPhi[0])");
   Tree->SetAlias("PhiMax", "(RawPhiMax+2*3.1415926535*(RawPhiMax<-3.1415926535)-2*3.1415926535*(RawPhiMax>3.1415926535))");
   Tree->SetAlias("DEtaMax", "(trackDeta-maxOppositeDEta)");
   Tree->SetAlias("RawDPhiMax", "(trackDphi-maxOppositeDPhi)");
   Tree->SetAlias("DPhiMax", "(RawDPhiMax+2*3.1415926535*(RawDPhiMax<-3.1415926535)-2*3.1415926535*(RawDPhiMax>3.1415926535))");
   Tree->SetAlias("DPhiMaxCorr", "(RawDPhiMax+2*3.14159*(RawDPhiMax<-1.57159)-2*3.14159*(RawDPhiMax>4.71239))/3.14159");
}

