{
   Tree->SetAlias("rawDPhi", "(trackDphi-maxOppositeWTADPhi)");
   Tree->SetAlias("DPhi", "(rawDPhi+2*3.1415926535*(rawDPhi<-3.1415926535)-2*3.1415926535*(rawDPhi>3.1415926535))");
   Tree->SetAlias("DPhiCorr", "(rawDPhi+2*3.14159*(rawDPhi<-1.57159)-2*3.14159*(rawDPhi>4.71239))/3.14159");
   Tree->SetAlias("DEta", "(trackDeta-maxOppositeWTADEta)");

   // TH1D H1("H1", ";#Delta#phi;N_{ch} / event", 40, 0, 3.14159);
   // TH1D H2("H2", ";#Delta#phi;N_{ch} / event", 40, 0, 3.14159);
   TH1D H1("H1", ";#Delta#eta;N_{ch} / event", 40, 0, 5);
   TH1D H2("H2", ";#Delta#eta;N_{ch} / event", 40, 0, 5);

   string Cut1 = "NCollWeight * (zMass[0] > 60 && zPt[0] > 60 && hiBin < 20)";
   string Cut2 = "NCollWeight * (zMass[0] > 60 && zPt[0] > 5 && zPt[0] < 20 && hiBin < 20)";

   Tree->Draw("abs(DEta)>>H1", Form("(%s) * (trackMuTagged == 0 && abs(DPhi) > 2) * trackWeight", Cut1.c_str()), "");
   Tree->Draw("abs(DEta)>>H2", Form("(%s) * (trackMuTagged == 0 && abs(DPhi) > 2) * trackWeight", Cut2.c_str()), "");
   // Tree->Draw("abs(trackDphi)>>H1", "(zPt[0] > 5 && zPt[0] < 20 && trackPt > 0 && trackMuTagged == 0 && abs(trackDeta) < 1 && hiBin < 20) * trackWeight", "");
   // Tree->Draw("abs(trackDphi)>>H2", "(zPt[0] > 100 && trackPt > 0 && trackMuTagged == 0 && abs(trackDeta) < 1 && hiBin < 20) * trackWeight", "");

   double N1 = Tree->GetEntries(Cut1.c_str());
   double N2 = Tree->GetEntries(Cut2.c_str());

   H1.Scale(1 / N1);
   H2.Scale(1 / N2);

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

   if(H1.GetMaximum() > H2.GetMaximum())
   {
      H1.Draw("");
      H2.Draw("same");
   }
   else
   {
      H2.Draw("");
      H1.Draw("same");
   }

   TLegend Legend(0.5, 0.8, 0.8, 0.6);
   Legend.SetTextFont(42);
   Legend.SetTextSize(0.035);
   Legend.SetBorderSize(0);
   Legend.SetFillStyle(0);
   // Legend.AddEntry(&H1, "0-10%", "pl");
   // Legend.AddEntry(&H2, "50-90%", "pl");
   Legend.AddEntry(&H1, "p_{T}^{Z} = 5-20 GeV", "pl");
   Legend.AddEntry(&H2, "p_{T}^{Z} > 100 GeV", "pl");
   Legend.Draw();
}
