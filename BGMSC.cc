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
    std::ifstream openfile("Materials.txt");
    std::string line;
    G4double sigma;
    while (std::getline(openfile, line))
    {
        std::string material = "";
        std::string thickness = "";

        std::istringstream iss(line);
        iss >> thickness >> sigma >> material;

        G4cout << material << " " << thickness << G4endl;

        if(!material.empty())
            UImanager->ApplyCommand("/BGMSC/det/setSlabMaterial "+material);
        UImanager->ApplyCommand("/BGMSC/det/setSlabThickness "+thickness);
        UImanager->ApplyCommand("/run/reinitializeGeometry");
        UImanager->ApplyCommand("/run/beamOn 10000");
    }
    // UImanager->ApplyCommand("/control/execute ranges.mac");
#endif

    delete runManager;
    return 0;
}
