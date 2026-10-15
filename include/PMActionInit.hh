#ifndef PMACTIONINIT_HH
#define PMACTIONINIT_HH

#include "G4VUserActionInitialization.hh"

#include "PMPrimaryGenerator.hh"
#include "PMRunAction.hh"
#include "PMUserSteppingAction.hh"
#include "PMEventAction.hh"

class PMActionInit : public G4VUserActionInitialization
{
public:
    PMActionInit();
    ~PMActionInit();

    virtual void BuildForMaster() const;
    virtual void Build() const;
};

#endif