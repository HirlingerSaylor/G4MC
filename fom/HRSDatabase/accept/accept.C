accept(){
  Bool_t plot = kFALSE;
  //Int_t new_col = 0;
  Int_t new_col = 2;//0 is old, 1 is new with low angle, 2 is new but no low angle, which is what we want to use
  //3 and 4 are like 2, except that you are losing 2 mm top and bottom, and 8.5 mm top and bottom respectively
  Int_t model = 3;//1 is PREX I, 2 is PREX II, 3 is CREX, 4 is PREX at 4 degrees
  //gStyle->SetOptStat(000001111);
  gStyle->SetOptStat(0);
  TFile* infile;

  if( model == 1 ){
    //infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/prex_settings_field/prex_I_compare.root", "READ");
    //infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/prex_settings_juliette/mistune.root", "READ");
    //infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/prex_settings_juliette/mistune2.root", "READ");
    infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/prex_settings_juliette/mistune1.root", "READ");//mistune1 is ideal/not mistuned
    if( new_col ){
      return -1;
    }
  } else if( model == 2 ){
    //if( new_col ) {
    infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/prex_settings_juliette/mistune1.root", "READ");
    //infile = new TFile("/home/Nickie/JLab/HallA/G4MC/CREX_Project/prex_settings_field/prex_II_no_col.root", "READ");      
    //}else{
    //infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/prex_settings_field/prex_II_compare.root", "READ");
    //}
  }else if ( model == 3 ){
    //if( new_col ){
      //infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/crex_settings/crex_no_col.root", "READ");
      infile = new TFile("~/BackupDrive/JLab/G4MCrootfiles/supercrex/realcrex.root", "READ");
      //infile = new TFile("/home/Nickie/JLab/HallA/G4MC/CREX_Project/crex_5_degrees/crex_5_degrees/crex_5_degrees3.root", "READ");
      //}else{
      //infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/crex_settings/crex_field_sos.root", "READ");
      //}
  }else if ( model == 4 ){
    if( new_col ){
      infile = new TFile("~/BackupDrive/JLab/G4MCrootfiles/prex_II_4_degrees.root", "READ");
    }else{
      return -1;
    }
  }else if ( model == 5 ){
      infile = new TFile(Form("~/BackupDrive/JLab/G4MCrootfiles/supercrex/supercrex%d.root", new_col + 1), "READ");
  }else{
    return -1;
  }
//TFile* infile = new TFile("~/JLab/HallA/G4MC/CREX_Project/crex_settings/crex_no_col.root", "READ");
  infile->cd();

  TString col_cut = "";
  TString col_pre = "";
  if( model == 5 ){
    col_cut = "TMath::Abs(X_col_tr) < 0.09 && Y_col_tr < 0.04 && X_col_tr > ( 1.88 * Y_col_tr - 0.1474 ) && X_col_tr < ( - 1.88 * Y_col_tr + 0.1474 ) && TMath::Power( Y_col_tr - 0.145, 2) + TMath::Power( X_col_tr, 2) < 0.1975 * 0.1975 && TMath::Power( Y_col_tr - 0.229, 2) + TMath::Power( X_col_tr, 2) > 0.2 * 0.2";
  }else if( new_col == 0 ){
    col_cut = " TMath::Abs(X_col_tr) < 0.117 && Y_col_tr < 0.04 && X_col_tr > ( 1.88 * Y_col_tr - 0.1474 ) && X_col_tr < ( - 1.88 * Y_col_tr + 0.1474 ) && TMath::Power( Y_col_tr - 0.145, 2) + TMath::Power( X_col_tr, 2) < 0.1975 * 0.1975 && TMath::Power( Y_col_tr - 0.229, 2) + TMath::Power( X_col_tr, 2) > 0.2 * 0.2";
  }else if( new_col == 1 ){
    col_cut = " TMath::Abs(X_col_tr) < 0.09 && Y_col_tr < 0.04 && X_col_tr > ( 1.88 * Y_col_tr - 0.1474 ) && X_col_tr < ( - 1.88 * Y_col_tr + 0.1474 ) && TMath::Power( Y_col_tr - 0.145, 2) + TMath::Power( X_col_tr, 2) < 0.1975 * 0.1975 ";
  }else if(new_col == 2){
    col_cut = " TMath::Abs(X_col_tr) < 0.09 && Y_col_tr < 0.04 && X_col_tr > ( 1.88 * Y_col_tr - 0.1474 ) && X_col_tr < ( - 1.88 * Y_col_tr + 0.1474 ) && TMath::Power( Y_col_tr - 0.145, 2) + TMath::Power( X_col_tr, 2) < 0.1975 * 0.1975 && TMath::Power( Y_col_tr - 0.229, 2) + TMath::Power( X_col_tr, 2) > 0.2 * 0.2";
    //col_cut = " TMath::Abs(X_q1en_tr) < 0.09 && Y_q1en_tr < 0.04 && X_q1en_tr > ( 1.88 * Y_q1en_tr - 0.1474 ) && X_q1en_tr < ( - 1.88 * Y_q1en_tr + 0.1474 ) && TMath::Power( Y_q1en_tr - 0.145, 2) + TMath::Power( X_q1en_tr, 2) < 0.1975 * 0.1975 && TMath::Power( Y_q1en_tr - 0.229, 2) + TMath::Power( X_q1en_tr, 2) > 0.2 * 0.2";
  }else if(new_col == 3){
    col_cut = " TMath::Abs(X_col_tr) < 0.088 && Y_col_tr < 0.04 && X_col_tr > ( 1.88 * Y_col_tr - 0.1474 ) && X_col_tr < ( - 1.88 * Y_col_tr + 0.1474 ) && TMath::Power( Y_col_tr - 0.145, 2) + TMath::Power( X_col_tr, 2) < 0.1975 * 0.1975 && TMath::Power( Y_col_tr - 0.229, 2) + TMath::Power( X_col_tr, 2) > 0.2 * 0.2";
  }else if(new_col == 4){
    col_cut = " TMath::Abs(X_col_tr) < 0.0815 && Y_col_tr < 0.04 && X_col_tr > ( 1.88 * Y_col_tr - 0.1474 ) && X_col_tr < ( - 1.88 * Y_col_tr + 0.1474 ) && TMath::Power( Y_col_tr - 0.145, 2) + TMath::Power( X_col_tr, 2) < 0.1975 * 0.1975 && TMath::Power( Y_col_tr - 0.229, 2) + TMath::Power( X_col_tr, 2) > 0.2 * 0.2";
  }else{
    //col_pre = "col_";
  }
//This cut satisfies the new collimator design.

  const Int_t n_bins = 250;

  TH1F* h1 = new TH1F("h1", "Acceptance", n_bins, 0., 15.);
  h1->GetXaxis()->SetTitle("#theta (degrees)");
  h1->GetYaxis()->SetTitle("Acceptance");
  TH1F* h2 = new TH1F("h2", "h2", n_bins, 0., 15.);
  h2->GetXaxis()->SetTitle("#theta (degrees)");
  h2->GetYaxis()->SetTitle("Acceptance");

  TH1F* h3 = new TH1F("h3", "Acceptance", n_bins, 0., 15.);
  h3->GetXaxis()->SetTitle("#theta (degrees)");
  h3->GetYaxis()->SetTitle("Acceptance");
  TH1F* h4 = new TH1F("h4", "h4", n_bins, 0., 15.);
  h4->GetXaxis()->SetTitle("#theta (degrees)");
  h4->GetYaxis()->SetTitle("Acceptance");

  TCanvas* can3 = new TCanvas("can3", "can3", 20, 750, 1100, 700);
  can3->cd();
  
  track0->Draw("X_col_tr:Y_col_tr>>colhist(200, -0.2, 0.2, 200, -0.2, 0.2)", "X_col_tr != -150 &&" + col_cut, "COLZ");
  //track0->Draw("X_col_tr:Y_col_tr>>colhist(200, -0.2, 0.2, 200, -0.2, 0.2)", "X_col_tr != -150", "COLZ");
  cout << colhist->GetEntries() << endl;
  
  TCanvas* can1 = new TCanvas("can1", "can1", 20, 20, 1100, 700);
  can1->cd();
  
  TString det_cut;
  //if( model == 1 || model == 2 ){
  //det_cut = "( X_qz2_tr != -150 && TMath::Abs(Y_qz2_tr) < ( 0.035 * 0.5 ) && TMath::Abs(X_qz2_tr + 0.045) < ( 0.14 * 0.5 / TMath::Sqrt(2.)) )";
  //}else if( model == 3 ){
  //det_cut = "( X_qz2_tr != -150 && TMath::Abs(Y_qz2_tr + 0.01) < ( 0.035 * 0.5 ) && TMath::Abs(X_qz2_tr + 0.06) < ( 0.14 * 0.5 / TMath::Sqrt(2.)) )";
  //det_cut = "( X_qz2_tr != -150 && TMath::Abs(Y_qz2_tr) < ( 0.035 * 0.5 ) && TMath::Abs(X_qz2_tr + 0.06) < ( 0.14 * 0.5 / TMath::Sqrt(2.)) )";
  if( model == 3 )
    det_cut = "TMath::Abs( 2.2 - P_qz2_tr ) < 0.0035";
  if( model == 2 || model == 1 )
    det_cut = "TMath::Abs( 1.063 - P_qz2_tr ) < 0.0035";
  //}
  if( model == 5 )
    det_cut = "( X_qz2_tr != -150 && TMath::Abs(Y_qz2_tr) < ( 0.1 ) && TMath::Abs(X_qz2_tr) < ( 0.1 / TMath::Sqrt(2.)) ) && ";

  //det_cut = "TMath::Abs(P_qz2_tr - 2.2) < 0.0035";
  //det_cut = "";
  //det_cut += col_cut;



  //if( model == 5 )
  //det_cut = col_cut;

  //track0->Draw("X_qz2_tr:Y_qz2_tr>>ahist", det_cut, "COLZ");
  track0->Draw("Theta0_tr:Phi0_tr>>ahist(200, -.1, .1, 200, -.1, .1)", col_cut + "&& X_qz2_tr != -150 &&" + det_cut, "COLZ");
  ahist->GetXaxis()->SetTitle("#phi_{tr}");
  ahist->GetYaxis()->SetTitle("#theta_{tr}");
  //ahist->GetEvents();

  TCanvas* can2 = new TCanvas("can2", "can2", 1200, 20, 1100, 700);
  can2->cd();

  
  //TString det_cut = "( X_vdc_tr != -150 )";
  //TString det_cut = "( X_vdc_tr != -150 ) / TMath::Sin( Theta0 )";
  track0->Draw("Theta0 * TMath::RadToDeg() >> h1", "", "");
  track0->Draw("Theta0 * TMath::RadToDeg() >> h2", det_cut + "&&" + col_cut + "&& X_qz2_tr != -150", "");

  cout << h2->GetEntries() << endl;

  h2->Divide(h1);//must look at ratio to get acceptance.
  //h1->Draw();
  //h2->Draw();

  track0->Draw("Theta0 * TMath::RadToDeg() >> h3", "", "");
  track0->Draw("Theta0 * TMath::RadToDeg() >> h4", col_cut + "&& X_qz2_tr != -150" , "");

  h4->Divide(h3);

  h4->SetLineColor(1);
  h2->SetLineColor(2);

  h4->Draw();
  h2->Draw("SAME");

  ofstream OUTFILE;
  if( model == 1 && new_col == 0){
    OUTFILE.open(col_pre + "nickie_accept_prex_I.dat");
  }else if ( model == 2 && new_col == 0){
    OUTFILE.open(col_pre + "nickie_accept_prex_II_col0.dat");
  }else if ( model == 2 && new_col == 1){
    OUTFILE.open(col_pre + "nickie_accept_prex_II_col1.dat");
  }else if ( model == 2 && new_col == 2){
    OUTFILE.open(col_pre + "nickie_accept_prex_II_col2.dat");
  }else if ( model == 2 && new_col == 3){
    OUTFILE.open(col_pre + "nickie_accept_prex_II_col3.dat");
  }else if ( model == 2 && new_col == 4){
    OUTFILE.open(col_pre + "nickie_accept_prex_II_col4.dat");
  }else if ( model == 3 && new_col == 0){
    OUTFILE.open(col_pre + "nickie_accept_crex_col0.dat");
  }else if ( model == 3 && new_col == 1){
    OUTFILE.open(col_pre + "nickie_accept_crex_col1.dat");
  }else if ( model == 3 && new_col == 2){
    OUTFILE.open(col_pre + "nickie_accept_crex_col2.dat");
  }else if ( model == 3 && new_col == 3){
    OUTFILE.open(col_pre + "nickie_accept_crex_col3.dat");
  }else if ( model == 3 && new_col == 4){
    OUTFILE.open(col_pre + "nickie_accept_crex_col4.dat");
  }else if ( model == 4 && new_col == 1){
    OUTFILE.open(col_pre + "nickie_accept_prex_4_deg_col1.dat");
  }else if ( model == 4 && new_col == 2){
    OUTFILE.open(col_pre + "nickie_accept_prex_4_deg_col2.dat");
  }else if ( model == 5){
    OUTFILE.open(Form("nickie_accept_supercrex%d.dat", new_col + 1));
  }else{
    cout << "Something is very wrong!" << endl;
  }
  
  //OUTFILE.open("nickie_accept_crex_no_col.dat");
  //OUTFILE.open("test.dat");
  
  Float_t acceptsum = 0.;
  
  for(Int_t i = 0; i < n_bins; i++){
    Float_t mytheta = 15. / n_bins * ( i + 0.5 );
    Float_t myaccept= h2->GetBinContent( i + 1 );
    if( myaccept == 1 )
      myaccept = 0.;
    OUTFILE << mytheta << " " << myaccept << endl;
    acceptsum += myaccept;
    //cout << mytheta << " " << myaccept << " " << acceptsum << endl;
  }
  OUTFILE.close();
  
  if( plot ){
    const Int_t n   = 291;
    const Int_t n_n = n_bins;
    Float_t theta   [n];
    Float_t accept  [n];
    Float_t n_theta [n_n];
    Float_t n_accept_plot [n_n];
    Float_t n_accept[n_n];
    
    ifstream INFILE;
    INFILE.open("accept.dat");
    for( Int_t i = 0; i < n; i++ ){
      INFILE >> theta[i] >> accept[i];
    }
    INFILE.close();
    INFILE.open("nickie_accept2.dat");
    for( Int_t i = 0; i < n_n; i++ ){
      n_accept[i] /= acceptsum;
      //n_accept[i] /= 25.846829287;
      n_accept[i] *= 0.937077;
      INFILE >> n_theta[i] >> n_accept[i];
      //cout << n_theta[i] << " " << n_accept[i] << endl;
      n_accept_plot[i] = n_accept[i] / 8.;
    }
    
    TH1F* hist = new TH1F("acceptance", "acceptance", 1, 0, 15);
    hist->GetYaxis()->SetRangeUser(0., 0.01);
    
    TGraph* gr   = new TGraph(n  ,   theta,   accept);
    TGraph* n_gr = new TGraph(n_n, n_theta, n_accept_plot);
    
    hist->Draw();
    gr->SetMarkerStyle(20);
    gr->SetMarkerSize(0.4);
    gr  ->Draw("P");
    n_gr->SetMarkerStyle(20);
    n_gr->SetMarkerSize(0.4);
    n_gr->SetMarkerColor(2);
    n_gr->Draw("P");
  }
}
