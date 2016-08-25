////////////////////////////////////////////////////////////////
// Program: targetseptum.cc
// Author: N. Hirlinger Saylor
// Date: 5 May, 2016
// Purpose: To calculate the target positions for various super-crex angles
// 
//
////////////////////////////////////////////////////////////////
#include "Rtypes.h"
#include "TMath.h"
#include <iostream>
using namespace std;



Int_t targetseptum(Float_t t_target){
  
  Float_t z_hall   = 0.0;
  Float_t z_septum = 69.99937; //Set by CREXI experiment
  
  Float_t t_hrs    =12.5;      //Minimum angle of HRS
  //Float_t t_target = 4.5;

  Float_t z_target =  z_septum * ( 1.0 - TMath::Tan( t_hrs * TMath::DegToRad() ) / TMath::Tan( t_target * TMath::DegToRad() ) );

  //cout << z_target << " " << z_hall << " " << z_septum << ": " << t_target << endl;
  cout << z_target << endl;

  return 0;
}
