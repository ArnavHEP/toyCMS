#ifndef ACTION_HH
#define ACTION_HH

#include "G4VUserActionInitialization.hh"
#include "generator.hh"
#include "RunAction.hh"
#include "G4String.hh"

class MyActionInitialization : public G4VUserActionInitialization
{
public:
	MyActionInitialization();
	MyActionInitialization(const G4String& hepmcFileName);
	~MyActionInitialization();
	
	virtual void Build() const;

private:
    G4String fHepMCFileName;
	G4bool fUseHepMC; 
};

#endif
