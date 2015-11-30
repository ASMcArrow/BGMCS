#include "BGMSCRunAction.hh"

#include "G4RunManager.hh"
#include "G4UnitsTable.hh"
#include "G4SystemOfUnits.hh"
#include "G4Run.hh"
#include "G4TrackingManager.hh"

#include "G4CsvAnalysisManager.hh"

#include <fstream>
#include <sstream>
#include <iostream>

#define _USE_MATH_DEFINES

BGMSCRunAction::BGMSCRunAction(BGMSCDetectorConstruction *geometry) : G4UserRunAction()
{
    Geometry = geometry;
    Openfile.open("Materials.txt");

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

    std::stringstream ss1;
    ss1 << (int)(thickness*1000);
    G4String name = ss1.str();
    Name = material+name;

    std::stringstream ss2;
    ss2 << thickness;
    G4String str = ss2.str();
    G4String title = material+" "+str;

    std::string line, notrelevant;
    G4double sigma;
    std::getline(Openfile, line);

    std::istringstream iss(line);
    iss >> notrelevant >> sigma >> notrelevant;

    G4cout << ceil(sigma) << G4endl;

    analysisManager->CreateH1(Name, Name, 500, (G4double)(-10*mrad), (G4double)(10*mrad), "mrad");
    if (analysisManager->GetNofH1s()-2 >= 0)
        analysisManager->SetH1Activation(analysisManager->GetNofH1s()-2, false);
}

void BGMSCRunAction::EndOfRunAction(const G4Run* aRun)
{
    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();

    analysisManager->Write();
    G4cout << "rms " << Name << " " << analysisManager->GetH1(analysisManager->GetH1Id(Name))->rms() << G4endl;
    analysisManager->CloseFile();
}
