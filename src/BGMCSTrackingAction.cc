#include "BGMCSTrackingAction.hh"
#include "G4Track.hh"
#include "G4TrackStatus.hh"

void BGMCSTrackingAction::PreUserTrackingAction(const G4Track*)
{
    G4MUTEXINIT(mutex);
}

void BGMCSTrackingAction::Reset()
{
//    G4cout << "sumTrack is " << sumTrack/cm << " numTrack is " << numTrack << G4endl;
//    G4cout << (G4double)((sumTrack/cm)/numTrack) << G4endl;

//    std::ofstream file;
//    file.open("ProjRanges.txt", std::ios_base::app | std::ios_base::out);
//    file << i << " " << (G4double)((sumTrack/cm)/numTrack) << "\n";
//    file.close();

//    sumTrack = 0;
//    numTrack = 0;
//    i = i + 1;
}

void BGMCSTrackingAction::PostUserTrackingAction(const G4Track* aTrack)
{
//    if (aTrack->GetTrackID() == 1)
//    {
//        G4AutoLock l(&mutex);
//        G4ThreeVector length = aTrack->GetPosition();
//        numTrack = numTrack + 1;
//        sumTrack = sumTrack + length.z();
//    }
}


