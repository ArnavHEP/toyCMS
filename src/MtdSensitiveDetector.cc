#include "MtdSensitiveDetector.hh"
#include "MipTimingDetectorHit.hh"
#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"

MtdSensitiveDetector::MtdSensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{
    collectionName.insert("MipTimingDetectorColl");
}

void MtdSensitiveDetector::Initialize(G4HCofThisEvent* hce)
{
    fHitsCollection = new MipTimingDetectorHitsCollection(SensitiveDetectorName, collectionName[0]);
    if (fMTDHCID < 0) {
        fMTDHCID = G4SDManager::GetSDMpointer()->GetCollectionID(fHitsCollection);
    }
    hce->AddHitsCollection(fMTDHCID, fHitsCollection);
}

G4bool MtdSensitiveDetector::ProcessHits(G4Step* step, G4TouchableHistory*)
{
    G4String detName = GetName();
    if (detName == "MipTimingDetector")
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

        if (pT < 700*MeV || charge == 0.0) return true;

        //G4cout << "MTD hit: " << track->GetDefinition()->GetParticleName() << G4endl;

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
            auto hit = new MipTimingDetectorHit(copyNo, hitTime);
            hit->SetPos(pos);
            hit->AddEdep(edep);
            hit->SetPID(pid);
            fHitsCollection->insert(hit);
        }
    }

    return true;
}