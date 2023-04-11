#include <iostream>
#include <vector>
using namespace std;

#include "TFile.h"
#include "TTree.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "CommonFunctions.h"
#include "ProgressBar.h"

#define MAX 1000

int main(int argc, char *argv[])
{
   CommandLine CL(argc, argv);

   vector<string> InputFileNames = CL.GetStringVector("Input");
   string OutputFileName         = CL.Get("Output");
   double Fraction               = CL.GetDouble("Fraction", 1.00);
   
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");
   TTree Tree("Tree", "Tree with energy sums");

   int NEta = 14;
   double EtaMin[]    = {-5, -4, -3, -2, -1, 0, 1, 2, 3, 4, -2.4, 0, -5, 3};
   double EtaMax[]    = {-4, -3, -2, -1, 0, 1, 2, 3, 4, 5, 0, 2.4, -3, 5};
   double PTSum[MAX]  = {0};
   double ESum[MAX]   = {0};

   Tree.Branch("NEta",   &NEta,   "NEta/I");
   Tree.Branch("EtaMin", &EtaMin, "EtaMin[NEta]/D");
   Tree.Branch("EtaMax", &EtaMax, "EtaMax[NEta]/D");
   Tree.Branch("PTSum",  &PTSum,  "PTSum[NEta]/D");
   Tree.Branch("ESum",   &ESum,   "ESum[NEta]/D");

   for(string InputFileName : InputFileNames)
   {
      TFile InputFile(InputFileName.c_str());

      string PFTreeName = "particleFlowAnalyser/pftree";
      if(InputFile.Get(PFTreeName.c_str()) == nullptr)
         PFTreeName = "pfcandAnalyzer/pfTree";
      if(InputFile.Get(PFTreeName.c_str()) == nullptr)   // neither AOD nor MiniAOD name works!
         continue;

      HiEventTreeMessenger MEvent(InputFile);
      PFTreeMessenger MPF(InputFile, PFTreeName.c_str());

      int EntryCount = MEvent.Tree->GetEntries() * Fraction;
      for(int iE = 0; iE < EntryCount; iE++)
      {
         MEvent.GetEntry(iE);
         MPF.GetEntry(iE);

         for(int i = 0; i < NEta; i++)
         {
            PTSum[i] = 0;
            ESum[i] = 0;
         }

         for(int iPF = 0; iPF < MPF.ID->size(); iPF++)
         {
            // TODO: potentially remove muons from Z.  For now it shouldn't matter

            for(int i = 0; i < NEta; i++)
            {
               if(MPF.Eta->at(iPF) < EtaMin[i])
                  continue;
               if(MPF.Eta->at(iPF) > EtaMax[i])
                  continue;

               PTSum[i] = PTSum[i] + MPF.PT->at(iPF);
               ESum[i] = ESum[i] + MPF.E->at(iPF);
            }
         }

         Tree.Fill();
      }
   }

   OutputFile.cd();
   Tree.Write();
   OutputFile.Close();

   return 0;
}



