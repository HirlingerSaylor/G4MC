#include <iostream>
#include "Rtypes.h"
#include "TMath.h"
#include "HRSDatabase.hh"
#include <iomanip>
using namespace std;

int main(){

  Float_t ene_mev = 2200.;
  //Float_t ene_mev = 2000.;
  //Float_t ene_mev = 2500.;
  Float_t theta_degr = 4.;
  //Float_t theta_degr = 5.;

  
  HRSDatabase* mydatabase = new HRSDatabase(1);
  Float_t XS = mydatabase->Interpolate(ene_mev, theta_degr, 0, 0)/1000.;//unit conversion, so divide by 1000.
  Float_t a0 = mydatabase->Interpolate(ene_mev, theta_degr, 0, 1);
  Float_t a1 = mydatabase->Interpolate(ene_mev, theta_degr, 1, 1);
  Float_t I  = 150. * 6.25e12;
  Float_t xi = 0.33;
  Float_t T  = 0.005 * 100; //cm
  Float_t rho= 1.55; // tgt density (g/cm^3)
  Float_t dom= 0.00293;
  //float domega = 0.0037;
  Float_t avo= 0.602;
  Float_t A  = 48.;
  Float_t pol= 0.85;

  //Float_t e_p = 0.01;
  Float_t e_p = 0.0; //already included in total systematics
  Float_t e_d = 1.06;
  Float_t e_s = 0.0125;

  Float_t R  = XS * I * xi * T * rho * dom * avo / A / 1000000.; //MHz
  
  Float_t daa= -( a1 - a0 ) / a0;

  Float_t xcnt = 2.0 * ( R * 1000000 ) * 35. * 24. * 3600;
  
  Float_t e_a     = 1.0 / TMath::Sqrt(xcnt) * e_d;
  Float_t newdaa  = e_a / (pol * a0);
  Float_t drr     = 0.01 * newdaa / daa;
  Float_t blowup  = (TMath::Sqrt(e_p*e_p + newdaa*newdaa + e_s*e_s))/newdaa;
  Float_t drrtot  = drr * blowup * 100.;
  Float_t drrfm   = 3.59 * drrtot / 100.;

  int setw_n = 12;
  
  cout << setw(setw_n) <<"E"     << setw(setw_n) << "theta" << endl;
  cout << setw(setw_n) << ene_mev<< setw(setw_n) << theta_degr << endl;
  cout << setw(setw_n) <<"XS"    << setw(setw_n) << "I"  << setw(setw_n) << "xi" << setw(setw_n) << "T"  
       << setw(setw_n) <<"rho"   << setw(setw_n) << "dom"<< setw(setw_n) << "avo"<< setw(setw_n) << "A"
       << setw(setw_n) << "R"    << setw(setw_n) << "daa"<< setw(setw_n) << "a0" << setw(setw_n) << "newdaa"
       << setw(setw_n) << "drtot (%)"<< setw(setw_n) << "drtot (fm)"<< endl; 
  cout << setw(setw_n) << XS     << setw(setw_n) << I    << setw(setw_n) << xi   << setw(setw_n) << T  
       << setw(setw_n) << rho    << setw(setw_n) << dom  << setw(setw_n) << avo  << setw(setw_n) << A
       << setw(setw_n) << R      << setw(setw_n) << daa  << setw(setw_n) << a0   << setw(setw_n) << newdaa
       << setw(setw_n) << drrtot << setw(setw_n) << drrfm<< endl;
    //cout << R << endl;
  
  delete mydatabase;
  return 0;
}
