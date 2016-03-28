#include "BGMSCDetectorConstruction.hh"
#include "BGMSCDetectorMessenger.hh"

#include "G4Material.hh"
#include "G4Box.hh"
#include "G4Tubs.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "G4PVPlacement.hh"
#include "G4PVReplica.hh"
#include "G4NistManager.hh"
#include "G4Transform3D.hh"
#include "G4RotationMatrix.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4GeometryManager.hh"
#include "G4PhysicalVolumeStore.hh"
#include "G4LogicalVolumeStore.hh"
#include "G4SolidStore.hh"
#include "G4RunManager.hh"
#include "G4VSolid.hh"

using namespace CLHEP;

BGMSCDetectorConstruction::BGMSCDetectorConstruction()
{
    this->InitializeMaterials();

    SlabMaterial = MaterialMap["Beryllium"];
    SetSlabThickness(0.0572*(g/cm2));
    DetectorMessenger = new BGMSCDetectorMessenger(this);
}

G4VPhysicalVolume* BGMSCDetectorConstruction::Construct()
{
    // Cleanup old geometry
    G4GeometryManager::GetInstance()->OpenGeometry();
    G4PhysicalVolumeStore::GetInstance()->Clean();
    G4LogicalVolumeStore::GetInstance()->Clean();
    G4SolidStore::GetInstance()->Clean();

    G4VisAttributes* visAttributes = new G4VisAttributes;
    visAttributes->SetForceWireframe(true);

    // World
    G4Box* world = new G4Box("World", 3*m, 3*m, 3*m);
    G4LogicalVolume *worldLogic = new G4LogicalVolume(world, MaterialMap["Air"], "WorldLogic");
    G4VPhysicalVolume *worldPhys = new G4PVPlacement(0, G4ThreeVector(), worldLogic, "WorldPhys", 0, false, 0);
    worldLogic->SetVisAttributes(visAttributes);

    // Material Slab
    G4Box *materialSlab = new G4Box("MaterialSlab", 5*cm, 5*cm, SlabThickness/2.0);
    MaterialLogic = new G4LogicalVolume(materialSlab, SlabMaterial, "MaterialLogic");
    new G4PVPlacement(0, G4ThreeVector(0, 0, (G4double)(SlabThickness/2.0)), MaterialLogic, "MaterialSlab", worldLogic, 0, 0);

    return worldPhys;
}

void BGMSCDetectorConstruction::SetSlabMaterial(G4String materialName)
{
    SlabMaterial = MaterialMap[materialName];
    // MaterialLogic->SetMaterial(MaterialMap[materialName]);
    G4cout << "Command SetSlabMaterial works. The material is set: " << SlabMaterial->GetName() << G4endl;
}

G4Material* BGMSCDetectorConstruction::GetSlabMaterial()
{
    return MaterialLogic->GetMaterial();
}

void BGMSCDetectorConstruction::SetSlabThickness(G4double thickness)
{
    SlabMassThickness = thickness/(g/cm2);
    SlabThickness = (G4double)(thickness/SlabMaterial->GetDensity());
    G4cout << "Command SetSlabThickness works. The thickness is set: " << SlabThickness/cm << " cm from: " << thickness/(g/cm2) << " g/cm2" << G4endl;
}

G4double BGMSCDetectorConstruction::GetSlabThickness()
{
    return SlabMassThickness;
}

void BGMSCDetectorConstruction::SetIForCurrentMaterial(G4double I)
{
    if (I !=0)
        MaterialMap[SlabMaterial->GetName()]->GetIonisation()->SetMeanExcitationEnergy(I);

    G4cout << "Command SetIForCirrentMaterial works. I is set to "<< MaterialMap[SlabMaterial->GetName()]->GetIonisation()->GetMeanExcitationEnergy()/eV << G4endl;
}

G4double BGMSCDetectorConstruction::GetIForCurrentMaterial()
{
    return SlabMaterial->GetIonisation()->GetMeanExcitationEnergy();
}

void BGMSCDetectorConstruction::UpdateGeometry()
{
    G4RunManager::GetRunManager()->DefineWorldVolume(Construct());
}

void BGMSCDetectorConstruction::InitializeMaterials()
{
    G4NistManager* nistManager = G4NistManager::Instance();

    G4Element* H = nistManager->FindOrBuildElement(1);
    G4Element* C = nistManager->FindOrBuildElement(6);
    G4Element* O = nistManager->FindOrBuildElement(8);
    G4Element* N = nistManager->FindOrBuildElement(7);
    G4Element* F = nistManager->FindOrBuildElement(9);
    G4Element* Ar = nistManager->FindOrBuildElement(18);
    G4Element* Cu = nistManager->FindOrBuildElement(29);
    G4Element* Zn = nistManager->FindOrBuildElement(30);
    G4Element* Pb = nistManager->FindOrBuildElement(82);

    G4Material* Water = nistManager->FindOrBuildMaterial("G4_WATER");
    MaterialMap["Water"] = Water;

    // BGMCS Materials

    G4Material* Beryllium = nistManager->FindOrBuildMaterial("G4_Be");
    Beryllium->SetName("Beryllium");
  //  G4Material* Beryllium = new G4Material("Beryllium", 4, 9.012*g/mole, 1.853*g/cm3, kStateSolid);
    MaterialMap["Beryllium"] = Beryllium;

//  G4Material* Polystyrene = new G4Material("Polystyrene", 1.032*g/cm3, 2, kStateSolid);
//  Polystyrene->AddElement(C, 0.923);
//  Polystyrene->AddElement(H, 0.077);
    G4Material* Polystyrene = nistManager->FindOrBuildMaterial("G4_POLYSTYRENE");
    Polystyrene->SetName("Polystyrene");
    MaterialMap["Polystyrene"] = Polystyrene;

//  G4Material* Carbon = new G4Material("Carbon", 6, 12.011*g/mole, 2.22*g/cm3, kStateSolid);
    G4Material* Carbon = nistManager->FindOrBuildMaterial("G4_C");
    Carbon->SetName("Carbon");
    MaterialMap["Carbon"] = Carbon;

    G4Material* Lexan = new G4Material("Lexan", 1.2*g/cm3, 3, kStateSolid);
    Lexan->AddElement(C, 0.741);
    Lexan->AddElement(O, 0.185);
    Lexan->AddElement(H, 0.074);
    MaterialMap["Lexan"] = Lexan;

    G4Material* Nylon = new G4Material("Nylon", 1.13*g/cm3, 4, kStateSolid);
    Nylon->AddElement(C, 0.549);
    Nylon->AddElement(O, 0.244);
    Nylon->AddElement(N, 0.107);
    Nylon->AddElement(H, 0.100);
    MaterialMap["Nylon"] = Nylon;

    G4Material* Lucite = new G4Material("Lucite", 1.2*g/cm3, 3, kStateSolid);
    Lucite->AddElement(C, 0.600);
    Lucite->AddElement(O, 0.320);
    Lucite->AddElement(H, 0.081);
    MaterialMap["Lucite"] = Lucite;

    G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");
    Air->SetName("Air");
    MaterialMap["Air"] = Air;

//  G4Material* Teflon = new G4Material("Teflon", 2.2*g/cm3, 2, kStateSolid);
//  Teflon->AddElement(F, 0.760);
//  Teflon->AddElement(C, 0.240);
    G4Material* Teflon = nistManager->FindOrBuildMaterial("G4_TEFLON");
    Teflon->SetName("Teflon");
    MaterialMap["Teflon"] = Teflon;

//  G4Material* Aluminum = new G4Material("Aluminum", 13, 26.981*g/mole, 2.700*g/cm3, kStateSolid);
    G4Material* Aluminum = nistManager->FindOrBuildMaterial("G4_Al");
    Aluminum->SetName("Aluminum");
    MaterialMap["Aluminum"] = Aluminum;

//  G4Material* Silicon = new G4Material("Silicon", 14, 28.086*g/mole, 2.330*g/cm3, kStateSolid);
    G4Material* Silicon = nistManager->FindOrBuildMaterial("G4_Si");
    Silicon->SetName("Silicon");
    MaterialMap["Silicon"] = Silicon;

//  G4Material* Copper = new G4Material("Copper", 29, 63.540*g/mole, 8.960*g/cm3, kStateSolid);
    G4Material* Copper = nistManager->FindOrBuildMaterial("G4_Cu");
    Copper->SetName("Copper");
    MaterialMap["Copper"] = Copper;

//  G4Material* Nickel = new G4Material("Nickel", 28, 58.710*g/mole, 8.900*g/cm3, kStateSolid);
    G4Material* Nickel = nistManager->FindOrBuildMaterial("G4_Ni");
    Nickel->SetName("Nickel");
    MaterialMap["Nickel"] = Nickel;

//  G4Material* Zinc = new G4Material("Zinc", 30, 65.370*g/mole, 7.133*g/cm3, kStateSolid);
    G4Material* Zinc = nistManager->FindOrBuildMaterial("G4_Zn");
    Zinc->SetName("Zinc");
    MaterialMap["Zinc"] = Zinc;

    G4Material* Brass = new G4Material("Brass", 8.489*g/cm3, 3, kStateSolid);
    Brass->AddElement(Cu, 0.615);
    Brass->AddElement(Zn, 0.352);
    Brass->AddElement(Pb, 0.033);
    MaterialMap["Brass"] = Brass;

//  G4Material* Molybdenum = new G4Material("Molybdenum", 42, 95.940*g/mole, 10.200*g/cm3, kStateSolid);
    G4Material* Molybdenum = nistManager->FindOrBuildMaterial("G4_Mo");
    Molybdenum->SetName("Molybdenum");
    MaterialMap["Molybdenum"] = Molybdenum;

//  G4Material* Tin = new G4Material("Tin", 50, 118.690*g/mole, 7.298*g/cm3, kStateSolid);
    G4Material* Tin = nistManager->FindOrBuildMaterial("G4_Sn");
    Tin->SetName("Tin");
    MaterialMap["Tin"] = Tin;

//  G4Material* Gadolinium = new G4Material("Gadolinium", 64, 157.250*g/mole, 7.950*g/cm3, kStateSolid);
    G4Material* Gadolinium = nistManager->FindOrBuildMaterial("G4_Gd");
    Gadolinium->SetName("Gadolinium");
    MaterialMap["Gadolinium"] = Gadolinium;

//  G4Material* Tantalum = new G4Material("Tantalum", 73, 180.950*g/mole, 16.600*g/cm3, kStateSolid);
    G4Material* Tantalum = nistManager->FindOrBuildMaterial("G4_Ta");
    Tantalum->SetName("Tantalum");
    MaterialMap["Tantalum"] = Tantalum;

//  G4Material* Lead = new G4Material("Lead", 82, 207.190*g/mole, 11.350*g/cm3, kStateSolid);
    G4Material* Lead = nistManager->FindOrBuildMaterial("G4_Pb");
    Lead->SetName("Lead");
    MaterialMap["Lead"] = Lead;

//  G4Material* Uranium = new G4Material("Uranium", 92, 238.030*g/mole, 18.700*g/cm3, kStateSolid);
    G4Material* Uranium = nistManager->FindOrBuildMaterial("G4_U");
    Uranium->SetName("Uranium");
    MaterialMap["Uranium"] = Uranium;
}

//    G4Material* Beryllium = new G4Material("Beryllium", 4, 9.012*g/mole, 1.853*g/cm3, kStateSolid);
//    Beryllium->GetIonisation()->SetMeanExcitationEnergy(58.39*eV);
//    MaterialMap["Beryllium"] = Beryllium;

//    G4Material* Polystyrene = new G4Material("Polystyrene", 1.032*g/cm3, 2, kStateSolid);
//    Polystyrene->AddElement(C, 0.923);
//    Polystyrene->AddElement(H, 0.077);
//    Polystyrene->GetIonisation()->SetMeanExcitationEnergy(62.98*eV);
//    MaterialMap["Polystyrene"] = Polystyrene;

//    G4Material* Carbon = new G4Material("Carbon", 6, 12.011*g/mole, 2.22*g/cm3, kStateSolid);
//    Carbon->GetIonisation()->SetMeanExcitationEnergy(72.92*eV);
//    MaterialMap["Carbon"] = Carbon;

//    G4Material* Lexan = new G4Material("Lexan", 1.2*g/cm3, 3, kStateSolid);
//    Lexan->AddElement(C, 0.741);
//    Lexan->AddElement(O, 0.185);
//    Lexan->AddElement(H, 0.074);
//    Lexan->GetIonisation()->SetMeanExcitationEnergy(67.01*eV);
//    MaterialMap["Lexan"] = Lexan;

//    G4Material* Nylon = new G4Material("Nylon", 1.13*g/cm3, 4, kStateSolid);
//    Nylon->AddElement(C, 0.549);
//    Nylon->AddElement(O, 0.244);
//    Nylon->AddElement(N, 0.107);
//    Nylon->AddElement(H, 0.100);
//    Nylon->GetIonisation()->SetMeanExcitationEnergy(64.75*eV);
//    MaterialMap["Nylon"] = Nylon;

//    G4Material* Lucite = new G4Material("Lucite", 1.2*g/cm3, 3, kStateSolid);
//    Lucite->AddElement(C, 0.600);
//    Lucite->AddElement(O, 0.320);
//    Lucite->AddElement(H, 0.081);
//    Nylon->GetIonisation()->SetMeanExcitationEnergy(62.83*eV);
//    MaterialMap["Lucite"] = Lucite;

    // G4Material* Air = nistManager->FindOrBuildMaterial("G4_AIR");
//    G4Material* Air = new G4Material("Air", 0.001*g/cm3, 3, kStateGas);
//    Air->AddElement(N, 0.745);
//    Air->AddElement(O, 0.229);
//    Air->AddElement(Ar, 0.026);
//    Air->GetIonisation()->SetMeanExcitationEnergy(85.7*eV);
//    MaterialMap["Air"] = Air;

//    G4Material* Teflon = new G4Material("Teflon", 2.2*g/cm3, 2, kStateSolid);
//    Teflon->AddElement(F, 0.760);
//    Teflon->AddElement(C, 0.240);
//    Teflon->GetIonisation()->SetMeanExcitationEnergy(109.01*eV);
//    MaterialMap["Teflon"] = Teflon;

//    G4Material* Aluminum = new G4Material("Aluminum", 13, 26.981*g/mole, 2.700*g/cm3, kStateSolid);
//    Carbon->GetIonisation()->SetMeanExcitationEnergy(152.17*eV);
//    MaterialMap["Aluminum"] = Aluminum;

//    G4Material* Silicon = new G4Material("Silicon", 14, 28.086*g/mole, 2.330*g/cm3, kStateSolid);
//    Silicon->GetIonisation()->SetMeanExcitationEnergy(158.58*eV);
//    MaterialMap["Silicon"] = Silicon;

//    G4Material* Copper = new G4Material("Copper", 29, 63.540*g/mole, 8.960*g/cm3, kStateSolid);
//    Copper->GetIonisation()->SetMeanExcitationEnergy(295.17*eV);
//    MaterialMap["Copper"] = Copper;

//    G4Material* Nickel = new G4Material("Nickel", 28, 58.710*g/mole, 8.900*g/cm3, kStateSolid);
//    Nickel->GetIonisation()->SetMeanExcitationEnergy(285.08*eV);
//    MaterialMap["Nickel"] = Nickel;

//    G4Material* Zinc = new G4Material("Zinc", 30, 65.370*g/mole, 7.133*g/cm3, kStateSolid);
//    Zinc->GetIonisation()->SetMeanExcitationEnergy(302.5*eV);
//    MaterialMap["Zinc"] = Zinc;

//    G4Material* Brass = new G4Material("Brass", 8.489*g/cm3, 3, kStateSolid);
//    Brass->AddElement(Cu, 0.615);
//    Brass->AddElement(Zn, 0.352);
//    Brass->AddElement(Pb, 0.033);
//    Brass->GetIonisation()->SetMeanExcitationEnergy(329.69*eV);
//    MaterialMap["Brass"] = Brass;

//    G4Material* Molybdenium = new G4Material("Molybdenum", 42, 95.940*g/mole, 10.200*g/cm3, kStateSolid);
//    Molybdenium->GetIonisation()->SetMeanExcitationEnergy(388.67*eV);
//    MaterialMap["Molybdenum"] = Molybdenium;

//    G4Material* Tin = new G4Material("Tin", 50, 118.690*g/mole, 7.298*g/cm3, kStateSolid);
//    Tin->GetIonisation()->SetMeanExcitationEnergy(447.33*eV);
//    MaterialMap["Tin"] = Tin;

//    G4Material* Gadolinium = new G4Material("Gadolinium", 64, 157.250*g/mole, 7.950*g/cm3, kStateSolid);
//    Gadolinium->GetIonisation()->SetMeanExcitationEnergy(541.75*eV);
//    MaterialMap["Gadolinium"] = Gadolinium;

//    G4Material* Tantalim = new G4Material("Tantalum", 73, 180.950*g/mole, 16.600*g/cm3, kStateSolid);
//    Tantalim->GetIonisation()->SetMeanExcitationEnergy(688.08*eV);
//    MaterialMap["Tantalum"] = Tantalim;

//    G4Material* Lead = new G4Material("Lead", 82, 207.190*g/mole, 11.350*g/cm3, kStateSolid);
//    Lead->GetIonisation()->SetMeanExcitationEnergy(754.42*eV);
//    MaterialMap["Lead"] = Lead;

//    G4Material* Uranium = new G4Material("Uranium", 92, 238.030*g/mole, 18.700*g/cm3, kStateSolid);
//    Uranium->GetIonisation()->SetMeanExcitationEnergy(815.83*eV);
//    MaterialMap["Uranium"] = Uranium;



