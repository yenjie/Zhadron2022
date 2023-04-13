{
   Tree->SetAlias("rawDPhi", "(trackDphi-maxOppositeWTADPhi)");
   Tree->SetAlias("DPhi", "(rawDPhi+2*3.14159*(rawDPhi<-3.14159)-2*3.14159*(rawDPhi>3.14159))");
   Tree->SetAlias("DEta", "trackDeta-maxOppositeWTADEta");

   TH1D H1("H1", ";#Delta#eta;", 40, 0, 5);
   TH1D H2("H2", ";#Delta#eta;", 40, 0, 5);

   Tree->Draw("abs(DEta)>>H1", "(zPt[0] > 30 && trackPt < 2 && trackMuTagged == 0 && abs(DPhi) > 2.5 && hiBin < 20) * trackWeight", "");
   Tree->Draw("abs(DEta)>>H2", "(zPt[0] > 30 && trackPt < 2 && trackMuTagged == 0 && abs(DPhi) > 2.5 && hiBin >= 100 && hiBin < 180) * trackWeight", "");
   // Tree->Draw("abs(trackDphi)>>H1", "(zPt[0] > 5 && zPt[0] < 20 && trackPt > 0 && trackMuTagged == 0 && abs(trackDeta) < 1 && hiBin < 20) * trackWeight", "");
   // Tree->Draw("abs(trackDphi)>>H2", "(zPt[0] > 100 && trackPt > 0 && trackMuTagged == 0 && abs(trackDeta) < 1 && hiBin < 20) * trackWeight", "");

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

   H2.DrawNormalized("");
   H1.DrawNormalized("same");

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   // Legend.AddEntry(&H1, "p_{T}^{Z} = 5-20 GeV", "pl");
   // Legend.AddEntry(&H2, "p_{T}^{Z} > 100 GeV", "pl");
   Legend.AddEntry(&H1, "0-10%", "pl");
   Legend.AddEntry(&H2, "50-90%", "pl");
   Legend.Draw();
}
