#include "MyHit.h"

#include <G4UserEventAction.hh>
#include <G4Event.hh>
#include <G4HCofThisEvent.hh>
#include <G4THitsCollection.hh>


class MyEventAction : public G4UserEventAction{
    public:
        MyEventAction();
        ~MyEventAction();

        void BeginOfEventAction(const G4Event *) override;
        void EndOfEventAction(const G4Event *) override;
};


