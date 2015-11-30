#include "BGMSCSteppingAction.hh"

#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4CsvAnalysisManager.hh"
#include "G4ThreeVector.hh"

void BGMSCSteppingAction::UserSteppingAction(const G4Step* aStep)
{
    if ((aStep->IsLastStepInVolume())&&(aStep->GetTrack()->GetCreatorProcess() == 0)
            &&(aStep->GetPreStepPoint()->GetMaterial()->GetName()!="Air"))
    {
        G4double z = (G4double)(aStep->GetPostStepPoint()->GetMomentumDirection().getZ());
        G4double x = (G4double)(aStep->GetPostStepPoint()->GetMomentumDirection().getX());
        G4double value = (G4double)atan((G4double)((G4double)x/(G4double)z));

        G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
        // G4cout << "Number of hist " << analysisManager->GetNofH1s()-1 << G4endl;
        analysisManager->FillH1(analysisManager->GetNofH1s()-1, value);
    }
}


