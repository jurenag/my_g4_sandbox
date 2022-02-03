#include <G4VUserDetectorConstruction.hh>
#include <G4VPhysicalVolume.hh>
#include <G4SystemOfUnits.hh>

class MyDetectorConstruction : public G4VUserDetectorConstruction{
    public:
    //The run manager needs to access just the Construct() method
        MyDetectorConstruction();
        ~MyDetectorConstruction();
        G4VPhysicalVolume * Construct();
        void set_wlsbar_dimensions(double wlsbar_diameter, double wlsbar_length);
    private:
        double world_diameter=1.*m, wlsbar_diameter = 2.*cm, wlsbar_length=10.*cm, sd_length=0.5*cm; 
        void ConstructWLSBar(G4LogicalVolume * world_lv);
        void ConstructSensitiveDetectors(G4LogicalVolume * world_lv);
};

