
# Skimming code from forest to plain root file

## Introduction



## Update Log

* Version 1 - 2023 Apr 25
   * Snapshot 2023 Apr 25 after MIT meeting
* Version 2 - 2023 Apr 25
   * Adding switch to do charged gen particles or all gen particles
   * Adding a new tree InfoTree that contains all the input arguments used to make the tree
* Version 3 - 2023 Apr 28
   * Fixing track vertex z selection
* Version 4 - 2023 May 1
   * Adding option to calculate CS WTA
* Version 5 - 2023 May 2
   * Adding HF ceiling for matching.  if lower bound of HF matching is larger than this, it is lowered to the HF ceiling value.  Set to -1 to disable this option.
* Version 5b - 2023 May 4
   * Disable VZ cut in track selection if it is data MB for the time being.
* Version 6 - 2023 May 5
   * reinstantiate the VZ cut in data MB
* Version 7 - 2023 May 7
   * doing gen Z kinematic cuts by default
   * adding Z weight capability
   * adding MC centrality shift by 1.5% as per Kaya analysis
* Version 8 - 2023 May 8
   * Adding tracking residual efficiency by Yenjie
* Version 8b - 2023 May 15
   * Bug fix Z weight
* Version 9 - 2023 May 15
   * Adding Z weight for data with muon tag and probe folded in
* Version 10 - 2023 May 23
   * Adding tracking residual efficiency by centrality by Yenjie
* Version 11 - 2023 May 26
   * Adding pp data mode
   * Adding pp Z weight for both MC and data
* Version 12 - 2023 May 27
   * Fixing pp track selection problem
* Version 12b - 2023 May 30
   * Adding track charge information
   * Adding vz weight for pp and PbPb
* Version 14 - 2023 May 31
   * Adding pp residual tracking weight by Yenjie
   * Deal with PT overflow correctly in the track residual weight code
* (non-version update) - 2023 May 31
   * Now we consolidate settings into a settings file.  Do `make Prepare` to prepare the settings database.  Do `DHQuery Setting.sh PPSignalMC Nominal` to see the settings for PP signal MC for example.


## Arguments


| Argument | type | default | comments |
| -------- | ---- | ------- | -------- |
| Input | vector<string> | _required_ | List of input files separated by comma |
| Output | string | _required_ | Name of the output file |
| DoGenLevel | bool | true | If we store gen muon/Z information or not |
| Fraction | double | 1.00 | What fraction of root file to use |
| MinZPT | double | 20 | Minimum Z PT to store correlated tracks.  If Z PT is below this tracks are not stored |
| MinTrackPT | double | 1.00 | Minimum track PT to store |
| IsData | bool | false | whether this is data or not |
| IsPP | bool | false | whether this is pp or not |
| DoGenCorrelation | bool | false | whether to use gen particles as the "tracks" or not |
| GenCorrelationCharged | bool | false | whether to use all gen particles or only charged |
| DoBackground | bool | false | whether to do background correlation or not |
| Background | vector<string> | _required if DoBackground = true_ | list of file names for background mixing |
| HFShift | double | _required if DoBackground is true_ | Amount of shift to subtract from the HF number |
| HFTolerance | double | _required if DoBackground is true_ | Tolerance to HF sum in GeV |
| HFToleranceFraction | double | _required if DoBackground is true_ | Tolerance to HF sum in fractions |
| HFCeiling | double | -1 | If lower bound of HF matching is larger than this, it is lowered to this value.  Prevents ultra-central matching failures.  Set to negative to disable this. |
| VZTolerance | double | 2 | Tolerance to VZ |
| Oversample | int | 1 | How many times we mix every signal event |
| DoSumET | bool | true | Whether we use SumET or SumE in HF for event matching |
| DoExtraAxes | bool | true | whether to store the extra WTA axes |
| MuonVeto | double | 0.01 | window for track-muon rejection |
| DoJet | bool | true | whether to store jets (and related axes) or not |
| JECFiles | vector<string> | _required if DoJet is true_ | JEC text file list |
| Jet | string | _required if DoJet is true_ | Name of the jet tree. |
| MinJetPT | double | 15 | Minimum jet PT to store |
| DoTrackEfficiency | bool | true | If we want to store track efficiency correction factor |
| TrackEfficiencyPath | string | _required if DoTrackEfficiency is true_ | Base path for track correction files |
| DoTrackResidual | bool | true | If we want to store track residual efficiency correction factor |
| TrackResidualPath | string | _required if DoTrackResidual is true_ | Path for track residual correction files |
| PFTreeName | string | "pfcandAnalyzer/pfTree" (IsPP true) or "particleFlowAnalyser/pftree" (IsPP false) | Name of the particle flow tree.  Default value depends on whether it is pp mode or not |
| DoCS | bool | false | Whether to do constituent-subtraction or not |
| RhoTreeName | string | "hiPuRhoAnalyzer/t" | Tree to get rho information |
| DoMCHiBinShift | bool | true | Whether to shift PbPb MC hiBin to match data better |
| MCHiBinShift | double | 3 | Amount of hiBin to shift PbPb MC.  Defaults to Kaya AN number (1.5%, or 3) |

