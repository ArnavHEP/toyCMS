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

        G4ThreeVector mom = track->GetMomentum();
        G4double pT = std::sqrt(mom.x()*mom.x() + mom.y()*mom.y());
        G4double charge = track->GetDefinition()->GetPDGCharge();

        if (edep < 0.06*MeV) return true;

        //G4cout << "ECAl hit: " << track->GetDefinition()->GetParticleName() << track->GetDefinition()->GetPDGEncoding() << G4endl;

        G4ThreeVector pos = preStepPoint->GetPosition();
        auto absTime = preStepPoint->GetGlobalTime();
        auto dist = pos.mag();
        auto hitTime = absTime - (dist/CLHEP::c_light);
        G4int pid = track->GetDefinition()->GetPDGEncoding();

        auto ix = -1;

        size_t nEntries = fHitsCollection->entries();
        size_t start = (nEntries > 50) ? nEntries - 50 : 0;
        for (size_t i = nEntries; i-- > start; )
        {
            if (i > 0 && (*fHitsCollection)[i]->GetCrystalNo() == copyNo &&
            (*fHitsCollection)[i]->GetPID() == pid && 
            fabs((*fHitsCollection)[i]->GetTime() - hitTime) <= 0.1*ns)
            {
                (*fHitsCollection)[i]->AddEdep(edep);
                ix = i;
                break;
            }
        }

        if (ix < 0) {
            auto hit = new EmCalorimeterHit(copyNo, hitTime);
            hit->AddEdep(edep);
            hit->SetPos(pos);
            hit->SetPID(pid);
            fHitsCollection->insert(hit);
        }
    }

    return true;
}

