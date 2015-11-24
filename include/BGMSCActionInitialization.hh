#ifndef BGMSCACTIONINITIASLIZATION_HH
#define BGMSCACTIONINITIASLIZATION_HH

#include "G4VUserActionInitialization.hh"
#include "BGMSCDetectorConstruction.hh"
#include "BGMCSTrackingAction.hh"

class BGMSCActionInitialization : public G4VUserActionInitialization
{
  public:

    BGMSCActionInitialization(BGMSCDetectorConstruction* geometry, BGMCSTrackingAction* trackingAction);
    virtual ~BGMSCActionInitialization();

    virtual void BuildForMaster() const;
    virtual void Build() const;

private:
    BGMSCDetectorConstruction* Geometry;
    BGMCSTrackingAction* TrackingAction;
};

#endif // BGMSCACTIONINITIASLIZATION_HH
