#include <TROOT.h>
#include <TSystem.h>
#include "Riostream.h"
#include "TFile.h"
#include "TCanvas.h"
#include "TF1.h"
#include "TH1D.h"
#include "TH2D.h"
#include "TTree.h"
#include "TFrame.h"
#include "TLegend.h"
#include "TString.h"
#include "TRandom.h"
#include "TVector.h"
#include "TLorentzVector.h"
#include "TStyle.h"


class fitZee{
public:
  TString treeName;
  TString treeFileName;
  TFile* treefile;
  TTree* tree; 
  TList* hList;
  TList* hListRaw;
  TString cutList[1000];
  Double_t massVec[1000];
  Double_t massErrVec[1000];
  Double_t resVec[1000];
  Int_t iCount;
  Int_t npar; 
  TCanvas* c1;

public:
  fitZee();  // constructor
  ~fitZee(); // destructor

  void Fit(TString cut, TString siz="medium", 
	   Int_t nbins=180, Double_t xmin=60., Double_t xmax=120., 
	   bool useCalib=true);

  void FitHist(TString hName, Double_t xmin=60., Double_t xmax=120.);

  void Draw();

  void Draw(Int_t id1, Int_t id2=-1, Int_t id3=-1, Int_t id4=-1, 
	    Int_t id5=-1, Int_t id6=-1);

  void List();

  void Save();

  void Compare();

  void SetDataSample(TString filename);

};
 
