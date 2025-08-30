#ifndef ECAL_SENSITIVE_DETECTOR_HH
#define ECAL_SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "EmCalorimeterHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class EcalSensitiveDetector : public G4VSensitiveDetector
{
public:
    EcalSensitiveDetector(G4String name);
    ~EcalSensitiveDetector() override = default;

    void Initialize(G4HCofThisEvent* hce) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* roHist) override;

private:
    EmCalorimeterHitsCollection* fHitsCollection = nullptr;
    G4int fECalHCID = -1;
};

#endif