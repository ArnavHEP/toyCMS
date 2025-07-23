
#include "construction.hh"
#include "detector.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{	
    //delete fSolenoidField;
    //delete fReturnField;
    //delete fSolenoidFieldMgr;
    //delete fReturnFieldMgr;
}

G4VPhysicalVolume *MyDetectorConstruction::Construct()
{	
	// Elements

	G4Element *elN  = new G4Element("Nitrogen", "N", 7, 14.01*g/mole);
	G4Element *elO  = new G4Element("Oxygen",   "O", 8, 15.999*g/mole);
	G4Element *elAr = new G4Element("Argon",    "Ar", 18, 39.948*g/mole);
	G4Element *elFe = new G4Element("Iron",     "Fe", 26, 55.845*g/mole);
	G4Element *elPb = new G4Element("Lead",     "Pb", 82, 207.2*g/mole);
	G4Element *elW  = new G4Element("Tungsten", "W", 74, 183.84*g/mole);
	G4Element *elC  = new G4Element("Carbon",   "C", 6, 12.011*g/mole);
	G4Element *elH  = new G4Element("Hydrogen", "H", 1, 1.008*g/mole);
	G4Element *elTi = new G4Element("Titanium", "Ti", 22, 47.867*g/mole);
	G4Element *elNb = new G4Element("Niobium",  "Nb", 41, 92.906*g/mole);
	G4Element *elCu = new G4Element("Copper",   "Cu", 29, 63.546*g/mole);
	G4Element *elZn = new G4Element("Zinc",     "Zn", 30, 65.38*g/mole);
	G4Element *elAl = new G4Element("Aluminum", "Al", 13, 26.982*g/mole);
	G4Element *elCr = new G4Element("Chromium", "Cr", 24, 51.996*g/mole);
	G4Element *elNi = new G4Element("Nickel",   "Ni", 28, 58.693*g/mole);

	//**********************************************************************************

	// Materials

	// Iron
	G4Material *Fe = new G4Material("Fe", 7.87*g/cm3, 1);
	Fe->AddElement(elFe, 1);

	// Lead
	G4Material *Lead = new G4Material("Lead", 11.34*g/cm3, 1);
	Lead->AddElement(elPb, 1);

	// Air (N2, O2, Ar)
	G4Material *Air = new G4Material("Air", 1.214*mg/cm3, 3);
	Air->AddElement(elN, 75*perCent);
	Air->AddElement(elO, 24*perCent);
	Air->AddElement(elAr, 1*perCent);

	// Lead Tungstate (PbWO4)
	G4Material *PbWO4 = new G4Material("PbWO4", 8.30*g/cm3, 3);
	PbWO4->AddElement(elPb, 1);
	PbWO4->AddElement(elW, 1);
	PbWO4->AddElement(elO, 4);

	// Brass (70% Cu, 30% Zn)
	G4Material *Brass = new G4Material("Brass", 8.4*g/cm3, 2);
	Brass->AddElement(elCu, 70*perCent);
	Brass->AddElement(elZn, 30*perCent);

	// NbTi
	G4Material *NbTi = new G4Material("NbTi", 6.5*g/cm3, 2);
	NbTi->AddElement(elNb, 1);
	NbTi->AddElement(elTi, 1);

	// Aluminum
	G4Material *Aluminum = new G4Material("Aluminum", 2.70*g/cm3, 1);
	Aluminum->AddElement(elAl, 1);

	// Argon Gas
	G4Material *ArgonGas = new G4Material("ArgonGas", 1.662*mg/cm3, 1, kStateGas, 293.15*kelvin, 1*atmosphere);
	ArgonGas->AddElement(elAr, 1);

	// Carbon Dioxide Gas (CO₂)
	G4Material *CO2Gas = new G4Material("CO2Gas", 1.842*mg/cm3, 2, kStateGas, 293.15*kelvin, 1*atmosphere);
	CO2Gas->AddElement(elC, 1);
	CO2Gas->AddElement(elO, 2);

	// Scintillator Tile ((C8H8)n)
	G4Material *Scintillator = new G4Material("Scintillator", 1.032*g/cm3, 2);
	Scintillator->AddElement(elC, 8);
	Scintillator->AddElement(elH, 8);

	// Stainless Steel (approx: Fe 70%, Cr 18%, Ni 10%, C 2%)
	G4Material *StainlessSteel = new G4Material("StainlessSteel", 8.0*g/cm3, 4);
	StainlessSteel->AddElement(elFe, 70*perCent);
	StainlessSteel->AddElement(elCr, 18*perCent);
	StainlessSteel->AddElement(elNi, 10*perCent);
	StainlessSteel->AddElement(elC, 2*perCent);

	// Argon-CO2 mixture (85% Ar, 15% CO2)
	G4Material* ArCO2 = new G4Material("ArCO2", 1.7*mg/cm3, 2, kStateGas, 293.15*kelvin, 1*atmosphere);
	ArCO2->AddMaterial(ArgonGas, 85*perCent);
	ArCO2->AddMaterial(CO2Gas, 15*perCent);

	// Vacuum
	G4NistManager* nist = G4NistManager::Instance();
	G4Material* Vacuum = nist->FindOrBuildMaterial("G4_Galactic");
	
	//**********************************************************************************

	//making world 
	G4Box *solidWorld = new G4Box("solidWorld", 15.0*m, 15.0*m, 15.0*m);
	G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, Vacuum, "logicWorld");
	G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physWorld", 0, false, 0, overlapCheck);
	//parameters (rotation, location, logic volume, name, mother volume, boolean operation, copy number, times created, checks for overlap)

	//**********************************************************************************
	/*
	//Magnetic field inside solenoid
	G4Tubs* solenoidFieldSolid = new G4Tubs("solenoidFieldTubs", 0.*m, 2.95*m, 6.6*m, 0.*deg, 360.*deg);
	fSolenoidFieldLogical = new G4LogicalVolume(solenoidFieldSolid, Vacuum, "solenoidFieldLogical");
	new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), fSolenoidFieldLogical, "solenoidFieldPhysical", logicWorld, false, 0, overlapCheck);
	fSolenoidFieldLogical->SetVisAttributes(G4VisAttributes::GetInvisible());

	//Magnetic field outside solenoid
	G4Tubs* returnFieldSolid = new G4Tubs("returnFieldTubs", 3.80*m, 7.31*m, 6.6*m, 0.*deg, 360.*deg);
	fReturnFieldLogical = new G4LogicalVolume(returnFieldSolid, Vacuum, "returnFieldLogical");
	new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), fReturnFieldLogical, "returnFieldPhysical", logicWorld, false, 0, overlapCheck);
	fReturnFieldLogical->SetVisAttributes(G4VisAttributes::GetInvisible());
	*/
	//**********************************************************************************

	//Beam Pipe
	G4double pipeInnerRadius = 2.75*cm;
	G4double pipeOuterRadius = 3.0*cm;
	G4double pipeHalfLength  = 200.0*cm;

	G4Tubs* solidBeamPipe = new G4Tubs("solidBeamPipe", pipeInnerRadius, pipeOuterRadius, pipeHalfLength, 0.*deg, 360.*deg);
	G4LogicalVolume* logicBeamPipe = new G4LogicalVolume(solidBeamPipe, Aluminum, "logicBeamPipe");
	G4VPhysicalVolume* physBeamPipe = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicBeamPipe, "physBeamPipe", logicWorld, false, 0, overlapCheck);

	G4VisAttributes* pipeVis = new G4VisAttributes(G4Colour(1.,0.,0.)); // red
	pipeVis->SetForceSolid(true);
	logicBeamPipe->SetVisAttributes(pipeVis);
	
	//**********************************************************************************

	//Absorber
	G4double absorberInnerRadius = 1.00*m;
	G4double absorberOuterRadius = 1.13*m; //max allowed : 1.13
	G4double absorberHalfLength  = 2.85*m;

	G4Tubs* solidAbsorber = new G4Tubs("solidAbsorber", absorberInnerRadius, absorberOuterRadius, absorberHalfLength, 0.*deg, 360.*deg);
	G4LogicalVolume* logicAbsorber = new G4LogicalVolume(solidAbsorber, Lead, "logicAbsorber");
	G4VPhysicalVolume* physAbsorber = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicAbsorber, "physAbsorber", logicWorld, false, 0, overlapCheck);

	G4VisAttributes* absorberVis = new G4VisAttributes(G4Colour(0.8,0.8,0.8,0.85)); // light gray
	absorberVis->SetForceSolid(true);
	logicAbsorber->SetVisAttributes(absorberVis);

	//**********************************************************************************

	//ECAL
	G4double ecalInnerRadius = 1.29*m;
	G4double ecalOuterRadius = 1.77*m;
	G4double ecalHalfLength  = 3.6*m;
	G4double ecalCrystalHalfSizeX = 0.23*m;
	G4double ecalCrystalHalfSizeY = 0.045*m; 
	G4double ecalCrystalHalfSizeZ  = 0.045*m;
	G4double nEcalRows = 80;
	G4double nEcalRings = 90;

	G4Box* solidECAL = new G4Box("solidECAL", ecalCrystalHalfSizeX, ecalCrystalHalfSizeY, ecalCrystalHalfSizeZ);
	logicECAL = new G4LogicalVolume(solidECAL, PbWO4, "logicECAL");

	for(G4int i = 0; i < nEcalRows; i++) 
	{
		for(G4int j = 0; j < nEcalRings; j++) 
		{
			G4Rotate3D rotZEcal(j*(360/nEcalRings)*deg, G4ThreeVector(0,0,1));
			G4Translate3D transXEcal(G4ThreeVector(ecalCrystalHalfSizeY/tan((360/nEcalRings)/2*deg)*mm + ecalCrystalHalfSizeX*mm, 0*mm, -ecalHalfLength+(2*i*ecalCrystalHalfSizeZ)*mm));
			G4Transform3D transformEcal = (rotZEcal)*(transXEcal);

			G4VPhysicalVolume* physECAL = new G4PVPlacement(transformEcal, logicECAL, "physECAL", logicWorld, false, (i*100)+j, overlapCheck);
			
			G4VisAttributes* ecalVis = new G4VisAttributes(G4Colour(0.4,1.0,0.4)); // light green
			ecalVis->SetForceSolid(true);
			logicECAL->SetVisAttributes(ecalVis);
		}
	}

	//**********************************************************************************

	//Stainless Steel layer between ECAL and HCAL
	G4double steelInnerRadius = 1.77*m;  
	G4double steelOuterRadius = 1.95*m;
	G4double steelHalfLength  = 4.4*m;

	G4Tubs* solidSteel = new G4Tubs("solidSteel", steelInnerRadius, steelOuterRadius, steelHalfLength, 0.*deg, 360.*deg);
	G4LogicalVolume* logicSteel = new G4LogicalVolume(solidSteel, StainlessSteel, "logicSteel");
	G4VPhysicalVolume* physSteel = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicSteel, "physSteel", logicWorld, false, 0, overlapCheck);

	G4VisAttributes* steelVis = new G4VisAttributes(G4Colour(0.7,0.7,0.7,0.7)); // metallic gray
	steelVis->SetForceSolid(true);
	logicSteel->SetVisAttributes(steelVis);

	//**********************************************************************************

	//HCAL
	G4double hcalInnerRadius = 1.95*m;
	G4double hcalOuterRadius = 2.86*m;  // 1.95 + 17*(0.05 + 0.0037) = 2.8629m
	G4double hcalHalfLength  = 4.4*m;

	G4double brassThickness = 5.0*cm;
	G4double scintillatorThickness = 3.7*mm;
	G4double layerThickness = brassThickness + scintillatorThickness;
	G4int hcalLayers = 17;

	for(G4int i = 0; i < hcalLayers; i++) 
	{
		G4double layerInnerRadius = hcalInnerRadius + i * layerThickness;
		G4double brassOuterRadius = layerInnerRadius + brassThickness;
		G4double scintOuterRadius = brassOuterRadius + scintillatorThickness;

		G4Tubs* solidBrassLayer = new G4Tubs("solidBrassLayer", layerInnerRadius, brassOuterRadius, hcalHalfLength, 0.*deg, 360.*deg);
		G4LogicalVolume* logicBrassLayer = new G4LogicalVolume(solidBrassLayer, Brass, "logicBrassLayer");
		hcalBrassLVs.push_back(logicBrassLayer);
		new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicBrassLayer, "physBrassLayer", logicWorld, false, i+1, overlapCheck);

		G4Tubs* solidScintLayer = new G4Tubs("solidScintLayer", brassOuterRadius, scintOuterRadius, hcalHalfLength, 0.*deg, 360.*deg);
		logicScintLayer = new G4LogicalVolume(solidScintLayer, Scintillator, "logicScintLayer");
		hcalScintillatorLVs.push_back(logicScintLayer);
		new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicScintLayer, "physScintLayer", logicWorld, false, i+1, overlapCheck);

		G4VisAttributes* brassVis = new G4VisAttributes(G4Colour(0.8,0.6,0.2,0.8)); // brass color
		brassVis->SetForceSolid(true);
		logicBrassLayer->SetVisAttributes(brassVis);

		G4VisAttributes* scintVis = new G4VisAttributes(G4Colour(0.2,0.8,1.0,0.8)); // light blue
		scintVis->SetForceSolid(true);
		logicScintLayer->SetVisAttributes(scintVis);
	}

	//**********************************************************************************

	//Stainless Steel layer between HCAL and Solenoid
	G4double steelInnerRadius2 = 2.86*m;  
	G4double steelOuterRadius2 = 2.95*m;  
	G4double steelHalfLength2  = 6.6*m; 

	G4Tubs* solidSteel2 = new G4Tubs("solidSteel2", steelInnerRadius2, steelOuterRadius2, steelHalfLength2, 0.*deg, 360.*deg);
	G4LogicalVolume* logicSteel2 = new G4LogicalVolume(solidSteel2, StainlessSteel, "logicSteel2");
	G4VPhysicalVolume* physSteel2 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicSteel2, "physSteel2", logicWorld, false, 0, overlapCheck);

	G4VisAttributes* steelVis2 = new G4VisAttributes(G4Colour(0.7,0.7,0.7,0.7)); // metallic gray
	steelVis2->SetForceSolid(true);
	logicSteel2->SetVisAttributes(steelVis2);

	//**********************************************************************************

	//Solenoid
    G4double solenoidInnerRadius = 2.95*m;
    G4double solenoidOuterRadius = 3.80*m;
    G4double solenoidHalfLength  = 6.6*m;

    G4Tubs* solidSolenoid = new G4Tubs("solidSolenoid", solenoidInnerRadius, solenoidOuterRadius, solenoidHalfLength, 0.*deg, 360.*deg);
    G4LogicalVolume* logicSolenoid = new G4LogicalVolume(solidSolenoid, NbTi, "logicSolenoid");
    G4VPhysicalVolume* physSolenoid = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicSolenoid, "physSolenoid", logicWorld, false, 0, overlapCheck);

	//**********************************************************************************

	//Stainless Steel layer after Solenoid
    G4double steelInnerRadius3 = 3.80*m;
    G4double steelOuterRadius3 = 3.84*m;
    G4double steelHalfLength3  = 6.6*m; 

    G4Tubs* solidSteel3 = new G4Tubs("solidSteel3", steelInnerRadius3, steelOuterRadius3, steelHalfLength3, 0.*deg, 360.*deg);
    G4LogicalVolume* logicSteel3 = new G4LogicalVolume(solidSteel3, StainlessSteel, "logicSteel3");
    G4VPhysicalVolume* physSteel3 = new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicSteel3, "physSteel3", logicWorld, false, 0, overlapCheck);

    G4VisAttributes* steelVis3 = new G4VisAttributes(G4Colour(0.7,0.7,0.7,0.7)); // metallic gray
    steelVis3->SetForceSolid(true);
    logicSteel3->SetVisAttributes(steelVis3);

	//**********************************************************************************

	//single HCAL scintillator tile after solenoid
	G4Tubs* solidScintLayer = new G4Tubs("solidScintLayer", steelOuterRadius3, steelOuterRadius3 + 1*cm, steelHalfLength3, 0.*deg, 360.*deg);
	logicScintLayer = new G4LogicalVolume(solidScintLayer, Scintillator, "logicScintLayer");
	hcalScintillatorLVs.push_back(logicScintLayer);
	new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicScintLayer, "physScintLayer", logicWorld, false, 18, overlapCheck);

	G4VisAttributes* scintVis = new G4VisAttributes(G4Colour(0.2,0.8,1.0,0.5)); // light blue
	scintVis->SetForceSolid(true);
	logicScintLayer->SetVisAttributes(scintVis);

	//**********************************************************************************

	//muon system
	G4double aluminumThickness = 1*mm;
	G4double gasThickness = 11*mm;
	G4double dtThickness = (2*aluminumThickness)+gasThickness;
	G4double dtLayers = 30;
	G4double nMuonSystem = 4;
	G4double ironYoke[4] = {0.0, 0.4, 0.61, 0.89}; //*m
	G4double ironYokeSum[4] = {0.0, 0.4, 1.01, 1.90}; //*m
	G4double muonSystemInnerRadius = 3.85*m;
	G4double muonSystemHalfLength  = 6.6*m;

	for(G4int i = 0; i < nMuonSystem; i++)
	{
		for(G4int j = 0; j < dtLayers; j++)
		{
			G4double layerInnerRadius = muonSystemInnerRadius + j*dtThickness + ironYokeSum[i]*m + i*(dtLayers*dtThickness);
			G4double bottomAluminumOuterRadius = layerInnerRadius + aluminumThickness;
			G4double gasOuterRadius = bottomAluminumOuterRadius + gasThickness;

			G4Tubs* solidBottomAluminumLayer = new G4Tubs("solidBottomAluminumLayer", layerInnerRadius, bottomAluminumOuterRadius, muonSystemHalfLength, 0.*deg, 360.*deg);
			G4LogicalVolume* logicBottomAluminumLayer = new G4LogicalVolume(solidBottomAluminumLayer, Aluminum, "logicBottomAluminumLayer");
			muonBottomAluminumLVs.push_back(logicBottomAluminumLayer);
			new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicBottomAluminumLayer, "physBottomAluminumLayer", logicWorld, false, 0, overlapCheck);

			G4Tubs* solidGasLayer = new G4Tubs("solidGasLayer", bottomAluminumOuterRadius, gasOuterRadius, muonSystemHalfLength, 0.*deg, 360.*deg);
			logicGasLayer = new G4LogicalVolume(solidGasLayer, ArCO2, "logicGasLayer");
			muonGasLVs.push_back(logicGasLayer);
			new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicGasLayer, "physGasLayer", logicWorld, false, (i*30)+(j+1), overlapCheck);

			G4VisAttributes* tubeGasVis = new G4VisAttributes(G4Colour(0.3, 0.6, 1.0, 0.3)); // transparent blue
			tubeGasVis->SetForceSolid(true);
			logicGasLayer->SetVisAttributes(tubeGasVis);

			G4Tubs* solidTopAluminumLayer = new G4Tubs("solidTopAluminumLayer", gasOuterRadius, gasOuterRadius+aluminumThickness, muonSystemHalfLength, 0.*deg, 360.*deg);
			G4LogicalVolume* logicTopAluminumLayer = new G4LogicalVolume(solidTopAluminumLayer, Aluminum, "logicTopAluminumLayer");
			muonTopAluminumLVs.push_back(logicTopAluminumLayer);
			new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicTopAluminumLayer, "physTopAluminumLayer", logicWorld, false, 0, overlapCheck);
		}

		if(i==3){break;}

		G4double yokeInnerRadius = muonSystemInnerRadius + (i+1)*(dtLayers*dtThickness) + ironYokeSum[i]*m;
		G4double yokeOuterRadius = yokeInnerRadius + ironYoke[i+1]*m;

		G4Tubs* solidIronYoke = new G4Tubs("solidIronYoke", yokeInnerRadius, yokeOuterRadius, muonSystemHalfLength, 0.*deg, 360.*deg);
        G4LogicalVolume* logicIronYoke = new G4LogicalVolume(solidIronYoke, Fe, "logicIronYoke");
		muonYokeLVs.push_back(logicIronYoke);
        new G4PVPlacement(0, G4ThreeVector(0.,0.,0.), logicIronYoke, "physIronYoke", logicWorld, false, 0, overlapCheck);
        
        G4VisAttributes* ironYokeVis = new G4VisAttributes(G4Colour(0.8, 0.2, 0.2, 0.4)); // red color
        ironYokeVis->SetForceSolid(true);
        logicIronYoke->SetVisAttributes(ironYokeVis);
	}

	//**********************************************************************************

	return physWorld; 
}

void MyDetectorConstruction::ConstructSDandField()
{
    // Sensitive Detectors
    auto sdManager = G4SDManager::GetSDMpointer();
    G4String SDname1, SDname2, SDname3;

    auto ECAL = new MySensitiveDetector(SDname1 = "/ECAL");
    auto HCAL = new MySensitiveDetector(SDname2 = "/HCAL");
    auto DT   = new MySensitiveDetector(SDname3 = "/DT");

    sdManager->AddNewDetector(ECAL);
    sdManager->AddNewDetector(HCAL);
    sdManager->AddNewDetector(DT);

    logicECAL->SetSensitiveDetector(ECAL);
    for (auto lv : hcalScintillatorLVs)
        lv->SetSensitiveDetector(HCAL);
    for (auto lv : muonGasLVs)
        lv->SetSensitiveDetector(DT);

	/*
    // Magnetic Fields - not working correctly right now
    if (useMagneticField)
    {
        G4bool forceToAllDaughters = true;

        // 4T Solenoid Field (inside)
        fSolenoidField = new MagneticField(4.0 * tesla);
        fSolenoidFieldMgr = new G4FieldManager();
        fSolenoidFieldMgr->SetDetectorField(fSolenoidField);
        fSolenoidFieldMgr->CreateChordFinder(fSolenoidField);

        fSolenoidFieldLogical->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        logicBeamPipe->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        logicAbsorber->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        logicECAL->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        logicSteel->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        logicSteel2->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        for (auto lv : hcalScintillatorLVs)
            lv->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);
        for (auto lv : hcalBrassLVs)
            lv->SetFieldManager(fSolenoidFieldMgr, forceToAllDaughters);

        // -2.5T Return Field (outside)
        fReturnField = new MagneticField(-2.5 * tesla);
        fReturnFieldMgr = new G4FieldManager();
        fReturnFieldMgr->SetDetectorField(fReturnField);
        fReturnFieldMgr->CreateChordFinder(fReturnField);

        fReturnFieldLogical->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
        logicSteel3->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
        logicScintLayer->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
        for (auto lv : muonGasLVs)
            lv->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
        for (auto lv : muonTopAluminumLVs)
            lv->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
        for (auto lv : muonBottomAluminumLVs)
            lv->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
        for (auto lv : muonYokeLVs)
            lv->SetFieldManager(fReturnFieldMgr, forceToAllDaughters);
    }
	*/
}
	
