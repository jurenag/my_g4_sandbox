#include "MyPhysicsList.h"

#include <G4EmStandardPhysics_option4.hh>
#include <G4DecayPhysics.hh>
#include <G4RadioactiveDecayPhysics.hh>
#include <G4StepLimiterPhysics.hh>
#include <G4OpticalPhysics.hh>
#include <G4VModularPhysicsList.hh>

MyPhysicsList::MyPhysicsList():
G4VModularPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics_option4());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4RadioactiveDecayPhysics());
    RegisterPhysics(new G4StepLimiterPhysics());
    RegisterPhysics(new G4OpticalPhysics());
}

MyPhysicsList::~MyPhysicsList()
{
}
//Remember that the deletion of every instantiated class is up to the run manager