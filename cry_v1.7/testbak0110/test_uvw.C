{
  fstream fin("test_uvw.txt",ios::in);
  double u,v,w;
  double theta;
  TH1F* hu = new TH1F("hu","",100,-1,1);
  TH1F* hv = new TH1F("hv","",100,-1,1);
  TH1F* hw = new TH1F("hw","",100,-1,1);
  TH1F* htheta = new TH1F("hTheta","",900,0,180);
  TH2F* htheta_vs_w = new TH2F("hTheta_vs_w","",900,0,180,100,-1,1);
  while(fin>>u>>v>>w){
   //cout<<u<<endl;
    theta = (TMath::Pi() - TMath::ACos(w))*180.0/TMath::Pi();
    htheta->Fill(theta);
    hu->Fill(u);
    hv->Fill(v);
    hw->Fill(w);
    htheta_vs_w->Fill(theta,w);
    if(w==-1){cout<<u<<"\t"<<v<<"\t"<<w<<endl;}
  }
  TCanvas* c = new TCanvas();
  hu->Draw(); hu->SetLineColor(1);
  hv->Draw("same"); hv->SetLineColor(2);
  hw->Draw("same"); hw->SetLineColor(3);
  TCanvas* c1 = new TCanvas();
  //htheta_vs_w->Draw("colz");
  htheta->Draw();
}
