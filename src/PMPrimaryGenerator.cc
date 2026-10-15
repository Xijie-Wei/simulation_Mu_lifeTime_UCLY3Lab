#include "PMPrimaryGenerator.hh"

PMPrimaryGenerator::PMPrimaryGenerator()
{
    fParticleGun = new G4ParticleGun(1);

    //particle position
    G4double x = 0. *m;
    G4double y = -7.5 *cm;
    G4double z = 0. *cm;

    G4ThreeVector pos(x,y,z);

    //particle direction
    G4double px = 0.;
    G4double py = 1.;
    G4double pz = 0.;

    G4ThreeVector mom(px,py,pz);

    // particle type
    G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
    G4ParticleDefinition *particle = particleTable->FindParticle("mu-");

    fParticleGun->SetParticlePosition(pos);
    fParticleGun->SetParticleMomentumDirection(mom);
    fParticleGun->SetParticleEnergy(160. *MeV);
    fParticleGun->SetParticleDefinition(particle);
}

PMPrimaryGenerator::~PMPrimaryGenerator()
{
    delete fParticleGun;
}

void PMPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
    // create vertex
    fParticleGun->GeneratePrimaryVertex(anEvent);
}