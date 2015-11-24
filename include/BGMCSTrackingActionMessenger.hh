#ifndef BGMSCTRACKINGMESSENGER_HH
#define BGMSCTRACKINGMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class BGMCSTrackingAction;
class G4UIdirectory;
class G4UIcmdWithoutParameter;

// Messenger class that implements command:
// - /BGMSC/tracking/reset

class BGMCSTrackingActionMessenger: public G4UImessenger
{

public:
    BGMCSTrackingActionMessenger(BGMCSTrackingAction* trackingAction);
    virtual ~BGMCSTrackingActionMessenger();

    virtual void SetNewValue(G4UIcommand* command, G4String newValue);

private:
    BGMCSTrackingAction* TrackingAction;
    G4UIdirectory* TopDirectory;
    G4UIdirectory* Directory;
    G4UIcmdWithoutParameter* ResetCmd;
};

#endif // BGMSCMESSENGER_HH
