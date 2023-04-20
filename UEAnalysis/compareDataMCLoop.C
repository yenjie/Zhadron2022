#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCut.h>
#include <TLegend.h>
#include "Tree.C"
#include <TNtuple.h>
#include <iostream>


void getDphi(TTree *t, Tree &b, TH1D *h, double cutL, double cutH, double trackCutL, double trackCutH)
{
    int nZ=0;
    h->Sumw2();
    cout <<"start "<<t<<endl;
    for (long i=0;i<t->GetEntries();i++) {
       bool foundZ=false;
       t->GetEntry(i);
       if (i%100000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
       if (b.hiBin>20) continue;
       
       for (int j=0;j<b.zMass->size();j++) {
          //cout <<(*b.zMass)[j]<<" "<<(*b.zPt)[j]<<endl;
          if ((*b.zMass)[j]<60) continue;
          if ((*b.zMass)[j]>120) continue;
          if (fabs((*b.zEta)[j])>2) continue;
	  if ((*b.zPt)[j]<cutL) continue;
	  if ((*b.zPt)[j]>cutH) continue;
	  foundZ=true;
	  nZ++;
	  break;
       }
       
       if (foundZ) {
          //cout <<"foundZ";
          for (long j=0;j<b.trackDphi->size();j++) {
	     if ((*b.trackMuTagged)[j]) continue;  
	     if ((*b.trackPt)[j]>trackCutH) continue;  
	     if ((*b.trackPt)[j]<trackCutL) continue;  
	     h->Fill(fabs((*b.trackDphi)[j]),(*b.trackWeight)[j]);
//	     h->Fill(fabs((*b.trackDphi)[j]));
	  }
       }
       
    }
    cout <<"done"<<endl;
    h->Scale(1./((double) nZ));
}


void compareDataMCLoop(double ZptCutL=120, double ZptCutH=200, double ptL=1, double ptH=4)
{
   TFile *infData = new TFile("HISingleMuon_20230414.root");
   TFile *infMC = new TFile("PbPbMC_20230414_small.root");


   TTree *tMC = (TTree*) infMC->Get("Tree");
   TTree *tData = (TTree*) infData->Get("Tree");

   Tree bMC(tMC);
   Tree bData(tData);
   


   TFile *outf = new TFile(Form("output/output_%.1f_%.1f_%.0f_%.0f.root",ptL,ptH,ZptCutL,ZptCutH),"recreate");
   TNtuple *nt = new TNtuple("nt","","zPtL:zPtH:trackPtL:trackPtH:mcY:dataY:mcYD:dataYD");
   
   TH1D *hMC = new TH1D("hMC","",10,0,3.141592653);
   TH1D *hMC2 = new TH1D("hMC2","",10,0,3.141592653);
   TH1D *hData = new TH1D("hData","",10,0,3.141592653);
   TH1D *hData2 = new TH1D("hData2","",10,0,3.141592653);

      cout <<"Projecting MC...Cut1"<<endl;
   getDphi(tMC,bMC,hMC,5,10,ptL,ptH);
   hMC->Draw();
      cout <<"Projecting MC...Cut2"<<endl;
   getDphi(tMC,bMC,hMC2,ZptCutL,ZptCutH,ptL,ptH);
      cout <<"Projecting Data...Cut1"<<endl;
   getDphi(tData,bData,hData,5,10,ptL,ptH);
      cout <<"Projecting Data...Cut1"<<endl;
   getDphi(tData,bData,hData2,ZptCutL,ZptCutH,ptL,ptH);


   hMC->Write();
   hMC2->Write();
   hData->Write();
   hData2->Write();
   TCanvas *c = new TCanvas("c","",800,800);



   hMC2->SetLineColor(2);
   hMC2->SetMarkerColor(2);
   
   hMC2->Add(hMC,-1);
   hData2->Add(hData,-1);
   hMC2->SetAxisRange(-20,60,"Y");

   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
   leg->SetBorderSize(0);
   leg->AddEntry(hData2,"Data","pl");
   leg->AddEntry(hMC2,"MC","pl");
   leg->AddEntry(hMC2,Form("%.1f<Track p_{T}<%.1f",ptL,ptH),"");
   leg->AddEntry(hMC2,Form("%.0f<Z p_{T}<%.0f",ZptCutL,ZptCutH),"");
   hMC2->SetXTitle("#Delta#phi(Z,track)");
   hMC2->SetYTitle("#Delta N_{ch} / Event");
   hMC2->Draw();
   leg->Draw();
   hData2->Draw("same");
   
   double mcY= hMC2->Integral(1,5);
   double dataY= hData2->Integral(1,5);
   double mcYD= hMC2->Integral(1,5)-hMC2->Integral(6,10);
   double dataYD= hData2->Integral(1,5)-hData2->Integral(6,10);
   
   nt->Fill(ZptCutL,ZptCutH,ptL,ptH,mcY,dataY,mcYD,dataYD);
   
   c->SaveAs(Form("output/Z_%.1f_%.1f_%.0f_%.0f.pdf",ptL,ptH,ZptCutL,ZptCutH));
   c->SaveAs(Form("output/Z_%.1f_%.1f_%.0f_%.0f.gif",ptL,ptH,ZptCutL,ZptCutH));
   
   nt->Write();
//   outf->Close();

}
