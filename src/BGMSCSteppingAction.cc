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
        G4double z = (G4double)(aStep->GetTrack()->GetMomentumDirection().getZ());
        G4double x = (G4double)(aStep->GetTrack()->GetMomentumDirection().getX());
        G4double value = atan((G4double)(x/z));

        G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
        analysisManager->FillH1(analysisManager->GetNofH1s()-1, value);
    }
}


