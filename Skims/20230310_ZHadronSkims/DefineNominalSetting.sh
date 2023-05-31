
Common="--MinZPT 5 --MinTrackPT 0.5 --DoSumET false --DoExtraAxes true"

MC="--DoGenLevel true --DoGenCorrelation false --IsData false"
MCGen="--DoGenLevel true --DoGenCorrelation true --GenCorrelationCharged true --IsData false"
Data="--DoGenLevel false --IsData true"

AODPF="--PFTree \"pfcandAnalyzer/pfTree\""
MiniAODPF="--PFTree \"particleFlowAnalyser/pftree\""

PPJECMC=Spring18_ppRef5TeV_RAAV3_MC
PPJECData=Spring18_ppRef5TeV_RAAV3_DATA
PbPbJECMC=Autumn18_HI_RAAV3_MC
PbPbJECData=Autumn18_HI_RAAV3_DATA

JECBase=${ProjectBase}/CommonCode/text/JEC/

PPJetMC="--DoJet true --Jet \"ak3PFJetAnlayzer/t\" --JEC ${JECBase}/$PPJECMC/${PPJECMC}_L2Relative_AK3PF.txt"
PPJetData="--DoJet true --Jet \"ak3PFJetAnlayzer/t\" --JEC ${JECBase}/$PPJECData/${PPJECData}_L2Relative_AK3PF.txt,$JECBase/$PPJECData/${PPJECData}_L2L3Residual_AK3PF.tx"
PbPbJetMC="--DoJet true --Jet \"akCs3PFJetAnlayzer/t\" --JEC ${JECBase}/$PbPbJECMC/${PbPbJECMC}_L2Relative_AK3PF.txt"
PbPbJetData="--DoJet true --Jet \"akCs3PFJetAnlayzer/t\" --JEC ${JECBase}/$PbPbJECData/${PbPbJECData}_L2Relative_AK3PF.txt,$JECBase/$PbPbJECData/${PbPbJECData}_L2L3Residual_AK3PF.tx"

TrackResidualPathPbPb="${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_0_20.root,${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_20_60.root,${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_60_100.root,${ProjectBase}/CommonCode/root/20230522_TrackResidualCorrection_V9_100_200.root"
TrackResidualPathPP="${ProjectBase}/CommonCode/root/20230531_TrackResidualCorrection_V12_pp.root"

GenTrack="--DoTrackEfficiency false --TrackEfficiencyPath ${ProjectBase}/CommonCode/root/ --DoTrackResidual false"
PPRecoTrack="--DoTrackEfficiency true --TrackEfficiencyPath ${ProjectBase}/CommonCode/root/ --DoTrackResidual true --TrackResidualPath $TrackResidualPathPP"
PbPbRecoTrack="--DoTrackEfficiency true --TrackEfficiencyPath ${ProjectBase}/CommonCode/root/ --DoTrackResidual true --TrackResidualPath $TrackResidualPathPbPb"

BackgroundMC="--DoBackground true --HFShift 682 --Tolerance 20 --ToleranceFraction 0.05 --HFCeiling 134000"
BackgroundGenMC="--DoBackground true --HFShift 1083 --Tolerance 10 --ToleranceFraction 0.01 --VZTolerance 10000 --HFCeiling 156000"
BackgroundData="--DoBackground true --HFShift 660 --Tolernace 0 --ToleranceFraction 0.01 --Oversample 10 --HFCeiling  70000"

DHSet Setting.dh PPSignalMC          Nominal string "$Common $MC    --IsPP true  $AODPF     $PPJetMC      $PPRecoTrack"
DHSet Setting.dh PPSignalGenMC       Nominal string "$Common $MCGen --IsPP true  $AODPF     $PPJetMC      $GenTrack"
DHSet Setting.dh PPSignalData        Nominal string "$Common $Data  --IsPP true  $AODPF     $PbPbJetData  $PPRecoTrack"
DHSet Setting.dh PbPbSignalMC        Nominal string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack"
DHSet Setting.dh PbPbSignalGenMC     Nominal string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack"
DHSet Setting.dh PbPbSignalData      Nominal string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack"
DHSet Setting.dh PbPbBackgroundMC    Nominal string "$Common $MC    --IsPP false $MiniAODPF $PbPbJetMC    $PbPbRecoTrack $BackgroundMC"
DHSet Setting.dh PbPbBackgroundGenMC Nominal string "$Common $MCGen --IsPP false $MiniAODPF $PbPbJetMC    $GenTrack $BackgroundGenMC"
DHSet Setting.dh PbPbBackgroundData  Nominal string "$Common $Data  --IsPP false $MiniAODPF $PbPbJetData  $PbPbRecoTrack $BackgroundData"




