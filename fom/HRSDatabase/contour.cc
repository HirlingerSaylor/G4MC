#include <iostream>
#include "HRSDatabase.hh"
#include "Rtypes.h"
#include "TCanvas.h"
#include "TH2.h"
#include "TMath.h"
#include "TGraph2D.h"
#include "TF1.h"
#include "TGraph.h"
using namespace std;

Int_t main(int argc, char* argv[]){

  if( argc != 2 ){
    cout << "Incorrect number of arguments." << endl;
    cout << "Usage: ./contour [0 <= model <= 1]" << endl;
    exit (EXIT_FAILURE);
  }
  Int_t hrsmodel = ((TString)argv[1]).Atoi();
  cout << "Using model " << hrsmodel << endl;

  if( hrsmodel < 0 || hrsmodel > 1 ){
    cout << "Invalid model." << endl;
    exit (EXIT_FAILURE);
  }

  
  //Int_t hrsmodel = 0;//0 is PREX, 1 is CREX
  HRSDatabase* mydatabase = new HRSDatabase(hrsmodel);

  TCanvas* can = new TCanvas("can", "can", 100, 100, 2100, 1300);
  can->cd();

  Float_t energy_min = 600.;
  Float_t energy_max;
  if( hrsmodel == 0 ){
    energy_max = 1200.;
  }else{
    energy_max = 3000.;
  }
  //Float_t angle_min  = 3.000;
  //Float_t angle_max  =14.000;
  Float_t angle_min;
  Float_t angle_max;
  
  if( hrsmodel == 0 ){
    angle_min = 4.000;
    angle_max = 6.000;
  }else{
    //angle_min = 3.000;
    //angle_max = 5.000;
    angle_min =  1.000;
    angle_max = 15.000;
  }
  const Int_t steps = 50;
  Float_t energies[steps * steps];
  Float_t angles  [steps * steps];
  Float_t anglesr [steps * steps];
  Float_t asymms  [steps * steps];
  Float_t asymms1 [steps * steps];
  Float_t asymmsd [steps * steps];
  Float_t crosses [steps * steps];
  Float_t fom     [steps * steps];

  for(Int_t i = 0; i < steps; i++){
    for(Int_t j = 0; j < steps; j++){
      float energy = energy_min + ( energy_max - energy_min ) / steps * i;
      float angle  = angle_min  + ( angle_max  - angle_min  ) / steps * j;
      float cross  = mydatabase->Interpolate(energy, angle, 0, 0);
      float asymm  = mydatabase->Interpolate(energy, angle, 0, 1);
      float asymm1 = mydatabase->Interpolate(energy, angle, 1, 1);
      energies[ i * steps + j ] = energy;
      angles  [ i * steps + j ] = angle;
      anglesr [ i * steps + j ] = -angle;
      asymms  [ i * steps + j ] = asymm * 1000000.;
      asymms1 [ i * steps + j ] = asymm1* 1000000.;
      asymmsd [ i * steps + j ] = ( asymm - asymm1 ) / asymm;
      crosses [ i * steps + j ] = cross;
      fom     [ i * steps + j ] = asymmsd [ i * steps + j ] * asymmsd [ i * steps + j ] 
	* crosses [ i * steps + j  ]* asymms  [ i * steps + j ] * asymms  [ i * steps + j ];
      cout << energy << " " << angle << " " << cross << " " << asymm << endl;
      //indices:
      //0. Pb Horowitz
      //1. Pb Horowitz, stretched by 1%
      //which is whether you want:
      //0. Cross section
      //1. Asymmetry
    }
  }

  //TString draw = "TRI1";
  TString draw = "COLZ";

  can->Divide(2, 2);
  can->cd(1);
  TGraph2D *g1 = new TGraph2D(steps * steps, energies, angles, crosses);
  g1->SetName("Cross Section (E (MeV), #theta (degrees)) in mb/sr");
  g1->SetTitle("Cross Section (E (MeV), #theta (degrees)) in mb/sr");
  g1->GetXaxis()->SetTitle("E (MeV)");
  g1->GetYaxis()->SetTitle("#theta (degrees)");
  g1->GetZaxis()->SetTitle("Cross Section");
  g1->Draw(draw);
  can->cd(2);
  TGraph2D *g2 = new TGraph2D(steps * steps, energies, angles, asymms);
  g2->SetName("Asymmetry (E (MeV), #theta (degrees)) in ppm");
  g2->SetTitle("Asymmetry (E (MeV), #theta (degrees)) in ppm");
  g2->GetXaxis()->SetTitle("E (MeV)");
  g2->GetYaxis()->SetTitle("#theta (degrees)");
  g2->GetZaxis()->SetTitle("Asymmetry (ppm)");
  g2->Draw(draw);
  can->cd(3);
  TGraph2D *g3 = new TGraph2D(steps * steps, energies, angles, asymmsd);
  g3->SetName("#varepsilon (E (MeV), #theta (degrees)) : (sensitivity to neutron radius)");
  g3->SetTitle("#varepsilon (E (MeV), #theta (degrees)) : (sensitivity to neutron radius)");
  g3->GetXaxis()->SetTitle("E (MeV)");
  g3->GetYaxis()->SetTitle("#theta (degrees)");
  g3->GetZaxis()->SetTitle("#epsilon");
  g3->Draw(draw);
  can->cd(4)->SetGridx();
  can->cd(4)->SetGridy();
  can->cd(4)->SetLogz();
  TGraph2D *g4 = new TGraph2D(steps * steps, energies, angles, fom);
  g4->SetName("Figure of Merit (E (MeV), #theta (degrees)) #propto XS * A^{2} * #varepsilon^{2}");
  g4->SetTitle("Figure of Merit (E (MeV), #theta (degrees)) #propto XS * A^{2} * #varepsilon^{2}");
  g4->GetXaxis()->SetTitle("E (MeV)");
  g4->GetYaxis()->SetTitle("#theta (degrees)");
  g4->GetZaxis()->SetTitle("Figure of Merit");
  g4->Draw(draw);
  //g->Draw("p");
  
  TCanvas* can2 = new TCanvas("can2", "can2", 60, 60, 1100, 700);
  can2->cd();

  Float_t my_y[6][15];
  Float_t my_x[6][15];

  Float_t q[6];
  TF1* f1[6];
  TGraph *gr[6];
for(Int_t i = 0; i < 6; i++){
  can->cd(4);
    q[i] = 0.39 * ( i + 1 ) * .197;
    //f1[i] = new TF1(Form("f%d", i), Form("%f * %f / 4. / TMath::Power(TMath::Sin( x / 2 * TMath::Pi() / 180. ), .5)",), 0., 3.55);
    f1[i] = new TF1(Form("f%d", i), Form("TMath::RadToDeg() * 2. * TMath::ASin( TMath::Sqrt( %f * %f / 4. / TMath::Power( x / 1000., 2. ) ) )", q[i], q[i]), 0., 3550.);
    cout << f1[i]->Eval(1000) << " " << f1[i]->Eval(2000) << " " << f1[i]->Eval(3000) << " " << f1[i]->Eval(3550) << endl ;
    f1[i]->SetLineColor( 1 );
    f1[i]->Draw("SAME");
    for(Int_t j = 0; j < 15; j++){
      float my_E     = ( 600. + 200. * j );
      float my_theta = TMath::RadToDeg() * 2. * TMath::ASin( q[i] / 2. / ( my_E / 1000. ) );
      float cross  = mydatabase->Interpolate(my_E, my_theta, 0, 0);
      float asymm  = mydatabase->Interpolate(my_E, my_theta, 0, 1);
      float asymm1 = mydatabase->Interpolate(my_E, my_theta, 1, 1);
      Float_t asymms  = asymm * 1000000.;
      Float_t asymms1 = asymm1* 1000000.;
      Float_t asymmsd = ( asymm - asymm1 ) / asymm;
      Float_t crosses = cross;
      Float_t fom     = asymmsd * asymmsd * crosses * asymms * asymms;
      my_y[i][j] = fom;
      my_x[i][j] = my_E;
      cout << my_E << " " << my_theta << " " << fom << endl;
    }
    gr[i] = new TGraph(15, my_x[i], my_y[i]);
    gr[i]->SetMarkerStyle(20);
    gr[i]->SetMarkerSize(0.5);
    gr[i]->SetMarkerColor( i + 1 );
  }
 can2->cd()->SetLogy();
 gr[1]->Draw("AP");
 gr[1]->GetYaxis()->SetRangeUser(0.000001, 1.);
 gr[0]->Draw("P");
 gr[2]->Draw("P");
 gr[3]->Draw("P");
 gr[4]->Draw("P");
 gr[5]->Draw("P");



  
  
  
  
  gPad->Update();
  //can->SetLogz();
  if( hrsmodel == 0 ){
    can->SaveAs("contour_p.png");
  }else{
    can->SaveAs("contour_c.png");
  }
  can2->SaveAs("opt.png");
  return 0;
}
