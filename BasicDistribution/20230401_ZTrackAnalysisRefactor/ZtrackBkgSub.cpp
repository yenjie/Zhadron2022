#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TLine.h>
#include <iostream>

double TptL_min = 0.5;

int main(int argc, char *argv[]);
void ZtrackDraw_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

void style(){

  gROOT->SetStyle("Plain");
  gStyle->SetPalette(1);
  gStyle->SetPadTickX(1);
  gStyle->SetPadTickY(1);
  gStyle->SetLabelFont(43,"xyz");
  gStyle->SetTitleFont(43);
  gStyle->SetTitleFont(43,"xyz");
  gStyle->SetStatFont(43);

  gStyle->SetFrameFillColor(kWhite);
  gStyle->SetCanvasColor(kWhite);
  gStyle->SetOptStat(0); /*don't show statistics box*/
  gStyle->SetOptTitle(0); /*don't show histogram titles*/
  gStyle->SetTitleSize(48, "xyz");
  gStyle->SetTitleOffset(1, "xyz");
  gStyle->SetLabelSize(36, "xyz");
  gStyle->SetLegendBorderSize(0);
  gStyle->SetLegendFillColor(kWhite);

  gStyle->SetPadTopMargin(0.05);
  gStyle->SetPadBottomMargin(0.15);
  gStyle->SetPadLeftMargin(0.15);
  gStyle->SetPadRightMargin(0.05);

  gStyle->SetLineScalePS(1.5);

  gROOT->ForceStyle();
}

TFile *file_sigMC;
TFile *file_bkgMC;
TFile *file_sigDA;
TFile *file_bkgDA;
TFile *file_ppMC;

TFile *file_sigMCgen;
TFile *file_bkgMCgen;

const char *typeofdata = "v17_PFMuon/20231120";
const char *typeofdata1 = "v17_PF_20231120";
const char *typeofdatatext = "single muon";

void ZtrackDraw_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",800,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH1D* hData_eta = (TH1D*) file_sigDA->Get(Form("%s/HEta", FolderName.c_str()));
   TH1D* hMC_eta = (TH1D*) file_sigMC->Get(Form("%s/HEta", FolderName.c_str()));
   TH1D* hpp_eta = (TH1D*) file_ppMC->Get(Form("%s/HEta", FolderName.c_str()));

   hData_eta->SetName("hData_eta");
   hMC_eta->SetName("hMC_eta");
   hpp_eta->SetName("hpp_eta");

   TH1D* hData_phi = (TH1D*) file_sigDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_phi = (TH1D*) file_sigMC->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hpp_phi = (TH1D*) file_ppMC->Get(Form("%s/HPhi", FolderName.c_str()));

   hData_phi->SetName("hData_phi");
   hMC_phi->SetName("hMC_phi");
   hpp_phi->SetName("hpp_phi");

   TH1D* hMC_phi_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_bkg_phi_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HPhi", FolderName.c_str()));

   hMC_phi_gen->SetName("hMC_phi");
   hMC_bkg_phi_gen->SetName("hMC_phi");

   TH1D* hData_bkg_eta = (TH1D*) file_bkgDA->Get(Form("%s/HEta", FolderName.c_str()));
   TH1D* hMC_bkg_eta = (TH1D*) file_bkgMC->Get(Form("%s/HEta", FolderName.c_str()));

   hData_bkg_eta->SetName("hData_bkg_eta");
   hMC_bkg_eta->SetName("hMC_bkg_eta");

   TH1D* hData_bkg_phi = (TH1D*) file_bkgDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_bkg_phi = (TH1D*) file_bkgMC->Get(Form("%s/HPhi", FolderName.c_str()));

   hData_bkg_phi->SetName("hData_bkg_phi");
   hMC_bkg_phi->SetName("hMC_bkg_phi");


   std::cout<<"Setting histograms..."<<std::endl;

   float hfL=0, hfH=0;

   if(centL==0) hfL=999999;
   else if (centL==10) hfL=3039.47;
   else if (centL==30) hfL=1342.21;
   else if (centL==50) hfL=484.422;
   else if (centL==90) hfL=24.7924;

   if(centH==0) hfH=999999;
   else if (centH==10) hfH=3039.47;
   else if (centH==30) hfH=1342.21;
   else if (centH==50) hfH=484.422;
   else if (centH==90) hfH=24.7924;

   std::cout<<"Getting Entries..."<<std::endl;

   TNamed *nD_tN  = (TNamed *) file_sigDA->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nM_tN  = (TNamed *) file_sigMC->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nDb_tN = (TNamed *) file_bkgDA->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nMb_tN = (TNamed *) file_bkgMC->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *npM_tN = (TNamed *) file_ppMC->Get(Form("%s/EntryCount",FolderName.c_str()));

   TNamed *nM_tNgen  = (TNamed *) file_sigMCgen->Get(Form("%s/GenEntryCount",FolderName.c_str()));
   TNamed *nMb_tNgen = (TNamed *) file_bkgMCgen->Get(Form("%s/GenEntryCount",FolderName.c_str()));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sDb_tN = (std::string) nDb_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();
   std::string spM_tN = (std::string) npM_tN->GetTitle();

   std::string sM_tNgen  = (std::string) nM_tNgen->GetTitle();
   std::string sMb_tNgen = (std::string) nMb_tNgen->GetTitle();

   float tD_tN  = std::stof(sD_tN);
   float tM_tN  = std::stof(sM_tN);
   float tDb_tN = std::stof(sDb_tN);
   float tMb_tN = std::stof(sMb_tN);
   float tpM_tN = std::stof(spM_tN);

   float tM_tNgen  = std::stof(sM_tNgen);
   float tMb_tNgen = std::stof(sMb_tNgen);

   std::cout<<"tD_tN = "<<tD_tN<<std::endl;
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tDb_tN = "<<tDb_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;

   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tMb_tNgen = "<<tMb_tNgen<<std::endl;

   double bineta = 0.032, binphi = M_PI/50;
   double bineta2d = 6.4/150, binphi2d = M_PI/75;

   hData_eta->Scale(1./tD_tN/bineta);
   hMC_eta->Scale(1./tM_tN/bineta);

   hData_phi->Scale(1./tD_tN/binphi);
   hMC_phi->Scale(1./tM_tN/binphi);

   hMC_phi_gen->Scale(1./tM_tNgen/binphi);

   hData_bkg_eta->Scale(1./tDb_tN/bineta);
   hMC_bkg_eta->Scale(1./tMb_tN/bineta);

   hData_bkg_phi->Scale(1./tDb_tN/binphi);
   hMC_bkg_phi->Scale(1./tMb_tN/binphi);

   hMC_bkg_phi_gen->Scale(1./tMb_tNgen/binphi);

   hpp_phi->Scale(1./tpM_tN/binphi);
   hpp_eta->Scale(1./tpM_tN/bineta);

   TH1D *hData_sb_eta = (TH1D*) hData_eta->Clone("hData_sb_eta");
   TH1D *hMC_sb_eta = (TH1D*) hMC_eta->Clone("hMC_sb_eta");
   TH1D *hData_sb_phi = (TH1D*) hData_phi->Clone("hData_sb_phi");
   TH1D *hMC_sb_phi = (TH1D*) hMC_phi->Clone("hMC_sb_phi");

   TH1D *hMC_sb_phi_gen = (TH1D*) hMC_phi_gen->Clone("hMC_sb_phi_gen");

   TH1D *hData_sbr_eta = (TH1D*) hData_eta->Clone("hData_sbr_eta");
   TH1D *hMC_sbr_eta = (TH1D*) hMC_eta->Clone("hMC_sbr_eta");
   TH1D *hData_sbr_phi = (TH1D*) hData_phi->Clone("hData_sbr_phi");
   TH1D *hMC_sbr_phi = (TH1D*) hMC_phi->Clone("hMC_sbr_phi");

   hData_sb_eta->Add(hData_bkg_eta,-1);
   hMC_sb_eta->Add(hMC_bkg_eta,-1);
   hData_sb_phi->Add(hData_bkg_phi,-1);
   hMC_sb_phi->Add(hMC_bkg_phi,-1);

   hMC_sb_phi_gen->Add(hMC_bkg_phi_gen,-1);

   hData_sbr_eta->Divide(hData_bkg_eta);
   hMC_sbr_eta->Divide(hMC_bkg_eta);
   hData_sbr_phi->Divide(hData_bkg_phi);
   hMC_sbr_phi->Divide(hMC_bkg_phi);

   int countD0 = hData_eta->GetEntries();
   std::cout<<"Data 0 = "<<countD0<<std::endl;
   int countM0 = hMC_eta->GetEntries();
   std::cout<<"MC 0 = "<<countM0<<std::endl;

   int countDb = hData_bkg_eta->GetEntries();
   std::cout<<"Data Bkg = "<<countDb<<std::endl;
   int countMb = hMC_bkg_eta->GetEntries();
   std::cout<<"MC Bkg = "<<countMb<<std::endl;

   std::cout<<"Drawing..."<<std::endl;

   hMC_eta->SetMarkerStyle(24);
   hMC_phi->SetMarkerStyle(24);
   hMC_bkg_eta->SetMarkerStyle(24);
   hMC_bkg_phi->SetMarkerStyle(24);
   hMC_sb_eta->SetMarkerStyle(24);
   hMC_sb_phi->SetMarkerStyle(24);
   hMC_sbr_eta->SetMarkerStyle(24);
   hMC_sbr_phi->SetMarkerStyle(24);

   hMC_sb_phi_gen->SetMarkerStyle(24);

   hData_eta->SetMarkerColor(kBlack);
   hMC_eta->SetMarkerColor(kRed);
   hData_phi->SetMarkerColor(kBlack);
   hMC_phi->SetMarkerColor(kRed);



   hData_eta->SetLineColor(kBlack);
   hMC_eta->SetLineColor(kRed);
   hData_phi->SetLineColor(kBlack);
   hMC_phi->SetLineColor(kRed);

   hData_bkg_eta->SetMarkerColor(kBlack);
   hMC_bkg_eta->SetMarkerColor(kRed);
   hData_bkg_phi->SetMarkerColor(kBlack);
   hMC_bkg_phi->SetMarkerColor(kRed);

   hData_bkg_eta->SetLineColor(kBlack);
   hMC_bkg_eta->SetLineColor(kRed);
   hData_bkg_phi->SetLineColor(kBlack);
   hMC_bkg_phi->SetLineColor(kRed);

   hData_sb_eta->SetMarkerColor(kBlack);
   hMC_sb_eta->SetMarkerColor(kRed);
   hData_sb_phi->SetMarkerColor(kBlack);
   hMC_sb_phi->SetMarkerColor(kRed);

   hData_sb_eta->SetLineColor(kBlack);
   hMC_sb_eta->SetLineColor(kRed);
   hData_sb_phi->SetLineColor(kBlack);
   hMC_sb_phi->SetLineColor(kRed);

   hData_sbr_eta->SetMarkerColor(kBlack);
   hMC_sbr_eta->SetMarkerColor(kRed);
   hData_sbr_phi->SetMarkerColor(kBlack);
   hMC_sbr_phi->SetMarkerColor(kRed);

   hData_sbr_eta->SetLineColor(kBlack);
   hMC_sbr_eta->SetLineColor(kRed);
   hData_sbr_phi->SetLineColor(kBlack);
   hMC_sbr_phi->SetLineColor(kRed);

   hMC_sb_phi_gen->SetLineColor(kGreen);

   if(TptL==0) TptL=TptL_min;

   TLegend leg(0.58,0.78,0.98,0.9);
   leg.AddEntry(hMC_eta ,"Monte Carlo: DYLL","lep");
   leg.AddEntry(hData_eta ,Form("Data: %s",typeofdatatext),"lep");
   leg.SetFillColorAlpha(kWhite,0);
   leg.SetLineColor(kBlack);
   leg.SetLineWidth(1);

   TLatex *pt = new TLatex(0.18,0.88,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt->SetTextFont(42);
   pt->SetTextSize(0.03);
   pt->SetNDC(kTRUE);

   TLatex *pt2 = new TLatex(0.18,0.82,Form("%.1f < Z p_{T} < %.1f GeV",ptL,ptH));
   pt2->SetTextFont(42);
   pt2->SetTextSize(0.03);
   pt2->SetNDC(kTRUE);

   TLatex *pt3 = new TLatex(0.18,0.76,Form("%.1f < Track p_{T} < %.1f GeV",TptL,TptH));
   pt3->SetTextFont(42);
   pt3->SetTextSize(0.03);
   pt3->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Dphi",typeofdata));


   TH1D *hMC_phi_com = (TH1D*) hMC_phi->Clone("hMC_phi_com");
   TH1D *hMC_bkg_phi_com = (TH1D*) hMC_bkg_phi->Clone("hMC_bkg_phi_com");
   TH1D *hMC_sb_phi_com = (TH1D*) hMC_sb_phi->Clone("hMC_sb_phi_com");
   TH1D *hpp_phi_com = (TH1D*) hpp_phi->Clone("hpp_phi_com");
/*
   TH1D *hMC_phi_com = new TH1D("hMC_phi_com","",20,0,M_PI);
   TH1D *hMC_bkg_phi_com = new TH1D("hMC_bkg_phi_com","",20,0,M_PI);
   TH1D *hMC_sb_phi_com = new TH1D("hMC_sb_phi_com","",20,0,M_PI);
   TH1D *hpp_phi_com = new TH1D("hpp_phi_com","",20,0,M_PI);

   for (int bin=1; bin<=hMC_phi->GetNbinsX(); bin++) {
     double x = hMC_phi->GetBinCenter(bin);
     double y = hMC_phi->GetBinContent(bin);
     //double err = hMC_phi->SetBinError(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hMC_phi_com->Fill(newX, y);
   }

   for (int bin=1; bin<=hMC_bkg_phi->GetNbinsX(); bin++) {
     double x = hMC_bkg_phi->GetBinCenter(bin);
     double y = hMC_bkg_phi->GetBinContent(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hMC_bkg_phi_com->Fill(newX, y);
   }

   for (int bin=1; bin<=hMC_sb_phi->GetNbinsX(); bin++) {
     double x = hMC_sb_phi->GetBinCenter(bin);
     double y = hMC_sb_phi->GetBinContent(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hMC_sb_phi_com->Fill(newX, y);
   }

   for (int bin=1; bin<=hpp_phi->GetNbinsX(); bin++) {
     double x = hpp_phi->GetBinCenter(bin);
     double y = hpp_phi->GetBinContent(bin);
     double newX = (x < 0) ? fabs(x) : ((x > M_PI) ? 2*M_PI - x : x); // apply the modifications
     hpp_phi_com->Fill(newX, y);
   }
*/

   
   hMC_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hMC_bkg_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hMC_sb_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hpp_phi_com->GetXaxis()->SetRangeUser(0,M_PI);
   hMC_sb_phi_gen->GetXaxis()->SetRangeUser(0,M_PI);


   double max1 = hMC_phi_com->GetMaximum();
   double max2 = hMC_bkg_phi_com->GetMaximum();

   hMC_phi_com->SetMarkerColor(kBlack);
   hMC_bkg_phi_com->SetMarkerColor(kBlue);
   hMC_sb_phi_com->SetMarkerColor(kRed);

   hMC_phi_com->SetLineColor(kBlack);
   hMC_bkg_phi_com->SetLineColor(kBlue);
   hMC_sb_phi_com->SetLineColor(kRed);
   hpp_phi_com->SetLineColor(kBlack);

   hMC_phi_com->SetMarkerStyle(kFullCircle);
   hMC_bkg_phi_com->SetMarkerStyle(kFullCircle);
   hMC_sb_phi_com->SetMarkerStyle(kFullCircle);

   hpp_phi_com->SetLineWidth(2);
   hMC_sb_phi_gen->SetLineWidth(2);

   
   if(max1<max2) hMC_bkg_phi_com->Draw("ep");
   else hMC_phi_com->Draw("ep");
   hMC_phi_com->Draw("ep same");
   hMC_bkg_phi_com->Draw("ep same");

   hMC_sb_phi_com->Draw("ep same");
   hpp_phi_com->Draw("hist same");
   hMC_sb_phi_gen->Draw("hist same");

   if(max1<max2) max1=max2;

   hMC_phi_com->SetXTitle("#Delta#phi_{Z,track}");
   hMC_bkg_phi_com->SetXTitle("#Delta#phi_{Z,track}");
   hMC_phi_com->SetYTitle("dN/d#Delta#phi");
   hMC_bkg_phi_com->SetYTitle("dN/d#Delta#phi");
   hMC_sb_phi_gen->SetYTitle("dN/d#Delta#phi");

   TLegend leg1(0.58,0.65,0.98,0.95);
   leg1.AddEntry(hMC_phi_com ,"raw","lep");
   leg1.AddEntry(hMC_bkg_phi_com ,"bkg","lep");
   leg1.AddEntry(hMC_sb_phi_com ,"raw-bkg","lep");
   leg1.AddEntry(hpp_phi_com ,"pp","l");
   leg1.AddEntry(hMC_sb_phi_gen,"raw-bkg GEN","lep");
   leg1.SetFillColorAlpha(kWhite,0);
   leg1.SetLineColor(kBlack);
   leg1.SetLineWidth(1);
   leg1.Draw();

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   //std::cout<<"max1 = "<<max1<<std::endl;
   //hMC_phi_com->SetMinimum(0);
   hMC_phi_com->SetMaximum(max1);
   //hMC_bkg_phi_com->SetMinimum(0);
   hMC_bkg_phi_com->SetMaximum(max1);
/*
   if(ptL==30&&centL==0&&centH==30){
    hMC_phi_com->SetMaximum(max1);
    hMC_bkg_phi_com->SetMaximum(max1);
   }else if(ptL==30&&centL==30&&centH==50){
    hMC_phi_com->SetMaximum(max1/1.6);
    hMC_bkg_phi_com->SetMaximum(max1/1.6);
   }
*/
   //hMC_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hMC_bkg_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hMC_sb_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);
   //hpp_phi_com->GetYaxis()->SetRangeUser(0,max1/1.6);

   //ptN0->Draw();

   hMC_phi_com->SetMinimum(0);
   hMC_bkg_phi_com->SetMinimum(0);
   hMC_sb_phi_com->SetMinimum(0);
   hpp_phi_com->SetMinimum(0);
   hMC_sb_phi_gen->SetMinimum(0);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogy();
   hMC_phi_com->SetMinimum(0.01);
   hMC_bkg_phi_com->SetMinimum(0.01);
   hMC_sb_phi_com->SetMinimum(0.01);
   hpp_phi_com->SetMinimum(0.01);
   hMC_sb_phi_gen->SetMinimum(0.01);
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/Ztrack_%s_comlog_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicomlog.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   gPad->SetLogy(0);
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/pdf/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.pdf",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Dphi/C/Ztrack_%s_com_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.C",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();



}

int main(int argc, char *argv[]){

   style();

   file_sigMC = TFile::Open("~/eos_base/BasicPlots/GraphMCSignal_v17_PFmuon.root","read");
   file_bkgMC = TFile::Open("~/eos_base/BasicPlots/GraphMCBackground_v17_PFmuon.root","read");
   file_sigDA = TFile::Open("~/eos_base/BasicPlots/GraphDataSignal_v17_PFmuon.root","read");
   file_bkgDA = TFile::Open("~/eos_base/BasicPlots/GraphDataBackground_v17_PFmuon.root","read");
   file_ppMC  = TFile::Open("~/eos_base/BasicPlots/GraphPPMC0Sub_v17_PFmuon.root","read");

   file_sigMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCSignalGen_v17_PFmuon.root","read");
   file_bkgMCgen = TFile::Open("~/eos_base/BasicPlots/GraphMCBackgroundGen_v17_PFmuon.root","read");

/*
   ZtrackDraw_single(40, 20, 2000,  0, 10,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 10, 30,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 30, 50,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(40, 20, 2000,  0, 90,  1,    2);
   ZtrackDraw_single(40, 20, 2000,  0, 90,  2,    5);
   ZtrackDraw_single(40, 20, 2000,  0, 90,  5,   10);
   ZtrackDraw_single(40, 20, 2000,  0, 90, 10,   20);
   ZtrackDraw_single(40, 20, 2000,  0, 90, 20,   50);
   ZtrackDraw_single(40, 20, 2000,  0, 90, 50,  100);
*/
   ZtrackDraw_single(40, 40, 200,  0, 10,  1, 1000);
   ZtrackDraw_single(40, 40, 200, 10, 30,  1, 1000);
   ZtrackDraw_single(40, 40, 200, 30, 50,  1, 1000);
   ZtrackDraw_single(40, 40, 200, 50, 90,  1, 1000);
/*
   ZtrackDraw_single(40, 20, 2000,  0, 10, 10,   20);
   ZtrackDraw_single(40, 20, 2000, 10, 30, 10,   20);
   ZtrackDraw_single(40, 20, 2000, 30, 50, 10,   20);
   ZtrackDraw_single(40, 20, 2000, 50, 90, 10,   20);
*/
   //ZtrackDraw_single(40, 40, 200,  0, 30, 1, 1000);
   //ZtrackDraw_single(40, 40, 200,  0, 10, 1, 1000);
   //ZtrackDraw_single(40, 40, 200, 10, 30, 1, 1000);
   //ZtrackDraw_single(40, 40, 200, 30, 50, 1, 1000);
   //ZtrackDraw_single(40, 40, 200, 50, 90, 1, 1000);

   file_sigMC->Close();
   file_bkgMC->Close();
   file_sigDA->Close();
   file_bkgDA->Close();
   file_ppMC->Close();

   file_sigMCgen->Close();
   file_bkgMCgen->Close();

   return 0;

}
