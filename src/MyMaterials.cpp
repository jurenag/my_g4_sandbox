#include "MyMaterials.h"

#include <G4Element.hh>
#include <G4SystemOfUnits.hh>

G4Material * MyMaterials::scintillator(){
    double a, density;
    a = 1.01*gram/mole;
    G4Element * elH  = new G4Element("Hydrogen", "H", 1., a);
    a = 12.01*gram/mole;
    G4Element * elC  = new G4Element("Carbon", "C", 6., a);
    density = 1.032*g/cm3;
    G4Material  * scintillator = new G4Material("Scintillator", density, 2);
    scintillator->AddElement(elC, 9);
    scintillator->AddElement(elH, 10);
    return scintillator;
}

G4Material * MyMaterials::liquid_argon(){
    double a, density;
    density = 1.390*g/cm3;
    a = 39.95*g/mole;
    G4Material * liquid_argon = new G4Material("LiquidArgon", 18., a, density);
    return liquid_argon;
}

G4Material * MyMaterials::water(){
    double a, density;
    a = 1.01*g/mole;
    G4Element * elH  = new G4Element("Hydrogen", "H", 1., a);
    a = 16.00*g/mole;
    G4Element * elO  = new G4Element("Oxygen", "O", 8., a);
    density = 1.000*g/cm3;
    G4Material* water = new G4Material("Water", density, 2);
    water->AddElement(elH, 2);
    water->AddElement(elO, 1);
    return water;
}
