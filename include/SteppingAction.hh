
#ifndef STEPPINGACTION_HH
#define STEPPINGACTION_HH

#include "G4UserSteppingAction.hh"

#include "EventAction.hh"

class EventAction;

class SteppingAction: public G4UserSteppingAction
{
  public:
	SteppingAction(EventAction* event);
	virtual ~SteppingAction();

	virtual void UserSteppingAction(const G4Step* step);
    

  private:
	EventAction* fEvent;

};

#endif
