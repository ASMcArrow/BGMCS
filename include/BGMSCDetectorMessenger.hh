#ifndef BGMSCMESSENGER_HH
#define BGMSCMESSENGER_HH

#include "G4UImessenger.hh"
#include "globals.hh"

class BGMSCDetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithAString;
class G4UIcmdWithADoubleAndUnit;

// Messenger class that implements commands:
// - /BGMSC/det/setSlabMaterialName name
// - /BGMSC/det/setSlabDimensions hx hy hz unit

class BGMSCDetectorMessenger: public G4UImessenger
{

public:
    BGMSCDetectorMessenger(BGMSCDetectorConstruction* detectorConstruction);
    virtual ~BGMSCDetectorMessenger();

    virtual void SetNewValue(G4UIcommand* command, G4String newValue);

private:
    BGMSCDetectorConstruction* DetectorConstruction;
    G4UIdirectory* TopDirectory;
    G4UIdirectory* Directory;

    G4UIcmdWithAString* SetSlabMaterialCmd;
    G4UIcmdWithADoubleAndUnit* SetSlabThicknessCmd;
    G4UIcmdWithADoubleAndUnit* SetICmd;
};

#endif // BGMSCMESSENGER_HH
