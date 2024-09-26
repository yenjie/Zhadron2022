{
   TFile F1("AllData.root");
   TFile F2("AllMC0.root");

   TTree *T1 = (TTree *)F1.Get("Tree");
   TTree *T2 = (TTree *)F2.Get("Tree");

   T1->SetAlias("rawDPhi", "(trackDphi-maxOppositeWTADPhi)");
   T1->SetAlias("DPhi", "(rawDPhi+2*3.14159*(rawDPhi<-3.14159)-2*3.14159*(rawDPhi>3.14159))");
   T1->SetAlias("DEta", "trackDeta-maxOppositeWTADEta");

   T2->SetAlias("rawDPhi", "(trackDphi-maxOppositeWTADPhi)");
   T2->SetAlias("DPhi", "(rawDPhi+2*3.14159*(rawDPhi<-3.14159)-2*3.14159*(rawDPhi>3.14159))");
   T2->SetAlias("DEta", "trackDeta-maxOppositeWTADEta");

   TH1D H1("H1", ";#Delta#phi;", 20, 0, 3.14159);
   TH1D H2("H2", ";#Delta#phi;", 20, 0, 3.14159);

   T1->Draw("abs(DEta)>>H1", "NCollWeight * (zPt[0] > 50 && trackPt < 1.5 && trackMuTagged == 0 && abs(DPhi) > 2. && hiBin < 20) * trackWeight", "");
   T2->Draw("abs(DEta)>>H2", "NCollWeight * (zPt[0] > 50 && trackPt < 1.5 && trackMuTagged == 0 && abs(DPhi) > 2. && hiBin < 20) * trackWeight", "");
   // T1->Draw("abs(trackDphi)>>H1", "(zPt[0] > 60 && trackPt < 3 && trackMuTagged == 0 && zMass[0] > 60) * trackWeight * NCollWeight", "");
   // T2->Draw("abs(trackDphi)>>H2", "(zPt[0] > 60 && trackPt < 3 && trackMuTagged == 0 && zMass[0] > 60) * trackWeight * NCollWeight", "");

   H1.SetStats(0);
   H2.SetStats(0);

   H1.SetMarkerStyle(20);
   H1.SetMarkerColor(kRed);
   H1.SetLineWidth(2);
   H1.SetLineColor(kRed);
   
   H2.SetMarkerStyle(20);
   H2.SetMarkerColor(kBlue);
   H2.SetLineWidth(2);
   H2.SetLineColor(kBlue);

   H1.DrawNormalized("");
   H2.DrawNormalized("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   // Legend.AddEntry(&H1, "p_{T}^{Z} = 5-20 GeV", "pl");
   // Legend.AddEntry(&H2, "p_{T}^{Z} > 100 GeV", "pl");
   Legend.AddEntry(&H1, "Data", "pl");
   Legend.AddEntry(&H2, "MC", "pl");
   Legend.Draw();
}
