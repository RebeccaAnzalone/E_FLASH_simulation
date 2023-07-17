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
/// \file FlashDetectorConstruction.cc
/// \brief Implementation of the FlashDetectorConstruction class


#include "FlashDetectorConstruction.hh"
#include "FlashDetectorSD.hh"

#include "G4RunManager.hh"

#include "G4Material.hh"
#include "G4NistManager.hh"
#include "G4Region.hh"
#include "G4SDManager.hh"

#include "G4AutoDelete.hh"
#include "G4Box.hh"
#include "G4GlobalMagFieldMessenger.hh"
#include "G4LogicalVolume.hh"
#include "G4PVParameterised.hh"
#include "G4PVPlacement.hh"
#include "G4Tubs.hh"

#include "G4GeometryManager.hh"
#include "G4GeometryTolerance.hh"

#include "G4UserLimits.hh"

#include "G4Colour.hh"
#include "G4VisAttributes.hh"

#include "G4SystemOfUnits.hh"

#include "Applicator.hh"


#include "G4MaterialPropertiesTable.hh"

#include "G4PSEnergyDeposit.hh"
#include "G4PhysicalConstants.hh"
#include "G4SystemOfUnits.hh"
#include "G4VPrimitiveScorer.hh"
#include "G4VisAttributes.hh"
#include "FlashDetectorMessenger.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorConstruction::FlashDetectorConstruction()
    : G4VUserDetectorConstruction(), physicalTreatmentRoom(0),logicTreatmentRoom(0), Collimator(0), phantom(0),
phantomLogicalVolume(0),phant_phys(0),
      fCheckOverlaps(true) {

  DefineMaterials();
  detectorMessenger = new FlashDetectorMessenger(this);


  SetPhantomSize(12. *mm, 30. *cm, 30. *cm);
  //SetPhantomSize(0. *mm, 0. *cm, 0. *cm);
  SetAirGap(0*cm); // Set the air gap between the water phantom and the end of the applicator
  //SetDetectorThickness(10*mm);
  //SetDetector_subThickness(370*um);
  //SetDetectorWidth(10*cm);
  SetAirGap_water_detector(30. *cm - phantomSizeX/2); // Set the air gap between the end of the water phantom and the entrance of the detector
                                   //i need 30 cm distance between the center of the phantom and the entrance of the detector


}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

FlashDetectorConstruction::~FlashDetectorConstruction() {

  delete detectorMessenger;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void FlashDetectorConstruction::DefineMaterials() {
  nist = G4NistManager::Instance();
//write here a function to define custom materials
G4bool isotopes = false;
  G4double A_Si=28.086*g/mole;
G4double density_SiC=3.22*g/cm3;
G4double Z_Si=14;

 Si = nist->FindOrBuildElement("Si", isotopes);
 C = nist->FindOrBuildElement("C", isotopes);


  }


//
G4VPhysicalVolume *
FlashDetectorConstruction::ConstructPhantom(G4double CollPos) {
//This function creates a cubic phantom with the point Collpos on the surface of the cube.

 phantomMaterial = nist->FindOrBuildMaterial("G4_WATER");

 Position_coefficient = CollPos;

 phantom_coordinateX = (Position_coefficient * mm + phantomSizeX / 2);

 G4ThreeVector phantomPosition =  G4ThreeVector(phantom_coordinateX, 0. * mm, 0. * mm); //phantom is constructed with the entrance surface attached to the applicator


  // Definition of the solid volume of the Phantom
  phantom = new G4Box("Phantom", phantomSizeX / 2, phantomSizeY / 2,
                      phantomSizeZ / 2);

  // Definition of the logical volume of the Phantom
  phantomLogicalVolume =
      new G4LogicalVolume(phantom, phantomMaterial, "phantomLog", 0, 0, 0);

  // Definition of the physical volume of the Phantom
  phant_phys =
      new G4PVPlacement(0, phantomPosition, "phantomPhys", phantomLogicalVolume,
                        physicalTreatmentRoom, false, 0);
//define the region to set cuts in FlashPhysicsList.cc and step limit
  G4Region *PhantomRegion = new G4Region("Phantom_reg");
  phantomLogicalVolume->SetRegion(PhantomRegion);
  PhantomRegion->AddRootLogicalVolume(phantomLogicalVolume);

  // Visualisation attributes of the phantom
  red = new G4VisAttributes(G4Colour(0 / 255., 255 / 255., 0 / 255.));
  red->SetVisibility(true);

  blue = new G4VisAttributes(G4Colour(0 / 255., 0. / 255., 255. / 255.));
  blue->SetVisibility(true);

  phantomLogicalVolume->SetVisAttributes(red);
//set step limit in phantom
  G4double maxStep = 0.1 * mm;
  fStepLimit = new G4UserLimits(maxStep);
  phantomLogicalVolume->SetUserLimits(fStepLimit);

  return phant_phys;

}

G4VPhysicalVolume *
FlashDetectorConstruction::ConstructDetector(){
 //Detector

/*
  G4double density_SiC=3.22*g/cm3;

 SiC=new G4Material("SiC", density_SiC,2);
SiC->AddElement(Si,1);
SiC->AddElement(C,1);

 detectorMaterial=SiC;


 DetectorPosition=phantom_coordinateX+AirGap+phantomSizeX/2+Det_thickness/2+AirGap_phantom_det; //al centro del fantoccio sull'asse del fascio

 Det_box = new G4Box("Detector",Det_thickness/2,Det_width/2,Det_width/2);

  // Definition of the logical volume of the Detector
  DetLogicalVolume =
      new G4LogicalVolume(Det_box, detectorMaterial, "DetectorLog", 0, 0, 0);
  Det_phys = new G4PVPlacement(0,G4ThreeVector(DetectorPosition, 0. * mm, 0. * mm), "DetPhys",DetLogicalVolume,physicalTreatmentRoom,false, 0, fCheckOverlaps);


  Det_sub = new G4Box("Det_sub",Det_sub_thickness/2,Det_width/2,Det_width/2);

  // Definition of the logical volume of the Detector
  Det_sub_LogicalVolume =
      new G4LogicalVolume(Det_sub, detectorMaterial, "Det_sub_Log", 0, 0, 0);
  Det_sub_phys = new G4PVPlacement(0,G4ThreeVector(DetectorPosition+Det_thickness+Det_sub_thickness/2, 0. * mm, 0. * mm), "Det_sub_Phys",Det_sub_LogicalVolume,physicalTreatmentRoom,false, 0, fCheckOverlaps);




    return Det_phys;
*/
airNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR");
detectorMaterial=airNist;


//DetectorPosition=phantom_coordinateX+AirGap+phantomSizeZ/2+Det_thickness/2+AirGap_phantom_det;
DetectorPosition=phantom_coordinateX+AirGap+AirGap_phantom_det+phantomSizeX;//Det_thickness/2;

G4double phi2 = 90. * deg;

  G4RotationMatrix rm2;
  rm2.rotateY(phi2);

// Define the detector wall dimensions
G4double wallSizeZ = 20.0 * cm; // Width of the detector wall
G4double wallSizeY = 20.0 * cm; // Height of the detector wall
G4double wallSizeX = 1.0 * cm;   // Thickness of the detector wall

// Create the detector wall volume
Det_box = new G4Box("Detector_wall", wallSizeX / 2, wallSizeY / 2, wallSizeZ / 2);
DetLogicalVolume = new G4LogicalVolume(Det_box, detectorMaterial, "DetectorLog", 0, 0, 0);

Det_phys = new G4PVPlacement(G4Transform3D(rm2,G4ThreeVector(phantomSizeX/2 + 40. *cm, 0. * mm, DetectorPosition)), "DetPhys",DetLogicalVolume,physicalTreatmentRoom,false, 0, fCheckOverlaps);
                                                             //centrato rispetto al fantoccio ma spostato di 40 cm lungo x
 return Det_phys;
}

G4VPhysicalVolume *FlashDetectorConstruction::Construct() {
  // -----------------------------
  // Treatment room - World volume
  //------------------------------
  // Treatment room sizes
  const G4double worldX = 400.0 * cm;
  const G4double worldY = 400.0 * cm;
  const G4double worldZ = 400.0 * cm;
  G4bool isotopes = false;

  airNist = G4NistManager::Instance()->FindOrBuildMaterial("G4_AIR", isotopes);
  // Air
  //

  G4Box *treatmentRoom = new G4Box("TreatmentRoom", worldX, worldY, worldZ);
  logicTreatmentRoom = new G4LogicalVolume(treatmentRoom, airNist,
                                           "logicTreatmentRoom", 0, 0, 0);
  physicalTreatmentRoom =
      new G4PVPlacement(0, G4ThreeVector(), "physicalTreatmentRoom",
                        logicTreatmentRoom, 0, false, 0);

  // The treatment room is invisible in the Visualisation
  logicTreatmentRoom->SetVisAttributes(G4VisAttributes::GetInvisible());

  // -----------------------------
  // Applicator + phantom +Default dimensions
  //------------------------------




  Collimator = new Applicator(physicalTreatmentRoom);



 phantom_physical =
        ConstructPhantom(Collimator->finalApplicatorXPositionFlash +
  Collimator->hightFinalApplicatorFlash+AirGap);
  ConstructDetector();


  return physicalTreatmentRoom;
}



void FlashDetectorConstruction::ConstructSDandField() {
//modify this function if you want to insert a sensitive detector
  /*
  // Sensitive detectors

  G4String FlashDetectorSDname = "FlashDetectorSD";
  G4String FlashDetectorHitsCollname = "FlashDetectorHitsCollection";
  FlashDetectorSD* aTrackerSD = new FlashDetectorSD(FlashDetectorSDname,
                                            FlashDetectorHitsCollname);
  G4SDManager::GetSDMpointer()->AddNewDetector(aTrackerSD);
  // Setting aTrackerSD to all logical volumes with the same name
  // of "DetectorLog".
  SetSensitiveDetector("DetectorLog", aTrackerSD, true);
  */
}


/////MESSANGER ///

G4bool FlashDetectorConstruction::SetPhantomMaterial(G4String material)
{

    if (G4Material* pMat = G4NistManager::Instance()->FindOrBuildMaterial(material, false) )
    {
	phantomMaterial  = pMat;

	if (phantomLogicalVolume)
	{

	    phantomLogicalVolume ->  SetMaterial(pMat);

	    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
	    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
	    G4cout << "The material of Phantom/Detector has been changed to " << material << G4endl;
	}
    }
    else
    {
	G4cout << "WARNING: material \"" << material << "\" doesn't exist in NIST elements/materials"
	    " table [located in $G4INSTALL/source/materials/src/G4NistMaterialBuilder.cc]" << G4endl;
	G4cout << "Use command \"/parameter/nist\" to see full materials list!" << G4endl;
	return false;
    }

    return true;
}


void FlashDetectorConstruction::SetPhantomSize(G4double sizeX, G4double sizeY, G4double sizeZ)
{
    if (sizeX > 0.) phantomSizeX = sizeX;
    if (sizeY > 0.) phantomSizeY = sizeY;
    if (sizeZ > 0.) phantomSizeZ = sizeZ;
}

void FlashDetectorConstruction::SetAirGap(G4double displ)
{

   AirGap=displ;
}

G4bool FlashDetectorConstruction::SetDetectorMaterial(G4String material)
{

    if (G4Material* pMat = G4NistManager::Instance()->FindOrBuildMaterial(material, false) )
    {
	detectorMaterial  = pMat;

	if (DetLogicalVolume)
	{

	    DetLogicalVolume ->  SetMaterial(pMat);

	    G4RunManager::GetRunManager() -> PhysicsHasBeenModified();
	    G4RunManager::GetRunManager() -> GeometryHasBeenModified();
	    G4cout << "The material of Phantom/Detector has been changed to " << material << G4endl;
	}
    }
    else
    {
	G4cout << "WARNING: material \"" << material << "\" doesn't exist in NIST elements/materials"
	    " table [located in $G4INSTALL/source/materials/src/G4NistMaterialBuilder.cc]" << G4endl;
	G4cout << "Use command \"/parameter/nist\" to see full materials list!" << G4endl;
	return false;
    }

    return true;
}




void FlashDetectorConstruction::SetDetectorThickness(G4double thickness)
{

   Det_thickness=thickness;
}

void FlashDetectorConstruction::SetDetectorWidth(G4double width)
{

   Det_width=width;
}

void FlashDetectorConstruction::SetDetector_subThickness(G4double thickness_sub)
{

    Det_sub_thickness= thickness_sub;
}





 void FlashDetectorConstruction::SetAirGap_water_detector(G4double spost)
{

  AirGap_phantom_det=spost;
}


void FlashDetectorConstruction::SetDetectorPosition(G4double position)
{

   DetectorPosition=position;
}
