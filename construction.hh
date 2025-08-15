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

#include "detector.hh"

class MyDetectorConstruction : public G4VUserDetectorConstruction
{
public:
	MyDetectorConstruction();
	~MyDetectorConstruction();
	
	virtual G4VPhysicalVolume *Construct();
	
private:
	G4bool overlapCheck = false;
	G4bool calibrationMode = false; // use with only ECAL or HCAL present

	// Detector element toggles
	G4bool useBeamPipe = true;
	G4bool useAbsorber = true;
	G4bool useECAL = true;
	G4bool useHCAL = true;
	G4bool useSolenoid = false;
	G4bool useStainlessSteel = false;
	G4bool useMuonSystem = false; 

	std::vector<G4LogicalVolume*> ecalLVs;
	std::vector<G4LogicalVolume*> hcalScintillatorLVs;
	std::vector<G4LogicalVolume*> muonGasLVs;
	std::vector<G4LogicalVolume*> hcalBrassLVs;
	std::vector<G4LogicalVolume*> muonTopAluminumLVs;
	std::vector<G4LogicalVolume*> muonBottomAluminumLVs;
	std::vector<G4LogicalVolume*> muonYokeLVs;

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
