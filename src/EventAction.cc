#include "EventAction.hh"
#include "EmCalorimeterHit.hh"
#include "HCalorimeterHit.hh"
#include "DriftTubeHit.hh"
#include "MipTimingDetectorHit.hh"

#include "G4Event.hh"
#include "G4RunManager.hh"
#include "G4EventManager.hh"
#include "G4HCofThisEvent.hh"
#include "G4VHitsCollection.hh"
#include "G4SDManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"
#include "G4AnalysisManager.hh"
#include "globals.hh"


G4VHitsCollection* GetHC(const G4Event* event, G4int collId) 
{
    auto hce = event->GetHCofThisEvent();
    auto hc = hce->GetHC(collId);
    return hc;
}

EventAction::EventAction()
{}

void EventAction::BeginOfEventAction(const G4Event*)
{
    auto sdManager = G4SDManager::GetSDMpointer();

    // hits collections names
    G4String mtdHCName =  "MipTimingDetector/MipTimingDetectorColl";
    G4String eHCName =  "EmCalorimeter/EmCalorimeterColl";
    G4String hHCName =  "HCalorimeter/HCalorimeterColl";
    G4String dtHCName =  "DriftTube/DriftTubeColl";

    // hit collections IDs
    if (fMTDHCID < 0) fMTDHCID = sdManager->GetCollectionID(mtdHCName);
    if (fECalHCID < 0) fECalHCID = sdManager->GetCollectionID(eHCName);
    if (fHCalHCID < 0) fHCalHCID = sdManager->GetCollectionID(hHCName);
    if (fDTHCID < 0) fDTHCID = sdManager->GetCollectionID(dtHCName);
}

void EventAction::EndOfEventAction(const G4Event* event)
{
    auto analysisManager = G4AnalysisManager::Instance();
    G4int EventID = event->GetEventID();

    //MTD
    auto mtdhc = GetHC(event, fMTDHCID);
    if (mtdhc)
    {
        for (G4int i = 0; i < mtdhc->GetSize(); i++)
        {
            auto hit = static_cast<MipTimingDetectorHit*>(mtdhc->GetHit(i));
            G4ThreeVector pos = hit->GetPos();

            analysisManager->FillNtupleIColumn(0, 0, hit->GetCrystalNo());
            analysisManager->FillNtupleDColumn(0, 1, pos.x());
            analysisManager->FillNtupleDColumn(0, 2, pos.y());
            analysisManager->FillNtupleDColumn(0, 3, pos.z());
            analysisManager->FillNtupleDColumn(0, 4, hit->GetTime());
            analysisManager->FillNtupleIColumn(0, 5, EventID);
            analysisManager->AddNtupleRow(0);
        }
    }

    //ECAL
    auto ehc = GetHC(event, fECalHCID);
    if (ehc)
    {
        for (G4int i = 0; i < ehc->GetSize(); i++)
        {
            auto hit = static_cast<EmCalorimeterHit*>(ehc->GetHit(i));
            G4ThreeVector pos = hit->GetPos();

            analysisManager->FillNtupleIColumn(1, 0, hit->GetCrystalNo());
            analysisManager->FillNtupleDColumn(1, 1, pos.x());
            analysisManager->FillNtupleDColumn(1, 2, pos.y());
            analysisManager->FillNtupleDColumn(1, 3, pos.z());
            analysisManager->FillNtupleDColumn(1, 4, hit->GetTime());
            analysisManager->FillNtupleDColumn(1, 5, hit->GetEdep());
            analysisManager->FillNtupleIColumn(1, 6, EventID);
            analysisManager->AddNtupleRow(1);
        }
    }

    //HCAL
    auto hhc = GetHC(event, fHCalHCID);
    if (hhc)
    {
        for (G4int i = 0; i < hhc->GetSize(); i++)
        {
            auto hit = static_cast<HCalorimeterHit*>(hhc->GetHit(i));
            analysisManager->FillNtupleIColumn(2, 0, hit->GetLayerNo());
            analysisManager->FillNtupleDColumn(2, 1, hit->GetTime());
            analysisManager->FillNtupleDColumn(2, 2, hit->GetEdep());
            analysisManager->FillNtupleIColumn(2, 3, EventID);
            analysisManager->AddNtupleRow(2);
        }
    }

    //DT
    auto dthc = GetHC(event, fDTHCID);
    if (dthc)
    {
        for (G4int i = 0; i < dthc->GetSize(); i++)
        {
            auto hit = static_cast<DriftTubeHit*>(dthc->GetHit(i));
            analysisManager->FillNtupleIColumn(3, 0, hit->GetLayerNo());
            analysisManager->FillNtupleDColumn(3, 1, hit->GetTime());
            analysisManager->FillNtupleDColumn(3, 2, hit->GetEdep());
            analysisManager->FillNtupleIColumn(3, 3, EventID);
            analysisManager->AddNtupleRow(3);
        }
    }

    G4cout << "Event : " << EventID+1 << G4endl << G4endl;
}
