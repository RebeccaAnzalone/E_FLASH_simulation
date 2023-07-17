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
/// \file FlashDetectorHit.hh
/// \brief Definition of the FlashDetectorHit class

#ifndef FlashDetectorHit_h
#define FlashDetectorHit_h 1

#include "G4VHit.hh"
#include "G4THitsCollection.hh"
#include "G4Allocator.hh"
#include "G4ThreeVector.hh"
#include "tls.hh"
#include <fstream>

/// Tracker hit class
///
/// It defines data members to store the trackID, chamberNb, energy deposit,
/// and position of charged particles in a selected volume:
/// - fTrackID, fChamberNB, fEdep, fPos

class FlashDetectorHit : public G4VHit
{
  public:
    FlashDetectorHit();
    FlashDetectorHit(const FlashDetectorHit&);
    virtual ~FlashDetectorHit();

    // operators
    const FlashDetectorHit& operator=(const FlashDetectorHit&);
    G4bool operator==(const FlashDetectorHit&) const;

    inline void* operator new(size_t);
    inline void  operator delete(void*);

    // methods from base class
    //virtual void Draw();
    virtual void Print();

    // Set methods
    void SeteventID (G4int eventid) {feventID = eventid;}
    void SetParticleName (G4String particleName) {fParticleName = particleName;}
    void SetEnergy (G4double kineticEnergy) {fEnergy = kineticEnergy;}
    void SetPosx (G4double pos_x) {fPosx = pos_x;}
    void SetPosy (G4double pos_y) {fPosy = pos_y;}

    //void SetTrackID  (G4int track)      { fTrackID = track; };
    //void SetChamberNb(G4int chamb)      { fChamberNb = chamb; };
    //void SetEdep     (G4double de)      { fEdep = de; };
    //void SetPos      (G4ThreeVector xyz){ fPos = xyz; };

    // Get methods
    G4int GeteventID() const     { return feventID; };
    G4String GetParticleName() const     { return fParticleName; };
    G4double GetEnergy() const   { return fEnergy; };
    G4double GetPosx() const     { return fPosx; };
    G4double GetPosy() const { return fPosy; };
    //G4int GetTrackID() const     { return fTrackID; };
    //G4int GetChamberNb() const   { return fChamberNb; };
    //G4double GetEdep() const     { return fEdep; };
    //G4ThreeVector GetPos() const { return fPos; };

  private:

      G4int ThreadNumber;

      G4int feventID;
      G4String fParticleName;
      G4double fEnergy;
      G4double fPosx;
      G4double fPosy;

      std::ofstream HitsFile;

      //G4int         fTrackID;
      //G4int         fChamberNb;
      //G4double      fEdep;
      //G4ThreeVector fPos;
};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

typedef G4THitsCollection<FlashDetectorHit> FlashDetectorHitsCollection;


extern G4ThreadLocal G4Allocator<FlashDetectorHit>* FlashDetectorHitAllocator;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void* FlashDetectorHit::operator new(size_t)
{
  if(!FlashDetectorHitAllocator)
      FlashDetectorHitAllocator = new G4Allocator<FlashDetectorHit>;
  return (void *) FlashDetectorHitAllocator->MallocSingle();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

inline void FlashDetectorHit::operator delete(void *hit)
{
  FlashDetectorHitAllocator->FreeSingle((FlashDetectorHit*) hit);
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif
