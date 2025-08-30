#include "EcalSensitiveDetector.hh"
#include "EmCalorimeterHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

EcalSensitiveDetector::EcalSensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{
    collectionName.insert("EmCalorimeterColl");
}

void EcalSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new EmCalorimeterHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fECalHCID < 0) {
        fECalHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fECalHCID, fHitsCollection);
}

G4bool EcalSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4String detName = GetName();
    if (detName == "EmCalorimeter")
    { 
        G4Track *track = step->GetTrack();
        
        G4StepPoint *preStepPoint = step->GetPreStepPoint();
        G4StepPoint *postStepPoint = step->GetPostStepPoint();

        const G4VTouchable *touchable = step->GetPreStepPoint()->GetTouchable();
            
        G4int copyNo = touchable->GetCopyNumber();
        auto edep = step->GetTotalEnergyDeposit();
        if (edep==0.) return true;

        G4ThreeVector pos = preStepPoint->GetPosition();
        auto absTime = preStepPoint->GetGlobalTime();
        auto dist = pos.mag();
        auto hitTime = absTime - (dist/CLHEP::c_light);

        auto ix = -1;
        for (size_t i=0; i<fHitsCollection->entries(); i++) {
            if ((*fHitsCollection)[i]->GetCrystalNo() == copyNo &&
                fabs((*fHitsCollection)[i]->GetTime() - hitTime) <= 0.1*ns) {
                (*fHitsCollection)[i]->AddEdep(edep);
                ix = i;
                break;
            }
        }

        if (ix < 0) {
            auto hit = new EmCalorimeterHit(copyNo, hitTime);
            hit->AddEdep(edep);
            hit->SetPos(pos);
            fHitsCollection->insert(hit);
        }
    }

    return true;
}

