#include "PhysicsList.hh"
#include "MCPDefinition.hh"
#include "G4EmStandardPhysics_option4.hh"
#include "G4HadronPhysicsQGSP_BERT.hh"
#include "G4IonPhysics.hh"

PhysicsList::PhysicsList()
{ 
    ReplacePhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4OpticalPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    //RegisterPhysics(new G4HadronPhysicsQGSP_BERT());
    //RegisterPhysics(new G4IonPhysics());
    RegisterPhysics(new MCPDefinition());
}


PhysicsList::~PhysicsList()
{
}

