
mistune(){
  TString filenames[2] = {"nickie_accept_prex_I.dat",
			  "nickie_accept_prex_II_col0.dat"};
  
  const Int_t nlines = 250;

  Float_t angle[2][nlines];
  Float_t acc  [2][nlines];

  TGraph* gr[2];

  TString draw[2] = {"AP", "P"};

  TCanvas* can = new TCanvas("can", "can", 20, 20, 1100, 700);
  can->cd();
  
  ifstream INFILE;
  for(Int_t i = 0; i < 2; i++){
    INFILE.open(filenames[i].Data());
    for(Int_t j = 0; j < nlines; j++){
      INFILE >> angle[i][j] >> acc[i][j];
    }
    INFILE.close();
    gr[i] = new TGraph(nlines, angle[i], acc[i]);
    gr[i]->SetMarkerStyle(20);
    gr[i]->SetMarkerColor(i + 1);
    gr[i]->Draw(draw[i]);
  }
  
}
