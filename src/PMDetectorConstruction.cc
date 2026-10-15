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

    // ---------------------------
        // PVT 基材：近似化学式 C9H10
    auto* H = new G4Element(
        "Hydrogen", "H", 1., 1.008*g/mole);

    auto* C = new G4Element(
        "Carbon", "C", 6., 12.011*g/mole);

    auto* pvt = new G4Material(
        "TeachSpinPVT",
        1.032*g/cm3,
        2
    );

    pvt->AddElement(C, 9);
    pvt->AddElement(H, 10);

    // 光学属性表
    auto* mpt = new G4MaterialPropertiesTable();

    // 光子能量：约对应 400--500 nm 的发射范围
    G4double photonEnergy[] = {
        2.48*eV,
        2.65*eV,
        2.93*eV,
        3.10*eV,
        3.26*eV
    };

    // 相对发射强度：仅用于初步调试
    G4double emission[] = {
        0.05, 0.40, 1.00, 0.55, 0.10
    };

    G4double rindex[] = {
        1.58, 1.58, 1.58, 1.58, 1.58
    };

    // 临时吸收长度，不是厂商实测值
    G4double absLength[] = {
        100.*cm, 100.*cm, 100.*cm,
        100.*cm, 100.*cm
    };

    mpt->AddProperty(
        "RINDEX", photonEnergy, rindex, 5);

    mpt->AddProperty(
        "ABSLENGTH", photonEnergy, absLength, 5);

    mpt->AddProperty(
        "SCINTILLATIONCOMPONENT1",
        photonEnergy, emission, 5);

    // 初始近似值：10000 photons/MeV
    mpt->AddConstProperty(
        "SCINTILLATIONYIELD", 10000./MeV);

    // TeachSpin 手册参数的近似初值
    mpt->AddConstProperty(
        "SCINTILLATIONTIMECONSTANT1", 2.4*ns);

    mpt->AddConstProperty(
        "SCINTILLATIONRISETIME1", 0.9*ns);

    mpt->AddConstProperty(
        "RESOLUTIONSCALE", 1.0);

    pvt->SetMaterialPropertiesTable(mpt);
    // ---------------------------

    G4bool checkOverlaps = true; //check boundary overlap 
    
    // define material
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *al = nist->FindOrBuildMaterial("G4_Al");
    G4Material *detMat = pvt;


    G4double rWorld = 7.5*cm;
    G4double hWorld = 12.5*cm / 2;
    G4double rShell = 5.*cm;

    G4Tubs *solidWorld = new G4Tubs("soildWorld",0,rWorld+rShell,hWorld,0*deg,360*deg);//define geometory
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld,worldMat,"logicWorld");//apply material
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicWorld,"physWorld",0,false,0,checkOverlaps);//create a physics volume
   
    G4Tubs *solidDet = new G4Tubs("Source",0,rWorld,hWorld,0*deg,360*deg);
    logicalDetector = new G4LogicalVolume(solidDet,detMat,"logicaldetector");
    G4VPhysicalVolume *physDec = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalDetector,"physdetector",logicWorld,false,checkOverlaps);

    G4Tubs *shellDet = new G4Tubs("Source",rWorld,rWorld+rShell,hWorld,0*deg,360*deg);
    G4LogicalVolume *logicalShell = new G4LogicalVolume(solidDet,al,"logicalShell");
    G4VPhysicalVolume *shellDec = new G4PVPlacement(0,G4ThreeVector(0.,0.,0.),logicalShell,"physShell",logicWorld,false,checkOverlaps);

    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0,1.0,0,0.3));
    detVisAtt->SetForceSolid(true);
    logicalDetector->SetVisAttributes(detVisAtt);


    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDec *sensDet = new PMSensitiveDec("SD");
    logicalDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}