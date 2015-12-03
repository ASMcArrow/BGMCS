#ifndef BGMCSTRACKINGACTION_h
#define BGMCSTRACKINGACTION_h

#include "G4UserTrackingAction.hh"

#include "G4SystemOfUnits.hh"
#include "G4UnitsTable.hh"

#include "G4Threading.hh"
#include "G4AutoLock.hh"

class BGMCSTrackingAction : public G4UserTrackingAction {

public:
    BGMCSTrackingAction()
    {
        SumTrack = 0;
        NumTrack = 0;
        I=1;
        NumMat = 0;
    }

    ~BGMCSTrackingAction()
    {
        G4cout << "Tracking Action deleted " << G4endl;
        G4MUTEXDESTROY(Mutex);
    }

    virtual void PreUserTrackingAction(const G4Track*);
    virtual void PostUserTrackingAction(const G4Track*);

    void Reset();

private:
    G4Mutex Mutex;

    G4double SumTrack;
    G4int NumTrack;
    G4int I, NumMat;
    G4double Ranges[20] = {/*11.3912574204*cm, 16.9612403101*cm, 8.6801801802*cm, 14.7225*cm, 15.2168141593*cm, 14.6533333333*cm, 9.5490909091*cm,
                           8.2066666667*cm, 9.2738197425*cm, 2.8931919643*cm, 2.7728089888*cm, 3.6429272396*cm, 3.1034279656*cm, 2.7812745098*cm, 4.1325020554*cm,*/
                           4.068427673*cm, 2.0445783133*cm, 3.1021145374*cm, 1.966631016*cm};
    G4String Materials[20] = {/*"Beryllium", "Polystyrene",  "Carbon", "Lexan", "Nylon", "Lucite", "Teflon", "Aluminum", "Silicon",
                              "Copper", "Nickel", "Zinc", "Brass", "Molybdenum", "Tin", */"Gadolinium", "Tantalum", "Lead", "Uranium"};
};

#endif
