#include "BGMCSTrackingAction.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4UImanager.hh"
#include "G4CsvAnalysisManager.hh"

BGMCSTrackingAction::BGMCSTrackingAction()
{
    G4MUTEXINIT(Mutex);
}

void BGMCSTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{}

void BGMCSTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
    if (aTrack->GetTrackID() == 1)
    {
        G4AutoLock l(&Mutex);
        G4ThreeVector path = aTrack->GetPosition();
        G4double length = path.z()-1*mm;
        G4double density = aTrack->GetMaterial()->GetDensity()/(g/cm3);
        G4double value = length/cm*density;

        G4CsvAnalysisManager* analysisManager = G4CsvAnalysisManager::Instance();
        analysisManager->FillH1(analysisManager->GetH1Id("ProjectedRangeHist"), value);

        l.unlock();
    }
}
