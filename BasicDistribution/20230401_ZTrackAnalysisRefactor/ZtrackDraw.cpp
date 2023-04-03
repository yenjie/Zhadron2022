#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>
#include <TH2D.h>
#include <TCut.h>
#include <TStyle.h>
#include <TCanvas.h>
#include <TLegend.h>
#include <TAxis.h>
#include <TSystem.h>
#include <TLatex.h>
#include <TChain.h>
#include <TLine.h>

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

const char *typeofdata = "20230402";
const char *typeofdatatext = "double muon";

Double_t bwfun(Double_t *x, Double_t *par) {

   //Fit parameters:
   
   //par[0]=mean
   //par[1]=width
   //par[2]=area
   
   //par[3]=width of the convoluted Gaussian function
   
   //par[0]=Width (scale) parameter of Landau density
   //par[1]=Most Probable (MP, location) parameter of Landau density
   //par[2]=Total area (integral -inf to inf, normalization constant)
   //par[3]=Width (sigma) of convoluted Gaussian function
   //
   //In the Landau distribution (represented by the CERNLIB approximation),
   //the maximum is located at x=-0.22278298 with the location parameter=0.
   //This shift is corrected within this function, so that the actual
   //maximum is identical to the MP parameter.

      // Numeric constants
      Double_t invsq2pi = 0.3989422804014;   // (2 pi)^(-1/2)
      Double_t mpshift  = -0.22278298;       // Landau maximum location

      // Control constants
      Double_t np = 1000.0;      // number of convolution steps
      Double_t sc =   5.0;      // convolution extends to +-sc Gaussian sigmas

      // Variables
      Double_t xx;
      Double_t mpc;
      Double_t fland;
      Double_t sum = 0.0;
      Double_t xlow,xupp;
      Double_t step;
      Double_t i;

      // Range of convolution integral
      xlow = x[0] - sc * par[3];
      xupp = x[0] + sc * par[3];

      step = (xupp-xlow) / np;

      // Convolution integral of Landau and Gaussian by sum
      for(i=1.0; i<=np/2; i++) {
         xx = xlow + (i-.5) * step;
         fland = TMath::BreitWigner(xx,par[0], par[1]);
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
//         sum += fland * ROOT::Math::crystalball_function(x[0], par[3], par[4], 1, xx);
         xx = xupp - (i-.5) * step;
         fland = TMath::BreitWigner(xx,par[0], par[1]);
         sum += fland * TMath::Gaus(x[0],xx,par[3]);
//         sum += fland * ROOT::Math::crystalball_function(x[0], par[3], par[4], 1, xx);
      }

      return (par[2] * step * sum * invsq2pi +par[4]*exp(par[6]+par[5]*x[0]));
 //     return (par[2] * step * sum * invsq2pi / par[3]+par[4]+par[5]*x[0]+par[6]*x[0]*x[0]+par[7]*x[0]*x[0]*x[0]);
}

void ZtrackDraw_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",800,800);

   std::cout<<"Getting histograms..."<<std::endl;

   TH1D* hData_eta = (TH1D*) file_sigDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEta",ptL,ptH,centL,centH,TptL,TptH));
   TH1D* hMC_eta = (TH1D*) file_sigMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEta",ptL,ptH,centL,centH,TptL,TptH));

   hData_eta->SetName("hData_eta");
   hMC_eta->SetName("hMC_eta");

   TH1D* hData_phi = (TH1D*) file_sigDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HPhi",ptL,ptH,centL,centH,TptL,TptH));
   TH1D* hMC_phi = (TH1D*) file_sigMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HPhi",ptL,ptH,centL,centH,TptL,TptH));

   hData_phi->SetName("hData_phi");
   hMC_phi->SetName("hMC_phi");

   TH2D* hData_etaphi_1 = (TH2D*) file_sigDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEtaPhi",ptL,ptH,centL,centH,TptL,TptH));
   TH2D* hMC_etaphi_1 = (TH2D*) file_sigMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEtaPhi",ptL,ptH,centL,centH,TptL,TptH));

   hData_etaphi_1->SetName("hData_etaphi_1");
   hMC_etaphi_1->SetName("hMC_etaphi_1");

   TH1D* hData_bkg_eta = (TH1D*) file_bkgDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEta",ptL,ptH,centL,centH,TptL,TptH));
   TH1D* hMC_bkg_eta = (TH1D*) file_bkgMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEta",ptL,ptH,centL,centH,TptL,TptH));

   hData_bkg_eta->SetName("hData_bkg_eta");
   hMC_bkg_eta->SetName("hMC_bkg_eta");

   TH1D* hData_bkg_phi = (TH1D*) file_bkgDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HPhi",ptL,ptH,centL,centH,TptL,TptH));
   TH1D* hMC_bkg_phi = (TH1D*) file_bkgMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HPhi",ptL,ptH,centL,centH,TptL,TptH));

   hData_bkg_phi->SetName("hData_bkg_phi");
   hMC_bkg_phi->SetName("hMC_bkg_phi");

   TH2D* hData_bkg_etaphi_1 = (TH2D*) file_bkgDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEtaPhi",ptL,ptH,centL,centH,TptL,TptH));
   TH2D* hMC_bkg_etaphi_1 = (TH2D*) file_bkgMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/HEtaPhi",ptL,ptH,centL,centH,TptL,TptH));

   hData_bkg_etaphi_1->SetName("hData_bkg_etaphi_1");
   hMC_bkg_etaphi_1->SetName("hMC_bkg_etaphi_1");

   std::cout<<"Rebinning..."<<std::endl;

   hData_etaphi_1->Rebin2D(10,10);
   hData_bkg_etaphi_1->Rebin2D(10,10);

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

   hData_eta->Sumw2();
   hMC_eta->Sumw2();
   hData_phi->Sumw2();
   hMC_phi->Sumw2();

   hData_bkg_eta->Sumw2();
   hMC_bkg_eta->Sumw2();
   hData_bkg_phi->Sumw2();
   hMC_bkg_phi->Sumw2();

   std::cout<<"Getting Entries..."<<std::endl;

   TNamed *nD_tN  = (TNamed *) file_sigDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/EntryCount",ptL,ptH,centL,centH,TptL,TptH));
   TNamed *nM_tN  = (TNamed *) file_sigMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/EntryCount",ptL,ptH,centL,centH,TptL,TptH));
   TNamed *nDb_tN = (TNamed *) file_bkgDA->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/EntryCount",ptL,ptH,centL,centH,TptL,TptH));
   TNamed *nMb_tN = (TNamed *) file_bkgMC->Get(Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.0f_%.0f/EntryCount",ptL,ptH,centL,centH,TptL,TptH));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sDb_tN = (std::string) nDb_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();

   int tD_tN  = std::stoi(sD_tN);
   int tM_tN  = std::stoi(sM_tN);
   int tDb_tN = std::stoi(sDb_tN);
   int tMb_tN = std::stoi(sMb_tN);

   std::cout<<"tD_tN = "<<tD_tN<<std::endl;
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tDb_tN = "<<tDb_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;

   hData_eta->Scale(1./tD_tN);
   hMC_eta->Scale(1./tM_tN);

   hData_phi->Scale(1./tD_tN);
   hMC_phi->Scale(1./tM_tN);

   hData_bkg_eta->Scale(1./tDb_tN);
   hMC_bkg_eta->Scale(1./tMb_tN);

   hData_bkg_phi->Scale(1./tDb_tN);
   hMC_bkg_phi->Scale(1./tMb_tN);

   hData_etaphi_1->Scale(1./tD_tN);
   hMC_etaphi_1->Scale(1./tM_tN);

   hData_bkg_etaphi_1->Scale(1./tDb_tN);
   hMC_bkg_etaphi_1->Scale(1./tMb_tN);

   TH1D *hData_sb_eta = (TH1D*) hData_eta->Clone("hData_sb_eta");
   TH1D *hMC_sb_eta = (TH1D*) hMC_eta->Clone("hMC_sb_eta");
   TH1D *hData_sb_phi = (TH1D*) hData_phi->Clone("hData_sb_phi");
   TH1D *hMC_sb_phi = (TH1D*) hMC_phi->Clone("hMC_sb_phi");
   TH2D *hMC_sb_etaphi_1 = (TH2D*) hMC_etaphi_1->Clone("hMC_sb_etaphi_1");
   TH2D *hData_sb_etaphi_1 = (TH2D*) hData_etaphi_1->Clone("hData_sb_etaphi_1");

   TH1D *hData_sbr_eta = (TH1D*) hData_eta->Clone("hData_sbr_eta");
   TH1D *hMC_sbr_eta = (TH1D*) hMC_eta->Clone("hMC_sbr_eta");
   TH1D *hData_sbr_phi = (TH1D*) hData_phi->Clone("hData_sbr_phi");
   TH1D *hMC_sbr_phi = (TH1D*) hMC_phi->Clone("hMC_sbr_phi");
   TH2D *hMC_sbr_etaphi_1 = (TH2D*) hMC_etaphi_1->Clone("hMC_sbr_etaphi_1");
   TH2D *hData_sbr_etaphi_1 = (TH2D*) hData_etaphi_1->Clone("hData_sbr_etaphi_1");

   hData_sb_eta->Add(hData_bkg_eta,-1);
   hMC_sb_eta->Add(hMC_bkg_eta,-1);
   hData_sb_phi->Add(hData_bkg_phi,-1);
   hMC_sb_phi->Add(hMC_bkg_phi,-1);
   hMC_sb_etaphi_1->Add(hMC_bkg_etaphi_1,-1);
   hData_sb_etaphi_1->Add(hData_bkg_etaphi_1,-1);

   hData_sbr_eta->Divide(hData_bkg_eta);
   hMC_sbr_eta->Divide(hMC_bkg_eta);
   hData_sbr_phi->Divide(hData_bkg_phi);
   hMC_sbr_phi->Divide(hMC_bkg_phi);
   hMC_sbr_etaphi_1->Divide(hMC_bkg_etaphi_1);
   hData_sbr_etaphi_1->Divide(hData_bkg_etaphi_1);

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

   TLatex *pt2 = new TLatex(0.18,0.82,Form("%.1f < Z p_{T} < %.1f",ptL,ptH));
   pt2->SetTextFont(42);
   pt2->SetTextSize(0.03);
   pt2->SetNDC(kTRUE);

   TLatex *pt3 = new TLatex(0.18,0.76,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   pt3->SetTextFont(42);
   pt3->SetTextSize(0.03);
   pt3->SetNDC(kTRUE);

   TLatex *pt3d = new TLatex(0.03,0.94,Form("%.0f %%< Centrality < %.0f %%",centL,centH));
   pt3d->SetTextFont(42);
   pt3d->SetTextSize(0.03);
   pt3d->SetNDC(kTRUE);

   TLatex *pt3d2 = new TLatex(0.03,0.88,Form("%.1f < Z p_{T} < %.1f",ptL,ptH));
   pt3d2->SetTextFont(42);
   pt3d2->SetTextSize(0.03);
   pt3d2->SetNDC(kTRUE);

   TLatex *pt3d3 = new TLatex(0.03,0.82,Form("%.1f < Track p_{T} < %.1f",TptL,TptH));
   pt3d3->SetTextFont(42);
   pt3d3->SetTextSize(0.03);
   pt3d3->SetNDC(kTRUE);


   TLatex *ptN0 = new TLatex(0.1,0.97,Form("Signal N_{MC} = %d, N_{Data} = %d",countM0,countD0));
   ptN0->SetTextFont(42);
   ptN0->SetTextSize(0.03);
   ptN0->SetNDC(kTRUE);

   TLatex *ptNb = new TLatex(0.1,0.97,Form("Background N_{MC} = %d, N_{Data} = %d",countMb,countDb));
   ptNb->SetTextFont(42);
   ptNb->SetTextSize(0.03);
   ptNb->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p figs/track/%s",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Deta",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Dphi",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/3D",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Deta/pdf",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Dphi/pdf",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/3D/pdf",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Deta/C",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Dphi/C",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/3D/C",typeofdata));

   // Draw eta 

   double max1 = hMC_eta->GetMaximum();
   double max2 = hData_eta->GetMaximum();
   
   if(max1<max2) hData_eta->Draw();
   else hMC_eta->Draw();
   hMC_eta->Draw("same");
   hData_eta->Draw("same");

   hMC_eta->SetXTitle("Signal |#Delta#eta_{Z,track}|");
   hData_eta->SetXTitle("Signal |#Delta#eta_{Z,track}|");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_eta->SetMinimum(0);
   hMC_eta->SetMaximum(3.0/binnum); 
   hData_eta->SetMinimum(0);
   hData_eta->SetMaximum(3.0/binnum); 

   ptN0->Draw();

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_bkg_eta->GetMaximum();
   max2 = hData_bkg_eta->GetMaximum();
   
   if(max1<max2) hData_bkg_eta->Draw();
   else hMC_bkg_eta->Draw();
   hMC_bkg_eta->Draw("same");
   hData_bkg_eta->Draw("same");

   hMC_bkg_eta->SetXTitle("Background |#Delta#eta_{Z,track}|");
   hData_bkg_eta->SetXTitle("Background |#Delta#eta_{Z,track}|");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_bkg_eta->SetMinimum(0);
   hMC_bkg_eta->SetMaximum(3.0/binnum); 
   hData_bkg_eta->SetMinimum(0);
   hData_bkg_eta->SetMaximum(3.0/binnum); 

   ptNb->Draw();

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sb_eta->GetMaximum();
   max2 = hData_sb_eta->GetMaximum();

   double min1 = hMC_sb_phi->GetMinimum();
   double min2 = hData_sb_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sb_eta->Draw();
   else hMC_sb_eta->Draw();
   hMC_sb_eta->Draw("same");
   hData_sb_eta->Draw("same");

   hMC_sb_eta->SetXTitle("Signal - Background |#Delta#eta_{Z,track}|");
   hData_sb_eta->SetXTitle("Signal - Background |#Delta#eta_{Z,track}|");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sb_eta->SetMinimum(min1);
   hMC_sb_eta->SetMaximum(3.0/binnum); 
   hData_sb_eta->SetMinimum(min1);
   hData_sb_eta->SetMaximum(3.0/binnum); 

   //ptN0->Draw();

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sbr_eta->GetMaximum();
   max2 = hData_sbr_eta->GetMaximum();

   min1 = hMC_sbr_phi->GetMinimum();
   min2 = hData_sbr_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sbr_eta->Draw();
   else hMC_sbr_eta->Draw();
   hMC_sbr_eta->Draw("same");
   hData_sbr_eta->Draw("same");

   hMC_sbr_eta->SetXTitle("Signal/Background |#Delta#eta_{Z,track}|");
   hData_sbr_eta->SetXTitle("Signal/Background |#Delta#eta_{Z,track}|");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sbr_eta->SetMinimum(min1);
   hMC_sbr_eta->SetMaximum(3.0/binnum); 
   hData_sbr_eta->SetMinimum(min1);
   hData_sbr_eta->SetMaximum(3.0/binnum); 

   //ptN0->Draw();

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Deta/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_phi->GetMaximum();
   max2 = hData_phi->GetMaximum();
   
   if(max1<max2) hData_phi->Draw();
   else hMC_phi->Draw();
   hMC_phi->Draw("same");
   hData_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_phi->SetXTitle("Signal #Delta#phi_{Z,track}");
   hData_phi->SetXTitle("Signal #Delta#phi_{Z,track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_phi->SetMinimum(0);
   hMC_phi->SetMaximum(1.6*max1);
   hData_phi->SetMinimum(0);
   hData_phi->SetMaximum(1.6*max1);

   ptN0->Draw();

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_bkg_phi->GetMaximum();
   max2 = hData_bkg_phi->GetMaximum();
   
   if(max1<max2) hData_bkg_phi->Draw();
   else hMC_bkg_phi->Draw();
   hMC_bkg_phi->Draw("same");
   hData_bkg_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_bkg_phi->SetXTitle("Background #Delta#phi_{Z,track}");
   hData_bkg_phi->SetXTitle("Background #Delta#phi_{Z,track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_bkg_phi->SetMinimum(0);
   hMC_bkg_phi->SetMaximum(1.6*max1);
   hData_bkg_phi->SetMinimum(0);
   hData_bkg_phi->SetMaximum(1.6*max1);

   ptNb->Draw();

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sb_phi->GetMaximum();
   max2 = hData_sb_phi->GetMaximum();

   min1 = hMC_sb_phi->GetMinimum();
   min2 = hData_sb_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sb_phi->Draw();
   else hMC_sb_phi->Draw();
   hMC_sb_phi->Draw("same");
   hData_sb_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_sb_phi->SetXTitle("Signal - Background #Delta#phi_{Z,track}");
   hData_sb_phi->SetXTitle("Signal - Background #Delta#phi_{Z,track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sb_phi->SetMinimum(min1);
   hMC_sb_phi->SetMaximum(1.6*max1);
   hData_sb_phi->SetMinimum(min1);
   hData_sb_phi->SetMaximum(1.6*max1);

   //ptN0->Draw();

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   max1 = hMC_sbr_phi->GetMaximum();
   max2 = hData_sbr_phi->GetMaximum();

   min1 = hMC_sbr_phi->GetMinimum();
   min2 = hData_sbr_phi->GetMinimum();
   if(min2<min1) min1=min2;
   
   if(max1<max2) hData_sbr_phi->Draw();
   else hMC_sbr_phi->Draw();
   hMC_sbr_phi->Draw("same");
   hData_sbr_phi->Draw("same");

   if(max1<max2) max1=max2;

   hMC_sbr_phi->SetXTitle("Signal/Background #Delta#phi_{Z,track}");
   hData_sbr_phi->SetXTitle("Signal/Background #Delta#phi_{Z,track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();
   hMC_sbr_phi->SetMinimum(min1);
   hMC_sbr_phi->SetMaximum(1.6*max1);
   hData_sbr_phi->SetMinimum(min1);
   hData_sbr_phi->SetMaximum(1.6*max1);

   //ptN0->Draw();

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/Dphi/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->SetCanvasSize(1400,800);
   c->Divide(2);
   c->cd(1);

   hMC_etaphi_1->Draw("lego20");
   hMC_etaphi_1->GetYaxis()->SetTitle("Signal MC #Delta#phi_{Z,track}");
   hMC_etaphi_1->GetXaxis()->SetTitle("Signal MC #Delta#eta_{Z,track}");
   hMC_etaphi_1->GetXaxis()->SetTitleSize(30);
   hMC_etaphi_1->GetYaxis()->SetTitleSize(30);
   hMC_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_etaphi_1->Draw("lego20");
   hData_etaphi_1->GetYaxis()->SetTitle("Signal Data #Delta#phi_{Z,track}");
   hData_etaphi_1->GetXaxis()->SetTitle("Signal Data #Delta#eta_{Z,track}");
   hData_etaphi_1->GetXaxis()->SetTitleSize(30);
   hData_etaphi_1->GetYaxis()->SetTitleSize(30);
   hData_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/pdf/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/C/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_etaphi_1->Draw("lego20");
   hMC_bkg_etaphi_1->GetYaxis()->SetTitle("Background MC #Delta#phi_{Z,track}");
   hMC_bkg_etaphi_1->GetXaxis()->SetTitle("Background MC #Delta#eta_{Z,track}");
   hMC_bkg_etaphi_1->GetXaxis()->SetTitleSize(30);
   hMC_bkg_etaphi_1->GetYaxis()->SetTitleSize(30);
   hMC_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_bkg_etaphi_1->Draw("lego20");
   hData_bkg_etaphi_1->GetYaxis()->SetTitle("Background Data #Delta#phi_{Z,track}");
   hData_bkg_etaphi_1->GetXaxis()->SetTitle("Background Data #Delta#eta_{Z,track}");
   hData_bkg_etaphi_1->GetXaxis()->SetTitleSize(30);
   hData_bkg_etaphi_1->GetYaxis()->SetTitleSize(30);
   hData_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   ptNb->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/pdf/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/C/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background MC #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background MC #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sb_etaphi_1->Draw("lego20");
   hData_sb_etaphi_1->GetYaxis()->SetTitle("Signal - Background Data #Delta#phi_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitle("Signal - Background Data #Delta#eta_{Z,track}");
   hData_sb_etaphi_1->GetXaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetYaxis()->SetTitleSize(24);
   hData_sb_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_sb_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_sb_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/pdf/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/C/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_etaphi_1->Draw("lego20");
   hMC_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background MC #Delta#phi_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background MC #Delta#eta_{Z,track}");
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hData_sbr_etaphi_1->Draw("lego20");
   hData_sbr_etaphi_1->GetYaxis()->SetTitle("Signal/Background Data #Delta#phi_{Z,track}");
   hData_sbr_etaphi_1->GetXaxis()->SetTitle("Signal/Background Data #Delta#eta_{Z,track}");
   hData_sbr_etaphi_1->GetXaxis()->SetTitleSize(24);
   hData_sbr_etaphi_1->GetYaxis()->SetTitleSize(24);
   hData_sbr_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hData_sbr_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hData_sbr_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   //ptN0->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/pdf/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.pdf",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->SaveAs(Form("figs/track/%s/3D/C/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.C",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

}

int main(int argc, char *argv[]){

   style();

   file_sigMC = TFile::Open("GraphMCSignal.root","read");
   file_bkgMC = TFile::Open("GraphMCBackground.root","read");
   file_sigDA = TFile::Open("GraphDataSignal.root","read");
   file_bkgDA = TFile::Open("GraphDataBackground.root","read");

   ZtrackDraw_single(40,  0, 2000,  0, 90,  0, 1000);
   ZtrackDraw_single(40, 30,   40,  0, 90,  0, 1000);
   ZtrackDraw_single(40, 40,   60,  0, 90,  0, 1000);
   ZtrackDraw_single(40, 60,   80,  0, 90,  0, 1000);
   ZtrackDraw_single(40, 80,  100,  0, 90,  0, 1000);
   ZtrackDraw_single(40,  0, 2000,  0, 10,  0, 1000);
   ZtrackDraw_single(40,  0, 2000, 10, 30,  0, 1000);
   ZtrackDraw_single(40,  0, 2000, 30, 50,  0, 1000);
   ZtrackDraw_single(40,  0, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(40,  0, 2000,  0, 90,  2,    5);
   ZtrackDraw_single(40,  0, 2000,  0, 90,  5,   10);
   ZtrackDraw_single(40,  0, 2000,  0, 90, 10,   20);
   ZtrackDraw_single(40,  0, 2000,  0, 90, 20,   50);
   ZtrackDraw_single(40,  0, 2000,  0, 90, 50,  100);
   ZtrackDraw_single(40, 20, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(40, 40, 2000, 50, 90,  0, 1000);
   ZtrackDraw_single(40, 20, 2000, 50, 90,  5,   10);
   ZtrackDraw_single(40, 40, 2000, 50, 90,  5,   10);
   ZtrackDraw_single(40, 20, 2000, 50, 90, 20,   50);
   ZtrackDraw_single(40, 40, 2000, 50, 90, 20,   50);
   ZtrackDraw_single(40, 20, 2000, 50, 90, 50,  100);
   ZtrackDraw_single(40, 40, 2000, 50, 90, 50,  100);

   file_sigMC->Close();
   file_bkgMC->Close();
   file_sigDA->Close();
   file_bkgDA->Close();

   return 0;

}