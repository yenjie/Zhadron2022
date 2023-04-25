{
   AxisTree->AddFriend(Tree, "T");
   
   AxisTree->SetAlias("PFDEta", "(SignalPFEta-MixedPFEta)");
   AxisTree->SetAlias("PFRawDPhi", "(SignalPFPhi-MixedPFPhi)");
   AxisTree->SetAlias("PFDPhi", "(PFRawDPhi+2*3.14159*(PFRawDPhi<-3.14159)-2*3.14159*(PFRawDPhi>3.14159))");
   AxisTree->SetAlias("PFDR", "sqrt(PFDEta*PFDEta+PFDPhi*PFDPhi)");
   AxisTree->SetAlias("TrackDEta", "(SignalTrackEta-MixedTrackEta)");
   AxisTree->SetAlias("TrackRawDPhi", "(SignalTrackPhi-MixedTrackPhi)");
   AxisTree->SetAlias("TrackDPhi", "(TrackRawDPhi+2*3.14159*(TrackRawDPhi<-3.14159)-2*3.14159*(TrackRawDPhi>3.14159))");
   AxisTree->SetAlias("TrackDR", "sqrt(TrackDEta*TrackDEta+TrackDPhi*TrackDPhi)");

   TCanvas Canvas;
   
   TH2D H("H", ";Signal #eta (track #pi/2);Mixed #eta (track #pi/2)", 150, -2.5, 2.5, 150, -2.5, 2.5);
   H.SetStats(0);
   AxisTree->Draw("SignalTrackEta+T.zEta[0]:MixedTrackEta+T.zEta[0]>>H", "AxisFilled > 0", "colz");
   Canvas.SaveAs("Meow.pdf");

   TH2D H2("H2", ";Centrality (%);#DeltaR (track #pi/2)", 100, 0, 100, 100, 0, 5);
   H2.SetStats(0);
   AxisTree->Draw("TrackDR:BackgroundHiBin/2>>H2", "AxisFilled > 0", "colz");
   Canvas.SaveAs("Meow2.pdf");
    
   TH2D H3("H3", ";p_{T}^{Z};#DeltaR (track #pi/2)", 100, 0, 120, 100, 0, 5);
   H3.SetStats(0);
   AxisTree->Draw("TrackDR:T.zPt[0]>>H3", "AxisFilled > 0", "colz");
   Canvas.SaveAs("Meow3.pdf");

   TH2D H4("H4", ";Centrality (%);#DeltaR (track #pi/2)", 100, 0, 100, 100, 0, 5);
   H4.SetStats(0);
   AxisTree->Draw("TrackDR:BackgroundHiBin/2>>H4", "AxisFilled > 0 && T.zPt[0] > 60", "colz");
   Canvas.SaveAs("Meow4.pdf");

   TProfile H5("H5", ";Centrality (%);#DeltaR (track #pi/2)", 20, 0, 100);
   H5.SetStats(0);
   AxisTree->Draw("TrackDR<0.001:BackgroundHiBin/2>>H5", "AxisFilled > 0 && T.zPt[0] > 60", "prof");
   Canvas.SaveAs("Meow5.pdf");
}
