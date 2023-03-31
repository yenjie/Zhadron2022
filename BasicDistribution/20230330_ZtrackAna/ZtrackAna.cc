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

const char *typeofdata = "20230331_2";
const char *typeofdatatext = "double muon";

const float hf_diff[5] = {999999, 3039.47, 1342.21, 484.422, 24.7924};
const float cent_diff[5] = {0, 10, 30, 50, 90};

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

void ZtrackAna_single(double ptL=0,double ptH=2000,int centL=0,int centH=4,double TptL=0,double TptH=10000)
{

   TCanvas *c = new TCanvas("c","",800,800);

   int binnum = 40;

   TH1D *hData_eta = new TH1D("hData_eta","",binnum,0,6.3);
   TH1D *hMC_eta = new TH1D("hMC_eta","",binnum,0,6.3);

   TH1D *hData_phi = new TH1D("hData_phi","",binnum,-3.1415926,3.1415926);
   TH1D *hMC_phi = new TH1D("hMC_phi","",binnum,-3.1415926,3.1415926);

   TH2D *hData_etaphi_1 = new TH2D("hData_etaphi_1","",30,-3.2,3.2,30,-3.1415926,3.1415926);
   TH2D *hMC_etaphi_1 = new TH2D("hMC_etaphi_1","",150,-3.2,3.2,150,-3.1415926,3.1415926);

   TH2D *hData_etaphi_2 = new TH2D("hData_etaphi_2","",30,-3.2,3.2,30,-3.1415926,3.1415926);
   TH2D *hMC_etaphi_2 = new TH2D("hMC_etaphi_2","",150,-3.2,3.2,150,-3.1415926,3.1415926);

   TH1D *hData_bkg_eta = new TH1D("hData_bkg_eta","",binnum,0,6.3);
   TH1D *hMC_bkg_eta = new TH1D("hMC_bkg_eta","",binnum,0,6.3);

   TH1D *hData_bkg_phi = new TH1D("hData_bkg_phi","",binnum,-3.1415926,3.1415926);
   TH1D *hMC_bkg_phi = new TH1D("hMC_bkg_phi","",binnum,-3.1415926,3.1415926);

   TH2D *hData_bkg_etaphi_1 = new TH2D("hData_bkg_etaphi_1","",30,-3.2,3.2,30,-3.1415926,3.1415926);
   TH2D *hMC_bkg_etaphi_1 = new TH2D("hMC_bkg_etaphi_1","",150,-3.2,3.2,150,-3.1415926,3.1415926);

   TH2D *hData_bkg_etaphi_2 = new TH2D("hData_bkg_etaphi_2","",30,-3.2,3.2,30,-3.1415926,3.1415926);
   TH2D *hMC_bkg_etaphi_2 = new TH2D("hMC_bkg_etaphi_2","",150,-3.2,3.2,150,-3.1415926,3.1415926);

   TChain *tMC = new TChain("Tree");
   tMC->Add("/eos/cms/store/group/phys_heavyions_ops/pchou/OutputMC_old/*.root?#Tree");
 
   TChain *tData = new TChain("Tree");
   tData->Add("/afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/Skims/20230310_ZHadronSkims/Output_old/*.root?#Tree");

   TChain *tMC_bkg = new TChain("Tree");
   tMC_bkg->Add("/eos/cms/store/group/phys_heavyions_ops/pchou/OutputMCbkg_old/*.root?#Tree");
 
   TChain *tData_bkg = new TChain("Tree");
   tData_bkg->Add("/afs/cern.ch/user/p/pchou/PhysicsHIZHadron2022/Skims/20230310_ZHadronSkims/OutputBkg_old/*.root?#Tree");

   TCut sel_reg = Form("zPt[0]>%f&&zPt[0]<%f&&hiHF<=%.4f&&hiHF>%.4f&&trackPt>%f&&trackPt<%f",ptL,ptH,hf_diff[centL],hf_diff[centH],TptL,TptH);

   //TCut nolepton = "abs(trackPDFId)!=13&&abs(trackPDFId)!=11";
   TCut nolepton = "";

   TCut zMassRange = "zMass[0]>60";

   tData->Draw("trackDeta>>hData_eta",zMassRange&&sel_reg&&nolepton);
   tMC->Draw("trackDeta>>hMC_eta",zMassRange&&sel_reg&&nolepton);
   tData->Draw("trackDphi>>hData_phi",zMassRange&&sel_reg&&nolepton);
   tMC->Draw("trackDphi>>hMC_phi",zMassRange&&sel_reg&&nolepton);
   tMC->Draw("trackDphi:trackDeta>>hMC_etaphi_1",zMassRange&&sel_reg&&nolepton);
   tData->Draw("trackDphi:trackDeta>>hData_etaphi_1",zMassRange&&sel_reg&&nolepton);
   tMC->Draw("trackDphi:-trackDeta>>hMC_etaphi_2",zMassRange&&sel_reg&&nolepton);
   tData->Draw("trackDphi:-trackDeta>>hData_etaphi_2",zMassRange&&sel_reg&&nolepton);

   tData_bkg->Draw("trackDeta>>hData_bkg_eta",zMassRange&&sel_reg&&nolepton);
   tMC_bkg->Draw("trackDeta>>hMC_bkg_eta",zMassRange&&sel_reg&&nolepton);
   tData_bkg->Draw("trackDphi>>hData_bkg_phi",zMassRange&&sel_reg&&nolepton);
   tMC_bkg->Draw("trackDphi>>hMC_bkg_phi",zMassRange&&sel_reg&&nolepton);
   tMC_bkg->Draw("trackDphi:trackDeta>>hMC_bkg_etaphi_1",zMassRange&&sel_reg&&nolepton);
   tData_bkg->Draw("trackDphi:trackDeta>>hData_bkg_etaphi_1",zMassRange&&sel_reg&&nolepton);
   tMC_bkg->Draw("trackDphi:-trackDeta>>hMC_bkg_etaphi_2",zMassRange&&sel_reg&&nolepton);
   tData_bkg->Draw("trackDphi:-trackDeta>>hData_bkg_etaphi_2",zMassRange&&sel_reg&&nolepton);

   hMC_etaphi_1->Add(hMC_etaphi_2);
   hData_etaphi_1->Add(hData_etaphi_2);

   hMC_bkg_etaphi_1->Add(hMC_bkg_etaphi_2);
   hData_bkg_etaphi_1->Add(hData_bkg_etaphi_2);

   hData_eta->Sumw2();
   hMC_eta->Sumw2();
   hData_phi->Sumw2();
   hMC_phi->Sumw2();

   hData_bkg_eta->Sumw2();
   hMC_bkg_eta->Sumw2();
   hData_bkg_phi->Sumw2();
   hMC_bkg_phi->Sumw2();

   int tD_tN = tData->GetEntries("Sum$(trackPt)>0");
   int tM_tN = tMC->GetEntries("Sum$(trackPt)>0");
   int tDb_tN = tData_bkg->GetEntries("Sum$(trackPt)>0");
   int tMb_tN = tMC_bkg->GetEntries("Sum$(trackPt)>0");

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

   TLatex *pt = new TLatex(0.18,0.88,Form("%.0f %%< Centrality < %.0f %%",cent_diff[centL],cent_diff[centH]));
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

   TLatex *pt3d = new TLatex(0.03,0.94,Form("%.0f %%< Centrality < %.0f %%",cent_diff[centL],cent_diff[centH]));
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


   TLatex *ptN0 = new TLatex(0.5,0.97,Form("Signal N_{MC} = %d, N_{Data} = %d",countM0,countD0));
   ptN0->SetTextFont(42);
   ptN0->SetTextSize(0.03);
   ptN0->SetNDC(kTRUE);

   TLatex *ptNb = new TLatex(0.5,0.97,Form("Background N_{MC} = %d, N_{Data} = %d",countM0,countD0));
   ptNb->SetTextFont(42);
   ptNb->SetTextSize(0.03);
   ptNb->SetNDC(kTRUE);

   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p figs/track/%s",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Deta",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/Dphi",typeofdata));
   gSystem->Exec(Form("mkdir -p figs/track/%s/3D",typeofdata));

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

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Deta/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Deta.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
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

   c->SaveAs(Form("figs/track/%s/Dphi/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Dphi.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
   c->Clear();

   c->SetCanvasSize(1400,800);
   c->Divide(2);
   c->cd(1);

   hMC_etaphi_1->Draw("lego20z");
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
   hData_etaphi_1->Draw("lego20z");
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

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_sig_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_bkg_etaphi_1->Draw("lego20z");
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
   hData_bkg_etaphi_1->Draw("lego20z");
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

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_bkg_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20z");
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
   hData_sb_etaphi_1->Draw("lego20z");
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

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   hMC_sbr_etaphi_1->Draw("lego20z");
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
   hData_sbr_etaphi_1->Draw("lego20z");
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

   c->SaveAs(Form("figs/track/%s/3D/Ztrack_%s_sbr_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_3D.png",typeofdata,typeofdata,ptL,ptH,cent_diff[centL],cent_diff[centH],TptL,TptH)); 
   c->Clear();

}


void ZtrackAna(int casenum){

   style();

   switch (casenum){
      case 0: ZtrackAna_single(); break;
      case 1: ZtrackAna_single(30,40);break;
      case 2: ZtrackAna_single(40,60);break;
      case 3: ZtrackAna_single(60,80);break;
      case 4: ZtrackAna_single(80,100); break;
      case 5: ZtrackAna_single(0,2000,0,1);break;
      case 6: ZtrackAna_single(0,2000,1,2);break;
      case 7: ZtrackAna_single(0,2000,2,3);break;
      case 8: ZtrackAna_single(0,2000,3,4);break;
      case 9: ZtrackAna_single(0,2000,0,4,2,5);break;
      case 10: ZtrackAna_single(0,2000,0,4,5,10);break;
      case 11: ZtrackAna_single(0,2000,0,4,10,20);break;
      case 12: ZtrackAna_single(0,2000,0,4,20,50);break;
      case 13: ZtrackAna_single(0,2000,0,4,50,100);break;
      case 14: ZtrackAna_single(20,2000,3,4);break;
      case 15: ZtrackAna_single(40,2000,3,4);break;
      case 16: ZtrackAna_single(20,2000,3,4,50,100);break;
      case 17: ZtrackAna_single(40,2000,3,4,50,100);break;
      case 18: ZtrackAna_single(20,2000,3,4,20,50);break;
      case 19: ZtrackAna_single(40,2000,3,4,20,50);break;
      case 20: ZtrackAna_single(20,2000,3,4,5,10);break;
      case 21: ZtrackAna_single(40,2000,3,4,5,10);break;

/*      
      case 0: ZtrackAna_single(); break;
      case 1: ZtrackAna_single(30,40);break;
      case 2: ZtrackAna_single(40,60);break;
      case 3: ZtrackAna_single(60,80);break;
      case 4: ZtrackAna_single(80,100); break;
      case 5: ZtrackAna_single(0,2000,0,1);break;
      case 6: ZtrackAna_single(0,2000,1,2);break;
      case 7: ZtrackAna_single(0,2000,2,3);break;
      case 8: ZtrackAna_single(0,2000,3,4);break;
      case 9: ZtrackAna_single(0,2000,0,4,0,1);break;
      case 10: ZtrackAna_single(0,2000,0,4,1,2);break;
      case 11: ZtrackAna_single(0,2000,0,4,2,5);break;
      case 12: ZtrackAna_single(0,2000,0,4,5,10);break;
      case 13: ZtrackAna_single(0,2000,0,4,10,20);break;
      case 14: ZtrackAna_single(0,2000,0,4,20,50);break;
      case 15: ZtrackAna_single(0,2000,0,4,50,100);break;
      case 16: ZtrackAna_single(0,2000,0,4,100,10000);break;
      case 17: ZtrackAna_single(0,2000,3,4,0,1);break;
      case 18: ZtrackAna_single(0,2000,3,4,1,2);break;
      case 19: ZtrackAna_single(0,2000,3,4,2,5);break;
      case 20: ZtrackAna_single(0,2000,3,4,5,10);break;
      case 21: ZtrackAna_single(0,2000,3,4,10,20);break;
      case 22: ZtrackAna_single(0,2000,3,4,20,50);break;
      case 23: ZtrackAna_single(0,2000,3,4,50,100);break;
      case 24: ZtrackAna_single(0,2000,3,4,100,10000);break;
      case 25: ZtrackAna_single(0,2000,2,4,0,1);break;
      case 26: ZtrackAna_single(0,2000,2,4,1,2);break;
      case 27: ZtrackAna_single(0,2000,2,4,2,5);break;
      case 28: ZtrackAna_single(0,2000,2,4,5,10);break;
      case 29: ZtrackAna_single(0,2000,2,4,10,20);break;
      case 30: ZtrackAna_single(0,2000,2,4,20,50);break;
      case 31: ZtrackAna_single(0,2000,2,4,50,100);break;
      case 32: ZtrackAna_single(0,2000,2,4,100,10000);break;
      case 33: ZtrackAna_single(60,100,0,4,0,1);break;
      case 34: ZtrackAna_single(60,100,0,4,1,2);break;
      case 35: ZtrackAna_single(60,100,0,4,2,5);break;
      case 36: ZtrackAna_single(60,100,0,4,5,10);break;
      case 37: ZtrackAna_single(60,100,0,4,10,20);break;
      case 38: ZtrackAna_single(60,100,0,4,20,50);break;
      case 39: ZtrackAna_single(60,100,0,4,50,100);break;
      case 40: ZtrackAna_single(60,100,0,4,100,10000);break;
     */    

      /*
      case 0: ZtrackAna_single(); break;
      case 1: ZtrackAna_single(0,2000,0,4,0,1);break;
      case 2: ZtrackAna_single(0,2000,0,4,1,2);break;
      case 3: ZtrackAna_single(0,2000,0,4,2,5);break;
      case 4: ZtrackAna_single(0,2000,0,4,5,10);break;
      case 5: ZtrackAna_single(0,2000,2,4,0,1);break;
      case 6: ZtrackAna_single(0,2000,2,4,1,2);break;
      case 7: ZtrackAna_single(0,2000,2,4,2,5);break;
      case 8: ZtrackAna_single(0,2000,2,4,5,10);break;
      case 9:  ZtrackAna_single(0,2000,3,4,0,1);break;
      case 10: ZtrackAna_single(0,2000,3,4,1,2);break;
      case 11: ZtrackAna_single(0,2000,3,4,2,5);break;
      case 12: ZtrackAna_single(0,2000,3,4,5,10);break;
      case 13: ZtrackAna_single(0,200,3,4);break;
         */
      
   }
}
