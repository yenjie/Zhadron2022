#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCut.h>
#include <TLegend.h>
#include <Tree.C>

#include <iostream>

void compareDataMC(TCut cut ="zPt[0]<20&&zPt[0]>5&&zMass[0]>60&&zMass[0]<120&&hiBin<60", 
                   TCut cut2="zPt[0]>120&&zMass[0]>60&&zMass[0]<120&&hiBin<60", bool dataOnly=false)
{
   TFile *infData = new TFile("HISingleMuon_20230414.root");
   TFile *infMC = new TFile("PbPbMC_20230414_small.root");
   TH1D *hMC = new TH1D("hMC","",10,0,3.141592653);
   TH1D *hMC2 = new TH1D("hMC2","",10,0,3.141592653);
   TH1D *hData = new TH1D("hData","",10,0,3.141592653);
   TH1D *hData2 = new TH1D("hData2","",10,0,3.141592653);
//   TH1D *h = new TH1D("h","",100,0,20000);
//   TH1D *h2 = new TH1D("h2","",100,0,20000);
   
   
   
   
   TTree *tMC = (TTree*) infMC->Get("Tree");
   TTree *tData = (TTree*) infData->Get("Tree");
   TCanvas *c = new TCanvas("c","",800,800);
   hMC->Sumw2();
   hMC2->Sumw2();
   hData->Sumw2();
   hData2->Sumw2();


   Tree bMC(tMC);
   Tree bData;

   
   TCut trackCut ="!trackMuTagged&&trackPt>0&&trackPt<40000&&abs(trackDeta)<2";
   if (!dataOnly) {
      cout <<"Projecting MC...Cut1"<<endl;
      tMC->Draw("trackDphi>>hMC","trackWeight"*(cut&&trackCut));
      cout <<"Projecting MC...Cut 2"<<endl;
      tMC->Draw("trackDphi>>hMC2","trackWeight"*(cut2&&trackCut));
   }
   cout <<"Projecting Data...Cut1"<<endl;
   tData->Draw("trackDphi>>hData","trackWeight"*(cut&&trackCut));
   tData->Draw("trackDphi>>hData2","trackWeight"*(cut2&&trackCut));

   hMC->Scale(1./tMC->GetEntries(cut));
   hMC2->Scale(1./tMC->GetEntries(cut2));
   hData->Scale(1./tData->GetEntries(cut));
   hData2->Scale(1./tData->GetEntries(cut2));

   hMC2->SetLineColor(2);
   hMC2->SetMarkerColor(2);
   
   hMC2->Add(hMC,-1);
   hData2->Add(hData,-1);
   hMC2->SetAxisRange(-20,30,"Y");

   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
   leg->SetBorderSize(0);
   leg->AddEntry(hData2,"Data","pl");
   leg->AddEntry(hMC2,"MC","pl");
   hMC2->SetXTitle("#Delta#phi(Z,track)");
   hMC2->SetYTitle("#Delta N_{ch} / Event");
   hMC2->Draw();
   leg->Draw();
   hData2->Draw("same");

}
