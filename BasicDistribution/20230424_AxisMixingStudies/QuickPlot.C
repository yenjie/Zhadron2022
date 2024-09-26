{
   AxisTree->AddFriend(Tree, "T");
   
   AxisTree->SetAlias("PFDEta", "(SignalPFEta-MixedPFEta)");
   AxisTree->SetAlias("PFRawDPhi", "(SignalPFPhi-MixedPFPhi)");
   AxisTree->SetAlias("PFDPhi", "(PFRawDPhi+2*3.14159*(PFRawDPhi<-3.14159)-2*3.14159*(PFRawDPhi>3.14159))");
   AxisTree->SetAlias("PFDR", "sqrt(PFDEta*PFDEta+PFDPhi*PFDPhi)");
   AxisTree->SetAlias("CSPFDEta", "(SignalCSPFEta-MixedCSPFEta)");
   AxisTree->SetAlias("CSPFRawDPhi", "(SignalCSPFPhi-MixedCSPFPhi)");
   AxisTree->SetAlias("CSPFDPhi", "(CSPFRawDPhi+2*3.14159*(CSPFRawDPhi<-3.14159)-2*3.14159*(CSPFRawDPhi>3.14159))");
   AxisTree->SetAlias("CSPFDR", "sqrt(CSPFDEta*CSPFDEta+CSPFDPhi*CSPFDPhi)");
   AxisTree->SetAlias("TrackDEta", "(SignalTrackEta-MixedTrackEta)");
   AxisTree->SetAlias("TrackRawDPhi", "(SignalTrackPhi-MixedTrackPhi)");
   AxisTree->SetAlias("TrackDPhi", "(TrackRawDPhi+2*3.14159*(TrackRawDPhi<-3.14159)-2*3.14159*(TrackRawDPhi>3.14159))");
   AxisTree->SetAlias("TrackDR", "sqrt(TrackDEta*TrackDEta+TrackDPhi*TrackDPhi)");
   AxisTree->SetAlias("HardTrackDEta", "(SignalHardTrackEta-MixedHardTrackEta)");
   AxisTree->SetAlias("HardTrackRawDPhi", "(SignalHardTrackPhi-MixedHardTrackPhi)");
   AxisTree->SetAlias("HardTrackDPhi", "(HardTrackRawDPhi+2*3.14159*(HardTrackRawDPhi<-3.14159)-2*3.14159*(HardTrackRawDPhi>3.14159))");
   AxisTree->SetAlias("HardTrackDR", "sqrt(HardTrackDEta*HardTrackDEta+HardTrackDPhi*HardTrackDPhi)");
   AxisTree->SetAlias("Track34DEta", "(SignalTrack34Eta-MixedTrack34Eta)");
   AxisTree->SetAlias("Track34RawDPhi", "(SignalTrack34Phi-MixedTrack34Phi)");
   AxisTree->SetAlias("Track34DPhi", "(Track34RawDPhi+2*3.14159*(Track34RawDPhi<-3.14159)-2*3.14159*(Track34RawDPhi>3.14159))");
   AxisTree->SetAlias("Track34DR", "sqrt(Track34DEta*Track34DEta+Track34DPhi*Track34DPhi)");

   TCanvas Canvas;
   
   TH2D H("H", ";Signal WTA #eta (track #pi/2);Mixed WTA #eta (track #pi/2)", 150, -2.5, 2.5, 150, -2.5, 2.5);
   H.SetStats(0);
   AxisTree->Draw("SignalTrackEta+T.zEta[0]:MixedTrackEta+T.zEta[0]>>H", "AxisFilled > 0", "colz");
   Canvas.SaveAs("Meow.pdf");

   TH2D H2("H2", ";Centrality (%);#DeltaR^{WTA (track #pi/2)}", 100, 0, 100, 100, 0, 5);
   H2.SetStats(0);
   AxisTree->Draw("TrackDR:BackgroundHiBin/2>>H2", "AxisFilled > 0", "colz");
   Canvas.SaveAs("Meow2.pdf");
    
   TH2D H3("H3", ";p_{T}^{Z};#DeltaR^{WTA (track #pi/2)}", 100, 0, 120, 100, 0, 5);
   H3.SetStats(0);
   AxisTree->Draw("TrackDR:T.zPt[0]>>H3", "AxisFilled > 0", "colz");
   Canvas.SaveAs("Meow3.pdf");

   TH2D H4("H4", ";Centrality (%);#DeltaR^{WTA (track #pi/2)}", 100, 0, 100, 100, 0, 5);
   H4.SetStats(0);
   AxisTree->Draw("TrackDR:BackgroundHiBin/2>>H4", "AxisFilled > 0 && T.zPt[0] > 60", "colz");
   Canvas.SaveAs("Meow4.pdf");

   TProfile H5("H5", ";Centrality (%);Good match WTA (track #pi/2)", 20, 0, 100);
   H5.SetStats(0);
   AxisTree->Draw("TrackDR<0.001:BackgroundHiBin/2>>H5", "AxisFilled > 0 && T.zPt[0] > 60", "prof");
   Canvas.SaveAs("Meow5.pdf");

   TProfile H6("H6", ";Centrality (%);Good match WTA (PF #pi/2)", 20, 0, 100);
   H6.SetStats(0);
   AxisTree->Draw("PFDR<0.001:BackgroundHiBin/2>>H6", "AxisFilled > 0 && T.zPt[0] > 60", "prof");
   Canvas.SaveAs("Meow6.pdf");

   TH2D H7("H7", ";Centrality (%);#DeltaR^{WTA (PF #pi/2)}", 100, 0, 100, 100, 0, 5);
   H7.SetStats(0);
   AxisTree->Draw("PFDR:BackgroundHiBin/2>>H7", "AxisFilled > 0 && T.zPt[0] > 60", "colz");
   Canvas.SaveAs("Meow7.pdf");

   TProfile H8("H8", ";Centrality (%);Good match WTA (Hard track #pi/2)", 20, 0, 100);
   H8.SetStats(0);
   AxisTree->Draw("HardTrackDR<0.001:BackgroundHiBin/2>>H8", "AxisFilled > 0 && T.zPt[0] > 60", "prof");
   Canvas.SaveAs("Meow8.pdf");

   TProfile H9("H9", ";Centrality (%);Good match WTA (Track 3#pi/4)", 20, 0, 100);
   H9.SetStats(0);
   AxisTree->Draw("Track34DR<0.001:BackgroundHiBin/2>>H9", "AxisFilled > 0 && T.zPt[0] > 60", "prof");
   Canvas.SaveAs("Meow9.pdf");

   TProfile H10("H10", ";Centrality (%);Good match WTA (CS PF #pi/2)", 20, 0, 100);
   H10.SetStats(0);
   AxisTree->Draw("CSPFDR<0.001:BackgroundHiBin/2>>H10", "AxisFilled > 0 && T.zPt[0] > 60", "prof");
   Canvas.SaveAs("Meow10.pdf");

   TH2D H11("H11", ";Centrality (%);#DeltaR^{WTA (CS PF #pi/2)}", 100, 0, 100, 100, 0, 5);
   H11.SetStats(0);
   AxisTree->Draw("PFDR:BackgroundHiBin/2>>H11", "AxisFilled > 0 && T.zPt[0] > 60", "colz");
   Canvas.SaveAs("Meow11.pdf");
}
