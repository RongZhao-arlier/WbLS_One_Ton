/* 

Copyright (c) 2007-2012, The Regents of the University of California. 
Produced at the Lawrence Livermore National Laboratory 
UCRL-CODE-227323. 
All rights reserved. 
 
For details, see http://nuclear.llnl.gov/simulations
Please also read this http://nuclear.llnl.gov/simulations/additional_bsd.html
 
Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are
met:
 
1.  Redistributions of source code must retain the above copyright
notice, this list of conditions and the disclaimer below.

2. Redistributions in binary form must reproduce the above copyright
notice, this list of conditions and the disclaimer (as noted below) in
the documentation and/or other materials provided with the
distribution.

3. Neither the name of the UC/LLNL nor the names of its contributors
may be used to endorse or promote products derived from this software
without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
"AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE REGENTS OF
THE UNIVERSITY OF CALIFORNIA, THE U.S. DEPARTMENT OF ENERGY OR
CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/


#include "CRYGenerator.h"
#include "CRYSetup.h"

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <stdlib.h>  // For Ubuntu Linux

#include <math.h>

int main( int argc, const char *argv[]) {

  int nEv=1000; //....default number of cosmic-ray events to produce
  std::string foutname="test_data.txt";//....default filename to output

  if ( argc < 2 ) {
    std::cout << "usage " << argv[0] << " <setup file name> <N events>\n";
    std::cout << "N events = " << nEv << " by default\n";
    return 0;
  }

  if ( argc > 2 ) nEv=atoi(argv[2]);

  //prepare a file to save data
  if( argc > 3 ) foutname = argv[3];
  std::fstream fout(foutname.c_str(),std::ios::out);

  // Read the setup file into setupString
  std::ifstream inputFile;
  inputFile.open(argv[1],std::ios::in);
  char buffer[1000];

  std::string setupString("");
  while ( !inputFile.getline(buffer,1000).eof()) {
    setupString.append(buffer);
    setupString.append(" ");
  }

  // Parse the contents of the setup file
  CRYSetup *setup=new CRYSetup(setupString,"./data");

  // Setup the CRY event generator
  CRYGenerator gen(setup);


  // Generate the events
  std::vector<CRYParticle*> *ev=new   std::vector<CRYParticle*>;
  
  double m_muon = 105.6583745; //muon mass in MeV/c^2. mu- pdg code 13, mu+ pdg code -13
  double m_e = 0.511;  //electron mass in MeV/c^2. electron pdg code 11, positron pdg code -11 
  double m_neutron = 939.5654133; //neutron mass in MeV/c^2. neutron pdg code 2112
  double m_proton = 938.2720813; //proton mass in MeV/c^2. proton pdg code 2212    
  double m_gamma = 0; //gamma, no mass, pdg code 22
  double m_pion = 139.57018; //pi+ pi-, pdg code 211, -211
  double m0 = 105.6583745; // muon mass in MeV/c^2
  double v_over_c; // v/c
  double ke;       // kinetic energy, in MeV;
  double px, py, pz;
  double r; // the lorentz factor
  double c = 3.0*1E8; // speed of light, m/s
  
  
  for ( int i=0; i<nEv; i++) {
    ev->clear();
    gen.genEvent(ev);

    // Write the event information to standard output
    std::cout << "Event: " << i << ", Nb of Secondaries: "<< ev->size() << std::endl;
    if(ev->size()!=1) continue;
    for ( unsigned j=0; j<ev->size(); j++) {
      CRYParticle* p = (*ev)[j];
      /*
      fout << "Secondary\t" << j 
                << "\t" << CRYUtils::partName(p->id()) //name
                << "\t" << p->ke() //ke
                //<< " (x,y,z)=" 
                << "\t" << p->x()
                << "\t" << p->y()
                << "\t" << p->z() //position unit in m
                << "\t" << p->charge()
                << "\t" << p->t()
//                << "\t" << p->id()
                << "\t" << p->PDGid()
                << "\t" << p->u()
                << "\t" << p->v()
                << "\t" << p->w() //direction cosines
                //<< " (m)"
                << "\n"; 
                */
      if(p->PDGid() == 11 || p->PDGid() == -11 || p->PDGid() == 22) continue;//ignore electrons and gamma
      if(p->PDGid() == 13 || p->PDGid() == -13) m0 = m_muon; //muon
      else if(p->PDGid()==2212||p->PDGid()==-2212) m0=m_proton;//proton
      else if(p->PDGid()==2112) m0=m_neutron;//neutron
      else if(p->PDGid()==211 || p->PDGid()==-211) m0=m_pion;//neutron
      else {std::cout<<"Looks there is unknown particle..."<<p->PDGid()<<std::endl; exit(0);}
      ke = p->ke();
      r = (ke+m0)/m0;
      v_over_c = sqrt(1.0-1.0/(r*r));
      px = r*m0*v_over_c*p->u();
      py = r*m0*v_over_c*p->v();
      pz = r*m0*v_over_c*p->w();
      fout<<1<<"\n";
      fout<<"1 "<<p->PDGid()<<" 0 0 "
          <<px/1000.0<<" " //MeV to GeV
          <<py/1000.0<<" "
          <<pz/1000.0<<" "
          <<m0/1000.0<<" "
          <<"0 "
          <<p->x()*1000.0<<" " // m to mm
          <<p->y()*1000.0<<" "
          <<3000.0
       //   <<ke/1000.0
          <<"\n";
      delete (*ev)[j];
    }
  }
  
  //close the txt file
  fout.close();

  std::cout << "Run completed.\n";
  std::cout << "Total time simulated: " << gen.timeSimulated() << " seconds\n";

  return 0;
}
