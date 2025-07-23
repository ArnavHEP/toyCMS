#include "detector.hh"

#include "G4HCofThisEvent.hh"
#include "G4TouchableHistory.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4SystemOfUnits.hh"

MySensitiveDetector::MySensitiveDetector(G4String name)
: G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *Step, G4TouchableHistory *)
{
	G4Track *track = Step->GetTrack();
	
	G4StepPoint *preStepPoint = Step->GetPreStepPoint();
	G4StepPoint *postStepPoint = Step->GetPostStepPoint();

	const G4VTouchable *touchable = Step->GetPreStepPoint()->GetTouchable();
		
	G4int copyNo = touchable->GetCopyNumber();

	G4VPhysicalVolume *physVol = touchable->GetVolume();
	G4ThreeVector posDetector = physVol->GetTranslation();

	auto hitTime = preStepPoint->GetGlobalTime();

	auto edep = Step->GetTotalEnergyDeposit();
	if (edep==0.) return true;

	G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

	G4AnalysisManager *analysisManager = G4AnalysisManager::Instance();
	
	G4String detName = GetName();

	if (detName == "ECAL") {
		analysisManager->FillNtupleDColumn(0, 0, posDetector[0]);
		analysisManager->FillNtupleDColumn(0, 1, posDetector[1]);
		analysisManager->FillNtupleDColumn(0, 2, posDetector[2]);
		analysisManager->FillNtupleDColumn(0, 3, hitTime);
		analysisManager->FillNtupleDColumn(0, 4, edep);
		analysisManager->FillNtupleIColumn(0, 5, evt);
		analysisManager->AddNtupleRow(0);
	}
	
	else if (detName == "HCAL") {
		analysisManager->FillNtupleIColumn(1, 0, copyNo);
		analysisManager->FillNtupleDColumn(1, 1, hitTime);
		analysisManager->FillNtupleDColumn(1, 2, edep);
		analysisManager->FillNtupleIColumn(1, 3, evt);
		analysisManager->AddNtupleRow(1);
	}
	else if (detName == "DT") {
		analysisManager->FillNtupleIColumn(2, 0, copyNo);
		analysisManager->FillNtupleDColumn(2, 1, hitTime);
		analysisManager->FillNtupleDColumn(2, 2, edep);
		analysisManager->FillNtupleIColumn(2, 3, evt);
		analysisManager->AddNtupleRow(2);
	}

	return true;
};







