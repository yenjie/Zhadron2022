#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1D.h>
#include <TCut.h>
#include <TLegend.h>
#include "Tree.C"
#include <TNtuple.h>
#include <iostream>

double PhiRangeSymmetric(double Phi)
{
   if(Phi < -M_PI)   Phi = Phi + 2 * M_PI;
   if(Phi > +M_PI)   Phi = Phi - 2 * M_PI;
   return Phi;
}

double DeltaPhi(double Phi1, double Phi2)
{
   return PhiRangeSymmetric(Phi1 - Phi2);
}




//======= eventSelection =====================================//
// Check if the event mass eventSelection criteria
// ZPtCutL < zPt < ZPtCutH
// hiBinL , hiBin < hiBinH
//============================================================//

bool eventSelection(Tree &b, double zPtCutL=30, double zPtCutH=200, int hiBinL=0, int hiBinH=60)
{
   bool foundZ = false;
   if (b.hiBin<hiBinL) return 0;
   if (b.hiBin>=hiBinH) return 0;

   /*
   for (int j=0;j<b.zMass->size();j++) {
      if ((*b.zMass)[j]<60) continue;
      if ((*b.zMass)[j]>120) continue;
      if (fabs((*b.zEta)[j])>2) continue;
      if ((*b.zPt)[j]<zPtCutL) continue;
      if ((*b.zPt)[j]>zPtCutH) continue;

      foundZ=true;
      break;
   }
   */
   if (b.zMass->size()==0) return 0;
   if ((*b.zMass)[0]<60) return 0;
   if ((*b.zMass)[0]>120) return 0;
   if (fabs((*b.zEta)[0])>2) return 0;
   if ((*b.zPt)[0]<zPtCutL) return 0;
   if ((*b.zPt)[0]>zPtCutH) return 0;

   foundZ=1;   
   return foundZ;
}

//============================================================//
// Z hadron dphi calculation
//============================================================//

void getDphi(TTree *t, Tree &b, TH1D *h, double zPtCutL, double zPtCutH, double trackCutL, double trackCutH, int hiBinL=0, int hiBinH=60, bool mix= false)
{
    double nZ=0;
    h->Sumw2();
    cout <<"start "<<t<<endl;
    cout <<"zPtCutL "<<zPtCutL<<endl;
    cout <<"zPtCutH "<<zPtCutH<<endl;
    cout <<"trackCutL "<<trackCutL<<endl;
    cout <<"trackCutH "<<trackCutH<<endl;
    cout <<"hiBinL "<<hiBinL<<endl;
    cout <<"hiBinH "<<hiBinH<<endl;
    if (mix) cout <<"mixing!"<<endl;
    for (long i=0;i<t->GetEntries();i++) {
       bool foundZ=false;
       t->GetEntry(i);
       if (i%100000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
       
       // check if the event pass the selection criteria
       if (eventSelection(b, zPtCutL, zPtCutH, hiBinL, hiBinH)) {
          nZ+=(b.NCollWeight);
          double zPhi = (*b.zPhi)[0];
	  
	  double mix_i = i;
	  bool foundMix = 0;
	     
	  if (mix) {
	     while (foundMix==0) {
	        mix_i = (mix_i+1);
		if (mix_i>=t->GetEntries()) mix_i=0;
		if (i==mix_i)  break;
	        t->GetEntry(mix_i);
		if (eventSelection(b, zPtCutL, zPtCutH, hiBinL, hiBinH)) foundMix=1;
	     }
	  }
	  
	  if (foundMix==0&&mix){
	     cout <<"Can not find a mixed event!!! Event = "<<i<<endl;
	     break;
	  }
	  
	  for (long j=0;j<b.trackDphi->size();j++) {
	     if ((*b.trackMuTagged)[j]) continue;  
	     if ((*b.trackPt)[j]>trackCutH) continue;  
	     if ((*b.trackPt)[j]<trackCutL) continue;  
	     if (fabs((*b.trackDeta)[j])>4) continue;
	     double trackDphi = DeltaPhi((*b.trackDphi)[j]+(*b.zPhi)[0], zPhi);
//	     cout <<trackDphi<<" "<<(*b.trackDphi)[j]<<endl;
 	     h->Fill(trackDphi,(b.NCollWeight)*(*b.trackWeight)[j]);
	  }
       }
       
    }
    cout <<"done"<<nZ<<endl;
    h->Scale(1./((double) nZ));
}


class DataAnalyzer {
public:
  DataAnalyzer(const char* filename, const char* treename, const char *mytitle = "Data") :
    inf(new TFile(filename)), t((TTree*) inf->Get(treename)), b(t), title(mytitle) {}

  void analyze(double ptL, double ptH, double ZptCutL, double ZptCutH, int hiBinL=0, int hiBinH=60) {
    hCut1 = projectDphi(5, 10, ptL, ptH, hiBinL, hiBinH, 0);
    hCut1->SetName(Form("h%s_1",title.c_str()));
    hCut2 = projectDphi(ZptCutL, ZptCutH, ptL, ptH, hiBinL, hiBinH, 0);
    hCut2->SetName(Form("h%s_2",title.c_str()));
    hCut2mix = projectDphi(ZptCutL, ZptCutH, ptL, ptH, hiBinL, hiBinH, 1);
    hCut2mix->SetName(Form("hmix%s_2",title.c_str()));
    hCut2mix->Draw();
    hDiff = (TH1D*) hCut2->Clone(Form("hDiff%s",title.c_str()));
    hDiff->Add(hCut2mix,-1);
  }

  void writeHistograms(TFile* outf) {
    outf->cd();
    hCut1->Write();
    hCut2->Write();
    hCut2mix->Write();
    hDiff->Write();
  }

  TH1D* getCut1() { return hCut1; }
  TH1D* getCut2() { return hCut2; }


  TFile *inf;
  TTree *t;
  Tree b;
  TH1D *hCut1, *hCut2;
  TH1D *hCut2mix;
  TH1D *hDiff;
  string title;

  TH1D* projectDphi(double zptL, double zptH, double ptL, double ptH,  int hiBinL=0, int hiBinH=60, bool mix=0) {
    TH1D *h = new TH1D("", "", 10, 0, 3.141592653);
    getDphi(t, b, h, zptL, zptH, ptL, ptH, hiBinL, hiBinH, mix);
    return h;
  }
};



void compareDataMCLoop(double ZptCutL=120, double ZptCutH=200, double ptL=1, double ptH=4)
{

   //Analyze Data
   DataAnalyzer analyzerData("HISingleMuon_20230428.root", "Tree", "Data");
   analyzerData.analyze(ptL, ptH, ZptCutL, ZptCutH);

   TFile *outf = new TFile(Form("output/output_data_%.1f_%.1f_%.0f_%.0f.root",ptL,ptH,ZptCutL,ZptCutH),"recreate");
   cout <<outf->GetName()<<endl;
   analyzerData.writeHistograms(outf);

   // Analyze MC
   DataAnalyzer analyzerMC("PbPbMC_small.root", "Tree","MC");
   analyzerMC.analyze(ptL, ptH, ZptCutL, ZptCutH);
   analyzerMC.writeHistograms(outf);

   // Analyze MC Gen level
   DataAnalyzer analyzerMCGen("PbPbMCGen_small.root", "Tree","MCGen");
   analyzerMCGen.analyze(ptL, ptH, ZptCutL, ZptCutH);


   analyzerMCGen.writeHistograms(outf);
   
   
   
   

   // Plotting

   TCanvas *c = new TCanvas("c","",800,800);
   analyzerMC.hDiff->SetLineColor(2);
   analyzerMC.hDiff->SetMarkerColor(2);
   analyzerMCGen.hDiff->SetLineColor(4);
   analyzerMCGen.hDiff->SetMarkerColor(4);
   
   analyzerMC.hDiff->SetAxisRange(-20,100,"Y");

   TLegend *leg = new TLegend(0.5,0.7,0.9,0.9);
   leg->SetBorderSize(0);
   leg->AddEntry(analyzerData.hDiff,"Data","pl");
   leg->AddEntry(analyzerMC.hDiff,"MC","pl");
   leg->AddEntry(analyzerMCGen.hDiff,"MC Gen","pl");
   leg->AddEntry(analyzerMC.hDiff,Form("%.1f<Track p_{T}<%.1f",ptL,ptH),"");
   leg->AddEntry(analyzerMC.hDiff,Form("%.0f<Z p_{T}<%.0f",ZptCutL,ZptCutH),"");
   analyzerMC.hDiff->SetXTitle("#Delta#phi(Z,track)");
   analyzerMC.hDiff->SetYTitle("#Delta N_{ch} / Event");
   analyzerMC.hDiff->Draw();
   analyzerMCGen.hDiff->Draw("hist same");
   leg->Draw();
   analyzerData.hDiff->Draw("same");
   
   double mcY= analyzerMC.hDiff->Integral(1,5);
   double dataY= analyzerData.hDiff->Integral(1,5);
   double mcYD= analyzerMC.hDiff->Integral(1,5)-analyzerMC.hDiff->Integral(6,10);
   double dataYD= analyzerData.hDiff->Integral(1,5)-analyzerData.hDiff->Integral(6,10);
   
//   nt->Fill(ZptCutL,ZptCutH,ptL,ptH,mcY,dataY,mcYD,dataYD);
   
   c->SaveAs(Form("output/Z_%.1f_%.1f_%.0f_%.0f.pdf",ptL,ptH,ZptCutL,ZptCutH));
   c->SaveAs(Form("output/Z_%.1f_%.1f_%.0f_%.0f.gif",ptL,ptH,ZptCutL,ZptCutH));
   c->Write();
   
//   nt->Write();

}
