#include "PMUserSteppingAction.hh"

#include "PMRunAction.hh"
#include "G4AnalysisManager.hh"
#include "G4MTRunManager.hh"
#include "PMEventAction.hh"

#include "G4VProcess.hh"
#include "G4Track.hh"
#include "G4OpticalPhoton.hh"
#include "G4UnitsTable.hh"
#include "G4Color.hh"
#include "G4VisAttributes.hh"
#include "G4VVisManager.hh"
#include "G4RunManager.hh"


#include "G4EmProcessSubType.hh"

PMUserSteppingAction::PMUserSteppingAction(){
};

PMUserSteppingAction::~PMUserSteppingAction(){
    
};

void PMUserSteppingAction::UserSteppingAction(const G4Step* Step) {
    G4Track* ThisTrack = Step->GetTrack();
    G4StepPoint* endPoint = Step->GetPostStepPoint();
    G4ThreeVector ElectronPosition = endPoint->GetPosition();
    G4double GlobalTime = endPoint->GetGlobalTime();
    auto* proc  = endPoint->GetProcessDefinedStep();

    auto StepNumber = ThisTrack->GetCurrentStepNumber();
    //if (StepNumber > eventAction->MaxNumTrackStep-1){
        //G4cout << "PMUserSteppingAction::UserSteppingAction: StepNumber "<< StepNumber << G4endl;
        //ThisTrack->SetTrackStatus(fStopAndKill);
    //}
    //G4Track* SecondaryTrack = Step->GetSecondaryInCurrentStep();


    //G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    
    //G4cout<<"Found a "<<ThisTrack->GetDefinition()->GetParticleName() << " at " << GlobalTime<<G4endl;  
    //G4cout<< ElectronPosition.x()<<", "<<ElectronPosition.y()<<", "<<ElectronPosition.z()<<G4endl;
    //G4cout<<proc->GetProcessName()<<G4endl; 
    if(proc->GetProcessName() == "Decay"){
        G4cout<<"Moun decay"<< " at " << GlobalTime<<G4endl; 
        auto eventAction = static_cast<const PMEventAction*>(G4RunManager::GetRunManager()->GetUserEventAction());
        eventAction->decay(GlobalTime);
    }
    if(ThisTrack->GetDefinition()->GetParticleName() == "gamma"){
        //G4cout<<"Found a photon"<< " at " << GlobalTime<<G4endl;  
        
        auto eventAction = static_cast<const PMEventAction*>(G4RunManager::GetRunManager()->GetUserEventAction());
        eventAction->AddGamma(GlobalTime);

        ThisTrack->SetTrackStatus(fStopAndKill);
    }
};