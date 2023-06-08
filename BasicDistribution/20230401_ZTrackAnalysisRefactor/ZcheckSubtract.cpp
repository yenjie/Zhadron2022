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

  gStyle->SetHistMinimumZero();

  gROOT->ForceStyle();
}

TFile *file_sigMC;
TFile *file_bkgMC;
//TFile *file_sigDA;
//TFile *file_bkgDA;
//TFile *file_ppMC;

TFile *file_sigMCgen;
TFile *file_bkgMCgen;

TFile *file_sigMCgen0Sub;

const char *typeofdata = "v14/20230601";
const char *typeofdata1 = "v14_20230601";
const char *typeofdatatext = "single muon";

void ZcheckSubtract_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",2000,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH2D* hMC_etaphi_1 = (TH2D*) file_sigMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   hMC_etaphi_1->SetName("hMC_etaphi_1");

   TH2D* hMC_etaphi_gen = (TH2D*) file_sigMCgen->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_etaphi_gen = (TH2D*) file_bkgMCgen->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   hMC_etaphi_gen->SetName("hMC_etaphi_gen");
   hMC_bkg_etaphi_gen->SetName("hMC_etaphi_gen");

   TH2D* hMC_bkg_etaphi_1 = (TH2D*) file_bkgMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   hMC_bkg_etaphi_1->SetName("hMC_bkg_etaphi_1");

   TH2D* hMC_etaphi_gen0Sub = (TH2D*) file_sigMCgen0Sub->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   hMC_etaphi_gen0Sub->SetName("hMC_etaphi_gen");

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

   TNamed *nM_tN  = (TNamed *) file_sigMC->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nMb_tN = (TNamed *) file_bkgMC->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nM_tNgen  = (TNamed *) file_sigMCgen->Get(Form("%s/GenEntryCount",FolderName.c_str()));
   TNamed *nMb_tNgen = (TNamed *) file_bkgMCgen->Get(Form("%s/GenEntryCount",FolderName.c_str()));

   TNamed *nM_tNgen0Sub  = (TNamed *) file_sigMCgen0Sub->Get(Form("%s/GenEntryCount",FolderName.c_str()));

   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();
   std::string sM_tNgen  = (std::string) nM_tNgen->GetTitle();
   std::string sMb_tNgen = (std::string) nMb_tNgen->GetTitle();

   std::string sM_tNgen0Sub  = (std::string) nM_tNgen0Sub->GetTitle();

   float tM_tN  = std::stof(sM_tN);
   float tMb_tN = std::stof(sMb_tN);
   float tM_tNgen  = std::stof(sM_tNgen);
   float tMb_tNgen = std::stof(sMb_tNgen);

   float tM_tNgen0Sub  = std::stof(sM_tNgen0Sub);

   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tMb_tNgen = "<<tMb_tNgen<<std::endl;
   std::cout<<"tM_tNgen0Sub = "<<tM_tNgen0Sub<<std::endl;

   double bineta2d = 6.4/150, binphi2d = M_PI/75;

   hMC_etaphi_1->Scale(1./tM_tN/bineta2d/binphi2d);
   hMC_bkg_etaphi_1->Scale(1./tMb_tN/bineta2d/binphi2d);
   hMC_etaphi_gen->Scale(1./tM_tNgen/bineta2d/binphi2d);
   hMC_bkg_etaphi_gen->Scale(1./tMb_tNgen/bineta2d/binphi2d);
   hMC_etaphi_gen0Sub->Scale(1./tM_tNgen0Sub/bineta2d/binphi2d);

   std::cout<<"Rebinning..."<<std::endl;

   hMC_etaphi_1->Rebin2D(10,10);
   hMC_bkg_etaphi_1->Rebin2D(10,10);
   hMC_etaphi_gen->Rebin2D(10,10);
   hMC_bkg_etaphi_gen->Rebin2D(10,10);
   hMC_etaphi_gen0Sub->Rebin2D(10,10);

   hMC_etaphi_1->Scale(1./100);
   hMC_bkg_etaphi_1->Scale(1./100);
   hMC_etaphi_gen->Scale(1./100);
   hMC_bkg_etaphi_gen->Scale(1./100);
   hMC_etaphi_gen0Sub->Scale(1./100);

   TH2D *hMC_sb_etaphi_1 = (TH2D*) hMC_etaphi_1->Clone("hMC_sb_etaphi_1");
   TH2D *hMC_sb_etaphi_gen = (TH2D*) hMC_etaphi_gen->Clone("hMC_sb_etaphi_gen");

   hMC_sb_etaphi_1->Add(hMC_bkg_etaphi_1,-1);
   hMC_sb_etaphi_gen->Add(hMC_bkg_etaphi_gen,-1);

   TH2D *RECO_o_GEN_sig = (TH2D*) hMC_etaphi_1->Clone("RECO_o_GEN_sig");
   TH2D *RECO_o_GEN_bkg = (TH2D*) hMC_bkg_etaphi_1->Clone("RECO_o_GEN_bkg");

   TH2D *GENsb_o_GEN0 = (TH2D*) hMC_sb_etaphi_gen->Clone("GENsb_o_GEN0");
   TH2D *RECOsb_o_GEN0 = (TH2D*) hMC_sb_etaphi_1->Clone("RECOsb_o_GEN0");

   RECO_o_GEN_sig->Divide(hMC_etaphi_gen);
   RECO_o_GEN_bkg->Divide(hMC_bkg_etaphi_gen);
   GENsb_o_GEN0->Divide(hMC_etaphi_gen0Sub);
   RECOsb_o_GEN0->Divide(hMC_etaphi_gen0Sub);

   if(TptL==0) TptL=TptL_min;

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
/*
   TLatex *ptN0 = new TLatex(0.1,0.97,Form("Signal N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tM_tN,tD_tN));
   ptN0->SetTextFont(42);
   ptN0->SetTextSize(0.03);
   ptN0->SetNDC(kTRUE);

   TLatex *ptNb = new TLatex(0.1,0.97,Form("Background N_{MC}^{Z} = %.1f, N_{Data}^{Z} = %.1f",tMb_tN,tDb_tN));
   ptNb->SetTextFont(42);
   ptNb->SetTextSize(0.03);
   ptNb->SetNDC(kTRUE);
*/
   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/CheckSubtract",typeofdata));

   c->Divide(3);
   c->cd(1);

   hMC_etaphi_1->Draw("lego20");
   hMC_etaphi_1->GetYaxis()->SetTitle("Signal MC RECO #Delta#phi_{Z,track}");
   hMC_etaphi_1->GetXaxis()->SetTitle("Signal MC RECO #Delta#eta_{Z,track}");
   hMC_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_etaphi_gen->Draw("lego20");
   hMC_etaphi_gen->GetYaxis()->SetTitle("Signal MC GEN #Delta#phi_{Z,track}");
   hMC_etaphi_gen->GetXaxis()->SetTitle("Signal MC GEN #Delta#eta_{Z,track}");
   hMC_etaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");
   hMC_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   RECO_o_GEN_sig->Draw("lego20");
   RECO_o_GEN_sig->GetYaxis()->SetTitle("Signal MC RECO/GEN #Delta#phi_{Z,track}");
   RECO_o_GEN_sig->GetXaxis()->SetTitle("Signal MC RECO/GEN #Delta#eta_{Z,track}");
   RECO_o_GEN_sig->GetZaxis()->SetTitle("dN/d#etad#phi");
   RECO_o_GEN_sig->GetXaxis()->SetTitleSize(24);
   RECO_o_GEN_sig->GetYaxis()->SetTitleSize(24);
   RECO_o_GEN_sig->GetXaxis()->SetTitleOffset(3.0);
   RECO_o_GEN_sig->GetYaxis()->SetTitleOffset(2.5);
   RECO_o_GEN_sig->GetXaxis()->SetNdivisions(50205,kFALSE);

   int max3 = RECO_o_GEN_sig->GetMaximum();
   if(max3>10) max3=10;
   RECO_o_GEN_sig->SetMaximum(max3);
   RECO_o_GEN_sig->SetMinimum(0);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/CheckSubtract/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_RECOGEN_sig.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_bkg_etaphi_1->Draw("lego20");
   hMC_bkg_etaphi_1->GetYaxis()->SetTitle("Background MC RECO #Delta#phi_{Z,track}");
   hMC_bkg_etaphi_1->GetXaxis()->SetTitle("Background MC RECO #Delta#eta_{Z,track}");
   hMC_bkg_etaphi_1->GetZaxis()->SetTitle("dN/d#etad#phi");
   hMC_bkg_etaphi_1->GetXaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_1->GetYaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_1->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_etaphi_1->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_etaphi_1->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_bkg_etaphi_gen->Draw("lego20");
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitle("Background MC GEN #Delta#phi_{Z,track}");
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitle("Background MC GEN #Delta#eta_{Z,track}");
   hMC_bkg_etaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_bkg_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_bkg_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_bkg_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   RECO_o_GEN_bkg->Draw("lego20");
   RECO_o_GEN_bkg->GetYaxis()->SetTitle("Background MC RECO/GEN #Delta#phi_{Z,track}");
   RECO_o_GEN_bkg->GetXaxis()->SetTitle("Background MC RECO/GEN #Delta#eta_{Z,track}");
   RECO_o_GEN_bkg->GetZaxis()->SetTitle("dN/d#etad#phi");
   RECO_o_GEN_bkg->GetXaxis()->SetTitleSize(24);
   RECO_o_GEN_bkg->GetYaxis()->SetTitleSize(24);
   RECO_o_GEN_bkg->GetXaxis()->SetTitleOffset(3.0);
   RECO_o_GEN_bkg->GetYaxis()->SetTitleOffset(2.5);
   RECO_o_GEN_bkg->GetXaxis()->SetNdivisions(50205,kFALSE);

   max3 = RECO_o_GEN_bkg->GetMaximum();
   if(max3>10) max3=10;
   RECO_o_GEN_bkg->SetMaximum(max3);
   RECO_o_GEN_bkg->SetMinimum(0);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/CheckSubtract/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_RECOGEN_bkg.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_gen->Draw("lego20");
   hMC_sb_etaphi_gen->GetYaxis()->SetTitle("GEN MC Sig-Bkg #Delta#phi_{Z,track}");
   hMC_sb_etaphi_gen->GetXaxis()->SetTitle("GEN MC Sig-Bkg #Delta#eta_{Z,track}");
   hMC_sb_etaphi_gen->GetZaxis()->SetTitle("dN/d#etad#phi");
   hMC_sb_etaphi_gen->GetXaxis()->SetTitleSize(24);
   hMC_sb_etaphi_gen->GetYaxis()->SetTitleSize(24);
   hMC_sb_etaphi_gen->GetXaxis()->SetTitleOffset(3.0);
   hMC_sb_etaphi_gen->GetYaxis()->SetTitleOffset(2.5);
   hMC_sb_etaphi_gen->GetXaxis()->SetNdivisions(50205,kFALSE);

   pt3d->Draw();
   pt3d2->Draw();
   pt3d3->Draw();

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(2);
   hMC_etaphi_gen0Sub->Draw("lego20");
   hMC_etaphi_gen0Sub->GetYaxis()->SetTitle("GEN Pythia MC Sig #Delta#phi_{Z,track}");
   hMC_etaphi_gen0Sub->GetXaxis()->SetTitle("GEN Pythia MC Sig #Delta#eta_{Z,track}");
   hMC_etaphi_gen0Sub->GetZaxis()->SetTitle("dN/d#etad#phi");
   hMC_etaphi_gen0Sub->GetXaxis()->SetTitleSize(24);
   hMC_etaphi_gen0Sub->GetYaxis()->SetTitleSize(24);
   hMC_etaphi_gen0Sub->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_gen0Sub->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_gen0Sub->GetXaxis()->SetNdivisions(50205,kFALSE);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   GENsb_o_GEN0->Draw("lego20");
   GENsb_o_GEN0->GetYaxis()->SetTitle("GEN MC (Sig-Bkg)/(Sig Pythia) #Delta#phi_{Z,track}");
   GENsb_o_GEN0->GetXaxis()->SetTitle("GEN MC (Sig-Bkg)/(Sig Pythia) #Delta#eta_{Z,track}");
   GENsb_o_GEN0->GetZaxis()->SetTitle("dN/d#etad#phi");
   GENsb_o_GEN0->GetXaxis()->SetTitleSize(24);
   GENsb_o_GEN0->GetYaxis()->SetTitleSize(24);
   GENsb_o_GEN0->GetXaxis()->SetTitleOffset(3.0);
   GENsb_o_GEN0->GetYaxis()->SetTitleOffset(2.5);
   GENsb_o_GEN0->GetXaxis()->SetNdivisions(50205,kFALSE);

   max3 = GENsb_o_GEN0->GetMaximum();
   if(max3>10) max3=10;
   GENsb_o_GEN0->SetMaximum(max3);
   GENsb_o_GEN0->SetMinimum(0);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/CheckSubtract/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_GENsb_GEN0.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(3);
   c->cd(1);

   hMC_sb_etaphi_1->Draw("lego20");
   hMC_sb_etaphi_1->GetYaxis()->SetTitle("RECO MC Sig-Bkg #Delta#phi_{Z,track}");
   hMC_sb_etaphi_1->GetXaxis()->SetTitle("RECO MC Sig-Bkg #Delta#eta_{Z,track}");
   hMC_sb_etaphi_1->GetZaxis()->SetTitle("dN/d#etad#phi");
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
   hMC_etaphi_gen0Sub->Draw("lego20");
   hMC_etaphi_gen0Sub->GetYaxis()->SetTitle("GEN Pythia MC Sig #Delta#phi_{Z,track}");
   hMC_etaphi_gen0Sub->GetXaxis()->SetTitle("GEN Pythia MC Sig #Delta#eta_{Z,track}");
   hMC_etaphi_gen0Sub->GetZaxis()->SetTitle("dN/d#etad#phi");
   hMC_etaphi_gen0Sub->GetXaxis()->SetTitleSize(24);
   hMC_etaphi_gen0Sub->GetYaxis()->SetTitleSize(24);
   hMC_etaphi_gen0Sub->GetXaxis()->SetTitleOffset(3.0);
   hMC_etaphi_gen0Sub->GetYaxis()->SetTitleOffset(2.5);
   hMC_etaphi_gen0Sub->GetXaxis()->SetNdivisions(50205,kFALSE);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->cd(3);
   RECOsb_o_GEN0->Draw("lego20");
   RECOsb_o_GEN0->GetYaxis()->SetTitle("RECO MC (Sig-Bkg)/(Sig Pythia) #Delta#phi_{Z,track}");
   RECOsb_o_GEN0->GetXaxis()->SetTitle("RECO MC (Sig-Bkg)/(Sig Pythia) #Delta#eta_{Z,track}");
   RECOsb_o_GEN0->GetZaxis()->SetTitle("dN/d#etad#phi");
   RECOsb_o_GEN0->GetXaxis()->SetTitleSize(24);
   RECOsb_o_GEN0->GetYaxis()->SetTitleSize(24);
   RECOsb_o_GEN0->GetXaxis()->SetTitleOffset(3.0);
   RECOsb_o_GEN0->GetYaxis()->SetTitleOffset(2.5);
   RECOsb_o_GEN0->GetXaxis()->SetNdivisions(50205,kFALSE);

   max3 = RECOsb_o_GEN0->GetMaximum();
   if(max3>10) max3=10;
   RECOsb_o_GEN0->SetMaximum(max3);
   RECOsb_o_GEN0->SetMinimum(0);

   gPad->SetTheta(60.839);
   gPad->SetPhi(38.0172);

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/CheckSubtract/Ztrack_%s_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_RECOsb_GEN0.png",typeofdata,typeofdata1,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

}

int main(int argc, char *argv[]){

  style();

   file_sigMC = TFile::Open("GraphMCSignal_v14.root","read");
   file_bkgMC = TFile::Open("GraphMCBackground_v14.root","read");
   //file_sigDA = TFile::Open("GraphDataSignal_v14.root","read");
   //file_bkgDA = TFile::Open("GraphDataBackground_v14.root","read");
   //file_ppMC  = TFile::Open("GraphPPMC_v14.root","read");

   file_sigMCgen = TFile::Open("GraphMCSignalGen_v14.root","read");
   file_bkgMCgen = TFile::Open("GraphMCBackgroundGen_v14.root","read");

   file_sigMCgen0Sub = TFile::Open("GraphMCSignalGen0Sub_v14.root","read");

   
  //ZcheckSubtract_single(40, 20, 2000,  0, 90,  0, 1000);
  //ZcheckSubtract_single(40,  5, 2000,  0, 90,  0, 1000);

  ZcheckSubtract_single(40, 20, 2000,  0, 90, 10,   20);
  ZcheckSubtract_single(40, 20, 2000,  0, 90, 20,   50);
  ZcheckSubtract_single(40, 20, 2000,  0, 90, 50,  100);

  ZcheckSubtract_single(40, 10, 2000,  0, 90,  2, 1000);

  return 0;
}