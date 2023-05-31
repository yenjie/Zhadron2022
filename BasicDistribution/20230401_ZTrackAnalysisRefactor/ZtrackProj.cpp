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
void ZtrackProj_single(int binnum,float ptL,float ptH,float centL,float centH,float TptL,float TptH);

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
  gStyle->SetTitleSize(30, "xyz");
  gStyle->SetTitleOffset(1.5, "xyz");
  gStyle->SetLabelSize(24, "xyz");
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
TFile *file_sigDA;
TFile *file_bkgDA;

TFile *file_ppData;
TFile *file_sigMC0Sub;
TFile *file_sigMCgen0Sub;

const char *typeofdata = "20230531";
const char *typeofdatatext = "single muon";

void ZtrackProj_single(int binnum=40,float ptL=20,float ptH=2000,float centL=0,float centH=90,float TptL=0,float TptH=10000)
{

   std::cout<<"ptL = "<<ptL<<", ptH = "<<ptH<<", centL = "<<centL<<", centH = "<<centH<<", TptL = "<<TptL<<", TptH = "<<TptH<<std::endl;
   TCanvas *c = new TCanvas("c","",1400,800);

   std::cout<<"Getting histograms..."<<std::endl;

   std::string FolderName = Form("Plot_ZPT_%.0f_%.0f_Cent_%.0f_%.0f_TrackPT_%.2f_%.2f",ptL,ptH,centL,centH,TptL,TptH);
   std::replace(FolderName.begin(), FolderName.end(), '.', 'p');

   TH2D* hData_etaphi_1 = (TH2D*) file_sigDA->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_etaphi_1 = (TH2D*) file_sigMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hpp_etaphi_1 = (TH2D*) file_ppData->Get(Form("%s/HEtaPhi", FolderName.c_str()));

   hData_etaphi_1->SetName("hData_etaphi_1");
   hMC_etaphi_1->SetName("hMC_etaphi_1");
   hpp_etaphi_1->SetName("hpp_etaphi_1");

   TH2D* hMC_etaphi_rec = (TH2D*) file_sigMC0Sub->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_etaphi_gen = (TH2D*) file_sigMCgen0Sub->Get(Form("%s/HEtaPhi", FolderName.c_str()));

   hMC_etaphi_gen->SetName("hMC_etaphi_gen");
   hMC_etaphi_rec->SetName("hMC_etaphi_rec");

   TH2D* hData_bkg_etaphi_1 = (TH2D*) file_bkgDA->Get(Form("%s/HEtaPhi", FolderName.c_str()));
   TH2D* hMC_bkg_etaphi_1 = (TH2D*) file_bkgMC->Get(Form("%s/HEtaPhi", FolderName.c_str()));

   hData_bkg_etaphi_1->SetName("hData_bkg_etaphi_1");
   hMC_bkg_etaphi_1->SetName("hMC_bkg_etaphi_1");

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
   
   TNamed *npM_tN = (TNamed *) file_ppData->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nM_tNrec = (TNamed *) file_sigMC0Sub->Get(Form("%s/EntryCount",FolderName.c_str()));
   TNamed *nM_tNgen = (TNamed *) file_sigMCgen0Sub->Get(Form("%s/EntryCount",FolderName.c_str()));

   std::string sD_tN  = (std::string) nD_tN->GetTitle();
   std::string sM_tN  = (std::string) nM_tN->GetTitle();
   std::string sDb_tN = (std::string) nDb_tN->GetTitle();
   std::string sMb_tN = (std::string) nMb_tN->GetTitle();

   std::string spM_tN = (std::string) npM_tN->GetTitle();
   std::string sM_tNgen = (std::string) nM_tNgen->GetTitle();
   std::string sM_tNrec = (std::string) nM_tNrec->GetTitle();

   float tD_tN  = std::stof(sD_tN);
   float tM_tN  = std::stof(sM_tN);
   float tDb_tN = std::stof(sDb_tN);
   float tMb_tN = std::stof(sMb_tN);

   float tpM_tN = std::stof(spM_tN);
   float tM_tNgen  = std::stof(sM_tNgen);
   float tM_tNrec = std::stof(sM_tNrec);

   std::cout<<"tD_tN = "<<tD_tN<<std::endl;
   std::cout<<"tM_tN = "<<tM_tN<<std::endl;
   std::cout<<"tDb_tN = "<<tDb_tN<<std::endl;
   std::cout<<"tMb_tN = "<<tMb_tN<<std::endl;
   std::cout<<"tpM_tN = "<<tpM_tN<<std::endl;

   std::cout<<"tM_tNgen = "<<tM_tNgen<<std::endl;
   std::cout<<"tM_tNrec = "<<tM_tNrec<<std::endl;

   double bineta2d = 6.4/150, binphi2d = M_PI/75;

   hData_etaphi_1->Scale(1./tD_tN/bineta2d/binphi2d);
   hMC_etaphi_1->Scale(1./tM_tN/bineta2d/binphi2d);
   hData_bkg_etaphi_1->Scale(1./tDb_tN/bineta2d/binphi2d);
   hMC_bkg_etaphi_1->Scale(1./tMb_tN/bineta2d/binphi2d);
   
   hpp_etaphi_1->Scale(1./tpM_tN/bineta2d/binphi2d);
   hMC_etaphi_gen->Scale(1./tM_tNgen/bineta2d/binphi2d/1.305);
   hMC_etaphi_rec->Scale(1./tM_tNrec/bineta2d/binphi2d/2.1104);

   std::cout<<"Rebinning..."<<std::endl;

   hData_etaphi_1->Rebin2D(10,10);
   hData_bkg_etaphi_1->Rebin2D(10,10);
   hMC_etaphi_1->Rebin2D(10,10);
   hMC_bkg_etaphi_1->Rebin2D(10,10);

   hData_etaphi_1->Scale(1./100);
   hData_bkg_etaphi_1->Scale(1./100);
   hMC_etaphi_1->Scale(1./100);
   hMC_bkg_etaphi_1->Scale(1./100);

   hpp_etaphi_1->Rebin2D(4,4);
   hMC_etaphi_gen->Rebin2D(4,4);
   hMC_etaphi_rec->Rebin2D(4,4);

   hpp_etaphi_1->Scale(1./16);
   hMC_etaphi_gen->Scale(1./16);
   hMC_etaphi_rec->Scale(1./16);

   
   TH2D *hMC_sb_etaphi_1 = (TH2D*) hMC_etaphi_1->Clone("hMC_sb_etaphi_1");
   TH2D *hData_sb_etaphi_1 = (TH2D*) hData_etaphi_1->Clone("hData_sb_etaphi_1");

   hMC_sb_etaphi_1->Add(hMC_bkg_etaphi_1,-1);
   hData_sb_etaphi_1->Add(hData_bkg_etaphi_1,-1);

   std::cout<<"Drawing..."<<std::endl;

   if(TptL==0) TptL=TptL_min;

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


   TLatex *pt_p1 = new TLatex(0.1,0.97,"Projected at |#Delta#eta|<#pi");
   pt_p1->SetTextFont(42);
   pt_p1->SetTextSize(0.03);
   pt_p1->SetNDC(kTRUE);

   TLatex *pt_p2 = new TLatex(0.1,0.97,"Projected at |#Delta#eta|<#pi/2");
   pt_p2->SetTextFont(42);
   pt_p2->SetTextSize(0.03);
   pt_p2->SetNDC(kTRUE);

   TLatex *pt_p3 = new TLatex(0.1,0.97,"Projected at |#Delta#phi|<#pi/2");
   pt_p3->SetTextFont(42);
   pt_p3->SetTextSize(0.03);
   pt_p3->SetNDC(kTRUE);

   TLatex *pt_p4 = new TLatex(0.1,0.97,"Projected at |#Delta#phi|>#pi/2");
   pt_p4->SetTextFont(42);
   pt_p4->SetTextSize(0.03);
   pt_p4->SetNDC(kTRUE);


   // == Start drawing == //

   gSystem->Exec(Form("mkdir -p /eos/user/p/pchou/figs/track/%s/proj",typeofdata));

   c->Divide(2);
   c->cd(1);


   int MCNbinsX = hMC_sb_etaphi_1->GetNbinsX();
   int DataNbinsX = hData_sb_etaphi_1->GetNbinsX();
   int MCNbinsY = hMC_sb_etaphi_1->GetNbinsY();
   int DataNbinsY = hData_sb_etaphi_1->GetNbinsY();

   double Nmc_full = hMC_sb_etaphi_1->Integral(1,MCNbinsX,1,MCNbinsY,"width");
   double Ndata_full = hData_sb_etaphi_1->Integral(1,DataNbinsX,1,DataNbinsY,"width");

   TH1D* hMC_sb_projphi = (TH1D*) hMC_sb_etaphi_1->ProjectionY("hMC_sb_projphi",1,MCNbinsX);
   TH1D* hData_sb_projphi = (TH1D*) hData_sb_etaphi_1->ProjectionY("hData_sb_projphi",1,DataNbinsX);

   double Nmc_proj = hMC_sb_etaphi_1->Integral(1,MCNbinsX,1,MCNbinsY,"width");
   double Ndata_proj = hData_sb_etaphi_1->Integral(1,DataNbinsX,1,DataNbinsY,"width");

   hMC_sb_projphi->Scale(Nmc_full/Nmc_proj);
   hData_sb_projphi->Scale(Ndata_full/Ndata_proj);

   hMC_sb_projphi->Draw("EP");
   hMC_sb_projphi->GetXaxis()->SetTitle("Sig-Bkg MC #Delta#phi_{Z,track}");
   hMC_sb_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   c->cd(2);
   hData_sb_projphi->Draw("EP");
   hData_sb_projphi->GetXaxis()->SetTitle("Sig-Bkg Data #Delta#phi_{Z,track}");
   hData_sb_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   pt_p1->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   TH1D* hMC_sb_projphi_cent = (TH1D*) hMC_sb_etaphi_1->ProjectionY("hMC_sb_projphi_cent",(int) MCNbinsX/4,(int) 3*MCNbinsX/4);
   TH1D* hData_sb_projphi_cent = (TH1D*) hData_sb_etaphi_1->ProjectionY("hData_sb_projphi_cent",(int) DataNbinsX/4,(int) 3*DataNbinsX/4);

   Nmc_proj = hMC_sb_etaphi_1->Integral((int) MCNbinsX/4,(int) 3*MCNbinsX/4,1,MCNbinsY,"width");
   Ndata_proj = hData_sb_etaphi_1->Integral((int) DataNbinsX/4,(int) 3*DataNbinsX/4,1,DataNbinsY,"width");

   hMC_sb_projphi_cent->Scale(Nmc_full/Nmc_proj);
   hData_sb_projphi_cent->Scale(Ndata_full/Ndata_proj);

   hMC_sb_projphi_cent->Draw("EP");
   hMC_sb_projphi_cent->GetXaxis()->SetTitle("Sig-Bkg MC #Delta#phi_{Z,track} (projection in peak region)");
   hMC_sb_projphi_cent->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_projphi_cent->GetYaxis()->SetTitle("dN/d#Delta#phi");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   c->cd(2);
   hData_sb_projphi_cent->Draw("EP");
   hData_sb_projphi_cent->GetXaxis()->SetTitle("Sig-Bkg Data #Delta#phi_{Z,track} (projection in peak region)");
   hData_sb_projphi_cent->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_projphi_cent->GetYaxis()->SetTitle("dN/d#Delta#phi");

   pt_p2->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projphi_cent.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   TH1D* hMC_sb_projeta = (TH1D*) hMC_sb_etaphi_1->ProjectionX("hMC_sb_projeta",1,(int) MCNbinsY/2);
   TH1D* hData_sb_projeta = (TH1D*) hData_sb_etaphi_1->ProjectionX("hData_sb_projeta",1,(int) DataNbinsY/2);

   Nmc_proj = hMC_sb_etaphi_1->Integral(1,MCNbinsX,1,(int) MCNbinsY/2,"width");
   Ndata_proj = hData_sb_etaphi_1->Integral(1,MCNbinsX,1,(int) DataNbinsY/2,"width");

   hMC_sb_projeta->Scale(Nmc_full/Nmc_proj);
   hData_sb_projeta->Scale(Ndata_full/Ndata_proj);

   hMC_sb_projeta->Draw("EP");
   hMC_sb_projeta->GetXaxis()->SetTitle("Sig-Bkg MC #Delta#eta_{Z,track}");
   hMC_sb_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   c->cd(2);
   hData_sb_projeta->Draw("EP");
   hData_sb_projeta->GetXaxis()->SetTitle("Sig-Bkg Data #Delta#eta_{Z,track}");
   hData_sb_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   pt_p3->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->Divide(2);
   c->cd(1);

   TH1D* hMC_sb_projeta_peak = (TH1D*) hMC_sb_etaphi_1->ProjectionX("hMC_sb_projeta_peak",(int) MCNbinsY/2,MCNbinsY);
   TH1D* hData_sb_projeta_peak = (TH1D*) hData_sb_etaphi_1->ProjectionX("hData_sb_projeta_peak",(int) DataNbinsY/2,DataNbinsY);

   Nmc_proj = hMC_sb_etaphi_1->Integral(1,MCNbinsX,(int) MCNbinsY/2,MCNbinsY,"width");
   Ndata_proj = hData_sb_etaphi_1->Integral(1,MCNbinsX,(int) DataNbinsY/2,DataNbinsY,"width");

   hMC_sb_projeta_peak->Scale(Nmc_full/Nmc_proj);
   hData_sb_projeta_peak->Scale(Ndata_full/Ndata_proj);

   hMC_sb_projeta_peak->Draw("EP");
   hMC_sb_projeta_peak->GetXaxis()->SetTitle("Sig-Bkg MC #Delta#eta_{Z,track}");
   hMC_sb_projeta_peak->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_sb_projeta_peak->GetYaxis()->SetTitle("dN/d#Delta#eta");

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   c->cd(2);
   hData_sb_projeta_peak->Draw("EP");
   hData_sb_projeta_peak->GetXaxis()->SetTitle("Sig-Bkg Data #Delta#eta_{Z,track}");
   hData_sb_projeta_peak->GetXaxis()->SetNdivisions(50205,kFALSE);
   hData_sb_projeta_peak->GetYaxis()->SetTitle("dN/d#Delta#eta");

   pt_p4->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sb_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_Detaphi_projeta_peak.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   c->SetCanvasSize(800,800);

   int ppNbinsX = hpp_etaphi_1->GetNbinsX();
   int recNbinsX = hMC_etaphi_rec->GetNbinsX();
   int genNbinsX = hMC_etaphi_gen->GetNbinsX();
   int ppNbinsY  = hpp_etaphi_1->GetNbinsY();
   int recNbinsY = hMC_etaphi_rec->GetNbinsY();
   int genNbinsY = hMC_etaphi_gen->GetNbinsY();

   double  Npp_full = hpp_etaphi_1->Integral(1,ppNbinsX,1,ppNbinsY,"width");
   double Nrec_full = hMC_etaphi_rec->Integral(1,recNbinsX,1,recNbinsY,"width");
   double Ngen_full = hMC_etaphi_gen->Integral(1,genNbinsX,1,genNbinsY,"width");

   TH1D* hpp_projphi = (TH1D*) hpp_etaphi_1->ProjectionY("hpp_projphi",1,ppNbinsX);
   TH1D* hMC_rec_projphi = (TH1D*) hMC_etaphi_rec->ProjectionY("hMC_rec_projphi",1,recNbinsX);
   TH1D* hMC_gen_projphi = (TH1D*) hMC_etaphi_gen->ProjectionY("hMC_gen_projphi",1,genNbinsX);

   double  Npp_proj = hpp_etaphi_1->Integral(1,ppNbinsX,1,ppNbinsY,"width");
   double Nrec_proj = hMC_etaphi_rec->Integral(1,recNbinsX,1,recNbinsY,"width");
   double Ngen_proj = hMC_etaphi_gen->Integral(1,genNbinsX,1,genNbinsY,"width");

   hpp_projphi->Scale(Npp_full/Npp_proj);
   hMC_rec_projphi->Scale(Nrec_full/Nrec_proj);
   hMC_gen_projphi->Scale(Ngen_full/Ngen_proj);

   double max1 = hpp_projphi->GetMaximum();
   double max2 = hMC_rec_projphi->GetMaximum();
   double max3 = hMC_gen_projphi->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_rec_projphi->Draw("hist");
   else if(max1<max3 && max2<max3) hMC_gen_projphi->Draw("hist");
   else hpp_projphi->Draw("ep");
   hpp_projphi->Draw("ep same");
   hMC_rec_projphi->Draw("hist same");
   hMC_gen_projphi->Draw("hist same");

   hpp_projphi->GetXaxis()->SetTitle("#Delta#phi_{Z,track}");
   hpp_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   hMC_rec_projphi->GetXaxis()->SetTitle("#Delta#phi_{Z,track}");
   hMC_rec_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_rec_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   hMC_gen_projphi->GetXaxis()->SetTitle("#Delta#phi_{Z,track}");
   hMC_gen_projphi->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_gen_projphi->GetYaxis()->SetTitle("dN/d#Delta#phi");

   hpp_projphi->SetLineColor(kBlack);
   hMC_rec_projphi->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_gen_projphi->SetLineColor(TColor::GetColor("#377eb8"));//blue

   hpp_projphi->SetLineWidth(2);
   hMC_rec_projphi->SetLineWidth(2);
   hMC_gen_projphi->SetLineWidth(2);

   hpp_projphi->SetMarkerStyle(24);
   hpp_projphi->SetMarkerColor(kBlack);

   TLegend leg1(0.58,0.72,0.98,0.9);
   leg1.AddEntry(hpp_projphi ,"pp Data","ep");
   leg1.AddEntry(hMC_rec_projphi ,"PbPb Pythia MC RECO","l");
   leg1.AddEntry(hMC_gen_projphi ,"PbPb Pythia MC GEN","l");
   leg1.SetFillColorAlpha(kWhite,0);
   leg1.SetLineColor(kBlack);
   leg1.SetLineWidth(1);
   leg1.Draw();

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   pt_p1->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sub0_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_projphi.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   TH1D* hpp_projphi_cent = (TH1D*) hpp_etaphi_1->ProjectionY("hpp_projphi_cent",(int) ppNbinsX/4,(int) 3*ppNbinsX/4);
   TH1D* hMC_rec_projphi_cent = (TH1D*) hMC_etaphi_rec->ProjectionY("hMC_rec_projphi_cent",(int) recNbinsX/4,(int) 3*recNbinsX/4);
   TH1D* hMC_gen_projphi_cent = (TH1D*) hMC_etaphi_gen->ProjectionY("hMC_gen_projphi_cent",(int) genNbinsX/4,(int) 3*genNbinsX/4);

   Npp_proj  = hpp_etaphi_1->Integral((int) ppNbinsX/4,(int) 3*ppNbinsX/4,1,ppNbinsY,"width");
   Nrec_proj = hMC_etaphi_rec->Integral((int) recNbinsX/4,(int) 3*recNbinsX/4,1,recNbinsY,"width");
   Ngen_proj = hMC_etaphi_gen->Integral((int) genNbinsX/4,(int) 3*genNbinsX/4,1,genNbinsY,"width");

   hpp_projphi_cent->Scale(Npp_full/Npp_proj);
   hMC_rec_projphi_cent->Scale(Nrec_full/Nrec_proj);
   hMC_gen_projphi_cent->Scale(Ngen_full/Ngen_proj);

   max1 = hpp_projphi_cent->GetMaximum();
   max2 = hMC_rec_projphi_cent->GetMaximum();
   max3 = hMC_gen_projphi_cent->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_rec_projphi_cent->Draw("hist");
   else if(max1<max3 && max2<max3) hMC_gen_projphi_cent->Draw("hist");
   else hpp_projphi_cent->Draw("ep");
   hpp_projphi_cent->Draw("ep same");
   hMC_rec_projphi_cent->Draw("hist same");
   hMC_gen_projphi_cent->Draw("hist same");

   hpp_projphi_cent->GetXaxis()->SetTitle("#Delta#phi_{Z,track}");
   hpp_projphi_cent->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_projphi_cent->GetYaxis()->SetTitle("dN/d#Delta#phi");

   hMC_rec_projphi_cent->GetXaxis()->SetTitle("#Delta#phi_{Z,track}");
   hMC_rec_projphi_cent->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_rec_projphi_cent->GetYaxis()->SetTitle("dN/d#Delta#phi");

   hMC_gen_projphi_cent->GetXaxis()->SetTitle("#Delta#phi_{Z,track}");
   hMC_gen_projphi_cent->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_gen_projphi_cent->GetYaxis()->SetTitle("dN/d#Delta#phi");

   hpp_projphi_cent->SetLineColor(kBlack);
   hMC_rec_projphi_cent->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_gen_projphi_cent->SetLineColor(TColor::GetColor("#377eb8"));//blue

   hpp_projphi_cent->SetLineWidth(2);
   hMC_rec_projphi_cent->SetLineWidth(2);
   hMC_gen_projphi_cent->SetLineWidth(2);

   hpp_projphi_cent->SetMarkerStyle(24);
   hpp_projphi_cent->SetMarkerColor(kBlack);

   leg1.Draw();

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   pt_p2->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sub0_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_projphi_cent.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   TH1D* hpp_projeta = (TH1D*) hpp_etaphi_1->ProjectionX("hpp_projeta",1,(int) ppNbinsY/2);
   TH1D* hMC_rec_projeta = (TH1D*) hMC_etaphi_rec->ProjectionX("hMC_rec_projeta",1,(int) recNbinsY/2);
   TH1D* hMC_gen_projeta = (TH1D*) hMC_etaphi_gen->ProjectionX("hMC_gen_projeta",1,(int) genNbinsY/2);

   Npp_proj = hpp_etaphi_1->Integral(1,ppNbinsX,1,(int) ppNbinsY/2,"width");
   Nrec_proj = hMC_etaphi_rec->Integral(1,recNbinsX,1,(int) recNbinsY/2,"width");
   Ngen_proj = hMC_etaphi_gen->Integral(1,genNbinsX,1,(int) genNbinsY/2,"width");

   hpp_projeta->Scale(Npp_full/Npp_proj);
   hMC_rec_projeta->Scale(Nrec_full/Nrec_proj);
   hMC_gen_projeta->Scale(Ngen_full/Ngen_proj);

   max1 = hpp_projeta->GetMaximum();
   max2 = hMC_rec_projeta->GetMaximum();
   max3 = hMC_gen_projeta->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_rec_projeta->Draw("hist");
   else if(max1<max3 && max2<max3) hMC_gen_projeta->Draw("hist");
   else hpp_projeta->Draw("ep");
   hpp_projeta->Draw("ep same");
   hMC_rec_projeta->Draw("hist same");
   hMC_gen_projeta->Draw("hist same");

   hpp_projeta->GetXaxis()->SetTitle("#Delta#eta_{Z,track}");
   hpp_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   hMC_rec_projeta->GetXaxis()->SetTitle("#Delta#eta_{Z,track}");
   hMC_rec_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_rec_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   hMC_gen_projeta->GetXaxis()->SetTitle("#Delta#eta_{Z,track}");
   hMC_gen_projeta->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_gen_projeta->GetYaxis()->SetTitle("dN/d#Delta#eta");

   hpp_projeta->SetLineColor(kBlack);
   hMC_rec_projeta->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_gen_projeta->SetLineColor(TColor::GetColor("#377eb8"));//blue

   hpp_projeta->SetLineWidth(2);
   hMC_rec_projeta->SetLineWidth(2);
   hMC_gen_projeta->SetLineWidth(2);

   hpp_projeta->SetMarkerStyle(24);
   hpp_projeta->SetMarkerColor(kBlack);

   leg1.Draw();

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   pt_p3->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sub0_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_projeta.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();

   TH1D* hpp_projeta_peak = (TH1D*) hpp_etaphi_1->ProjectionX("hpp_projeta_peak",(int) ppNbinsY/2,ppNbinsY);
   TH1D* hMC_rec_projeta_peak = (TH1D*) hMC_etaphi_rec->ProjectionX("hMC_rec_projeta_peak",(int) ppNbinsY/2,ppNbinsY);
   TH1D* hMC_gen_projeta_peak = (TH1D*) hMC_etaphi_gen->ProjectionX("hMC_gen_projeta_peak",(int) ppNbinsY/2,ppNbinsY);

   Npp_proj = hpp_etaphi_1->Integral(1,ppNbinsX,(int) ppNbinsY/2,ppNbinsY,"width");
   Nrec_proj = hMC_etaphi_rec->Integral(1,recNbinsX,(int) ppNbinsY/2,ppNbinsY,"width");
   Ngen_proj = hMC_etaphi_gen->Integral(1,genNbinsX,(int) ppNbinsY/2,ppNbinsY,"width");

   hpp_projeta_peak->Scale(Npp_full/Npp_proj);
   hMC_rec_projeta_peak->Scale(Nrec_full/Nrec_proj);
   hMC_gen_projeta_peak->Scale(Ngen_full/Ngen_proj);

   max1 = hpp_projeta_peak->GetMaximum();
   max2 = hMC_rec_projeta_peak->GetMaximum();
   max3 = hMC_gen_projeta_peak->GetMaximum();
   
   if(max1<max2 && max3<max2) hMC_rec_projeta_peak->Draw("hist");
   else if(max1<max3 && max2<max3) hMC_gen_projeta_peak->Draw("hist");
   else hpp_projeta_peak->Draw("ep");
   hpp_projeta_peak->Draw("ep same");
   hMC_rec_projeta_peak->Draw("hist same");
   hMC_gen_projeta_peak->Draw("hist same");

   hpp_projeta_peak->GetXaxis()->SetTitle("#Delta#eta_{Z,track}");
   hpp_projeta_peak->GetXaxis()->SetNdivisions(50205,kFALSE);
   hpp_projeta_peak->GetYaxis()->SetTitle("dN/d#Delta#eta");

   hMC_rec_projeta_peak->GetXaxis()->SetTitle("#Delta#eta_{Z,track}");
   hMC_rec_projeta_peak->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_rec_projeta_peak->GetYaxis()->SetTitle("dN/d#Delta#eta");

   hMC_gen_projeta_peak->GetXaxis()->SetTitle("#Delta#eta_{Z,track}");
   hMC_gen_projeta_peak->GetXaxis()->SetNdivisions(50205,kFALSE);
   hMC_gen_projeta_peak->GetYaxis()->SetTitle("dN/d#Delta#eta");

   hpp_projeta_peak->SetLineColor(kBlack);
   hMC_rec_projeta_peak->SetLineColor(TColor::GetColor("#e41a1c"));//red
   hMC_gen_projeta_peak->SetLineColor(TColor::GetColor("#377eb8"));//blue

   hpp_projeta_peak->SetLineWidth(2);
   hMC_rec_projeta_peak->SetLineWidth(2);
   hMC_gen_projeta_peak->SetLineWidth(2);

   hpp_projeta_peak->SetMarkerStyle(24);
   hpp_projeta_peak->SetMarkerColor(kBlack);

   leg1.Draw();

   pt->Draw();
   pt2->Draw();
   pt3->Draw();

   pt_p4->Draw();

   c->SaveAs(Form("/eos/user/p/pchou/figs/track/%s/proj/Ztrack_%s_sub0_%.0f_%.0f_%.0f_%.0f_%.0f_%.0f_projeta_peak.png",typeofdata,typeofdata,ptL,ptH,centL,centH,TptL,TptH)); 
   c->Clear();



}

int main(int argc, char *argv[]){
//void ZtrackProj(){
   style();

   file_sigMC = TFile::Open("GraphMCSignal_v10-1.root","read");
   file_bkgMC = TFile::Open("GraphMCBackground_v10-1.root","read");
   file_sigDA = TFile::Open("GraphDataSignal_v10-1.root","read");
   file_bkgDA = TFile::Open("GraphDataBackground_v10-1.root","read");

   file_ppData       = TFile::Open("GraphPPMC0Sub_v11.root","read");
   file_sigMC0Sub    = TFile::Open("GraphMCSignal0Sub_v10-1.root","read");
   file_sigMCgen0Sub = TFile::Open("GraphMCSignalGen0Sub_v10-1.root","read");

   //ZtrackProj_single(40, 20, 2000,  0, 30,  4,    5);
   //ZtrackProj_single(40, 20, 2000,  0, 30,  5,    7);
   //ZtrackProj_single(40, 20, 2000,  0, 30,  7,   10);

   /*
   ZtrackProj_single(40, 30,   40,  0, 90,  0, 1000);
   ZtrackProj_single(40, 40,   60,  0, 90,  0, 1000);
   ZtrackProj_single(40, 60,   80,  0, 90,  0, 1000);
   ZtrackProj_single(40, 80,  100,  0, 90,  0, 1000);*/
   //ZtrackProj_single(40, 20, 2000,  0, 10,  0, 1000);
   //ZtrackProj_single(40, 20, 2000, 10, 30,  0, 1000);
   //ZtrackProj_single(40, 20, 2000, 30, 50,  0, 1000);
   //ZtrackProj_single(40, 20, 2000, 50, 90,  0, 1000);
   //ZtrackProj_single(40, 20, 2000,  0, 90,  1,    2);
   //ZtrackProj_single(40, 20, 2000,  0, 90,  2,    5);
   //ZtrackProj_single(40, 20, 2000,  0, 90,  5,   10);
   ZtrackProj_single(40, 20, 2000,  0, 90, 10,   20);
   ZtrackProj_single(40, 20, 2000,  0, 90, 20,   50);
   ZtrackProj_single(40, 20, 2000,  0, 90, 50,  100);

   ZtrackProj_single(40, 10, 2000,  0, 90,  2, 1000);

   //ZtrackProj_single(40, 20, 2000,  0, 10, 10,   20);

   //ZtrackProj_single(40, 20, 2000,  0, 10, 10,   20);
   //ZtrackProj_single(40, 20, 2000, 10, 30, 10,   20);
   //ZtrackProj_single(40, 20, 2000, 30, 50, 10,   20);
   //ZtrackProj_single(40, 20, 2000, 50, 90, 10,   20);

   file_sigMC->Close();
   file_bkgMC->Close();
   file_sigDA->Close();
   file_bkgDA->Close();

   file_ppData->Close();
   file_sigMC0Sub->Close();
   file_sigMCgen0Sub->Close();

   //return 0;

}