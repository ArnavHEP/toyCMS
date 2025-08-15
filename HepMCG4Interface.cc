#include "HepMCG4Interface.hh"

#include "G4Event.hh"
#include "G4PrimaryParticle.hh"
#include "G4PrimaryVertex.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"

#include "HepMC/IO_GenEvent.h"
#include "HepMC/GenEvent.h"
#include "HepMC/GenParticle.h"
#include "HepMC/GenVertex.h"

#include <map>

HepMCG4Interface::HepMCG4Interface(const G4String& hepmcFileName)
{
    m_asciiInput = new HepMC::IO_GenEvent(hepmcFileName.c_str(), std::ios::in);
}

HepMCG4Interface::~HepMCG4Interface()
{
    delete m_asciiInput;
}

void HepMCG4Interface::GeneratePrimaries(G4Event* anEvent)
{
    HepMC::GenEvent* hepmcEvt = m_asciiInput->read_next_event();
    ConvertHepMCEvent(hepmcEvt, anEvent);
    delete hepmcEvt;
    hepmcEvt = nullptr;
}

G4bool HepMCG4Interface::ConvertHepMCEvent(const HepMC::GenEvent* hepmcEvt, G4Event* g4Evt)
{ 
    std::map<int, G4PrimaryVertex*> geant4Vertices;

    for (HepMC::GenEvent::particle_const_iterator piter = hepmcEvt->particles_begin();
         piter != hepmcEvt->particles_end(); ++piter)
    {
        HepMC::GenParticle* hepmcParticle = *piter;

        if (hepmcParticle->status() == 1) {
            HepMC::GenVertex* prodVertexHepMC = hepmcParticle->production_vertex();
            int vertexBarcode = prodVertexHepMC->barcode();
            G4PrimaryVertex* g4Vertex = nullptr;

            auto vtxIt = geant4Vertices.find(vertexBarcode);
            if (vtxIt == geant4Vertices.end())
            {
                HepMC::FourVector pos = prodVertexHepMC->position();
                G4double x = pos.x() * lengthUnit; // Assumes mm
                G4double y = pos.y() * lengthUnit; // Assumes mm
                G4double z = pos.z() * lengthUnit; // Assumes mm
                G4double t = (pos.t() * lengthUnit) / c_light; // Convert t_mm to G4 time (ns)

                g4Vertex = new G4PrimaryVertex(x, y, z, t);
                geant4Vertices[vertexBarcode] = g4Vertex;
                g4Evt->AddPrimaryVertex(g4Vertex);
            } 
            else 
            {
                g4Vertex = vtxIt->second;
            }

            HepMC::FourVector mom = hepmcParticle->momentum();
            G4double px = mom.px() * momentumUnit;
            G4double py = mom.py() * momentumUnit;
            G4double pz = mom.pz() * momentumUnit; 
            G4int pdgCode = hepmcParticle->pdg_id();

            G4PrimaryParticle* g4Particle = new G4PrimaryParticle(pdgCode, px, py, pz);
            g4Vertex->SetPrimary(g4Particle); // Add particle to vertex
        }
    } 
    return true; 
}