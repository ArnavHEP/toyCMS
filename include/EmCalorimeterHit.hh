#ifndef EMCALORIMETERHIT_HH
#define EMCALORIMETERHIT_HH 



#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "G4LogicalVolume.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"

class G4AttDef;
class G4AttValue;

//namespace SIM
//{

class EmCalorimeterHit : public G4VHit
{
  public:
    //making hit class
    EmCalorimeterHit() = default;
    EmCalorimeterHit(G4int CrystalNo, G4double time);
    EmCalorimeterHit(const EmCalorimeterHit &right) = default;
    ~EmCalorimeterHit();//override = default;

    EmCalorimeterHit& operator=(const EmCalorimeterHit &right) = default;
    G4bool operator==(const EmCalorimeterHit &right) const;

    inline void *operator new(size_t);
    inline void operator delete(void *aHit);

    //getting attributes for visualization
    const std::map<G4String,G4AttDef>* GetAttDefs() const override;
    std::vector<G4AttValue>* CreateAttValues() const override;

    //making methods
    void SetCrystalNo(G4int z) { fCrystalNo = z; }
    G4int GetCrystalNo() const { return fCrystalNo; }

    void SetTime(G4double val) { fTime = val; }
    G4double GetTime() const { return fTime; }

    void SetEdep(G4double de) { fEdep = de; }
    void AddEdep(G4double de) { fEdep += de; }
    G4double GetEdep() const { return fEdep; }

    void SetPos(G4ThreeVector xyz) { fPos = xyz; }
    G4ThreeVector GetPos() const { return fPos; }

    //void SetLogV(G4LogicalVolume* val) { fPLogV = val; }
    //const G4LogicalVolume* GetLogV() const { return fPLogV; }

  private:
    G4int fCrystalNo = -1;
    G4double fTime = 0.;
    G4double fEdep = 0.;
    G4ThreeVector fPos;
    //const G4LogicalVolume* fPLogV = nullptr;
};

using EmCalorimeterHitsCollection = G4THitsCollection<EmCalorimeterHit>; // allocates and deallocates memory

extern G4ThreadLocal G4Allocator<EmCalorimeterHit>* EmCalorimeterHitAllocator;

inline void* EmCalorimeterHit::operator new(size_t)
{
  if (!EmCalorimeterHitAllocator)
  {
      EmCalorimeterHitAllocator = new G4Allocator<EmCalorimeterHit>;
  }
  return (void*)EmCalorimeterHitAllocator->MallocSingle();
}

inline void EmCalorimeterHit::operator delete(void* aHit)
{
  EmCalorimeterHitAllocator->FreeSingle((EmCalorimeterHit*) aHit);
}
//}
#endif
