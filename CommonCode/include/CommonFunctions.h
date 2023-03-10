#include <cmath>

#define M_MU 0.1056583755

// Function declarations

double DeltaPhi(double Phi1, double Phi2);




// Function implementations

double DeltaPhi(double Phi1, double Phi2)
{
   double DPhi = Phi1 - Phi2;
   while(DPhi < -M_PI)   DPhi = DPhi + 2 * M_PI;
   while(DPhi > +M_PI)   DPhi = DPhi - 2 * M_PI;
   return DPhi;
}


