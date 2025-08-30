#include "action.hh"
#include "RunAction.hh"
#include "HepMCG4Interface.hh"
#include "EventAction.hh"

MyActionInitialization::MyActionInitialization()
 : G4VUserActionInitialization(), fHepMCFileName(""), fUseHepMC(false)
{}

MyActionInitialization::MyActionInitialization(const G4String& hepmcFileName)
: G4VUserActionInitialization(), fHepMCFileName(hepmcFileName), fUseHepMC(true)
{}

MyActionInitialization::~MyActionInitialization()
{}

void MyActionInitialization::Build() const
{	
	if (fUseHepMC && !fHepMCFileName.empty())
	{
        G4cout << "MyActionInitialization: Using HepMC interface with file: " << fHepMCFileName << G4endl;
        SetUserAction(new HepMCG4Interface(fHepMCFileName));
    }
	else 
	{
        G4cout << "MyActionInitialization: Using particle gun generator" << G4endl;
        MyPrimaryGenerator *generator = new MyPrimaryGenerator();
		SetUserAction(generator);
    }

	auto eventAction = new EventAction;
  	SetUserAction(eventAction);

  	SetUserAction(new MyRunAction(eventAction));
}