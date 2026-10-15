#include "PMRunAction.hh"

PMRunAction::PMRunAction(){
    G4AnalysisManager *analymanager = G4AnalysisManager::Instance();

    analymanager->CreateH1("PhotonDt","Time difference between 2 photon",100,0.3*us,8. * us);
    analymanager->CreateH1("Moun decay","Time Time moun decay",100,0.3*us,8. * us);

}

PMRunAction::~PMRunAction(){

}

void PMRunAction::BeginOfRunAction(const G4Run *run){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    G4int runId = run->GetRunID();

    std::stringstream strRunID;
    strRunID << runId;

    analysisManager->OpenFile("output.root");
}

void PMRunAction::EndOfRunAction(const G4Run *run){
    G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();

    analysisManager->Write();

    analysisManager->CloseFile();

    G4int runID = run->GetRunID();
    G4cout << "Finish run " << runID <<G4endl;
}