compare_acceptance(){
  for(Int_t i = 1; i < 3; i++){
    plot(i);
  }
}

plot(int p_model){

  Int_t model = p_model;//0 is prex, 1 is prex II, 2 is crex

  ifstream INFILE;
  if( model == 0 ){
    INFILE.open("nickie_accept_prex_I.dat");
  }else if( model == 1 ){
    INFILE.open("nickie_accept_prex_II_col2.dat");
  }else if( model == 2 ){
    INFILE.open("nickie_accept_crex_col2.dat");
  }else{
    cout << "Something is very wrong." << endl;
  }
  //ifstream INFILE("nickie_accept_prex_I.dat");
  
  //ifstream INFILE("nickie_accept_crex_col0.dat");
  
  const Int_t n_nickie = 250;
  Float_t angle_nickie[n_nickie];
  Float_t acc_nickie[n_nickie];

  Int_t n_bob_mod;
  if( model == 1 ){
    n_bob_mod = 291;//prex
  }else if( model == 2){
  //const Int_t n_bob = 175;
    n_bob_mod = 600;//crex
  }
  const Int_t n_bob = n_bob_mod;

  Float_t angle_bob[n_bob];
  Float_t acc_bob[n_bob];

  for(Int_t i = 0; i < n_nickie; i++){
    INFILE >> angle_nickie[i] >> acc_nickie[i];
    //acc_nickie[i] *= 80. / 360. * 2.;
    //acc_nickie[i] *= 80. / 360.;// * 62000.;
    //acc_nickie[i] *= 80. / 360. / 4.;
    acc_nickie[i] *= TMath::Sin( angle_nickie[i] * TMath::DegToRad() );
  }
  
  INFILE.close();
  //INFILE.open("accept.dat");
  //INFILE.open("crex_accept.dat");//incorrectly done
  INFILE.open("crex_hamc_mod.dat");

  for(Int_t i = 0; i < n_bob; i++){
    INFILE >> angle_bob[i] >> acc_bob[i];
    //acc_bob[i] *= 14.;
  }

  INFILE.close();

  TGraph* gr_nickie = new TGraph(n_nickie, angle_nickie, acc_nickie);
  TGraph* gr_bob    = new TGraph(n_bob   , angle_bob   , acc_bob   );
  
  TCanvas* can = new TCanvas("can", "can", 20, 20, 1100, 700);
  can->cd();

  gr_nickie->SetMarkerColor(1);
  gr_nickie->SetMarkerStyle(20);
  gr_nickie->SetMarkerSize(0.5);

  gr_bob   ->SetMarkerStyle(20);
  gr_bob   ->SetMarkerSize(0.5);

  //gr_bob   ->Draw("AP");
  gr_nickie->Draw("AP");
  if( model == 1 ){
    gr_nickie->GetXaxis()->SetRangeUser(2., 8.);
    gr_nickie->SetTitle("PREX Acceptance, 5 degrees configuration");
  }else if( model == 2 ){
    gr_nickie->GetXaxis()->SetRangeUser(2., 8.);
    gr_nickie->SetTitle("CREX Acceptance, 4 degrees configuration");
  }
  gr_nickie->GetXaxis()->SetTitle("#theta (degrees)");
  gr_nickie->GetYaxis()->SetTitle("Acceptance");
  gr_bob   ->Draw("P");
  if( model == 1 ){
    can->SaveAs("prex_accept.png");
  }else if( model == 2 ){
    can->SaveAs("crex_accept.png");
  }
}
