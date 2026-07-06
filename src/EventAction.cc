#include "G4RunManager.hh"
#include "EventAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4AnalysisManager.hh"
#include "G4ParticleDefinition.hh"
#include "RunAction.hh"
#include "G4Threading.hh"
#include "PrimaryGeneratorAction.hh"

using namespace std;

EventAction::EventAction() : G4UserEventAction()
{
	nPhot = 0;
}

EventAction::~EventAction()
{
}

void EventAction::BeginOfEventAction(const G4Event *event)
{
	if (G4Threading::G4GetThreadId() == 0) {
    		G4int eventID = event -> GetEventID();
    		G4int TotalEvents = RunAction::fTotalEvents;
    		cerr << fixed << setprecision(2) << "\rProgress: " << eventID << " Completed out of " << TotalEvents << " Events" << flush;
	}

    nPhot = 0;
}

void EventAction::EndOfEventAction(const G4Event *event)
{    
	G4int eventID = event -> GetEventID();
	G4AnalysisManager *AM = G4AnalysisManager::Instance();

	if (PrimaryGeneratorAction::IsVertical) AM -> FillNtupleDColumn(0, cid.pos, PrimaryGeneratorAction::fzpos /cm);
	AM -> FillNtupleIColumn(0, cid.eid, eventID);
	AM -> FillNtupleIColumn(0, cid.num, nPhot);
	AM -> AddNtupleRow(0);
}

void EventAction::AddNum() 
{
	nPhot++;
}