#include <iostream>
using namespace std;

#include "TFile.h"
#include "TGraphAsymmErrors.h"

int main(int argc, char *argv[]);
void PrintGraph(TFile &F, string Name);

int main(int argc, char *argv[])
{
   TFile File("effs_tnp_pp_5TeV_2017.root");
   
   cout << endl;
   cout << endl;
   cout << "SF" << endl;
   cout << endl;

   PrintGraph(File, "TightID/ScaleFactor");
   PrintGraph(File, "TightID_PFIsoTight/ScaleFactor");
   PrintGraph(File, "L3Mu12/ScaleFactor");
   PrintGraph(File, "L3Mu12_PFIsoTight/ScaleFactor");
   
   cout << endl;
   cout << endl;
   cout << "data" << endl;
   cout << endl;
   
   PrintGraph(File, "TightID/eff_data");
   PrintGraph(File, "TightID_PFIsoTight/eff_data");
   PrintGraph(File, "L3Mu12/eff_data");
   PrintGraph(File, "L3Mu12_PFIsoTight/eff_data");
   
   cout << endl;
   cout << endl;
   cout << "MC" << endl;
   cout << endl;

   PrintGraph(File, "TightID/eff_MC");
   PrintGraph(File, "TightID_PFIsoTight/eff_MC");
   PrintGraph(File, "L3Mu12/eff_MC");
   PrintGraph(File, "L3Mu12_PFIsoTight/eff_MC");

   File.Close();

   return 0;
}

void PrintGraph(TFile &F, string Name)
{
   cout << "Printing content of the graph with name \"" << Name << "\":" << endl;
   cout << endl;

   TGraphAsymmErrors *G = (TGraphAsymmErrors *)F.Get(Name.c_str());

   if(G != nullptr)
   {
      int N = G->GetN();

      cout << "Nominal" << endl;
      for(int i = 0; i < N; i++)
      {
         double X, Y;
         G->GetPoint(i, X, Y);
         double EXL = G->GetErrorXlow(i);
         double EXH = G->GetErrorXhigh(i);
         double EYL = G->GetErrorYlow(i);
         double EYH = G->GetErrorYhigh(i);

         cout << "   if(eta < " << X + EXH << " && eta >= " << X - EXL << ")   return " << Y << ";" << endl;
      }
      cout << endl;
      
      cout << "Down" << endl;
      for(int i = 0; i < N; i++)
      {
         double X, Y;
         G->GetPoint(i, X, Y);
         double EXL = G->GetErrorXlow(i);
         double EXH = G->GetErrorXhigh(i);
         double EYL = G->GetErrorYlow(i);
         double EYH = G->GetErrorYhigh(i);

         cout << "   if(eta < " << X + EXH << " && eta >= " << X - EXL << ")   return " << Y - EYL << ";" << endl;
      }
      cout << endl;
     
      cout << "Up" << endl;
      for(int i = 0; i < N; i++)
      {
         double X, Y;
         G->GetPoint(i, X, Y);
         double EXL = G->GetErrorXlow(i);
         double EXH = G->GetErrorXhigh(i);
         double EYL = G->GetErrorYlow(i);
         double EYH = G->GetErrorYhigh(i);

         cout << "   if(eta < " << X + EXH << " && eta >= " << X - EXL << ")   return " << Y + EYH << ";" << endl;
      }
      cout << endl;
   }

   cout << endl;
}



