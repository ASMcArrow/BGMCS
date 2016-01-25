#ifndef BGMCSTRACKINGACTION_h
#define BGMCSTRACKINGACTION_h

#include "BGMSCDetectorConstruction.hh"

#include "G4UserTrackingAction.hh"
#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"

class BGMCSTrackingAction : public G4UserTrackingAction {

public:
    BGMCSTrackingAction();

    virtual ~BGMCSTrackingAction()
    {
        G4MUTEXDESTROY(Mutex);
    }

    virtual void PreUserTrackingAction(const G4Track* aTrack);
    virtual void PostUserTrackingAction(const G4Track* aTrack);

private:
    G4Mutex Mutex;
};

#endif
