#include "DriftTubeSensitiveDetector.hh"
#include "DriftTubeHit.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

DriftTubeSensitiveDetector::DriftTubeSensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{
    collectionName.insert("DriftTubeColl");
}

void DriftTubeSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new DriftTubeHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fDTHCID < 0) {
        fDTHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fDTHCID, fHitsCollection);
}

G4bool DriftTubeSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4String detName = GetName();
    if (detName == "DriftTube")
    {    
        G4Track* track = step->GetTrack();

        G4StepPoint* preStepPoint = step->GetPreStepPoint();
        G4StepPoint* postStepPoint = step->GetPostStepPoint();

        const G4VTouchable* touchable = preStepPoint->GetTouchable();

        G4int copyNo = touchable->GetCopyNumber();
        auto edep = step->GetTotalEnergyDeposit();
        if (edep == 0.) return true;

        G4ThreeVector pos = preStepPoint->GetPosition();
        auto absTime = preStepPoint->GetGlobalTime();
        auto dist = pos.mag();
        auto hitTime = absTime - (dist/CLHEP::c_light);

        auto ix = -1;
        for (size_t i = 0; i < fHitsCollection->entries(); i++) {
            if ((*fHitsCollection)[i]->GetLayerNo() == copyNo &&
                fabs((*fHitsCollection)[i]->GetTime() - hitTime) <= 0.1*ns) {
                (*fHitsCollection)[i]->AddEdep(edep);
                ix = i;
                break;
            }
        }

        if (ix < 0) {
            auto hit = new DriftTubeHit(copyNo, hitTime);
            hit->AddEdep(edep);
            fHitsCollection->insert(hit);
        }
    }
    return true;
}
