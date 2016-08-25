void SetStyle(TGraph* gr, Int_t color){
  gr->SetMarkerStyle(20);
  gr->SetMarkerSize(0.5);
  gr->SetMarkerColor(color);
}

shim(){
  
  const Int_t nfiles = 4;
  //const Int_t nfiles = 3;
  ifstream INFILE;
  
  /*TString infiles[nfiles] = {"fom_crex_col0.dat",
			     "fom_crex_col2.dat",
			     "fom_crex_col3.dat",
			     "fom_crex_col4.dat"};
  */
  TString infiles[nfiles] = {"fom_prexII_col0.dat",
			     "fom_prexII_col2.dat",
			     "fom_prexII_col3.dat",
			     "fom_prexII_col4.dat"};
  

  const Int_t nlines = 62;
  Float_t rate[nfiles][nlines];
  Float_t energy[nfiles][nlines];
  
  TString data, rate_str, energy_str;

  TGraph* gr[nfiles];
  
  for(Int_t i = 0; i < nfiles; i++){
    INFILE.open(infiles[i]);
    for(Int_t j = 0; j < nlines; j++){
      INFILE >> energy_str >> data >> rate_str >> data >> data >> data >> data >> data;
      rate  [i][j] = rate_str  .Atof();
      energy[i][j] = energy_str.Atof();
      cout << energy[i][j] << " " << rate[i][j] << endl;
    }
    INFILE.close();
    gr[i] = new TGraph(nlines, energy[i], rate[i]);
  }
  
  TCanvas* can = new TCanvas("can", "can", 20, 20, 1100, 700);
  can->SetGridx();
  can->SetGridy();

  can->cd();
  SetStyle(gr[0], 1);
  gr[0]->Draw("AP");
  SetStyle(gr[1], 2);
  gr[1]->Draw("P");
  SetStyle(gr[2], 3);
  gr[2]->Draw("P");
  SetStyle(gr[3], 4);
  gr[3]->Draw("P");

  gr[0]->SetTitle("Rate as a function of acceptance narrowing at collimator, FOR CREX EXPERIMENT.");
  gr[0]->GetXaxis()->SetTitle("Energy (GeV)");
  gr[0]->GetYaxis()->SetTitle("Rate (Hz)");

  TPaveText *pt1 = new TPaveText(.5,.8,.85,.9, "NDC");
  pt1->SetTextColor(1);
  pt1->AddText("PREX collimator");
  TPaveText *pt2 = new TPaveText(.5,.7,.85,.8, "NDC");
  pt2->SetTextColor(2);
  pt2->AddText("CREX collimator");
  TPaveText *pt3 = new TPaveText(.5,.6,.85,.7, "NDC");
  pt3->SetTextColor(3);
  pt3->AddText("CREX collimator + 2 mm top and bottom");
  TPaveText *pt4 = new TPaveText(.5,.5,.85,.6, "NDC");
  pt4->SetTextColor(4);
  pt4->AddText("CREX collimator + 8.5 mm top and bottom");

  pt1->Draw();
  pt2->Draw();
  pt3->Draw();
  pt4->Draw();

  //can->SaveAs("shim.png");
  can->SaveAs("shimprex.png");

}
