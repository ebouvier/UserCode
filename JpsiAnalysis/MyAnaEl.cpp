#define MyAna_cxx

#include <memory>
#include "MyAna.h"
#include "HiggsTriggerEfficiencyProvider.h"
#include "PUReweighter.h"


#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <TH2F.h>

using namespace std;

  MyAna::MyAna(TTree *_muonstree, TTree *_electronstree, TTree *_jetstree, TTree *_METtree, TTree *_verticestree, TTree *_eventstree, TTree *_HLTtree, TTree *_muonsloosetree, TTree *_electronsloosetree, TTree *_jpsitree, TTree *_MCtree)
:RootTupleDefs(_muonstree, _electronstree, _jetstree, _METtree, _verticestree, _eventstree, _HLTtree, _muonsloosetree, _electronsloosetree, _jpsitree, _MCtree)
{
  _isMC     = false;
  _isTTbar  = false;
  _isSIG    = false;
  _debug    = false;
  _rootName = "output.root";
  _doSkim   = false;
  _nevt     = -1; 
}

MyAna::~MyAna()
{
}

void MyAna::Loop()
{
  cout << " => Running on MC     ? " << boolalpha << _isMC  << endl;
  cout << " => Running on Signal ? " << boolalpha << _isSIG << endl;

  PUReweighter* myPUReweighter = new PUReweighter("../../PatTopFilteredProduction/crab_tasks/15Apr01/LumiAndPU/PUProfiles/MyDataPileupHistogram.root"); 
  // PUReweighter* myPUReweighter = new PUReweighter("../../PatTopFilteredProduction/crab_tasks/15Apr01/LumiAndPU/PUProfiles/MyDataPileupHistogram_PUup.root"); 
  // PUReweighter* myPUReweighter = new PUReweighter("../../PatTopFilteredProduction/crab_tasks/15Apr01/LumiAndPU/PUProfiles/MyDataPileupHistogram_PUdown.root"); 

  _newfile = new TFile(_rootName.c_str(),"RECREATE");

  //================================================================================================
  // HISTOGRAMS
  //================================================================================================

  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);

  TH1F* _h_nPUBefore = new TH1F("NTrueInteractions", "NTrueInteractions", 80, 0., 80.);
  _h_nPUBefore->SetXTitle("Number of true interactions (before PU reweighing)");
  TH1F* _h_nPUAfter = new TH1F("NTrueInteractionsReweighted", "NTrueInteractionsReweighted", 80, 0., 80.);
  _h_nPUAfter->SetXTitle("Number of true interactions (after PU reweighing)");
  if (!_isMC) {
    for (int ibin = 1; ibin <= _h_nPUBefore->GetNbinsX(); ++ibin) {
      _h_nPUBefore->SetBinContent(ibin, myPUReweighter->getBinContent(ibin));
      _h_nPUAfter->SetBinContent(ibin, myPUReweighter->getBinContent(ibin));
    }
  }

  TH1F* _h_iCut = new TH1F("Event-yields","Event-yields", 3, 0., 3.);
  _h_iCut->SetOption("bar");
  _h_iCut->SetBarWidth(0.75);
  _h_iCut->SetBarOffset(0.125);
  TH1F* _h_weight = new TH1F("Weight", "Weight", 20, 0., 2.);
  _h_weight->SetXTitle("Weight");

  TH1F* _h_nVtx = new TH1F("NPrimaryVtx", "NPrimaryVtx", 50, 0., 50.);
  _h_nVtx->SetXTitle("Primary vertex multiplicity");

  float _weight = 1.;

  //================================================================================================
  // Clone the tree
  //================================================================================================

  if ( _doSkim ) {
    GetEntry(0);
    _newmuonstree=muonsChain->GetTree()->CloneTree(0);
    _newelectronstree=electronsChain->CloneTree(0);
    _newjetstree=jetsChain->CloneTree(0);
    _newverticestree=verticesChain->CloneTree(0);
    _newMETtree=METChain->CloneTree(0);
    _neweventstree=eventsChain->CloneTree(0);
    _newHLTtree=HLTChain->CloneTree(0);
    _newmuonsloosetree=muonslooseChain->CloneTree(0);
    _newelectronsloosetree=electronslooseChain->CloneTree(0);
    _newjpsitree=jpsiChain->CloneTree(0);

    if (_isMC) {
      _newMCtree=MCChain->CloneTree(0);
    }
  }

  //================================================================================================
  // Start the Loop
  //================================================================================================

  if (muonsChain == 0) return;

  Int_t nentries = Int_t(muonsChain->GetEntriesFast());
  if (_nevt < 0) _nevt = (int)nentries; //nevt initialised to -1 unless -num option is requested  

  int nwrite = 0;
  int nselected = 0;

  TString cutName[100]; for (int i=0;i<100;++i) cutName[i] = "";

  TString currentfile = "";
  Int_t nbytes = 0, nb = 0;

  for (Int_t jentry=0; jentry<_nevt;jentry++) { //Starting events loop
    nb = GetEntry(jentry);   nbytes += nb; // call rootupledf GetEntry method that do the GetEntry for all 6 trees  and returns muonstree size (bytes)

    if (jentry % 1000 == 0) { //Display number of events each 10000 events
      cout << "Loop: processing event  " << jentry <<endl;     
    }

    TString thisfile = muonsChain->GetCurrentFile()->GetName();
    if (thisfile != currentfile) {
      currentfile = thisfile;
      cout << " => Start processing : " << currentfile << endl;
    }

    if (_isMC) 
      _weight = generator_weight;
    else
      _weight = 1.;

    // PU reweighting 
    if (_isMC) {
      _h_nPUBefore->Fill((float)nTrueInteractions, _weight);
      int npu = (int) nTrueInteractions;
      if (npu > 79) npu = 79;
      _weight = _weight * myPUReweighter->weight(npu);
      _h_nPUAfter->Fill((float)nTrueInteractions, _weight);
    }

    int iCut = 0;
    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Starting"; ++iCut; // /!\ no scalefactors yet
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Starting");

    //======================================================
    // Trigger
    //======================================================

    bool passTrigger = false;

    if (!_isMC) {
      for ( unsigned int i=0; i<HLT_vector->size(); ++i){
        TString ThistrigName= (TString) HLT_vector->at(i);        
        if (ThistrigName.Contains("HLT_Ele27_WP80")) passTrigger = true;
      }
    }	

    if (!passTrigger && !_isMC) continue;  

    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Trigger"; ++iCut; // /!\ no scalefactors yet
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Trigger");

    //================================================================================================
    // Objects selection 
    //================================================================================================

    vector<int> indgoodel;
    vector<int> indsoftmu;
    vector<int> indgoodjet;
    vector<int> ind30jet;
    vector<int> indgoodver;

    //======================================================
    // Good electrons selection
    //======================================================

    if (_debug) cout << " -> electrons size " << n_electrons << endl;

    for (unsigned int i = 0; i < n_electrons; ++i) {
      float elPt = GetP4(electron_4vector,i)->Pt();
      float elEta = GetP4(electron_4vector,i)->Eta();
      if (elPt <= 30) continue;
      if (fabs(elEta) >= 2.5) continue;
      if (!electron_passTightID[i]) continue;
      if (fabs(electron_SCEta[i]) >= 1.4442 && fabs(electron_SCEta[i]) < 1.5660) continue;
      indgoodel.push_back(i);
    }
    unsigned int ngoodelectron = indgoodel.size();

    if (_debug) cout << "Number of good electrons = " << ngoodelectron << endl;

    //======================================================
    // Soft muons selection
    //======================================================

    if (_debug) cout << " -> loose muons size " << n_muonsloose << endl;

    for (unsigned int i = 0; i < n_muonsloose; ++i) {
      float muPt = GetP4(muonloose_4vector,i)->Pt();
      float muEta = GetP4(muonloose_4vector,i)->Eta();
      if (muPt <= 10) continue;
      if (fabs(muEta) >= 2.5) continue;
      indsoftmu.push_back(i);
    }
    unsigned int nsoftmuon = indsoftmu.size();

    if (_debug) cout << "Number of soft muons = " << nsoftmuon << endl;

    //======================================================
    // Good jet selection
    //======================================================

    int n55jet = 0;
    int n45jet = 0;
    int n35jet = 0;

    if (_debug) cout << " -> jets size " << n_jets << endl;

    for (unsigned int i = 0; i < n_jets; ++i) {
      float jetPt = GetP4(jet_4vector,i)->Pt();
      float jetEta = GetP4(jet_4vector,i)->Eta();
      if (jetPt <= 20.) continue;
      if (fabs(jetEta) >= 2.5) continue;
      if (jetPt > 55.) ++n55jet;
      if (jetPt > 45.) ++n45jet;
      if (jetPt > 35.) ++n35jet;
      if (jetPt > 30.) ind30jet.push_back(i);
      indgoodjet.push_back(i);
    }
    unsigned int ngoodjet = indgoodjet.size();
    unsigned int n30jet = ind30jet.size();

    if (_debug) cout << "Number of good jets = " << ngoodjet << endl;

    //======================================================
    // Vertices
    //======================================================

    if (_debug) cout <<" -> vertices size "<< n_vertices << endl;

    for (unsigned int i = 0; i < n_vertices; ++i) {
      if (vertex_isFake[i]) continue;
      if (vertex_ndof[i] <= 4) continue;   
      indgoodver.push_back(i);
    }
    unsigned int nvtx = indgoodver.size();

    if (_debug) cout << "Number of good vertices "<< nvtx << endl;

    //======================================================
    // Semi-electronic event selection and scale factor
    //======================================================

    if (ngoodelectron != 1 || nsoftmuon != 0 || n30jet < 4) continue;

    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Event selection"; ++iCut; // /!\ no scalefactors yet
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Event selection");

    if (_isMC) {
      // Trigger scalefactors
      HiggsTriggerEfficiencyProvider *weight_provider = new HiggsTriggerEfficiencyProvider();
      _weight = _weight*weight_provider->get_weight_isoel(GetP4(electron_4vector, indgoodel[0])->Pt(), GetP4(electron_4vector, indgoodel[0])->Eta()); 
      // Electron scalefactor
      _weight = _weight*(*electron_scaleFactor_tighteff_tightiso)[indgoodel[0]][0]; // 0 for central, 1 for up, 2 for down
      // Jet scalefactors
      _weight = _weight*(*jet_scaleFactor)[ind30jet[0]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jet_scaleFactor)[ind30jet[1]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jet_scaleFactor)[ind30jet[2]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jet_scaleFactor)[ind30jet[3]][0]; // 0 for central, 1 for up, 2 for down
    }
    _h_weight->Fill(_weight);

    //======================================================
    // Analyze mu-tagged jets
    //======================================================

    _h_nVtx->Fill((float)indgoodver.size(), _weight);

    //===============================================================================================
    // Write new tree
    //===============================================================================================

    if (_doSkim) {
      _newmuonstree->Fill();
      _newelectronstree->Fill();
      _newjetstree->Fill();
      _newverticestree->Fill();
      _newMETtree->Fill();
      _neweventstree->Fill();
      _newHLTtree->Fill();
      _newmuonsloosetree->Fill();
      _newelectronsloosetree->Fill();
      _newjpsitree->Fill();
      if (_isMC) {
        _newMCtree->Fill();
      }
      nwrite++;
    }

    ++nselected;
  }

  //================================================================================================
  // Delete dynamical objects
  //================================================================================================

  cout << "========================================================================" << endl;
  cout << "Initial number of events                                  = " << _h_iCut->GetBinContent(1) << endl;
  cout << "------------------------------------------------------------------------" << endl;
  cout << "Number of events after cut : " << endl;
  for (int i = 1; i < 3 ; i++){
    cout << "..." << cutName[i] << " = " << _h_iCut->GetBinContent(i+1) << endl;
  }
  cout << "------------------------------------------------------------------------" << endl;
  cout << "Total Number of events selected                           = "  << nselected			   << endl;
  cout << "========================================================================" << endl;
  cout << "Total Number of events skimmed                            = "  << nwrite			   << endl;
  cout << "========================================================================" << endl;

  _newfile->Write();
  _newfile->Close();

}
