#include <map>
#include <cmath>
#include <iostream>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH1D.h"
#include "TMath.h"
#include "TROOT.h"
#include "TH2D.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TLegend.h"
#include "TAxis.h"
#include "TSystem.h"
#include "TLatex.h"
#include "TLine.h"
#include "TPad.h"

#include "SetStyle.h"

#define TptL_min 0.5
#define typeofdata "20230518"
#define typeofdatatext "single muon"

struct Files;
struct Plots;
struct Setting;
int main(int argc, char *argv[]);
void ZtrackDraw_single(Files &File, Setting S, string OutputBase);
void DivideByBinWidth(TH1D *H = nullptr);
void DivideByBinWidth(TH2D *H = nullptr);
void Draw1DPlot(TH1D *H1, TH1D *H2, string XTitle, string YTitle, bool WithMin,
   Setting &S, string Base, string Tag);
void Draw2DPlot2Panel(TH2D *H1, TH2D *H2, string XTitle, string YTitle, string ZTitle,
   Setting &S, string Base, string Tag, string Option, vector<string> Identifier = {"MC", "Data"});
void Draw2DPlot3Panel(TH2D *H1, TH2D *H2, TH2D *H3, string XTitle, string YTitle, string ZTitle,
   Setting &S, string Base, string Tag, string Option, vector<string> Identifier = {"PbPB MC", "Data", "pp MC"});

struct Files
{
public:
   TFile *SignalMC;
   TFile *BackgroundMC;
   TFile *SignalData;
   TFile *BackgroundData;
   TFile *ppMC;
   TFile *ppData;
   TFile *SignalMCGen;
   TFile *BackgroundMCGen;
public:
   Files() : SignalMC(nullptr), BackgroundMC(nullptr), SignalData(nullptr), BackgroundData(nullptr),
      ppMC(nullptr), ppData(nullptr), SignalMCGen(nullptr), BackgroundMCGen(nullptr)
   {
   }
   ~Files()
   {
      if(SignalMC != nullptr)          {SignalMC->Close(); delete SignalMC;}
      if(BackgroundMC != nullptr)      {BackgroundMC->Close(); delete BackgroundMC;}
      if(SignalData != nullptr)        {SignalData->Close(); delete SignalData;}
      if(BackgroundData != nullptr)    {BackgroundData->Close(); delete BackgroundData;}
      if(ppMC != nullptr)              {ppMC->Close(); delete ppMC;}
      if(ppData != nullptr)            {ppData->Close(); delete ppData;}
      if(SignalMCGen != nullptr)       {SignalMCGen->Close(); delete SignalMCGen;}
      if(BackgroundMCGen != nullptr)   {BackgroundMCGen->Close(); delete BackgroundMCGen;}
   }
};

struct Plots
{
public:
   vector<string> N1;
   vector<string> N2;
   map<string, TH1D *> H1;
   map<string, TH2D *> H2;
public:
   Plots() {}
   Plots(TFile *File, string FolderName, int Rebin1D = 1, int Rebin2D = 1) :
      N1{"HEta", "HPhi", "HTrackMuonDEta", "HTrackMuonDPhi"},
      N2{"HEtaPhi", "HTrackMuonDEtaDPhi", "HMaxHadronEtaPhi", "HMaxOppositeHadronEtaPhi",
         "HWTAEtaPhi", "HWTAMoreEtaPhi", "HZMaxHadronEtaPhi", "HZMaxOppositeHadronEtaPhi",
         "HZWTAEtaPhi", "HZWTAMoreEtaPhi"}
   {
      for(string N : N1) H1[N] = Prepare1DHistogram(File, FolderName, N, Rebin1D);
      for(string N : N2) H2[N] = Prepare2DHistogram(File, FolderName, N, Rebin2D);
   }
   Plots(Plots &other) : N1(other.N1), N2(other.N2)
   {
      for(string N : N1)
         if(other.H1[N] != nullptr)
            H1[N] = (TH1D *)other.H1[N]->Clone();
      for(string N : N2)
         if(other.H2[N] != nullptr)
            H2[N] = (TH2D *)other.H2[N]->Clone();
   }
   void HistogramStyle(int Color, int Marker)
   {
      for(string N : N1)
      {
         if(H1[N] != nullptr)
         {
            H1[N]->SetLineColor(Color);
            H1[N]->SetMarkerColor(Color);
            H1[N]->SetLineWidth(2);
            H1[N]->SetMarkerStyle(Marker);
         }
      }
      for(string N : N2)
      {
         if(H2[N] != nullptr)
         {
            H2[N]->SetMarkerColor(Color);
            H2[N]->SetMarkerStyle(Marker);
         }
      }
   }
   void Subtract(Plots &other)
   {
      for(string N : N1)
         if(other.H1.find(N) != other.H1.end() && other.H1[N] != nullptr && H1[N] != nullptr)
            H1[N]->Add(other.H1[N], -1);
      for(string N : N2)
         if(other.H2.find(N) != other.H2.end() && other.H2[N] != nullptr && H2[N] != nullptr)
            H2[N]->Add(other.H2[N], -1);
   }
   void Divide(Plots &other)
   {
      for(string N : N1)
         if(other.H1.find(N) != other.H1.end() && other.H1[N] != nullptr && H1[N] != nullptr)
            H1[N]->Divide(other.H1[N]);
      for(string N : N2)
         if(other.H2.find(N) != other.H2.end() && other.H2[N] != nullptr && H2[N] != nullptr)
            H2[N]->Divide(other.H2[N]);
   }
   TH1D *Prepare1DHistogram(TFile *File, string FolderName, string HistogramName, int Rebin)
   {
      if(File == nullptr)
         return nullptr;

      TH1D *H = (TH1D *)File->Get(Form("%s/%s", FolderName.c_str(), HistogramName.c_str()));

      TNamed *N  = (TNamed *)File->Get(Form("%s/EntryCount", FolderName.c_str()));
      float I = atof(N->GetTitle());
      H->Scale(1 / I);

      if(Rebin > 1)
         H->Rebin(Rebin);

      DivideByBinWidth(H);

      return H;
   }
   TH2D *Prepare2DHistogram(TFile *File, string FolderName, string HistogramName, int Rebin)
   {
      if(File == nullptr)
         return nullptr;

      TH2D *H = (TH2D *)File->Get(Form("%s/%s", FolderName.c_str(), HistogramName.c_str()));

      TNamed *N  = (TNamed *)File->Get(Form("%s/EntryCount", FolderName.c_str()));
      float I = atof(N->GetTitle());
      H->Scale(1 / I);

      if(Rebin > 1)
         H->Rebin2D(Rebin, Rebin);

      DivideByBinWidth(H);

      return H;
   }
};

struct Setting
{
public:
   int binnum;
   float ptL;
   float ptH;
   float centL;
   float centH;
   float TptL;
   float TptH;
public:
   Setting() {}
   Setting(int b, float p1, float p2, float c1, float c2, float T1, float T2)
      : binnum(b), ptL(p1), ptH(p2), centL(c1), centH(c2), TptL(T1), TptH(T2)
   {
   }
};

int main(int argc, char *argv[])
{
   SetCorrelationStyle();

   Files File;
   
   File.SignalData      = TFile::Open("GraphDataSignal_v9.root", "read");
   File.SignalMC        = TFile::Open("GraphMCSignal_v9.root", "read");
   File.BackgroundData  = TFile::Open("GraphDataBackground_v9.root", "read");
   File.BackgroundMC    = TFile::Open("GraphMCBackground_v9.root", "read");
   File.ppData          = nullptr;
   File.ppMC            = TFile::Open("GraphPPMC0Sub_v9.root", "read");
   File.SignalMCGen     = TFile::Open("GraphMCSignalGen_v9.root", "read");
   File.BackgroundMCGen = TFile::Open("GraphMCBackgroundGen_v9.root", "read");

   string OutputBase = "/eos/user/p/pchou/figs/track";
   // string OutputBase = ".";

/*
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40,  5, 2000,  0, 90,  0, 1000), OutputBase);

   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  1,    2), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  2,    5), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  5,   10), OutputBase);

   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  4,    5), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  5,    7), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  7,   10), OutputBase);

   //ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 30,  1,    2), OutputBase);
   //ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 30,  2,    5), OutputBase);
   //ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 30,  5,   10), OutputBase);
*/
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 30,  4,    5), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 30,  5,    7), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 30,  7,   10), OutputBase);


   /*
   ZtrackDraw_single(File, Setting(40, 30,   40,  0, 90,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 40,   60,  0, 90,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 60,   80,  0, 90,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 80,  100,  0, 90,  0, 1000), OutputBase);*/
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 10,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 10, 30,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 30, 50,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  1,    2), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  2,    5), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90,  5,   10), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90, 10,   20), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90, 20,   50), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 90, 50,  100), OutputBase);
   /*
   ZtrackDraw_single(File, Setting(40, 40, 2000, 50, 90,  0, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90,  1,    2), OutputBase);
   ZtrackDraw_single(File, Setting(40, 40, 2000, 50, 90,  1,    2), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90,  2,    5), OutputBase);
   ZtrackDraw_single(File, Setting(40, 40, 2000, 50, 90,  2,    5), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90,  5,   10), OutputBase);
   ZtrackDraw_single(File, Setting(40, 40, 2000, 50, 90,  5,   10), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90, 20,   50), OutputBase);
   ZtrackDraw_single(File, Setting(40, 40, 2000, 50, 90, 20,   50), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90, 50,  100), OutputBase);
   ZtrackDraw_single(File, Setting(40, 40, 2000, 50, 90, 50,  100), OutputBase);
   ZtrackDraw_single(File, Setting(40, 30, 2000,  0, 30,  1, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 30, 2000, 30, 50,  1, 1000), OutputBase);
   ZtrackDraw_single(File, Setting(40, 30, 2000, 50, 90,  1, 1000), OutputBase);*/

/* 
   ZtrackDraw_single(File, Setting(40,  5, 2000,  0, 90,  5,   10), OutputBase);
   ZtrackDraw_single(File, Setting(40,  5, 2000,  0, 90, 10,   20), OutputBase);
   ZtrackDraw_single(File, Setting(40,  5, 2000,  0, 90, 20,   50), OutputBase);
   ZtrackDraw_single(File, Setting(40,  5, 2000,  0, 90, 50,  100), OutputBase);
*/

   ZtrackDraw_single(File, Setting(40, 10, 2000,  0, 90,  2, 1000), OutputBase);

   //ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 10, 10,   20), OutputBase);

   ZtrackDraw_single(File, Setting(40, 20, 2000,  0, 10, 10,   20), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 10, 30, 10,   20), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 30, 50, 10,   20), OutputBase);
   ZtrackDraw_single(File, Setting(40, 20, 2000, 50, 90, 10,   20), OutputBase);

   return 0;

}

void ZtrackDraw_single(Files &File, Setting S, string OutputBase)
{
   cout << "ptL = " << S.ptL << ", ptH = " << S.ptH
      << ", centL = " << S.centL << ", centH = " << S.centH
      << ", TptL = " << S.TptL << ", TptH = " << S.TptH << endl;
   
   TCanvas *c = new TCanvas("Canvas", "", 800, 800);

   cout << "Getting histograms..." << endl;

   string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",S.ptL,S.ptH,S.centL,S.centH,S.TptL,S.TptH);
   replace(FolderName.begin(), FolderName.end(), '.', 'p');

   Plots HSignalData(File.SignalData, FolderName, 1, 5);
   Plots HSignalMC(File.SignalMC, FolderName, 1, 4);
   Plots HppData(File.ppData, FolderName, 1, 5);
   Plots HppMC(File.ppMC, FolderName, 1, 4);
   Plots HBackgroundData(File.BackgroundData, FolderName, 1, 5);
   Plots HBackgroundMC(File.BackgroundMC, FolderName, 1, 4);
   Plots HSignalMCGen(File.SignalMCGen, FolderName, 1, 4);
   Plots HBackgroundMCGen(File.BackgroundMCGen, FolderName, 1, 4);

   HSignalData.HistogramStyle(kBlack, 24);
   HSignalMC.HistogramStyle(kRed, 24);
   HppData.HistogramStyle(kBlack, 24);
   HppMC.HistogramStyle(kRed, 24);
   HBackgroundData.HistogramStyle(kBlack, 24);
   HBackgroundMC.HistogramStyle(kRed, 24);

   Plots HSignalDataSB(HSignalData);
   Plots HSignalMCSB(HSignalMC);
   Plots HSignalMCGenSB(HSignalMCGen);
   
   HSignalDataSB.Subtract(HBackgroundData);
   HSignalMCSB.Subtract(HBackgroundMC);
   HSignalMCGenSB.Subtract(HBackgroundMCGen);

   Plots HSignalDataSBR(HSignalData);
   Plots HSignalMCSBR(HSignalMC);
   Plots HSignalMCGenSBR(HSignalMCGen);
   
   HSignalDataSBR.Divide(HBackgroundData);
   HSignalMCSBR.Divide(HBackgroundMC);
   HSignalMCGenSBR.Divide(HBackgroundMCGen);
   
   int countD0 = HSignalData.H1["HEta"]->GetEntries();
   cout<<"Data 0 = "<<countD0<<endl;
   int countM0 = HSignalMC.H1["HEta"]->GetEntries();
   cout<<"MC 0 = "<<countM0<<endl;

   int countDb = HBackgroundData.H1["HEta"]->GetEntries();
   cout<<"Data Bkg = "<<countDb<<endl;
   int countMb = HBackgroundMC.H1["HEta"]->GetEntries();
   cout<<"MC Bkg = "<<countMb<<endl;

   if(S.TptL==0) S.TptL=TptL_min;

   TLegend Legend(0.58, 0.78, 0.98, 0.90);
   Legend.AddEntry(HSignalMC.H1["HEta"], "Monte Carlo: DYLL","lep");
   Legend.AddEntry(HSignalData.H1["HEta"], Form("Data: %s",typeofdatatext),"lep");
   Legend.SetFillStyle(0);
   Legend.SetLineColor(kBlack);
   Legend.SetLineWidth(1);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);

   //// TLatex *pt = new TLatex(0.18,0.88,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   //// pt->SetTextFont(42);
   //// pt->SetTextSize(0.03);
   //// pt->SetNDC(kTRUE);

   //// TLatex *pt2 = new TLatex(0.18,0.82,Form("%.1f < Z p_{T} < %.1f",ptL,ptH));
   //// pt2->SetTextFont(42);
   //// pt2->SetTextSize(0.03);
   //// pt2->SetNDC(kTRUE);

   //// TLatex *pt3 = new TLatex(0.18,0.76,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   //// pt3->SetTextFont(42);
   //// pt3->SetTextSize(0.03);
   //// pt3->SetNDC(kTRUE);

   //// TLatex *pt3d = new TLatex(0.03,0.94,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   //// pt3d->SetTextFont(42);
   //// pt3d->SetTextSize(0.03);
   //// pt3d->SetNDC(kTRUE);

   //// TLatex *pt3d2 = new TLatex(0.03,0.88,Form("%.1f < Z p_{T} < %.1f",ptL,ptH));
   //// pt3d2->SetTextFont(42);
   //// pt3d2->SetTextSize(0.03);
   //// pt3d2->SetNDC(kTRUE);

   //// TLatex *pt3d3 = new TLatex(0.03,0.82,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   //// pt3d3->SetTextFont(42);
   //// pt3d3->SetTextSize(0.03);
   //// pt3d3->SetNDC(kTRUE);


   //// TLatex *ptN0 = new TLatex(0.1,0.97,Form("Signal N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tM_tN,tD_tN));
   //// ptN0->SetTextFont(42);
   //// ptN0->SetTextSize(0.03);
   //// ptN0->SetNDC(kTRUE);

   //// TLatex *ptNb = new TLatex(0.1,0.97,Form("Background N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tMb_tN,tDb_tN));
   //// ptNb->SetTextFont(42);
   //// ptNb->SetTextSize(0.03);
   //// ptNb->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p %s/%s", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/Deta", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/Dphi", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/3D", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/pp", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/muD", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/gen", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/Deta/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/Dphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/3D/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/Deta/C", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/Dphi/C", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/3D/C", OutputBase.c_str(), typeofdata));

   gSystem->Exec(Form("mkdir -p %s/%s/maxetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/maxetaphi/C", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/maxOetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/maxOetaphi/C", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/WTAetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/WTAetaphi/C", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/WTAMoreetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/WTAMoreetaphi/C", OutputBase.c_str(), typeofdata));

   gSystem->Exec(Form("mkdir -p %s/%s/Zmaxetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/Zmaxetaphi/C", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/ZmaxOetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/ZmaxOetaphi/C", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/ZWTAetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/ZWTAetaphi/C", OutputBase.c_str(), typeofdata));
   gSystem->Exec(Form("mkdir -p %s/%s/ZWTAMoreetaphi/pdf", OutputBase.c_str(), typeofdata));
   //gSystem->Exec(Form("mkdir -p %s/%s/ZWTAMoreetaphi/C", OutputBase.c_str(), typeofdata));

   //// // Draw eta 

   string Identifier = Form("%.0f_%.0f_%.0f_%.0f_%.0f_%.0f", S.ptL, S.ptH, S.centL, S.centH, S.TptL, S.TptH);

   Draw1DPlot(HSignalMC.H1["HEta"], HSignalData.H1["HEta"],
      "Signal |#Delta#eta_{Z,track}|", "dN/d#Delta#eta", false, S,
      OutputBase + "/" + typeofdata + "/Deta",
      Form("Ztrack_%s_sig_%s_Deta", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HBackgroundMC.H1["HEta"], HBackgroundData.H1["HEta"],
      "Background |#Delta#eta_{Z,track}|", "dN/d#Delta#eta", false, S,
      OutputBase + "/" + typeofdata + "/Deta",
      Form("Ztrack_%s_bkg_%s_Deta", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HSignalMCSB.H1["HEta"], HSignalDataSB.H1["HEta"],
      "Signal - Background |#Delta#eta_{Z,track}|", "dN/d#Delta#eta", false, S,
      OutputBase + "/" + typeofdata + "/Deta",
      Form("Ztrack_%s_sb_%s_Deta", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HSignalMCSBR.H1["HEta"], HSignalDataSBR.H1["HEta"],
      "Signal - Background |#Delta#eta_{Z,track}|", "dN/d#Delta#eta", false, S,
      OutputBase + "/" + typeofdata + "/Deta",
      Form("Ztrack_%s_sb_%s_Deta", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HSignalMC.H1["HTrackMuonEta"], HSignalData.H1["HTrackMuonEta"],
      "Signal |#Delta#eta_{#mu#mu}|", "dN/d#Delta#eta", false, S,
      OutputBase + "/" + typeofdata + "/muD",
      Form("Ztrack_%s_sig_%s_muDeta", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HBackgroundMC.H1["HTrackMuonEta"], HBackgroundData.H1["HTrackMuonEta"],
      "Background |#Delta#eta_{#mu#mu}|", "dN/d#Delta#eta", false, S,
      OutputBase + "/" + typeofdata + "/muD",
      Form("Ztrack_%s_bkg_%s_muDeta", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HSignalMC.H1["HPhi"], HSignalData.H1["HPhi"],
      "Signal |#Delta#phi_{Z,track}|", "dN/d#Delta#phi", false, S,
      OutputBase + "/" + typeofdata + "/Dphi",
      Form("Ztrack_%s_sig_%s_Dphi", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HBackgroundMC.H1["HPhi"], HBackgroundData.H1["HPhi"],
      "Background |#Delta#phi_{Z,track}|", "dN/d#Delta#phi", false, S,
      OutputBase + "/" + typeofdata + "/Dphi",
      Form("Ztrack_%s_bkg_%s_Dphi", typeofdata, Identifier.c_str()));
   
   Draw1DPlot(HSignalMCSB.H1["HPhi"], HSignalDataSB.H1["HPhi"],
      "Signal - Background |#Delta#phi_{Z,track}|", "dN/d#Delta#phi", false, S,
      OutputBase + "/" + typeofdata + "/Dphi",
      Form("Ztrack_%s_sb_%s_Dphi", typeofdata, Identifier.c_str()));

   {
      // TODO: do something about this 4-curve plot
      //// TH1D *hMC_phi_com = (TH1D*) hMC_phi->Clone("hMC_phi_com");
      //// TH1D *hMC_bkg_phi_com = (TH1D*) hMC_bkg_phi->Clone("hMC_bkg_phi_com");
      //// TH1D *hMC_sb_phi_com = (TH1D*) hMC_sb_phi->Clone("hMC_sb_phi_com");
      //// TH1D *hpp_phi_com = (TH1D*) hpp_phi->Clone("hpp_phi_com");

      //// hMC_phi_com->GetXaxis()->SetRangeUser(0,3.2);
      //// hMC_bkg_phi_com->GetXaxis()->SetRangeUser(0,3.2);
      //// hMC_sb_phi_com->GetXaxis()->SetRangeUser(0,3.2);
      //// hpp_phi_com->GetXaxis()->SetRangeUser(0,3.2);

      //// max1 = hMC_phi_com->GetMaximum();
      //// max2 = hMC_bkg_phi_com->GetMaximum();

      //// hMC_phi_com->SetMarkerColor(kBlack);
      //// hMC_bkg_phi_com->SetMarkerColor(kBlue);
      //// hMC_sb_phi_com->SetMarkerColor(kRed);

      //// hMC_phi_com->SetLineColor(kBlack);
      //// hMC_bkg_phi_com->SetLineColor(kBlue);
      //// hMC_sb_phi_com->SetLineColor(kRed);
      //// hpp_phi_com->SetLineColor(kBlack);

      //// hMC_phi_com->SetMarkerStyle(kFullCircle);
      //// hMC_bkg_phi_com->SetMarkerStyle(kFullCircle);
      //// hMC_sb_phi_com->SetMarkerStyle(kFullCircle);

      //// hpp_phi_com->SetLineWidth(2);

      //// 
      //// if(max1<max2) hMC_bkg_phi_com->Draw("ep");
      //// else hMC_phi_com->Draw("ep");
      //// hMC_phi_com->Draw("ep same");
      //// hMC_bkg_phi_com->Draw("ep same");

      //// hMC_sb_phi_com->Draw("ep same");
      //// hpp_phi_com->Draw("hist same");

      //// if(max1<max2) max1=max2;

      //// hMC_phi_com->SetXTitle("#Delta#phi_{Z,track}");
      //// hMC_bkg_phi_com->SetXTitle("#Delta#phi_{Z,track}");
      //// hMC_phi_com->SetYTitle("dN/d#Delta#phi");
      //// hMC_bkg_phi_com->SetYTitle("dN/d#Delta#phi");

      //// TLegend leg1(0.58,0.68,0.98,0.9);
      //// leg1.AddEntry(hMC_phi_com ,"raw","lep");
      //// leg1.AddEntry(hMC_bkg_phi_com ,"bkg","lep");
      //// leg1.AddEntry(hMC_sb_phi_com ,"raw-bkg","lep");
      //// leg1.AddEntry(hpp_phi_com ,"pp","l");
      //// leg1.SetFillColorAlpha(kWhite,0);
      //// leg1.SetLineColor(kBlack);
      //// leg1.SetLineWidth(1);
      //// leg1.Draw();

      //// pt->Draw();
      //// pt2->Draw();
      //// pt3->Draw();

      //// //cout<<"max1 = "<<max1<<endl;
      //// //hMC_phi_com->SetMinimum(0);
      //// hMC_phi_com->SetMaximum(max1/2.56);
      //// //hMC_bkg_phi_com->SetMinimum(0);
      //// hMC_bkg_phi_com->SetMaximum(max1/2.56);

      //// if(ptL==30&&centL==0&&centH==30){
      ////  hMC_phi_com->SetMaximum(max1);
      ////  hMC_bkg_phi_com->SetMaximum(max1);
      //// }else if(ptL==30&&centL==30&&centH==50){
      ////  hMC_phi_com->SetMaximum(max1/1.6);
      ////  hMC_bkg_phi_com->SetMaximum(max1/1.6);
      //// }

      //// //hMC_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
      //// //hMC_bkg_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
      //// //hMC_sb_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
      //// //hpp_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);

      //// //ptN0->Draw();

      //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// c->Clear();
   }

   Draw1DPlot(HSignalMCSBR.H1["HPhi"], HSignalDataSBR.H1["HPhi"],
         "Signal / Background |#Delta#phi_{Z,track}|", "dN/d#Delta#phi", true, S,
         OutputBase + "/" + typeofdata + "/Dphi",
         Form("Ztrack_%s_sbr_%s_Dphi", typeofdata, Identifier.c_str()));

   // TODO Check this?
   //// hMC_MuDphi->SetMaximum(3.0/binnum); 
   //// hData_MuDphi->SetMaximum(3.0/binnum); 
   Draw1DPlot(HSignalMC.H1["HTrackMuonPhi"], HSignalData.H1["HTrackMuonPhi"],
         "Signal |#Delta#phi_{#mu#mu}|", "dN/d#Delta#phi", false, S,
         OutputBase + "/" + typeofdata + "/muD",
         Form("Ztrack_%s_sig_%s_muDphi", typeofdata, Identifier.c_str()));
   
   //// hMC_bkg_MuDphi->SetMaximum(3.0/binnum); 
   //// hData_bkg_MuDphi->SetMaximum(3.0/binnum); 
   Draw1DPlot(HSignalMC.H1["HTrackMuonPhi"], HSignalData.H1["HTrackMuonPhi"],
      "Background |#Delta#phi_{#mu#mu}|", "dN/d#Delta#phi", false, S,
      OutputBase + "/" + typeofdata + "/muD",
      Form("Ztrack_%s_bkg_%s_muDphi", typeofdata, Identifier.c_str()));


   // Now we move to 2D plots

   Draw2DPlot2Panel(HSignalMC.H2["HEtaPhi"], HSignalData.H2["HEtaPhi"],
      "Signal #Delta#eta_{Z,track}", "Signal #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/3D",
      Form("Ztrack_%s_sig_%s_Detaphi_3D", typeofdata, Identifier.c_str()), "lego20");
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HEtaPhi"], HBackgroundData.H2["HEtaPhi"],
      "Background #Delta#eta_{Z,track}", "Background #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/3D",
      Form("Ztrack_%s_bkg_%s_Detaphi_3D", typeofdata, Identifier.c_str()), "lego20");

   Draw2DPlot2Panel(HSignalMCSB.H2["HEtaPhi"], HSignalDataSB.H2["HEtaPhi"],
      "Signal - Background #Delta#eta_{Z,track}", "Signal - Background #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/3D",
      Form("Ztrack_%s_sb_%s_Detaphi_3D", typeofdata, Identifier.c_str()), "lego20");
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HEtaPhi"], HSignalDataSBR.H2["HEtaPhi"],
      "Signal/Background #Delta#eta_{Z,track}", "Signal/Background #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/3D",
      Form("Ztrack_%s_sbr_%s_Detaphi_3D", typeofdata, Identifier.c_str()), "lego20");
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HEtaPhi"], HSignalDataSBR.H2["HEtaPhi"],
      "Signal/Background #Delta#eta_{Z,track}", "Signal/Background #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/3D",
      Form("Ztrack_%s_sbr_%s_Detaphi_COLZ", typeofdata, Identifier.c_str()), "colz");
   
   Draw2DPlot2Panel(HSignalMCGen.H2["HEtaPhi"], HSignalMCGen.H2["HEtaPhi"],
      "MC Gen #Delta#eta_{Z,track}", "MC Gen #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/gen",
      Form("Ztrack_%s_sig_%s_Detaphi_gen", typeofdata, Identifier.c_str()), "lego20",
      {"Signal", "Background"});
   
   Draw2DPlot2Panel(HSignalMCGenSB.H2["HEtaPhi"], HSignalMCGenSBR.H2["HEtaPhi"],
      "MC Gen #Delta#eta_{Z,track}", "MC Gen #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/gen",
      Form("Ztrack_%s_sig_%s_Detaphi_gensub", typeofdata, Identifier.c_str()), "lego20",
      {"Signal - Background", "Signal/Background"});
   
   Draw2DPlot2Panel(HSignalMCGen.H2["HEtaPhi"], HSignalMCGen.H2["HEtaPhi"],
      "MC Gen #Delta#eta_{Z,track}", "MC Gen #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/gen",
      Form("Ztrack_%s_sig_%s_Detaphi_gen_COLZ", typeofdata, Identifier.c_str()), "colz",
      {"Signal", "Background"});

   Draw2DPlot2Panel(HSignalMCGenSB.H2["HEtaPhi"], HSignalMCGenSBR.H2["HEtaPhi"],
      "MC Gen #Delta#eta_{Z,track}", "MC Gen #Delta#phi_{Z,track}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/gen",
      Form("Ztrack_%s_sig_%s_Detaphi_gensub_COLZ", typeofdata, Identifier.c_str()), "colz",
      {"Signal - Background", "Signal/Background"});
  
   // Now we move on to some 3-panel plots
   
   Draw2DPlot3Panel(HSignalMCSB.H2["HEtaPhi"], HSignalDataSB.H2["HEtaPhi"], HppMC.H2["HEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "dN/d#Delta#eta#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/pp",
      Form("Ztrack_%s_sb_%s_Detaphi_pp", typeofdata, Identifier.c_str()), "lego20",
      {"Signal - Background MC", "Signal - Background Data", "pp MC (NPU = 0)"});
   
   Draw2DPlot3Panel(HSignalMCSB.H2["HEtaPhi"], HSignalDataSB.H2["HEtaPhi"], HppMC.H2["HEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "dN/d#Delta#eta#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/pp",
      Form("Ztrack_%s_sb_%s_Detaphi_pp_COLZ", typeofdata, Identifier.c_str()), "colz",
      {"Signal - Background MC", "Signal - Background Data", "pp MC (NPU = 0)"});

   Draw2DPlot3Panel(HSignalMCSB.H2["HEtaPhi"], HSignalMCSBR.H2["HEtaPhi"], HppMC.H2["HEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "dN/d#Delta#eta#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/pp",
      Form("Ztrack_%s_sbr_%s_Detaphi_pp", typeofdata, Identifier.c_str()), "lego20",
      {"Signal - Background MC", "Signal/Background Data", "pp MC (NPU = 0)"});
   
   Draw2DPlot3Panel(HSignalMCSB.H2["HEtaPhi"], HSignalMCSBR.H2["HEtaPhi"], HppMC.H2["HEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "dN/d#Delta#eta#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/pp",
      Form("Ztrack_%s_sbr_%s_Detaphi_pp_COLZ", typeofdata, Identifier.c_str()), "colz",
      {"Signal - Background MC", "Signal/Background Data", "pp MC (NPU = 0)"});
  
   // Back to 2 panel?
   
   Draw2DPlot2Panel(HSignalMC.H2["HTrackMuonDEtaDPhi"], HSignalData.H2["HTrackMuonDEtaDPhi"],
      "#Delta#eta_{#mu#mu}", "#Delta#phi_{#mu#mu}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/muD",
      Form("Ztrack_%s_sig_%s_muDetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});

   Draw2DPlot2Panel(HBackgroundMC.H2["HTrackMuonDEtaDPhi"], HBackgroundData.H2["HTrackMuonDEtaDPhi"],
      "#Delta#eta_{#mu#mu}", "#Delta#phi_{#mu#mu}", "dN/d#Delta#etad#Delta#phi", S,
      OutputBase + "/" + typeofdata + "/muD",
      Form("Ztrack_%s_bkg_%s_muDetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});

   // TODO: do something about these projected 2-panel plots
   {
      //// c->Divide(2);
      //// c->cd(1);

      //// int MCNbinsX = hMC_sbr_etaphi_1->GetNbinsX();
      //// int DataNbinsX = hMC_sbr_etaphi_1->GetNbinsX();

      //// TH1D* hMC_sbr_etaphi_projphi = (TH1D*) hMC_sbr_etaphi_1->ProjectionY("hMC_sbr_etaphi_projphi",1,MCNbinsX);
      //// TH1D* hData_sbr_etaphi_projphi = (TH1D*) hData_sbr_etaphi_1->ProjectionY("hData_sbr_etaphi_projphi",1,DataNbinsX);

      //// hMC_sbr_etaphi_projphi->Scale(1./MCNbinsX);
      //// hData_sbr_etaphi_projphi->Scale(1./DataNbinsX);

      //// hMC_sbr_etaphi_projphi->Draw("COLZ");
      //// hMC_sbr_etaphi_projphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track} (projection)");
      //// hMC_sbr_etaphi_projphi->GetXaxis()->SetTitleSize(30);
      //// hMC_sbr_etaphi_projphi->GetXaxis()->SetLabelSize(24);
      //// hMC_sbr_etaphi_projphi->GetXaxis()->SetTitleOffset(1.5);
      //// hMC_sbr_etaphi_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
      //// hMC_sbr_etaphi_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

      //// pt->Draw();
      //// pt2->Draw();
      //// pt3->Draw();

      //// c->cd(2);
      //// hData_sbr_etaphi_projphi->Draw("COLZ");
      //// hData_sbr_etaphi_projphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track} (projection)");
      //// hData_sbr_etaphi_projphi->GetXaxis()->SetTitleSize(30);
      //// hData_sbr_etaphi_projphi->GetXaxis()->SetLabelSize(24);
      //// hData_sbr_etaphi_projphi->GetXaxis()->SetTitleOffset(1.5);
      //// hData_sbr_etaphi_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
      //// hData_sbr_etaphi_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

      //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// c->Clear();

      //// c->Divide(2);
      //// c->cd(1);

      //// int MCNbinsY = hMC_sbr_etaphi_1->GetNbinsY();
      //// int DataNbinsY = hMC_sbr_etaphi_1->GetNbinsY();

      //// TH1D* hMC_sbr_etaphi_projeta = (TH1D*) hMC_sbr_etaphi_1->ProjectionX("hMC_sbr_etaphi_projeta",1,(int) MCNbinsY/2);
      //// TH1D* hData_sbr_etaphi_projeta = (TH1D*) hData_sbr_etaphi_1->ProjectionX("hData_sbr_etaphi_projeta",1,(int) DataNbinsY/2);

      //// hMC_sbr_etaphi_projeta->Scale(2./MCNbinsY);
      //// hData_sbr_etaphi_projeta->Scale(2./DataNbinsY);

      //// hMC_sbr_etaphi_projeta->Draw("COLZ");
      //// hMC_sbr_etaphi_projeta->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track} (projection)");
      //// hMC_sbr_etaphi_projeta->GetXaxis()->SetTitleSize(30);
      //// hMC_sbr_etaphi_projeta->GetXaxis()->SetLabelSize(24);
      //// hMC_sbr_etaphi_projeta->GetXaxis()->SetTitleOffset(1.5);
      //// hMC_sbr_etaphi_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
      //// hMC_sbr_etaphi_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

      //// pt->Draw();
      //// pt2->Draw();
      //// pt3->Draw();

      //// c->cd(2);
      //// hData_sbr_etaphi_projeta->Draw("COLZ");
      //// hData_sbr_etaphi_projeta->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track} (projection)");
      //// hData_sbr_etaphi_projeta->GetXaxis()->SetTitleSize(30);
      //// hData_sbr_etaphi_projeta->GetXaxis()->SetLabelSize(24);
      //// hData_sbr_etaphi_projeta->GetXaxis()->SetTitleOffset(1.5);
      //// hData_sbr_etaphi_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
      //// hData_sbr_etaphi_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

      //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
      //// c->Clear();
   }

   // /* Don't draw other axes yet 
   Draw2DPlot2Panel(HSignalMC.H2["HMaxHadronEtaPhi"], HSignalData.H2["HMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_maxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HMaxHadronEtaPhi"], HBackgroundData.H2["HMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_maxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HMaxHadronEtaPhi"], HSignalDataSB.H2["HMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_maxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HMaxHadronEtaPhi"], HSignalDataSBR.H2["HMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_maxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});
   
   Draw2DPlot2Panel(HSignalMC.H2["HMaxOppositeHadronEtaPhi"], HSignalData.H2["HMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxOetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_maxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HMaxOppositeHadronEtaPhi"], HBackgroundData.H2["HMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxOetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_maxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HMaxOppositeHadronEtaPhi"], HSignalDataSB.H2["HMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxOetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_maxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HMaxOppositeHadronEtaPhi"], HSignalDataSBR.H2["HMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/maxOetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_maxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});
   
   Draw2DPlot2Panel(HSignalMC.H2["HWTAEtaPhi"], HSignalData.H2["HWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_WTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HWTAEtaPhi"], HBackgroundData.H2["HWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_WTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HWTAEtaPhi"], HSignalDataSB.H2["HWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_WTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HWTAEtaPhi"], HSignalDataSBR.H2["HWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_WTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});

   Draw2DPlot2Panel(HSignalMC.H2["HWTAMoreEtaPhi"], HSignalData.H2["HWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAMoreetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_WTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HWTAMoreEtaPhi"], HBackgroundData.H2["HWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAMoreetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_WTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HWTAMoreEtaPhi"], HSignalDataSB.H2["HWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAMoreetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_WTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HWTAMoreEtaPhi"], HSignalDataSBR.H2["HWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/WTAMoreetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_WTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});

   Draw2DPlot2Panel(HSignalMC.H2["HZMaxHadronEtaPhi"], HSignalData.H2["HZMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/Zmaxetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_Zmaxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HZMaxHadronEtaPhi"], HBackgroundData.H2["HZMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/Zmaxetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_Zmaxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HZMaxHadronEtaPhi"], HSignalDataSB.H2["HZMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/Zmaxetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_Zmaxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HZMaxHadronEtaPhi"], HSignalDataSBR.H2["HZMaxHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/Zmaxetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_Zmaxetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});
   
   Draw2DPlot2Panel(HSignalMC.H2["HZMaxOppositeHadronEtaPhi"], HSignalData.H2["HZMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZmaxOetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_ZmaxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HZMaxOppositeHadronEtaPhi"], HBackgroundData.H2["HZMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZmaxOetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_ZmaxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HZMaxOppositeHadronEtaPhi"], HSignalDataSB.H2["HZMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZmaxOetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_ZmaxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HZMaxOppositeHadronEtaPhi"], HSignalDataSBR.H2["HZMaxOppositeHadronEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZmaxOetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_ZmaxOetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});
   
   Draw2DPlot2Panel(HSignalMC.H2["HZWTAEtaPhi"], HSignalData.H2["HZWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_ZWTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HZWTAEtaPhi"], HBackgroundData.H2["HZWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_ZWTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HZWTAEtaPhi"], HSignalDataSB.H2["HZWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_ZWTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HZWTAEtaPhi"], HSignalDataSBR.H2["HZWTAEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_ZWTAetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});

   Draw2DPlot2Panel(HSignalMC.H2["HZWTAMoreEtaPhi"], HSignalData.H2["HZWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAMoreetaphi",
      Form("Ztrack_%s_sig_%s_Detaphi_ZWTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal MC", "Signal Data"});
   
   Draw2DPlot2Panel(HBackgroundMC.H2["HZWTAMoreEtaPhi"], HBackgroundData.H2["HZWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAMoreetaphi",
      Form("Ztrack_%s_bkg_%s_Detaphi_ZWTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Background MC", "Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSB.H2["HZWTAMoreEtaPhi"], HSignalDataSB.H2["HZWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAMoreetaphi",
      Form("Ztrack_%s_sb_%s_Detaphi_ZWTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal-Background MC", "Signal-Background Data"});
   
   Draw2DPlot2Panel(HSignalMCSBR.H2["HZWTAMoreEtaPhi"], HSignalDataSBR.H2["HZWTAMoreEtaPhi"],
      "#Delta#eta_{Z,track}", "#Delta#phi_{Z,track}", "", S,
      OutputBase + "/" + typeofdata + "/ZWTAMoreetaphi",
      Form("Ztrack_%s_sbr_%s_Detaphi_ZWTAMoreetaphi", typeofdata, Identifier.c_str()), "lego20",
      {"Signal/Background MC", "Signal/Background Data"});
   // */
}


void DivideByBinWidth(TH1D *H)
{
   if(H == nullptr)
      return;

   int NBin = H->GetNbinsX();
   for(int i = 1; i <= NBin; i++)
   {
      double XL = H->GetXaxis()->GetBinLowEdge(i);
      double XH = H->GetXaxis()->GetBinUpEdge(i);
      H->SetBinContent(i, H->GetBinContent(i) / (XH - XL));
      H->SetBinError(i, H->GetBinError(i) / (XH - XL));
   }
}

void DivideByBinWidth(TH2D *H)
{
   if(H == nullptr)
      return;

   int NBinX = H->GetNbinsX();
   int NBinY = H->GetNbinsY();
   for(int iX = 1; iX <= NBinX; iX++)
   {
      for(int iY = 1; iY <= NBinY; iY++)
      {
         double XL = H->GetXaxis()->GetBinLowEdge(iY);
         double XH = H->GetXaxis()->GetBinUpEdge(iY);
         double YL = H->GetYaxis()->GetBinLowEdge(iY);
         double YH = H->GetYaxis()->GetBinUpEdge(iY);
         H->SetBinContent(iX, iY, H->GetBinContent(iX, iY) / (XH - XL) / (YH - YL));
         H->SetBinError(iX, iY, H->GetBinError(iX, iY) / (XH - XL) / (YH - YL));
      }
   }
}

void Draw1DPlot(TH1D *H1, TH1D *H2, string XTitle, string YTitle, bool WithMin,
   Setting &S, string Base, string Tag)
{
   if(H1 == nullptr || H2 == nullptr)
      return;
   
   TCanvas Canvas("Canvas", "", 800, 800);

   double Max1 = H1->GetMaximum();
   double Max2 = H2->GetMaximum();
   double Min1 = H1->GetMinimum();
   double Min2 = H2->GetMinimum();
   
   if(Max1 < Max2)
   {
      H1->Draw();
      H2->Draw("same");
   }
   else
   {
      H2->Draw();
      H1->Draw("same");
   }

   double Max = (Max1 < Max2) ? Max2 : Max1;
   double Min = (Min1 < Min2) ? Min1 : Min2;

   H1->SetXTitle(XTitle.c_str());
   H1->SetYTitle(YTitle.c_str());
   H2->SetXTitle(XTitle.c_str());
   H2->SetYTitle(YTitle.c_str());

   TLegend Legend(0.58, 0.78, 0.98, 0.90);
   Legend.AddEntry(H1, "Monte Carlo: DYLL","lep");
   Legend.AddEntry(H2, Form("Data: %s",typeofdatatext),"lep");
   Legend.SetFillStyle(0);
   Legend.SetLineColor(kBlack);
   Legend.SetLineWidth(1);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   
   Legend.Draw();

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();

   Latex.DrawLatex(0.18, 0.88, Form("%.0f %%< Centrality < %.0f %%", S.centL, S.centH));
   Latex.DrawLatex(0.18, 0.82, Form("%.1f < Z p_{T} < %.1f", S.ptL, S.ptH));
   Latex.DrawLatex(0.18, 0.76, Form("%.1f < Track p_{T} < %.1f", S.TptL, S.TptH));
   // Latex.DrawLatex(0.10, 0.97, Form("Signal N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f", tM_tN, tD_tN));

   H1->SetMaximum(1.6 * Max); 
   H2->SetMaximum(1.6 * Max); 

   if(WithMin == false)
   {
      H1->SetMinimum(0);
      H2->SetMinimum(0);
   }
   else
   {
      H1->SetMinimum(Min);
      H2->SetMinimum(Min);
   }
   
   Canvas.SaveAs(Form("%s/%s.png", Base.c_str(), Tag.c_str())); 
   // Canvas.SaveAs(Form("%s/pdf/%s.pdf", Base.c_str(), Tag.c_str())); 
   // Canvas.SaveAs(Form("%s/C/%s.C", Base.c_str(), Tag.c_str())); 
}

void Draw2DPlot2Panel(TH2D *H1, TH2D *H2, string XTitle, string YTitle, string ZTitle,
   Setting &S, string Base, string Tag, string Option, vector<string> Identifier)
{
   if(H1 == nullptr || H2 == nullptr)
      return;

   TCanvas Canvas("Canvas", "", 1400, 800);

   Canvas.Divide(2);
   TPad *P1 = (TPad *)Canvas.cd(1);
   P1->SetTheta(60.839);
   P1->SetPhi(38.0172);

   if(Identifier.size() >= 1)
      H1->SetTitle(Identifier[0].c_str());
   else
      H1->SetTitle("MC");
   H1->Draw(Option.c_str());
   H1->GetXaxis()->SetTitle(XTitle.c_str());
   H1->GetYaxis()->SetTitle(YTitle.c_str());
   H1->GetXaxis()->SetTitleSize(30);
   H1->GetYaxis()->SetTitleSize(30);
   H1->GetXaxis()->SetTitleOffset(3.0);
   H1->GetYaxis()->SetTitleOffset(2.5);
   H1->GetXaxis()->SetNdivisions(50205, kFALSE);
   H1->GetZaxis()->SetTitle(ZTitle.c_str());

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();

   Latex.DrawLatex(0.03, 0.94, Form("%.0f %% < Centrality < %.0f %%", S.centL, S.centH));
   Latex.DrawLatex(0.03, 0.88, Form("%.1f < Z p_{T} < %.1f", S.ptL, S.ptH));
   Latex.DrawLatex(0.03, 0.82, Form("%.1f < Track p_{T} < %.1f", S.TptL, S.TptH));

   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.97, 0.94, H1->GetTitle());
   
   TPad *P2 = (TPad *)Canvas.cd(2);
   P2->SetTheta(60.839);
   P2->SetPhi(38.0172);

   if(Identifier.size() >= 2)
      H2->SetTitle(Identifier[1].c_str());
   else
      H2->SetTitle("Data");
   H2->Draw(Option.c_str());
   H2->GetXaxis()->SetTitle(XTitle.c_str());
   H2->GetYaxis()->SetTitle(YTitle.c_str());
   H2->GetXaxis()->SetTitleSize(30);
   H2->GetYaxis()->SetTitleSize(30);
   H2->GetXaxis()->SetTitleOffset(3.0);
   H2->GetYaxis()->SetTitleOffset(2.5);
   H2->GetXaxis()->SetNdivisions(50205, kFALSE);
   H2->GetZaxis()->SetTitle(ZTitle.c_str());

   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.97, 0.94, H2->GetTitle());
   
   // ptN0->Draw();

   Canvas.SaveAs(Form("%s/%s.png", Base.c_str(), Tag.c_str())); 
   // Canvas.SaveAs(Form("%s/pdf/%s.pdf", Base.c_str(), Tag.c_str())); 
   // Canvas.SaveAs(Form("%s/C/%s.C", Base.c_str(), Tag.c_str())); 
}

void Draw2DPlot3Panel(TH2D *H1, TH2D *H2, TH2D *H3, string XTitle, string YTitle, string ZTitle,
   Setting &S, string Base, string Tag, string Option, vector<string> Identifier)
{
   if(H1 == nullptr || H2 == nullptr || H3 == nullptr)
      return;

   TCanvas Canvas("Canvas", "", 2000, 800);

   Canvas.Divide(3);
   TPad *P1 = (TPad *)Canvas.cd(1);
   P1->SetTheta(60.839);
   P1->SetPhi(38.0172);

   if(Identifier.size() >= 1)
      H1->SetTitle(Identifier[0].c_str());
   else
      H1->SetTitle("PbPb MC");
   H1->Draw(Option.c_str());
   H1->GetXaxis()->SetTitle(XTitle.c_str());
   H1->GetYaxis()->SetTitle(YTitle.c_str());
   H1->GetXaxis()->SetTitleSize(24);
   H1->GetYaxis()->SetTitleSize(24);
   H1->GetXaxis()->SetTitleOffset(3.0);
   H1->GetYaxis()->SetTitleOffset(2.5);
   H1->GetXaxis()->SetNdivisions(50205, kFALSE);
   H1->GetZaxis()->SetTitle(ZTitle.c_str());

   TLatex Latex;
   Latex.SetTextFont(42);
   Latex.SetTextSize(0.03);
   Latex.SetNDC();

   Latex.DrawLatex(0.03, 0.94, Form("%.0f %% < Centrality < %.0f %%", S.centL, S.centH));
   Latex.DrawLatex(0.03, 0.88, Form("%.1f < Z p_{T} < %.1f", S.ptL, S.ptH));
   Latex.DrawLatex(0.03, 0.82, Form("%.1f < Track p_{T} < %.1f", S.TptL, S.TptH));

   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.97, 0.94, H1->GetTitle());

   TPad *P2 = (TPad *)Canvas.cd(2);
   P2->SetTheta(60.839);
   P2->SetPhi(38.0172);

   if(Identifier.size() >= 2)
      H2->SetTitle(Identifier[1].c_str());
   else
      H2->SetTitle("Data");
   H2->Draw(Option.c_str());
   H2->GetXaxis()->SetTitle(XTitle.c_str());
   H2->GetYaxis()->SetTitle(YTitle.c_str());
   H2->GetXaxis()->SetTitleSize(24);
   H2->GetYaxis()->SetTitleSize(24);
   H2->GetXaxis()->SetTitleOffset(3.0);
   H2->GetYaxis()->SetTitleOffset(2.5);
   H2->GetXaxis()->SetNdivisions(50205, kFALSE);
   H2->GetZaxis()->SetTitle(ZTitle.c_str());
   
   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.97, 0.94, H2->GetTitle());

   TPad *P3 = (TPad *)Canvas.cd(3);
   P3->SetTheta(60.839);
   P3->SetPhi(38.0172);

   if(Identifier.size() >= 3)
      H3->SetTitle(Identifier[1].c_str());
   else
      H3->SetTitle("pp MC");
   H3->Draw(Option.c_str());
   H3->GetXaxis()->SetTitle(XTitle.c_str());
   H3->GetYaxis()->SetTitle(YTitle.c_str());
   H3->GetXaxis()->SetTitleSize(24);
   H3->GetYaxis()->SetTitleSize(24);
   H3->GetXaxis()->SetTitleOffset(3.0);
   H3->GetYaxis()->SetTitleOffset(2.5);
   H3->GetXaxis()->SetNdivisions(50205, kFALSE);
   H3->GetZaxis()->SetTitle(ZTitle.c_str());

   Latex.SetTextSize(0.05);
   Latex.SetTextAlign(32);
   Latex.DrawLatex(0.97, 0.94, H3->GetTitle());
   
   // ptN0->Draw();

   Canvas.SaveAs(Form("%s/%s.png", Base.c_str(), Tag.c_str())); 
   // Canvas.SaveAs(Form("%s/pdf/%s.pdf", Base.c_str(), Tag.c_str())); 
   // Canvas.SaveAs(Form("%s/C/%s.C", Base.c_str(), Tag.c_str())); 
}
