void drawZenithAll(){
    gStyle->SetOptStat(0);
    TFile* rootf[12];
    TH1F* hist[12];
    char filename[100], legtitle[20];
    int thesenumber[12]={2,4,6,8,10,12,14,16,18,20,25,30};
    TCanvas* c = new TCanvas();
    TLegend* leg = new TLegend(0.7,0.6,0.95,0.75);
    leg->SetHeader("Box size");
    leg->SetNColumns(2);
    for(int i=0; i<12; i++){
        sprintf(filename, "cosmic_muons_only_3MEvts_box30m_onlyHitCD_2_%dmRange_out.root",thesenumber[i]);
        rootf[i]=new TFile(filename,"read");
        hist[i]=(TH1F*)rootf[i]->Get("hPolarAngleAll");
        hist[i]->SetXTitle("Cosine of angle");
        hist[i]->SetYTitle("Counts");
        hist[i]->Draw("same");
        if(i%2==0) {hist[i]->SetLineStyle(2);hist[i]->SetLineColor(i/2+1);}
        else {hist[i]->SetLineStyle(1);    hist[i]->SetLineColor(i/2+1);}
        hist[i]->SetLineWidth(2);
        sprintf(legtitle,"%d m", thesenumber[i]);
        leg->AddEntry(hist[i],legtitle,"l");
    }
    leg->Draw();
}
