#ifndef HepMCG4Interface_h
#define HepMCG4Interface_h 1

#include "G4VUserPrimaryGeneratorAction.hh"
#include "G4String.hh"
#include "globals.hh"
#include "G4SystemOfUnits.hh"

namespace HepMC
{
    class IO_GenEvent;
    class GenEvent;
}
class G4Event;


class HepMCG4Interface : public G4VUserPrimaryGeneratorAction
{
public:
    HepMCG4Interface(const G4String& hepmcFileName);
    virtual ~HepMCG4Interface();

    virtual void GeneratePrimaries(G4Event* anEvent);

private:
    HepMC::IO_GenEvent* m_asciiInput = nullptr;
    G4bool ConvertHepMCEvent(const HepMC::GenEvent* hepmcEvt, G4Event* g4Evt);

    const G4double momentumUnit = GeV;
    const G4double lengthUnit   = mm; 
};

#endif