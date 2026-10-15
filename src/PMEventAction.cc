#include "PMEventAction.hh"
#include "PMRunAction.hh"
#include "G4RunManager.hh"
#include "G4Event.hh"
#include "G4Polyline.hh"
#include "G4VisAttributes.hh"
#include "G4Color.hh"
#include "G4VVisManager.hh"
#include "G4EventManager.hh"
#include "G4UImanager.hh"
#include "G4AnalysisManager.hh"
#include "G4MTRunManager.hh"

#include <iostream>
#include <fstream>

PMEventAction::PMEventAction()
{ 
    
} 


PMEventAction::~PMEventAction()
{
}

void PMEventAction::decay(G4double t) const{
    timeDecay = t;
    ifDecay  = true;
}

void PMEventAction::AddGamma(G4double t) const{
    GammaNumber++;
    GammaGeneratingTime.push_back(t);
}


void PMEventAction::BeginOfEventAction(const G4Event*)
{   
    timeDecay = 0.;
    ifDecay = false;
    GammaNumber = 0;
    GammaGeneratingTime.clear();
}


void PMEventAction::EndOfEventAction(const G4Event*)
{   
    G4double dt; 

    if (ifDecay && GammaNumber>=2){
        G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
        analysisManager->FillH1(1,timeDecay);
        std::sort(GammaGeneratingTime.begin(), GammaGeneratingTime.end());

        dt = 0;
        for(int i =0; i< GammaGeneratingTime.size()-1;i++){
            G4cout<<GammaGeneratingTime[i+1] - GammaGeneratingTime[i]<<G4endl;
            if(dt < GammaGeneratingTime[i+1] - GammaGeneratingTime[i]){dt = GammaGeneratingTime[i+1] - GammaGeneratingTime[i];}
        }

        G4cout<<"Found "<<GammaNumber<<" Gammas"<<G4endl;
        
        analysisManager->FillH1(0,dt);
    }


}