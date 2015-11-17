#include "BGMSCDetectorMessenger.hh"
#include "BGMSCDetectorConstruction.hh"

#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"

BGMSCDetectorMessenger::BGMSCDetectorMessenger(BGMSCDetectorConstruction* detectorConstruction)
    :G4UImessenger(), DetectorConstruction(detectorConstruction)
{
    TopDirectory = new G4UIdirectory("/BGMSC/");
    TopDirectory->SetGuidance("UI commands for BGMSC");

    Directory = new G4UIdirectory("/BGMSC/det/");
    Directory->SetGuidance("Control of material slab size and dimension");

    SetSlabMaterialCmd = new G4UIcmdWithAString("/BGMSC/det/setSlabMaterial", this);
    SetSlabMaterialCmd->SetGuidance("Select material of the slab");
    SetSlabMaterialCmd->SetParameterName("SlabMaterial", false);
    SetSlabMaterialCmd->AvailableForStates(G4State_PreInit, G4State_Idle);

    SetSlabThicknessCmd = new G4UIcmdWithADoubleAndUnit("/BGMSC/det/setSlabThickness",this);
    SetSlabThicknessCmd->SetGuidance("Set slab thickness (in g/cm^2)");
    SetSlabThicknessCmd->SetParameterName("SlabThickness", false);
    SetSlabThicknessCmd->SetUnitCategory("Mass/Surface");
    SetSlabThicknessCmd->SetDefaultUnit("g/cm2");
    SetSlabThicknessCmd->AvailableForStates(G4State_PreInit, G4State_Idle);
}

BGMSCDetectorMessenger::~BGMSCDetectorMessenger()
{
    delete TopDirectory;
    delete Directory;
    delete SetSlabMaterialCmd;
}

void BGMSCDetectorMessenger::SetNewValue(G4UIcommand* command, G4String newValue)
{
    if(command == SetSlabMaterialCmd)
        DetectorConstruction->SetSlabMaterial(newValue);

    else if (command == SetSlabThicknessCmd)
    {
        G4double thickness = (SetSlabThicknessCmd->ConvertToDimensionedDouble(newValue))/(g/cm2);
        DetectorConstruction->SetSlabThickness(thickness);
    }
}
