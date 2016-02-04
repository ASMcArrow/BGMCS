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
        G4double value = aStep->GetPostStepPoint()->GetMomentumDirection().getTheta();

        G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
        analysisManager->FillH1(analysisManager->GetNofH1s()-1, value);
    }
}


