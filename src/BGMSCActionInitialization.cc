#include "BGMSCActionInitialization.hh"
#include "BGMSCPrimaryGeneratorAction.hh"
#include "BGMSCRunAction.hh"
#include "BGMSCEventAction.hh"
#include "BGMSCSteppingAction.hh"
#include "BGMCSTrackingAction.hh"

BGMSCActionInitialization::BGMSCActionInitialization(BGMSCDetectorConstruction *geometry, BGMCSTrackingAction *trackingAction)
    : G4VUserActionInitialization()
{
    Geometry = geometry;
    TrackingAction = trackingAction;
}

BGMSCActionInitialization::~BGMSCActionInitialization()
{}

void BGMSCActionInitialization::BuildForMaster() const
{
    SetUserAction(new BGMSCRunAction(Geometry));
}

void BGMSCActionInitialization::Build() const
{
    SetUserAction(new BGMSCPrimaryGeneratorAction);
    SetUserAction(new BGMSCEventAction);
    SetUserAction(new BGMSCSteppingAction);
    SetUserAction(TrackingAction);
    SetUserAction(new BGMSCRunAction(Geometry));
}
