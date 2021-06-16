void getPart(){
  // 189057 events for ..._2.dat, 190438 for ..._3.dat
  fstream myfile("cosmic_run1025_HodoOnly.dat",ios::in); 
  string line;
  int cnt=0;
  fstream fout("cosmic_run1025_HodoOnly_run05_10kEvts.dat",ios::out);
  int index = 5;
  if (myfile)  // same as: if (myfile.good())
    {
    while (getline( myfile, line ))  // same as: while (getline( myfile, line ).good())
      {
         cnt++;
         if(cnt<=20000*(index+1) && cnt>=20000*index+1) fout<<line<<endl;
      }
    myfile.close();
    }
  else cout << "fooey\n";  
  cout<<cnt<<endl;
  myfile.close();
  fout.close();  
  exit(0);
}
