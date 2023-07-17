//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Appaboration.  It is provided  under  the terms  and *
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
//

#ifndef Applicator_H
#define Applicator_H 1

#include "FlashDetectorConstruction.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4LogicalVolume.hh"
#include "G4SubtractionSolid.hh"
#include "G4Tubs.hh"
#include "G4VUserDetectorConstruction.hh"
#include "G4VisAttributes.hh"
#include "globals.hh"

class G4VPhysicalVolume;

class Applicator {
public:
  Applicator(G4VPhysicalVolume *);
  ~Applicator();

  G4double finalApplicatorXPositionFlash;
  G4double hightFinalApplicatorFlash;

  void SetOuterRadius(G4double radius);
   void SetApplicatorLength(G4double length);

private:
void ConstructCollimator(G4VPhysicalVolume *);

  void FlashBeamLineVacuumSource();

  void FlashBeamLineTitaniumWindows();
  void FlashVWAlcover();
    void FlashAlCover2();
      void FlashExitBit();
        void FlashToroid();
          void OverCover();
            void OverCover2();
              void MonitorChamber();
                void Flash_connector();
                                void Bigconnector();
                                                void Bigconnector2();
                                                                void Bigconnector3();
                                                                void FlashBeamLineApplicator();
                                                                void Smallconnector();


  G4double initial_pos;
  
  G4double innerRadiusFirstApplicatorFlash;
  G4VPhysicalVolume *motherPhys;

  G4Material* Fe;
  G4Material* PVDF;
  G4Material* FILM;
  G4Material* aluminumNist;
  G4Material* PMMA;

  G4double outRadiusVSFlash;
  G4double hightVSFlash;
  G4double XPositionVSFlash;
  G4double hightFTFlash;
  
    G4double outRadiusFTFlash;
      G4double outRadius;
        G4double toroid_outRadius;
          G4double toroid_hight;
                    G4double toroid_XPosition;
                              G4double Bigcover_hight;
                                        G4double Bigcover_XPosition;
                                        G4double Chamberpos;
  
  G4bool fCheckOverlaps;
  void SetDefaultDimensions();

  void ConstructApplicator();

  G4VisAttributes *blue;
  G4VisAttributes *gray;
  G4VisAttributes *white;
  G4VisAttributes *red;
  G4VisAttributes *yellow;
  G4VisAttributes *green;
  G4VisAttributes *darkGreen;
  G4VisAttributes *darkOrange3;
  G4VisAttributes *skyBlue;
  G4VisAttributes *magenta;


  G4double OuterRadiusFirstApplicatorFlash;
  G4Tubs *solidFirstApplicatorFlash;
  G4VPhysicalVolume *physiFirstApplicatorFlash;
  G4Material *firstApplicatorMaterialFlash;

  
  //  Titanium Window
  G4Tubs *solidFTFlash;
  G4VPhysicalVolume *physiFTFlash;
  G4Material *FTFlashMaterialFlash;

  //  Vacuum Source
  G4Tubs *solidVSFlash;
  G4VPhysicalVolume *physiVSFlash;
  G4Material *VSFlashMaterialFlash;
};
#endif
