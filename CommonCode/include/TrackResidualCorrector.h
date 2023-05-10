#include <iostream>

#include "TFile.h"
#include "TH1D.h"

class TrackResidualCorrector
{
public:
   TrackResidualCorrector(std::string filename = "ResidualCorrector_20230508/totalCorrection.root")
   {
      f = new TFile(filename.c_str());
      hPtCorrTotal  = (TH1D *)f->Get("hPtCorrTotal");
      hEtaCorrTotal = (TH1D *)f->Get("hEtaCorrTotal");
      hPhiCorrTotal = (TH1D *)f->Get("hPhiCorrTotal");
   }

   ~TrackResidualCorrector()
   {
      f->Close();
      delete f;
   }

   double GetCorrectionFactor(double pt, double eta, double phi)
   {
      if(phi < 0)
         phi += 2 * M_PI;

      int bin_pt = hPtCorrTotal->GetXaxis()->FindBin(pt);
      int bin_eta = hEtaCorrTotal->GetXaxis()->FindBin(eta);
      int bin_phi = hPhiCorrTotal->GetXaxis()->FindBin(phi);
      double corr = hPtCorrTotal->GetBinContent(bin_pt) *
         hEtaCorrTotal->GetBinContent(bin_eta) *
         hPhiCorrTotal->GetBinContent(bin_phi);

      if(isnan(corr))
      {
         std::cerr << "Error! 0 efficiency! " << bin_pt << " " << bin_eta << " " << bin_phi << std::endl;
         corr = 1;
      }

      return corr;
   }

private:
   TFile* f;
   TH1D *hPtCorrTotal;
   TH1D *hEtaCorrTotal;
   TH1D *hPhiCorrTotal;
};




