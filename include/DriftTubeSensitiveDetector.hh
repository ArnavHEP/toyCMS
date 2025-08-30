#ifndef DRIFT_TUBE_SENSITIVE_DETECTOR_HH
#define DRIFT_TUBE_SENSITIVE_DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "DriftTubeHit.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class DriftTubeSensitiveDetector : public G4VSensitiveDetector
{
public:
    DriftTubeSensitiveDetector(G4String name);
    ~DriftTubeSensitiveDetector() override = default;

    void Initialize(G4HCofThisEvent* hce) override;
    G4bool ProcessHits(G4Step* step, G4TouchableHistory* roHist) override;

private:
    DriftTubeHitsCollection* fHitsCollection = nullptr;
    G4int fDTHCID = -1;
};

#endif
