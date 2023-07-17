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
/// \file FlashDetectorHit.cc
/// \brief Implementation of the FlashDetectorHit class

#include "FlashDetectorHit.hh"
#include "G4UnitsTable.hh"
#include "G4VVisManager.hh"
#include "G4Circle.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4Threading.hh"

#include <iomanip>
#include <sstream>
#include <string>

G4ThreadLocal G4Allocator<FlashDetectorHit>* FlashDetectorHitAllocator=0;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorHit::FlashDetectorHit()
 : G4VHit(),
   ThreadNumber(G4Threading::G4GetThreadId()),
   //fTrackID(-1),
   //fChamberNb(-1),
   feventID(0),
   fParticleName(G4String()),
   fEnergy(0.),
   fPosx(),
   fPosy()
{std::ostringstream oss;
oss << "Hits_" << ThreadNumber << ".csv";
std::string filename_1 = oss.str();

HitsFile.open(filename_1, std::ios_base::app);  }

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorHit::~FlashDetectorHit() {HitsFile.close();}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorHit::FlashDetectorHit(const FlashDetectorHit& right)
  : G4VHit()
{
  feventID = right.feventID;
  fParticleName = right.fParticleName;
  fEnergy = right.fEnergy;
  fPosx =right.fPosx;
  fPosy = right.fPosy;
  /*
  fTrackID   = right.fTrackID;
  //fChamberNb = right.fChamberNb;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
  */
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

const FlashDetectorHit& FlashDetectorHit::operator=(const FlashDetectorHit& right)
{
  feventID = right.feventID;
  fParticleName = right.fParticleName;
  fEnergy = right.fEnergy;
  fPosx =right.fPosx;
  fPosy = right.fPosy;
  /*
  fTrackID   = right.fTrackID;
  //fChamberNb = right.fChamberNb;
  fEdep      = right.fEdep;
  fPos       = right.fPos;
  */
  return *this;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

G4bool FlashDetectorHit::operator==(const FlashDetectorHit& right) const
{
  return ( this == &right ) ? true : false;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

/*
void FlashDetectorHit::Draw()
{
  G4VVisManager* pVVisManager = G4VVisManager::GetConcreteInstance();
  if(pVVisManager)
  {
    G4Circle circle(fPos);
    circle.SetScreenSize(4.);
    circle.SetFillStyle(G4Circle::filled);
    G4Colour colour(1.,0.,0.);
    G4VisAttributes attribs(colour);
    circle.SetVisAttributes(attribs);
    pVVisManager->Draw(circle);
  }
}
*/
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FlashDetectorHit::Print()
{
  //G4cout << "Particle name: " << fParticleName << G4endl;
  if (HitsFile.is_open()) {

   HitsFile << "Hit"
            << "\t" << feventID << "\t" << fParticleName << "\t" << fEnergy << "\t" << fPosx << "\t" << fPosy  << G4endl;
  }
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
