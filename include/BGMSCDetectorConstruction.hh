#ifndef BGMSCDETECTORCONSTRUCTION_H
#define BGMSCDETECTORCONSTRUCTION_H

#include "G4VUserDetectorConstruction.hh"
#include "G4Material.hh"

class BGMSCDetectorMessenger;
class G4LogicalVolume;
class G4VPhysicalVolume;

using namespace CLHEP;

class BGMSCDetectorConstruction : public G4VUserDetectorConstruction
{
public:
    BGMSCDetectorConstruction();
    ~BGMSCDetectorConstruction() {}

    G4VPhysicalVolume* Construct();

    void SetSlabMaterial(G4String materialName);
    G4Material* GetSlabMaterial();

    void SetSlabThickness(G4double thickness);
    G4double GetSlabThickness();

 // void ConstructSDandField();
 // This method is used in multi-threaded applications to build
 // per-worker non-shared objects: SensitiveDetectors and Field managers

private:
    void InitializeMaterials();
    void UpdateGeometry();

    BGMSCDetectorMessenger* DetectorMessenger;

    G4LogicalVolume* MaterialLogic;
    std::map <std::string, G4Material*> MaterialMap;
    G4Material* Material;

    G4double SlabThickness;
    G4Material* SlabMaterial;
    G4double SlabMassThickness;
};

#endif

