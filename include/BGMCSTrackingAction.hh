#ifndef BGMCSTRACKINGACTION_h
#define BGMCSTRACKINGACTION_h

#include "G4UserTrackingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4Threading.hh"
#include "G4AutoLock.hh"

class BGMCSTrackingAction : public G4UserTrackingAction {

public:
    BGMCSTrackingAction()
    {
        sumTrack = 0;
        numTrack = 0;
        i=1;
    }

    ~BGMCSTrackingAction()
    {
        G4cout << "Tracking Action deleted " << G4endl;
        G4MUTEXDESTROY(mutex);
    }

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

    void Reset();

private:
    G4Mutex mutex;

    G4double sumTrack;
    G4int numTrack;
    G4int i;
};

#endif
