#include "math.h"
#include "TMath.h"

double ElecCalib(double e_raw, double pt, double eta, 
		 double phi, double etiso, double eoverp, double mindrjet)
{
  double dummy=pt*eta*phi*etiso*eoverp*mindrjet;
  double energy = e_raw;
  // if (fabs(eta)>1.5) energy = energy * 91.2/78.2;
  // else if (fabs(eta)>2.0) energy = energy * 91.2/85.4;
  return energy;
} 
