#ifndef DETECTOR_HH
#define DETECTOR_HH

#include "G4VSensitiveDetector.hh"
#include "G4AnalysisManager.hh"
#include "G4RunManager.hh"  
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;

class MySensitiveDetector : public G4VSensitiveDetector
{
public:
	MySensitiveDetector(G4String name);
	~MySensitiveDetector();

	virtual G4bool ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist) override;
	int prevEvent=-1;
};

#endif
