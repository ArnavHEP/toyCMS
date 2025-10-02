#include "RunAction.hh"
#include "EventAction.hh"
#include "globals.hh"


MyRunAction::MyRunAction(EventAction* eventAction)
 : fEventAction(eventAction)
{
	G4AnalysisManager *man = G4AnalysisManager::Instance();
  
  if ( fEventAction )
	{
    // MTD
    man->CreateNtuple("MTD", "MTD");
    man->CreateNtupleIColumn("CrystalNo");
    man->CreateNtupleDColumn("x");
    man->CreateNtupleDColumn("y");
    man->CreateNtupleDColumn("z");
    man->CreateNtupleDColumn("Time");
    man->CreateNtupleDColumn("EnergyDep");
    man->CreateNtupleIColumn("ParticleID");
    man->CreateNtupleIColumn("EventID");
    man->FinishNtuple(0);

    // ECAL
    man->CreateNtuple("ECAL", "ECAL");
    man->CreateNtupleIColumn("CrystalNo");
    man->CreateNtupleDColumn("x");
    man->CreateNtupleDColumn("y");
    man->CreateNtupleDColumn("z");
    man->CreateNtupleDColumn("Time");
    man->CreateNtupleDColumn("EnergyDep");
    man->CreateNtupleIColumn("ParticleID");
    man->CreateNtupleIColumn("EventID");
    man->FinishNtuple(1);

    // HCAL
    man->CreateNtuple("HCAL", "HCAL");
    man->CreateNtupleIColumn("LayerNo");
    man->CreateNtupleDColumn("Time");
    man->CreateNtupleDColumn("EnergyDep");
    man->CreateNtupleIColumn("EventID");
    man->FinishNtuple(2);

    // DT
    man->CreateNtuple("DT", "DT");
    man->CreateNtupleIColumn("LayerNo");
    man->CreateNtupleDColumn("Time");
    man->CreateNtupleDColumn("EnergyDep");
    man->CreateNtupleIColumn("EventID");
    man->FinishNtuple(3);
  }   
}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Reset();
  man->OpenFile("output.root");
  //man->OpenFile("softQCD_20TeV_40cm_Cu.root");

}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile("output.root");
  //man->CloseFile("softQCD_20TeV_40cm_Cu.root");
  G4cout << "Root File Generated" << G4endl << G4endl;
}

