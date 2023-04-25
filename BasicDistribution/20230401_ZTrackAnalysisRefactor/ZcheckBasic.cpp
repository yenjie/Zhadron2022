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

double TptL_min = 0.5;

int main(int argc, char *argv[]);
void ZcheckBasic_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

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

TFile *file_sigMCgen0Sub;

const char *typeofdata = "20230425";
const char *typeofdatatext = "double muon";

void ZcheckBasic_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",1400,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH1D* hData_Zeta = (TH1D*) file_sigDA->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_Zeta = (TH1D*) file_sigMC->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hpp_Zeta = (TH1D*) file_ppMC->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hData_bkg_Zeta = (TH1D*) file_bkgDA->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_bkg_Zeta = (TH1D*) file_bkgMC->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_Zeta_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_bkg_Zeta_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HZEta", FolderName.c_str()));
   TH1D* hMC_Zeta_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HZEta", FolderName.c_str()));

   hData_Zeta->SetName("hData_Zeta");
   hMC_Zeta->SetName("hMC_Zeta");
   hpp_Zeta->SetName("hpp_Zeta");
   hData_bkg_Zeta->SetName("hData_bkg_Zeta");
   hMC_bkg_Zeta->SetName("hMC_bkg_Zeta");
   hMC_Zeta_gen->SetName("hMC_Zeta_gen");
   hMC_bkg_Zeta_gen->SetName("hMC_bkg_Zeta_gen");
   hMC_Zeta_gen0Sub->SetName("hMC_Zeta_gen0Sub");

   TH1D* hData_Zphi = (TH1D*) file_sigDA->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_Zphi = (TH1D*) file_sigMC->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hpp_Zphi = (TH1D*) file_ppMC->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hData_bkg_Zphi = (TH1D*) file_bkgDA->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Zphi = (TH1D*) file_bkgMC->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_Zphi_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Zphi_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HZPhi", FolderName.c_str()));
   TH1D* hMC_Zphi_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HZPhi", FolderName.c_str()));

   hData_Zphi->SetName("hData_Zphi");
   hMC_Zphi->SetName("hMC_Zphi");
   hpp_Zphi->SetName("hpp_Zphi");
   hData_bkg_Zphi->SetName("hData_bkg_Zphi");
   hMC_bkg_Zphi->SetName("hMC_bkg_Zphi");
   hMC_Zphi_gen->SetName("hMC_Zphi_gen");
   hMC_bkg_Zphi_gen->SetName("hMC_bkg_Zphi_gen");
   hMC_Zphi_gen0Sub->SetName("hMC_Zphi_gen0Sub");

   TH1D* hData_Tracketa = (TH1D*) file_sigDA->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_Tracketa = (TH1D*) file_sigMC->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hpp_Tracketa = (TH1D*) file_ppMC->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hData_bkg_Tracketa = (TH1D*) file_bkgDA->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_bkg_Tracketa = (TH1D*) file_bkgMC->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_Tracketa_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_bkg_Tracketa_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HTrackEta", FolderName.c_str()));
   TH1D* hMC_Tracketa_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HTrackEta", FolderName.c_str()));

   hData_Tracketa->SetName("hData_Tracketa");
   hMC_Tracketa->SetName("hMC_Tracketa");
   hpp_Tracketa->SetName("hpp_Tracketa");
   hData_bkg_Tracketa->SetName("hData_bkg_Tracketa");
   hMC_bkg_Tracketa->SetName("hMC_bkg_Tracketa");
   hMC_Tracketa_gen->SetName("hMC_Tracketa_gen");
   hMC_bkg_Tracketa_gen->SetName("hMC_bkg_Tracketa_gen");
   hMC_Tracketa_gen0Sub->SetName("hMC_Tracketa_gen0Sub");

   TH1D* hData_Trackphi = (TH1D*) file_sigDA->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_Trackphi = (TH1D*) file_sigMC->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hpp_Trackphi = (TH1D*) file_ppMC->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hData_bkg_Trackphi = (TH1D*) file_bkgDA->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Trackphi = (TH1D*) file_bkgMC->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_Trackphi_gen = (TH1D*) file_sigMCgen->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_bkg_Trackphi_gen = (TH1D*) file_bkgMCgen->Get(Form("%s/HTrackPhi", FolderName.c_str()));
   TH1D* hMC_Trackphi_gen0Sub = (TH1D*) file_sigMCgen0Sub->Get(Form("%s/HTrackPhi", FolderName.c_str()));

   hData_Trackphi->SetName("hData_Trackphi");
   hMC_Trackphi->SetName("hMC_Trackphi");
   hpp_Trackphi->SetName("hpp_Trackphi");
   hData_bkg_Trackphi->SetName("hData_bkg_Trackphi");
   hMC_bkg_Trackphi->SetName("hMC_bkg_Trackphi");
   hMC_Trackphi_gen->SetName("hMC_Trackphi_gen");
   hMC_bkg_Trackphi_gen->SetName("hMC_bkg_Trackphi_gen");
   hMC_Trackphi_gen0Sub->SetName("hMC_Trackphi_gen0Sub");

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

   TNamed *nM_tNgen  = (TNamed *) file_sigMCgen->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nMb_tNgen = (TNamed *) file_bkgMCgen->Get(Form("%s/EntryCount",FolderName.c_str()));

   TNamed *nM_tNgen0Sub  = (TNamed *) file_sigMCgen0Sub->Get(Form("%s/EntryCount",FolderName.c_str()));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sDb_tN = (std::string) nDb_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();
   std::string spM_tN = (std::string) npM_tN->GetTitle();

   std::string sM_tNgen  = (std::string) nM_tNgen->GetTitle();
   std::string sMb_tNgen = (std::string) nMb_tNgen->GetTitle();

   std::string sM_tNgen0Sub  = (std::string) nM_tNgen0Sub->GetTitle();

   float tD_tN  = std::stof(sD_tN);
   float tM_tN  = std::stof(sM_tN);
   float tDb_tN = std::stof(sDb_tN);
   float tMb_tN = std::stof(sMb_tN);
   float tpM_tN = std::stof(spM_tN);

   float tM_tNgen  = std::stof(sM_tNgen);
   float tMb_tNgen = std::stof(sMb_tNgen);

   float tM_tNgen0Sub  = std::stof(sM_tNgen0Sub);

   std::cout<<"tD_tN = "<<tD_tN<<std::endl;
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tDb_tN = "<<tDb_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;

   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tMb_tNgen = "<<tMb_tNgen<<std::endl;

   std::cout<<"tM_tNgen0Sub = "<<tM_tNgen0Sub<<std::endl;

   hData_Zeta->Scale(1./tD_tN);
   hMC_Zeta->Scale(1./tM_tN);
   hpp_Zeta->Scale(1./tpM_tN);
   hData_bkg_Zeta->Scale(1./tDb_tN);
   hMC_bkg_Zeta->Scale(1./tMb_tN);
   hMC_Zeta_gen->Scale(1./tM_tNgen);
   hMC_bkg_Zeta_gen->Scale(1./tMb_tNgen);
   hMC_Zeta_gen0Sub->Scale(1./tM_tNgen0Sub);


   hData_Zeta->SetMarkerStyle(24);
   hMC_Zeta->SetMarkerStyle(24);
   hpp_Zeta->SetMarkerStyle(24);
   hData_bkg_Zeta->SetMarkerStyle(24);
   hMC_bkg_Zeta->SetMarkerStyle(24);
   hMC_Zeta_gen->SetMarkerStyle(24);
   hMC_bkg_Zeta_gen->SetMarkerStyle(24);
   hMC_Zeta_gen0Sub->SetMarkerStyle(24);

   hData_Zeta->SetMarkerColor(kBlack);
   hData_bkg_Zeta->SetMarkerColor(kBlack);

   hData_Zeta->SetLineColor(kBlack);
   hMC_Zeta->SetLineColor(kBlue);
   hpp_Zeta->SetLineColor(kViolet);
   hData_bkg_Zeta->SetLineColor(kBlack);
   hMC_bkg_Zeta->SetLineColor(kBlue);
   hMC_Zeta_gen->SetLineColor(kBlack);
   hMC_bkg_Zeta_gen->SetLineColor(kBlack);
   hMC_Zeta_gen0Sub->SetLineColor(kRed);


   hData_Tracketa->Scale(1./tD_tN);
   hMC_Tracketa->Scale(1./tM_tN);
   hpp_Tracketa->Scale(1./tpM_tN);
   hData_bkg_Tracketa->Scale(1./tDb_tN);
   hMC_bkg_Tracketa->Scale(1./tMb_tN);
   hMC_Tracketa_gen->Scale(1./tM_tNgen);
   hMC_bkg_Tracketa_gen->Scale(1./tMb_tNgen);
   hMC_Tracketa_gen0Sub->Scale(1./tM_tNgen0Sub);


   hData_Tracketa->SetMarkerStyle(24);
   hMC_Tracketa->SetMarkerStyle(24);
   hpp_Tracketa->SetMarkerStyle(24);
   hData_bkg_Tracketa->SetMarkerStyle(24);
   hMC_bkg_Tracketa->SetMarkerStyle(24);
   hMC_Tracketa_gen->SetMarkerStyle(24);
   hMC_bkg_Tracketa_gen->SetMarkerStyle(24);
   hMC_Tracketa_gen0Sub->SetMarkerStyle(24);

   hData_Tracketa->SetMarkerColor(kBlack);
   hData_bkg_Tracketa->SetMarkerColor(kBlack);

   hData_Tracketa->SetLineColor(kBlack);
   hMC_Tracketa->SetLineColor(kBlue);
   hpp_Tracketa->SetLineColor(kViolet);
   hData_bkg_Tracketa->SetLineColor(kBlack);
   hMC_bkg_Tracketa->SetLineColor(kBlue);
   hMC_Tracketa_gen->SetLineColor(kBlack);
   hMC_bkg_Tracketa_gen->SetLineColor(kBlack);
   hMC_Tracketa_gen0Sub->SetLineColor(kRed);

   if(TptL==0) TptL=TptL_min;

   TLegend leg(0.58,0.78,0.98,0.9);
   leg.AddEntry(hMC_Zeta_gen ,"Monte Carlo: GEN level","lep");
   leg.AddEntry(hMC_Zeta ,"Monte Carlo: RECO level","lep");
   leg.AddEntry(hData_Zeta ,Form("Data: %s",typeofdatatext),"lep");
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

   TLatex *ptN0 = new TLatex(0.1,0.97,Form("Signal N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tM_tN,tD_tN));
   ptN0->SetTextFont(42);
   ptN0->SetTextSize(0.03);
   ptN0->SetNDC(kTRUE);

   TLatex *ptNb = new TLatex(0.1,0.97,Form("Background N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tMb_tN,tDb_tN));
   ptNb->SetTextFont(42);
   ptNb->SetTextSize(0.03);
   ptNb->SetNDC(kTRUE);

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/Basic",typeofdata));

   c->Divide(2);
   c->cd(1);

   double max1 = hMC_Zeta_gen->GetMaximum();
   double max2 = hMC_Zeta->GetMaximum();
   double max3 = hData_Zeta->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Zeta->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Zeta->Draw("ep");
   else hMC_Zeta_gen->Draw("hist");
   hMC_Zeta_gen->Draw("hist same");
   hMC_Zeta->Draw("hist same");
   hData_Zeta->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Zeta_gen->SetXTitle("Signal #eta_{Z}");
   hMC_Zeta->SetXTitle("Signal #eta_{Z}");
   hData_Zeta->SetXTitle("Signal #eta_{Z}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Zeta_gen->SetMinimum(0);
   hMC_Zeta_gen->SetMaximum(1.6*max1); 
   hMC_Zeta->SetMinimum(0);
   hMC_Zeta->SetMaximum(1.6*max1); 
   hData_Zeta->SetMinimum(0);
   hData_Zeta->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Zeta_gen->GetMaximum();
   max2 = hMC_bkg_Zeta->GetMaximum();
   max3 = hData_bkg_Zeta->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Zeta->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Zeta->Draw("ep");
   else hMC_bkg_Zeta_gen->Draw("hist");
   hMC_bkg_Zeta_gen->Draw("hist same");
   hMC_bkg_Zeta->Draw("hist same");
   hData_bkg_Zeta->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Zeta_gen->SetXTitle("Background #eta_{Z}");
   hMC_bkg_Zeta->SetXTitle("Background #eta_{Z}");
   hData_bkg_Zeta->SetXTitle("Background #eta_{Z}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Zeta_gen->SetMinimum(0);
   hMC_bkg_Zeta_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Zeta->SetMinimum(0);
   hMC_bkg_Zeta->SetMaximum(1.6*max1); 
   hData_bkg_Zeta->SetMinimum(0);
   hData_bkg_Zeta->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zeta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   max1 = hMC_Zphi_gen->GetMaximum();
   max2 = hMC_Zphi->GetMaximum();
   max3 = hData_Zphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Zphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Zphi->Draw("ep");
   else hMC_Zphi_gen->Draw("hist");
   hMC_Zphi_gen->Draw("hist same");
   hMC_Zphi->Draw("hist same");
   hData_Zphi->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Zphi_gen->SetXTitle("Signal #phi_{Z}");
   hMC_Zphi->SetXTitle("Signal #phi_{Z}");
   hData_Zphi->SetXTitle("Signal #phi_{Z}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Zphi_gen->SetMinimum(0);
   hMC_Zphi_gen->SetMaximum(1.6*max1); 
   hMC_Zphi->SetMinimum(0);
   hMC_Zphi->SetMaximum(1.6*max1); 
   hData_Zphi->SetMinimum(0);
   hData_Zphi->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Zphi_gen->GetMaximum();
   max2 = hMC_bkg_Zphi->GetMaximum();
   max3 = hData_bkg_Zphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Zphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Zphi->Draw("ep");
   else hMC_bkg_Zphi_gen->Draw("hist");
   hMC_bkg_Zphi_gen->Draw("hist same");
   hMC_bkg_Zphi->Draw("hist same");
   hData_bkg_Zphi->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Zphi_gen->SetXTitle("Background #phi_{Z}");
   hMC_bkg_Zphi->SetXTitle("Background #phi_{Z}");
   hData_bkg_Zphi->SetXTitle("Background #phi_{Z}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Zphi_gen->SetMinimum(0);
   hMC_bkg_Zphi_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Zphi->SetMinimum(0);
   hMC_bkg_Zphi->SetMaximum(1.6*max1); 
   hData_bkg_Zphi->SetMinimum(0);
   hData_bkg_Zphi->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Zphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();



   c->Divide(2);
   c->cd(1);

   max1 = hMC_Tracketa_gen->GetMaximum();
   max2 = hMC_Tracketa->GetMaximum();
   max3 = hData_Tracketa->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Tracketa->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Tracketa->Draw("ep");
   else hMC_Tracketa_gen->Draw("hist");
   hMC_Tracketa_gen->Draw("hist same");
   hMC_Tracketa->Draw("hist same");
   hData_Tracketa->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Tracketa_gen->SetXTitle("Signal #eta_{Track}");
   hMC_Tracketa->SetXTitle("Signal #eta_{Track}");
   hData_Tracketa->SetXTitle("Signal #eta_{Track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Tracketa_gen->SetMinimum(0);
   hMC_Tracketa_gen->SetMaximum(1.6*max1); 
   hMC_Tracketa->SetMinimum(0);
   hMC_Tracketa->SetMaximum(1.6*max1); 
   hData_Tracketa->SetMinimum(0);
   hData_Tracketa->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Tracketa_gen->GetMaximum();
   max2 = hMC_bkg_Tracketa->GetMaximum();
   max3 = hData_bkg_Tracketa->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Tracketa->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Tracketa->Draw("ep");
   else hMC_bkg_Tracketa_gen->Draw("hist");
   hMC_bkg_Tracketa_gen->Draw("hist same");
   hMC_bkg_Tracketa->Draw("hist same");
   hData_bkg_Tracketa->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Tracketa_gen->SetXTitle("Background #eta_{Track}");
   hMC_bkg_Tracketa->SetXTitle("Background #eta_{Track}");
   hData_bkg_Tracketa->SetXTitle("Background #eta_{Track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Tracketa_gen->SetMinimum(0);
   hMC_bkg_Tracketa_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Tracketa->SetMinimum(0);
   hMC_bkg_Tracketa->SetMaximum(1.6*max1); 
   hData_bkg_Tracketa->SetMinimum(0);
   hData_bkg_Tracketa->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/Tracktrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Tracketa.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   max1 = hMC_Trackphi_gen->GetMaximum();
   max2 = hMC_Trackphi->GetMaximum();
   max3 = hData_Trackphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_Trackphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_Trackphi->Draw("ep");
   else hMC_Trackphi_gen->Draw("hist");
   hMC_Trackphi_gen->Draw("hist same");
   hMC_Trackphi->Draw("hist same");
   hData_Trackphi->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_Trackphi_gen->SetXTitle("Signal #phi_{Track}");
   hMC_Trackphi->SetXTitle("Signal #phi_{Track}");
   hData_Trackphi->SetXTitle("Signal #phi_{Track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_Trackphi_gen->SetMinimum(0);
   hMC_Trackphi_gen->SetMaximum(1.6*max1); 
   hMC_Trackphi->SetMinimum(0);
   hMC_Trackphi->SetMaximum(1.6*max1); 
   hData_Trackphi->SetMinimum(0);
   hData_Trackphi->SetMaximum(1.6*max1); 

   ptN0->Draw();

   c->cd(2);

   max1 = hMC_bkg_Trackphi_gen->GetMaximum();
   max2 = hMC_bkg_Trackphi->GetMaximum();
   max3 = hData_bkg_Trackphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_bkg_Trackphi->Draw("hist");
   else if(max1<max3 && max2<max3) hData_bkg_Trackphi->Draw("ep");
   else hMC_bkg_Trackphi_gen->Draw("hist");
   hMC_bkg_Trackphi_gen->Draw("hist same");
   hMC_bkg_Trackphi->Draw("hist same");
   hData_bkg_Trackphi->Draw("ep same");

   if(max1<max2 && max3<max2)  max1=max2;
   else if(max1<max3 && max2<max3) max1=max3;

   hMC_bkg_Trackphi_gen->SetXTitle("Background #phi_{Track}");
   hMC_bkg_Trackphi->SetXTitle("Background #phi_{Track}");
   hData_bkg_Trackphi->SetXTitle("Background #phi_{Track}");

   leg.Draw();
   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   hMC_bkg_Trackphi_gen->SetMinimum(0);
   hMC_bkg_Trackphi_gen->SetMaximum(1.6*max1); 
   hMC_bkg_Trackphi->SetMinimum(0);
   hMC_bkg_Trackphi->SetMaximum(1.6*max1); 
   hData_bkg_Trackphi->SetMinimum(0);
   hData_bkg_Trackphi->SetMaximum(1.6*max1); 

   ptNb->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/Basic/Tracktrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Trackphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();


}
int main(int argc, char *argv[]){

  style();

   file_sigMC = TFile::Open("GraphMCSignal_0422.root","read");
   file_bkgMC = TFile::Open("GraphMCBackground_0422.root","read");
   file_sigDA = TFile::Open("GraphDataSignal_0422.root","read");
   file_bkgDA = TFile::Open("GraphDataBackground_0422.root","read");
   file_ppMC  = TFile::Open("GraphPPMC_0422.root","read");

   file_sigMCgen = TFile::Open("GraphMCSignalGen_0422.root","read");
   file_bkgMCgen = TFile::Open("GraphMCBackgroundGen_0422.root","read");

   file_sigMCgen0Sub = TFile::Open("GraphMCSignalGen0Sub_0422.root","read");

   
  ZcheckBasic_single(40, 20, 2000,  0, 90,  0, 1000);
  ZcheckBasic_single(40,  5, 2000,  0, 90,  0, 1000);

  return 0;
}