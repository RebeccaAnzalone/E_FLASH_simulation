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
/// \file FlashDetectorSD.cc
/// \brief Implementation of the FlashDetectorSD class

#include "FlashDetectorSD.hh"
#include "G4HCofThisEvent.hh"
#include "G4Step.hh"
#include "G4ThreeVector.hh"
#include "G4SDManager.hh"
#include "G4ios.hh"
#include "G4RunManager.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorSD::FlashDetectorSD(const G4String& name,
                         const G4String& hitsCollectionName)
 : G4VSensitiveDetector(name),
   fHitsCollection(NULL)
   
{
  collectionName.insert(hitsCollectionName);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorSD::~FlashDetectorSD()
{}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FlashDetectorSD::Initialize(G4HCofThisEvent* hce)
{
  // Create hits collection

  fHitsCollection = new FlashDetectorHitsCollection(SensitiveDetectorName, collectionName[0]);

  // Add this collection in hce
  G4int hcID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  hce->AddHitsCollection( hcID, fHitsCollection );
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool FlashDetectorSD::ProcessHits(G4Step* aStep,
                                     G4TouchableHistory*)
{
  // energy deposit
  //G4double edep = aStep->GetTotalEnergyDeposit();

  //if (edep==0.) return false;
  G4int eventid =
      G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();

  G4StepPoint *postStep = aStep->GetPostStepPoint();
  G4StepPoint *preStep = aStep->GetPreStepPoint();
  G4TouchableHandle touchable = preStep->GetTouchableHandle();
  // Get the track of the current particle
  G4Track* track = aStep->GetTrack();

  if (preStep->GetStepStatus() == fGeomBoundary) {
  // Get the particle name
  G4String particleName = track->GetDefinition()->GetParticleName();

  G4double kineticEnergy = aStep->GetTrack()->GetKineticEnergy();

  G4double pos_x = aStep->GetTrack()->GetPosition().x();
  G4double pos_y = aStep->GetTrack()->GetPosition().y();


  //G4int threadID = G4Threading::G4GetThreadId();

  FlashDetectorHit* newHit = new FlashDetectorHit();



  //newHit->SetTrackID  (aStep->GetTrack()->GetTrackID());
  //newHit->SetChamberNb(aStep->GetPreStepPoint()->GetTouchableHandle()->GetCopyNumber());
  newHit->SeteventID(eventid);
  newHit->SetParticleName(particleName);
  newHit->SetEnergy(kineticEnergy);
  //newHit->SetEdep(edep);
  newHit->SetPosx (pos_x);
  newHit->SetPosy (pos_y);

  newHit->Print();

  fHitsCollection->insert(newHit);

  }

  if (postStep->GetStepStatus() == fGeomBoundary) {
          ((G4Track*)track)->SetTrackStatus(fStopAndKill);
        }

  return true;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FlashDetectorSD::EndOfEvent(G4HCofThisEvent*hce)
{
G4cout << "ciaoooooooo" << G4endl;

G4int threadID = G4Threading::G4GetThreadId();

//  if ( verboseLevel>=1 ) {
     G4int nofHits = fHitsCollection->entries();

     G4cout << "-------->Hits Collection: in this event they are " << nofHits << G4endl;

     // Check if the hit collection exists
if (fHitsCollection) {
    // Get the number of hits in the collection
    G4int numHits = fHitsCollection->GetSize();

    // Print the number of hits
    G4cout << "Number of hits in the collection: " << numHits << G4endl;
} else {
    G4cout << "Hit collection does not exist!" << G4endl;
}

     //for ( G4int i=0; i<nofHits; i++ ) (*fHitsCollection)[i]->Print();
 //}
}


//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
