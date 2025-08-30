#include "generator.hh"
#include "Randomize.hh"

MyPrimaryGenerator::MyPrimaryGenerator()
{
	fParticleGun = new G4ParticleGun(1); // number of particle per event
}

MyPrimaryGenerator::~MyPrimaryGenerator()
{
	delete fParticleGun;
}

void MyPrimaryGenerator::GeneratePrimaries(G4Event *anEvent)
{
	G4ParticleTable *particleTable = G4ParticleTable::GetParticleTable();
	
	G4ParticleDefinition *particle = particleTable->FindParticle("gamma");
	
	G4ThreeVector pos(0.,0.,0.);
	G4ThreeVector mom;
	do{
	mom = G4ThreeVector(G4UniformRand()*2-1, G4UniformRand()*2-1, G4UniformRand()*2-1);}
	while (mom.mag() == 0 || std::abs(mom.unit().z()) > std::cos(45*deg));
	
	fParticleGun->SetParticlePosition(pos);
	fParticleGun->SetParticleMomentumDirection(mom.unit());
	fParticleGun->SetParticleMomentum(10*GeV);
	fParticleGun->SetParticleDefinition(particle);
	fParticleGun->GeneratePrimaryVertex(anEvent);
}

