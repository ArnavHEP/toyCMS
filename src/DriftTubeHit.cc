#include "DriftTubeHit.hh"

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

G4ThreadLocal G4Allocator<DriftTubeHit>* DriftTubeHitAllocator = nullptr;

DriftTubeHit::DriftTubeHit(G4int layerNo, G4double time)
: fLayerNo(layerNo), fTime(time)
{}

DriftTubeHit::~DriftTubeHit()
{}

G4bool DriftTubeHit::operator==(const DriftTubeHit &right) const
{
  return (fLayerNo == right.fLayerNo);
}

const std::map<G4String,G4AttDef>* DriftTubeHit::GetAttDefs() const
{
  G4bool isNew;
  auto store = G4AttDefStore::GetInstance("DriftTubeHit", isNew);

  if (isNew) {
    (*store)["HitType"]
      = G4AttDef("HitType","Hit Type","Physics","","G4String");

    (*store)["LayerNo"]
      = G4AttDef("LayerNo","Layer Number","Physics","","G4int");

    (*store)["Time"]
      = G4AttDef("Time","Hit Time","Physics","G4BestUnit","G4double");

    (*store)["EDep"]
      = G4AttDef("EDep","Energy Deposit","Physics","G4BestUnit","G4double");

    (*store)["Pos"]
      = G4AttDef("Pos","Hit Position","Physics","G4BestUnit","G4ThreeVector");
  }
  return store;
}

std::vector<G4AttValue>* DriftTubeHit::CreateAttValues() const
{
  auto values = new std::vector<G4AttValue>;

  values->push_back(G4AttValue("HitType","DriftTubeHit",""));
  values->push_back(G4AttValue("LayerNo", G4UIcommand::ConvertToString(fLayerNo), ""));
  values->push_back(G4AttValue("Time", G4BestUnit(fTime,"Time"), ""));
  values->push_back(G4AttValue("EDep", G4BestUnit(fEdep,"Energy"), ""));
  values->push_back(G4AttValue("Pos", G4BestUnit(fPos,"Length"), ""));

  return values;
}
