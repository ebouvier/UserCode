#define MyAna_cxx

#include <memory>
#include "MyAna.h"
#include "TopTriggerEfficiencyProvider.h"


#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>

using namespace std;

  MyAna::MyAna(TTree *_muonstree, TTree *_electronstree, TTree *_jetstree, TTree *_METtree, TTree *_verticestree, TTree *_eventstree, TTree *_HLTtree, TTree *_muonsloosetree, TTree *_electronsloosetree, TTree *_mujetstree, TTree *_MCtree)
:RootTupleDefs(_muonstree, _electronstree, _jetstree, _METtree, _verticestree, _eventstree, _HLTtree, _muonsloosetree, _electronsloosetree, _mujetstree, _MCtree)
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

  float PUWEIGHT[41] = {0.343966,0.421778,0.436096,0.244907,0.159864,0.301344,0.241472,0.274829,0.44007,0.758224,1.17234,1.57047,1.65648,1.48344,1.25881,1.09602,1.02284,1.01614,1.05619,1.11854,1.17075,1.1998,1.20717,1.1982,1.17317,1.13123,1.0737,1.00772,0.928615,0.834017,0.723992,0.605741,0.485348,0.371787,0.270933,0.187491,0.124365,0.0791913,0.0484192,0.0288752,0.0127159};

  _newfile = new TFile(_rootName.c_str(),"RECREATE");

  //================================================================================================
  // HISTOGRAMS
  //================================================================================================

  TH1::SetDefaultSumw2(true);
  TH1F* _h_iCut = new TH1F("Event-yields","event-yields",100,0.,100.);
  _h_iCut->SetOption("bar");
  _h_iCut->SetBarWidth(0.75);
  _h_iCut->SetBarOffset(0.125);

  TH1F* _h_nVtx = new TH1F("NPrimaryVtx", "NPrimaryVtx", 50, 0., 50.);

  TH1F* _h_NSelJets = new TH1F("N-b-jets", "N-b-jets", 5, 0., 5.);
  _h_NSelJets->SetXTitle("Primary vertices multiplicity");
  TH1F* _h_CSVSelJets = new TH1F("CSV-b-jets", "CSV-b-jets", 100, 0., 1.);
  _h_CSVSelJets->SetXTitle("CSV discriminant");
  TH1F* _h_pTSelJets = new TH1F("TransverseMomentum-b-jets", "TransverseMomentum-b-jets", 100, 0., 500.); 
  _h_pTSelJets->SetXTitle("p_{T}(jets) (GeV/c)");
  TH1F* _h_etaSelJets = new TH1F("Eta-b-jets", "Eta-b-jets", 60, -3., 3.); 
  _h_etaSelJets->SetXTitle("#eta(jets)");

  TH1F* _h_Nch = new TH1F("Nch-b-jets", "Nch-b-jets", 45, 0, 45); 
  _h_Nch->SetXTitle("Track multiplicity");
  TH1F* _h_sump = new TH1F("Sump-b-jets", "Sump-b-jets", 200, 0, 1000);
  _h_sump->SetXTitle("Scalar sum of track momenta (GeV/c)");
  TH1F* _h_sumpvec = new TH1F("VectorialSump-b-jets", "VectorialSump-b-jets", 300, 0, 1500);
  _h_sumpvec->SetXTitle("Vectorial sum of tracks momenta (GeV/c)");

  TH1F* _h_sum1p = new TH1F("Highestp-b-jets", "Highestp-b-jets", 150, 0, 300);
  _h_sum1p->SetXTitle("Highest track momentum (GeV/c)");
  TH1F* _h_sum2p = new TH1F("Sum2p-b-jets", "Sum2p-b-jets", 150, 0, 300);
  _h_sum2p->SetXTitle("Scalar sum of the 2 highest track momenta (GeV/c)");
  TH1F* _h_sum3p = new TH1F("Sum3p-b-jets", "Sum3p-b-jets", 150, 0, 300);
  _h_sum3p->SetXTitle("Scalar sum of the 3 highest track momenta (GeV/c)");
  TH1F* _h_mass3 = new TH1F("Mass3-b-jets", "Mass3-b-jets", 400, 0., 10.);
  _h_mass3->SetXTitle("Invariant mass of the 3 highest momentum tracks (GeV/c^{2})");
  TH1F* _h_R1 = new TH1F("R1-b-jets", "R1-b-jets", 102, 0, 1.02);
  _h_R1->SetXTitle("R_{1}");
  TH1F* _h_R2 = new TH1F("R2-b-jets", "R2-b-jets", 102, 0, 1.02);
  _h_R2->SetXTitle("R_{2}");
  TH1F* _h_R3 = new TH1F("R3-b-jets", "R3-b-jets", 102, 0, 1.02);
  _h_R3->SetXTitle("R_{3}");

  TH1F* _h_sum1p_nomu = new TH1F("Highestp-nomu-b-jets", "Highestp-nomu-b-jets", 150, 0, 300);
  _h_sum1p_nomu->SetXTitle("Highest track momentum (no #mu) (GeV/c)");
  TH1F* _h_sum2p_nomu = new TH1F("Sum2p-nomu-b-jets", "Sum2p-nomu-b-jets", 150, 0, 300);
  _h_sum2p_nomu->SetXTitle("Scalar sum of the 2 highest track momenta (no #mu) (GeV/c)");
  TH1F* _h_sum3p_nomu = new TH1F("Sum3p-nomu-b-jets", "Sum3p-nomu-b-jets", 150, 0, 300);
  _h_sum3p_nomu->SetXTitle("Scalar sum of the 3 highest track momenta (no #mu) (GeV/c)");
  TH1F* _h_mass3_nomu = new TH1F("Mass3-nomu-b-jets", "Mass3-nomu-b-jets", 400, 0., 10.);
  _h_mass3_nomu->SetXTitle("Invariant mass of the 3 highest momentum tracks (no #mu) (GeV/c^{2})");
  TH1F* _h_R1_nomu = new TH1F("R1-nomu-b-jets", "R1-nomu-b-jets", 102, 0, 1.02);
  _h_R1_nomu->SetXTitle("R_{1} (no #mu)");
  TH1F* _h_R2_nomu = new TH1F("R2-nomu-b-jets", "R2-nomu-b-jets", 102, 0, 1.02);
  _h_R2_nomu->SetXTitle("R_{2} (no #mu)");
  TH1F* _h_R3_nomu = new TH1F("R3-nomu-b-jets", "R3-nomu-b-jets", 102, 0, 1.02);
  _h_R3_nomu->SetXTitle("R_{3} (no #mu)");

  TH1F* _h_D0Mass = new TH1F("D0Mass-b-jets", "D0Mass-b-jets", 400, 0, 8);
  _h_D0Mass->SetXTitle("M(D^{0}#rightarrow#kappa^{+}#pi^{-}) (GeV/c^{2})");
  TH1F* _h_D0p = new TH1F("D0p-b-jets", "D0p-b-jets", 150, 0, 300); 
  _h_D0p->SetXTitle("p(D^{0}#rightarrow#kappa^{+}#pi^{-}) (GeV/c)");
  TH1F* _h_D0pT = new TH1F("D0pT-b-jets", "D0pT-b-jets", 100, 0, 400); 
  _h_D0pT->SetXTitle("p_{T}(D^{0}#rightarrow#kappa^{+}#pi^{-}) (GeV/c)");
  TH1F* _h_D0eta = new TH1F("D0eta-b-jets", "D0eta-b-jets", 60, -3, 3);
  _h_D0eta->SetXTitle("#eta(D^{0}#rightarrow#kappa^{+}#pi^{-})");
  TH1F* _h_BMomentum_unbiased = new TH1F("BMomentum-nobias-b-jets", "BMomentum-nobias-b-jets", 100, 0, 400);
  _h_BMomentum_unbiased->SetXTitle("p(#kappa^{+}#pi^{-}+#mu^{-}) (GeV/c)");
  TH1F* _h_BMass_unbiased = new TH1F("BMass-nobias-b-jets", "BMass-nobias-b-jets", 100, 0., 10.);
  _h_BMass_unbiased->SetXTitle("M(#kappa^{+}#pi^{-}+#mu^{-}) (GeV/c^{2})");
  TH1F* _h_BMomentumClean = new TH1F("BMomentum-D0cut-b-jets", "BMomentum-D0cut-b-jets", 100, 0, 400);
  _h_BMomentumClean->SetXTitle("p(#kappa^{+}#pi^{-}+#mu^{-}) (GeV/c)");
  TH1F* _h_BMassClean = new TH1F("BMass-D0cut-b-jets", "BMass-D0cut-b-jets", 100, 0., 10.); 
  _h_BMassClean->SetXTitle("M(#kappa^{+}#pi^{-}+#mu^{-}) (GeV/c^{2})");
  TH1F* _h_mup_unbiased = new TH1F("Muonp-nobias-b-jets", "Muonp-nobias-b-jets", 150, 0, 300); 
  _h_mup_unbiased->SetXTitle("p(soft #mu) (GeV/c)");

  TTree* _t_D0window_bjets = new TTree("D0window-b-jets", "D0window-b-jets", 1);
  float _weight = 1.;
  _t_D0window_bjets->Branch("Weight", &_weight, "Weight/F");
  float _CSVdisc = -10.;
  _t_D0window_bjets->Branch("CSVdisc", &_CSVdisc, "CSVdisc/F");
  float _D0mass = 0.;
  _t_D0window_bjets->Branch("D0mass", &_D0mass, "D0mass/F");
  float _Bmomentum = 0.;
  _t_D0window_bjets->Branch("Bmomentum", &_Bmomentum, "Bmomentum/F");
  float _Bmass = 0.;
  _t_D0window_bjets->Branch("Bmass", &_Bmass, "Bmass/F");
  float _Mup = 0.;
  _t_D0window_bjets->Branch("Mup", &_Mup, "Mup/F");
  float _R1 = 0.;
  _t_D0window_bjets->Branch("R1", &_R1, "R1/F");
  float _R2 = 0.;
  _t_D0window_bjets->Branch("R2", &_R2, "R2/F");
  float _R3 = 0.;
  _t_D0window_bjets->Branch("R3", &_R3, "R3/F");
  float _Ntr = 0.;
  _t_D0window_bjets->Branch("Nch", &_Ntr, "Nch/F");
  float _sumP = 0.;
  _t_D0window_bjets->Branch("Sump", &_sumP, "Sump/F");
  float _sumpT = 0.;
  _t_D0window_bjets->Branch("SumpT", &_sumpT, "SumpT/F");
  float _averpT = 0.;
  _t_D0window_bjets->Branch("AveragepT", &_averpT, "SumpT/F");
  float _R1_nomu = 0.;
  _t_D0window_bjets->Branch("R1_nomu", &_R1_nomu, "R1_nomu/F");
  float _R2_nomu = 0.;
  _t_D0window_bjets->Branch("R2_nomu", &_R2_nomu, "R2_nomu/F");
  float _R3_nomu = 0.;
  _t_D0window_bjets->Branch("R3_nomu", &_R3_nomu, "R3_nomu/F");


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
    _newmujetstree=mujetsChain->CloneTree(0);

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

    int iCut = 0;
    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Starting"; ++iCut; // /!\ no pu reweighting or scalefactors yet
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Starting");

    //======================================================
    // Trigger
    //======================================================

    bool passTrigger = false;

    if (!_isMC) {
      for ( unsigned int i=0; i<HLT_vector->size(); ++i){
        TString ThistrigName= (TString) HLT_vector->at(i);        
        if (run <  191691                 && ThistrigName.Contains("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFJet30")) passTrigger = true;
        if (run >= 191691 && run < 194225 && ThistrigName.Contains("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30")) passTrigger = true;
        if (run >= 194225 && run < 199608 && ThistrigName.Contains("HLT_Ele25_CaloIdVT_CaloIsoT_TrkIdT_TrkIsoT_TriCentralPFNoPUJet30_30_20")) passTrigger = true;
        if (run >= 199608                 && ThistrigName.Contains("HLT_Ele25_CaloIdVT_CaloIsoVL_TrkIdVL_TrkIsoT_TriCentralPFNoPUJet45_35_25")) passTrigger = true;        
      }
    }	

    if (!passTrigger && !_isMC) continue;  

    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Trigger"; ++iCut; // /!\ no pu reweighting or scalefactors yet
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

    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Event selection"; ++iCut; // /!\ no pu reweighting or scalefactors yet
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Event selection");

    if (_isMC) {
      // Trigger scalefactors
      double lumitab[4]= {888.7,4446,7021 ,7221}; // when running on all the stat
      TopTriggerEfficiencyProvider *weight_provider = new TopTriggerEfficiencyProvider(true,lumitab);
      _weight = _weight*weight_provider->get_weight(GetP4(electron_4vector, indgoodel[0])->Pt(), 
          GetP4(electron_4vector, indgoodel[0])->Eta(), 
          GetP4(jet_4vector, ind30jet[3])->Pt(), 
          GetP4(jet_4vector, ind30jet[3])->Eta(), 
          nvtx, ngoodjet,
          false, TopTriggerEfficiencyProvider::NOMINAL);
      // Electron scalefactor
      _weight = _weight*(*electron_scaleFactor_tighteff_tightiso)[indgoodel[0]][0]; // 0 for central, 1 for up, 2 for down
      // Jet scalefactors
      _weight = _weight*(*jet_scaleFactor)[ind30jet[0]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jet_scaleFactor)[ind30jet[1]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jet_scaleFactor)[ind30jet[2]][0]; // 0 for central, 1 for up, 2 for down
      // PU reweighting 
      // FIXME
      _weight = _weight*(*jet_scaleFactor)[ind30jet[3]][0]; // 0 for central, 1 for up, 2 for down
      int npu = (int) nTrueInteractions;
      if (npu>40) npu = 40;
      _weight = _weight * PUWEIGHT[npu];
    }

    //======================================================
    // Analyze mu-tagged jets
    //======================================================

    _h_nVtx->Fill((float)indgoodver.size(), _weight);

    float gMassMu = 0.105658367;
    
    int nSelJets = 0;
    for (int i = 0; i < n_mujet; ++i) {
      if (GetP4(mujet_jet_4vector,i)->Pt() <= 20.) continue;
      // Look for good soft muon
      if (GetP4(mujet_nonisomuplus_4vector,i)->Pt() <= 4. && GetP4(mujet_nonisomuplus_4vector,i)->Pt() <= 4.) continue;
      // no Z veto in semi_e channel
      ++nSelJets;

      // Apply scale factor for soft muon and jet
      if (_isMC) {
        _weight = _weight*(*mujet_jet_scaleFactor)[i][0]; // 0 for central, 1 for up, 2 for down
        if (GetP4(mujet_nonisomuplus_4vector,i)->Pt() > GetP4(mujet_nonisomuplus_4vector,i)->Pt())
          _weight = _weight*(*mujet_nonisomuplus_muon_scaleFactor_looseeff_looseiso)[i][0]; // 0 for central, 1 for up, 2 for down
        else
          _weight = _weight*(*mujet_nonisomuminus_muon_scaleFactor_looseeff_looseiso)[i][0]; // 0 for central, 1 for up, 2 for down
      }
      
      _CSVdisc = mujet_jet_btag_CSV[i];
      _h_CSVSelJets->Fill(mujet_jet_btag_CSV[i], _weight);
      _h_pTSelJets->Fill(GetP4(mujet_jet_4vector,i)->Pt(), _weight);
      _h_etaSelJets->Fill(GetP4(mujet_jet_4vector,i)->Eta(), _weight);
      
      _Ntr = (float)mujet_ntr[i];
      _h_Nch->Fill((float)mujet_ntr[i], _weight);
      _sumP = mujet_sump[i];
      _h_sump->Fill(mujet_sump[i], _weight);
      _sumpT = mujet_sump[i];
      _h_sumpvec->Fill(mujet_sumvecp[i], _weight);
      if (_Ntr > 1e-6) _averpT = _sumpT/_Ntr;
      
      vector<int> indtr;
      vector<int> indtrnomu;
      for (int j = 0; j < n_tr; ++j) {
        if (mujet_tr_indmujet[j] != i) continue;
        indtr.push_back(j);
        if (abs(mujet_tr_pdgid[j]) != 13) indtrnomu.push_back(j);
      }
      if (indtr.size() > 0) {
        TLorentzVector p_sum;
        p_sum.SetPtEtaPhiM(GetP4(mujet_tr_4vector,indtr[0])->Pt(), GetP4(mujet_tr_4vector,indtr[0])->Eta(), GetP4(mujet_tr_4vector,indtr[0])->Phi(), GetP4(mujet_tr_4vector,indtr[0])->M());
        _h_sum1p->Fill(p_sum.P(), _weight);
        _R1 = p_sum.P()/mujet_sump[i];
        _h_R1->Fill(p_sum.P()/mujet_sump[i], _weight);
        if (indtr.size() > 1) {
          p_sum = p_sum + TLorentzVector(GetP4(mujet_tr_4vector,indtr[1])->Pt(), GetP4(mujet_tr_4vector,indtr[1])->Eta(), GetP4(mujet_tr_4vector,indtr[1])->Phi(), GetP4(mujet_tr_4vector,indtr[1])->M());
          _h_sum2p->Fill(p_sum.P(), _weight);
          _R2 = p_sum.P()/mujet_sump[i];
          _h_R2->Fill(p_sum.P()/mujet_sump[i], _weight);
          if (indtr.size() > 2) {
            p_sum = p_sum + TLorentzVector(GetP4(mujet_tr_4vector,indtr[2])->Pt(), GetP4(mujet_tr_4vector,indtr[2])->Eta(), GetP4(mujet_tr_4vector,indtr[2])->Phi(), GetP4(mujet_tr_4vector,indtr[2])->M());
            _h_sum3p->Fill(p_sum.P(), _weight);
            _h_mass3->Fill(p_sum.M(), _weight);
            _R3 = p_sum.P()/mujet_sump[i];
            _h_R3->Fill(p_sum.P()/mujet_sump[i], _weight);
          } // at least 3 tracks
        } // at least 2 tracks
      } // at least 1 track
      if (indtrnomu.size() > 0) {
        TLorentzVector p_sum;
        p_sum.SetPtEtaPhiM(GetP4(mujet_tr_4vector,indtrnomu[0])->Pt(), GetP4(mujet_tr_4vector,indtrnomu[0])->Eta(), GetP4(mujet_tr_4vector,indtrnomu[0])->Phi(), GetP4(mujet_tr_4vector,indtrnomu[0])->M());
        _h_sum1p_nomu->Fill(p_sum.P(), _weight);
        _R1_nomu = p_sum.P()/mujet_sump[i];
        _h_R1_nomu->Fill(p_sum.P()/mujet_sump[i], _weight);
        if (indtrnomu.size() > 1) {
          p_sum = p_sum + TLorentzVector(GetP4(mujet_tr_4vector,indtrnomu[1])->Pt(), GetP4(mujet_tr_4vector,indtrnomu[1])->Eta(), GetP4(mujet_tr_4vector,indtrnomu[1])->Phi(), GetP4(mujet_tr_4vector,indtrnomu[1])->M());
          _h_sum2p_nomu->Fill(p_sum.P(), _weight);
          _R2_nomu = p_sum.P()/mujet_sump[i];
          _h_R2_nomu->Fill(p_sum.P()/mujet_sump[i], _weight);
          if (indtrnomu.size() > 2) {
            p_sum = p_sum + TLorentzVector(GetP4(mujet_tr_4vector,indtrnomu[2])->Pt(), GetP4(mujet_tr_4vector,indtrnomu[2])->Eta(), GetP4(mujet_tr_4vector,indtrnomu[2])->Phi(), GetP4(mujet_tr_4vector,indtrnomu[2])->M());
            _h_sum3p_nomu->Fill(p_sum.P(), _weight);
            _h_mass3_nomu->Fill(p_sum.M(), _weight);
            _R3_nomu = p_sum.P()/mujet_sump[i];
            _h_R3_nomu->Fill(p_sum.P()/mujet_sump[i], _weight);
          } // at least 3 tracks \mu
        } // at least 2 tracks \mu
      } // at least 1 track \mu   
      
      for (int j = 0; j < n_d0; ++j) {
        if (mujet_d0_indmujet[j] != i) continue;
        if (!mujet_d0_vtxvalid[j]) continue;
        if (mujet_d0_vtxchi2[j]/mujet_d0_ndf[j] >= 4.) continue;
        if (mujet_d0_L3DoverSigmaL3D[j] <= 100.) continue;
        if (GetP4(mujet_d0_4vector,j)->Pt() <= 12.) continue;

        TLorentzVector p_d0;
        p_d0.SetPtEtaPhiM(GetP4(mujet_d0_4vector,j)->Pt(), GetP4(mujet_d0_4vector,j)->Phi(), GetP4(mujet_d0_4vector,j)->Eta(), GetP4(mujet_d0_4vector,j)->M());
        _D0mass = p_d0.M();
        _h_D0Mass->Fill(p_d0.M(), _weight);
        _h_D0p->Fill(p_d0.P(), _weight);
        _h_D0pT->Fill(p_d0.Pt(), _weight);
        _h_D0eta->Fill(p_d0.Eta(), _weight);
        
        // consider a mu with OS to the kaon
        TLorentzVector p_mu;
        if (mujet_d0_kaon_pdgid[j] > 0)
          p_mu.SetPtEtaPhiM(GetP4(mujet_nonisomuminus_4vector,i)->Pt(), GetP4(mujet_nonisomuminus_4vector,i)->Eta(), GetP4(mujet_nonisomuminus_4vector,i)->Phi(), gMassMu);
        else 
          p_mu.SetPtEtaPhiM(GetP4(mujet_nonisomuplus_4vector,i)->Pt(), GetP4(mujet_nonisomuplus_4vector,i)->Eta(), GetP4(mujet_nonisomuplus_4vector,i)->Phi(), gMassMu);
        if (p_mu.P() < 1e-6) continue;
        _Mup = p_mu.P();
        _h_mup_unbiased->Fill(p_mu.P(), _weight);
        
        TLorentzVector p_b = p_d0+p_mu;
        _Bmomentum = p_b.P();
        _Bmass = p_b.M();        
        _h_BMomentum_unbiased->Fill(p_b.P(), _weight);
        _h_BMass_unbiased->Fill(p_b.M(), _weight);
        if (p_d0.M() >= 1.7 && p_d0.M() < 2.) {
          _h_BMomentumClean->Fill(p_b.P(), _weight);
          _h_BMassClean->Fill(p_b.M(), _weight);
          _t_D0window_bjets->Fill();
        }

      }
      
    } // Mu-tagged jet loop
    
    _h_NSelJets->Fill((float)nSelJets, _weight);

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
      _newmujetstree->Fill();
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
  for ( Int_t i=1; i<10 ; i++ ){
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