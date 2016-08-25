plot_fom_short(){
  gStyle->SetOptStat(0);
  int model = 2;//1 is prex, 2 is crex, 5 is supercrex
  int mym = 0;
  int myn = 0;
  if( model == 1 ){
    mym = 1;
    myn = 13;
  }else if( model == 2 ){
    mym = 1;
    myn = 62;
  }else if( model == 5 ){
    mym = 1;
    myn = 62;
  }

  const Int_t m = mym;
  const Int_t n = myn;

  ifstream INFILE;
  
  TString filenames[10] = {"fom_prexI.dat", "fom_prexII_col0.dat", "fom_prexII_col1.dat", "fom_prexII_col2.dat", "fom_prex_4_deg_col2.dat", "", "", "", "", ""};
  if( model == 2 ){
    //filenames[0] = "fom_crex_col3.dat";
    filenames[0] = "fom_crex_col2.dat";
    //filenames[1] = "fom_crex_col1.dat";
    //filenames[2] = "fom_crex_col2.dat";
  }else if( model == 5 ){
    filenames[0] = "fom_supercrex1.dat";
    filenames[1] = "fom_supercrex2.dat";
    filenames[2] = "fom_supercrex3.dat";
  }


  

  
  float E [m][n], A [m][n], rate [m][n], daa [m][n], fom [m][n], newdaa [m][n], drtot [m][n], drtot2[m][n];

  for(Int_t i = 0; i < m; i++ ){
    INFILE.open(filenames[i].Data());
    cout << "Opened " << filenames[i] << endl;
    cout   << E << " " << A << " " << rate << " " << daa << " " << fom << " " << newdaa << " " << drtot << " " << drtot2 << endl;;
    for( Int_t j = 0; j < n; j++ ){
      INFILE >> E[i][j] >> A[i][j] >> rate[i][j] >> daa[i][j] >> fom[i][j] >> newdaa[i][j] >> drtot[i][j] >> drtot2[i][j];
      cout   << E[i][j] << " " << A[i][j] << " " << rate[i][j] << " " << daa[i][j] << " " << fom[i][j] << " " << newdaa[i][j] << " " << drtot[i][j] << " " << drtot2[i][j] << endl;
      rate[i][j] /= 1000000.;
    }
    INFILE.close();
  }

  TCanvas* can = new TCanvas("can", "can", 20, 20, 900, 900);
  can->Divide(2, 2);
  
  TString y_axes[4]  = {"Average Asymmetry", "1 HRS Rate (MHz)", "dA/A", "Error in Neutron Radius (%)"};
  TString titles[4]  = {"Average Asymmetry", "1 HRS Rate (MHz)", "dA/A", "Error in Neutron Radius (%)"};
  Float_t y_axis_ranges[4]  = {1.5, 15000, 500., 5};
  TH1F* hist[4];
  for(Int_t i = 0; i < m; i++){
    for(Int_t j = 0; j < 4; j++){
      can->cd( j + 1 )->SetGridx();
      can->cd( j + 1 )->SetGridy();
      if( j == 1 )
	can->cd( j + 1 )->SetLogy();
      TGraph* gr;
      if     ( j == 0 ){ gr = new TGraph(n, E[i], A     [i]); }
      else if( j == 1 ){ gr = new TGraph(n, E[i], rate  [i]); }
      //else if( j == 2 ){ gr = new TGraph(n, E[i], fom   [i]); }
      else if( j == 2 ){ gr = new TGraph(n, E[i], daa   [i]); }
      else if( j == 3 ){ gr = new TGraph(n, E[i], drtot [i] );
	                 gr2= new TGraph(n, E[i], drtot2[i] ); }
      
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
	//hist[j] = new TH1F(titles[j], titles[j], 1, 0.0, 2.5);
	//hist[j]->GetYaxis()->SetRangeUser(0.0, y_axis_ranges[j]);
	//hist[j]->Draw();
	gr->Draw("AP");
	if( j == 3 ){
	  gr2->SetMarkerStyle(20);
	  gr2->SetMarkerSize(1.);
	  gr2->Draw("P");
	}
      }else{
	if( i == 4 )
	  gr->Draw("P");
      }
      
      gr->GetHistogram()->GetXaxis()->SetTitle("Energy (GeV)");
      gr->GetHistogram()->GetXaxis()->SetRangeUser(1.5, 3.0);
      //gr->GetHistogram()->GetXaxis()->SetRangeUser(1.2, 2.7);
      gr->GetHistogram()->GetYaxis()->SetTitle(y_axes[j]);
      if( j == 0 ){
	gr->GetHistogram()->GetYaxis()->SetRangeUser(0., 3.0);
      }else if( j == 1 ){
	gr->GetHistogram()->GetYaxis()->SetRangeUser(0., 1000.);
      }else if( j == 2 ){
	gr->GetHistogram()->GetYaxis()->SetRangeUser(0., .1);
      }else if( j == 3 ){
	gr->GetHistogram()->GetYaxis()->SetRangeUser(0., 1.5);
      }else{
	cout << "Something is wrong" << endl;
      }      
      gr->GetHistogram()->GetYaxis()->SetTitleOffset(1.6);
      //if( model == 1 ){
	//gr->GetHistogram()->GetXaxis()->SetRangeUser(0., 2.5);
	//gr->GetHistogram()->GetYaxis()->SetRangeUser(0., y_axis_ranges[j]);
      //}else{
	//gr->GetHistogram()->GetXaxis()->SetRangeUser(0., 4.0);
	//if( i == 0 && j == 5 )
	  //gr->GetHistogram()->GetYaxis()->SetRangeUser(0., 0.05);
      //}
      if( i == 4 ) 
	gr->Draw("P");

    }
  }


  
  //can->SaveAs("fom_I.png");
  //can->SaveAs("fom_II.png");
  //can->SaveAs("fom_c.png");
  /*
  if( model == 1 ){
    can->SaveAs("fom_p_short.png");
  }else if ( model == 2 ) {
    can->SaveAs("fom_c_short.png");
  }else if ( model == 5 ) {
    can->SaveAs("fom_supercrex_short.png");
  }
  */

  
}
