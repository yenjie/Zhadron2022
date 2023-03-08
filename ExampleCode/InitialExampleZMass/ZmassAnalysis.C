#include <TFile.h>
#include <TTree.h>
#include <TH1D.h>
#include <TF1.h>
#include <TMath.h>
#include <TROOT.h>
#include <cmath>

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

TH1D* ZmassAnalysis(double ptL=0,double ptH=2000,int centL=0,int centH=200)
{
   TH1D *h = new TH1D("h","",100,0,1);
   TFile *infData = new TFile("output_doubleMu_221107.root");
   TFile *infMC = new TFile("outputMC.root");
   
   TCanvas *c = new TCanvas("c","",800,800);

   TTree *tData = (TTree*)infData->Get("t");
   TTree *tMC = (TTree*)infMC->Get("t");
   
   TH1D *hData = new TH1D("hData","",40,81.2,101.2);
   TH1D *hDataSame = new TH1D("hDataSame","",40,81.2,101.2);
   TH1D *hMC = new TH1D("hMC","",40,81.2,101.2);
   TH1D *hMCSame = new TH1D("hMCSame","",40,81.2,101.2);
   
   tData->Draw("zMass>>hData",Form("zPt>%f&&zPt<%f&&hiBin>=%d&&hiBin<%d",ptL,ptH,centL,centH));
   tData->Draw("zMass>>hDataSame",Form("zPt>%f&&zPt<%f&&hiBin>=%d&&hiBin<%d",ptL,ptH,centL,centH));

   hData->Sumw2();
   hDataSame->Sumw2();

   hDataSame->SetLineColor(2);
   hDataSame->SetMarkerColor(2);


   tMC->Draw("zMass>>hMC",Form("zPt>%f&&zPt<%f&&hiBin>=%d&&hiBin<%d",ptL,ptH,centL,centH));
   tMC->Draw("zMass>>hMCSame",Form("zPt>%f&&zPt<%f&&hiBin>=%d&&hiBin<%d",ptL,ptH,centL,centH));

   hMC->Sumw2();
   hMCSame->Sumw2();
   hMC->SetMarkerStyle(24);
   hMCSame->SetMarkerStyle(24);
   hMCSame->SetLineColor(2);
   hMCSame->SetMarkerColor(2);

   
//   hData->Draw("e");
//   hMC->Draw("e same");
 //  hDataSame->Draw("same");
//   hMCSame->Draw("same");
      
   hData->Scale(1./hData->GetEntries());
   hMC->Scale(1./hMC->GetEntries());
   hMC->Draw();
   hMC->SetXTitle("M_{#mu#mu} (GeV)");
   hData->Draw("same"); 
   hMC->SetLineColor(2);
   hMC->SetMarkerColor(2);
   
//   TF1 *f = new TF1("f","[0]+[1]*x+[2]*TMath::BreitWigner(x, [3], [4])");
   TF1 *f = new TF1("f",bwfun,81.2,101.2,7);
   f->SetParNames("Mean","Width","Area","GSigma","BkgArea","ExpCont","ExpShift");
   f->SetParameters(91,4.6,3,0.1,0,0,0,0);
   f->SetLineStyle(2);
   f->SetLineColor(1);
   
 //  TF1 *f2 = new TF1("f2","[0]+[1]*x+[2]*TMath::BreitWigner(x, [3], [4])");
//   f2->SetParameters(0,0,1,91.2,1);

   TF1 *f2 = new TF1("f2",bwfun,81.2,101.2,7);
   f2->SetParNames("Mean","Width","Area","GSigma","BkgArea","ExpCont","ExpShift");
   f2->SetParameters(91,4.6,3,0.1,0,0,0,0);
   f2->SetLineStyle(2);
   f2->SetLineColor(2);
   

   hData->Fit("f","LL");
   hData->Fit("f","");
   hData->Fit("f","LL m");
   hData->Fit("f","");
   hData->Fit("f","LL m");
   hData->Fit("f","");
   hData->Fit("f","");
   hData->Fit("f","");
   hData->Fit("f","");
 
   hMC->Fit("f2","LL m");
   hMC->Fit("f2","");
   hMC->Fit("f2","LL");
   hMC->Fit("f2","");
   hMC->Fit("f2","LL m");
   hMC->Fit("f2","");
   hMC->Fit("f2","");
   hMC->Fit("f2","");
   hMC->Fit("f2","");
  
   h->SetBinContent(1,f->GetParameter(0));
   h->SetBinContent(2,f->GetParError(0));
   h->SetBinContent(3,f2->GetParameter(0));
   h->SetBinContent(4,f2->GetParError(0));

   return h;
}

void loop()
{
   TH1D *hDataMass = new TH1D("hDataMass","",5,0,100);
   TH1D *hMCMass = new TH1D("hMCMass","",5,0,100);
   
   for (int i=1;i<=hDataMass->GetNbinsX();i++)
   {
      TH1D *h = ZmassAnalysis(hDataMass->GetBinLowEdge(i),hDataMass->GetBinLowEdge(i+1));
      hDataMass->SetBinContent(i,h->GetBinContent(1));
      hDataMass->SetBinError(i,h->GetBinContent(2));
      hMCMass->SetBinContent(i,h->GetBinContent(3));
      hMCMass->SetBinError(i,h->GetBinContent(4));
   }
   
   hDataMass->SetXTitle("Z p_{T} (GeV)");
   hDataMass->Draw("e");
   hMCMass->SetLineColor(2);
   hMCMass->SetMarkerColor(2);
   hMCMass->Draw("e same");
}  


void loopHiBin()
{
   TH1D *hDataMass = new TH1D("hDataMass","",10,0,200);
   TH1D *hMCMass = new TH1D("hMCMass","",10,0,200);
   
   for (int i=1;i<=hDataMass->GetNbinsX();i++)
   {
      TH1D *h = ZmassAnalysis(0,200,hDataMass->GetBinLowEdge(i),hDataMass->GetBinLowEdge(i+1));
      hDataMass->SetBinContent(i,h->GetBinContent(1));
      hDataMass->SetBinError(i,h->GetBinContent(2));
      hMCMass->SetBinContent(i,h->GetBinContent(3));
      hMCMass->SetBinError(i,h->GetBinContent(4));
   }
   
   hDataMass->SetXTitle("Centrality Bin");
   hDataMass->Draw("e");
   hMCMass->SetLineColor(2);
   hMCMass->SetMarkerColor(2);
   hMCMass->Draw("e same");
}  



