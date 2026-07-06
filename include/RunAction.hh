#ifndef RUNACTION_HH
#define RUNACTION_HH

#include "G4UserRunAction.hh"
#include "G4Run.hh"
#include "globals.hh"

/*
struct IDList {
	G4int pName;
	G4int cProc;
	G4int E;
	G4int px;
	G4int py;
	G4int pz;
	G4int eid;
	G4int pid;
};
*/

struct countList {
	G4int pos;
	G4int eid;
	G4int num;
};

/*
struct EList { 
	G4int Escint;
	G4int Echeren;
};
*/

//extern G4ThreadLocal IDList id;
extern G4ThreadLocal countList cid;
//xtern G4ThreadLocal EList Enid;

class RunAction : public G4UserRunAction
{
public:
    RunAction();
    virtual ~RunAction() override;
    virtual void BeginOfRunAction(const G4Run* run) override;
    virtual void EndOfRunAction(const G4Run* run) override;
    static G4ThreadLocal G4int fTotalEvents;
};

#endif
