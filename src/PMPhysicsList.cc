#include "PMPhysicsList.hh"

PMPhysicsList::PMPhysicsList()
{
    //EM
    RegisterPhysics(new G4EmStandardPhysics());
}

PMPhysicsList::~PMPhysicsList()
{

}