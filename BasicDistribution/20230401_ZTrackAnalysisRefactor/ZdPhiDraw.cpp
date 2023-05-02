#include <TFile.h>
#include <TROOT.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TSystem.h>
#include <TLatex.h>
#include <iostream>

double TptL_min = 0.5;
const char *typeofdata = "20230503";

TFile *file_sigMC;
TFile *file_sigDA;

int main(int argc, char *argv[]);
void ZdPhiDraw_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

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


void ZdPhiDraw_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

  std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",1400,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   //std::cout<<"FolderName = "<<FolderName<<std::endl;

   TH1D* hData_phi = (TH1D*) file_sigDA->Get(Form("%s/HPhi", FolderName.c_str()));
   TH1D* hMC_phi = (TH1D*) file_sigMC->Get(Form("%s/HPhi", FolderName.c_str()));

   hData_phi->SetName("hData_phi");
   hMC_phi->SetName("hMC_phi");

   std::string FolderName1 = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",5.,20.,centL,centH,TptL,TptH);
   std::replace(FolderName1.begin(), FolderName1.end(), '.', 'p');

   //std::cout<<"FolderName1 = "<<FolderName1<<std::endl;

   TH1D* hData_phi1 = (TH1D*) file_sigDA->Get(Form("%s/HPhi", FolderName1.c_str()));
   TH1D* hMC_phi1 = (TH1D*) file_sigMC->Get(Form("%s/HPhi", FolderName1.c_str()));

   hData_phi1->SetName("hData_phi");
   hMC_phi1->SetName("hMC_phi");

   TNamed *nD_tN  = (TNamed *) file_sigDA->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nM_tN  = (TNamed *) file_sigMC->Get(Form("%s/EntryCount",FolderName.c_str()));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();

   float tD_tN  = std::stof(sD_tN);
   float tM_tN  = std::stof(sM_tN);

   hData_phi->Scale(1./tD_tN);
   hMC_phi->Scale(1./tM_tN);

   TNamed *nD_tN1  = (TNamed *) file_sigDA->Get(Form("%s/EntryCount",FolderName1.c_str()));
   TNamed *nM_tN1  = (TNamed *) file_sigMC->Get(Form("%s/EntryCount",FolderName1.c_str()));

   std::string sD_tN1  = (std::string) nD_tN1->GetTitle();
   std::string sM_tN1  = (std::string) nM_tN1->GetTitle();

   float tD_tN1  = std::stof(sD_tN1);
   float tM_tN1  = std::stof(sM_tN1);

   hData_phi1->Scale(1./tD_tN1);
   hMC_phi1->Scale(1./tM_tN1);

   TLatex *pt = new TLatex(0.18,0.88,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt->SetTextFont(42);
   pt->SetTextSize(0.035);
   pt->SetNDC(kTRUE);

   TLatex *pt3 = new TLatex(0.18,0.82,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   pt3->SetTextFont(42);
   pt3->SetTextSize(0.035);
   pt3->SetNDC(kTRUE);

   hData_phi->SetLineColor(kBlack);
   hMC_phi->SetLineColor(kBlack);
   hData_phi1->SetLineColor(kRed);
   hMC_phi1->SetLineColor(kRed);


  hData_phi->SetMarkerColor(kBlack);
   hMC_phi->SetMarkerColor(kBlack);
   hData_phi1->SetMarkerColor(kRed);
   hMC_phi1->SetMarkerColor(kRed);

   hData_phi->SetMarkerStyle(kFullCircle);
   hMC_phi->SetMarkerStyle(kFullCircle);
   hData_phi1->SetMarkerStyle(kFullCircle);
   hMC_phi1->SetMarkerStyle(kFullCircle);

   hData_phi->GetXaxis()->SetRangeUser(0,3.2);
   hMC_phi->GetXaxis()->SetRangeUser(0,3.2);
   hData_phi1->GetXaxis()->SetRangeUser(0,3.2);
   hMC_phi1->GetXaxis()->SetRangeUser(0,3.2);

   c->Divide(2);

   c->cd(1);

   double max1 = hMC_phi->GetMaximum();
   double max2 = hMC_phi1->GetMaximum();

   double min1 = hMC_phi->GetMinimum();
   double min2 = hMC_phi1->GetMinimum();
   
   if(max1<max2) hMC_phi1->Draw("ep");
   else hMC_phi->Draw("ep");

   hMC_phi->Draw("ep same");
   hMC_phi1->Draw("ep same");

   hMC_phi->SetXTitle("MC #Delta#phi_{Z,track}");
   hMC_phi1->SetXTitle("MC #Delta#phi_{Z,track}");

   if(max1<max2) max1=max2;
   if(min2<min1) min1=min2;

   hMC_phi->SetMaximum(1.4*max1); 
   hMC_phi1->SetMaximum(1.4*max1); 

   hMC_phi->SetMinimum(0.9*min1); 
   hMC_phi1->SetMinimum(0.9*min1); 

   TLegend leg1(0.5,0.72,0.98,0.9);
   leg1.AddEntry(hData_phi1 ,"5 < p^{Z}_{T} < 20 GeV","lep");
   leg1.AddEntry(hData_phi ,Form("%.0f < p^{Z}_{T} < %.0f GeV",ptL,ptH),"lep");
   leg1.SetFillColorAlpha(kWhite,0);
   leg1.SetLineColor(kBlack);
   leg1.SetLineWidth(1);
   //leg1.Draw();

   pt->Draw();
   pt3->Draw();

   c->cd(2);

   max1 = hData_phi->GetMaximum();
    max2 = hData_phi1->GetMaximum();

     min1 = hData_phi->GetMinimum();
  min2 = hData_phi1->GetMinimum();

    if(max1<max2) hData_phi1->Draw("ep");
   else hData_phi->Draw("ep");

   hData_phi->Draw("ep same");
   hData_phi1->Draw("ep same");

   hData_phi->SetXTitle("Data #Delta#phi_{Z,track}");
   hData_phi1->SetXTitle("Data #Delta#phi_{Z,track}");

   if(max1<max2) max1=max2;
   if(min2<min1) min1=min2;

   hData_phi->SetMaximum(1.4*max1); 
   hData_phi1->SetMaximum(1.4*max1); 

   hData_phi->SetMinimum(0.9*min1); 
   hData_phi1->SetMinimum(0.9*min1); 

   leg1.Draw();

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/comDphi",typeofdata));
   
   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/comDphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/comDphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   //c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/comDphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphicom.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

}

int main(int argc, char *argv[]){

   style();

   file_sigMC = TFile::Open("GraphMCSignal_0503.root","read");
   file_sigDA = TFile::Open("GraphDataSignal_0503.root","read");

   ZdPhiDraw_single(40, 60, 2000,  0, 90,0.5,    2);
   ZdPhiDraw_single(40,100, 2000,  0, 90,0.5,    2);
   ZdPhiDraw_single(40,120, 2000,  0, 90,0.5,    2);
   ZdPhiDraw_single(40, 60, 2000,  0, 90,  4, 1000);
   ZdPhiDraw_single(40,100, 2000,  0, 90,  4, 1000);
   ZdPhiDraw_single(40,120, 2000,  0, 90,  4, 1000);
   ZdPhiDraw_single(40, 60, 2000,  0, 30,0.5,    2);
   ZdPhiDraw_single(40,100, 2000,  0, 30,0.5,    2);
   ZdPhiDraw_single(40,120, 2000,  0, 30,0.5,    2);
   ZdPhiDraw_single(40, 60, 2000,  0, 30,  4, 1000);
   ZdPhiDraw_single(40,100, 2000,  0, 30,  4, 1000);
   ZdPhiDraw_single(40,120, 2000,  0, 30,  4, 1000);

   file_sigMC->Close();
   file_sigDA->Close();

   return 0;

}
