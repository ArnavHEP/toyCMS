#ifndef DRIFTTUBEHIT_HH
#define DRIFTTUBEHIT_HH 

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

class DriftTubeHit : public G4VHit
{
  public:
    DriftTubeHit() = default;
    DriftTubeHit(G4int layerNo, G4double time);
    DriftTubeHit(const DriftTubeHit &right) = default;
    ~DriftTubeHit();

    DriftTubeHit& operator=(const DriftTubeHit &right) = default;
    G4bool operator==(const DriftTubeHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    const std::map<G4String,G4AttDef>* GetAttDefs() const override;
    std::vector<G4AttValue>* CreateAttValues() const override;

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

using DriftTubeHitsCollection = G4THitsCollection<DriftTubeHit>;

extern G4ThreadLocal G4Allocator<DriftTubeHit>* DriftTubeHitAllocator;

inline void* DriftTubeHit::operator new(size_t)
{
  if (!DriftTubeHitAllocator)
  {
      DriftTubeHitAllocator = new G4Allocator<DriftTubeHit>;
  }
  return (void*)DriftTubeHitAllocator->MallocSingle();
}

inline void DriftTubeHit::operator delete(void* aHit)
{
  DriftTubeHitAllocator->FreeSingle((DriftTubeHit*) aHit);
}

#endif
