#ifndef HCALORIMETERHIT_HH
#define HCALORIMETERHIT_HH 

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"

class G4AttDef;
class G4AttValue;

class HCalorimeterHit : public G4VHit
{
  public:
    // Constructors and destructor
    HCalorimeterHit() = default;
    HCalorimeterHit(G4int layerNo, G4double time);
    HCalorimeterHit(const HCalorimeterHit &right) = default;
    ~HCalorimeterHit();

    HCalorimeterHit& operator=(const HCalorimeterHit &right) = default;
    G4bool operator==(const HCalorimeterHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    // Visualization attributes
    const std::map<G4String,G4AttDef>* GetAttDefs() const override;
    std::vector<G4AttValue>* CreateAttValues() const override;

    // Setters and getters
    void SetLayerNo(G4int n) { fLayerNo = n; }
    G4int GetLayerNo() const { return fLayerNo; }

    void SetTime(G4double val) { fTime = val; }
    G4double GetTime() const { return fTime; }

    void SetEdep(G4double de) { fEdep = de; }
    void AddEdep(G4double de) { fEdep += de; }
    G4double GetEdep() const { return fEdep; }

    void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    G4ThreeVector GetPos() const { return fPos; }

  private:
    G4int fLayerNo = -1;
    G4double fTime = 0.;
    G4double fEdep = 0.;
    G4ThreeVector fPos;
};

using HCalorimeterHitsCollection = G4THitsCollection<HCalorimeterHit>;

extern G4ThreadLocal G4Allocator<HCalorimeterHit>* HCalorimeterHitAllocator;

inline void* HCalorimeterHit::operator new(size_t)
{
  if (!HCalorimeterHitAllocator)
  {
      HCalorimeterHitAllocator = new G4Allocator<HCalorimeterHit>;
  }
  return (void*)HCalorimeterHitAllocator->MallocSingle();
}

inline void HCalorimeterHit::operator delete(void* aHit)
{
  HCalorimeterHitAllocator->FreeSingle((HCalorimeterHit*) aHit);
}

#endif
