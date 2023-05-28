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

#include "SetStyle.h"

#define TptL_min 0.5
#define typeofdata "20230518"
#define typeofdatatext "single muon"

struct Files;
struct Plots;
int main(int argc, char *argv[]);
void ZtrackDraw_single(Files &File, int binnum = 40,
   float ptL = 20, float ptH = 2000,
   float centL = 0, float centH = 90,
   float TptL = 0, float TptH = 10000);
void DivideByBinWidth(TH1D *H = nullptr);
void DivideByBinWidth(TH2D *H = nullptr);

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
   TH1D *HEta;
   TH1D *HPhi;
   TH2D *HEtaphi;
   TH1D *HMuDeta;
   TH1D *HMuDphi;
   TH2D *HMuDetaphi;
   TH2D *HMaxetaphi;
   TH2D *HMaxOetaphi;
   TH2D *HWTAetaphi;
   TH2D *HWTAMoreetaphi;
   TH2D *HZmaxetaphi;
   TH2D *HZmaxOetaphi;
   TH2D *HZWTAetaphi;
   TH2D *HZWTAMoreetaphi;
public:
   Plots() {}
   Plots(TFile *File, string FolderName, int Rebin1D = 1, int Rebin2D = 1)
   {
      HEta            = Prepare1DHistogram(File, FolderName, "HEta", Rebin1D);
      HPhi            = Prepare1DHistogram(File, FolderName, "HPhi", Rebin1D);
      HEtaphi         = Prepare2DHistogram(File, FolderName, "HEtaPhi", Rebin2D);
      HMuDeta         = Prepare1DHistogram(File, FolderName, "HTrackMuonDEta", Rebin1D);
      HMuDphi         = Prepare1DHistogram(File, FolderName, "HTrackMuonDPhi", Rebin1D);
      HMuDetaphi      = Prepare2DHistogram(File, FolderName, "HTrackMuonDEtaDPhi", Rebin2D);
      HMaxetaphi      = Prepare2DHistogram(File, FolderName, "HMaxHadronEtaPhi", Rebin2D);
      HMaxOetaphi     = Prepare2DHistogram(File, FolderName, "HMaxOppositeHadronEtaPhi", Rebin2D);
      HWTAetaphi      = Prepare2DHistogram(File, FolderName, "HWTAEtaPhi", Rebin2D);
      HWTAMoreetaphi  = Prepare2DHistogram(File, FolderName, "HWTAMoreEtaPhi", Rebin2D);
      HZmaxetaphi     = Prepare2DHistogram(File, FolderName, "HZMaxHadronEtaPhi", Rebin2D);
      HZmaxOetaphi    = Prepare2DHistogram(File, FolderName, "HZMaxOppositeHadronEtaPhi", Rebin2D);
      HZWTAetaphi     = Prepare2DHistogram(File, FolderName, "HZWTAEtaPhi", Rebin2D);
      HZWTAMoreetaphi = Prepare2DHistogram(File, FolderName, "HZWTAMoreEtaPhi", Rebin2D);
   }
   Plots(Plots &other)
   {
      HEta            = (other.HEta != nullptr) ? (TH1D *)other.HEta->Clone() : nullptr;
      HPhi            = (other.HPhi != nullptr) ? (TH1D *)other.HPhi->Clone() : nullptr;
      HEtaphi         = (other.HEtaphi != nullptr) ? (TH2D *)other.HEtaphi->Clone() : nullptr;
      HMuDeta         = (other.HMuDeta != nullptr) ? (TH1D *)other.HMuDeta->Clone() : nullptr;
      HMuDphi         = (other.HMuDphi != nullptr) ? (TH1D *)other.HMuDphi->Clone() : nullptr;
      HMuDetaphi      = (other.HMuDetaphi != nullptr) ? (TH2D *)other.HMuDetaphi->Clone() : nullptr;
      HMaxetaphi      = (other.HMaxetaphi != nullptr) ? (TH2D *)other.HMaxetaphi->Clone() : nullptr;
      HMaxOetaphi     = (other.HMaxOetaphi != nullptr) ? (TH2D *)other.HMaxOetaphi->Clone() : nullptr;
      HWTAetaphi      = (other.HWTAetaphi != nullptr) ? (TH2D *)other.HWTAetaphi->Clone() : nullptr;
      HWTAMoreetaphi  = (other.HWTAMoreetaphi != nullptr) ? (TH2D *)other.HWTAMoreetaphi->Clone() : nullptr;
      HZmaxetaphi     = (other.HZmaxetaphi != nullptr) ? (TH2D *)other.HZmaxetaphi->Clone() : nullptr;
      HZmaxOetaphi    = (other.HZmaxOetaphi != nullptr) ? (TH2D *)other.HZmaxOetaphi->Clone() : nullptr;
      HZWTAetaphi     = (other.HZWTAetaphi != nullptr) ? (TH2D *)other.HZWTAetaphi->Clone() : nullptr;
      HZWTAMoreetaphi = (other.HZWTAMoreetaphi != nullptr) ? (TH2D *)other.HZWTAMoreetaphi->Clone() : nullptr;
   }
   void Subtract(Plots &other)
   {
      if(HEta != nullptr && other.HEta != nullptr) HEta->Add(other.HEta, -1);
      if(HPhi != nullptr && other.HPhi != nullptr) HPhi->Add(other.HPhi, -1);
      if(HEtaphi != nullptr && other.HEtaphi != nullptr) HEtaphi->Add(other.HEtaphi, -1);
      if(HMuDeta != nullptr && other.HMuDeta != nullptr) HMuDeta->Add(other.HMuDeta, -1);
      if(HMuDphi != nullptr && other.HMuDphi != nullptr) HMuDphi->Add(other.HMuDphi, -1);
      if(HMuDetaphi != nullptr && other.HMuDetaphi != nullptr) HMuDetaphi->Add(other.HMuDetaphi, -1);
      if(HMaxetaphi != nullptr && other.HMaxetaphi != nullptr) HMaxetaphi->Add(other.HMaxetaphi, -1);
      if(HMaxOetaphi != nullptr && other.HMaxOetaphi != nullptr) HMaxOetaphi->Add(other.HMaxOetaphi, -1);
      if(HWTAetaphi != nullptr && other.HWTAetaphi != nullptr) HWTAetaphi->Add(other.HWTAetaphi, -1);
      if(HWTAMoreetaphi != nullptr && other.HWTAMoreetaphi != nullptr) HWTAMoreetaphi->Add(other.HWTAMoreetaphi, -1);
      if(HZmaxetaphi != nullptr && other.HZmaxetaphi != nullptr) HZmaxetaphi->Add(other.HZmaxetaphi, -1);
      if(HZmaxOetaphi != nullptr && other.HZmaxOetaphi != nullptr) HZmaxOetaphi->Add(other.HZmaxOetaphi, -1);
      if(HZWTAetaphi != nullptr && other.HZWTAetaphi != nullptr) HZWTAetaphi->Add(other.HZWTAetaphi, -1);
      if(HZWTAMoreetaphi != nullptr && other.HZWTAMoreetaphi != nullptr) HZWTAMoreetaphi->Add(other.HZWTAMoreetaphi, -1);
   }
   void Divide(Plots &other)
   {
      if(HEta != nullptr && other.HEta != nullptr) HEta->Divide(other.HEta);
      if(HPhi != nullptr && other.HPhi != nullptr) HPhi->Divide(other.HPhi);
      if(HEtaphi != nullptr && other.HEtaphi != nullptr) HEtaphi->Divide(other.HEtaphi);
      if(HMuDeta != nullptr && other.HMuDeta != nullptr) HMuDeta->Divide(other.HMuDeta);
      if(HMuDphi != nullptr && other.HMuDphi != nullptr) HMuDphi->Divide(other.HMuDphi);
      if(HMuDetaphi != nullptr && other.HMuDetaphi != nullptr) HMuDetaphi->Divide(other.HMuDetaphi);
      if(HMaxetaphi != nullptr && other.HMaxetaphi != nullptr) HMaxetaphi->Divide(other.HMaxetaphi);
      if(HMaxOetaphi != nullptr && other.HMaxOetaphi != nullptr) HMaxOetaphi->Divide(other.HMaxOetaphi);
      if(HWTAetaphi != nullptr && other.HWTAetaphi != nullptr) HWTAetaphi->Divide(other.HWTAetaphi);
      if(HWTAMoreetaphi != nullptr && other.HWTAMoreetaphi != nullptr) HWTAMoreetaphi->Divide(other.HWTAMoreetaphi);
      if(HZmaxetaphi != nullptr && other.HZmaxetaphi != nullptr) HZmaxetaphi->Divide(other.HZmaxetaphi);
      if(HZmaxOetaphi != nullptr && other.HZmaxOetaphi != nullptr) HZmaxOetaphi->Divide(other.HZmaxOetaphi);
      if(HZWTAetaphi != nullptr && other.HZWTAetaphi != nullptr) HZWTAetaphi->Divide(other.HZWTAetaphi);
      if(HZWTAMoreetaphi != nullptr && other.HZWTAMoreetaphi != nullptr) HZWTAMoreetaphi->Divide(other.HZWTAMoreetaphi);
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

void ZtrackDraw_single(Files &Files, int binnum,
   float ptL, float ptH, float centL, float centH, float TptL, float TptH)
{
   cout << "ptL = " << ptL << ", ptH = " << ptH
      << ", centL = " << centL << ", centH = " << centH
      << ", TptL = " << TptL << ", TptH = " << TptH << endl;
   
   TCanvas *c = new TCanvas("c","",800,800);

   cout<<"Getting histograms..."<<endl;

   string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   replace(FolderName.begin(), FolderName.end(), '.', 'p');

   Plots HSignalData(Files.SignalData, FolderName);
   Plots HSignalMC(Files.SignalMC, FolderName);
   Plots HppData(Files.ppData, FolderName);
   Plots HppMC(Files.ppMC, FolderName);
   Plots HBackgroundData(Files.BackgroundData, FolderName);
   Plots HBackgroundMC(Files.BackgroundMC, FolderName);
   Plots HSignalMCGen(Files.SignalMCGen, FolderName);
   Plots HBackgroundMCGen(Files.BackgroundMCGen, FolderName);

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
   
   int countD0 = HSignalData.HEta->GetEntries();
   cout<<"Data 0 = "<<countD0<<endl;
   int countM0 = HSignalMC.HEta->GetEntries();
   cout<<"MC 0 = "<<countM0<<endl;

   int countDb = HBackgroundData.HEta->GetEntries();
   cout<<"Data Bkg = "<<countDb<<endl;
   int countMb = HBackgroundMC.HEta->GetEntries();
   cout<<"MC Bkg = "<<countMb<<endl;

   //// cout<<"Drawing..."<<endl;

   //// hMC_eta->SetMarkerStyle(24);
   //// hMC_phi->SetMarkerStyle(24);
   //// hMC_bkg_eta->SetMarkerStyle(24);
   //// hMC_bkg_phi->SetMarkerStyle(24);
   //// hMC_sb_eta->SetMarkerStyle(24);
   //// hMC_sb_phi->SetMarkerStyle(24);
   //// hMC_sbr_eta->SetMarkerStyle(24);
   //// hMC_sbr_phi->SetMarkerStyle(24);

   //// hData_eta->SetMarkerColor(kBlack);
   //// hMC_eta->SetMarkerColor(kRed);
   //// hData_phi->SetMarkerColor(kBlack);
   //// hMC_phi->SetMarkerColor(kRed);

   //// hData_eta->SetLineColor(kBlack);
   //// hMC_eta->SetLineColor(kRed);
   //// hData_phi->SetLineColor(kBlack);
   //// hMC_phi->SetLineColor(kRed);

   //// hData_bkg_eta->SetMarkerColor(kBlack);
   //// hMC_bkg_eta->SetMarkerColor(kRed);
   //// hData_bkg_phi->SetMarkerColor(kBlack);
   //// hMC_bkg_phi->SetMarkerColor(kRed);

   //// hData_bkg_eta->SetLineColor(kBlack);
   //// hMC_bkg_eta->SetLineColor(kRed);
   //// hData_bkg_phi->SetLineColor(kBlack);
   //// hMC_bkg_phi->SetLineColor(kRed);

   //// hData_sb_eta->SetMarkerColor(kBlack);
   //// hMC_sb_eta->SetMarkerColor(kRed);
   //// hData_sb_phi->SetMarkerColor(kBlack);
   //// hMC_sb_phi->SetMarkerColor(kRed);

   //// hData_sb_eta->SetLineColor(kBlack);
   //// hMC_sb_eta->SetLineColor(kRed);
   //// hData_sb_phi->SetLineColor(kBlack);
   //// hMC_sb_phi->SetLineColor(kRed);

   //// hData_sbr_eta->SetMarkerColor(kBlack);
   //// hMC_sbr_eta->SetMarkerColor(kRed);
   //// hData_sbr_phi->SetMarkerColor(kBlack);
   //// hMC_sbr_phi->SetMarkerColor(kRed);

   //// hData_sbr_eta->SetLineColor(kBlack);
   //// hMC_sbr_eta->SetLineColor(kRed);
   //// hData_sbr_phi->SetLineColor(kBlack);
   //// hMC_sbr_phi->SetLineColor(kRed);

   //// if(TptL==0) TptL=TptL_min;

   //// TLegend leg(0.58,0.78,0.98,0.9);
   //// leg.AddEntry(hMC_eta ,"Monte Carlo: DYLL","lep");
   //// leg.AddEntry(hData_eta ,Form("Data: %s",typeofdatatext),"lep");
   //// leg.SetFillColorAlpha(kWhite,0);
   //// leg.SetLineColor(kBlack);
   //// leg.SetLineWidth(1);

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

   //// // == Start drawing == //

   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Deta",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/3D",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/pp",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/muD",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/gen",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Deta/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/3D/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Deta/C",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi/C",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/3D/C",typeofdata));

/*
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxetaphi/C",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/maxOetaphi/C",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAetaphi/C",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C",typeofdata));

   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C",typeofdata));
   //// gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf",typeofdata));
   //// //gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C",typeofdata));
*/

   //// // Draw eta 

   //// double max1 = hMC_eta->GetMaximum();
   //// double max2 = hData_eta->GetMaximum();
   //// 
   //// if(max1<max2) hData_eta->Draw();
   //// else hMC_eta->Draw();
   //// hMC_eta->Draw("same");
   //// hData_eta->Draw("same");

   //// if(max1<max2) max1=max2;

   //// hMC_eta->SetXTitle("Signal |#Delta#eta_{Z,track}|");
   //// hData_eta->SetXTitle("Signal |#Delta#eta_{Z,track}|");
   //// hMC_eta->SetYTitle("dN/d#Delta#eta");
   //// hData_eta->SetYTitle("dN/d#Delta#eta");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_eta->SetMinimum(0);
   //// hMC_eta->SetMaximum(1.6*max1); 
   //// hData_eta->SetMinimum(0);
   //// hData_eta->SetMaximum(1.6*max1); 

   //// ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_bkg_eta->GetMaximum();
   //// max2 = hData_bkg_eta->GetMaximum();
   //// 
   //// if(max1<max2) hData_bkg_eta->Draw();
   //// else hMC_bkg_eta->Draw();
   //// hMC_bkg_eta->Draw("same");
   //// hData_bkg_eta->Draw("same");

   //// if(max1<max2) max1=max2;

   //// hMC_bkg_eta->SetXTitle("Background |#Delta#eta_{Z,track}|");
   //// hData_bkg_eta->SetXTitle("Background |#Delta#eta_{Z,track}|");
   //// hMC_bkg_eta->SetYTitle("dN/d#Delta#eta");
   //// hData_bkg_eta->SetYTitle("dN/d#Delta#eta");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_bkg_eta->SetMinimum(0);
   //// hMC_bkg_eta->SetMaximum(1.6*max1); 
   //// hData_bkg_eta->SetMinimum(0);
   //// hData_bkg_eta->SetMaximum(1.6*max1); 

   //// ptNb->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();


   //// max1 = hMC_sb_eta->GetMaximum();
   //// max2 = hData_sb_eta->GetMaximum();

   //// double min1 = hMC_sb_phi->GetMinimum();
   //// double min2 = hData_sb_phi->GetMinimum();
   //// if(min2<min1) min1=min2;
   //// 
   //// if(max1<max2) hData_sb_eta->Draw();
   //// else hMC_sb_eta->Draw();
   //// hMC_sb_eta->Draw("same");
   //// hData_sb_eta->Draw("same");

   //// hMC_sb_eta->SetXTitle("Signal - Background |#Delta#eta_{Z,track}|");
   //// hData_sb_eta->SetXTitle("Signal - Background |#Delta#eta_{Z,track}|");
   //// hMC_sb_eta->SetYTitle("dN/d#Delta#eta");
   //// hData_sb_eta->SetYTitle("dN/d#Delta#eta");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_sb_eta->SetMinimum(min1);
   //// hMC_sb_eta->SetMaximum(1.6*max1); 
   //// hData_sb_eta->SetMinimum(min1);
   //// hData_sb_eta->SetMaximum(1.6*max1); 

   //// //ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_sbr_eta->GetMaximum();
   //// max2 = hData_sbr_eta->GetMaximum();

   //// min1 = hMC_sbr_phi->GetMinimum();
   //// min2 = hData_sbr_phi->GetMinimum();
   //// if(min2<min1) min1=min2;
   //// 
   //// if(max1<max2) hData_sbr_eta->Draw();
   //// else hMC_sbr_eta->Draw();
   //// hMC_sbr_eta->Draw("same");
   //// hData_sbr_eta->Draw("same");

   //// hMC_sbr_eta->SetXTitle("Signal/Background |#Delta#eta_{Z,track}|");
   //// hData_sbr_eta->SetXTitle("Signal/Background |#Delta#eta_{Z,track}|");
   //// hMC_sbr_eta->SetYTitle("dN/d#Delta#eta");
   //// hData_sbr_eta->SetYTitle("dN/d#Delta#eta");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_sbr_eta->SetMinimum(min1);
   //// hMC_sbr_eta->SetMaximum(1.6*max1); 
   //// hData_sbr_eta->SetMinimum(min1);
   //// hData_sbr_eta->SetMaximum(1.6*max1); 

   //// //ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Deta/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_MuDeta->GetMaximum();
   //// max2 = hData_MuDeta->GetMaximum();
   //// 
   //// if(max1<max2) hData_MuDeta->Draw();
   //// else hMC_MuDeta->Draw();
   //// hMC_MuDeta->Draw("same");
   //// hData_MuDeta->Draw("same");

   //// hMC_MuDeta->SetXTitle("Signal |#Delta#eta_{#mu#mu}|");
   //// hData_MuDeta->SetXTitle("Signal |#Delta#eta_{#mu#mu}|");
   //// hMC_MuDeta->SetYTitle("dN/d#Delta#eta");
   //// hData_MuDeta->SetYTitle("dN/d#Delta#eta");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_MuDeta->SetMinimum(0);
   //// hMC_MuDeta->SetMaximum(3.0/binnum); 
   //// hData_MuDeta->SetMinimum(0);
   //// hData_MuDeta->SetMaximum(3.0/binnum); 

   //// //ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_bkg_MuDeta->GetMaximum();
   //// max2 = hData_bkg_MuDeta->GetMaximum();
   //// 
   //// if(max1<max2) hData_bkg_MuDeta->Draw();
   //// else hMC_bkg_MuDeta->Draw();
   //// hMC_bkg_MuDeta->Draw("same");
   //// hData_bkg_MuDeta->Draw("same");

   //// hMC_bkg_eta->SetXTitle("Background |#Delta#eta_{#mu#mu}|");
   //// hData_bkg_eta->SetXTitle("Background |#Delta#eta_{#mu#mu}|");
   //// hMC_bkg_eta->SetYTitle("dN/d#Delta#eta");
   //// hData_bkg_eta->SetYTitle("dN/d#Delta#eta");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_bkg_MuDeta->SetMinimum(0);
   //// hMC_bkg_MuDeta->SetMaximum(3.0/binnum); 
   //// hData_bkg_MuDeta->SetMinimum(0);
   //// hData_bkg_MuDeta->SetMaximum(3.0/binnum); 

   //// //ptNb->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDeta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_phi->GetMaximum();
   //// max2 = hData_phi->GetMaximum();
   //// 
   //// if(max1<max2) hData_phi->Draw();
   //// else hMC_phi->Draw();
   //// hMC_phi->Draw("same");
   //// hData_phi->Draw("same");

   //// if(max1<max2) max1=max2;

   //// hMC_phi->SetXTitle("Signal #Delta#phi_{Z,track}");
   //// hData_phi->SetXTitle("Signal #Delta#phi_{Z,track}");
   //// hMC_phi->SetYTitle("dN/d#Delta#phi");
   //// hData_phi->SetYTitle("dN/d#Delta#phi");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_phi->SetMinimum(0);
   //// hMC_phi->SetMaximum(1.6*max1);
   //// hData_phi->SetMinimum(0);
   //// hData_phi->SetMaximum(1.6*max1);

   //// ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_bkg_phi->GetMaximum();
   //// max2 = hData_bkg_phi->GetMaximum();
   //// 
   //// if(max1<max2) hData_bkg_phi->Draw();
   //// else hMC_bkg_phi->Draw();
   //// hMC_bkg_phi->Draw("same");
   //// hData_bkg_phi->Draw("same");

   //// if(max1<max2) max1=max2;

   //// hMC_bkg_phi->SetXTitle("Background #Delta#phi_{Z,track}");
   //// hData_bkg_phi->SetXTitle("Background #Delta#phi_{Z,track}");
   //// hMC_bkg_phi->SetYTitle("dN/d#Delta#phi");
   //// hData_bkg_phi->SetYTitle("dN/d#Delta#phi");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_bkg_phi->SetMinimum(0);
   //// hMC_bkg_phi->SetMaximum(1.6*max1);
   //// hData_bkg_phi->SetMinimum(0);
   //// hData_bkg_phi->SetMaximum(1.6*max1);

   //// ptNb->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_sb_phi->GetMaximum();
   //// max2 = hData_sb_phi->GetMaximum();

   //// min1 = hMC_sb_phi->GetMinimum();
   //// min2 = hData_sb_phi->GetMinimum();
   //// if(min2<min1) min1=min2;
   //// 
   //// if(max1<max2) hData_sb_phi->Draw();
   //// else hMC_sb_phi->Draw();
   //// hMC_sb_phi->Draw("same");
   //// hData_sb_phi->Draw("same");

   //// if(max1<max2) max1=max2;

   //// hMC_sb_phi->SetXTitle("Signal - Background #Delta#phi_{Z,track}");
   //// hData_sb_phi->SetXTitle("Signal - Background #Delta#phi_{Z,track}");
   //// hMC_sb_phi->SetYTitle("dN/d#Delta#phi");
   //// hData_sb_phi->SetYTitle("dN/d#Delta#phi");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_sb_phi->SetMinimum(min1);
   //// hMC_sb_phi->SetMaximum(1.6*max1);
   //// hData_sb_phi->SetMinimum(min1);
   //// hData_sb_phi->SetMaximum(1.6*max1);

   //// //ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

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

   //// max1 = hMC_sbr_phi->GetMaximum();
   //// max2 = hData_sbr_phi->GetMaximum();

   //// min1 = hMC_sbr_phi->GetMinimum();
   //// min2 = hData_sbr_phi->GetMinimum();
   //// if(min2<min1) min1=min2;
   //// 
   //// if(max1<max2) hData_sbr_phi->Draw();
   //// else hMC_sbr_phi->Draw();
   //// hMC_sbr_phi->Draw("same");
   //// hData_sbr_phi->Draw("same");

   //// if(max1<max2) max1=max2;

   //// hMC_sbr_phi->SetXTitle("Signal/Background #Delta#phi_{Z,track}");
   //// hData_sbr_phi->SetXTitle("Signal/Background #Delta#phi_{Z,track}");
   //// hMC_sbr_phi->SetYTitle("dN/d#Delta#phi");
   //// hData_sbr_phi->SetYTitle("dN/d#Delta#phi");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_sbr_phi->SetMinimum(min1);
   //// hMC_sbr_phi->SetMaximum(1.6*max1);
   //// hData_sbr_phi->SetMinimum(min1);
   //// hData_sbr_phi->SetMaximum(1.6*max1);

   //// //ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_MuDphi->GetMaximum();
   //// max2 = hData_MuDphi->GetMaximum();
   //// 
   //// if(max1<max2) hData_MuDphi->Draw();
   //// else hMC_MuDphi->Draw();
   //// hMC_MuDphi->Draw("same");
   //// hData_MuDphi->Draw("same");

   //// hMC_MuDphi->SetXTitle("Signal |#Delta#phi_{#mu#mu}|");
   //// hData_MuDphi->SetXTitle("Signal |#Delta#phi_{#mu#mu}|");
   //// hMC_MuDphi->SetYTitle("dN/d#Delta#phi");
   //// hData_MuDphi->SetYTitle("dN/d#Delta#phi");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_MuDphi->SetMinimum(0);
   //// hMC_MuDphi->SetMaximum(3.0/binnum); 
   //// hData_MuDphi->SetMinimum(0);
   //// hData_MuDphi->SetMaximum(3.0/binnum); 

   //// //ptN0->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// max1 = hMC_bkg_MuDphi->GetMaximum();
   //// max2 = hData_bkg_MuDphi->GetMaximum();
   //// 
   //// if(max1<max2) hData_bkg_MuDphi->Draw();
   //// else hMC_bkg_MuDphi->Draw();
   //// hMC_bkg_MuDphi->Draw("same");
   //// hData_bkg_MuDphi->Draw("same");

   //// hMC_bkg_phi->SetXTitle("Background |#Delta#phi_{#mu#mu}|");
   //// hData_bkg_phi->SetXTitle("Background |#Delta#phi_{#mu#mu}|");
   //// hMC_bkg_phi->SetYTitle("dN/d#Delta#phi");
   //// hData_bkg_phi->SetYTitle("dN/d#Delta#phi");

   //// leg.Draw();
   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();
   //// hMC_bkg_MuDphi->SetMinimum(0);
   //// hMC_bkg_MuDphi->SetMaximum(3.0/binnum); 
   //// hData_bkg_MuDphi->SetMinimum(0);
   //// hData_bkg_MuDphi->SetMaximum(3.0/binnum); 

   //// //ptNb->Draw();

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->SetCanvasSize(1400,800);
   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_etaphi_1->Draw("lego20");
   //// hMC_etaphi_1->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   //// hMC_etaphi_1->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   //// hMC_etaphi_1->GetXaxis()->SetTitleSize(30);
   //// hMC_etaphi_1->GetYaxis()->SetTitleSize(30);
   //// hMC_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_etaphi_1->Draw("lego20");
   //// hData_etaphi_1->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   //// hData_etaphi_1->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   //// hData_etaphi_1->GetXaxis()->SetTitleSize(30);
   //// hData_etaphi_1->GetYaxis()->SetTitleSize(30);
   //// hData_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hData_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hData_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_bkg_etaphi_1->Draw("lego20");
   //// hMC_bkg_etaphi_1->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   //// hMC_bkg_etaphi_1->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   //// hMC_bkg_etaphi_1->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_etaphi_1->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_bkg_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_bkg_etaphi_1->Draw("lego20");
   //// hData_bkg_etaphi_1->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   //// hData_bkg_etaphi_1->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   //// hData_bkg_etaphi_1->GetXaxis()->SetTitleSize(30);
   //// hData_bkg_etaphi_1->GetYaxis()->SetTitleSize(30);
   //// hData_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hData_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hData_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_bkg_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_etaphi_1->Draw("lego20");
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_etaphi_1->Draw("lego20");
   //// hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   //// hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   //// hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sbr_etaphi_1->Draw("lego20");
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sbr_etaphi_1->Draw("lego20");
   //// hData_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   //// hData_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   //// hData_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hData_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hData_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sbr_etaphi_1->Draw("COLZ");
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(48);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(48);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(1);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(1);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt->Draw();
   //// pt2->Draw();
   //// pt3->Draw();

   //// //gPad->SetTheta(60.839);
   //// //gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sbr_etaphi_1->Draw("COLZ");
   //// hData_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   //// hData_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   //// hData_sbr_etaphi_1->GetXaxis()->SetTitleSize(48);
   //// hData_sbr_etaphi_1->GetYaxis()->SetTitleSize(48);
   //// hData_sbr_etaphi_1->GetXaxis()->SetTitleOffset(1);
   //// hData_sbr_etaphi_1->GetYaxis()->SetTitleOffset(1);
   //// hData_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// //gPad->SetTheta(60.839);
   //// //gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_COLZ.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_etaphi_gen->Draw("lego20");
   //// hMC_etaphi_gen->GetYaxis()->SetTitle("Signal MC gen #Delta#phi_{Z,track}");
   //// hMC_etaphi_gen->GetXaxis()->SetTitle("Signal MC gen #Delta#eta_{Z,track}");
   //// hMC_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hMC_bkg_etaphi_gen->Draw("lego20");
   //// hMC_bkg_etaphi_gen->GetYaxis()->SetTitle("Backgrond MC gen #Delta#phi_{Z,track}");
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetTitle("Backgrond MC gen #Delta#eta_{Z,track}");
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_bkg_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_etaphi_gen->Draw("lego20");
   //// hMC_sb_etaphi_gen->GetYaxis()->SetTitle("Signal-Background MC gen #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_gen->GetXaxis()->SetTitle("Signal-Background MC gen #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_sb_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_sb_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hMC_sbr_etaphi_gen->Draw("lego20");
   //// hMC_sbr_etaphi_gen->GetYaxis()->SetTitle("Signal/Backgrond MC gen #Delta#phi_{Z,track}");
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetTitle("Signal/Backgrond MC gen #Delta#eta_{Z,track}");
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_sbr_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sbr_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_etaphi_gen->Draw("COLZ");
   //// hMC_etaphi_gen->GetYaxis()->SetTitle("Signal MC gen #Delta#phi_{Z,track}");
   //// hMC_etaphi_gen->GetXaxis()->SetTitle("Signal MC gen #Delta#eta_{Z,track}");
   //// hMC_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hMC_bkg_etaphi_gen->Draw("COLZ");
   //// hMC_bkg_etaphi_gen->GetYaxis()->SetTitle("Backgrond MC gen #Delta#phi_{Z,track}");
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetTitle("Backgrond MC gen #Delta#eta_{Z,track}");
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_bkg_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen_COLZ.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen_COLZ.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gen_COLZ.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_etaphi_gen->Draw("COLZ");
   //// hMC_sb_etaphi_gen->GetYaxis()->SetTitle("Signal-Background MC gen #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_gen->GetXaxis()->SetTitle("Signal-Background MC gen #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_sb_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_sb_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hMC_sbr_etaphi_gen->Draw("COLZ");
   //// hMC_sbr_etaphi_gen->GetYaxis()->SetTitle("Signal/Backgrond MC gen #Delta#phi_{Z,track}");
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetTitle("Signal/Backgrond MC gen #Delta#eta_{Z,track}");
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetTitleSize(30);
   //// hMC_sbr_etaphi_gen->GetYaxis()->SetTitleSize(30);
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sbr_etaphi_gen->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub_COLZ.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub_COLZ.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/gen/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_gensub_COLZ.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->SetCanvasSize(2000,800);
   //// c->Divide(3);
   //// c->cd(1);

   //// hMC_sb_etaphi_1->Draw("lego20");
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_etaphi_1->Draw("lego20");
   //// hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   //// hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   //// hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(3);
   //// hpp_etaphi_1->Draw("lego20");
   //// hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(3);
   //// c->cd(1);

   //// hMC_sb_etaphi_1->Draw("COLZ");
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_etaphi_1->Draw("COLZ");
   //// hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(3);
   //// hpp_etaphi_1->Draw("COLZ");
   //// hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(3);
   //// c->cd(1);

   //// hMC_sb_etaphi_1->Draw("lego20");
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hMC_sbr_etaphi_1->Draw("lego20");
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(3);
   //// hpp_etaphi_1->Draw("lego20");
   //// hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(3);
   //// c->cd(1);

   //// hMC_sb_etaphi_1->Draw("COLZ");
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hMC_sbr_etaphi_1->Draw("COLZ");
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_sbr_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(3);
   //// hpp_etaphi_1->Draw("COLZ");
   //// hpp_etaphi_1->GetYaxis()->SetTitle("pp MC #Delta#phi_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitle("pp MC #Delta#eta_{Z,track} (NPU=0)");
   //// hpp_etaphi_1->GetXaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetYaxis()->SetTitleSize(24);
   //// hpp_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   //// hpp_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   //// hpp_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hpp_etaphi_1->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/pp/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_pp_COLZ.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->SetCanvasSize(1400,800);

   //// c->Divide(2);
   //// c->cd(1);
   //// hMC_MuDetaphi->Draw("lego20");
   //// hMC_MuDetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{#mu,#mu}");
   //// hMC_MuDetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{#mu,#mu}");
   //// hMC_MuDetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_MuDetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_MuDetaphi->Draw("lego20");
   //// hData_MuDetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{#mu,#mu}");
   //// hData_MuDetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{#mu,#mu}");
   //// hData_MuDetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_MuDetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_bkg_MuDetaphi->Draw("lego20");
   //// hMC_bkg_MuDetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{#mu,#mu}");
   //// hMC_bkg_MuDetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{#mu,#mu}");
   //// hMC_bkg_MuDetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_MuDetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hMC_bkg_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_bkg_MuDetaphi->Draw("lego20");
   //// hData_bkg_MuDetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{#mu,#mu}");
   //// hData_bkg_MuDetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{#mu,#mu}");
   //// hData_bkg_MuDetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_bkg_MuDetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_bkg_MuDetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_bkg_MuDetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_bkg_MuDetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   //// hData_bkg_MuDetaphi->GetZaxis()->SetTitle("dN/d#Delta#etad#Delta#phi");

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/muD/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_muDetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

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

   //// /* Don't draw other axes yet 

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_maxetaphi->Draw("lego20");
   //// hMC_maxetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   //// hMC_maxetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   //// hMC_maxetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_maxetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_maxetaphi->Draw("lego20");
   //// hData_maxetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   //// hData_maxetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   //// hData_maxetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_maxetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_bkg_maxetaphi->Draw("lego20");
   //// hMC_bkg_maxetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   //// hMC_bkg_maxetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   //// hMC_bkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_bkg_maxetaphi->Draw("lego20");
   //// hData_bkg_maxetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   //// hData_bkg_maxetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   //// hData_bkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_bkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_bkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_bkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_bkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_maxetaphi->Draw("lego20");
   //// hMC_sb_maxetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_maxetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_maxetaphi->Draw("lego20");
   //// hData_sb_maxetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   //// hData_sb_maxetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   //// hData_sb_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sb_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sbr_maxetaphi->Draw("lego20");
   //// hMC_sbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sbr_maxetaphi->Draw("lego20");
   //// hData_sbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   //// hData_sbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   //// hData_sbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_maxOetaphi->Draw("lego20");
   //// hMC_maxOetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   //// hMC_maxOetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   //// hMC_maxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_maxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_maxOetaphi->Draw("lego20");
   //// hData_maxOetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   //// hData_maxOetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   //// hData_maxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_maxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_bkg_maxOetaphi->Draw("lego20");
   //// hMC_bkg_maxOetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   //// hMC_bkg_maxOetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   //// hMC_bkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_bkg_maxOetaphi->Draw("lego20");
   //// hData_bkg_maxOetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   //// hData_bkg_maxOetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   //// hData_bkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_bkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_bkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_bkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_bkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_maxOetaphi->Draw("lego20");
   //// hMC_sb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_maxOetaphi->Draw("lego20");
   //// hData_sb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   //// hData_sb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   //// hData_sb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sbr_maxOetaphi->Draw("lego20");
   //// hMC_sbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sbr_maxOetaphi->Draw("lego20");
   //// hData_sbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   //// hData_sbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   //// hData_sbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/maxOetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_maxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_WTAetaphi->Draw("lego20");
   //// hMC_WTAetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   //// hMC_WTAetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   //// hMC_WTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_WTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_WTAetaphi->Draw("lego20");
   //// hData_WTAetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   //// hData_WTAetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   //// hData_WTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_WTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_bkg_WTAetaphi->Draw("lego20");
   //// hMC_bkg_WTAetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   //// hMC_bkg_WTAetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   //// hMC_bkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_bkg_WTAetaphi->Draw("lego20");
   //// hData_bkg_WTAetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   //// hData_bkg_WTAetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   //// hData_bkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_bkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_bkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_bkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_bkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_WTAetaphi->Draw("lego20");
   //// hMC_sb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_WTAetaphi->Draw("lego20");
   //// hData_sb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   //// hData_sb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   //// hData_sb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sbr_WTAetaphi->Draw("lego20");
   //// hMC_sbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sbr_WTAetaphi->Draw("lego20");
   //// hData_sbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   //// hData_sbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   //// hData_sbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_WTAMoreetaphi->Draw("lego20");
   //// hMC_WTAMoreetaphi->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   //// hMC_WTAMoreetaphi->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   //// hMC_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_WTAMoreetaphi->Draw("lego20");
   //// hData_WTAMoreetaphi->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   //// hData_WTAMoreetaphi->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   //// hData_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_bkg_WTAMoreetaphi->Draw("lego20");
   //// hMC_bkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   //// hMC_bkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   //// hMC_bkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_bkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_bkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_bkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_bkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_bkg_WTAMoreetaphi->Draw("lego20");
   //// hData_bkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   //// hData_bkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   //// hData_bkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_bkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_bkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_bkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_bkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sb_WTAMoreetaphi->Draw("lego20");
   //// hMC_sb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   //// hMC_sb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   //// hMC_sb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sb_WTAMoreetaphi->Draw("lego20");
   //// hData_sb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   //// hData_sb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   //// hData_sb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_sbr_WTAMoreetaphi->Draw("lego20");
   //// hMC_sbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   //// hMC_sbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   //// hMC_sbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_sbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_sbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_sbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_sbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_sbr_WTAMoreetaphi->Draw("lego20");
   //// hData_sbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   //// hData_sbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   //// hData_sbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_sbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_sbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_sbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_sbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/WTAMoreetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_WTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zmaxetaphi->Draw("lego20");
   //// hMC_Zmaxetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   //// hMC_Zmaxetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   //// hMC_Zmaxetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_Zmaxetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_Zmaxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zmaxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zmaxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zmaxetaphi->Draw("lego20");
   //// hData_Zmaxetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   //// hData_Zmaxetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   //// hData_Zmaxetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_Zmaxetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_Zmaxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zmaxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zmaxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zbkg_maxetaphi->Draw("lego20");
   //// hMC_Zbkg_maxetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   //// hMC_Zbkg_maxetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   //// hMC_Zbkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_Zbkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_Zbkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zbkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zbkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zbkg_maxetaphi->Draw("lego20");
   //// hData_Zbkg_maxetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   //// hData_Zbkg_maxetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   //// hData_Zbkg_maxetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_Zbkg_maxetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_Zbkg_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zbkg_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zbkg_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsb_maxetaphi->Draw("lego20");
   //// hMC_Zsb_maxetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   //// hMC_Zsb_maxetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   //// hMC_Zsb_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsb_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsb_maxetaphi->Draw("lego20");
   //// hData_Zsb_maxetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   //// hData_Zsb_maxetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   //// hData_Zsb_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsb_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsb_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsb_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsb_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsbr_maxetaphi->Draw("lego20");
   //// hMC_Zsbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   //// hMC_Zsbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   //// hMC_Zsbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsbr_maxetaphi->Draw("lego20");
   //// hData_Zsbr_maxetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   //// hData_Zsbr_maxetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   //// hData_Zsbr_maxetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsbr_maxetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsbr_maxetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsbr_maxetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsbr_maxetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Zmaxetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_Zmaxetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_ZmaxOetaphi->Draw("lego20");
   //// hMC_ZmaxOetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   //// hMC_ZmaxOetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   //// hMC_ZmaxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_ZmaxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_ZmaxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_ZmaxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_ZmaxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_ZmaxOetaphi->Draw("lego20");
   //// hData_ZmaxOetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   //// hData_ZmaxOetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   //// hData_ZmaxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_ZmaxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_ZmaxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_ZmaxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_ZmaxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zbkg_maxOetaphi->Draw("lego20");
   //// hMC_Zbkg_maxOetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   //// hMC_Zbkg_maxOetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   //// hMC_Zbkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_Zbkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_Zbkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zbkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zbkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zbkg_maxOetaphi->Draw("lego20");
   //// hData_Zbkg_maxOetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   //// hData_Zbkg_maxOetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   //// hData_Zbkg_maxOetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_Zbkg_maxOetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_Zbkg_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zbkg_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zbkg_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsb_maxOetaphi->Draw("lego20");
   //// hMC_Zsb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   //// hMC_Zsb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   //// hMC_Zsb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsb_maxOetaphi->Draw("lego20");
   //// hData_Zsb_maxOetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   //// hData_Zsb_maxOetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   //// hData_Zsb_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsb_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsb_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsb_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsb_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsbr_maxOetaphi->Draw("lego20");
   //// hMC_Zsbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   //// hMC_Zsbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   //// hMC_Zsbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsbr_maxOetaphi->Draw("lego20");
   //// hData_Zsbr_maxOetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   //// hData_Zsbr_maxOetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   //// hData_Zsbr_maxOetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsbr_maxOetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsbr_maxOetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsbr_maxOetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsbr_maxOetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZmaxOetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZmaxOetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_ZWTAetaphi->Draw("lego20");
   //// hMC_ZWTAetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   //// hMC_ZWTAetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   //// hMC_ZWTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_ZWTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_ZWTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_ZWTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_ZWTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_ZWTAetaphi->Draw("lego20");
   //// hData_ZWTAetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   //// hData_ZWTAetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   //// hData_ZWTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_ZWTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_ZWTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_ZWTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_ZWTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zbkg_WTAetaphi->Draw("lego20");
   //// hMC_Zbkg_WTAetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   //// hMC_Zbkg_WTAetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   //// hMC_Zbkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_Zbkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_Zbkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zbkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zbkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zbkg_WTAetaphi->Draw("lego20");
   //// hData_Zbkg_WTAetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   //// hData_Zbkg_WTAetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   //// hData_Zbkg_WTAetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_Zbkg_WTAetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_Zbkg_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zbkg_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zbkg_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsb_WTAetaphi->Draw("lego20");
   //// hMC_Zsb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   //// hMC_Zsb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   //// hMC_Zsb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsb_WTAetaphi->Draw("lego20");
   //// hData_Zsb_WTAetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   //// hData_Zsb_WTAetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   //// hData_Zsb_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsb_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsb_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsb_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsb_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsbr_WTAetaphi->Draw("lego20");
   //// hMC_Zsbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   //// hMC_Zsbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   //// hMC_Zsbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsbr_WTAetaphi->Draw("lego20");
   //// hData_Zsbr_WTAetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   //// hData_Zsbr_WTAetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   //// hData_Zsbr_WTAetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsbr_WTAetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsbr_WTAetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsbr_WTAetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsbr_WTAetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_ZWTAMoreetaphi->Draw("lego20");
   //// hMC_ZWTAMoreetaphi->GetYaxis()->SetTitle("Signal MC #phi_{axis}");
   //// hMC_ZWTAMoreetaphi->GetXaxis()->SetTitle("Signal MC #eta_{axis}");
   //// hMC_ZWTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_ZWTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_ZWTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_ZWTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_ZWTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_ZWTAMoreetaphi->Draw("lego20");
   //// hData_ZWTAMoreetaphi->GetYaxis()->SetTitle("Signal Data #phi_{axis}");
   //// hData_ZWTAMoreetaphi->GetXaxis()->SetTitle("Signal Data #eta_{axis}");
   //// hData_ZWTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_ZWTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_ZWTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_ZWTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_ZWTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zbkg_WTAMoreetaphi->Draw("lego20");
   //// hMC_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background MC #phi_{axis}");
   //// hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background MC #eta_{axis}");
   //// hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hMC_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zbkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zbkg_WTAMoreetaphi->Draw("lego20");
   //// hData_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitle("Background Data #phi_{axis}");
   //// hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitle("Background Data #eta_{axis}");
   //// hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleSize(30);
   //// hData_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleSize(30);
   //// hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zbkg_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zbkg_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// ptNb->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsb_WTAMoreetaphi->Draw("lego20");
   //// hMC_Zsb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background MC #phi_{axis}");
   //// hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background MC #eta_{axis}");
   //// hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsb_WTAMoreetaphi->Draw("lego20");
   //// hData_Zsb_WTAMoreetaphi->GetYaxis()->SetTitle("Signal - Background Data #phi_{axis}");
   //// hData_Zsb_WTAMoreetaphi->GetXaxis()->SetTitle("Signal - Background Data #eta_{axis}");
   //// hData_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsb_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsb_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsb_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// c->Divide(2);
   //// c->cd(1);

   //// hMC_Zsbr_WTAMoreetaphi->Draw("lego20");
   //// hMC_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background MC #phi_{axis}");
   //// hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background MC #eta_{axis}");
   //// hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hMC_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hMC_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hMC_Zsbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// pt3d->Draw();
   //// pt3d2->Draw();
   //// pt3d3->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->cd(2);
   //// hData_Zsbr_WTAMoreetaphi->Draw("lego20");
   //// hData_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitle("Signal/Background Data #phi_{axis}");
   //// hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitle("Signal/Background Data #eta_{axis}");
   //// hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleSize(24);
   //// hData_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleSize(24);
   //// hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetTitleOffset(3.0);
   //// hData_Zsbr_WTAMoreetaphi->GetYaxis()->SetTitleOffset(2.5);
   //// hData_Zsbr_WTAMoreetaphi->GetXaxis()->SetNdivisions(50205,kFALSE);

   //// //ptN0->Draw();

   //// gPad->SetTheta(60.839);
   //// gPad->SetPhi(38.0172);

   //// c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/ZWTAMoreetaphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_ZWTAMoreetaphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //// c->Clear();

   //// */

   //// delete hMC_eta; hMC_eta=NULL;
   //// delete hData_eta; hData_eta=NULL;
   //// delete gROOT->FindObject("hMC_eta");
   //// delete gROOT->FindObject("hData_eta");

   //// delete hMC_bkg_eta; hMC_bkg_eta=NULL;
   //// delete hData_bkg_eta; hData_bkg_eta=NULL;
   //// delete gROOT->FindObject("hMC_bkg_eta");
   //// delete gROOT->FindObject("hData_bkg_eta");

   //// delete hMC_sb_eta; hMC_sb_eta=NULL;
   //// delete hData_sb_eta; hData_sb_eta=NULL;
   //// delete gROOT->FindObject("hMC_sb_eta");
   //// delete gROOT->FindObject("hData_sb_eta");

}

int main(int argc, char *argv[])
{
   SetCorrelationStyle();

   Files File;
   
   File.SignalData      = TFile::Open("GraphDataSignal_v9.root","read");
   File.SignalMC        = TFile::Open("GraphMCSignal_v9.root","read");
   File.BackgroundData  = TFile::Open("GraphDataBackground_v9.root","read");
   File.BackgroundMC    = TFile::Open("GraphMCBackground_v9.root","read");
   File.ppData          = nullptr;
   File.ppMC            = TFile::Open("GraphPPMC0Sub_v9.root","read");
   File.SignalMCGen     = TFile::Open("GraphMCSignalGen_v9.root","read");
   File.BackgroundMCGen = TFile::Open("GraphMCBackgroundGen_v9.root","read");

/*
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  0, 1000);
   ZtrackDraw_single(File, 40,  5, 2000,  0, 90,  0, 1000);

   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  1,    2);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  2,    5);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  5,   10);

   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  4,    5);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  5,    7);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  7,   10);

   //ZtrackDraw_single(File, 40, 20, 2000,  0, 30,  1,    2);
   //ZtrackDraw_single(File, 40, 20, 2000,  0, 30,  2,    5);
   //ZtrackDraw_single(File, 40, 20, 2000,  0, 30,  5,   10);
*/
   ZtrackDraw_single(File, 40, 20, 2000,  0, 30,  4,    5);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 30,  5,    7);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 30,  7,   10);


   /*
   ZtrackDraw_single(File, 40, 30,   40,  0, 90,  0, 1000);
   ZtrackDraw_single(File, 40, 40,   60,  0, 90,  0, 1000);
   ZtrackDraw_single(File, 40, 60,   80,  0, 90,  0, 1000);
   ZtrackDraw_single(File, 40, 80,  100,  0, 90,  0, 1000);*/
   ZtrackDraw_single(File, 40, 20, 2000,  0, 10,  0, 1000);
   ZtrackDraw_single(File, 40, 20, 2000, 10, 30,  0, 1000);
   ZtrackDraw_single(File, 40, 20, 2000, 30, 50,  0, 1000);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  1,    2);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  2,    5);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90,  5,   10);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90, 10,   20);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90, 20,   50);
   ZtrackDraw_single(File, 40, 20, 2000,  0, 90, 50,  100);
   /*
   ZtrackDraw_single(File, 40, 40, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90,  1,    2);
   ZtrackDraw_single(File, 40, 40, 2000, 50, 90,  1,    2);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90,  2,    5);
   ZtrackDraw_single(File, 40, 40, 2000, 50, 90,  2,    5);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90,  5,   10);
   ZtrackDraw_single(File, 40, 40, 2000, 50, 90,  5,   10);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90, 20,   50);
   ZtrackDraw_single(File, 40, 40, 2000, 50, 90, 20,   50);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90, 50,  100);
   ZtrackDraw_single(File, 40, 40, 2000, 50, 90, 50,  100);
   ZtrackDraw_single(File, 40, 30, 2000,  0, 30,  1, 1000);
   ZtrackDraw_single(File, 40, 30, 2000, 30, 50,  1, 1000);
   ZtrackDraw_single(File, 40, 30, 2000, 50, 90,  1, 1000);*/

/* 
   ZtrackDraw_single(File, 40,  5, 2000,  0, 90,  5,   10);
   ZtrackDraw_single(File, 40,  5, 2000,  0, 90, 10,   20);
   ZtrackDraw_single(File, 40,  5, 2000,  0, 90, 20,   50);
   ZtrackDraw_single(File, 40,  5, 2000,  0, 90, 50,  100);
*/

   ZtrackDraw_single(File, 40, 10, 2000,  0, 90,  2, 1000);

   //ZtrackDraw_single(File, 40, 20, 2000,  0, 10, 10,   20);

   ZtrackDraw_single(File, 40, 20, 2000,  0, 10, 10,   20);
   ZtrackDraw_single(File, 40, 20, 2000, 10, 30, 10,   20);
   ZtrackDraw_single(File, 40, 20, 2000, 30, 50, 10,   20);
   ZtrackDraw_single(File, 40, 20, 2000, 50, 90, 10,   20);

   return 0;

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

