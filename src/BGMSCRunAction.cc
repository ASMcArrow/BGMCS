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

    std::stringstream ss;
    ss << (int)(thickness*1000);
    G4String name = ss.str();
    Name = material+name;

    std::string line, notrelevant;
    G4double sigma;
    std::getline(Openfile, line);

    std::istringstream iss(line);
    iss >> notrelevant >> sigma >> notrelevant;

    std::stringstream ss2;
    ss2 << thickness << " " << sigma << " ";
    G4String str = ss2.str();
    G4String title = material+" "+str;
    G4cout << "Title is " << title << G4cout;

    G4cout << ceil(sigma) << G4endl;

    G4cout << "id is " << analysisManager->CreateH1(Name, title, 1000, (G4double)(0*mrad), (G4double)(2.5*ceil(sigma)*mrad), "mrad") << G4endl;
    if (analysisManager->GetNofH1s()-2 >= 0)
        analysisManager->SetH1Activation(analysisManager->GetNofH1s()-2, false);
}

void BGMSCRunAction::EndOfRunAction(const G4Run* aRun)
{
    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();

    analysisManager->Write();

    if (isMaster)
    {
        std::ofstream file;
        file.open("RMS.txt", std::ios_base::app | std::ios_base::out);
        file << Name << " " << analysisManager->GetH1(analysisManager->GetH1Id(Name))->rms() << "\n";
        file.close();

        G4cout << "rms = " << analysisManager->GetH1(analysisManager->GetH1Id(Name))->rms() << G4endl;
    }

    analysisManager->CloseFile();
}
