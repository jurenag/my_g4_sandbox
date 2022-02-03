#include "MyHit.h"

#include <G4VSensitiveDetector.hh>
#include <G4Step.hh>
#include <G4TouchableHistory.hh>
#include <G4HCofThisEvent.hh>
#include <G4SDManager.hh>

class MySensitiveDetector : public G4VSensitiveDetector{
    public:
        MySensitiveDetector(G4String detector_name, G4String collection_name);
        ~MySensitiveDetector();

        void Initialize(G4HCofThisEvent *) override;
        G4bool ProcessHits(G4Step *, G4TouchableHistory *) override;
        void EndOfEvent (G4HCofThisEvent *) override;

    private:
        G4THitsCollection<MyHit> * hc;
        G4String detName, colName;
};