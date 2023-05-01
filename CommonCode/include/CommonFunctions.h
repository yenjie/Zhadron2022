#include <cmath>
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#define M_MU 0.1056583755

// Structs

struct PseudoParticle;

struct PseudoParticle
{
   double Eta;
   double Phi;
   double PT;
   PseudoParticle(double eta, double phi, double pt)
   {
      Eta = eta;
      Phi = phi;
      PT = pt;
   }
   bool operator <(const PseudoParticle &other) const
   {
      if(Eta < other.Eta)   return true;
      if(Eta > other.Eta)   return false;
      if(Phi < other.Phi)   return true;
      if(Phi > other.Phi)   return false;
      if(PT < other.PT)     return true;
      if(PT > other.PT)     return false;
      return false;
   }
};

// Function declarations

double DeltaPhi(double Phi1, double Phi2);
double PhiRangePositive(double Phi);
double PhiRangeSymmetric(double Phi);
double PhiRangeCorrelation(double Phi);
double FindNColl(int hiBin);
double FindNPart(int hiBin);
double FindNCollAverage(int hiBin);
double FindNPartAverage(int hiBin);
std::pair<double, double> WTAAxis(std::vector<double> &Eta, std::vector<double> &Phi, std::vector<double> &PT);
std::pair<double, double> WTAAxisCA(std::vector<double> Eta, std::vector<double> Phi, std::vector<double> PT);
std::pair<double, double> WTAAxisTable(std::vector<double> Eta, std::vector<double> Phi, std::vector<double> PT);
void ConstituentSubtraction(std::vector<double> &Eta, std::vector<double> &Phi, std::vector<double> &PT,
   std::vector<double> *EtaMin = nullptr, std::vector<double> *EtaMax = nullptr, std::vector<double> *Rho = nullptr,
   double MaxR = 1.0);
void DoCSBruteForce(std::vector<double> &Eta, std::vector<double> &Phi, std::vector<double> &PT,
   std::vector<double> &GhostEta, std::vector<double> &GhostPhi, std::vector<double> &GhostPT,
   double MaxR2);
std::string InfoString(std::string Info);
std::string InfoString(char *Info);
std::string InfoString(int Info);
std::string InfoString(float Info);
std::string InfoString(double Info);
std::string InfoString(bool Info);
std::string InfoString(std::vector<std::string> Info);

// Function implementations

double DeltaPhi(double Phi1, double Phi2)
{
   return PhiRangeSymmetric(Phi1 - Phi2);
}

double PhiRangePositive(double Phi)
{
   while(Phi < 0)   Phi = Phi + 2 * M_PI;
   return Phi;
}

double PhiRangeSymmetric(double Phi)
{
   if(Phi < -M_PI)   Phi = Phi + 2 * M_PI;
   if(Phi > +M_PI)   Phi = Phi - 2 * M_PI;
   return Phi;
}

double PhiRangeCorrelation(double Phi)
{
   if(Phi < -M_PI * 0.5)   Phi = Phi + 2 * M_PI;
   if(Phi > +M_PI * 1.5)   Phi = Phi - 2 * M_PI;
   return Phi;
}

double FindNColl(int hiBin)
{
   static const int nbins = 200;
   static const double Ncoll[nbins] = {1976.95, 1944.02, 1927.29, 1891.9, 1845.3, 1807.2, 1760.45, 1729.18, 1674.8, 1630.3, 1590.52, 1561.72, 1516.1, 1486.5, 1444.68, 1410.88, 1376.4, 1347.32, 1309.71, 1279.98, 1255.31, 1219.89, 1195.13, 1165.96, 1138.92, 1113.37, 1082.26, 1062.42, 1030.6, 1009.96, 980.229, 955.443, 936.501, 915.97, 892.063, 871.289, 847.364, 825.127, 806.584, 789.163, 765.42, 751.187, 733.001, 708.31, 690.972, 677.711, 660.682, 640.431, 623.839, 607.456, 593.307, 576.364, 560.967, 548.909, 530.475, 519.575, 505.105, 490.027, 478.133, 462.372, 451.115, 442.642, 425.76, 416.364, 405.154, 392.688, 380.565, 371.167, 360.28, 348.239, 340.587, 328.746, 320.268, 311.752, 300.742, 292.172, 281.361, 274.249, 267.025, 258.625, 249.931, 240.497, 235.423, 228.63, 219.854, 214.004, 205.425, 199.114, 193.618, 185.644, 180.923, 174.289, 169.641, 161.016, 157.398, 152.151, 147.425, 140.933, 135.924, 132.365, 127.017, 122.127, 117.817, 113.076, 109.055, 105.16, 101.323, 98.098, 95.0548, 90.729, 87.6495, 84.0899, 80.2237, 77.2201, 74.8848, 71.3554, 68.7745, 65.9911, 63.4136, 61.3859, 58.1903, 56.4155, 53.8486, 52.0196, 49.2921, 47.0735, 45.4345, 43.8434, 41.7181, 39.8988, 38.2262, 36.4435, 34.8984, 33.4664, 31.8056, 30.351, 29.2074, 27.6924, 26.7754, 25.4965, 24.2802, 22.9651, 22.0059, 21.0915, 19.9129, 19.1041, 18.1487, 17.3218, 16.5957, 15.5323, 14.8035, 14.2514, 13.3782, 12.8667, 12.2891, 11.61, 11.0026, 10.3747, 9.90294, 9.42648, 8.85324, 8.50121, 7.89834, 7.65197, 7.22768, 6.7755, 6.34855, 5.98336, 5.76555, 5.38056, 5.11024, 4.7748, 4.59117, 4.23247, 4.00814, 3.79607, 3.68702, 3.3767, 3.16309, 2.98282, 2.8095, 2.65875, 2.50561, 2.32516, 2.16357, 2.03235, 1.84061, 1.72628, 1.62305, 1.48916, 1.38784, 1.28366, 1.24693, 1.18552, 1.16085, 1.12596, 1.09298, 1.07402, 1.06105, 1.02954};
   return Ncoll[hiBin];
}

double FindNPart(int hiBin)
{
   static const int nbins = 200;
   static const double Npart[nbins] = {401.99, 398.783, 396.936, 392.71, 387.901, 383.593, 377.914, 374.546, 367.507, 361.252, 356.05, 352.43, 345.701, 341.584, 335.148, 330.581, 325.135, 320.777, 315.074, 310.679, 306.687, 301.189, 296.769, 291.795, 287.516, 283.163, 277.818, 274.293, 269.29, 265.911, 260.574, 256.586, 252.732, 249.194, 245.011, 241.292, 236.715, 232.55, 229.322, 225.328, 221.263, 218.604, 214.728, 210.554, 206.878, 203.924, 200.84, 196.572, 193.288, 189.969, 186.894, 183.232, 180.24, 177.36, 174.008, 171.222, 168.296, 165.319, 162.013, 158.495, 156.05, 154.218, 150.559, 148.455, 145.471, 142.496, 139.715, 137.395, 134.469, 131.926, 129.817, 127.045, 124.467, 122.427, 119.698, 117.607, 114.543, 112.662, 110.696, 108.294, 105.777, 103.544, 101.736, 99.943, 97.4951, 95.4291, 93.2148, 91.2133, 89.5108, 87.2103, 85.7498, 83.5134, 81.9687, 79.7456, 78.1684, 76.4873, 74.7635, 72.761, 71.0948, 69.6102, 67.7806, 66.2215, 64.5813, 63.0269, 61.4325, 59.8065, 58.2423, 57.2432, 55.8296, 54.2171, 52.8809, 51.3254, 49.9902, 48.6927, 47.5565, 46.136, 44.8382, 43.6345, 42.3964, 41.4211, 39.9681, 39.178, 37.9341, 36.9268, 35.5626, 34.5382, 33.6912, 32.8156, 31.6695, 30.6552, 29.7015, 28.8655, 27.9609, 27.0857, 26.105, 25.3163, 24.4872, 23.6394, 23.0484, 22.2774, 21.4877, 20.5556, 19.9736, 19.3296, 18.5628, 17.916, 17.2928, 16.6546, 16.1131, 15.4013, 14.8264, 14.3973, 13.7262, 13.2853, 12.8253, 12.2874, 11.7558, 11.2723, 10.8829, 10.4652, 9.96477, 9.6368, 9.09316, 8.84175, 8.48084, 8.05694, 7.64559, 7.29709, 7.07981, 6.70294, 6.45736, 6.10284, 5.91788, 5.5441, 5.33311, 5.06641, 4.96415, 4.6286, 4.38214, 4.2076, 4.01099, 3.81054, 3.63854, 3.43403, 3.23244, 3.08666, 2.86953, 2.74334, 2.62787, 2.48354, 2.38115, 2.26822, 2.23137, 2.1665, 2.14264, 2.10636, 2.07358, 2.05422, 2.04126, 2.00954};
   return Npart[hiBin];
}

double FindNCollAverage(int hiBinLow, int hiBinHigh)
{
   double w=0;
   static const int nbins = 200;
   static const double Ncoll[nbins] = {1976.95, 1944.02, 1927.29, 1891.9, 1845.3, 1807.2, 1760.45, 1729.18, 1674.8, 1630.3, 1590.52, 1561.72, 1516.1, 1486.5, 1444.68, 1410.88, 1376.4, 1347.32, 1309.71, 1279.98, 1255.31, 1219.89, 1195.13, 1165.96, 1138.92, 1113.37, 1082.26, 1062.42, 1030.6, 1009.96, 980.229, 955.443, 936.501, 915.97, 892.063, 871.289, 847.364, 825.127, 806.584, 789.163, 765.42, 751.187, 733.001, 708.31, 690.972, 677.711, 660.682, 640.431, 623.839, 607.456, 593.307, 576.364, 560.967, 548.909, 530.475, 519.575, 505.105, 490.027, 478.133, 462.372, 451.115, 442.642, 425.76, 416.364, 405.154, 392.688, 380.565, 371.167, 360.28, 348.239, 340.587, 328.746, 320.268, 311.752, 300.742, 292.172, 281.361, 274.249, 267.025, 258.625, 249.931, 240.497, 235.423, 228.63, 219.854, 214.004, 205.425, 199.114, 193.618, 185.644, 180.923, 174.289, 169.641, 161.016, 157.398, 152.151, 147.425, 140.933, 135.924, 132.365, 127.017, 122.127, 117.817, 113.076, 109.055, 105.16, 101.323, 98.098, 95.0548, 90.729, 87.6495, 84.0899, 80.2237, 77.2201, 74.8848, 71.3554, 68.7745, 65.9911, 63.4136, 61.3859, 58.1903, 56.4155, 53.8486, 52.0196, 49.2921, 47.0735, 45.4345, 43.8434, 41.7181, 39.8988, 38.2262, 36.4435, 34.8984, 33.4664, 31.8056, 30.351, 29.2074, 27.6924, 26.7754, 25.4965, 24.2802, 22.9651, 22.0059, 21.0915, 19.9129, 19.1041, 18.1487, 17.3218, 16.5957, 15.5323, 14.8035, 14.2514, 13.3782, 12.8667, 12.2891, 11.61, 11.0026, 10.3747, 9.90294, 9.42648, 8.85324, 8.50121, 7.89834, 7.65197, 7.22768, 6.7755, 6.34855, 5.98336, 5.76555, 5.38056, 5.11024, 4.7748, 4.59117, 4.23247, 4.00814, 3.79607, 3.68702, 3.3767, 3.16309, 2.98282, 2.8095, 2.65875, 2.50561, 2.32516, 2.16357, 2.03235, 1.84061, 1.72628, 1.62305, 1.48916, 1.38784, 1.28366, 1.24693, 1.18552, 1.16085, 1.12596, 1.09298, 1.07402, 1.06105, 1.02954};
   for(int i=hiBinLow; i<hiBinHigh; i++)  w+=Ncoll[i]/(hiBinHigh-hiBinLow);
   return w;
}

double FindNPartAverage(int hiBinLow, int hiBinHigh)
{
   double w=0;
   static const int nbins = 200;
   static const double Npart[nbins] = {401.99, 398.783, 396.936, 392.71, 387.901, 383.593, 377.914, 374.546, 367.507, 361.252, 356.05, 352.43, 345.701, 341.584, 335.148, 330.581, 325.135, 320.777, 315.074, 310.679, 306.687, 301.189, 296.769, 291.795, 287.516, 283.163, 277.818, 274.293, 269.29, 265.911, 260.574, 256.586, 252.732, 249.194, 245.011, 241.292, 236.715, 232.55, 229.322, 225.328, 221.263, 218.604, 214.728, 210.554, 206.878, 203.924, 200.84, 196.572, 193.288, 189.969, 186.894, 183.232, 180.24, 177.36, 174.008, 171.222, 168.296, 165.319, 162.013, 158.495, 156.05, 154.218, 150.559, 148.455, 145.471, 142.496, 139.715, 137.395, 134.469, 131.926, 129.817, 127.045, 124.467, 122.427, 119.698, 117.607, 114.543, 112.662, 110.696, 108.294, 105.777, 103.544, 101.736, 99.943, 97.4951, 95.4291, 93.2148, 91.2133, 89.5108, 87.2103, 85.7498, 83.5134, 81.9687, 79.7456, 78.1684, 76.4873, 74.7635, 72.761, 71.0948, 69.6102, 67.7806, 66.2215, 64.5813, 63.0269, 61.4325, 59.8065, 58.2423, 57.2432, 55.8296, 54.2171, 52.8809, 51.3254, 49.9902, 48.6927, 47.5565, 46.136, 44.8382, 43.6345, 42.3964, 41.4211, 39.9681, 39.178, 37.9341, 36.9268, 35.5626, 34.5382, 33.6912, 32.8156, 31.6695, 30.6552, 29.7015, 28.8655, 27.9609, 27.0857, 26.105, 25.3163, 24.4872, 23.6394, 23.0484, 22.2774, 21.4877, 20.5556, 19.9736, 19.3296, 18.5628, 17.916, 17.2928, 16.6546, 16.1131, 15.4013, 14.8264, 14.3973, 13.7262, 13.2853, 12.8253, 12.2874, 11.7558, 11.2723, 10.8829, 10.4652, 9.96477, 9.6368, 9.09316, 8.84175, 8.48084, 8.05694, 7.64559, 7.29709, 7.07981, 6.70294, 6.45736, 6.10284, 5.91788, 5.5441, 5.33311, 5.06641, 4.96415, 4.6286, 4.38214, 4.2076, 4.01099, 3.81054, 3.63854, 3.43403, 3.23244, 3.08666, 2.86953, 2.74334, 2.62787, 2.48354, 2.38115, 2.26822, 2.23137, 2.1665, 2.14264, 2.10636, 2.07358, 2.05422, 2.04126, 2.00954};
   for(int i=hiBinLow; i<hiBinHigh; i++)  w+=Npart[i]/(hiBinHigh-hiBinLow);
   return w;
}

std::pair<double, double> WTAAxis(std::vector<double> &Eta, std::vector<double> &Phi, std::vector<double> &PT)
{
   return WTAAxisTable(Eta, Phi, PT);
}

std::pair<double, double> WTAAxisCA(std::vector<double> Eta, std::vector<double> Phi, std::vector<double> PT)
{
   std::pair<double, double> Result;

   if(Eta.size() == 0)
      return Result;

   std::vector<PseudoParticle> Particles;
   for(int i = 0; i < (int)Eta.size(); i++)
      Particles.push_back(PseudoParticle(Eta[i], Phi[i], PT[i]));
   std::sort(Particles.begin(), Particles.end());

   while(Particles.size() >= 2)
   {
      int N = Particles.size();

      int BestI = -1, BestJ = -1;
      double BestD2 = -1;

      // Loop over particles
      for(int i = 0; i < N; i++)
      {
         for(int j = i + 1; j < N; j++)
         {
            double DEta = Particles[i].Eta - Particles[j].Eta;
            double DPhi = DeltaPhi(Particles[i].Phi, Particles[j].Phi);
            double PTMin = std::min(Particles[i].PT, Particles[j].PT);
            // double D2 = (DEta * DEta + DPhi * DPhi) / (PTMin * PTMin);
            double D2 = DEta * DEta + DPhi * DPhi;

            if(BestD2 < 0)
            {
               BestI = i;
               BestJ = j;
               BestD2 = D2;
               continue;
            }

            // Since things are eta-sorted, if we hit something larger than best already, we skip the rest
            // This is true only for C/A case
            if(DEta * DEta > BestD2)   
               break;

            if(D2 < BestD2)
            {
               BestI = i;
               BestJ = j;
               BestD2 = D2;
            }
         }
      }

      // Now we found the closest pair, we merge particles
      if(Particles[BestI].PT > Particles[BestJ].PT)
      {
         Particles[BestI].PT = Particles[BestI].PT + Particles[BestJ].PT;
         Particles.erase(Particles.begin() + BestJ);
      }
      else
      {
         Particles[BestJ].PT = Particles[BestI].PT + Particles[BestJ].PT;
         Particles.erase(Particles.begin() + BestI);
      }
   }

   Result.first = Particles[0].Eta;
   Result.second = Particles[0].Phi;

   return Result;
}

std::pair<double, double> WTAAxisTable(std::vector<double> Eta, std::vector<double> Phi, std::vector<double> PT)
{
   int N = Eta.size();

   std::vector<bool> Alive(N, true);
   std::vector<int> ClosestIndex(N);
   std::vector<double> ClosestD2(N);

   // First we initialize the tables
   for(int i = 0; i < N; i++)
   {
      int BestIndex = -1;
      double BestD2 = -1;

      for(int j = 0; j < N; j++)
      {
         if(i == j)
            continue;
            
         double DEta = Eta[i] - Eta[j];
         double DPhi = DeltaPhi(Phi[i], Phi[j]);
         double PTMin = std::min(PT[i], PT[j]);
         double D2 = (DEta * DEta + DPhi * DPhi) / (PTMin * PTMin);
         // double D2 = DEta * DEta + DPhi * DPhi;

         if(BestD2 < 0 || D2 < BestD2)
         {
            BestIndex = j;
            BestD2 = D2;
         }
      }

      ClosestIndex[i] = BestIndex;
      ClosestD2[i] = BestD2;
   }

   // Now we loop.  If there are N particles we need to recombine N - 1 times
   for(int iS = 0; iS < N - 1; iS++)
   {
      // First find the best pair from the table
      int BestI = -1;
      for(int i = 0; i < N; i++)
      {
         if(Alive[i] == false)
            continue;
         if(BestI < 0 || ClosestD2[i] <= ClosestD2[BestI])
            BestI = i;
      }

      // Now merge the two
      int BestJ = ClosestIndex[BestI];
      int NewI = BestI;
      
      // cout << Eta[BestI] << " " << Eta[BestJ] << endl;
      // cout << ClosestD2[BestI] << endl;

      if(PT[BestI] > PT[BestJ])
      {
         PT[BestI] = PT[BestI] + PT[BestJ];
         Alive[BestJ] = false;
         NewI = BestI;
      }
      else
      {
         PT[BestJ] = PT[BestI] + PT[BestJ];
         Alive[BestI] = false;
         NewI = BestJ;
      }

      // Finally update the tables
      // First we update ones where closest is the old NewI
      for(int i = 0; i < N; i++)
      {
         if(Alive[i] == false)
            continue;

         if(ClosestIndex[i] == BestI || ClosestIndex[i] == BestJ)   // need full reevaluation (?)
         {
            int BestIndex = 0;
            double BestD2 = -1;
            for(int j = 0; j < N; j++)
            {
               if(Alive[j] == false)   continue;
               if(i == j)              continue;
         
               double DEta = Eta[i] - Eta[j];
               double DPhi = DeltaPhi(Phi[i], Phi[j]);
               double PTMin = std::min(PT[i], PT[j]);
               double D2 = (DEta * DEta + DPhi * DPhi) / (PTMin * PTMin);
               // double D2 = DEta * DEta + DPhi * DPhi;
               
               if(BestD2 < 0 || D2 < BestD2)
               {
                  BestIndex = j;
                  BestD2 = D2;
               }
            }

            ClosestIndex[i] = BestIndex;
            ClosestD2[i] = BestD2;
         }
      }

      // Then we update the NewI with everyone else
      ClosestIndex[NewI] = -1;
      ClosestD2[NewI] = -1;
      for(int j = 0; j < N; j++)
      {
         if(Alive[j] == false)
            continue;
         if(j == NewI)
            continue;

         double DEta = Eta[NewI] - Eta[j];
         double DPhi = DeltaPhi(Phi[NewI], Phi[j]);
         double PTMin = std::min(PT[NewI], PT[j]);
         double D2 = (DEta * DEta + DPhi * DPhi) / (PTMin * PTMin);
         // double D2 = DEta * DEta + DPhi * DPhi;

         if(ClosestD2[NewI] < 0 || D2 < ClosestD2[NewI])
         {
            ClosestIndex[NewI] = j;
            ClosestD2[NewI] = D2;
         }
         if(D2 < ClosestD2[j])
         {
            ClosestIndex[j] = NewI;
            ClosestD2[j] = D2;
         }
      }
   }

   std::pair<double, double> Result;
   
   for(int i = 0; i < N; i++)
   {
      if(Alive[i] == false)
         continue;

      Result.first = Eta[i];
      Result.second = Phi[i];
   }
   
   return Result;
}

void ConstituentSubtraction(std::vector<double> &Eta, std::vector<double> &Phi, std::vector<double> &PT,
   std::vector<double> *EtaMin, std::vector<double> *EtaMax, std::vector<double> *Rho,
   double MaxR)
{
   if(EtaMin == nullptr || EtaMax == nullptr || Rho == nullptr)
      return;

   double GhostA = 0.005;
   double GhostDPhi = sqrt(GhostA);
   double GhostDEta = sqrt(GhostA);

   // Setup ghosts
   std::vector<double> GhostEta;
   std::vector<double> GhostPhi;
   std::vector<double> GhostPT;

   int NBin = EtaMin->size();
   for(int iBin = 0; iBin < NBin; iBin++)
   {
      double NPhi = std::ceil(2 * M_PI / GhostDPhi);
      double NEta = std::ceil(((*EtaMax)[iBin] - (*EtaMin)[iBin]) / GhostDEta);
      double A = ((*EtaMax)[iBin] - (*EtaMin)[iBin]) / NEta * (2 * M_PI) / NPhi;

      for(int iEta = 0; iEta < NEta; iEta++)
      {
         for(int iPhi = 0; iPhi < NPhi; iPhi++)
         {
            GhostEta.push_back((*EtaMin)[iBin] + ((*EtaMax)[iBin] - (*EtaMin)[iBin]) / NEta * (iBin + 0.5));
            GhostPhi.push_back(-M_PI + 2 * M_PI / NPhi * (iPhi + 0.5));
            GhostPT.push_back(A * (*Rho)[iBin]);
         }
      }
   }

   if(NBin == 0)
      return;

   // Run CS
   DoCSBruteForce(Eta, Phi, PT, GhostEta, GhostPhi, GhostPT, MaxR * MaxR);
}

void DoCSBruteForce(std::vector<double> &Eta, std::vector<double> &Phi, std::vector<double> &PT,
   std::vector<double> &GhostEta, std::vector<double> &GhostPhi, std::vector<double> &GhostPT,
   double MaxR2)
{
   std::vector<PseudoParticle> Particles;
   for(int i = 0; i < (int)Eta.size(); i++)
      Particles.push_back(PseudoParticle(Eta[i], Phi[i], PT[i]));
   std::sort(Particles.begin(), Particles.end());
   std::vector<bool> ParticlesAlive(Particles.size(), true);

   std::vector<PseudoParticle> Ghosts;
   for(int i = 0; i < (int)GhostEta.size(); i++)
      Ghosts.push_back(PseudoParticle(GhostEta[i], GhostPhi[i], GhostPT[i]));
   std::sort(Ghosts.begin(), Ghosts.end());
   std::vector<bool> GhostsAlive(Ghosts.size(), true);

   bool Changed = true;
   while(Changed == true)
   {
      Changed = false;

      int OverallBestI = -1;
      int OverallBestJ = -1;
      double OverallBestR2 = -1;
      for(int i = 0; i < (int)Particles.size(); i++)
      {
         if(ParticlesAlive[i] == false)
            continue;

         int StartJ = 0;
         if(OverallBestR2 > 0)
         {
            double Limit = Particles[i].Eta - sqrt(OverallBestR2);
            int MinJ = 0;
            int MaxJ = Ghosts.size();

            if(Ghosts[MinJ].Eta > Limit)   // min already above limit.  Stop.
               StartJ = MinJ;
            else if(Ghosts[MaxJ].Eta < Limit)   // max still below limit.  Stop.
               StartJ = MaxJ;
            else   // min and max sandwich the limit.  Binary search.
            {
               while(MaxJ - MinJ > 1)
               {
                  int Middle = (MinJ + MaxJ) / 2;
                  if(Ghosts[Middle].Eta < Limit)
                     MinJ = Middle;
                  else
                     MaxJ = Middle;
               }

               StartJ = MinJ;
            }
         }

         int BestJ = -1;
         double BestR2 = -1;
         for(int j = StartJ; j < (int)Ghosts.size(); j++)
         {
            if(GhostsAlive[j] == false)
               continue;

            double DEta = Particles[i].Eta - Ghosts[j].Eta;
            double DPhi = DeltaPhi(Particles[i].Phi, Ghosts[j].Phi);
            double DR2 = DEta * DEta + DPhi * DPhi;
            
            if(OverallBestR2 > 0 && j != StartJ && DEta * DEta > OverallBestR2)
               break;

            if(BestR2 < 0 || DR2 < BestR2)
            {
               BestJ = j;
               BestR2 = DR2;
            }
         }

         if(OverallBestR2 < 0 || OverallBestR2 > BestR2)
         {
            OverallBestI = i;
            OverallBestJ = BestJ;
            OverallBestR2 = BestR2;
         }
      }

      if(OverallBestR2 >= 0 && (MaxR2 < 0 || OverallBestR2 < MaxR2))   // found a pair!
      {
         Changed = true;

         if(Particles[OverallBestI].PT > Ghosts[OverallBestJ].PT)
         {
            Particles[OverallBestI].PT = Particles[OverallBestI].PT - Ghosts[OverallBestJ].PT;
            Ghosts[OverallBestJ].PT = 0;
            GhostsAlive[OverallBestJ] = false;
         }
         else
         {
            Ghosts[OverallBestJ].PT = Ghosts[OverallBestJ].PT - Particles[OverallBestI].PT;
            Particles[OverallBestI].PT = 0;
            ParticlesAlive[OverallBestI] = false;
         }
      }
   }

   // cout << Particles.size() << " " << PT.size() << ", " << Ghosts.size() << " " << GhostPT.size() << endl;

   PT.clear();
   Eta.clear();
   Phi.clear();

   for(int i = 0; i < (int)Particles.size(); i++)
   {
      PT.push_back(Particles[i].PT);
      Eta.push_back(Particles[i].Eta);
      Phi.push_back(Particles[i].Phi);
   }

   return;
}

std::string InfoString(std::string Info)
{
   return "\"" + Info + "\"";
}

std::string InfoString(char *Info)
{
   if(Info == nullptr)
      return "";
   return string(Info);
}

std::string InfoString(int Info)
{
   return to_string(Info);
}

std::string InfoString(double Info)
{
   return to_string(Info);
}

std::string InfoString(float Info)
{
   return to_string(Info);
}

std::string InfoString(bool Info)
{
   if(Info == false)
      return "false";
   if(Info == true)
      return "true";
   return "";
}

std::string InfoString(std::vector<std::string> Info)
{
   if(Info.size() == 0)
      return "{}";

   std::string Result = "{" + InfoString(Info[0]);
   for(int i = 1; i < (int)Info.size(); i++)
      Result = Result + "," + InfoString(Info[i]);
   Result = Result + "}";

   return Result;
}


