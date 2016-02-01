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
    Num_bins = 10000;

    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->SetActivation(true);
}

BGMSCRunAction::~BGMSCRunAction()
{}

void BGMSCRunAction::BeginOfRunAction(const G4Run* aRun)
{
    G4cout << "### Run " << aRun->GetRunID() << " start." << G4endl;

    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->CreateH1("ProjectedRangeHist", "ProjectedRangeHist", Num_bins, 0.0, Geometry->GetSlabThickness());
}

void BGMSCRunAction::EndOfRunAction(const G4Run* aRun)
{
    G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
    analysisManager->Write();

    if (isMaster)
    {
        G4int max = analysisManager->GetH1(analysisManager->GetH1Id("ProjectedRangeHist"))->max_bin_height();
        G4int index = 0;

        for (G4int i = 0; i < Num_bins; i++)
        {
            if (analysisManager->GetH1(analysisManager->GetH1Id("ProjectedRangeHist"))->bins_entries()[i] == max)
                index = i;
        }

        G4double range = analysisManager->GetH1(analysisManager->GetH1Id("ProjectedRangeHist"))->bin_center(index);

        std::ofstream file("Output.txt", std::ios::app);
        file << range << " " << Geometry->GetIForCurrentMaterial()/eV << "\n";
        file.close();
    }

    analysisManager->CloseFile();
}
