#include <TFile.h>
#include <TCanvas.h>
#include <TH1D.h>

void view(string infName)
{
    TFile *inf = new TFile(infName.c_str());
    TH1D *hMC2 = (TH1D*)inf->Get("hMC2");
    TH1D *hData2 = (TH1D*)inf->Get("hData2");
    

     hData2->Add(hMC2,-1);
     hData2->SetYTitle("Data-MC");
     hData2->Draw();

}
