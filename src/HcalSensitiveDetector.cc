#include "HcalSensitiveDetector.hh"
#include "HCalorimeterHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

HcalSensitiveDetector::HcalSensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{
    collectionName.insert("HCalorimeterColl");
}

void HcalSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new HCalorimeterHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fHCalHCID < 0) {
        fHCalHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fHCalHCID, fHitsCollection);
}

G4bool HcalSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4String detName = GetName();
    if (detName == "HCalorimeter")
    {    
        G4Track *track = step->GetTrack();

        G4StepPoint *preStepPoint = step->GetPreStepPoint();
        G4StepPoint *postStepPoint = step->GetPostStepPoint();

        const G4VTouchable *touchable = preStepPoint->GetTouchable();

        G4int copyNo = touchable->GetCopyNumber();
        auto edep = step->GetTotalEnergyDeposit();
        if (edep == 0.) return true;

        G4ThreeVector pos = preStepPoint->GetPosition();
        auto absTime = preStepPoint->GetGlobalTime();
        auto dist = pos.mag();
        auto hitTime = absTime - (dist/CLHEP::c_light);

        auto ix = -1;

        size_t nEntries = fHitsCollection->entries();
        size_t start = (nEntries > 50) ? nEntries - 50 : 0;
        for (size_t i = nEntries; i-- > start; )
        {
            if (i > 0 && (*fHitsCollection)[i]->GetLayerNo() == copyNo && 
            fabs((*fHitsCollection)[i]->GetTime() - hitTime) <= 0.1*ns)
            {
                (*fHitsCollection)[i]->AddEdep(edep);
                ix = i;
                break;
            }
        }

        if (ix < 0) {
            auto hit = new HCalorimeterHit(copyNo, hitTime);
            hit->AddEdep(edep);
            fHitsCollection->insert(hit);
        }
    }
    return true;
}