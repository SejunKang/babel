#include "SteppingAction.hh"
#include "RunAction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4TrackStatus.hh"
#include "G4Step.hh"
#include "G4VProcess.hh"
#include "G4AnalysisManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Track.hh"

SteppingAction::SteppingAction(EventAction* event) : G4UserSteppingAction(), fEvent(event)
{
}

SteppingAction::~SteppingAction()
{
}

void SteppingAction::UserSteppingAction(const G4Step* step)
{
    G4AnalysisManager* AM = G4AnalysisManager::Instance();
    G4int eventID = G4RunManager::GetRunManager() -> GetCurrentEvent() -> GetEventID();
    G4int parentID = step -> GetTrack() -> GetParentID();
    G4Track *track = step -> GetTrack();

    //Defining particle name
    G4String parName = step -> GetTrack() -> GetDefinition() -> GetParticleName();

    //Defining process
    const G4VProcess* creProc = step -> GetTrack() -> GetCreatorProcess();
    G4String creProcName;
    if (creProc) creProcName = creProc -> GetProcessName();
    else creProcName = "primary";
    const G4VProcess* proc = step -> GetPostStepPoint() -> GetProcessDefinedStep();
    G4String procName = proc -> GetProcessName();    

    //Defining Physical Volume
    G4String namePostPV;
    G4VPhysicalVolume* postPV = step -> GetPostStepPoint() -> GetPhysicalVolume();
    if (postPV != 0) namePostPV = postPV -> GetName();
    else namePostPV = "outside";

    G4String namePrePV;
    G4VPhysicalVolume* prePV = step -> GetPreStepPoint() -> GetPhysicalVolume();
    namePrePV = prePV -> GetName();

    //Defining Kinetic Energy
    G4double preKinEgy  = step -> GetPreStepPoint()  -> GetKineticEnergy();
    G4double postKinEgy = step -> GetPostStepPoint() -> GetKineticEnergy();
    
    //Defining Momentum
    auto preMomentum = step -> GetPreStepPoint() -> GetMomentum();
    auto postMomentum = step -> GetPostStepPoint() -> GetMomentum();

    //Extracting informations of the created particles inside the scintillator
    /*
    if (track -> GetCurrentStepNumber() == 1 && (namePrePV == "ScintPV" && namePostPV == "ScintPV") && parName != "opticalphoton") {
	AM -> FillNtupleSColumn(0, id.pName, parName);
    	AM -> FillNtupleSColumn(0, id.cProc, creProcName);
        AM -> FillNtupleDColumn(0, id.E, postKinEgy /MeV);
	AM -> FillNtupleDColumn(0, id.px, postMomentum.getX() /MeV);
	AM -> FillNtupleDColumn(0, id.py, postMomentum.getY() /MeV);
	AM -> FillNtupleDColumn(0, id.pz, postMomentum.getZ() /MeV);
        AM -> FillNtupleIColumn(0, id.eid, eventID);
	AM -> FillNtupleIColumn(0, id.pid, parentID);
        AM -> AddNtupleRow(0);
   }
   */

   //About opticalphotons
   if (parName == "opticalphoton" && namePostPV == "PMTPhy") {
	fEvent -> AddNum();		
        track -> SetTrackStatus(fStopAndKill);  
   }

   if (parName == "opticalphoton" && namePostPV == "WorldPV") track -> SetTrackStatus(fStopAndKill);
}