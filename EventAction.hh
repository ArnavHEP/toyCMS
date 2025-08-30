#ifndef EVENTACTION_HH
#define EVENTACTION_HH 

#include "G4UserEventAction.hh"
#include "globals.hh"

class EventAction : public G4UserEventAction
{
public:
    EventAction();
    ~EventAction() override = default;

    void BeginOfEventAction(const G4Event*) override;
    void EndOfEventAction(const G4Event*) override;
    
private:
    // hit collections Ids
    G4int fMTDHCID = -1;
    G4int fECalHCID = -1;
    G4int fHCalHCID = -1;
    G4int fDTHCID = -1;
};

#endif
