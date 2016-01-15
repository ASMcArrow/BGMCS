#include "BGMCSTrackingAction.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4UImanager.hh"

extern G4double SumTrack;
extern G4int NumTrack;

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
        G4ThreeVector length = aTrack->GetPosition();
        ::NumTrack = ::NumTrack + 1;
        ::SumTrack = ::SumTrack + length.z()-1*mm;
        l.unlock();
    }
}
