#include "G4MuonMinus.hh"
#include "PrimaryGeneratorAction.hh"
#include "G4ThreeVector.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTable.hh"
#include "Randomize.hh"

G4bool PrimaryGeneratorAction::IsVertical = true;
G4double PrimaryGeneratorAction::fzpos = 0.*cm;

PrimaryGeneratorAction::PrimaryGeneratorAction(): G4VUserPrimaryGeneratorAction()
{
    fPrimary = new G4ParticleGun();
	messenger = new G4GenericMessenger(this, "/gun/", "Primary control");
	messenger -> DeclarePropertyWithUnit("zpos", "cm", fzpos, "Cosmic muon z position");
	messenger -> DeclareProperty("vertical", IsVertical, "Decide particle gun direction");
}

PrimaryGeneratorAction::~PrimaryGeneratorAction()
{
    delete fPrimary;
	delete messenger;
}

void PrimaryGeneratorAction::GeneratePrimaries(G4Event *event)
{
	auto parTable = G4ParticleTable::GetParticleTable();
	auto particle = parTable -> FindParticle("mu-");
   		fPrimary -> SetParticleDefinition(particle);
    	fPrimary -> SetParticleEnergy(1. *GeV);

		//Horizontal
		if (!IsVertical) {
    		fPrimary -> SetParticlePosition(G4ThreeVector(0., 0., -80. *cm));
    		fPrimary -> SetParticleMomentumDirection(G4ThreeVector(0., 0., 1.));
		}

		//Vertical
		else {
			fPrimary -> SetParticlePosition(G4ThreeVector(0., 5. *cm, fzpos));
    		fPrimary -> SetParticleMomentumDirection(G4ThreeVector(0., -1., 0.));
		}

    	fPrimary -> GeneratePrimaryVertex(event);
}                                                                                                       
