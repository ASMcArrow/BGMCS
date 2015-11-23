#include "BGMSCRunAction.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"

#include "G4CsvAnalysisManager.hh"

#include <fstream>
#include <sstream>
#include <iostream>

#define _USE_MATH_DEFINES

BGMSCRunAction::BGMSCRunAction(BGMSCDetectorConstruction *geometry) : G4UserRunAction()
{
    Geometry = geometry;

    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->SetActivation(true);
}

BGMSCRunAction::~BGMSCRunAction()
{}

void BGMSCRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;
    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    G4String material = Geometry->GetSlabMaterial()->GetName();
    G4double thickness = Geometry->GetSlabThickness();

    std::stringstream ss;
    ss << (int)(thickness*1000);
    G4String str = ss.str();
    G4String name = material+str;

    G4cout << "id is " << analysisManager->CreateH1(name, name, 500, (G4double)(-20.0*mrad), (G4double)(20.0*mrad), "mrad") << G4endl;
    if (analysisManager->GetNofH1s()-2 >= 0)
        analysisManager->SetH1Activation(analysisManager->GetNofH1s()-2, false);
}

void BGMSCRunAction::EndOfRunAction(const G4Run* aRun)
{
 //   if(!IsMaster()) return;

    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->Write();
    analysisManager->CloseFile();
}
