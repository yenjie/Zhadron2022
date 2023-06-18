{
   TFile F("HiForestMiniAOD_14.root");

   TTree *Tree = (TTree *)F.Get("PbPbTracks/trackTree");
   TTree *Event = (TTree *)F.Get("hiEvtAnalyzer/HiTree");

   Tree->AddFriend(Event, "E");

   Tree->Draw("Sum$(trkPt>1&&trkPt<2):E.hiHF", "", "colz");
}
