#include "BGMCSTrackingAction.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"

void BGMCSTrackingAction::PreUserTrackingAction(const G4Track*)
{
    G4MUTEXINIT(Mutex);
}

void BGMCSTrackingAction::Reset()
{
    G4cout << "sumTrack is " << SumTrack/cm << " numTrack is " << NumTrack << G4endl;
    G4cout << (G4double)((SumTrack/cm)/NumTrack) << G4endl;

    std::ofstream file;
    file.open("Ranges.txt", std::ios_base::app | std::ios_base::out);
    file << Materials[NumMat] << " " << (G4double)((SumTrack/cm)/NumTrack) << " " <<
            Ranges[NumMat]/cm << " " << (G4double)((Ranges[NumMat]/cm - SumTrack/cm/NumTrack)/(Ranges[NumMat]/cm))*100.0 << "\n";
    file.close();

    SumTrack = 0;
    NumTrack = 0;
    NumMat = NumMat+1;
}

void BGMCSTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
    if (aTrack->GetTrackID() == 1)
    {
        G4AutoLock l(&Mutex);
        G4ThreeVector length = aTrack->GetPosition();
        NumTrack = NumTrack + 1;
        SumTrack = SumTrack + length.z();
        l.unlock();
    }
}


