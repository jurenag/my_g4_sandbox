#include <G4VUserPrimaryGeneratorAction.hh>
#include <G4SystemOfUnits.hh>
#include <G4Event.hh>

class MyPrimaryGenerator : public G4VUserPrimaryGeneratorAction{
    public:
        double vertex_x, vertex_y, vertex_z, kinetic_energy;
        MyPrimaryGenerator();
        ~MyPrimaryGenerator();
        void GeneratePrimaries(G4Event*) override;
};
