#ifndef MIPTIMINGDETECTORHIT_HH
#define MIPTIMINGDETECTORHIT_HH 

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

class MipTimingDetectorHit : public G4VHit
{
  public:
    MipTimingDetectorHit() = default;
    MipTimingDetectorHit(G4int crystalNo, G4double time);
    MipTimingDetectorHit(const MipTimingDetectorHit &right) = default;
    ~MipTimingDetectorHit();

    MipTimingDetectorHit& operator=(const MipTimingDetectorHit &right) = default;
    G4bool operator==(const MipTimingDetectorHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    const std::map<G4String,G4AttDef>* GetAttDefs() const override;
    std::vector<G4AttValue>* CreateAttValues() const override;

    void SetCrystalNo(G4int z) { fCrystalNo = z; }
    G4int GetCrystalNo() const { return fCrystalNo; }

    void SetTime(G4double val) { fTime = val; }
    G4double GetTime() const { return fTime; }

    void SetEdep(G4double de) { fEdep = de; }
    void AddEdep(G4double de) { fEdep += de; }
    G4double GetEdep() const { return fEdep; }

    void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    G4ThreeVector GetPos() const { return fPos; }

  private:
    G4int fCrystalNo = -1;
    G4double fTime = 0.;
    G4double fEdep = 0.;
    G4ThreeVector fPos;
};

using MipTimingDetectorHitsCollection = G4THitsCollection<MipTimingDetectorHit>;

extern G4ThreadLocal G4Allocator<MipTimingDetectorHit>* MipTimingDetectorHitAllocator;

inline void* MipTimingDetectorHit::operator new(size_t)
{
  if (!MipTimingDetectorHitAllocator)
  {
      MipTimingDetectorHitAllocator = new G4Allocator<MipTimingDetectorHit>;
  }
  return (void*)MipTimingDetectorHitAllocator->MallocSingle();
}

inline void MipTimingDetectorHit::operator delete(void* aHit)
{
  MipTimingDetectorHitAllocator->FreeSingle((MipTimingDetectorHit*) aHit);
}

#endif