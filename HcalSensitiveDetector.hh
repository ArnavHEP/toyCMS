#ifndef HCAL_SENSITIVE_DETECTOR_HH
#define HCAL_SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "HCalorimeterHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class HcalSensitiveDetector : public G4VSensitiveDetector
{
public:
    HcalSensitiveDetector(G4String name);
    ~HcalSensitiveDetector() override = default;

    void Initialize(G4HCofThisEvent* hce) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* roHist) override;

private:
    HCalorimeterHitsCollection* fHitsCollection = nullptr;
    G4int fHCalHCID = -1;
};

#endif
