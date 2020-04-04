#include <stdexcept>
#include <iostream>
#include "globals.hh"

#include "G4RunManager.hh"
#include "G4UImanager.hh"
#include "G4UIterminal.hh"
#include "G4UItcsh.hh"

#include "DetectorConstruction.hh"
#include "PhysicsList.hh"
#include "PrimaryGeneratorAction.hh"
#include "EventAction.hh"
#include "SteppingAction.hh"
#include "AnalysisManager.hh"
#include "G4TrajectoryDrawByParticleID.hh"

#ifdef G4VIS_USE
#include "G4VisExecutive.hh"
#endif

//---------------------------------------------------------------------------

int main(int argc, char** argv)
{
std::cout<<"Begining of main() of AnaBarMC.cc"<<std::endl;

  G4RunManager* runManager = new G4RunManager;
  PhysicsList*  phys       = new PhysicsList();
  runManager->SetUserInitialization(phys);
  
std::cout<<"anaManger is being created"<<std::endl;
  AnalysisManager*        anaManager = new AnalysisManager();
std::cout<<"detCon is being created"<<std::endl;
  DetectorConstruction*   detCon     = new DetectorConstruction();
  runManager->SetUserInitialization(detCon);
  std::cout<<"PrimaryGeneratorAction is going"<<std::endl;
std::cout<<"PrimaryGeneratorAction is going"<<std::endl;
  PrimaryGeneratorAction* pga        = new PrimaryGeneratorAction();
  runManager->SetUserAction(pga);
std::cout<<"SteppingAction is going"<<std::endl;
  SteppingAction*         step       = new SteppingAction();
  runManager->SetUserAction(step);
std::cout<<"EventAction is going"<<std::endl;
  EventAction*            event      = new EventAction( anaManager, pga );
  runManager->SetUserAction(event);

std::cout<<"VisManager is going"<<std::endl;
  G4UImanager * UI         = G4UImanager::GetUIpointer();
  G4VisManager* visManager = 0;

std::cout<<"VisManager was setup"<<std::endl;
  if (argc==1)   // Define UI session for interactive mode.
    {
      std::cout<<"argc==1"<<std::endl;
#ifdef G4VIS_USE
      std::cout<<"About to create VisManager"<<std::endl;
      visManager = new G4VisExecutive;
      std::cout<<"About to initialize VisManager"<<std::endl;
      visManager->Initialize();

#endif
      std::cout<<"Setting session = 0"<<std::endl;
      G4UIsession * session = 0;
#ifdef G4UI_USE_TCSH
      std::cout<<"session is a uiterminal"<<std::endl;
      session = new G4UIterminal(new G4UItcsh);
#else
      std::cout<<"session is a different uiterminal"<<std::endl;
      session = new G4UIterminal();
#endif
      std::cout<<"start session"<<std::endl;
      session->SessionStart();
      std::cout<<"delete session"<<std::endl;
      delete session;
      std::cout<<"session was deleted"<<std::endl;
    }
  else           // Batch mode
    {
      std::cout<<"Else: entering batch mode??"<<std::endl;
      G4String command = "/control/execute ";
      std::cout<<"Set fileName"<<std::endl;
      G4String fileName = argv[1];
      std::cout<<"apply ui command"<<std::endl;
      UI->ApplyCommand(command+fileName);
      std::cout<<"enter if statement??"<<std::endl;
      if( pga->GetMode()==EPGA_ROOT ) {
        std::cout<<"have enterd the if statement"<<std::endl;
	G4String commandr = "/run/beamOn ";
        std::cout<<"get number of events"<<std::endl;
	G4int nev = pga->GetNEvents();
        std::cout<<"create a char snev"<<std::endl;
	char snev[50];
        std::cout<<"change that char"<<std::endl;
	sprintf( snev, "%d",nev );
        std::cout<<"apply another ui command"<<std::endl;
	UI->ApplyCommand(commandr+snev);
        std::cout<<"done with the if block"<<std::endl;
      }
    }

std::cout<<"VisManager is being deleted next"<<std::endl;
  if(visManager) delete visManager;
std::cout<<"anaManger is being deleted next"<<std::endl;
  delete anaManager;
std::cout<<"anaManger has been deleted"<<std::endl;
  delete runManager;

  return 0;
}

//---------------------------------------------------------------------------
