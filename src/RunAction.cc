#include "G4RunManager.hh"
#include "RunAction.hh"
#include "G4AnalysisManager.hh"
#include "PrimaryGeneratorAction.hh"
#include "TFile.h"

//G4ThreadLocal IDList id;
G4ThreadLocal countList cid;
//G4ThreadLocal EList Enid;
G4ThreadLocal G4int RunAction::fTotalEvents = 0;

RunAction::RunAction() : G4UserRunAction()
{
    G4AnalysisManager *AM = G4AnalysisManager::Instance();
    AM -> SetDefaultFileType("root");
    AM -> SetNtupleMerging(true);
/*
    AM -> CreateNtuple("tree", "Information_of_created_particles");
    id.pName = AM -> CreateNtupleSColumn(0, "parName");
    id.cProc = AM -> CreateNtupleSColumn(0, "creProc");
    id.E = AM -> CreateNtupleDColumn(0, "E");
    id.px = AM -> CreateNtupleDColumn(0, "px");
    id.py = AM -> CreateNtupleDColumn(0, "py");
    id.pz = AM -> CreateNtupleDColumn(0, "pz");
    id.eid = AM -> CreateNtupleIColumn(0, "eid");
    id.pid = AM -> CreateNtupleIColumn(0, "pid");
    AM -> FinishNtuple(0);
*/

    AM -> CreateNtuple("tree", "Information_of_opticalphotons");
    if (PrimaryGeneratorAction::IsVertical) cid.pos = AM -> CreateNtupleDColumn(0, "zpos");
    cid.eid = AM -> CreateNtupleIColumn(0, "eid");
    cid.num = AM -> CreateNtupleIColumn(0, "num");
    AM -> FinishNtuple(0);

/*
    AM -> CreateNtuple("energy", "Energy_distribution_of_photons");
    Enid.Escint = AM -> CreateNtupleDColumn(2, "Escint");
    Enid.Echeren = AM -> CreateNtupleDColumn(2, "Echeren");
    AM -> FinishNtuple(2);
*/
}

RunAction::~RunAction()
{
}

void RunAction::BeginOfRunAction(const G4Run* run)
{
    fTotalEvents = run -> GetNumberOfEventToBeProcessed();
    G4AnalysisManager *AM = G4AnalysisManager::Instance();

    AM -> SetVerboseLevel(0);
    if (PrimaryGeneratorAction::IsVertical) AM -> OpenFile();
    else AM -> OpenFile("output_hor.root");
/*   
    id.pName = AM -> CreateNtupleSColumn(0, "parName");
    id.cProc = AM -> CreateNtupleSColumn(0, "creProc");
    id.E = AM -> CreateNtupleDColumn(0, "E");
    id.px = AM -> CreateNtupleDColumn(0, "px");
    id.py = AM -> CreateNtupleDColumn(0, "py");
    id.pz = AM -> CreateNtupleDColumn(0, "pz");
    id.eid = AM -> CreateNtupleIColumn(0, "eid");
    id.pid = AM -> CreateNtupleIColumn(0, "pid");

    mid.eid = AM -> CreateNtupleIColumn(1, "eid");
    mid.scint = AM -> CreateNtupleIColumn(1, "scint");
    mid.cheren = AM -> CreateNtupleIColumn(1, "cheren");
*/
    }


void RunAction::EndOfRunAction(const G4Run* run)
{
    G4AnalysisManager *AM = G4AnalysisManager::Instance();
    AM -> Write();
    AM -> CloseFile();
}