#include "PMSensitiveDec.hh"

PMSensitiveDec::PMSensitiveDec(G4String name): G4VSensitiveDetector(name)
{
    fTotalEnergyDeposited = 0.;
}

PMSensitiveDec::~PMSensitiveDec()
{
}

void PMSensitiveDec::Initialize(G4HCofThisEvent *)
{
    fTotalEnergyDeposited = 0.;
}

void PMSensitiveDec::EndOfEvent(G4HCofThisEvent *)
{
}

G4bool PMSensitiveDec::ProcessHits(G4Step *astep, G4TouchableHistory *)
{
    return true;
}