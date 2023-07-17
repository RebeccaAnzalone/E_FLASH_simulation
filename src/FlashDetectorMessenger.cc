//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
//////////////////////////////////////////////////////////////////////////////////////////////

#include "FlashDetectorMessenger.hh"
#include "FlashDetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWith3VectorAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"  

/////////////////////////////////////////////////////////////////////////////
FlashDetectorMessenger::FlashDetectorMessenger(FlashDetectorConstruction* detector)
  :flashDetector(detector)
{
    // Change Phantom size
    changeThePhantomDir = new G4UIdirectory("/changePhantom/");
    changeThePhantomDir -> SetGuidance("Command to change the Phantom Size/position");

     // Change Phantom material 
    changeThePhantomMaterialCmd = new G4UIcmdWithAString("/changePhantom/material", this);
    changeThePhantomMaterialCmd -> SetGuidance("Change the Phantom and the detector material"); 
    changeThePhantomMaterialCmd -> SetParameterName("PhantomMaterial", false);
    changeThePhantomMaterialCmd -> SetDefaultValue("G4_WATER");
    changeThePhantomMaterialCmd -> AvailableForStates(G4State_Idle);


    /*  changeThePhantomSizeCmd = new G4UIcmdWith3VectorAndUnit("/changePhantom/size", this);
    changeThePhantomSizeCmd -> SetGuidance("Insert sizes X Y and Z"
	                                   "\n   0 or negative values mean <<Don't change it!>>");
    changeThePhantomSizeCmd -> SetParameterName("PhantomSizeAlongX", 
						"PhantomSizeAlongY", 
						"PhantomSizeAlongZ", false);
    changeThePhantomSizeCmd -> SetDefaultUnit("mm");
    changeThePhantomSizeCmd -> SetUnitCandidates("nm um mm cm"); 
    changeThePhantomSizeCmd -> AvailableForStates(G4State_Idle);


   
    // Change Phantom position
    changeThePhantomPositionCmd = new G4UIcmdWithADoubleAndUnit("/changePhantom/position", this);
    //  changeThePhantomPositionCmd = new G4UIcmdWith3VectorAndUnit("/changePhantom/position", this);
    changeThePhantomPositionCmd -> SetGuidance("Insert X position of the center of the Water Phantom"
						" respect to that of the \"World\""); 
     changeThePhantomPositionCmd -> SetParameterName("PositionX", 
    						    false);

     // changeThePhantomPositionCmd -> SetParameterName("PositionX","PositionY","PositionZ", 
     //						    false);
     
    changeThePhantomPositionCmd -> SetDefaultUnit("mm");
    changeThePhantomPositionCmd -> SetUnitCandidates("um mm cm m"); 
    changeThePhantomPositionCmd -> AvailableForStates(G4State_Idle);
    
    */


    // Change Detector size
    changeTheDetectorDir = new G4UIdirectory("/changeDetector/");
    changeTheDetectorDir -> SetGuidance("Command to change the Detector Size");

// Change Detector material 
    changeTheDetectorMaterialCmd = new G4UIcmdWithAString("/changeDetector/material", this);
    changeTheDetectorMaterialCmd  -> SetGuidance("Change the Phantom and the detector material"); 
    changeTheDetectorMaterialCmd  -> SetParameterName("PhantomMaterial", false);
   
    changeTheDetectorMaterialCmd  -> AvailableForStates(G4State_Idle);

    
    /*  
      changeTheDetectorSizeCmd = new G4UIcmdWithADoubleAndUnit("/changeDetector/gap", this);
    changeTheDetectorSizeCmd -> SetGuidance("Insert width"
	                                   "\n   0 or negative values mean <<Don't change it!>>");
    changeTheDetectorSizeCmd -> SetParameterName("width", 
						 false);
    changeTheDetectorSizeCmd -> SetDefaultUnit("mm");
    changeTheDetectorSizeCmd -> SetUnitCandidates("nm um mm cm"); 
    changeTheDetectorSizeCmd -> AvailableForStates(G4State_Idle);


    
    
     // Change Detector position
    changeTheDetectorPositionCmd = new G4UIcmdWithADoubleAndUnit("/changeDetector/position", this);
   
    changeTheDetectorPositionCmd -> SetGuidance("Insert X position of the center of the detector"
						" respect to that of the \"World\""); 
     changeTheDetectorPositionCmd -> SetParameterName("PositionX", 
    						    false);

 
     
    changeThePhantomPositionCmd -> SetDefaultUnit("mm");
    changeThePhantomPositionCmd -> SetUnitCandidates("um mm cm m"); 
    changeThePhantomPositionCmd -> AvailableForStates(G4State_Idle); 


    
    */
    

    updateCmd = new G4UIcmdWithoutParameter("/changePhantom/update",this);
    updateCmd->SetGuidance("Update Phantom/Detector geometry.");
    updateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
    updateCmd->SetGuidance("if you changed geometrical value(s).");
    updateCmd->AvailableForStates(G4State_Idle);

    updateCmd_d = new G4UIcmdWithoutParameter("/changeDetector/update",this);
    updateCmd_d->SetGuidance("Update Detector geometry.");
    updateCmd_d->SetGuidance("This command MUST be applied before \"beamOn\" ");
    updateCmd_d->SetGuidance("if you changed geometrical value(s).");
    updateCmd_d->AvailableForStates(G4State_Idle);
    


   }

/////////////////////////////////////////////////////////////////////////////
FlashDetectorMessenger::~FlashDetectorMessenger()
{
  /* 
    delete changeThePhantomSizeCmd; 
    delete changeThePhantomPositionCmd; 
  

   
    delete changeTheDetectorSizeCmd; 
    delete changeTheDetectorPositionCmd;*/

  delete changeThePhantomDir;
    delete changeTheDetectorDir;
  
    delete changeThePhantomMaterialCmd;
    delete changeTheDetectorMaterialCmd; 
    
}

/////////////////////////////////////////////////////////////////////////////
void FlashDetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{
	
  /*if( command == changeThePhantomSizeCmd)
    {
	G4ThreeVector size = changeThePhantomSizeCmd -> GetNew3VectorValue(newValue);
	flashDetector -> SetPhantomSize(size.getX(),size.getY(),size.getZ());
    }
  else if (command == changeThePhantomPositionCmd )
  {
     G4double size = changeThePhantomPositionCmd -> GetNewDoubleValue(newValue);
    
         flashDetector -> SetAirGap(size);
  }
  */
  if (command == changeThePhantomMaterialCmd)
  {
      flashDetector -> SetPhantomMaterial(newValue);
  }

    else if (command == changeTheDetectorMaterialCmd)
  {
      flashDetector -> SetDetectorMaterial(newValue);
  }
  
  /* else if (command == changeTheDetectorSizeCmd)
  {
    G4double size = changeTheDetectorSizeCmd -> GetNewDoubleValue(newValue);
    
      flashDetector -> SetAirGap_water_detector(size);
  }
  
   else if (command == changeTheDetectorPositionCmd)
  {
     G4double size = changeTheDetectorPositionCmd -> GetNewDoubleValue(newValue);
     
      flashDetector -> SetDetectorPosition(size);
      }*/

  
  
}
