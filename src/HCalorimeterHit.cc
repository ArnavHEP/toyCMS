#include "HCalorimeterHit.hh"

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

G4ThreadLocal G4Allocator<HCalorimeterHit>* HCalorimeterHitAllocator = nullptr;

HCalorimeterHit::HCalorimeterHit(G4int layerNo, G4double time)
: fLayerNo(layerNo), fTime(time)
{}

HCalorimeterHit::~HCalorimeterHit()
{}

G4bool HCalorimeterHit::operator==(const HCalorimeterHit &right) const
{
  return (fLayerNo == right.fLayerNo);
}

const std::map<G4String,G4AttDef>* HCalorimeterHit::GetAttDefs() const
{
  G4bool isNew;
  auto store = G4AttDefStore::GetInstance("HCalorimeterHit", isNew);

  if (isNew) {
    (*store)["HitType"]
      = G4AttDef("HitType","Hit Type","Physics","","G4String");

    (*store)["LayerNo"]
      = G4AttDef("LayerNo","LayerNo","Physics","","G4int");

    (*store)["Time"]
      = G4AttDef("Time","Time","Physics","G4BestUnit","G4double");

    (*store)["EDep"]
      = G4AttDef("EDep","EDep","Physics","G4BestUnit","G4double");

    (*store)["Pos"]
      = G4AttDef("Pos","Pos","Physics","G4BestUnit","G4ThreeVector");
  }
  return store;
}

std::vector<G4AttValue>* HCalorimeterHit::CreateAttValues() const
{
  auto values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("HitType","HCalorimeterHit",""));
  values->push_back(G4AttValue("LayerNo", G4UIcommand::ConvertToString(fLayerNo), ""));
  values->push_back(G4AttValue("Time", G4BestUnit(fTime,"Time"), ""));
  values->push_back(G4AttValue("EDep", G4BestUnit(fEdep,"Energy"), ""));
  values->push_back(G4AttValue("Pos", G4BestUnit(fPos,"Length"), ""));

  return values;
}
