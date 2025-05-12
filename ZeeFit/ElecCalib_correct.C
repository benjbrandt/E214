#include "math.h"
#include "TMath.h"

double ElecCalib(double e_raw, double pt, double eta, 
		 double phi, double etiso, double eoverp, double mindrjet)
{
  double dummy=pt*eta*phi*etiso*eoverp*mindrjet;
  double energy = e_raw;
  //if (fabs(eta)>1.5) energy = energy * 91.2/89.89;
  //else if (fabs(eta)>2.0) energy = energy * 91.2/85.4;
  //if (0.5<fabs(eta)<1) energy = energy * 91.2/89.82;  
//   if  (0<fabs(eta)<0.2) energy = energy * 91.2/90.14; 
//   else if (0.2<fabs(eta)<0.4) energy = energy * 91.2/90.1;
//   else if (0.4<fabs(eta)<0.6) energy = energy * 91.2/90.07;
//   else if (0.6<fabs(eta)<0.8) energy = energy * 91.2/89.79;
//   else if (0.8<fabs(eta)<1.0) energy = energy * 91.2/89.47;
//   else if (1.0<fabs(eta)<1.2) energy = energy * 91.2/89.50;
//   else if (1.2<fabs(eta)<1.4) energy = energy * 91.2/89.48;
//   else if (1.4<fabs(eta)<1.6) energy = energy * 91.2/90.10;
//   else if (1.6<fabs(eta)<1.8) energy = energy * 91.2/91.25;
//   else if (1.8<fabs(eta)<2.0) energy = energy * 91.2/91.27;
//   else if (2.0<fabs(eta)<2.2) energy = energy * 91.2/89.03;
//   else if (2.2<fabs(eta)<2.4) energy = energy * 91.2/88.11;
//   else if (2.4<fabs(eta)<2.5) energy = energy * 91.2/87.77;

  
    if  (0.<fabs(eta)<0.5) energy = energy * 91.2/90.18; 
    else if (0.5<fabs(eta)<1.) energy = energy * 91.2/90.12;
    else if (1<fabs(eta)<1.5) energy = energy * 91.2/89.8;
    else if (1.5<fabs(eta)<2.) energy = energy * 91.2/91.22;
    else if (2.<fabs(eta)<2.5) energy = energy * 91.2/88.72;  
   
//    if (20<pt && pt<30) energy = energy * 91.2/90.86;
//    else if (30<pt && pt<40) energy = energy * 91.2/90.92;
//    else if (40<pt && pt<50) energy = energy * 91.2/91.95;
//    else if (50<pt && pt<60) energy = energy * 91.2/92.49;
/*   
    if (20<e_raw && e_raw<30) energy = energy * 91.2/91.68;
    else if (30<e_raw && e_raw<40) energy = energy * 91.2/92.74;
    else if (40<e_raw && e_raw<50) energy = energy * 91.2/92.02;
    else if (50<e_raw && e_raw<60) energy = energy * 91.2/92.13;
    else if (60<e_raw && e_raw<80) energy = energy * 91.2/91.96;
    else if (e_raw > 80) energy = energy * 91.2/92.64;*/
   
  
//   if (0 <= phi && phi<=0.5) energy = energy * 91.2/90.06;
//   else if (phi>0.5) energy = energy * 91.2/91.19;

  //if (0 <= fabs(eta) < 1) energy = energy * 91.2/91.1;
  //else if  (1 <= fabs(eta) <= 2) energy = energy * 91.2/
  //else if (fabs(eta)>2) energy  = energy * 91.2/
  return energy;
} 
