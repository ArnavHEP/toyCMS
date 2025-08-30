#ifndef MTD_SENSITIVE_DETECTOR_HH
#define MTD_SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "MipTimingDetectorHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class MtdSensitiveDetector : public G4VSensitiveDetector
{
public:
    MtdSensitiveDetector(G4String name);
    ~MtdSensitiveDetector() override = default;

    void Initialize(G4HCofThisEvent* hce) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* roHist) override;

private:
    MipTimingDetectorHitsCollection* fHitsCollection = nullptr;
    G4int fMTDHCID = -1;
};

#endif