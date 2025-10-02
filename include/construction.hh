#ifndef CONSTRUCTION_HH
#define CONSTRUCTION_HH

#include "G4VUserDetectorConstruction.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "G4FieldManager.hh"

#include "EcalSensitiveDetector.hh"
#include "HcalSensitiveDetector.hh"
#include "DriftTubeSensitiveDetector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	G4bool overlapCheck = false;
	G4bool calibrationMode = false; // when using this only keep ECAL or HCAL active

	// Detector element toggles
	G4bool useBeamPipe = false;
	G4bool useAbsorber = true;
	G4bool useMTD = true;
	G4bool useECAL = true;
	G4bool useHCAL = false;
	G4bool useSolenoid = false;
	G4bool useStainlessSteel = false;
	G4bool useMuonSystem = false; 

	std::vector<G4LogicalVolume*> ecalLVs;
	std::vector<G4LogicalVolume*> mtdLVs;
	std::vector<G4LogicalVolume*> hcalScintillatorLVs;
	std::vector<G4LogicalVolume*> muonGasLVs;
	std::vector<G4LogicalVolume*> hcalBrassLVs;
	std::vector<G4LogicalVolume*> muonTopAluminumLVs;
	std::vector<G4LogicalVolume*> muonBottomAluminumLVs;
	std::vector<G4LogicalVolume*> muonYokeLVs;

	G4LogicalVolume *logicMTD;
	G4LogicalVolume *logicECAL;
    G4LogicalVolume *logicBeamPipe;
    G4LogicalVolume *logicAbsorber;
    G4LogicalVolume *logicSteel;
    G4LogicalVolume *logicSteel2;
    G4LogicalVolume *logicSteel3;
    G4LogicalVolume *logicScintLayer;
    G4LogicalVolume *logicGasLayer;

	virtual void ConstructSDandField();
};

#endif
