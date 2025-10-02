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
    char response;
    
    std::cout << "Use HepMC file? (y/n): ";
    std::cin >> response;
    bool useHepMC = (response == 'y' || response == 'Y');
    
    std::cout << "Use visualisation? (y/n): ";
    std::cin >> response;
    bool batchMode = (response == 'y' || response == 'Y');

    G4UIExecutive* ui = nullptr;
    if (!batchMode) {
        ui = new G4UIExecutive(argc, argv);
    }
    
    G4String hepmcFileName = "../events/LLP2jets/phi0_30GeV.hepmc";
    
    G4RunManager *runManager = new G4RunManager();
    
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());

    if (useHepMC) {
        runManager->SetUserInitialization(new MyActionInitialization(hepmcFileName));
    } 
    else {
        runManager->SetUserInitialization(new MyActionInitialization());
    }

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    
    if (batchMode)
    {
        runManager->Initialize();
        UImanager->ApplyCommand("/run/beamOn 1");
    }
    else
    {    
        runManager->Initialize();
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        UImanager->ApplyCommand("/vis/open OGL");    
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 0");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager->ApplyCommand("/vis/tracking/storeTrajectory 0");
        ui->SessionStart();

        delete visManager;
        delete ui;
    }

    delete runManager;
    return 0;
}


/*
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

    G4UIExecutive* ui = nullptr;
    if (argc == 1) {
        ui = new G4UIExecutive(argc, argv);
    }

    G4bool useHepMC = true;

    G4String hepmcFileName = "../events/LLP2jets/phi0_30GeV.hepmc";
    //G4String hepmcFileName = "../events/LLP2photons/phi_gamma_30GeV.hepmc";
    //G4String hepmcFileName = "../events/softQCD/softQCD_14TeV.hepmc";
    
    G4RunManager *runManager = new G4RunManager();
    
    runManager->SetUserInitialization(new MyDetectorConstruction());
    runManager->SetUserInitialization(new MyPhysicsList());

    if (useHepMC) {
        runManager->SetUserInitialization(new MyActionInitialization(hepmcFileName));
    } 
	else {
        runManager->SetUserInitialization(new MyActionInitialization());
    }

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    if (!ui)
    {
        // Batch mode: execute the macro file passed as an argument
        G4String command = "/control/execute ";
        G4String fileName = argv[1];
        UImanager->ApplyCommand(command + fileName);
    }

    else
    {    
        runManager->Initialize();
        G4VisManager* visManager = new G4VisExecutive;
        visManager->Initialize();
        UImanager->ApplyCommand("/vis/open OGL");    
        UImanager->ApplyCommand("/vis/viewer/set/viewpointVector 0 0 0");
        UImanager->ApplyCommand("/vis/drawVolume");
        UImanager->ApplyCommand("/vis/viewer/set/autoRefresh true");
        UImanager->ApplyCommand("/vis/scene/add/trajectories smooth");
        UImanager->ApplyCommand("/vis/tracking/storeTrajectory 0");
        UImanager->ApplyCommand("/control/execute ../init_vis.mac");
        ui->SessionStart();

        delete visManager;
        delete ui;
    }

    delete runManager;
    return 0;
}
*/

/*
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
*/



