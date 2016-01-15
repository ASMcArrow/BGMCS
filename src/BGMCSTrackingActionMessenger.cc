#include "BGMCSTrackingActionMessenger.hh"
#include "BGMCSTrackingAction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

BGMCSTrackingActionMessenger::BGMCSTrackingActionMessenger(BGMCSTrackingAction *trackingAction)
    :G4UImessenger(), TrackingAction(trackingAction)
{
    TopDirectory = new G4UIdirectory("/BGMSC/");
    TopDirectory->SetGuidance("UI commands for BGMSC");

    Directory = new G4UIdirectory("/BGMSC/tracking/");
    Directory->SetGuidance("Reset for new calculation of projected range");

    ResetCmd = new G4UIcmdWithoutParameter("/BGMSC/tracking/reset", this);
    ResetCmd->SetGuidance("Reset the ranges");
    ResetCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

BGMCSTrackingActionMessenger::~BGMCSTrackingActionMessenger()
{
    delete TopDirectory;
    delete Directory;
    delete ResetCmd;
}

void BGMCSTrackingActionMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
//    if(command == ResetCmd)
//        TrackingAction->GetRange();
}
