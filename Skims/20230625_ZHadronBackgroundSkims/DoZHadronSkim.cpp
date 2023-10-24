#include <cstdlib>
#include <vector>
#include <iostream>
#include <algorithm>
#include <ctime>
using namespace std;

#include "TFile.h"
#include "TTree.h"
#include "TH2D.h"
#include "TMath.h"
#include "TSystem.h"
#include "TSystemFile.h"
#include "TSystemDirectory.h"
#include "TLorentzVector.h"

#include "Messenger.h"
#include "CommandLine.h"
#include "CommonFunctions.h"
#include "ProgressBar.h"
#include "CustomAssert.h"

#include "tnp_weight.h"
#include "trackingEfficiency2017pp.h"
#include "trackingEfficiency2018PbPb.h"
#include "TrackResidualCorrector.h"

struct EventIndex;
int main(int argc, char *argv[]);
int FindFirstAbove(vector<EventIndex> &Indices, double X);
double GetHFSum(PFTreeMessenger *M);
double GetGenHFSum(GenParticleTreeMessenger *M);

struct EventIndex
{
public:
   double HF;
   double VZ;
   int Index;
public:
   bool operator <(const EventIndex &other) const
   {
      if(HF < other.HF)         return true;
      if(HF > other.HF)         return false;
      if(VZ < other.VZ)         return true;
      if(VZ > other.VZ)         return false;
      if(Index < other.Index)   return true;
      if(Index > other.Index)   return false;
      return false;
   }
};

int main(int argc, char *argv[])
{
   string Version = "V17";

   CommandLine CL(argc, argv);

   string InputFileName               = CL.Get("Input");   // let's do one by one
   string OutputFileName              = CL.Get("Output");
   bool DoGenLevel                    = CL.GetBool("DoGenLevel", true);
   double Fraction                    = CL.GetDouble("Fraction", 1.00);
   double MinTrackPT                  = CL.GetDouble("MinTrackPT", 1.00);
   bool IsData                        = CL.GetBool("IsData", false);
   bool IsPP                          = CL.GetBool("IsPP", false);
   bool DoGenCorrelation              = CL.GetBool("DoGenCorrelation", false);
   bool GenCorrelationCharged         = CL.GetBool("GenCorrelationCharged", false);
   bool DoSumET                       = CL.GetBool("DoSumET", true);
   double MuonVeto                    = CL.GetDouble("MuonVeto", 0.01);
   string PFTreeName                  = IsPP ? "pfcandAnalyzer/pfTree" : "particleFlowAnalyser/pftree";
   PFTreeName                         = CL.Get("PFTree", PFTreeName);

   bool DoAlternateTrackSelection     = CL.GetBool("DoAlternateTrackSelection", false);
   int AlternateTrackSelection        = DoAlternateTrackSelection ? CL.GetInt("AlternateTrackSelection") : 0;
   bool DoTrackEfficiency             = CL.GetBool("DoTrackEfficiency", true);
   string TrackEfficiencyPath         = (DoTrackEfficiency == true) ? CL.Get("TrackEfficiencyPath") : "";
   bool DoTrackResidual               = CL.GetBool("DoTrackResidual", false);
   vector<string> TrackResidualPath   = (DoTrackResidual == true) ? CL.GetStringVector("TrackResidualPath") : vector<string>{"", "", "", ""};

   // Assert(!(IsPP == true && IsData == true), "Data selections for pp not implemented yet");
   Assert(!(DoGenCorrelation == true && DoGenLevel == false), "You need to turn on gen level to do gen correlation!");
   if(DoTrackResidual == true)
      Assert(TrackResidualPath.size() == 1 || TrackResidualPath.size() == 4, "You need 1 file for residual correction or 4 files for centrality-dependence");

   vector<string> BackgroundFileNames = CL.GetStringVector("Background");
   double VZTolerance                 = CL.GetDouble("VZTolerance", 2);
   double HFShift                     = CL.GetDouble("HFShift");
   double HFTolerance                 = CL.GetDouble("Tolerance");
   double HFToleranceFraction         = CL.GetDouble("ToleranceFraction");
   double HFCeiling                   = CL.GetDouble("HFCeiling", -1);
   int NBackground                    = BackgroundFileNames.size();
   double Oversample                  = CL.GetInteger("Oversample", 1);
   bool ReuseBackground               = CL.GetBool("ReuseBackground", false);

   TrkEff2017pp *TrackEfficiencyPP = nullptr;
   TrkEff2018PbPb *TrackEfficiencyPbPb = nullptr;
   if(DoTrackEfficiency == true)
   {
      if(IsPP == true)
         TrackEfficiencyPP = new TrkEff2017pp(false, TrackEfficiencyPath);
      else
      {
         if(DoAlternateTrackSelection == false)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "", false, TrackEfficiencyPath);
         if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "", false, TrackEfficiencyPath);
         if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "Loose", false, TrackEfficiencyPath);
         if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2)
            TrackEfficiencyPbPb = new TrkEff2018PbPb("general", "Tight", false, TrackEfficiencyPath);
      }
   }
   TrackResidualCentralityCorrector TrackResidual(TrackResidualPath);

   // Let's build an index of signal.  We need (SignalHF, VertexZ)
   TFile SignalFile(InputFileName.c_str());
   ZHadronMessenger MSignalZHadron(SignalFile, "Tree");

   vector<EventIndex> SignalIndex;
   map<EventIndex, int> SignalCount;
   int SignalEntryCount = MSignalZHadron.GetEntries() * Fraction;
   for(int iE = 0; iE < SignalEntryCount; iE++)
   {
      MSignalZHadron.GetEntry(iE);

      EventIndex Index;
      Index.HF = MSignalZHadron.SignalHF;
      Index.VZ = MSignalZHadron.VZ;
      Index.Index = iE;

      // Only proceed if there is something on the signal side
      if(MSignalZHadron.trackPt->size() == 0)
         continue;

      // I think the previous condition is sufficient
      // if(DoGenCorrelation == true && MSignalZHadron.genZPt->size() == 0)   continue;
      // if(DoGenCorrelation == false && MSignalZHadron.zPt->size() == 0)     continue;

      // Too small signal HF.  Too peripheral.  Won't attempt to match it
      if(MSignalZHadron.SignalHF < HFShift)
         continue;

      SignalIndex.push_back(Index);
      SignalCount.insert(pair<EventIndex, int>(Index, 0));
   }

   cout << "Number of signal events to be matched: " << SignalIndex.size() << endl;

   // Declare output files
   TFile OutputFile(OutputFileName.c_str(), "RECREATE");

   TTree Tree("Tree", Form("Tree for ZHadron analysis, %s", Version.c_str()));
   TTree InfoTree("InfoTree", "Information");
   TTree UnmatchedTree("Unmatched", "Information for unmatched");

   string Key, Value;
   InfoTree.Branch("Key", &Key);
   InfoTree.Branch("Value", &Value);

   time_t CurrentTime = time(NULL);
   string StringTime = ctime(&CurrentTime);
   replace(StringTime.begin(), StringTime.end(), '\n', ' ');

   Key = "Version";                 Value = InfoString(Version);                 InfoTree.Fill();
   Key = "CurrentTime";             Value = InfoString(StringTime);              InfoTree.Fill();
   Key = "Input";                   Value = InfoString(InputFileName);           InfoTree.Fill();
   Key = "Output";                  Value = InfoString(OutputFileName);          InfoTree.Fill();
   Key = "DoGenLevel";              Value = InfoString(DoGenLevel);              InfoTree.Fill();
   Key = "Fraction";                Value = InfoString(Fraction);                InfoTree.Fill();
   Key = "IsData";                  Value = InfoString(IsData);                  InfoTree.Fill();
   Key = "IsPP";                    Value = InfoString(IsPP);                    InfoTree.Fill();
   Key = "DoGenCorrelation";        Value = InfoString(DoGenCorrelation);        InfoTree.Fill();
   Key = "GenCorrelationCharged";   Value = InfoString(GenCorrelationCharged);   InfoTree.Fill();
   Key = "DoSumET";                 Value = InfoString(DoSumET);                 InfoTree.Fill();
   Key = "MuonVeto";                Value = InfoString(MuonVeto);                InfoTree.Fill();
   Key = "DoTrackEfficiency";       Value = InfoString(DoTrackEfficiency);       InfoTree.Fill();
   Key = "TrackEfficiencyPath";     Value = InfoString(TrackEfficiencyPath);     InfoTree.Fill();
   Key = "DoTrackResidual";         Value = InfoString(DoTrackResidual);         InfoTree.Fill();
   Key = "TrackResidualPath";       Value = InfoString(TrackResidualPath);       InfoTree.Fill();
   Key = "Background";              Value = InfoString(BackgroundFileNames);     InfoTree.Fill();
   Key = "VZTolerance";             Value = InfoString(VZTolerance);             InfoTree.Fill();
   Key = "HFShift";                 Value = InfoString(HFShift);                 InfoTree.Fill();
   Key = "Tolerance";               Value = InfoString(HFTolerance);             InfoTree.Fill();
   Key = "ToleranceFraction";       Value = InfoString(HFToleranceFraction);     InfoTree.Fill();
   Key = "HFCeiling";               Value = InfoString(HFCeiling);               InfoTree.Fill();
   Key = "Oversample";              Value = InfoString(Oversample);              InfoTree.Fill();
   Key = "ReuseBackground";         Value = InfoString(ReuseBackground);         InfoTree.Fill();

   TH2D H2D("H2D", "", 100, -6, 6, 100, -M_PI, M_PI);

   ZHadronMessenger MZHadron;
   MZHadron.SetBranch(&Tree);
   Tree.SetAlias("zP", "(zPt*cosh(zEta))");
   Tree.SetAlias("zPz", "(zPt*sinh(zEta))");
   Tree.SetAlias("zE", "sqrt(zP*zP+zMass*zMass)");
   Tree.SetAlias("zY", "(0.5*log((zE+zPz)/(zE-zPz)))");

   // Loop over background files
   for(string BackgroundFileName : BackgroundFileNames)
   {
      if(SignalIndex.size() == 0)   // nothing more to match
         break;
      
      MZHadron.Clear();

      // Get the input file
      TFile InputFile(BackgroundFileName.c_str());

      // Setup all the messengers.  In the future we'll add more for triggers etc.
      HiEventTreeMessenger     MEvent(InputFile);
      TrackTreeMessenger       MTrackPP(InputFile);
      PbPbTrackTreeMessenger   MTrack(InputFile);
      GenParticleTreeMessenger MGen(InputFile);
      PFTreeMessenger          MPF(InputFile, PFTreeName);

      // Start looping over events
      int EntryCount = MEvent.GetEntries();
      ProgressBar Bar(cout, EntryCount);
      Bar.SetStyle(-1);
      // Bar.SetStyle(6);

      for(int iE = 0; iE < EntryCount; iE++)
      {
         // Progress bar stuff
         if(EntryCount < 300 || (iE % (EntryCount / 250)) == 0)
         {
            Bar.Update(iE);
            Bar.Print();
         }

         if(SignalIndex.size() == 0)   // nothing more to match
            break;

         MEvent.GetEntry(iE);
         MGen.GetEntry(iE);
         if(IsPP == true)
            MTrackPP.GetEntry(iE);
         else
            MTrack.GetEntry(iE);
         MPF.GetEntry(iE);

         // Now we find if there is a signal event that this background event can be matched to

         double SumHF = DoGenCorrelation ? GetGenHFSum(&MGen) : (DoSumET ? MEvent.hiHF : GetHFSum(&MPF));
         double VZ = MEvent.vz;

         double ShiftedHF = SumHF + HFShift;

         double HFMin = min(ShiftedHF - HFTolerance, ShiftedHF / (1 + HFToleranceFraction));
         double HFMax = max(ShiftedHF + HFTolerance, ShiftedHF / (1 - HFToleranceFraction));

         // Think about this later
         // if(HFCeiling >= 0 && LowerHF > HFCeiling)
         //    LowerHF = HFCeiling;

         // Loop over surviving signal events and see how things go
         for(int i = 0; i < (int)SignalIndex.size(); i++)
         {
            double SignalHF = SignalIndex[i].HF;
            double SignalVZ = SignalIndex[i].VZ;

            if(SignalHF < HFMin || SignalHF > HFMax)
               continue;
            if(fabs(SignalVZ - VZ) > VZTolerance)
               continue;

            // cout << "We have a match!  Signal (" << SignalHF << " " << SignalVZ << "), Background (" << SumHF << " " << VZ << ")" << endl;

            // we have a winner!
            MSignalZHadron.GetEntry(SignalIndex[i].Index);

            MZHadron.Clear();
            MZHadron.CopyNonTrack(MSignalZHadron);   // this needs to be implemented
            MZHadron.BackgroundHF = SumHF;

            // Copy over background tracks
            int NTrack = DoGenCorrelation ? MGen.Mult : (IsPP ? MTrackPP.nTrk : MTrack.TrackPT->size());
            for(int itrack = 0; itrack < NTrack; itrack++)
            {
               if(DoGenCorrelation == false)   // track selection on reco
               {
                  if(IsPP == true)
                  {
                     if(DoAlternateTrackSelection == false && MTrackPP.PassZHadron2022Cut(itrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0 && MTrackPP.PassZHadron2022Cut(itrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1 && MTrackPP.PassZHadron2022CutLoose(itrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2 && MTrackPP.PassZHadron2022CutTight(itrack) == false)
                        continue;
                  }
                  if(IsPP == false)
                  {
                     if(DoAlternateTrackSelection == false && MTrack.PassZHadron2022Cut(itrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 0 && MTrack.PassZHadron2022Cut(itrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 1 && MTrack.PassZHadron2022CutLoose(itrack) == false)
                        continue;
                     if(DoAlternateTrackSelection == true && AlternateTrackSelection == 2 && MTrack.PassZHadron2022CutTight(itrack) == false)
                        continue;
                  }
                  if((IsPP ? MTrackPP.trkPt[itrack] : MTrack.TrackPT->at(itrack)) < MinTrackPT)
                     continue;
               }

               if(DoGenCorrelation == true)
               {
                  if(MGen.PT->at(itrack) < MinTrackPT)
                     continue;
                  if(MGen.Eta->at(itrack) < -2.4)
                     continue;
                  if(MGen.Eta->at(itrack) > +2.4)
                     continue;
                  if(MGen.DaughterCount->at(itrack) > 0)
                     continue;
                  if(GenCorrelationCharged == true && MGen.Charge->at(itrack) == 0)
                     continue;
               }

               double TrackEta = DoGenCorrelation ? MGen.Eta->at(itrack) : (IsPP ? MTrackPP.trkEta[itrack] : MTrack.TrackEta->at(itrack));
               double TrackPhi = DoGenCorrelation ? MGen.Phi->at(itrack) : (IsPP ? MTrackPP.trkPhi[itrack] : MTrack.TrackPhi->at(itrack));
               double TrackPT  = DoGenCorrelation ? MGen.PT->at(itrack) : (IsPP ? MTrackPP.trkPt[itrack] : MTrack.TrackPT->at(itrack));
               int TrackCharge = DoGenCorrelation ? MGen.Charge->at(itrack) : (IsPP ? MTrackPP.trkCharge[itrack] : MTrack.TrackCharge->at(itrack));
               int SubEvent    = DoGenCorrelation ? (MGen.SubEvent->at(itrack) + 1) : (IsPP ? 0 : 1);

               double Mu1Eta = DoGenCorrelation ? MZHadron.genMuEta1->at(0) : MZHadron.muEta1->at(0);
               double Mu1Phi = DoGenCorrelation ? MZHadron.genMuPhi1->at(0) : MZHadron.muPhi1->at(0);
               double Mu2Eta = DoGenCorrelation ? MZHadron.genMuEta2->at(0) : MZHadron.muEta2->at(0);
               double Mu2Phi = DoGenCorrelation ? MZHadron.genMuPhi2->at(0) : MZHadron.muPhi2->at(0);

               double DeltaEtaMu1 = TrackEta - Mu1Eta;
               double DeltaEtaMu2 = TrackEta - Mu2Eta;
               double DeltaPhiMu1 = DeltaPhi(TrackPhi, Mu1Phi);
               double DeltaPhiMu2 = DeltaPhi(TrackPhi, Mu2Phi);

               double DeltaRMu1 = sqrt(DeltaEtaMu1 * DeltaEtaMu1 + DeltaPhiMu1 * DeltaPhiMu1);
               double DeltaRMu2 = sqrt(DeltaEtaMu2 * DeltaEtaMu2 + DeltaPhiMu2 * DeltaPhiMu2);

               bool MuTagged = false;
               if(DeltaRMu1 < MuonVeto)   MuTagged = true;
               if(DeltaRMu2 < MuonVeto)   MuTagged = true;

               double ZEta = DoGenCorrelation ? MZHadron.genZEta->at(0) : MZHadron.zEta->at(0);
               double ZPhi = DoGenCorrelation ? MZHadron.genZPhi->at(0) : MZHadron.zPhi->at(0);

               double deltaEta = TrackEta - ZEta;
               double deltaPhi = DeltaPhi(TrackPhi, ZPhi);

               H2D.Fill(+deltaEta, +deltaPhi, 0.25);
               H2D.Fill(-deltaEta, +deltaPhi, 0.25);
               H2D.Fill(-deltaEta, -deltaPhi, 0.25);
               H2D.Fill(+deltaEta, -deltaPhi, 0.25);

               MZHadron.trackDphi->push_back(deltaPhi);
               MZHadron.trackDeta->push_back(deltaEta);
               MZHadron.trackPt->push_back(TrackPT);
               MZHadron.trackMuTagged->push_back(MuTagged);
               MZHadron.trackMuDR->push_back(min(DeltaRMu1, DeltaRMu2));
               MZHadron.subevent->push_back(SubEvent);

               double TrackCorrection = 1;
               if(DoTrackEfficiency == true && DoGenCorrelation == false)
               {
                  if(IsPP == true)
                     TrackCorrection = TrackEfficiencyPP->getCorrection(TrackPT, TrackEta);
                  else
                     TrackCorrection = TrackEfficiencyPbPb->getCorrection(TrackPT, TrackEta, MZHadron.hiBin);
               }
               double TrackResidualCorrection = 1;
               if(DoTrackResidual == true && DoGenCorrelation == false)
               {
                  TrackResidualCorrection = TrackResidual.GetCorrectionFactor(TrackPT, TrackEta, TrackPhi, MZHadron.hiBin);
               }
               MZHadron.trackWeight->push_back(TrackCorrection);
               MZHadron.trackResidualWeight->push_back(TrackResidualCorrection);
            }

            MZHadron.FillEntry();

            // Now we increment the counter, and remove from index if necessary
            SignalCount[SignalIndex[i]] = SignalCount[SignalIndex[i]] + 1;
            if(SignalCount[SignalIndex[i]] >= Oversample)
            {
               SignalIndex.erase(SignalIndex.begin() + i);
               i = i - 1;
            }

            // We found a match, let's move on to the next MB event
            if(ReuseBackground == false)
               break;
         }
      }

      Bar.Update(EntryCount);
      Bar.Print();
      Bar.PrintLine();

      InputFile.Close();
   
      int NonMatchedCount = 0;
      for(auto iter : SignalCount)
         if(iter.second == 0)
            NonMatchedCount = NonMatchedCount + 1;

      cout << "So far...number of events remaining to be matched: " << SignalIndex.size() << endl;
      cout << "So far...number of events completely not matched: " << NonMatchedCount << endl;
   }

   double UnmatchedHF;
   double UnmatchedVZ;
   int UnmatchedCount;
   UnmatchedTree.Branch("HF", &UnmatchedHF, "HF/D");
   UnmatchedTree.Branch("VZ", &UnmatchedVZ, "VZ/D");
   UnmatchedTree.Branch("Count", &UnmatchedCount, "Count/I");
   for(EventIndex &Index : SignalIndex)
   for(auto iter : SignalCount)
   {
      const EventIndex &Index = iter.first;
      UnmatchedHF = Index.HF;
      UnmatchedVZ = Index.VZ;
      UnmatchedCount = iter.second;
      UnmatchedTree.Fill();
   }

   OutputFile.cd();
   H2D.Write();
   Tree.Write();
   InfoTree.Write();
   UnmatchedTree.Write();

   OutputFile.Close();

   SignalFile.Close();

   if(DoTrackEfficiency == true)
   {
      if(TrackEfficiencyPP != nullptr)
         delete TrackEfficiencyPP;
      if(TrackEfficiencyPbPb != nullptr)
         delete TrackEfficiencyPbPb;
   }

   return 0;
}

int FindFirstAbove(vector<EventIndex> &Indices, double X)
{
   if(X < Indices[0].HF)
      return 0;

   if(X >= Indices[Indices.size()-1].HF)
      return Indices.size();

   int Low = 0;
   int High = Indices.size();

   while(High - Low > 1)
   {
      int Middle = (High + Low) / 2;
      if(X < Indices[Middle].HF)
         High = Middle;
      else
         Low = Middle;
   }

   return Low;
}

double GetHFSum(PFTreeMessenger *M)
{
   if(M == nullptr)
      return -1;
   if(M->Tree == nullptr)
      return -1;

   double Sum = 0;
   for(int iPF = 0; iPF < M->ID->size(); iPF++)
      if(fabs(M->Eta->at(iPF)) > 3 && fabs(M->Eta->at(iPF)) < 5)
         Sum = Sum + M->E->at(iPF);

   // cout << Sum << endl;

   return Sum;
}

double GetGenHFSum(GenParticleTreeMessenger *M)
{
   if(M == nullptr)
      return -1;
   if(M->Tree == nullptr)
      return -1;

   double Sum = 0;
   for(int iGen = 0; iGen < M->Mult; iGen++)
   {
      if(fabs(M->Eta->at(iGen)) < 3)
         continue;
      if(fabs(M->Eta->at(iGen)) > 5)
         continue;
      if(M->DaughterCount->at(iGen) > 0)
         continue;
      Sum = Sum + M->PT->at(iGen) * cosh(M->Eta->at(iGen));
   }

   return Sum;
}


