#include "PMTSD.hh"
#include "PMTHit.hh"

#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4ParticleDefinition.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4ios.hh"
#include "G4ParticleTypes.hh"
#include "G4ParticleDefinition.hh"
#include "G4SDManager.hh"

//---------------------------------------------------------------------------

PMTSD::PMTSD(G4String name, G4int Nelements )
  :G4VSensitiveDetector(name)
{
  collectionName.insert(name+G4String("Collection"));
  fCollection = NULL;
  fNelements  = Nelements;
  fNhits      = 0;
  fHCID       = -1;
  fhitID      = new G4int[fNelements];
  fHits       = new G4int[fNelements];
  for(G4int i=0; i<fNelements; i++) fhitID[i] = -1;
  for(G4int i=0; i<fNelements; i++) fHits[i]  = 0; 
}

//---------------------------------------------------------------------------

PMTSD::~PMTSD()
{;}

//---------------------------------------------------------------------------

void PMTSD::Initialize(G4HCofThisEvent*)
{
  fCollection = new PMTHitsCollection(SensitiveDetectorName,collectionName[0]); 

}

//---------------------------------------------------------------------------

G4bool PMTSD::ProcessHits(G4Step*,G4TouchableHistory*)
{
  return false;
}

//---------------------------------------------------------------------------

G4bool PMTSD::ProcessHits_constStep(const G4Step* aStep,
				       G4TouchableHistory* )
{
  if(aStep->GetTrack()->GetDefinition() 
     != G4OpticalPhoton::OpticalPhotonDefinition()) return false;
 
  G4int pmtNumberPost= aStep->GetPostStepPoint()->GetTouchable()
    ->GetVolume()->GetCopyNo();
  G4int pmtNumber = pmtNumberPost;
  if (pmtNumber == 1) pmtNumber--;
 
  // if this PMT hasn't been hit in this event
  if ( fhitID[pmtNumber] == -1 ) {
    PMTHit* OpHit = new PMTHit;
    OpHit->SetPMTNumber(pmtNumber);
    OpHit->IncPhotonCount();

    fhitID[pmtNumber] = fCollection->insert(OpHit) - 1;
    fHits[fNhits++] = pmtNumber;
    //std::cout << "First PMT hit ... pmtNumber = " << pmtNumber << std::endl; 
  }
  else // this is not a new hit
    if (pmtNumber == 0) {
    	(*fCollection)[fhitID[pmtNumber]]->IncPhotonCount();
    }else{
    	std::cout << "Danger Will Robinson!!! Additional PMT hit on pmtNumber = " << pmtNumber << std::endl; 
    }
  
  return true;
}
//---------------------------------------------------------------------------

void PMTSD::EndOfEvent(G4HCofThisEvent* HCE)
{
  if(fHCID<0)  fHCID = G4SDManager::GetSDMpointer()->GetCollectionID(collectionName[0]);
  if(fNhits>0) HCE->AddHitsCollection(fHCID,fCollection);

  for (G4int i=0;i<fNhits;i++) {
    fhitID[fHits[i]] = -1;
    fHits[i]         = 0;
  }
  fNhits = 0;
}

//---------------------------------------------------------------------------

