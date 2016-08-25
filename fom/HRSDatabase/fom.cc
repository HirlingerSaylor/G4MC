#include <iostream>
#include <string>
#include <cstdio>
#include <fstream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>
#include "HRSDatabase.hh"
#include "TString.h"
using namespace std;

int main(int argc, char* argv[]){

  if( argc != 3 ){
    cout << "Incorrect number of arguments." << endl;
    cout << "Usage: ./fom [1 <= model <= 5] [0 <= col <= 2]" << endl;
    exit (EXIT_FAILURE);
  }
  int new_col = -1;
  //cout << argv[2] << "test" <<endl;
  if( (string)argv[2] == "0" ){
    new_col = 0;
  }else if ( (string)argv[2] == "1" ){
    new_col = 1;
  }else if ( (string)argv[2] == "2" ){
    new_col = 2;
  }else if ( (string)argv[2] == "3" ){
    new_col = 3;
  }else if ( (string)argv[2] == "4" ){
    new_col = 4;
  }else{
    cout << "Are you using new or old collimator?" << endl;
    cout << "Usage: ./fom [1 <= model <= 5] [new|old]" << endl;
    exit (EXIT_FAILURE);
  }
  int model = atoi(argv[1]);
  cout << "Using model " << model << endl;

  if( model < 1 || model > 5 ){
    cout << "Invalid model." << endl;
    exit (EXIT_FAILURE);
  }

  ofstream OUTFILE;
  if( model == 1 ){
    if( new_col > 0 ){
      cout << "PREX I does not have new collimator mode" << endl;
      exit (EXIT_FAILURE);
    }
    OUTFILE.open("fom_prexI.dat");
  }else if( model == 2 ){
    if( new_col == 4 ){
      OUTFILE.open("fom_prexII_col4.dat");
    }else if( new_col == 3 ){
      OUTFILE.open("fom_prexII_col3.dat");
    }else if( new_col == 2 ){
      OUTFILE.open("fom_prexII_col2.dat");
    }else if( new_col == 1 ){
      OUTFILE.open("fom_prexII_col1.dat");
    }else{
      OUTFILE.open("fom_prexII_col0.dat");
    }
  }else if ( model == 3 ){
    if( new_col == 4 ){
      OUTFILE.open("fom_crex_col4.dat");
    }else if( new_col == 3 ){
      OUTFILE.open("fom_crex_col3.dat");
    }else if( new_col == 2 ){
      OUTFILE.open("fom_crex_col2.dat");
    }else if( new_col == 1 ){
      OUTFILE.open("fom_crex_col1.dat");
    }else{
      OUTFILE.open("fom_crex_col0.dat");
    }     
  }else if ( model == 4 ){
    if( new_col == 4 ){
      OUTFILE.open("fom_prex_4_deg_col4.dat");
    }else if( new_col == 3 ){
      OUTFILE.open("fom_prex_4_deg_col3.dat");
    }else if( new_col == 2 ){
      OUTFILE.open("fom_prex_4_deg_col2.dat");
    }else if( new_col == 1 ){
      OUTFILE.open("fom_prex_4_deg_col1.dat");
    }else{
      OUTFILE.open("fom_prex_4_deg_col0.dat");
    }     
  }else if ( model == 5 ){
    OUTFILE.open(Form("fom_supercrex%d.dat", new_col + 1));
  }else{
    cout << "Something is terribly wrong!" << endl;
  }
  
  //int model = 0;//0 is prex, 1 is crex, 2 is extended prex table

  int hrsmodel;
  if( model == 1 || model == 2 || model == 4){
    hrsmodel = 0;//use old table
    // hrsmodel = 2;//use extended table
  }else if( model == 3 || model == 5){
    hrsmodel = 1;
  }

  HRSDatabase* mydatabase = new HRSDatabase(hrsmodel);
  //mydatabase->PrintTable(0);

  float tdens;
  float tlen;
  float current;
  float anum;
  float ene_min;
  float ene_step;
  int   n_ene_steps;
  float theta_degr;
  if( model == 1 || model == 2 || model == 4){
    tdens   = 11.35; // tgt density (g/cm^3)  
    //tlen    = 0.000135;  // tgt len (m)
    tlen    = 0.0005;  // tgt len (m)
    tlen    = tlen * 100; // need cm 
    current = 70.;   // microAmps (uA)  
    anum    = 208.;  // atomic num.
    ene_min = 0.6;   //GeV
    //ene_min = 1.0;   //GeV
    ene_step= 0.05;
    //ene_step= 0.1;
    n_ene_steps= 13;
    //n_ene_steps= 16;
    theta_degr = 5.;
    if( model == 4 )
      theta_degr = 4.;
  }else if( model == 3 || model == 5 ){
    tdens   = 1.55; // tgt density (g/cm^3)  
    //tlen    = 0.0065;  // tgt len (m)
    tlen    = 0.005;  // tgt len (m)
    tlen    = tlen * 100; // need cm 
    current = 150.;   // microAmps (uA)
    anum    = 48.;   // atomic num.  
    ene_min = 0.5;   //GeV
    ene_step= 0.05;
    n_ene_steps= 62;
    theta_degr = 4.;
    //theta_degr = 5.;
  }

  current       = current * 6.25e12;    // 100 uA = 6.25e14 e- / sec
  //cout << current << endl;

  int setw_n = 12;

  cout << setw(setw_n) << "I"    << setw(setw_n) << "tlen"
       << setw(setw_n) <<"rho"   << setw(setw_n) << "A" << endl;
  cout << setw(setw_n) << current<< setw(setw_n) << tlen
       << setw(setw_n) << tdens  << setw(setw_n) << anum << endl;

  float ene, ene_mev,xacc, theta_rad;
  float daa, rate, asyavg, fom, newdaa, drr, drrtot, drrtot2, blowup, blowup2;
  float daasum, ratesum, asysum, xnorm, q2sum, thetasum;
  float asy0, asy1, crsec;
  //float domega = 0.0037;
  float domega = .00293;
  float xi = .33;
  
  char schar[200];
  
  FILE* fd;

  //cout << current << " " << tlen << " " << tdens << " " << domega << " " << anum << endl;
  //for (int iene=0; iene < 30; iene++) {
  for (int iene=0; iene < n_ene_steps; iene++) {
    
    ene = ene_min + ene_step*((float)iene); // GeV
    ene_mev = ene_min * 1000. + ene_step * 1000. * iene; // MeV

    
    ratesum = 0;
    xnorm=0;
    asysum = 0;
    daasum = 0;
    thetasum = 0;
    q2sum = 0;
    
    //cout << "Reading acceptance function." << endl;
    //fd=fopen("./nickie_accept2.dat", "r");
    if( model == 1 ){
      //cout << "model 1: opening nickie_accept_prex_I.dat" << endl;
      if( new_col > 0){
	cout << "PREX I does not have new collimator mode" << endl;
	exit (EXIT_FAILURE);
      }
      fd=fopen("./accept/nickie_accept_prex_I.dat", "r");
    }else if ( model == 2 ){
      //cout << "model 2: opening nickie_accept_prex_II.dat" << endl;
      if( new_col == 1){
	fd=fopen("./accept/nickie_accept_prex_II_col1.dat", "r");
      }else if( new_col == 2){
	fd=fopen("./accept/nickie_accept_prex_II_col2.dat", "r");
      }else if( new_col == 3){
	fd=fopen("./accept/nickie_accept_prex_II_col3.dat", "r");
      }else if( new_col == 4){
	fd=fopen("./accept/nickie_accept_prex_II_col4.dat", "r");
      }else{
	fd=fopen("./accept/nickie_accept_prex_II_col0.dat", "r");
      }
    }else if ( model == 3 ){
      //cout << "model 2: opening nickie_accept_prex_II.dat" << endl;
      if( new_col == 1){
	fd=fopen("./accept/nickie_accept_crex_col1.dat", "r");
      }else if( new_col == 3){
	fd=fopen("./accept/nickie_accept_crex_col3.dat", "r");
      }else if( new_col == 4){
	fd=fopen("./accept/nickie_accept_crex_col4.dat", "r");
      }else if( new_col == 2){
	fd=fopen("./accept/nickie_accept_crex_col2.dat", "r");
	//fd=fopen("./accept/nickie_accept_crex_5_degrees.dat", "r");
      }else{
	fd=fopen("./accept/nickie_accept_crex_col0.dat", "r");
      }
    }else if ( model == 4 ){
      //cout << "model 2: opening nickie_accept_prex_II.dat" << endl;
      if( new_col == 1){
	return -1;
	//fd=fopen("./accept/nickie_accept_crex_col1.dat", "r");
      }else if( new_col == 2){
	fd=fopen("./accept/nickie_accept_prex_4_deg_col2.dat", "r");
      }else{
	return -1;
	//fd=fopen("./accept/nickie_accept_crex_col0.dat", "r");
      }
    }else if ( model == 5 ){
      fd=fopen(Form("./accept/nickie_accept_supercrex%d.dat", new_col + 1), "r");
    }
    //fd=fopen("./accept.dat", "r");
    //cout << "File open." << endl;
    while(fgets(schar,100,fd)!=NULL) {
      //cout << "Scanning." << endl;
      sscanf(schar, "%f  %f", &theta_degr, &xacc);
      //cout << "Scanned!" << endl;
      theta_rad = 3.1415926*theta_degr/180.0;
      //CrossSection(ene,theta_rad,0);
      crsec = mydatabase->Interpolate(ene_mev, theta_degr, 0, 0)/1000.;
      //cout << ene_mev << " " << theta_degr << " " << crsec << endl;
      asy0  = mydatabase->Interpolate(ene_mev, theta_degr, 0, 1);
      asy1  = mydatabase->Interpolate(ene_mev, theta_degr, 1, 1);
      //cout << ene_mev << " " << theta_degr << " " << crsec << " " << asy0 << " " << asy1 << endl;
      //Asymmetry(ene,theta_rad,0);
      //Asymmetry(ene,theta_rad,1);
      daa = 0;
      if (asy0 != 0)
	daa = -(asy1-asy0)/asy0;
      float dtheta = 0.06 * 3.141592654 / 180.;
      //float dphi   = 0.06;//rad already, 0.06, in rectangular approximation
      //float dphi   = 70. * 3.141592654 / 180.;
      float dphi   = 80. * 3.141592654 / 180.;
      domega = sin( theta_rad ) * dtheta * dphi;
      rate = xacc * current * crsec * 0.602 * tlen * tdens * domega / anum;// * xi;
      ratesum += rate;  
      daasum += daa * rate;
      asysum += asy0 * rate;
      thetasum += theta_degr * rate;
      xnorm += xacc;
      if ( 0) { 
	cout << "energy "<<ene<<"  theta "<<theta_degr<<endl;
	cout << "accept  "<<xacc<<"  A= "<<asy0<<"  "<<asy1<<"  daa = "<<daa<<endl;
	cout << "crsec  "<<crsec<<"  tlen  "<<tlen<<" tdens " << tdens << endl;
	cout << "rate "<<rate<<"  "<<ratesum<<"  cnt = "<<xnorm<<" current " << current << " xacc " << xacc << endl;
	//cout << xacc << " " << rate << endl;
	//energy 1.2  theta 5.33
	//accept  0.007908  A= 7.80396e-07  7.57978e-07  daa = -0.0287264
	//crsec  295.972
	//rate 8.88209e+08  1.0224e+11  cnt = 0.366795
      }
    }

    float R_N = 3.594;
    //float sys = R_N * 0.015;
    //float sys = 0.015;
    float sys = 0.0125;
    //float sys = 0.0;
    float detec = sqrt( 1.06 );
    //float detec = 1.0;
    float pol    = 0.85;
    //float polerr = 0.01;
    float polerr = 0.0;//taken into account in sys

    if (ratesum > 0) {
      asyavg = asysum / ratesum;  // Accounts for polarization "pol"
      
      daa = daasum / ratesum;
      thetasum /= ratesum;
      q2sum = 4. * sin( thetasum * 3.141592654 / 180. / 2 ) * sin(thetasum * 3.141592654 / 180. / 2 ) * ene * ene;
      //rate = ratesum / xnorm;
      rate = ratesum;

      //qsqavg = qsqsum / ratesum;
      fom = 1e9 * rate * (asyavg*asyavg) * (daa*daa);
      // For 2 HRS and 30 days (PREX), 35 days (CREX)
      //float xcnt = 2.0 * rate * 30. * 24. * 3600;
      float xcnt = 2.0 * rate * 35. * 24. * 3600;
      float asy_err = 0;
      if (xcnt != 0) asy_err = 1.0 / sqrt(xcnt) * detec;
      newdaa = asy_err / (pol * asyavg);   // stat. error.
      drr = 1;
      if (daa != 0) drr = 0.01 * newdaa / daa;
      if (drr < 0) drr = -1.0*drr;
      blowup = 1;
      if (newdaa != 0) blowup = (sqrt(newdaa*newdaa))/newdaa;
      if (newdaa != 0) blowup2= (sqrt(polerr*polerr + newdaa*newdaa + sys*sys))/newdaa;
      //if (newdaa != 0) blowup = (sqrt(polerr*polerr + newdaa*newdaa))/newdaa;
      //drrtot = drr * blowup * R_N;//R_N for Ca
      drrtot = drr * blowup * 100.;//R_N for Ca
      drrtot2= drr * blowup2* 100.;//R_N for Ca
    } else {
      asyavg=0; daa=0; rate=0; fom=0; drr=1;
    }
    /*
    if (ratesum > 0) {        
      asyavg = asysum / ratesum;
      daa = daasum / ratesum;
      rate = ratesum / xnorm;
      fom = 1e9 * rate * (asyavg*asyavg) * (daa*daa);
    } else {
      asyavg=0; daa=0; rate=0; fom=0;
    }
    */

    cout << "E= "<<ene<<"   <A> = "<<1e6*asyavg<<" ppm";
    cout << "  rate = "<<rate<<" Hz     daa = "<<daa<<"   fom = "<<fom<< " newdaa " << newdaa << " drrtot " << drrtot << " thetasum " << thetasum << " q2sum " << q2sum << endl;
    OUTFILE << " " << ene << " " << 1e6*asyavg << " " << rate << " " << daa << " " << fom << " " << newdaa << " " << drrtot << " " << drrtot2 << endl;
    
    
  }

  OUTFILE.close();

  return 0;
}
