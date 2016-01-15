#ifndef BGMCSUISESSION_HH
#define BGMCSUISESSION_HH

#include "G4UIsession.hh"
#include "G4Threading.hh"

class BGMCSUISession : public G4UIsession
{
public:

    G4int ReceiveG4cout(const G4String& coutString);
    //G4int ReceiveG4cerr(const G4String& cerrString);
};

#endif // BGMCSUISESSION_HH
