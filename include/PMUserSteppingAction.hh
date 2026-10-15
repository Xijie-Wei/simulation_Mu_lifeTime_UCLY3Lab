#ifndef PMUSERSTEEPINGACTION_HH
#define PMUSERSTEEPINGACTION_HH

#include "G4UserSteppingAction.hh"

class PMUserSteppingAction : public G4UserSteppingAction 
{
public:
    PMUserSteppingAction();
    ~PMUserSteppingAction();

    virtual void UserSteppingAction(const G4Step*);
};

#endif