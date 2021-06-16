void AnalysisCosmicSpectrum_v1(){
    TFile* rootfile = new TFile("20170724/cosmic_muons_only_3MEvts_box30m_onlyHitCD_2_2mRange.root","read");
    TTree* tree = (TTree*)rootfile->Get("CryEvtTree");
    TBranch* bEvtNumber = tree->GetBranch("EventNumber");
    TBranch* bCosPolarAngle = tree->GetBranch("CosPolarAngle");
    TBranch* bCosZenithAngle = tree->GetBranch("CosZenithAngle");
    TBranch* bXpos = tree->GetBranch("XTree");
    TBranch* bYpos = tree->GetBranch("YTree");
    TBranch* bZpos = tree->GetBranch("ZTree");
    TBranch* bHodoTrigFlag = tree->GetBranch("HodoTrigFlag");
    TBranch* bhitCDFlag = tree->GetBranch("hitCDFlag");

    int evtNb;
    float evtPolarAngle;
    float evtZenithAngle;
    float evtX, evtY, evtZ;
    bool evtHodoFlag, evtHitCDFlag;

    bEvtNumber->SetAddress(&evtNb);
    bCosPolarAngle->SetAddress(&evtPolarAngle);
    bCosZenithAngle->SetAddress(&evtZenithAngle);
    bXpos->SetAddress(&evtX);
    bYpos->SetAddress(&evtY);
    bZpos->SetAddress(&evtZ);
    bHodoTrigFlag->SetAddress(&evtHodoFlag);
    bhitCDFlag->SetAddress(&evtHitCDFlag);
   
    TFile* rootout = new TFile("20170724/cosmic_muons_only_3MEvts_box30m_onlyHitCD_2_2mRange_out.root","recreate");

    TH1F* hPolarAngle[4];
    TH1F* hZenithAngle[4];
    hPolarAngle[0]=new TH1F("hPolarAngleAll","",1000,-1,1);
    hPolarAngle[1]=new TH1F("hPolarAngleHodo","",1000,-1,1);
    hPolarAngle[2]=new TH1F("hPolarAngleHitCD","",1000,-1,1);
    hPolarAngle[3]=new TH1F("hPolarAngle_HodoAndHitCD","",1000,-1,1);
    hZenithAngle[0]=new TH1F("hZenithAngleAll","",1000,-1,1);
    hZenithAngle[1]=new TH1F("hZenithAngleHodo","",1000,-1,1);
    hZenithAngle[2]=new TH1F("hZenithAngleHitCD","",1000,-1,1);
    hZenithAngle[3]=new TH1F("hZenithAngle_HodoAndHitCD","",1000,-1,1);
    TH1F* hZ = new TH1F("hZpos","",(801+501)*1.0,-501-0.05,801-0.05);
    TH2F* hxy = new TH2F("hXY","",520*2,-520-0.5,520-0.5,520*2,-520-0.5,520-0.5);
    TGraph2D* gxyz = new TGraph2D();
    int cntforhitcd=0;

    int cnttest=0;
    
    int nentries = (int)tree->GetEntries();
    for(int i=0;i<nentries;i++){
        bEvtNumber->GetEntry(i);
        bCosPolarAngle->GetEntry(i);
        bCosZenithAngle->GetEntry(i);
        bXpos->GetEntry(i);
        bYpos->GetEntry(i);
        bZpos->GetEntry(i);
        bHodoTrigFlag->GetEntry(i);
        bhitCDFlag->GetEntry(i);

        //do some test here to select muons in a square
        //if(TMath::Abs(evtX)>1 && TMath::Abs(evtY)>1) continue;

        //cout<<evtHodoFlag<<endl;
        if(evtHodoFlag) {cnttest++;}
        
        hPolarAngle[0]->Fill(evtPolarAngle);   
        hZenithAngle[0]->Fill(evtZenithAngle); 
        if(evtHodoFlag)  {
            //cout<<"SOmething"<<endl;
            hPolarAngle[1]->Fill(evtPolarAngle);   
            hZenithAngle[1]->Fill(evtZenithAngle); 
        }
        if(evtHitCDFlag /*&& evtZ<800.4*/)  {
            hPolarAngle[2]->Fill(evtPolarAngle);   
            hZenithAngle[2]->Fill(evtZenithAngle); 
            hZ->Fill(evtZ);
            hxy->Fill(evtX,evtY);
            gxyz->SetPoint(cntforhitcd,evtX,evtY,evtZ); cntforhitcd++;
        }
        if(evtHitCDFlag && evtHodoFlag)  {
            hPolarAngle[3]->Fill(evtPolarAngle);   
            hZenithAngle[3]->Fill(evtZenithAngle); 
        }
    }//end reading event

    cout<<"test: "<<cnttest<<endl;

    int theindex=0;
    TCanvas* c1 = new TCanvas();
    hPolarAngle[theindex]->Draw(); hPolarAngle[theindex]->SetLineColor(kBlue);
    hPolarAngle[theindex]->SetXTitle("Cosine of angle");
    hPolarAngle[theindex]->SetYTitle("Counts");
    hZenithAngle[theindex]->Draw("same"); hZenithAngle[theindex]->SetLineColor(kBlack);
    if(theindex==1 || theindex==3){hPolarAngle[theindex]->Rebin(4);hZenithAngle[theindex]->Rebin(4);}
    TLegend* leg1 = new TLegend(0.2,0.7,0.45,0.9);
    leg1->AddEntry(hZenithAngle[theindex],"Zenith Angle", "l");
    leg1->AddEntry(hPolarAngle[theindex],"Azimuth Angle", "l");
    leg1->Draw();
    for(int i=0;i<3;i++){
        hPolarAngle[i]->Write();
        hZenithAngle[i]->Write();
    }

    TCanvas* c2 = new TCanvas("cxy","",600,600);
    hxy->Draw("colz"); hxy->SetXTitle("X (mm)"); hxy->SetYTitle("Y (mm)");
    TCanvas* c3 = new TCanvas();
    hZ->Draw(); hZ->SetXTitle("Z (mm)"); hZ->SetYTitle("Counts"); 
    TCanvas* c4= new TCanvas("xyz","",600,600);
    gxyz->SetMarkerStyle(8);
    gxyz->GetXaxis()->SetTitle("X (mm)");    gxyz->GetYaxis()->SetTitle("Y (mm)");    gxyz->GetZaxis()->SetTitle("Z (mm)");
    gxyz->Draw("P");

}

