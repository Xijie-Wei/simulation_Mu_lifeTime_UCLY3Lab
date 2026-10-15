#ifndef PMEVENTACRION_HH
#define PMEVENTACRION_HH

#include "G4Event.hh"
#include "G4UserEventAction.hh"

class PMEventAction : public G4UserEventAction 
{
public:
    PMEventAction();
    virtual ~PMEventAction();

    void AddGamma(G4double) const;
    virtual void BeginOfEventAction(const G4Event*);
    virtual void EndOfEventAction(const G4Event*);

    void decay(G4double) const;

    // Secondary electron data
    mutable std::vector< G4double > GammaGeneratingTime;
    mutable G4int GammaNumber;
    mutable G4bool ifDecay;
    mutable G4double timeDecay;
};

#endif