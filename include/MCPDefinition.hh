#pragma once
#include "G4VPhysicsConstructor.hh"
class MCPDefinition : public G4VPhysicsConstructor {
public:
  MCPDefinition(const G4String& name="MCPDefinition") : G4VPhysicsConstructor(name) {}
  ~MCPDefinition() override = default;
  void ConstructParticle() override; 
  void ConstructProcess() override; 
};
