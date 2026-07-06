#include "G4RunManagerFactory.hh"
#include "G4UImanager.hh"
#include "DetectorConstruction.hh"
#include "ActionInitialization.hh"
#include "G4VisExecutive.hh"
#include "G4UIExecutive.hh"
#include "PhysicsList.hh"
#include "G4AnalysisManager.hh"
#include "TThread.h"

int main(int argc, char **argv) {     
     
     //Initialize MT
     TThread::Initialize();

     //Detect interactive mode (if no arguments) and define UI session
     G4UIExecutive *ui = nullptr;
     if (argc == 1) ui = new G4UIExecutive(argc, argv);

     //Set random seed number
     G4Random::setTheSeed(time(nullptr));

     //Construct the default run manager
     auto runManager = G4RunManagerFactory::CreateRunManager(G4RunManagerType::Default);

     //Apply MT mode
#ifdef G4MULTITHREAD
     runManager -> SetNumberOfThreads(10);   //10 cores
     auto AM = G4AnalysisManager::Instance();
     AM -> SetNtupleMerging(true);
#endif

     //Set mandatory initialization classes
     runManager->SetUserInitialization(new DetectorConstruction());
     runManager->SetUserInitialization(new PhysicsList());
     runManager->SetUserInitialization(new ActionInitialization());

     //Initialize G4 kernel
     runManager->Initialize();

     //Get the pointer to the User Interface manager
     auto UImanager = G4UImanager::GetUIpointer();

     //Process macro or start UI session
     if (ui) {
	 auto visManager = new G4VisExecutive;
         visManager->Initialize();
         //interactive mode
         UImanager->ApplyCommand("/control/execute vis.mac");
         ui->SessionStart();
         delete ui;
	 delete visManager;
     }

     else {
         //batch mode
         G4String command = "/control/execute ";
         G4String filename = argv[1];
         UImanager->ApplyCommand(command + filename);
     }
   

     auto AM = G4AnalysisManager::Instance();

     if (AM -> IsOpenFile()) {
        AM -> Write();
        AM -> CloseFile();
     }

     delete runManager;

     return 0;
}
