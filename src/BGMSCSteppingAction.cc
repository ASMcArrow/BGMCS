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
        // G4double value = (G4double)atan((G4double)((G4double)x/(G4double)z));
        // G4cout << (G4double)(aStep->GetTrack()->GetMomentumDirection().getX()) << G4endl;
        // G4cout << "Step size " << aStep->GetStepLength()/cm << G4endl;
        //G4double z = (G4double)(aStep->GetPostStepPoint()->GetPosition().getZ());
        //G4double x = (G4double)(aStep->GetPostStepPoint()->GetPosition().getX());
        G4double value = (G4double)atan((G4double)((G4double)x/(G4double)z));

//        G4cout << "PreStep point " << aStep->GetPreStepPoint()->GetPosition().getZ()/cm <<
//                  " Material is " << aStep->GetPreStepPoint()->GetMaterial()->GetName() << G4endl;
//        G4cout << "PostStep point " << aStep->GetPostStepPoint()->GetPosition().getZ()/cm <<
//                  " Material is " << aStep->GetPostStepPoint()->GetMaterial()->GetName() << G4endl;

        G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
        analysisManager->FillH1(analysisManager->GetNofH1s()-1, value);
    }
}


