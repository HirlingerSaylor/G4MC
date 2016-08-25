plot_fom(){
  gStyle->SetOptStat(0);
  int model = 1;//1 is prex, 2 is crex, 5 is supercrex
  int mym = 0;
  int myn = 0;
  if( model == 1 ){
    mym = 5;
    myn = 13;
  }else if( model == 2 ){
    mym = 3;
    myn = 62;
  }else if( model == 5 ){
    mym = 3;
    myn = 62;
  }

  const Int_t m = mym;
  const Int_t n = myn;

  ifstream INFILE;
  
  TString filenames[10] = {"fom_prexI.dat", "fom_prexII_col0.dat", "fom_prexII_col1.dat", "fom_prexII_col2.dat", "fom_prex_4_deg_col2.dat", "", "", "", "", ""};
  if( model == 2 ){
    filenames[0] = "fom_crex_col0.dat";
    filenames[1] = "fom_crex_col1.dat";
    filenames[2] = "fom_crex_col2.dat";
  }else if( model == 5 ){
    filenames[0] = "fom_supercrex1.dat";
    filenames[1] = "fom_supercrex2.dat";
    filenames[2] = "fom_supercrex3.dat";
  }


  

  
  float E [m][n], A [m][n], rate [m][n], daa [m][n], fom [m][n], newdaa [m][n], drtot [m][n];

  for(Int_t i = 0; i < m; i++ ){
    INFILE.open(filenames[i].Data());
    cout << "Opened " << filenames[i] << endl;
    for( Int_t j = 0; j < n; j++ ){
      INFILE >> E[i][j] >> A[i][j] >> rate[i][j] >> daa[i][j] >> fom[i][j] >> newdaa[i][j] >> drtot[i][j];
      cout   << E[i][j] << " " << A[i][j] << " " << rate[i][j] << " " << daa[i][j] << " " << fom[i][j] << " " << newdaa[i][j] << " " << drtot[i][j] << endl;;
      rate[i][j] /= 1000000.;
    }
    INFILE.close();
  }

  TCanvas* can = new TCanvas("can", "can", 20, 20, 2100, 1100);
  can->Divide(3, 2);
  
  TString y_axes[6]  = {"Asymmetry", "Sensitivity to Neutron Radius", "Rate (MHz)", "Figure of Merit", "newdaa", "Error in Neutron Radius"};
  TString titles[6]  = {"Asymmetry", "Sensitivity to Neutron Radius", "Rate (MHz)", "Figure of Merit", "newdaa", "Error in Neutron Radius"};
  Float_t y_axis_ranges[6]  = {1.5, 0.03, 15000, 500., 0.05, 0.08};
  TH1F* hist[6];
  for(Int_t i = 0; i < m; i++){
    for(Int_t j = 0; j < 6; j++){
      can->cd( j + 1 )->SetGridx();
      can->cd( j + 1 )->SetGridy();
      TGraph* gr;
      if     ( j == 0 ){ gr = new TGraph(n, E[i], A     [i]); }
      else if( j == 1 ){ gr = new TGraph(n, E[i], daa   [i]); }
      else if( j == 2 ){ gr = new TGraph(n, E[i], rate  [i]); }
      else if( j == 3 ){ gr = new TGraph(n, E[i], fom   [i]); }
      else if( j == 4 ){ gr = new TGraph(n, E[i], newdaa[i]); }
      else if( j == 5 ){ gr = new TGraph(n, E[i], drtot [i]); }
      
      gr->SetMarkerStyle(20);
      gr->SetMarkerSize(1.);
      if( model == 1 || model == 5 ){
	gr->SetMarkerColor(i + 1);
      }else{
	gr->SetMarkerColor(i + 2);
      }
      if( i > 3 )
	gr->SetMarkerColor(i + 2);
      gr->SetTitle(titles[j]);
      if( i == 0 ){
	hist[j] = new TH1F(titles[j], titles[j], 1, 0.0, 2.5);
	hist[j]->GetYaxis()->SetRangeUser(0.0, y_axis_ranges[j]);
	hist[j]->Draw();
	gr->Draw("P");
      }else{
	if( i == 4 )
	  gr->Draw("P");
      }
      
      gr->GetHistogram()->GetXaxis()->SetTitle("Energy (GeV)");
      gr->GetHistogram()->GetYaxis()->SetTitle(y_axes[j]);
            
      if( model == 1 ){
	gr->GetHistogram()->GetXaxis()->SetRangeUser(0., 2.5);
	gr->GetHistogram()->GetYaxis()->SetRangeUser(0., y_axis_ranges[j]);
      }else{
	gr->GetHistogram()->GetXaxis()->SetRangeUser(0., 4.0);
	if( i == 0 && j == 5 )
	  gr->GetHistogram()->GetYaxis()->SetRangeUser(0., 0.05);
      }
      if( i == 4 ) 
	gr->Draw("P");

    }
  }


  
  //can->SaveAs("fom_I.png");
  //can->SaveAs("fom_II.png");
  //can->SaveAs("fom_c.png");
  if( model == 1 ){
    can->SaveAs("fom_p.png");
  }else if ( model == 2 ) {
    can->SaveAs("fom_c.png");
  }else if ( model == 5 ) {
    can->SaveAs("fom_supercrex.png");
  }


  
}
