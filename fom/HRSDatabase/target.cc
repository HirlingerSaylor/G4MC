#include "Rtypes.h"
#include <iostream>
#include "TString.h"
#include "targetseptum.cc"
using namespace std;

Int_t main(int argc, char* argv[]){
  TString input = argv[1];
  Float_t angle = input.Atoi();
  cout << "septum: 69.99937, " << "angle: " << angle << ", target: ";
  targetseptum(angle);
  return 0;
}
