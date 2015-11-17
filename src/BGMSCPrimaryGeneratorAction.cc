#include "BGMSCPrimaryGeneratorAction.hh"

#include "G4Proton.hh"

using namespace CLHEP;

BGMSCPrimaryGeneratorAction::BGMSCPrimaryGeneratorAction()
{
    Source = new G4ParticleGun;
    Source->SetParticleDefinition(G4Proton::Definition());
    Source->SetParticleEnergy(158.6*MeV);
    Source->SetParticleMomentumDirection(G4ThreeVector(0,0,1));
    Source->SetParticlePosition(G4ThreeVector(0,0,-1*mm));
}

BGMSCPrimaryGeneratorAction::~BGMSCPrimaryGeneratorAction()
{
    delete Source;
}

void BGMSCPrimaryGeneratorAction::GeneratePrimaries(G4Event* event)
{
    Source->GeneratePrimaryVertex(event);
}
