//_____________________macro fitZee.C___________________________
 //
 //  This is an example for a complex fit to a 
 //  Z-Peak with detector resolution effects, used the Voigt function
 //
 //  Eckhard von Toerne, Bonn University
 //  Usage:
 //  .x fitZee.C(TCut cut, idstring, small,medium,big string)
#include "fitZee.h"

#include "ElecCalib.C"
#include <cmath>
#include "TMath.h"


Double_t fitf(Double_t *v, Double_t *par)
 {
//http://root.cern.ch/root/html310/TMath.html
//Voigt(Double_t x, Double_t sigma, Double_t lg, Int_t R = 4)
 
  // Computation of Voigt function (normalised).
  // Voigt is a convolution of
  // gauss(x) = 1/(sqrt(2*pi)*sigma) * exp(x*x/(2*sigma*sigma) and
  //lorentz(x) = (1/pi) * (lg/2) / (x*x + g*g/4)
  //functions.
  //The Voigt function is known to be the real part of Faddeeva function also
  //called complex error function [2].
  //The algoritm was developed by J. Humlicek [1].
  //This code is based on fortran code presented by R. J. Wells [2].
  //Translated and adapted by Miha D. Puc
  //To calculate the Faddeeva function with relative error less than 10^(-R).
  //R can be set by the the user subject to the constraints 2 <= R <= 5.
  //[1] J. Humlicek, JQSRT, 21, 437 (1982).
  //[2] R.J. Wells "Rapid Approximation to the Voigt/Faddeeva Function and its
  //Derivatives" JQSRT 62 (1999), pp 29-48.
  //http://www-atm.physics.ox.ac.uk/user/wells/voigt.html

  //Double_t x = v[0];
  static const double zwidth=2.4952;
  double x2=v[0]*v[0];
  //const double Aint = 2.*3.142/(137.*137.*2.); // - 2 Qf pi alpha² / 2s
  //double xintTerm = Aint * sqrt(par[0]*par[3]) * (x2-par[1]*par[1])/
  //  ((x2-par[1]*par[1])*(x2-par[1]*par[1])+par[1]*par[1]*zwidth*zwidth)*1.E4/x2;
  double backgr = par[3] * (1.+par[4]*1.E2/v[0]+par[5]*1.E4/x2+par[6]*1.E6/x2/v[0]+par[7]*1.E8/x2/x2) *1.E4/x2; // + xintTerm;
  //double backgr = par[3] * (1.+par[4]*v[0]/1.E2+par[5]*x2/1.E4+par[6]*x2*v[0]/1.E6+par[7]*x2*x2/1.E8)*1.E4/x2 + xintTerm;
  if (backgr < 0.) backgr = 0.;
  double sig = par[0]*TMath::Voigt(v[0]-par[1],par[2],zwidth,3)*1.E4/x2;
  //cout << "x=" << v[0] << " bg=" << backgr<<" sig=" << sig<< " int=" << xintTerm<<endl;
  return sig+backgr;
 }




Double_t MeeCalib(Double_t en1, Double_t pt1, Double_t eta1, Double_t phi1, Double_t etiso1, Double_t eoverp1, Double_t drjet1,
	     Double_t en2, Double_t pt2, Double_t eta2, Double_t phi2, Double_t etiso2, Double_t eoverp2, Double_t drjet2)
{
  const double elecMass=0.51099892E-3;
  double newe1=ElecCalib(en1,pt1,eta1,phi1,etiso1,eoverp1,drjet1);
  double newPt1 = pt1 * newe1/en1; // dreisatz unter vernachlässigung der electronmasse
  TLorentzVector e1;
  e1.SetPtEtaPhiM(newPt1,eta1,phi1,elecMass);
  TLorentzVector e2;
  double newe2=ElecCalib(en2,pt2,eta2,phi2,etiso2,eoverp2,drjet2);
  double newPt2 = pt2 * newe2/en2; 
  e2.SetPtEtaPhiM(newPt2,eta2,phi2,elecMass);
  TLorentzVector z0 = e1+e2;
  return z0.M();
}

Double_t Mee(Double_t pt1, Double_t eta1, Double_t phi1, Double_t pt2, Double_t eta2, Double_t phi2)
{
  const double elecMass=0.51099892E-3;
  TLorentzVector e1;
  e1.SetPtEtaPhiM(pt1,eta1,phi1,elecMass);
  TLorentzVector e2;
  e2.SetPtEtaPhiM(pt2,eta2,phi2,elecMass);
  TLorentzVector z0 = e1+e2;
  return z0.M();
}

fitZee::~fitZee()
{
  treefile->Close();
  hList->Clear();
  hListRaw->Clear();
  delete hList;
  delete hListRaw;
  delete c1;
}

fitZee::fitZee()
{
  //gStyle->SetOptFit(1); // 1111 also nice
  //gStyle->SetOptStat(11); 
  cout << "constructor fitZee"<<endl;
  treeName="tree";
  //treeFileName="../makeNtuple/PythiaZee-ZeeNtuple.root";
  //treeFileName="PythiaZee-ZeeNtupleCalib1.root";
  treeFileName="ATLASDATA-Zee.root";
  hList=new TList();
  hListRaw=new TList();
  
  iCount=0;
  treefile = TFile::Open(treeFileName);
  tree = (TTree*) treefile->Get(treeName);
  npar=8; 
  c1 = new TCanvas("c1","Zee Fit, Bonn University",200,10,700,500);
  c1->cd();

}

void fitZee::SetDataSample(TString filename)
{
  treefile->Close();
  treeFileName=filename;
  treefile = TFile::Open(treeFileName);
  delete treefile;
  treefile = TFile::Open(treeFileName);
  tree = (TTree*) treefile->Get(treeName);
  return;
}

void fitZee::Draw()
{
  if (iCount==0) return;
  if (iCount==1) Draw(0);
  if (iCount==2) Draw(0,1);
  if (iCount==3) Draw(0,1,2);
  if (iCount==4) Draw(0,1,2,3);
  if (iCount==5) Draw(0,1,2,3,4);
  if (iCount==6) Draw(0,1,2,3,4,5);

}


void fitZee::Draw(Int_t id1, Int_t id2, Int_t id3, Int_t id4, Int_t id5, Int_t id6)
{
  //  Int_t linsav = gStyle->GetLineWidth();
  //gStyle->SetLineWidth(3);
  Int_t mcolor[7]= { 2, 4, 3, 5, 6, 7, 8 } ;
  const int kMax=6;
  //TCanvas* c1 = new TCanvas("c1","Zee Fit, Bonn University",200,10,700,500);
  //c1->SetFillColor(42);
  c1->GetFrame()->SetFillColor(21);
  c1->GetFrame()->SetBorderSize(6);
  c1->GetFrame()->SetBorderMode(-1);
  //TLegend* leg = new TLegend(0.6,0.7,0.89,0.89);
  TLegend* leg = new TLegend(0.05,0.5,0.45,0.89);
  
  TString opt="e";
  for (int k=1;k<=kMax;k++){
    Int_t id=0;
    if (k==1) id = id1;
    if (k==2) id = id2;
    if (k==3) id = id3;
    if (k==4) id = id4;
    if (k==5) id = id5;
    if (k==6) id = id6;
    if (id>=0 && id < iCount) {
      TH1D* h= (TH1D*) hList->At(id);
      h->SetLineColor(mcolor[k]);
      leg->AddEntry(hList->At(id), cutList[id], "f"); // "l"
      //h->SetTextColor(mcolor[k]);
      h->SetFillColor(mcolor[k]);
      h->Draw(opt);
      //h->DrawNormalized(opt);
      h->GetFunction("fit")->SetLineColor(mcolor[k]);
      opt="esame";
    }
  }
  leg->Draw();
  //gStyle->SetLineWidth(linsav);
}

void fitZee::Fit(TString cut, TString siz, Int_t nbins, Double_t xmin, Double_t xmax, bool useCalib) 
{
  Int_t id = iCount;
  TString calibString="";
  if (!useCalib) calibString= " raw";
  cutList[id]=cut+calibString;
  cout << "fitZee::filling histogram" << endl;
  bool dogetChar=false;
  Int_t nEntries = 20000;
  if (strstr(siz,"small")) nEntries=10000;
  if (strstr(siz,"medium")) nEntries=50000;
  if (strstr(siz,"large")) nEntries=100000;
  if (strstr(siz,"LARGE")) nEntries=200000;
  if (strstr(siz,"tiny")) nEntries=1000;

  TString MeeCalibString="MeeCalib(el_energy,el_pt,el_eta,el_phi,el_etiso,el_eoverp,el_drjet,pos_energy,pos_pt,pos_eta,pos_phi,pos_etiso,pos_eoverp,pos_drjet)";
  TString MeeRawString="Mee(el_pt,el_eta,el_phi,pos_pt,pos_eta,pos_phi)";
  TString MeeString = MeeCalibString;
  if (! useCalib) {
    MeeString=MeeRawString;
    cout << "fitZee:filling uncalibrated energies " << endl;
  }
  TString hName=TString("Mee")+Form("%d",id); 
  TH1D* h= new TH1D(hName," "+cut,nbins, xmin,xmax);
  hList->Add(h);

  TF1 *func = new TF1("fit",fitf,xmin,xmax,npar);
  func->SetParNames("Signal","Mass","Resol.","NBg","Bg1","Bg2","Bg3","Bg4");
  func->SetLineColor(2);

  tree->Draw(MeeString+">>"+hName,cut,"goff", nEntries); 
  cout << "fitZee::fitting " << endl;

  double maxM= xmin + (xmax-xmin) * ((double) h->GetMaximumBin()) / ((double) h->GetNbinsX());
  func->SetParameters(h->GetEntries()/6. , maxM , 1.0 , h->GetEntries()/5000., 0., 0., 0.,0.);
  h->Fit("fit","q","",xmin,xmax);  // minos errors -> "e" + fitrange
  h->Fit("fit","q","",xmin,xmax);  // minos errors -> "e" + fitrange
  //h->Fit("fit","eq","",xmin,xmax);  // minos errors -> "e" + fitrange
  h->Fit("fit","","",xmin,xmax);  // minos errors -> "e" + fitrange

  massVec[id]=func->GetParameter(1);
  massErrVec[id]=func->GetParError(1);
  resVec[id]=func->GetParameter(2);
  if (dogetChar) getchar();
  //h->Draw("e");
  iCount++;
  return;
}

void fitZee::FitHist(TString hName, Double_t xmin, Double_t xmax)
{
  TH1D* h=(TH1D*) treefile->Get(hName);
  TF1 *func = new TF1("fit",fitf,xmin,xmax,npar);
  func->SetParNames("Signal","Mass","Resol.","NBg","Bg1","Bg2","Bg3","Bg4");
  func->SetLineColor(2);
 
  double maxM= 91.2;
  func->SetParameters(h->GetEntries()/3. ,maxM  , 0.001 , h->GetEntries()/5000., 0. , 0., 0.,0.);
  //func->Draw();
  //h->Draw("esame");
  h->Fit("fit","q","",xmin,xmax);  // minos errors -> "e" + fitrange
  h->Fit("fit","","",xmin,xmax);  // minos errors -> "e" + fitrange
  //h->Fit("fit","eq","",xmin,xmax);  // minos errors -> "e" + fitrange
  //h->Fit("fit","e","",xmin,xmax);  // minos errors -> "e" + fitrange

  //h->Draw("e");
}

void fitZee::List()
{
  cout <<"Id="<<" Mass "<<" Resol."<<" cut"<< endl;
  for (int k=0;k<iCount;k++){
    cout <<" "<< k <<" "<< massVec[k]<< " +/- "<< massErrVec[k] << "    " << resVec[k]<<"  "<< cutList[k]<< endl;
  }
}

void fitZee::Save()
{
  printf("under construction, this routine does nothing yet\n");

}


void fitZee::Compare()
{
  printf("Comparison of calibrated and uncalibrated Z-Peaks\n");
  Fit("","LARGE",180,60.,120.,false);
  Fit("","LARGE",180,60.,120.,true);
  Draw(iCount-1,iCount-2);
  List();

}
