// #undef G4MULTITHREADED

#undef G4VIS_USE

#include <cstdio>
#include <ctime>

#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

#include "G4UImanager.hh"
#ifdef G4UI_USE
#include "G4UIExecutive.hh"
#endif

#include "BGMSCPhysicsList.hh"
#include "BGMSCDetectorConstruction.hh"
#include "BGMSCPrimaryGeneratorAction.hh"
#include "BGMSCEventAction.hh"
#include "BGMSCRunAction.hh"
#include "BGMCSTrackingAction.hh"
#include "BGMCSTrackingActionMessenger.hh"
#include "BGMSCActionInitialization.hh"

#include "G4CsvAnalysisManager.hh"
#include "G4LossTableManager.hh"
#include "G4EnergyLossMessenger.hh"

#include <math.h>

static G4double Sigma;

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(8);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    BGMSCDetectorConstruction* massWorld = new BGMSCDetectorConstruction;
    runManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new BGMSCPhysicsList;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);

    BGMCSTrackingAction* trackingAction = new BGMCSTrackingAction;
    BGMCSTrackingActionMessenger* trackingActionMessenger = new BGMCSTrackingActionMessenger(trackingAction);

    BGMSCActionInitialization* actionInit = new BGMSCActionInitialization(massWorld, trackingAction);
    runManager->SetUserInitialization(actionInit);
    runManager->Initialize();
    runManager->SetVerboseLevel(0);

    G4UImanager* UImanager = G4UImanager::GetUIpointer();

#ifdef G4VIS_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
    delete visManager;
#else
    //    std::ifstream openfile("Materials.txt");
    //    std::string line;
    //    G4double sigma;
    //    while (std::getline(openfile, line))
    //    {
    //        std::string material = "";
    //        std::string thickness = "";

    //        std::istringstream iss(line);
    //        iss >> thickness >> sigma >> material;

    //        G4cout << material << " " << thickness << G4endl;

    //        if(!material.empty())
    //            UImanager->ApplyCommand("/BGMSC/det/setSlabMaterial "+material);
    //        UImanager->ApplyCommand("/BGMSC/det/setSlabThickness "+thickness);
    //        UImanager->ApplyCommand("/run/reinitializeGeometry");
    //        UImanager->ApplyCommand("/run/beamOn 1000");
    //    }

    G4double Ranges[20] = {11.3912574204*cm, 16.9612403101*cm, 8.6801801802*cm, 14.7225*cm, 15.2168141593*cm, 14.6533333333*cm, 9.5490909091*cm,
                           8.2066666667*cm, 9.2738197425*cm, 2.8931919643*cm, 2.7728089888*cm, 3.6429272396*cm, 3.1034279656*cm, 2.7812745098*cm, 4.1325020554*cm,
                           4.068427673*cm, 2.0445783133*cm, 3.1021145374*cm, 1.966631016*cm};
    G4double Thickness[20] = {60, 40, 50, 40, 200, 40, 60, 60, 60, 60, 60,
                              60, 60, 70, 70, 80, 80, 80, 80};
    G4String Materials[20] = {"Beryllium", "Polystyrene",  "Carbon", "Lexan", "Nylon", "Lucite", "Teflon", "Aluminum", "Silicon",
                              "Copper", "Nickel", "Zinc", "Brass", "Molybdenum", "Tin", "Gadolinium", "Tantalum", "Lead", "Uranium"};
    //        for (G4int i = 0; i < 20; i++)
    //        {
    //            // First find I that yields bigger range than experimental
    G4double roof_range = 0;

    //            std::stringstream ss1;
    //            ss1 << Thickness[i];
    //            G4String thickness_str = ss1.str();

    UImanager->ApplyCommand("/BGMSC/det/setSlabMaterial Beryllium"/*+Materials[i]*/);
    UImanager->ApplyCommand("/BGMSC/det/setSlabThickness 60"/*+thickness_str*/);

    G4double I = massWorld->GetIForCurrentMaterial()/eV;

    while (roof_range < Ranges[0])
    {
        std::stringstream ss2;
        ss2 << I;
        G4String I_str = ss2.str();

       // UImanager->ApplyCommand("/BGMSC/det/setI "+I_str);
        UImanager->ApplyCommand("/run/reinitializeGeometry");
        UImanager->ApplyCommand("/run/physicsModified");
        //            UImanager->ApplyCommand("/run/initialize");
        UImanager->ApplyCommand("/run/beamOn 10000");

        roof_range = trackingAction->Reset();

        std::ofstream file;
        file.open("Debug.txt", std::ios_base::app | std::ios_base::out);
        // file << "I is " << I << "\n";
        file << "I from DetectorConstruction is " << massWorld->GetIForCurrentMaterial()/eV << "\n";
        file << "range is " << Ranges[0] << " roof_range is " << roof_range << "\n";
        file.close();

        I = I*1.5;
    }

    // G4cout << "Exp range is " << Ranges[i] << " roof_range is " << roof_range << " new I is " << I << G4endl;
    //}
#endif

    delete runManager;
    return 0;
}
