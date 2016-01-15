#include "BGMCSUISession.hh"

#include <fstream>
#include <sstream>
#include <string>
#include <iostream>

using namespace G4Threading;

G4int BGMCSUISession::ReceiveG4cout(const G4String& coutString)
{
    std::ofstream file;
    file.open("Dump.txt", std::ios_base::app | std::ios_base::out);
    file << coutString;
    file.close();

    return 0;
}
