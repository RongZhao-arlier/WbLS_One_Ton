#include <stdio>
#include <string>
void checkHodoRate(){
    fstream fin("cosmic_run1023.dat",ios::in);
    fstream fin_time("cosmic_run1023_time.dat",ios::in);
    fstream fout_time("cosmic_run1023_time_hodo.dat",ios::out);
    string secondary;
    int id;
    string name;
    float ke, x, y, z;
    float charge, t;
    int PDGid;
    float u, v, w;
    float mass;
    float px,py,pz;
    float time;
    
    TH1F* hKE = new TH1F("Energy","",50000,0,1000);
    TH1F* hX = new TH1F("x","",2000*2.5,-2000*2.5,2000*2.5);
    TH1F* hY = new TH1F("y","",2000*2.5,-2000*2.5,2000*2.5);
    TH1F* hZ = new TH1F("z","",2000,-1000,3000); 
    TH1F* hU = new TH1F("direction_u","",500,-1,1);
    TH1F* hV = new TH1F("direction_v","",500,-1,1);
    TH1F* hW = new TH1F("direction_w","",500,-1,1);
    TH2F* hxy = new TH2F("MuonPos","",2000*2.5,-2000*2.5,2000*2.5,2000*2.5,-2000*2.5,2000*2.5);
    TH2F* hxy1 = new TH2F("MuonPos1","",2000*2.5,-2000*2.5,2000*2.5,2000*2.5,-2000*2.5,2000*2.5);
    TH1F* hZenithAngle = new TH1F("hZenithAngle","",100.0*2,-1.0*TMath::Pi(),1.0*TMath::Pi());
    TH1F* hPolarAngle = new TH1F("hPolarAngle","",100.0*2,-1.0*TMath::Pi(),1.0*TMath::Pi());
    TH1F* hZenithAngleHodo = new TH1F("hZenithAngle_Hodo","",100.0*2,-1.0*TMath::Pi(),1.0*TMath::Pi());
    TH1F* hPolarAngleHodo = new TH1F("hPolarAngle_Hodo","",100.0*2,-1.0*TMath::Pi(),1.0*TMath::Pi());

    TFile* myrootfile = new TFile("cosmic_run1023_30mRange.root","recreate"); //cosmic_muons_only_5MEvts

    TTree* mytree = new TTree("CryEvtTree","Cry Event Tree");
    int EvtNumber;
    float cospolarangle;
    float coszenithangle;
    const int nlayers = 13009; // I divide 13009 layers with 0.1 mm step from z=800.4 to z=-500.4.
    float xpos_tree, ypos_tree;
    float zpos_tree[nlayers]; // start from 800.4 to -500.4, with a step of 0.1 mm.
    for(int i=0;i<nlayers;i++) zpos_tree[i] = 800.4 - 0.1*i;
    float xbounder = 500.0; //497.5 is actually outeredge for the acrylic, here I use 500 to allow some margin.
    float ybounder = xbounder; // same for y.
    bool hodotrigflag;
    bool hitCDflag;
    float zposincd; // the first z coordinate when in the CD.
    mytree->Branch("EventNumber",&EvtNumber,"EventNumber/I");
    mytree->Branch("CosPolarAngle",&cospolarangle,"CosPolarAngle/F");
    mytree->Branch("CosZenithAngle",&coszenithangle,"CosZenithAngle/F");
    mytree->Branch("XTree",&xpos_tree,"XTree/F");
    mytree->Branch("YTree",&ypos_tree,"YTree/F");
    mytree->Branch("HodoTrigFlag",&hodotrigflag,"HodoTrigFlag/O");
    mytree->Branch("hitCDFlag",&hitCDflag,"hitCDFlag/O");
    mytree->Branch("ZTree",&zposincd,"ZTree/F");
    
    int tempID;
    float tempKE;
    int placeholder; // the 1s 
    int placeholder1; //the 0s

    double z0 = 3000;
    double z1 = 1148; // a little right above Z coordinate of H2
    double x1, y1;
    double x11, y11;
    double lowx = 268.288, lowy = -24.604, highx=369.888, highy = 76.994;
    int cntforH2 = 0;
    double zenithangle = 0, azimuthangle = 0;
    double len = 0;
    double lenxy = 0;

    double z11[4]={1136.7125, 894.425, 1147.825, 900.925};
    bool hodoFlag[4]={false, false, false, false};
    double lowx1[4]={215.9,216.25, 268.288, 222.25};
    double lowy1[4]={-20.034,-32.671,-24.606,37.116};
    double highx1[4]={317.5, 317.85, 369.888, 323.85};
    double highy1[4]={68.866, 81.629, 76.994, 151.416};
    float range = 30.0*1000.0;//mm
    int totalcnt = 0;   
    while(fin>>placeholder){
        fin>>placeholder>>id>>placeholder1>>placeholder1>>px>>py>>pz>>mass>>placeholder1>>x>>y>>z;
        fin_time>>time;
        // only select the muons that are not within 2m box, in other words, muons between 2 and 3 m.
        if(TMath::Abs(x)>range/2.0 || TMath::Abs(y)>range/2.0 ) {totalcnt++; if(totalcnt>=3000000) break; continue;}
        //if(name.compare("muon")==0 && id==0 ) {
          ke = TMath::Sqrt(px*px+py*py+pz*pz);
          hKE->Fill(ke*ke+mass*mass);
          hX->Fill(x);
          hY->Fill(y);
          hZ->Fill(z);
          hU->Fill(px);
          hV->Fill(py);
          hW->Fill(pz);
          hxy->Fill(x,y);
          len = TMath::Sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1)+(z1-z)*(z1-z));
          lenxy = TMath::Sqrt((x-x1)*(x-x1)+(y-y1)*(y-y1));
          zenithangle = TMath::ACos((z1-z)/len);  coszenithangle = (z1-z)/len;
          azimuthangle = TMath::ASin((y-y1)/lenxy); cospolarangle = (y-y1)/lenxy;
          hZenithAngle->Fill(zenithangle);
          hPolarAngle->Fill(azimuthangle);
          x1 = (px/pz)*(z1-z)+x;
          y1 = (py/pz)*(z1-z)+y;
          for(int j=0;j<4;j++){
              x11 = (px/pz)*(z11[j]-z)+x;
              y11 = (py/pz)*(z11[j]-z)+y;
              if(x11>=lowx1[j] && x11<=highx1[j] && y11>=lowy1[j] && y11<=highy1[j])  {hodoFlag[j]=true;}
          }
          for(int j=0;j<nlayers;j++){
              xpos_tree = (px/pz)*(zpos_tree[j]-z)+x;
              ypos_tree = (py/pz)*(zpos_tree[j]-z)+y;
              if(TMath::Sqrt(xpos_tree*xpos_tree+ypos_tree*ypos_tree)<=xbounder){
                if(TMath::Abs(xpos_tree)<=xbounder && TMath::Abs(ypos_tree)<=ybounder ){
                  hitCDflag=true;
                  zposincd=zpos_tree[j];
                  break;
              }
            }
          }
          //the hodo trigger is defined this way: H0||H2 && H1||H3
          if( (hodoFlag[0]||hodoFlag[1]) && (hodoFlag[1]||hodoFlag[3])){
              hZenithAngleHodo->Fill(zenithangle);
              hPolarAngleHodo->Fill(azimuthangle);
              hodotrigflag=true;
              fout_time<<time<<endl;
          }
          if(x1>=lowx && x1<=highx && y1>=lowy && y1<=highy) cntforH2++;
          hxy1->Fill(x1,y1);
          totalcnt++; EvtNumber = totalcnt;
          //prepare to write the tree

          mytree->Fill();
          //after every event reset the flags
          for(int j=0;j<4;j++) hodoFlag[j]=false; 
          hodotrigflag=false; hitCDflag=false; 
          zposincd=1000; // give it a strange number out of range (for initialization)
          if(totalcnt%500==0) cout<<totalcnt<<endl;
          if(totalcnt>=3000000) break;
        //}
    }
    fin.close();
    fin_time.close(); fout_time.close();
    mytree->Write();
    myrootfile->Write();
    cout<<"Number of events should pass through H2: "<<cntforH2;
    
    TCanvas* c = new TCanvas();
    c->Divide(2,2);
    c->cd(1);
    hKE->Draw();
    hKE->SetXTitle("Energy (GeV)");
    hKE->SetYTitle("Counts");
    c->cd(2);
    hX->Draw();
    hX->SetXTitle("x (meter)");
    hX->SetYTitle("Counts");
    c->cd(3);
    hY->Draw();
    hY->SetXTitle("y (meter)");
    hY->SetYTitle("Counts");
    c->cd(4);
    hZ->Draw();
    hZ->SetXTitle("z (meter)");
    hZ->SetYTitle("Counts");
    
    TCanvas* c2 = new TCanvas();
    c2->Divide(2,2);
    c2->cd(1); hU->Draw(); hU->SetXTitle("u"); hU->SetYTitle("counts");
    c2->cd(2); hV->Draw(); hV->SetXTitle("v"); hV->SetYTitle("counts");
    c2->cd(3); hW->Draw(); hW->SetXTitle("w"); hW->SetYTitle("counts");

    TCanvas* c3 = new TCanvas();
    hxy->Draw("colz");
    hxy->SetXTitle("X (mm)");
    hxy->SetYTitle("Y (mm)");
    c3->Update();
    TPaveStats* ps = (TPaveStats *)hxy->GetListOfFunctions()->FindObject("stats");
    cout<<"test output"<<endl;
    ps->SetX2NDC(0.9);
    ps->SetY2NDC(0.9);
    ps->SetX1NDC(0.65);
    ps->SetY1NDC(0.65);
    c3->Modified();
    c3->Update();

    TCanvas* c4 = new TCanvas();
    hxy1->Draw("colz");
    hxy1->SetXTitle("X (mm)");
    hxy1->SetYTitle("Y (mm)");
    c4->Update();
    TPaveStats* ps1 = (TPaveStats *)hxy1->GetListOfFunctions()->FindObject("stats");
    cout<<"test output"<<endl;
    ps1->SetX2NDC(0.9);
    ps1->SetY2NDC(0.9);
    ps1->SetX1NDC(0.65);
    ps1->SetY1NDC(0.65);
    c4->Modified();
    c4->Update();
    TLine* l1 = new TLine(lowx,lowy,highx,lowy); l1->Draw();
    TLine* l2 = new TLine(lowx,lowy,lowx,highy); l2->Draw();
    TLine* l3 = new TLine(highx,lowy,highx,highy);l3->Draw();
    TLine* l4 = new TLine(lowx,highy,highx,highy);l4->Draw();

    TCanvas* c5 = new TCanvas();
    hZenithAngle->Draw(); hZenithAngle->SetLineColor(kBlack);
    hPolarAngle->Draw("same"); hPolarAngle->SetLineColor(kBlue);
    TLegend* leg5 = new TLegend(0.2,0.7,0.45,0.9);
    leg5->AddEntry(hZenithAngle,"Zenith Angle","l");
    leg5->AddEntry(hPolarAngle,"Azimuth angle","l");
    leg5->Draw();

    TCanvas* c6 = new TCanvas();
    hZenithAngleHodo->Draw(); hZenithAngleHodo->SetLineColor(kBlack);
    hPolarAngleHodo->Draw("same"); hPolarAngleHodo->SetLineColor(kBlue);
    TLegend* leg6 = new TLegend(0.2,0.7,0.45,0.9);
    leg6->SetHeader("Hodo Triggers");
    leg6->AddEntry(hZenithAngleHodo,"Zenith Angle","l");
    leg6->AddEntry(hPolarAngleHodo,"Azimuth angle","l");
    leg6->Draw();
}
