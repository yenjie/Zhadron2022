#include <vector>
#include <iostream>
using namespace std;

#include "TH1D.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TLegend.h"

#include "SetStyle.h"

int main(int argc, char *argv[])
{
   vector<int> Colors = GetPrimaryColors();

   SetThesisStyle();

   TFile File("PPMC.root");

   string Tag1 = "Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_1";
   string Tag2 = "Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_10";

   vector<string> Types{"DeltaPhi", "DeltaEta", "DeltaEtaZSide", "DeltaEtaJetSide"};

   for(string Type : Types)
   {
      TH1D *H1 = (TH1D *)File.Get(Form("H%s_%s", Type.c_str(), Tag1.c_str()));
      TH1D *H2 = (TH1D *)File.Get(Form("H%s_%s", Type.c_str(), Tag2.c_str()));

      TH1D *HN1 = (TH1D *)File.Get(Form("HN_%s", Tag1.c_str()));
      TH1D *HN2 = (TH1D *)File.Get(Form("HN_%s", Tag2.c_str()));

      H1->Scale(1 / HN1->GetBinContent(1));
      H2->Scale(1 / HN2->GetBinContent(1));

      TCanvas Canvas;

      H1->SetStats(0);
      H2->SetStats(0);

      H1->SetMarkerStyle(20);
      H2->SetMarkerStyle(20);

      H1->SetLineColor(Colors[0]);
      H2->SetLineColor(Colors[1]);
      H1->SetLineWidth(2);
      H2->SetLineWidth(2);
      H1->SetMarkerColor(Colors[0]);
      H2->SetMarkerColor(Colors[1]);
      H1->SetMarkerSize(2);
      H2->SetMarkerSize(2);

      H1->Draw();
      H2->Draw("same");

      TLegend Legend(0.5, 0.65, 0.8, 0.8);
      Legend.SetTextFont(42);
      Legend.SetTextSize(0.035);
      Legend.SetBorderSize(0);
      Legend.SetFillStyle(0);
      Legend.AddEntry(H1, "PV = 1");
      Legend.AddEntry(H2, "All PV");
      Legend.Draw();

      Canvas.SaveAs(Form("PPMCPUPlot_%s.pdf", Type.c_str()));

      H1->Divide(H2);
      H1->Draw();

      H1->SetMinimum(0.5);
      H1->SetMaximum(1.5);

      Canvas.SaveAs(Form("PPMCPUPlot_%sRatio.pdf", Type.c_str()));
   }

   File.Close();

   return 0;
}

// HDeltaPhi_Centrality_0_30_ZPT_40_200_TrackPT_10_1000_PV_0_1


