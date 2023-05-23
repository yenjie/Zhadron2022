#include <TFile.h>
#include <TCanvas.h>
#include <TTree.h>
#include <TH1D.h>
#include <TH2D.h>
#include <TH3D.h>
#include <TCut.h>
#include <TLegend.h>
#include <TNtuple.h>

#include "Tree.C"
#include <iostream>

#include "utilities.h"
#include "ResidualCorrection.h"


//============================================================//
// Define analysis parameters
//============================================================//

class Parameters {
public:
  Parameters(double zPtCutL, double zPtCutH, double ptCutL, double ptCutH,
             int hiBinL = 0, int hiBinH = 200, bool mix = false, bool isGen = false,
             double scaleFactor = 1.0)
    : zPtCutL(zPtCutL), zPtCutH(zPtCutH), ptCutL(ptCutL), ptCutH(ptCutH),
      hiBinL(hiBinL), hiBinH(hiBinH), mix(mix), isGen(isGen), scaleFactor(scaleFactor) {}

  double zPtCutL;      // Lower limit of zpt
  double zPtCutH;      // Upper limit of zpt
  double ptCutL;       // Lower limit of pt
  double ptCutH;       // Upper limit of pt
  int hiBinL;          // Lower limit of hiBin
  int hiBinH;          // Upper limit of hiBin
  bool mix;            // Mix flag
  bool isGen;          // isGen flag
  double scaleFactor;  // Scale factor

  void printParameters() const {
    cout << "zPtCutL: " << zPtCutL << endl;
    cout << "zPtCutH: " << zPtCutH << endl;
    cout << "ptCutL: " << ptCutL << endl;
    cout << "ptCutH: " << ptCutH << endl;
    cout << "hiBinL: " << hiBinL << endl;
    cout << "hiBinH: " << hiBinH << endl;
    cout << "mix: " << mix << endl;
    cout << "isGen: " << isGen << endl;
    if (mix) cout <<"Event mixing!"<<endl;
    cout << "scaleFactor: " << scaleFactor << endl;
  }
};

//============================================================//
// Turn off all branches and only turn on the relevant ones
//============================================================//
void smartBranch(TTree* fChain)
{
   // Turn off all branches
   fChain->SetBranchStatus("*",0);

   // Turn on necessary branches
   fChain->SetBranchStatus("zMass",1);
   fChain->SetBranchStatus("zEta",1);
   fChain->SetBranchStatus("zPhi",1);
   fChain->SetBranchStatus("zPt",1);
   fChain->SetBranchStatus("hiBin",1);
   fChain->SetBranchStatus("trackPt",1);
   fChain->SetBranchStatus("trackMuTagged",1);
   fChain->SetBranchStatus("trackDeta",1);
   fChain->SetBranchStatus("trackDphi",1);
   fChain->SetBranchStatus("NCollWeight",1);
   fChain->SetBranchStatus("trackWeight",1);
   fChain->SetBranchStatus("ZWeight",1);
   fChain->SetBranchStatus("trackResidualWeight",1);
}

//======= eventSelection =====================================//
// Check if the event mass eventSelection criteria
// ZPtCutL < zPt < ZPtCutH
// hiBinL , hiBin < hiBinH
//============================================================//
bool eventSelection(Tree &b, const Parameters& par)
{
   bool foundZ = false;
   if (b.hiBin< par.hiBinL) return 0;
   if (b.hiBin>=par.hiBinH) return 0;
   if (b.zMass->size()==0) return 0;
   if ((*b.zMass)[0]<60) return 0;
   if ((*b.zMass)[0]>120) return 0;
   if (fabs((*b.zEta)[0])>2) return 0;
   if ((*b.zPt)[0]<par.zPtCutL) return 0;
   if ((*b.zPt)[0]>par.zPtCutH) return 0;

   foundZ=1;   
   return foundZ;
}

//======= trackSelection =====================================//
// Check if the track pass selection criteria
// ZPtCutL < zPt < ZPtCutH
// hiBinL , hiBin < hiBinH
//============================================================//
bool trackSelection(Tree &b, Parameters par, int j) {
    if ((*b.trackMuTagged)[j]) return false;  
    if ((*b.trackPt)[j]>par.ptCutH) return false;  
    if ((*b.trackPt)[j]<par.ptCutL) return false;  
    //if (fabs((*b.trackDeta)[j])>4) return false;
    return true;
}


//============================================================//
// Z hadron dphi calculation
//============================================================//
void getDphi(TTree *t, Tree &b, TH2D *h, const Parameters& par)
{
    double nZ=0;
    h->Sumw2();
    par.printParameters();
    
    for (unsigned long i=0;i<t->GetEntries()*par.scaleFactor;i++) {
       bool foundZ=false;
       t->GetEntry(i);
       if (i%100000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
       
       // check if the event pass the selection criteria
       if (eventSelection(b, par)) {
          double zPhi = (*b.zPhi)[0];
          double zEta = (*b.zEta)[0];	  
	  /*	  
	  int iMax = findIndexOfLargestValue(b.trackPt);
	  
	  zPhi = (*b.trackDphi)[iMax]+(*b.zPhi)[0];
	  zEta = (*b.trackDeta)[iMax]+(*b.zEta)[0];
	*/  
	  double mix_i = i;
	  for (unsigned int nMix=0;nMix<(9*par.mix+1);nMix++) {
   	     bool foundMix = 0;
	     nZ+=(b.NCollWeight);    // Ncoll reweighting in the event level.
	     if (par.mix) {
	        while (foundMix==0) {
	           mix_i = (mix_i+1);
		   if (mix_i>=t->GetEntries()) mix_i=0;
		   if (i==mix_i)  break;
	           t->GetEntry(mix_i);
		   if (eventSelection(b, par)) foundMix=1;
	        }
	     }
	  
	     if (foundMix==0&&par.mix){
	        cout <<"Can not find a mixed event!!! Event = "<<i<<endl;
	        break;
	     }
	  
	     for (unsigned long j=0;j<b.trackDphi->size();j++) {
                if (!trackSelection(b, par, j)) continue;  
                double trackPhi = (*b.trackDphi)[j]+(*b.zPhi)[0];
	        if (trackPhi<0) trackPhi+=2*M_PI;
	        double trackEta = (*b.trackDeta)[j]+(*b.zEta)[0];
                //double residualCorr = isGen ? 1 : cfg.GetCorrectionFactor((*b.trackPt)[j], trackEta, trackPhi);
		double trackDphi = DeltaPhi((*b.trackDphi)[j]+(*b.zPhi)[0], zPhi);
	        double trackDeta = fabs((*b.trackDeta)[j]+(*b.zEta)[0]- zEta);
		double weight = (b.NCollWeight)*(*b.trackWeight)[j]*(*b.trackResidualWeight)[j]*(b.ZWeight);
		
		h->Fill(trackDeta,trackDphi,weight);
 	        h->Fill(-trackDeta,trackDphi,weight);
 	        h->Fill(trackDeta,-trackDphi,weight);
 	        h->Fill(-trackDeta,-trackDphi,weight);
	     }
          }
       }
    }
    cout <<"done"<<nZ<<endl;
    h->Scale(1./((double) nZ));
}


void get3D(TTree *t, Tree &b, TH3D *h, const Parameters& par)
{
    double nZ=0;
    h->Sumw2();
    cout <<"3D Histogram";
    par.printParameters();
    
    for (unsigned long i=0;i<t->GetEntries();i++) {
       bool foundZ=false;
       t->GetEntry(i);
       if (i%100000==0) cout <<i<<" / "<<t->GetEntries()<<endl;
       
       // check if the event pass the selection criteria
       if (eventSelection(b, par)) {
          nZ+=(b.NCollWeight);
	  for (long j=0;j<b.trackDphi->size();j++) {
             if (!trackSelection(b, par, j)) continue;  
	     double trackPhi = (*b.trackDphi)[j]+(*b.zPhi)[0];
	     if (trackPhi<0) trackPhi+=2*M_PI;
	     double trackEta = (*b.trackDeta)[j]+(*b.zEta)[0];
	     double residualCorr = 1;
	     //if (!isGen) residualCorr = cfg.GetCorrectionFactor((*b.trackPt)[j],trackEta,trackPhi);
	     //cout <<isGen<<" "<<residualCorr<<" "<<cfg.GetCorrectionFactor((*b.trackPt)[j],trackEta,trackPhi)<<endl;
	     h->Fill((*b.trackPt)[j], trackEta, trackPhi,(b.NCollWeight)*(*b.trackWeight)[j]*residualCorr);
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


  ~DataAnalyzer() {
    deleteHistograms();
    closeFile();
  }
  
  

  void analyze(Parameters& par) {
    smartBranch(t);
    par.mix=false;
    hCut2 = project2D(par);
    hCut2->SetName(Form("h%s_2",title.c_str()));
    par.mix=true;
    hCut2mix = project2D(par);
    hCut2mix->SetName(Form("hmix%s_2",title.c_str()));
    hCut2mix->Draw();
    hDiff2D = (TH2D*) hCut2->Clone(Form("hDiff2D%s",title.c_str()));
    hDiff2D->Add(hCut2mix,-1);
    hDiff = (TH1D*) hDiff2D->ProjectionY(Form("hDiff%s",title.c_str()));
    
  }

  void analyze3D(Parameters& par) {
    smartBranch(t);
    h3D = project3D(par);
    h3D->SetName(Form("h3D%s_%d_%d",title.c_str(),par.hiBinL,par.hiBinH));
  }

  void writeHistograms(TFile* outf) {
    outf->cd();
    smartWrite(hCut1);
    smartWrite(hCut2);
    smartWrite(hCut2mix);
    smartWrite(hDiff);
    smartWrite(hDiff2D);
    smartWrite(h3D);
  }

  TH2D* getCut1() { return hCut1; }
  TH2D* getCut2() { return hCut2; }


  TFile *inf;
  TTree *t;
  Tree b;
  TH2D *hCut1=0, *hCut2=0;
  TH2D *hCut2mix=0;
  TH2D *hDiff2D=0;
  TH1D *hDiff=0;
  TH3D *h3D=0;
  string title;

  TH2D* project2D(const Parameters& par) {
    TH2D *h = new TH2D("h", "", 20,-4,4, 20, -M_PI, M_PI);
    getDphi(t, b, h, par);
    return h;
  }
  
    TH3D* project3D(const Parameters& par) {

    TH3D* h3D = new TH3D("h3D", "Histogram Title; p_{T} (GeV/c); #eta; #phi", 50,0,10,50,-2.4,2.4,50, 0,2*M_PI);

    get3D(t, b, h3D, par);
    return h3D;
  }
  
  private:
  void deleteHistograms() {
    delete hCut1;
    delete hCut2;
    delete hCut2mix;
    delete hDiff2D;
    delete hDiff;
    delete h3D;
  }

  void closeFile() {
    inf->Close();
  }
};



//============================================================//
// Main analysis
//============================================================//

int compareDataMCLoop(double ZptCutL=20, double ZptCutH=200, double ptL=1, double ptH=4, double hiBinL=0, double
hiBinH=20)
{
   // Initialize a Parameters object with default values
   Parameters par(ZptCutL, ZptCutH, ptL, ptH, hiBinL, hiBinH);
   par.isGen=0;
   par.mix=0;
   par.scaleFactor=0.01;

   //Analyze Data
   DataAnalyzer analyzerData("sample/HISingleMuon_V8.root", "Tree", "Data");
   analyzerData.analyze(par);

   TFile *outf = new TFile(Form("result/output_data_%.1f_%.1f_%.0f_%.0f.root",ptL,ptH,ZptCutL,ZptCutH),"recreate");
   analyzerData.writeHistograms(outf);

   // Analyze MC
   DataAnalyzer analyzerMC("sample/PbPbMC_V8.root", "Tree","MC");
   analyzerMC.analyze(par);
   analyzerMC.writeHistograms(outf);

   // Analyze MC Gen level
   DataAnalyzer analyzerMCGen("sample/PbPbMCGen_V8.root", "Tree","MCGen");
   par.isGen=1;
   analyzerMCGen.analyze(par);


   analyzerMCGen.writeHistograms(outf);
   
   cout <<"done!"<<endl;   

   // Plotting
   outf->cd();
   TCanvas *c = new TCanvas("c","",800,800);
   analyzerMC.hDiff->SetLineColor(2);
   analyzerMC.hDiff->SetMarkerColor(2);
   analyzerMCGen.hDiff->SetLineColor(4);
   analyzerMCGen.hDiff->SetMarkerColor(4);
   
   analyzerMC.hDiff->SetAxisRange(-6,6,"Y");
   analyzerMC.hDiff->SetAxisRange(0,3.2,"X");

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
      

/*
   double mcY= analyzerMC.hDiff->Integral(1,5);
   double dataY= analyzerData.hDiff->Integral(1,5);
   double mcYD= analyzerMC.hDiff->Integral(1,5)-analyzerMC.hDiff->Integral(6,10);
   double dataYD= analyzerData.hDiff->Integral(1,5)-analyzerData.hDiff->Integral(6,10);
   */
//   nt->Fill(ZptCutL,ZptCutH,ptL,ptH,mcY,dataY,mcYD,dataYD);
   c->SaveAs(Form("result/Z_%.1f_%.1f_%.0f_%.0f.pdf",ptL,ptH,ZptCutL,ZptCutH));
   c->SaveAs(Form("result/Z_%.1f_%.1f_%.0f_%.0f.gif",ptL,ptH,ZptCutL,ZptCutH));
   c->Write();
//   nt->Write();
//   analyzerMC.h3D->ProjectionX()->Draw();
   cout <<outf->GetName()<<endl;
   return 1;
}



//============================================================//
// Efficiency Study
//============================================================//

int efficiencyStudy(double ZptCutL=5, double ZptCutH=200, double ptL=0, double ptH=10)
{
    // Initialize a Parameters object with default values
   Parameters par(ZptCutL, ZptCutH, ptL, ptH);

   double hiBin[5] = {0, 20, 60, 100, 200};
  
   for (unsigned int i=0;i<4;i++) {
      par.hiBinL=hiBin[i];
      par.hiBinH=hiBin[i+1];
   TFile *outf = new TFile(Form("result/output_data_%.1f_%.1f_%.0f_%.0f_%d_%d.root",ptL,ptH,ZptCutL,ZptCutH,par.hiBinL,par.hiBinH),"recreate");
      DataAnalyzer* analyzerMC = new DataAnalyzer("PbPbMC_V9.root", "Tree",Form("MC", hiBin[i], hiBin[i+1]));
      analyzerMC->analyze3D(par);
      cout <<"good"<<endl;
      analyzerMC->writeHistograms(outf);
      delete analyzerMC;

      DataAnalyzer* analyzerMCGen = new DataAnalyzer("PbPbMCGen_V9.root", "Tree",Form("MCGen", hiBin[i], hiBin[i+1]));
      analyzerMCGen->analyze3D(par);
      analyzerMCGen->writeHistograms(outf);
      
      delete analyzerMCGen;
      outf->Close();
   }
   return 1;
}

