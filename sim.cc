#include <iostream>

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "G4String.hh"

#include "construction.hh"
#include "physics.hh"
#include "action.hh"

int main(int argc, char** argv)
{
    G4String hepmcFileName = ""; 
    G4bool useHepMC = false;
    
    for (G4int i = 1; i < argc; i++) {
        if (G4String(argv[i]) == "-f" && i+1 < argc) {
            hepmcFileName = argv[i+1];
            useHepMC = true;
        }
    }
    
    G4RunManager *runManager = new G4RunManager();
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());

    if (useHepMC) {
        runManager->SetUserInitialization(new MyActionInitialization(hepmcFileName));
    } 
	else {
        runManager->SetUserInitialization(new MyActionInitialization());
    }
    
    runManager->Initialize();
    G4UIExecutive *ui = new G4UIExecutive(argc, argv);
    G4VisManager *visManager = new G4VisExecutive();
    visManager->Initialize();
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/vis/open OGL");    
    UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 0");
    UImanager->ApplyCommand("/vis/drawVolume");
    UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
    UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
    UImanager->ApplyCommand("/vis/tracking/storeTrajectory 0");
    
    ui->SessionStart();
    delete ui;
    delete visManager;
    delete runManager;
    
    return 0;
}


