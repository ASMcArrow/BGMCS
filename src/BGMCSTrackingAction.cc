#include "BGMCSTrackingAction.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"
#include "G4UImanager.hh"

BGMCSTrackingAction::BGMCSTrackingAction()
{
    SumTrack = 0;
    NumTrack = 0;
}

void BGMCSTrackingAction::PreUserTrackingAction(const G4Track* aTrack)
{
    G4MUTEXINIT(Mutex);
}

G4double BGMCSTrackingAction::Reset()
{
    G4double range = (G4double)(SumTrack/NumTrack);

    SumTrack = 0;
    NumTrack = 0;

    return range;
}

void BGMCSTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
    if (aTrack->GetTrackID() == 1)
    {
        G4AutoLock l(&Mutex);
        G4ThreeVector length = aTrack->GetPosition();
        NumTrack = NumTrack + 1;
        SumTrack = SumTrack + length.z()-1*mm;
        l.unlock();
    }
}
