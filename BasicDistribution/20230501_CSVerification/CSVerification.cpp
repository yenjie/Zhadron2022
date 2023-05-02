#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TNtuple.h"
#include "TH2D.h"
#include "TMath.h"
#include "TSystem.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TLorentzVector.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "CommonFunctions.h"
#include "ProgressBar.h"
#include "CustomAssert.h"
#include "JetCorrector.h"

#include "trackingEfficiency2017pp.h"
#include "trackingEfficiency2018PbPb.h"

int main(int argc, char *argv[]);
double GetHFSum(PFTreeMessenger *M);

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   string InputFileName          = CL.Get("Input");
   string OutputFileName         = CL.Get("Output");
   string PFTreeName             = CL.Get("PFTree", "particleFlowAnalyser/pftree");
   int Entry                     = CL.GetInt("Entry", 0);

   // Get the input file
   TFile InputFile(InputFileName.c_str());
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("Tree", "Tree");

   double Eta, Phi, PT;
   bool Type;

   Tree.Branch("Eta", &Eta, "Eta/D");
   Tree.Branch("Phi", &Phi, "Phi/D");
   Tree.Branch("PT", &PT, "PT/D");
   Tree.Branch("Type", &Type, "Type/O");

   // Setup all the messengers.
   HiEventTreeMessenger     MEvent(InputFile);
   PFTreeMessenger          MPF(InputFile, PFTreeName);
   RhoTreeMessenger         MRho(InputFile, "hiPuRhoAnalyzer/t");

   int EntryCount = MEvent.GetEntries();
   if(Entry >= EntryCount)
      Entry = 0;

   MEvent.GetEntry(Entry);
   MPF.GetEntry(Entry);
   MRho.GetEntry(Entry);

   cout << MPF.ID->size() << endl;
   cout << MRho.Rho << endl;
   cout << MRho.Rho ->at(10) << endl;

   // Now we do the constituent subtraction
   vector<double> CSPFEta, CSPFPhi, CSPFPT;
   vector<double> PFEta, PFPhi, PFPT;
   for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
   {
      if(MPF.Eta->at(iPF) < -3 || MPF.Eta->at(iPF) > 3)
         continue;
      CSPFEta.push_back(MPF.Eta->at(iPF));
      CSPFPhi.push_back(MPF.Phi->at(iPF));
      CSPFPT.push_back(MPF.PT->at(iPF));
      PFEta.push_back(MPF.Eta->at(iPF));
      PFPhi.push_back(MPF.Phi->at(iPF));
      PFPT.push_back(MPF.PT->at(iPF));
   }
   ConstituentSubtraction(CSPFEta, CSPFPhi, CSPFPT, MRho.EtaMin, MRho.EtaMax, MRho.Rho, 3.14, 3.0);

   cout << "Event information:" << endl;
   cout << "   hiBin = " << MEvent.hiBin << endl;

   for(int iPF = 0; iPF < PFEta.size(); iPF++)
   {
      Eta = PFEta[iPF];
      Phi = PFPhi[iPF];
      PT = PFPT[iPF];
      Type = true;
      Tree.Fill();
   }
   for(int iPF = 0; iPF < CSPFEta.size(); iPF++)
   {
      Eta = CSPFEta[iPF];
      Phi = CSPFPhi[iPF];
      PT = CSPFPT[iPF];
      Type = false;
      Tree.Fill();
   }

   Tree.Write();

   OutputFile.Close();
   InputFile.Close();

   return 0;
}


