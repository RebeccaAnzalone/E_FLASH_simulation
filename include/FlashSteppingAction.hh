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
/// \file FlashSteppingAction.hh
/// \brief Definition of the FlashSteppingAction class

#ifndef FlashSteppingAction_h
#define FlashSteppingAction_h 1

#include "G4UserSteppingAction.hh"
#include "globals.hh"
#include <fstream>
class FlashEventAction;

class G4LogicalVolume;

class FlashSteppingAction : public G4UserSteppingAction {
public:
  FlashSteppingAction(FlashEventAction *eventAction);
  virtual ~FlashSteppingAction();

  virtual void UserSteppingAction(const G4Step *);

private:
  std::ofstream KinEnFile;
  std::ofstream KinEnElectronFile;
  std::ofstream Gamma_ann_stepFile;
  std::ofstream step_on_detector_File;
  std::ofstream step_in_phantom_File;
  
    std::ofstream KinEnFile_2;
  std::ofstream OpticFiber;
  std::ofstream OpticInfo;
  G4int ThreadNumber;
  G4int fparticlecount;
  FlashEventAction *fEventAction;
  
  G4int fAnnihilation;
};

#endif
