#include "PMDetectorConstruction.hh"

PMDetectorConstruction::PMDetectorConstruction()
{
}

PMDetectorConstruction::~PMDetectorConstruction()
{
}

// define geometory
G4VPhysicalVolume *PMDetectorConstruction::Construct()
{
    G4bool checkOverlaps = true; //check boundary overlap 
    
    // define material
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");

    G4double xWorld = 1.*m;
    G4double yWorld = 1.*m;
    G4double zWorld = 1.*m;

    G4Box *solidWorld = new G4Box("soildWorld",0.5 * xWorld,0.5 * yWorld,0.5 * zWorld);//define geometory
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"logicWorld");//apply material
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,checkOverlaps);//create a physics volume


    return physWorld;
}