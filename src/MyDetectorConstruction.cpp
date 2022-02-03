#include "MyDetectorConstruction.h"
#include "MyMaterials.h"
#include "MySensitiveDetector.h"
#include "MyOpticalMaterialPropertiesTables.h"

#include <G4PhysicalConstants.hh>
#include <G4SystemOfUnits.hh>
#include <G4LogicalVolume.hh>
#include <G4CSGSolid.hh>
#include <G4Sphere.hh>
#include <G4Tubs.hh>
#include <G4PVPlacement.hh>
#include <G4RotationMatrix.hh>
#include <G4ThreeVector.hh>
#include <G4SDManager.hh>
#include <G4VisAttributes.hh>

MyDetectorConstruction::MyDetectorConstruction(): 
G4VUserDetectorConstruction()
{
}

MyDetectorConstruction::~MyDetectorConstruction()
{
}

G4VPhysicalVolume * MyDetectorConstruction::Construct()
{
    const G4String pWorldName  = "world";
    G4CSGSolid * world_sv = new G4Sphere(pWorldName, 0., world_diameter, 0., 360.*degree, 0., 180.*degree);

    G4Material * lAr =  MyMaterials::liquid_argon();
    lAr->SetMaterialPropertiesTable(MyOpticalMaterialPropertiesTables::liquid_argon());

    G4LogicalVolume * world_lv = new G4LogicalVolume(world_sv, lAr, pWorldName);
    world_lv->SetVisAttributes(G4VisAttributes::Invisible);
    ConstructWLSBar(world_lv);
    ConstructSensitiveDetectors(world_lv);
    return new G4PVPlacement(new G4RotationMatrix(), G4ThreeVector(), world_lv, pWorldName, nullptr, false, 0);
}

void MyDetectorConstruction::ConstructWLSBar(G4LogicalVolume * world_lv){
    const G4String pWLSBarName = "WLSBar";
    G4Tubs * wls_sv = new G4Tubs(pWLSBarName, 0., wlsbar_diameter/2., wlsbar_length/2., 0., 360.*degree);

    G4Material * scintillator =  MyMaterials::scintillator();
    scintillator->SetMaterialPropertiesTable(MyOpticalMaterialPropertiesTables::scintillator());

    G4LogicalVolume * wls_lv = new G4LogicalVolume(wls_sv, scintillator, pWLSBarName);
    new G4PVPlacement(new G4RotationMatrix(), G4ThreeVector(), wls_lv, pWLSBarName, world_lv, false, 0);
}

void MyDetectorConstruction::ConstructSensitiveDetectors(G4LogicalVolume * world_lv){
    const G4String pSensitiveDetName = "SensitiveDetector";
    G4Tubs * detector_sv = new G4Tubs(pSensitiveDetName, 0., wlsbar_diameter/2., sd_length/2., 0., 360.*degree);
    MySensitiveDetector * sensitive_detector = new MySensitiveDetector("my_det", "my_coll");
    G4SDManager::GetSDMpointer()->AddNewDetector(sensitive_detector); 

    G4Material * scintillator =  MyMaterials::scintillator();
    scintillator->SetMaterialPropertiesTable(MyOpticalMaterialPropertiesTables::scintillator());

    G4LogicalVolume * detector_lv = new G4LogicalVolume(detector_sv, scintillator, pSensitiveDetName, 0, sensitive_detector);
    new G4PVPlacement(new G4RotationMatrix(), G4ThreeVector(0.,0.,(wlsbar_length+sd_length+1.*cm)/2.), detector_lv, pSensitiveDetName, world_lv,  false, 0);
    new G4PVPlacement(new G4RotationMatrix(), G4ThreeVector(0.,0.,-1.*(wlsbar_length+sd_length+1.*cm)/2.), detector_lv, pSensitiveDetName, world_lv,  false, 1);   

    //G4RotationMatrix* rot = new G4RotationMatrix();
    //rot->rotateX(0*deg);
}