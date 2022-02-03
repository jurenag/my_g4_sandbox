#include "MySensitiveDetector.h"

MySensitiveDetector::MySensitiveDetector(G4String detector_name, G4String collection_name): 
G4VSensitiveDetector(detector_name)
{
    detName = detector_name;
    colName = collection_name;
    collectionName.insert(colName);//This type of detector only gathers one collection of hits. The constructor of another type of sensitive detector whose goal were constructing different hit collections could take an array of strings, each per collection.
}

MySensitiveDetector::~MySensitiveDetector()
{
}

void MySensitiveDetector::Initialize(G4HCofThisEvent * hcc) //This method is invoked at the beginning of each event.
{
    isFirstStepInVolume = true;
    hc = new G4THitsCollection<MyHit>(detName, colName);
    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(colName);
    hcc->AddHitsCollection(hcID, hc);
}

G4bool MySensitiveDetector::ProcessHits(G4Step * aStep, G4TouchableHistory * th)
{
    G4bool temp = isFirstStepInVolume;
    if(isFirstStepInVolume){
        MyHit * aHit = new MyHit();
        aHit->SetSensorID(aStep->GetTrack()->GetVolume()->GetCopyNo());
        aHit->SetInitHitPos(G4ThreeVector(aStep->GetPreStepPoint()->GetPosition()));
        hc->insert(aHit);
        isFirstStepInVolume = false;
    }
    return temp?true:false;
}

void MySensitiveDetector::EndOfEvent(G4HCofThisEvent * hcc)
{
    auto hcID = G4SDManager::GetSDMpointer()->GetCollectionID(colName);
    hcc->GetHC(hcID)->PrintAllHits();
}