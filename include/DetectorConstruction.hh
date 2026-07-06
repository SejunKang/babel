#ifndef DETECTORCONSTRUCTION_HH
#define DETECTORCONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
 
class DetectorConstruction : public G4VUserDetectorConstruction
 {
 public:
     DetectorConstruction();
     virtual ~DetectorConstruction();
     virtual G4VPhysicalVolume* Construct();

 private:

 };

#endif

