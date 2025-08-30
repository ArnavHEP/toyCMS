#ifndef RUNACTION_HH
#define RUNACTION_HH
 
#include "G4UserRunAction.hh"
#include "G4AnalysisManager.hh"
#include "globals.hh"

class G4Run;
class EventAction;

class MyRunAction : public G4UserRunAction
{
public:
	MyRunAction(EventAction* eventAction);
	~MyRunAction() override = default;
	
	void BeginOfRunAction(const G4Run*);
	void EndOfRunAction(const G4Run*);

private:
    EventAction* fEventAction = nullptr;
};

#endif
