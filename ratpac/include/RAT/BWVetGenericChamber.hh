//
// $Id: BWVetGenericChamber.hh,v 1.1 2005/09/28 05:04:23 sekula Exp $
// --------------------------------------------------------------
//
#ifndef __RAT_BWVetGenericChamber__
#define __RAT_BWVetGenericChamber__

#include <G4VSensitiveDetector.hh>
#include <RAT/BWVetGenericChamberHit.hh>


class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

namespace RAT {

class BWVetGenericChamber : public G4VSensitiveDetector //, public GLG4Configurable
{
  
public:
  BWVetGenericChamber(G4String name);
  virtual ~BWVetGenericChamber();
  
  virtual void Initialize(G4HCofThisEvent*HCE);
  virtual G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*ROhist);
  virtual void EndOfEvent(G4HCofThisEvent*HCE);

  void InitializeHitFlag(){hitFlag.resize(6);for(int i=0;i<6;i++) hitFlag[i]=0;}
  void ResetHitFlag(){for(int i=0;i<6;i++) hitFlag[i]=0;}
  void SetHitFlag(int number, int flag){hitFlag[number]=flag;}
  std::vector<int> GetHitFlag(){return hitFlag;}

  void InitializeHitEdep(){hitEdep.resize(6);for(int i=0;i<6;i++)hitEdep[i]=0.0;}
  void ResetHitEdep(){for(int i=0;i<6;i++)hitEdep[i]=0.0;}
  std::vector<double> GetHitEdep(){return hitEdep;}
  void SetHitEdep(int number, double energy){hitEdep[number]+=energy;}

  void InitializeHodoHitTime(){hodoHitTime.resize(6);for(int i=0;i<6;i++)hodoHitTime[i]=0.0;}
  void ResetHodoHitTime(){for(int i=0;i<6;i++)hodoHitTime[i]=0.0;}
  std::vector<double> GetHodoHitTime(){return hodoHitTime;}
  void SetHodoHitTime(int number, double thetime){
      hodoHitTime[number]=thetime;
  }


  // Data members which are publicly accessible and can be
  // written out to the RAT event tree

  std::vector<float> _hit_x;
  /** hit x-coordinate */
  std::vector<float> _hit_y;
  /** hit y-coordinate */
  std::vector<float> _hit_z;
  /** hit z-coordinate */
  std::vector<double> _hit_E;
  /** hit energy deposition */
  std::vector<float> _hit_time;
  /** global time of the hit */
  std::vector<int> _hit_uid;
  /** unique identifier code of the hit */
  std::vector<int> _hit_pdg;
  /** pdg of particle that left the hit */
  std::vector<std::string> _hit_volume;
  /** name of volume of hit */

private:
  int fLastEventID;
  int fLastTrackID;
  std::vector<int> hitFlag;
  std::vector<double> hitEdep;
  std::vector<double> hodoHitTime;
    
  BWVetGenericChamberHitsCollection* _hitsCollection;
  G4int HCID;
  G4HCofThisEvent*              _HCE;
};


} // namespace RAT

#endif
