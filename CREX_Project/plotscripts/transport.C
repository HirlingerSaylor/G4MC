transport(){
  TFile* infile2 = new TFile("/home/Nickie/JLab/HallA/G4MC/CREX_Project/theta.root", "READ");
  TFile* infile1 = new TFile("/home/Nickie/JLab/HallA/G4MC/CREX_Project/p.root", "READ");
  //TCanvas* can = new TCanvas("can", "can", 20, 20, 1500, 900);
  TCanvas* can = new TCanvas("can", "can", 20, 20, 1100, 700);
  can->Divide(4, 4);

  infile1->cd();

  can->cd(1);
  track0->Draw("Yfp_tr:Xfp_tr>>hist1(200, -20, 20, 200, -20, 20)", "", "COLZ");
  hist1->GetXaxis()->SetTitle("x (cm)");
  //track0->Draw("Yfp_tr:Xfp_tr", "", "COLZ");
  can->cd(2);
  track0->Draw("Yvb_tr:Xvb_tr>>hist2(200, -20, 20, 200, -20, 20)", "", "COLZ");
  //track0->Draw("Yvb_tr:Xvb_tr", "", "COLZ");
  can->cd(3);
  track0->Draw("Theta0 * 180. / 3.14159265358979 :Yfp_tr>>hist3(200, -20, 20, 200, 10, 15)", "", "COLZ");
  can->cd(4);
  track0->Draw("P0:Xfp_tr>>hist4(200, -20, 20, 200, 2., 2.5)", "", "COLZ");

  infile2->cd();

  can->cd(5);
  track0->Draw("Yfp_tr:Xfp_tr>>hist1(200, -20, 20, 200, -20, 20)", "", "COLZ");
  //track0->Draw("Yfp_tr:Xfp_tr", "", "COLZ");
  can->cd(6);
  track0->Draw("Yvb_tr:Xvb_tr>>hist2(200, -20, 20, 200, -20, 20)", "", "COLZ");
  //track0->Draw("Yvb_tr:Xvb_tr", "", "COLZ");
  can->cd(7);
  track0->Draw("Theta0 * 180. / 3.14159265358979 :Yfp_tr>>hist3(200, -20, 20, 200, 10, 15)", "", "COLZ");
  can->cd(8);
  track0->Draw("P0:Xfp_tr>>hist4(200, -20, 20, 200, 2., 2.5)", "", "COLZ");
}
