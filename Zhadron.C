#include "HiForest.h"
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>
#include <TH2D.h>
#include <TMath.h>

double dphi(double phi1,double phi2)
{
 double a=phi1-phi2;
 while (a<-TMath::Pi()) a+=2*TMath::Pi();
 while (a>TMath::Pi()) a-=2*TMath::Pi();
   
// if (a<-TMath::Pi()/2) a=2*TMath::Pi()+a;
 return a;
}


class ZhadronData
{
   public:
   vector<double> zMass;
   vector<double> zEta;
   vector<double> zPhi;
   vector<double> zPt;
   vector<double> trackDphi;
   vector<double> trackPt;
   vector<double> trackDeta;
   int hiBin;
   
   ZhadronData(){};
   ~ZhadronData(){};
   void setBranch(TTree *t){
      t->Branch("zMass",&zMass);
      t->Branch("zEta",&zEta);
      t->Branch("zPhi",&zPhi);
      t->Branch("zPt",&zPt);
      t->Branch("trackDphi",&trackDphi);
      t->Branch("trackDeta",&trackDeta);
      t->Branch("trackPt",&trackPt);
      t->Branch("hiBin",&hiBin);
   };
   
   void clear() {
      zMass.clear();
      zEta.clear();
      zPhi.clear();
      zPt.clear();
      trackDphi.clear();
      trackPt.clear();
      trackDeta.clear();
   }
   
};

void Zhadron(string
infname="DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8_merged.root", string outfname="output.root")
{
   HiForest f(infname.c_str());
   f.doGenParticle=0;
   f.doPbPbTracks=1;
   f.doMuTree=1;
   f.doHiTree=1;
   f.Init();
   
   TFile *outfile = new TFile(outfname.c_str(),"recreate");
   
   TNtuple *nt = new TNtuple("ntZ","Z tree","mass:pt:eta");
   TTree *t = new TTree("t","tree");
   
   TH2D *h2D = new TH2D("h2D","",100,-6,6,100,-3.14159,3.14159);
   TH2D *h2Dmix = new TH2D("h2Dmix","",100,-6,6,100,-3.14159,3.14159);
   
   ZhadronData data;
   data.setBranch(t);
   data.clear();
  
   
   for (int i=0;i<f.GetEntries();i++)
   {
     f.GetEntry(i);
     if (i%1000==0) cout <<i<<"/"<<f.GetEntries()<<endl;
     for (int ipair=0;ipair<f.muTree.Di_npair;ipair++) {
        //cout <<ipair<<" "<<f.muTree.Di_mass[ipair]<<endl;
	if (f.muTree.Di_charge1[ipair]==f.muTree.Di_charge2[ipair]) continue;
	if (fabs(f.muTree.Di_eta1[ipair])>2.4) continue;
	if (fabs(f.muTree.Di_eta2[ipair])>2.4) continue;
	if (fabs(f.muTree.Di_pt1[ipair])<20) continue;
	if (fabs(f.muTree.Di_pt2[ipair])<20) continue;
	data.zMass.push_back(f.muTree.Di_mass[ipair]);
	data.zEta.push_back(f.muTree.Di_eta[ipair]);
	data.zPhi.push_back(f.muTree.Di_phi[ipair]);
	data.zPt.push_back(f.muTree.Di_pt[ipair]);
	data.hiBin=f.hi.hiBin;
	nt->Fill(f.muTree.Di_mass[ipair],f.muTree.Di_pt[ipair], f.muTree.Di_eta[ipair], f.muTree.Di_phi[ipair]);
     }
     
     if (data.zMass.size()>0&&data.zPt.at(0)>30) {
        for (int itrack=0;itrack<f.tracks.trkPt->size();itrack++) {
	   if (!f.tracks.highPurity) continue;
           double deltaPhi = dphi(data.zPhi.at(0),f.tracks.trkPhi->at(itrack));
	   double deltaEta = fabs(data.zEta.at(0)-f.tracks.trkEta->at(itrack));
	   h2D->Fill(deltaEta,deltaPhi,0.25);
	   h2D->Fill(-deltaEta,deltaPhi,0.25);
	   h2D->Fill(-deltaEta,-deltaPhi,0.25);
	   h2D->Fill(deltaEta,-deltaPhi,0.25);
	   data.trackDphi.push_back(deltaPhi);
	   data.trackDeta.push_back(deltaEta);
	   data.trackPt.push_back(f.tracks.trkPt->at(itrack));
	}
	f.GetEntry(i+1);
	if (i+1==f.GetEntries()) f.GetEntry(0);
        for (int itrack=0;itrack<f.tracks.trkPt->size();itrack++) {
	   if (!f.tracks.highPurity) continue;
           double deltaPhi = dphi(data.zPhi.at(0),f.tracks.trkPhi->at(itrack));
	   double deltaEta = fabs(data.zEta.at(0)-f.tracks.trkEta->at(itrack));
	   h2Dmix->Fill(deltaEta,deltaPhi,0.25);
	   h2Dmix->Fill(-deltaEta,deltaPhi,0.25);
	   h2Dmix->Fill(-deltaEta,-deltaPhi,0.25);
	   h2Dmix->Fill(deltaEta,-deltaPhi,0.25);
//	   data.trackDphi.push_back(deltaPhi);
//	   data.trackDeta.push_back(deltaEta);
//	   data.trackPt.push_back(f.tracks.trkPt->at(itrack));
	}
     }
     t->Fill();
     data.clear();
   }

   h2D->Write();   
   nt->Write();
   outfile->Write();
   outfile->Close();      

}

