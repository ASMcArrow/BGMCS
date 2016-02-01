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
#include "BGMSCActionInitialization.hh"
#include "BGMCSUISession.hh"

#include "G4CsvAnalysisManager.hh"
#include "G4LossTableManager.hh"
#include "G4EnergyLossMessenger.hh"

#include <math.h>

// First argument is material
// Second argument is thickness in g/cm2
// Third argument is I

int main(int argc,char** argv)
{
    // Set the custom seed for the random engine
    G4Random::setTheEngine(new CLHEP::RanecuEngine);
    G4long seed = time(NULL);
    G4Random::setTheSeed(seed);

    G4double thickness, I;

    std::stringstream ss;
    ss << argv[2];
    ss >> thickness;
    ss.clear();
    ss << argv[3];
    ss >> I;

    std::cout << argv[1] << " " << thickness << " " << I << std::endl;

#ifdef G4MULTITHREADED
    G4MTRunManager* runManager = new G4MTRunManager;
    runManager->SetNumberOfThreads(8);
#else
    G4RunManager* runManager = new G4RunManager;
#endif

    BGMSCDetectorConstruction* massWorld = new BGMSCDetectorConstruction;
    massWorld->SetSlabMaterial(G4String(argv[1]));
    massWorld->SetSlabThickness(thickness*g/cm2);
    massWorld->SetIForCurrentMaterial(I*eV);
    runManager->SetUserInitialization(massWorld);

    G4VModularPhysicsList* physicsList = new BGMSCPhysicsList;
    physicsList->SetVerboseLevel(0);
    runManager->SetUserInitialization(physicsList);

    BGMSCActionInitialization* actionInit = new BGMSCActionInitialization(massWorld);
    runManager->SetUserInitialization(actionInit);
    runManager->Initialize();
    runManager->SetVerboseLevel(2);

    G4UImanager* UImanager = G4UImanager::GetUIpointer();
    //UImanager->SetCoutDestination(new BGMCSUISession);

#ifdef G4VIS_USE
    G4UIExecutive* ui = new G4UIExecutive(argc, argv);
    G4VisManager* visManager = new G4VisExecutive;
    visManager->Initialize();
    UImanager->ApplyCommand("/control/execute init_vis.mac");
    ui->SessionStart();
    delete ui;
    delete visManager;
#else
    runManager->BeamOn(10000);
#endif

    delete runManager;
    return 0;
}
