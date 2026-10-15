#include "PMPhysicsList.hh"

PMPhysicsList::PMPhysicsList()
{
    // EM
    RegisterPhysics(new G4EmStandardPhysics());
    
    // Decay
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4DecayPhysics());
}

PMPhysicsList::~PMPhysicsList()
{

}