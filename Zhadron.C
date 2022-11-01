#include "HiForest.h"
#include <TFile.h>
#include <TTree.h>
#include <TNtuple.h>

class ZhadronData
{
   public:
   vector<double> Zmass;
   vector<double> Zeta;
   vector<double> Zphi;
   int hiBin;
   
   ZhadronData(){};
   ~ZhadronData(){};
   void setBranch(TTree *t){
      t->Branch("Zmass",&Zmass);
      t->Branch("Zeta",&Zeta);
      t->Branch("Zphi",&Zphi);
      t->Branch("hiBin",&hiBin);
   };
   
   void clear() {
      Zmass.clear();
      Zeta.clear();
      Zphi.clear();
   }
   
};

void Zhadron(string
infname="DYJetsToLL_MLL-50_TuneCP5_HydjetDrumMB_5p02TeV-amcatnloFXFX-pythia8_merged.root", string outfname="output.root")
{
   HiForest f(infname.c_str());
   f.doGenParticle=0;
   f.doPbPbTracks=0;
   f.doMuTree=1;
   f.doHiTree=1;
   f.Init();
   
   TFile *outfile = new TFile(outfname.c_str(),"recreate");
   
   TNtuple *nt = new TNtuple("ntZ","Z tree","mass:pt:eta");
   TTree *t = new TTree("t","tree");
   
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
	data.Zmass.push_back(f.muTree.Di_mass[ipair]);
	data.Zeta.push_back(f.muTree.Di_eta[ipair]);
	data.Zeta.push_back(f.muTree.Di_phi[ipair]);
	data.hiBin=f.hi.hiBin;
	nt->Fill(f.muTree.Di_mass[ipair],f.muTree.Di_pt[ipair], f.muTree.Di_eta[ipair], f.muTree.Di_phi[ipair]);
     }
     t->Fill();
     data.clear();
   }
   
   nt->Write();
   outfile->Write();
   outfile->Close();      

}

