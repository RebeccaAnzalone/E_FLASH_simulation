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
/// \file FlashStackingAction.cc
/// \brief Implementation of the FlashStackingAction class

#include "FlashStackingAction.hh"

#include "FlashDetectorConstruction.hh"
#include "FlashEventAction.hh"
#include "FlashRunAction.hh"
#include "G4Electron.hh"
#include "G4Event.hh"
#include "G4Gamma.hh"
#include "G4LogicalVolume.hh"
#include "G4OpticalPhoton.hh"


#include "G4Electron.hh"
#include "G4Gamma.hh"
#include "G4ParticleDefinition.hh"
#include "G4ParticleTypes.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4Track.hh"
#include "G4VProcess.hh"
#include "G4ios.hh"
#include <sstream>
#include <string>


FlashStackingAction::FlashStackingAction()
    : G4UserStackingAction(), fScintillationCounter(0), fCerenkovCounter(0),
      fBremstralung(0), fFluo(0), fAnnihilation(0) {
  std::ostringstream oss_1;
  oss_1 << "detectorgamma_" << G4Threading::G4GetThreadId() << ".csv";
  std::string filename_1 = oss_1.str();

  DetectorGammaFile.open(filename_1, std::ios_base::app);

  std::ostringstream oss_2;
  oss_2 << "detectorelectron_" << G4Threading::G4GetThreadId() << ".csv";
  std::string filename_2 = oss_2.str();

  DetectorElectronFile.open(filename_2, std::ios_base::app);
}

FlashStackingAction::~FlashStackingAction() { DetectorGammaFile.close();
                                              DetectorElectronFile.close();}

G4ClassificationOfNewTrack
FlashStackingAction::ClassifyNewTrack(const G4Track *aTrack) {


  G4double kineticEnergy = aTrack->GetKineticEnergy();
  G4double pos_x = aTrack->GetPosition().x();
  G4double pos_y = aTrack->GetPosition().y();
  G4double pos_z = aTrack->GetPosition().z();
  G4double cos_x = aTrack->GetMomentum().x();
  G4double cos_y = aTrack->GetMomentum().y();
  G4double cos_z = aTrack->GetMomentum().z();

  //G4String particleName = aTrack->GetDynamicParticle()->GetParticleDefinition()->GetParticleName();
  //G4String particleName = particleDefinition->GetParticleName();

  //G4String particleName = aTrack->GetDefinition()->GetParticleName();
  if(aTrack->GetDefinition()==G4Gamma::GammaDefinition()){
  G4String procName = aTrack->GetCreatorProcess()->GetProcessName();

  if(aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
  "DetectorLog"){


    G4int eventid =
        G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


  if (DetectorGammaFile.is_open()) {

    DetectorGammaFile << "Gamma on detector"
              << "\t" << eventid << "\t" << kineticEnergy << "\t" << pos_x << "\t" << pos_y << "\t" << pos_z
              << "\t" << procName << G4endl;
  }
 }
}
  /*
  else if(aTrack->GetCreatorProcess()->GetProcessName()== "eBrem")
  {
  fBremstralung++;
  }
  else if (aTrack->GetCreatorProcess()->GetProcessName()== "eIoni")
  {
  fFluo++;
  }*/


  return fUrgent; }

  G4ClassificationOfNewTrack
  FlashStackingAction::ClassifyNewTrack1(const G4Track *aTrack) {


    G4double kineticEnergy = aTrack->GetKineticEnergy();
    G4double pos_x = aTrack->GetPosition().x();
    G4double pos_y = aTrack->GetPosition().y();
    G4double pos_z = aTrack->GetPosition().z();
    G4double cos_x = aTrack->GetMomentum().x();
    G4double cos_y = aTrack->GetMomentum().y();
    G4double cos_z = aTrack->GetMomentum().z();

    if(aTrack->GetDefinition()==G4Electron::ElectronDefinition()){

    G4String procName = aTrack->GetCreatorProcess()->GetProcessName();
    if(aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
    "DetectorLog"){


      G4int eventid =
          G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();


    if (DetectorElectronFile.is_open()) {

      DetectorElectronFile << "Electron on detector"
                << "\t" << eventid << "\t" << kineticEnergy << "\t" << pos_x << "\t" << pos_y << "\t" << pos_z
                << "\t" << procName << G4endl;
    }
   }
  }

    return fUrgent; }

  /*if(aTrack->GetDefinition()==G4Gamma::GammaDefinition()){
  if((aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
  "OF_core_LV"||aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
  "OF_clad_LV"||aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
  "OF_cladding_LV") || aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
  "CrystalLV" ){

  if(aTrack->GetCreatorProcess()->GetProcessName()== "eBrem")
  {
  fBremstralung++;
  }
  else if (aTrack->GetCreatorProcess()->GetProcessName()== "eIoni")
  {
  fFluo++;
  }
  }
  }
  if (aTrack->GetDefinition() == G4OpticalPhoton::OpticalPhotonDefinition()) {
    if ((aTrack->GetVolume()->GetLogicalVolume()->GetName() == "OF_core_LV" ||
         aTrack->GetVolume()->GetLogicalVolume()->GetName() == "OF_clad_LV" ||
         aTrack->GetVolume()->GetLogicalVolume()->GetName() ==
             "OF_cladding_LV") ||
        aTrack->GetVolume()->GetLogicalVolume()->GetName() == "CrystalLV") {

      if (aTrack->GetCreatorProcess()->GetProcessName() == "Scintillation") {
        if (aTrack->GetParentID() == 1) {
          fScintillationCounter++;
        } else if (aTrack->GetParentID() > 1) {
          fBremstralung++;
        }
        fScintillationCounter++;
       if (OpticFile.is_open()) {

   OpticFile
       << "event ID: "
       << G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()
       << "\t"
       << "scintillation parent id:" << aTrack->GetParentID() << G4endl;
       //<< "Secondary Scintillation events: "<<fBremstralung<<"\t"
       //<<"Secondary Cerenkov Events: "<<fFluo<< G4endl;
 }
      }
      if (aTrack->GetCreatorProcess()->GetProcessName() == "Cerenkov") {
        if (aTrack->GetParentID() == 1) {
          fCerenkovCounter++;
        } else if (aTrack->GetParentID() > 1) {
          fFluo++;
        }
        fCerenkovCounter++;
if (OpticFile.is_open()) {

OpticFile
<< "event ID: "
<< G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()
<< "\t"
<< "cerenkov parent id:" << aTrack->GetParentID() << G4endl;
//<< "Secondary Scintillation events: "<<fBremstralung<<"\t"
//<<"Secondary Cerenkov Events: "<<fFluo<< G4endl;
}
      }
    } else
      return fKill;
  }

  return fUrgent;
}

void FlashStackingAction::NewStage()

{
  if (fScintillationCounter != 0 || fCerenkovCounter != 0) {

    if (OpticFile.is_open()) {

      OpticFile
          << "event ID: "
          << G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID()
          << "\t"
          << "Primary scintillation events:" << fScintillationCounter << "\t"
          << "Primary Cerenkov events: " << fCerenkovCounter << "\t"
          << "Secondary Scintillation events: " << fBremstralung << "\t"
          << "Secondary Cerenkov Events: " << fFluo << G4endl;
    }
  }
}

void FlashStackingAction::PrepareNewEvent() {
  fScintillationCounter = 0;
  fCerenkovCounter = 0;
} */
