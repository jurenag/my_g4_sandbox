#include <G4MaterialPropertiesTable.hh>
#include <G4SystemOfUnits.hh>

namespace MyOpticalMaterialPropertiesTables {

    const G4double energy_min =  2.0 * eV; // 620 nm
    const G4double energy_max = 11.3 * eV; // 110 nm

    G4MaterialPropertiesTable * scintillator();
    G4MaterialPropertiesTable * scintillator_2();
    G4MaterialPropertiesTable * liquid_argon();
    G4MaterialPropertiesTable * water();
}

