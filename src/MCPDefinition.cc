#include "MCPDefinition.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "G4PionZero.hh"
#include "G4DecayTable.hh"
#include "G4PhaseSpaceDecayChannel.hh"
#include "G4ProcessManager.hh"
#include "G4eMultipleScattering.hh"
#include "G4CoulombScattering.hh"
#include "G4Transportation.hh"
#include "G4StepLimiter.hh"
#include "G4WentzelVIModel.hh"
#include "G4eIonisation.hh"
#include "G4hIonisation.hh"

void MCPDefinition::ConstructParticle(){
  G4ParticleTable* pTable = G4ParticleTable::GetParticleTable();
  G4ParticleDefinition* mcp = new G4ParticleDefinition(
    "mcp",             //name
    10 *MeV, //mass -> Must be changed if simulated with other mCP mass models!
    0. *MeV,           //width
    0.001 *eplus,      //charge  
    1,                 //spin
    0,                 //parity
    0,                 //C-conjugation
    0,                 //isospin
    0,                 //isospin3
    0,                 //G-parity
    "lepton",          //type
    1,                 //lepton number
    0,                 //baryon number
    31,                //PDG code
    true,              //stability 
    -1.0,              //lifetime 
    nullptr            //decay table
    );
  
  //pTable -> Insert(mcp);

    G4ParticleDefinition* anti_mcp = new G4ParticleDefinition(
    "anti_mcp",        //name
    10 *MeV, //mass -> Must be changed if simulated with other mCP mass models!
    0. *MeV,           //width
    -0.001 *eplus,     //charge
    1,                 //spin
    0,                 //parity
    0,                 //C-conjugation
    0,                 //isospin
    0,                 //isospin3
    0,                 //G-parity
    "lepton",          //type
    1,                 //lepton number
    0,                 //baryon number
    -31,               //PDG code
    true,              //stability
    -1.0,              //lifetime
    nullptr            //decay table
    );

}

void MCPDefinition::ConstructProcess() {

  auto parTable = G4ParticleTable::GetParticleTable();
  auto pi0 = parTable -> FindParticle("pi0");

  //Erase old decay channel
  if (auto* oldChannel = pi0 -> GetDecayTable()) {
    delete oldChannel; 
    pi0 -> SetDecayTable(nullptr);
  }
  
  G4DecayTable* dTable = new G4DecayTable();
  dTable -> Insert(new G4PhaseSpaceDecayChannel("pi0", 1.0, 3, "gamma", "mcp", "anti_mcp"));
  pi0 -> SetDecayTable(dTable);

  //mCP scattering
  auto mcp = parTable -> FindParticle("mcp");
  auto anti_mcp = parTable -> FindParticle("anti_mcp");
  mcp -> SetApplyCutsFlag(true);
  anti_mcp -> SetApplyCutsFlag(true);

  for (auto p : {mcp, anti_mcp}) {
    if (!p) continue;
    auto PM = p -> GetProcessManager();
    if (!PM) continue;

    auto msc = new G4eMultipleScattering();
    auto wentzelvi = new G4WentzelVIModel();
    msc -> SetEmModel(wentzelvi);

    PM -> AddProcess(msc, -1, 1, 1);
    PM -> AddDiscreteProcess(new G4CoulombScattering());
    PM -> AddDiscreteProcess(new G4StepLimiter());
    PM -> AddProcess(new G4eIonisation(), -1, 2, 2);
    PM -> AddProcess(new G4hIonisation(), -1, 2, 2);
}

}
