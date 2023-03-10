#include <cmath>

#define M_MU 0.1056583755

// Function declarations

double DeltaPhi(double Phi1, double Phi2);
double PhiRangePositive(double Phi);
double PhiRangeSymmetric(double Phi);


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
   while(Phi < -M_PI)   Phi = Phi + 2 * M_PI;
   while(Phi > +M_PI)   Phi = Phi - 2 * M_PI;
   return Phi;
}

