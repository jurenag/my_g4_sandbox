#include "src/MyPhysicsList.h"
#include "src/MyDetectorConstruction.h"
#include "src/MyEventAction.h"
#include "src/MyPrimaryGenerator.h"

#include <G4RunManager.hh>
#include <G4UImanager.hh>
#include <G4VisExecutive.hh>
#include <G4UIterminal.hh>
#include <G4UItcsh.hh>


int main(int argc, const char * argv[]){
    G4RunManager * pRunMgr = new G4RunManager();
    pRunMgr->SetUserInitialization(new MyPhysicsList());
    pRunMgr->SetUserInitialization(new MyDetectorConstruction());
    pRunMgr->SetUserAction(new MyPrimaryGenerator());
//  pRunMgr->SetUserAction(new MyEventAction());

    pRunMgr->Initialize();

    // If no macro file was provided via command line,
    // start an interactive session.
    if (argc == 1) {
        G4VisManager* vismgr = new G4VisExecutive();
        vismgr->Initialize();
        G4UImanager::GetUIpointer()->
        ApplyCommand("/control/execute mac/vis.mac");
        G4UIsession* session = new G4UIterminal(new G4UItcsh);
        session->SessionStart();
        delete session;
        delete vismgr;
    }
    // We will assume that the first command-line argument is the name
    // of a valid macro file. Any other argument will be ignored.
    else {
        G4String command = "/control/execute " + std::string(argv[1]);
        G4UImanager::GetUIpointer()->ApplyCommand(command);
    }

    // Job termination
    // Free the store: user actions, physics_list and detector_description are
    // owned and deleted by the run manager, so they should not be deleted
    // in the main() program.
    delete pRunMgr;

    return EXIT_SUCCESS;
}