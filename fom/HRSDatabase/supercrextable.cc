#include "Rtypes.h"
#include <iostream>
#include <iomanip>
#include "TMath.h"
#include "HRSDatabase.hh"
#include "targetseptum.cc"
using namespace std;

Int_t main(){
  
  HRSDatabase* mydatabase = new HRSDatabase(1);//1 is crex - that is all we will be using here  
  
  const Int_t n        = 6;
  Float_t E[n]         = {2.20, 2.06, 3.09, 4.00, 4.00, 4.00};
  Float_t q[n];

  Float_t M            = 48. * .931494095;
  Float_t fmtogev      = 0.197;
  Int_t   w            = 15;

    cout << setw(w) << "q"
	 << setw(w) << "energy"
	 << setw(w) << "cross section"
	 << setw(w) << "asymmetry"
	 << setw(w) << "theta"
	 << setw(w) << "z_target"
	 << endl;

  for(Int_t i = 0; i < n; i++){
    if( i != 0 ){
      q[i] = 0.45 * ( i + 1 );
    }else{
      q[0] = 0.78;
    }
    Float_t Q2           = TMath::Power(q[i] * fmtogev, 2);//convert inverse fermis to GeV
    Float_t sin2thetaby2 = Q2 / ( 4 * E[i] * E[i] + 2 * E[i] / M * Q2 );
    Float_t sinthetaby2  = TMath::Sqrt( sin2thetaby2 );
    Float_t theta        = 2 * TMath::ASin( sinthetaby2 ) * TMath::RadToDeg();
    
    Float_t xs           = mydatabase->Interpolate(E[i] * 1000., theta, 0, 0);//originally mb without dividing// 1000.;//unit conversion, so divide by 1000.
    Float_t asy          = mydatabase->Interpolate(E[i] * 1000., theta, 0, 1) * 1000000.;//ppm

    cout << setw(w) << q[i]
	 << setw(w) << E[i]
	 << setw(w) << xs
	 << setw(w) << asy
	 << setw(w) << theta
	 << setw(w);
    targetseptum(theta);
  }
  
  
  for(Int_t i = 0; i < 100; i++){
    Float_t q            =0.1 * i;
    Float_t E            =2.2;
    Float_t Q2           = TMath::Power(q * fmtogev, 2);//convert inverse fermis to GeV
    Float_t sin2thetaby2 = Q2 / ( 4 * E * E + 2 * E / M * Q2 );
    Float_t sinthetaby2  = TMath::Sqrt( sin2thetaby2 );
    Float_t theta        = 2 * TMath::ASin( sinthetaby2 ) * TMath::RadToDeg();
    
    Float_t xs           = mydatabase->Interpolate(E * 1000., theta, 0, 0);//originally mb without dividing// 1000.;//unit conversion, so divide by 1000.
    Float_t asy          = mydatabase->Interpolate(E * 1000., theta, 0, 1) * 1000000.;//ppm
    cout << setw(w) << q
	 << setw(w) << E
	 << setw(w) << xs
	 << setw(w) << asy
	 << setw(w) << theta
	 << setw(w);
    targetseptum(theta);
  }
  
  return 0;
  
}
