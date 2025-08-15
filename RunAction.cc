#include "RunAction.hh"
#include "globals.hh"

MyRunAction::MyRunAction()
{}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Reset();
  man->OpenFile("output.root");

  man->CreateNtuple("ECAL", "ECAL");
  man->CreateNtupleDColumn("x");
  man->CreateNtupleDColumn("y");
  man->CreateNtupleDColumn("z");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->CreateNtupleIColumn("EventID");
  man->FinishNtuple(0);

  man->CreateNtuple("HCAL", "HCAL");
  man->CreateNtupleIColumn("LayerNo");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->CreateNtupleIColumn("EventID");
  man->FinishNtuple(1);

  man->CreateNtuple("DT", "DT");
  man->CreateNtupleIColumn("LayerNo");
  man->CreateNtupleDColumn("Time");
  man->CreateNtupleDColumn("EnergyDep");
  man->CreateNtupleIColumn("EventID");
  man->FinishNtuple(2);
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
  G4AnalysisManager *man = G4AnalysisManager::Instance();
  man->Write();
  man->CloseFile("output.root");
  G4cout << "Root File Generated" << G4endl << G4endl;
}

