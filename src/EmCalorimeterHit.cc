#include "EmCalorimeterHit.hh"

#include "G4VVisManager.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4AttDefStore.hh"
#include "G4AttDef.hh"
#include "G4AttValue.hh"
#include "G4UIcommand.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4ios.hh"


G4ThreadLocal G4Allocator<EmCalorimeterHit>* EmCalorimeterHitAllocator = nullptr;

EmCalorimeterHit::EmCalorimeterHit(G4int CrystalNo, G4double time)
: fCrystalNo(CrystalNo), fTime(time)
{}

EmCalorimeterHit::~EmCalorimeterHit()
{}

G4bool EmCalorimeterHit::operator==(const EmCalorimeterHit &right) const
{
  return (fCrystalNo==right.fCrystalNo);
}

const std::map<G4String,G4AttDef>* EmCalorimeterHit::GetAttDefs() const
{
  G4bool isNew;
  auto store = G4AttDefStore::GetInstance("EmCalorimeterHit",isNew);

  if (isNew) {
    (*store)["HitType"]
      = G4AttDef("HitType","Hit Type","Physics","","G4String");

    (*store)["CrystalNo"]
      = G4AttDef("CrystalNo","CrystalNo","Physics","","G4int");

    (*store)["Time"]
      = G4AttDef("Time","Time","Physics","G4BestUnit","G4double");

    (*store)["EDep"]
      = G4AttDef("EDep","EDep","Physics","G4BestUnit",
                 "G4double");

    (*store)["Pos"] 
      = G4AttDef("Pos", "Position", "Physics", "G4BestUnit", "G4ThreeVector");

    (*store)["PID"]
      = G4AttDef("PID","Particle ID","Physics","G4BestUnit","G4int");
  }
  return store;
}

std::vector<G4AttValue>* EmCalorimeterHit::CreateAttValues() const
{
  auto values = new std::vector<G4AttValue>;

  values
    ->push_back(G4AttValue("HitType","EmCalorimeterHit",""));
  values
    ->push_back(G4AttValue("CrystalNo",G4UIcommand::ConvertToString(fCrystalNo),""));
  values
    ->push_back(G4AttValue("Time",G4BestUnit(fTime,"Time"),""));
  values
    ->push_back(G4AttValue("EDep",G4BestUnit(fEdep,"EDep"),""));
  values
    ->push_back(G4AttValue("Pos", G4BestUnit(fPos, "Length"), ""));
  values
    ->push_back(G4AttValue("PID", G4BestUnit(fPID,"ParticleID"), ""));

  return values;
}
//}