#include <stdio>
#include <string>
void countValidEventNumber(){
    fstream fin("cosmic_include_np_5MEvts.dat",ios::in);
    string secondary;
    int id;
    string name;
    float ke, x, y, z;
    float charge, t;
    int PDGid;
    float u, v, w;
    float mass;
    float px,py,pz;
    
    TH1F* hKE = new TH1F("Energy","",50000,0,500);
    TH1F* hX = new TH1F("x","",2000,-2000,2000);
    TH1F* hY = new TH1F("y","",2000,-2000,2000);
    TH1F* hZ = new TH1F("z","",2000,-1000,3000); 
    TH1F* hU = new TH1F("direction_u","",500,-1,1);
    TH1F* hV = new TH1F("direction_v","",500,-1,1);
    TH1F* hW = new TH1F("direction_w","",500,-1,1);
    TH2F* hxy = new TH2F("MuonPos","",2000,-2000,2000,2000,-2000,2000);
    TH2F* hxy1 = new TH2F("MuonPos1","",2000*2.5,-2000*2.5,2000*2.5,2000*2.5,-2000*2.5,2000*2.5);
    
    int tempID;
    float tempKE;
    int placeholder; // the 1s 
    int placeholder1; //the 0s

    double z0 = 3000;
    double z1 = 1148;
    double x1, y1;
    double lowx = 268.288, lowy = -24.604, highx=369.888, highy = 76.994;
    int cntforH2 = 0;
    
    int totalcnt = 0;   
    int pioncnt = 0;
    while(fin>>placeholder){
        fin>>placeholder>>id>>placeholder1>>placeholder1>>px>>py>>pz>>mass>>placeholder1>>x>>y>>z;
        if(id==211 || id==-211) pioncnt++;
 
          totalcnt++;

        //}
    }
    fin.close();
    cout<<"Number of events : "<<totalcnt<<endl;
    cout<<"Number of pions : "<<pioncnt<<endl;
    
}
