#include <iostream>

#include "G4RunManager.hh"
#include "G4MTRunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"

#include "PMPhysicslist.hh"
#include "PMDetectorConstruction.hh"
#include "PMActionInit.hh"
#include "FTFP_BERT.hh"

int main(int argc, char** argv)
{
    //G4UIExecutive *ui = new G4UIExecutive(argc,argv);
    G4UIExecutive *ui;

    #ifdef G4MULTITHREADED 
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4MTRunManager *runManager = new G4RunManager;
    #endif

    // Physics List
    runManager->SetUserInitialization(new PMPhysicsList());
    //runManager->SetUserInitialization(new FTFP_BERT());

    // Detector construction
    runManager->SetUserInitialization(new PMDetectorConstruction());

    // Action Initialization
    runManager->SetUserInitialization(new PMActionInit());

    if (argc == 1){
        ui = new G4UIExecutive(argc,argv);
    }

    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();

    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    if(ui){
        UImanager->ApplyCommand("/control/execute vis.mac");
        ui->SessionStart();
    }
    else{
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    
    
    return 0;
}