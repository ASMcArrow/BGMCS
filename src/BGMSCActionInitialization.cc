#include "BGMSCPrimaryGeneratorAction.hh"
#include "BGMSCRunAction.hh"
#include "BGMSCEventAction.hh"
#include "BGMSCSteppingAction.hh"
#include "BGMSCActionInitialization.hh"

BGMSCActionInitialization::BGMSCActionInitialization(BGMSCDetectorConstruction *geometry)
    : G4VUserActionInitialization()
{
    Geometry = geometry;
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
    SetUserAction(new BGMSCRunAction(Geometry));
}
