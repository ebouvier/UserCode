#define MyAna_cxx

#include <memory>
#include "MyAna.h"
#include "HiggsTriggerEfficiencyProvider.h"
#include "BfragWeightsProvider.h"
#include "JpsiWeightsProvider.h"
#include "PUReweighter.h"


#include <TStyle.h>
#include <TCanvas.h>
#include <TMath.h>
#include <iostream>
#include <iomanip>
#include <set>
#include <map>
#include <TH2F.h>
#include "LHAPDF/LHAPDF.h"

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

  // Trigger scalefactors
  HiggsTriggerEfficiencyProvider *weight_provider = new HiggsTriggerEfficiencyProvider();

  PUReweighter* myPUReweighter = new PUReweighter("../../PatTopFilteredProduction/crab_tasks/15Apr01/LumiAndPU/PUProfiles/MyDataPileupHistogram.root"); 
  // PUReweighter* myPUReweighter = new PUReweighter("../../PatTopFilteredProduction/crab_tasks/15Apr01/LumiAndPU/PUProfiles/MyDataPileupHistogram_PUup.root"); 
  // PUReweighter* myPUReweighter = new PUReweighter("../../PatTopFilteredProduction/crab_tasks/15Apr01/LumiAndPU/PUProfiles/MyDataPileupHistogram_PUdown.root"); 
  
  /* PDF set variations
   * https://twiki.cern.ch/twiki/bin/viewauth/CMS/PDFatCMS#Recommendation_for_PDF_use_in_CM
   */
  /* PDF set name */
  // const std::string setname = "NNPDF30_nlo_as_0118";
  // const std::string setname = "MMHT2014nlo68cl";
  // const std::string setname = "CT14nlo";
  /* Deviation up or down */
  // bool devUp = true;
  // bool devUp = false;
  /* Loading LHAPDF */
  /*
  const LHAPDF::PDFSet set(setname);
  const std::vector<LHAPDF::PDF*> pdfs = set.mkPDFs();
  */

  /* JpsiWeightsProvider */
  /*
  JpsiWeightsProvider* myJpsiReweighter = new JpsiWeightsProvider("15Nov24", "MyAnaMu"); 
  */

  /* BfragWeightsProvider */
  /*
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("16Feb23", "Z2star_rbLEP", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("16Feb23", "Z2star_rbLEP_soft", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("16Feb23", "Z2star_rbLEP_hard", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("16Feb23", "P12", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("16Feb23", "P12FT", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("16Feb23", "P12FL", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("Inclusive", "Z2star_rbLEPhard", "xb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("15Dec05", "Z2star_rbLEP", "xjpsixb"); 
  BfragWeightsProvider* myBfragReweighter = new BfragWeightsProvider("15Dec05", "Z2star_rbLEP", "xb"); 
  */

  _newfile = new TFile(_rootName.c_str(),"RECREATE");

  //================================================================================================
  // HISTOGRAMS
  //================================================================================================

  TH1::SetDefaultSumw2(true);
  TH2::SetDefaultSumw2(true);

  TH1F* _h_PUBefore = new TH1F("PUBefore", "PUBefore", 80, 0., 80.);
  _h_PUBefore->SetXTitle("Number of true interactions (before PU reweighing)");
  TH1F* _h_PUAfter = new TH1F("PUAfter", "PUAfter", 80, 0., 80.);
  _h_PUAfter->SetXTitle("Number of true interactions (after PU reweighing)");
  if (!_isMC) {
    for (int ibin = 1; ibin <= _h_PUBefore->GetNbinsX(); ++ibin) {
      _h_PUBefore->SetBinContent(ibin, myPUReweighter->getBinContent(ibin));
      _h_PUAfter->SetBinContent(ibin, myPUReweighter->getBinContent(ibin));
    }
  }

  int counter[20]; for (int i=0; i<20; ++i) counter[i] = 0;
  TH1F* _h_iCut = new TH1F("Event-yields","event-yields", 9, 0., 9.);
  _h_iCut->SetOption("bar");
  _h_iCut->SetBarWidth(0.75);
  _h_iCut->SetBarOffset(0.125);
  TH1F* _h_weight = new TH1F("Weight", "Weight", 2000, 0., 2.);
  _h_weight->SetXTitle("Weight");
  TH1F* _h_decay = new TH1F("Decay","Decay", 6, 0., 6.);
  _h_decay->SetOption("bar");
  _h_decay->SetBarWidth(0.75);
  _h_decay->SetBarOffset(0.125);
  _h_decay->GetXaxis()->SetBinLabel(1, "#mu + Jets");
  _h_decay->GetXaxis()->SetBinLabel(2, "#mu#mu + Jets");
  _h_decay->GetXaxis()->SetBinLabel(3, "#mue + Jets");
  _h_decay->GetXaxis()->SetBinLabel(4, "e + Jets");
  _h_decay->GetXaxis()->SetBinLabel(5, "ee + Jets");
  _h_decay->GetXaxis()->SetBinLabel(6, "e#mu + Jets");
  TH1F* _h_decay_part = new TH1F("Decay-part","Decay-part", 3, 0., 3.);
  _h_decay_part->SetOption("bar");
  _h_decay_part->SetBarWidth(0.75);
  _h_decay_part->SetBarOffset(0.125);
  _h_decay->GetXaxis()->SetBinLabel(1, "#mu + Jets");
  _h_decay->GetXaxis()->SetBinLabel(2, "#mu#mu + Jets");
  _h_decay->GetXaxis()->SetBinLabel(3, "#mue + Jets");

  float _weight = 1.;

  TH1F* _h_cuts_muons_n          = new TH1F("NMuons-cuts", "NMuons-cuts", 4, 0., 4.);
  _h_cuts_muons_n->SetXTitle("Number of isolated #mu (before cut)");
  TH1F* _h_cuts_electrons_n      = new TH1F("NElectrons-cuts", "NElectrons-cuts", 4, 0., 4.);
  _h_cuts_electrons_n->SetXTitle("Number of veto e (before cut)");
  TH1F* _h_cuts_jet20_n          = new TH1F("NJets20-cuts", "NJets20-cuts", 15, 0., 15.);
  _h_cuts_jet20_n->SetXTitle("Number of jets with p_{T} > 20 GeV (before cut)");
  TH1F* _h_cuts_jet30_n          = new TH1F("NJets30-cuts", "NJets30-cuts", 15, 0., 15.);
  _h_cuts_jet30_n->SetXTitle("Number of jets with p_{T} > 30 GeV (before cut)");
  TH1F* _h_cuts_jet40_n          = new TH1F("NJets40-cuts", "NJets40-cuts", 15, 0., 15.);
  _h_cuts_jet40_n->SetXTitle("Number of jets with p_{T} > 40 GeV (before cut)");
  TH1F* _h_cuts_jet50_n          = new TH1F("NJets50-cuts", "NJets50-cuts", 15, 0., 15.);
  _h_cuts_jet50_n->SetXTitle("Number of jets with p_{T} > 50 GeV (before cut)");
  TH1F* _h_cuts_csvJet20_n       = new TH1F("NCsvJets20-cuts", "NCsvJets20-cuts", 6, 0., 6.);
  _h_cuts_csvJet20_n->SetXTitle("Number of CSV b-tagged jets (before cut)");
  TH1F* _h_large_jpsi_m          = new TH1F("MJpsi-large", "MJpsi-large", 24, 2.8, 3.4);
  _h_large_jpsi_m->SetXTitle("J/#psi mass (GeV)");
  TH1F* _h_cuts_jpsi_m           = new TH1F("MJpsi-cuts", "MJpsi-cuts", 8, 3., 3.2);
  _h_cuts_jpsi_m->SetXTitle("J/#psi mass (GeV) (before cut)");
  TH1F* _h_cuts_jpsi_n           = new TH1F("NJpsi-cuts", "NJpsi-cuts", 3, 0., 3.);
  _h_cuts_jpsi_n->SetXTitle("Number of J/#psi (before cut)");
  TH1F* _h_cuts_jpsi_chi2        = new TH1F("Chi2Jpsi-cuts", "Chi2Jpsi-cuts", 32, 0., 16.);
  _h_cuts_jpsi_chi2->SetXTitle("#chi^{2}(J/#psi vertex) (before cut)");
  TH1F* _h_cuts_jpsi_l           = new TH1F("LJpsi-cuts", "LJpsi-cuts", 25, 0., 0.5);
  _h_cuts_jpsi_l->SetXTitle("c#tau(J/#psi) (cm) (before cut)");
  TH1F* _h_cuts_jpsi_l_zoom      = new TH1F("LJpsi-cuts-zoom", "LJpsi-cuts-zoom", 100, 0., 0.05);
  _h_cuts_jpsi_l_zoom->SetXTitle("c#tau(J/#psi) (cm)");
  TH1F* _h_cuts_jpsi_lOverSig    = new TH1F("LOverSigmaJpsi-cuts", "LOverSigmaJpsi-cuts", 42, 0., 7000.);
  _h_cuts_jpsi_lOverSig->SetXTitle("(c#tau)/#Delta(c#tau)(J/#psi) (before cut)");
  double xbins[15] = {0., 5., 10., 15., 20., 25., 35., 50., 70., 100., 150., 250., 400., 600., 1000.};
  TH1F* _h_cuts_jpsi_lOverSig_zoom = new TH1F("LOverSigmaJpsi-cuts-zoom", "LOverSigmaJpsi-cuts-zoom", 14, xbins);
  _h_cuts_jpsi_lOverSig_zoom->SetXTitle("(c#tau)/#Delta(c#tau)(J/#psi) (before cut)");
  TH1F* _h_cuts_jpsi_dRLept      = new TH1F("DRJpsiIsoLept-cuts", "DRJpsiIsoLept-cuts", 100, 0., 5.);
  _h_cuts_jpsi_dRLept->SetXTitle("#DeltaR (J/#psi-leading #mu) (before cut)");

  TH1F* _h_dRJpsibjet_gen   = new TH1F("DeltaRJpsibjet-gen", "DeltaRJpsibjet-gen", 250, 0., 5);
  _h_dRJpsibjet_gen->SetXTitle("#DeltaR(J/#psi-b jet)^{gen}");
  TH1F* _h_pTJpsiOverpTbjet_gen  = new TH1F("PtJpsiOverPtbjet-gen", "PtJpsiOverPtbjet-gen", 100, 0., 2.);
  _h_pTJpsiOverpTbjet_gen->SetXTitle("p_{T}^{gen}(J/#psi)/p_{T}^{gen}(b jet)");
  TH1F* _h_dRJpsiBhad_gen   = new TH1F("DeltaRJpsiBhad-gen", "DeltaRJpsiBhad-gen", 250, 0., 5);
  _h_dRJpsiBhad_gen->SetXTitle("#DeltaR(J/#psi-B hadron)^{gen}");
  TH1F* _h_pTJpsiOverpTBhad_gen  = new TH1F("PtJpsiOverPtBhad-gen", "PtJpsiOverPtBhad-gen", 100, 0., 2.);
  _h_pTJpsiOverpTBhad_gen->SetXTitle("p_{T}^{gen}(J/#psi)/p_{T}^{gen}(B hadron)");
  TH1F* _h_dRBhadbjet_gen   = new TH1F("DeltaRBhadbjet-gen", "DeltaRBhadbjet-gen", 250, 0., 5);
  _h_dRBhadbjet_gen->SetXTitle("#DeltaR(B hadron-b jet)^{gen}");
  TH1F* _h_pTBhadOverpTbjet_gen  = new TH1F("PtBhadOverPtbjet-gen", "PtBhadOverPtbjet-gen", 100, 0., 2.);
  _h_pTBhadOverpTbjet_gen->SetXTitle("p_{T}^{gen}(B hadron)/p_{T}^{gen}(b jet)");

  TH1F* _h_isoLept_n              = new TH1F("NIsoLept", "NIsoLept", 3, 0., 3.);
  _h_isoLept_n->SetXTitle("Number of leading #mu");
  TH1F* _h_isoLept_pt             = new TH1F("PtIsoLept", "PtIsoLept", 30, 0., 300.);   
  _h_isoLept_pt->SetXTitle("p_{T}(leading #mu) (GeV)");
  TH1F* _h_isoLept_eta            = new TH1F("EtaIsoLept", "EtaIsoLept", 30, -3., 3.); 
  _h_isoLept_eta->SetXTitle("#eta(leading #mu)");
  TH1F* _h_isoLept_phi            = new TH1F("PhiIsoLept", "PhiIsoLept", 32, -3.2, 3.2); 
  _h_isoLept_phi->SetXTitle("#phi(leading #mu)");
  TH1F* _h_isoLept_pfiso          = new TH1F("PfIsoIsoLept", "PfIsoIsoLept", 50, 0., 0.5);  
  _h_isoLept_pfiso->SetXTitle("#mu isolation");

  TH1F* _h_jet20_n                = new TH1F("NJets20", "NJets20", 11, 0., 11.); 
  _h_jet20_n->SetXTitle("Number of jets with p_{T}>20 GeV");
  TH1F* _h_jet20_pt               = new TH1F("PtJets20", "PtJets20", 25, 0., 500.); 
  _h_jet20_pt->SetXTitle("p_{T}(jets) (GeV)");
  TH1F* _h_jet20_eta              = new TH1F("EtaJets20", "EtaJets20", 30, -3., 3);
  _h_jet20_eta->SetXTitle("#eta(jets)");
  TH1F* _h_jet20_phi              = new TH1F("PhiJets20", "PhiJets20", 32, -3.2, 3.2);
  _h_jet20_phi->SetXTitle("#phi(jets)");
  TH1F* _h_jet20_csv              = new TH1F("CsvJets20", "CsvJets20", 50, 0., 1.);
  _h_jet20_csv->SetXTitle("CSV discriminant");
  TH1F* _h_jet20_chmult           = new TH1F("ChMultJets20", "ChMultJets20", 50, 0., 50.);
  _h_jet20_chmult->SetXTitle("Charge multiplicity");
  TH1F* _h_csvJet20_n             = new TH1F("NCsvJets20", "NCsvJets20", 5, 0., 5.); 
  _h_csvJet20_n->SetXTitle("Number of CSV b-tagged jets with p_{T}>20 GeV");
  TH1F* _h_jet30_n                = new TH1F("NJets30", "NJets30", 11, 0., 11.);
  _h_jet30_n->SetXTitle("Number of jets with p_{T}>30 GeV");
  TH1F* _h_jet40_n                = new TH1F("NJets40", "NJets40", 9, 0., 9.);
  _h_jet40_n->SetXTitle("Number of jets with p_{T}>40 GeV");
  TH1F* _h_jet50_n                = new TH1F("NJets50", "NJets50", 8, 0., 8.);
  _h_jet50_n->SetXTitle("Number of jets with p_{T}>50 GeV");

  TH1F* _h_leadJet1_pt            = new TH1F("PtLeadJet1", "PtLeadJet1", 25, 0., 500.); 
  _h_leadJet1_pt->SetXTitle("p_{T}(1st jet) (GeV)");
  TH1F* _h_leadJet1_eta           = new TH1F("EtaLeadJet1", "EtaLeadJet1", 25, -5., 5);
  _h_leadJet1_eta->SetXTitle("#eta(1st jet)");
  TH1F* _h_leadJet1_phi           = new TH1F("PhiLeadJet1", "PhiLeadJet1", 32, -3.2, 3.2);
  _h_leadJet1_phi->SetXTitle("#phi(1st jet)");
  TH1F* _h_leadJet2_pt            = new TH1F("PtLeadJet2", "PtLeadJet2", 25, 0., 500.); 
  _h_leadJet2_pt->SetXTitle("p_{T}(2nd jet) (GeV)");
  TH1F* _h_leadJet2_eta           = new TH1F("EtaLeadJet2", "EtaLeadJet2", 25, -5., 5);
  _h_leadJet2_eta->SetXTitle("#eta(2nd jet)");
  TH1F* _h_leadJet2_phi           = new TH1F("PhiLeadJet2", "PhiLeadJet2", 32, -3.2, 3.2);
  _h_leadJet2_phi->SetXTitle("#phi(2nd jet)");
  TH1F* _h_leadJet3_pt            = new TH1F("PtLeadJet3", "PtLeadJet3", 25, 0., 500.); 
  _h_leadJet3_pt->SetXTitle("p_{T}(3th jet) (GeV)");
  TH1F* _h_leadJet3_eta           = new TH1F("EtaLeadJet3", "EtaLeadJet3", 25, -5., 5);
  _h_leadJet3_eta->SetXTitle("#eta(3th jet)");
  TH1F* _h_leadJet3_phi           = new TH1F("PhiLeadJet3", "PhiLeadJet3", 32, -3.2, 3.2);
  _h_leadJet3_phi->SetXTitle("#phi(3th jet)");
  TH1F* _h_leadJet4_pt            = new TH1F("PtLeadJet4", "PtLeadJet4", 25, 0., 500.); 
  _h_leadJet4_pt->SetXTitle("p_{T}(4th jet) (GeV)");
  TH1F* _h_leadJet4_eta           = new TH1F("EtaLeadJet4", "EtaLeadJet4", 25, -5., 5);
  _h_leadJet4_eta->SetXTitle("#eta(4th jet)");
  TH1F* _h_leadJet4_phi           = new TH1F("PhiLeadJet4", "PhiLeadJet4", 32, -3.2, 3.2);
  _h_leadJet4_phi->SetXTitle("#phi(4th jet)");

  TH1F* _h_met_met                = new TH1F("MetMet", "MetMet", 35, 0., 350.);
  _h_met_met->SetXTitle("MET (GeV)");
  TH1F* _h_met_phi                = new TH1F("PhiMet", "PhiMet", 32, -3.2, 3.2);
  _h_met_phi->SetXTitle("#phi(MET)");
  TH1F* _h_W_mt                   = new TH1F("MtW", "MtW", 30, 0., 300.);
  _h_W_mt->SetXTitle("W transverse mass (GeV)");

  TH1F* _h_vertex_n               = new TH1F("NVertices", "NVertices", 20, 0., 40.);
  _h_vertex_n->SetXTitle("Number of vertices");
  TH1F* _h_vertex_x               = new TH1F("XVertices", "XVertices", 25, 0., 0.5);
  _h_vertex_x->SetXTitle("x(vertices) (cm)");
  TH1F* _h_vertex_y               = new TH1F("YVertices", "YVertices", 25, 0., 0.5);
  _h_vertex_y->SetXTitle("y(vertices) (cm)");
  TH1F* _h_vertex_z               = new TH1F("ZVertices", "ZVertices", 15, -30., 30.);
  _h_vertex_z->SetXTitle("z(vertices) (cm)");
  TH1F* _h_vertex_ndof            = new TH1F("NdofVertices", "NdofVertices", 25, 0., 250.);
  _h_vertex_ndof->SetXTitle("Number of degrees of freedom (vertices)");
  TH1F* _h_vertex_chi2Norm        = new TH1F("NormChi2Vertices","NormChi2Vertices", 10, 0., 5.);
  _h_vertex_chi2Norm->SetXTitle("Normalized #chi^{2}(vertices)");
  TH1F* _h_vertex_isFake          = new TH1F("IsFakeVertex","IsFakeVertex", 3, 0., 3.);
  _h_vertex_isFake->SetXTitle("Vertex validity");
  TH1F* _h_vertex_nTracks         = new TH1F("NTracksVertices","NTracksVertices", 70, 0., 140.);
  _h_vertex_nTracks->SetXTitle("Track multiplicity per vertex");

  TH1F* _h_leadVertex_x           = new TH1F("XLeadingVertex", "XLeadingVertex", 25, 0., 0.5);
  _h_leadVertex_x->SetXTitle("x(main vertex) (cm)");
  TH1F* _h_leadVertex_y           = new TH1F("YLeadingVertex", "YLeadingVertex", 25, 0., 0.5);
  _h_leadVertex_y->SetXTitle("y(main vertex) (cm)");
  TH1F* _h_leadVertex_z           = new TH1F("ZLeadingVertex", "ZLeadingVertex", 15, -30., 30.);
  _h_leadVertex_z->SetXTitle("z(main vertex) (cm)");
  TH1F* _h_leadVertex_ndof        = new TH1F("NdofLeadingVertex", "NdofLeadingVertex", 25, 0., 250.);
  _h_leadVertex_ndof->SetXTitle("Number of degrees of freedom (main vertex)");
  TH1F* _h_leadVertex_chi2Norm    = new TH1F("NormChi2LeadingVertex","NormChi2LeadingVertex", 10, 0., 5.);
  _h_leadVertex_chi2Norm->SetXTitle("Normalized #chi^{2}(main vertex)");
  TH1F* _h_leadVertex_isFake      = new TH1F("IsFakeLeadingVertex","IsFakeLeadingVertex", 3, 0., 3.);
  _h_leadVertex_isFake->SetXTitle("Main vertex validity");
  TH1F* _h_leadVertex_nTracks     = new TH1F("NTracksLeadingVertex","NTracksLeadingVertex", 100, 0., 200.);
  _h_leadVertex_nTracks->SetXTitle("Track multiplicity for the main vertex");

  TH1F* _h_jpsi_n                 = new TH1F("NJpsi", "NJpsi", 3, 0., 3.);
  _h_jpsi_n->SetXTitle("Number of J/#psi");
  TH1F* _h_jpsi_m                 = new TH1F("MJpsi", "MJpsi", 8, 3., 3.2);
  _h_jpsi_m->SetXTitle("J/#psi mass (GeV)");
  TH1F* _h_jpsi_pt                = new TH1F("PtJpsi", "PtJpsi", 28, 0., 140.);   
  _h_jpsi_pt->SetXTitle("p_{T} (J/#psi) (GeV)");
  TH1F* _h_jpsi_eta               = new TH1F("EtaJpsi", "EtaJpsi", 30, -3., 3.); 
  _h_jpsi_eta->SetXTitle("#eta (J/#psi)");
  TH1F* _h_jpsi_phi               = new TH1F("PhiJpsi", "PhiJpsi", 32, -3.2, 3.2); 
  _h_jpsi_phi->SetXTitle("#phi (J/#psi)");
  TH1F* _h_jpsi_chi2              = new TH1F("Chi2Jpsi", "Chi2Jpsi", 16, 0., 8.);
  _h_jpsi_chi2->SetXTitle("#chi^{2}(J/#psi vertex)");
  TH1F* _h_jpsi_l                 = new TH1F("LJpsi", "LJpsi", 25, 0., 0.5);
  _h_jpsi_l->SetXTitle("c#tau(J/#psi) (cm)");
  TH1F* _h_jpsi_l_zoom            = new TH1F("LJpsi-zoom", "LJpsi-zoom", 100, 0., 0.05);
  _h_jpsi_l_zoom->SetXTitle("c#tau(J/#psi) (cm)");
  TH1F* _h_jpsi_sigmaL            = new TH1F("SigmaLJpsi", "SigmaLJpsi", 30, 0., 0.0015);
  _h_jpsi_sigmaL->SetXTitle("#Delta(c#tau)(J/#psi) (cm)");
  TH1F* _h_jpsi_lOverSigma        = new TH1F("LOverSigmaJpsi", "LOverSigmaJpsi", 42, 0., 7000.);
  _h_jpsi_lOverSigma->SetXTitle("(c#tau)/#Delta(c#tau)(J/#psi)");
  TH1F* _h_jpsi_jetPtFrac         = new TH1F("PtFracJpsiJet", "PtFracJpsiJet", 20, 0., 1.);
  _h_jpsi_jetPtFrac->SetXTitle("p_{T}(J/#psi)/p_{T}(jet)");
  TH1F* _h_jpsiraw_jetPtFrac      = new TH1F("PtFracJpsiRawJet", "PtFracJpsiRawJet", 20, 0., 1.);
  _h_jpsiraw_jetPtFrac->SetXTitle("p_{T}(J/#psi)/p_{T}(jet)");

  TH1F* _h_jpsi_dPhiLept          = new TH1F("DPhiJpsiIsoLept", "DPhiJpsiIsoLept", 16, 0., 4.);
  _h_jpsi_dPhiLept->SetXTitle("#Delta#phi (J/#psi-leading #mu)");
  TH1F* _h_jpsi_dRLept            = new TH1F("DRJpsiIsoLept", "DRJpsiIsoLept", 20, 0., 5.);
  _h_jpsi_dRLept->SetXTitle("#DeltaR (J/#psi-leading #mu)");

  TH1F* _h_muJpsi_pt              = new TH1F("PtMuJpsi", "PtMuJpsi", 15, 0., 150.);  
  _h_muJpsi_pt->SetXTitle("p_{T}(#mu^{#pm}) (GeV)");
  TH1F* _h_muJpsi_pt_zoom         = new TH1F("PtMuJpsi-zoom", "PtMuJpsi-zoom", 20, 0., 10.);  
  _h_muJpsi_pt_zoom->SetXTitle("p_{T}(#mu^{#pm}) (GeV)");
  TH1F* _h_muJpsi_eta             = new TH1F("EtaMuJpsi", "EtaMuJpsi", 30, -3., 3.); 
  _h_muJpsi_eta->SetXTitle("#eta(#mu^{#pm})");
  TH1F* _h_muJpsi_phi             = new TH1F("PhiMuJpsi", "PhiMuJpsi", 32, -3.2, 3.2);
  _h_muJpsi_phi->SetXTitle("#phi(#mu^{#pm})");

  TH1F* _h_jetJpsi_pt               = new TH1F("PtJetJpsi", "PtJetJpsi", 25, 0., 500.); 
  _h_jetJpsi_pt->SetXTitle("p_{T}(jets with a J/#psi) (GeV)");
  TH1F* _h_jetJpsi_csv              = new TH1F("CsvJetJpsi", "CsvJetJpsi", 50, 0., 1.);
  _h_jetJpsi_csv->SetXTitle("CSV discriminant (jets with a J/#psi)");
  TH1F* _h_jetJpsi_chmult           = new TH1F("ChMultJetJpsi", "ChMultJetJpsi", 50, 0., 50.);
  _h_jetJpsi_chmult->SetXTitle("Charge multiplicity (jets with a J/#psi)");
  TH1F* _h_jetJpsi_chMuEFrac        = new TH1F("ChMuEFracJetJpsi", "ChMuEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_chMuEFrac->SetXTitle("#mu^{#pm} energy fraction (jets with a J/#psi)");
  TH1F* _h_jetJpsi_chEMEFrac        = new TH1F("ChEMEFracJetJpsi", "ChEMEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_chEMEFrac->SetXTitle("e^{#pm} energy fraction (jets with a J/#psi)");
  TH1F* _h_jetJpsi_chHadEFrac       = new TH1F("ChHadEFracJetJpsi", "ChHadEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_chHadEFrac->SetXTitle("Charged hadron energy fraction (jets with a J/#psi)");
  TH1F* _h_jetJpsi_chEFrac          = new TH1F("ChEFracJetJpsi", "ChEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_chEFrac->SetXTitle("Charged energy fraction (jets with a J/#psi)");
  TH1F* _h_jetJpsi_nEMEFrac        = new TH1F("NEMEFracJetJpsi", "NEMEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_nEMEFrac->SetXTitle("#gamma energy fraction (jets with a J/#psi)");
  TH1F* _h_jetJpsi_nHadEFrac       = new TH1F("NHadEFracJetJpsi", "NHadEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_nHadEFrac->SetXTitle("Neutral hadron energy fraction (jets with a J/#psi)");
  TH1F* _h_jetJpsi_nEFrac          = new TH1F("NEFracJetJpsi", "NEFracJetJpsi", 50, 0., 1.);
  _h_jetJpsi_nEFrac->SetXTitle("Neutral energy fraction (jets with a J/#psi)");

  TH1F* _h_triLept_m              = new TH1F("MTriLept-allPair", "MTriLept-allPair", 25, 0., 250.);
  _h_triLept_m->SetXTitle("M(J/#psi+#mu) (GeV)");
  TH1F* _h_triLept_goodPair_m     = new TH1F("MTriLept-goodPair", "MTriLept-goodPair", 25, 0., 250.);
  _h_triLept_goodPair_m->SetXTitle("M(J/#psi+#mu, from same top) (GeV)");
  TH1F* _h_triLept_wrongPair_m    = new TH1F("MTriLept-wrongPair", "MTriLept-wrongPair", 25, 0., 250.);
  _h_triLept_wrongPair_m->SetXTitle("M(J/#psi+#mu, not from same top) (GeV)");
  TH1F* _h_triLept_pt             = new TH1F("PtTriLept", "PtTriLept", 25, 0., 250.); 
  _h_triLept_pt->SetXTitle("p_{T}(J/#psi+#mu) (GeV)");
  TH1F* _h_jpsi_resR              = new TH1F("ResRJpsi", "ResRJpsi", 200, 0., 0.1); 
  _h_jpsi_resR->SetXTitle("#DeltaR(gen-reco J/#psi)");
  TH1F* _h_jpsi_resPt 	          = new TH1F("ResPtJpsi", "ResPtJpsi", 20,0.,0.2); 
  _h_jpsi_resPt->SetXTitle("#Deltap_{T}(gen-reco J/#psi)/p_{T}^{gen}(J/#psi)");
  TH1F* _h_isoLept_resR		        = new TH1F("ResRIsoLept", "ResRIsoLept", 50, 0., 0.2); 
  _h_isoLept_resR->SetXTitle("#DeltaR(gen-reco iso #mu)");
  TH1F* _h_isoLept_resPt		      = new TH1F("ResPtIsoLept", "ResPtIsoLept", 80, 0., 0.2); 
  _h_isoLept_resPt->SetXTitle("#Deltap_{T}(gen-reco iso #mu)/p_{T}^{gen}(iso #mu)");

  TH1F* _h_bjj_m                  = new TH1F("bjjMass", "bjjMass", 25, 0., 500.);
  _h_bjj_m->SetXTitle("M(bjj) (GeV)");
  TH1F* _h_W_m                    = new TH1F("WMass", "WMass", 20, 0., 200.);
  _h_W_m->SetXTitle("W mass (GeV)");

  TTree* _t_triLept_m       = new TTree("MTriLept","MTriLept");
  float triLept_mass, triLept_weight;
  _t_triLept_m->Branch("mass", &triLept_mass, "mass/F");  
  _t_triLept_m->Branch("weight", &triLept_weight, "weight/F");  

  TTree* _t_pairingStudies_m       = new TTree("PairingStudies","PairingStudies");
  float weight_m, jpsi_m_m, jpsi_pt_m, jpsi_eta_m, jpsi_phi_m, jpsi_chi2_m, jpsi_l_m, jpsi_lOverSig_m,
        jpsi_sigmaL_m, jpsi_jetPtFrac_m, jetJpsi_pt_m, jetJpsi_csv_m, jetJpsi_chMuEFrac_m, jetJpsi_chEMEFrac_m, 
        jetJpsi_chHadEFrac_m, jetJpsi_chEFrac_m, jetJpsi_nEMEFrac_m, jetJpsi_nHadEFrac_m, jetJpsi_nEFrac_m,
        isoLept_pt_m, isoLept_eta_m, isoLept_phi_m, jpsi_dPhiLept_m, jpsi_dRLept_m, triLept_m_m, triLept_pt_m,
        jet20_n_m, pairing_m; // -1 if wrong, +1 if good
  _t_pairingStudies_m->Branch("Weight", &weight_m, "Weight/F");
  _t_pairingStudies_m->Branch("Pairing", &pairing_m, "Pairing/F");
  _t_pairingStudies_m->Branch("NJets20", &jet20_n_m, "NJets20/F");
  _t_pairingStudies_m->Branch("MJpsi", &jpsi_m_m, "MJpsi/F");
  _t_pairingStudies_m->Branch("PtJpsi", &jpsi_pt_m, "PtJpsi/F");
  _t_pairingStudies_m->Branch("EtaJpsi", &jpsi_eta_m, "EtaJpsi/F");
  _t_pairingStudies_m->Branch("PhiJpsi", &jpsi_phi_m, "PhiJpsi/F");
  _t_pairingStudies_m->Branch("Chi2Jpsi", &jpsi_chi2_m, "Chi2Jpsi/F");
  _t_pairingStudies_m->Branch("LJpsi", &jpsi_l_m, "LJpsi/F");
  _t_pairingStudies_m->Branch("SigmaLJpsi", &jpsi_sigmaL_m, "SigmaLJpsi/F");
  _t_pairingStudies_m->Branch("LOverSigmaJpsi", &jpsi_lOverSig_m, "LOverSigmaJpsi/F");
  _t_pairingStudies_m->Branch("PtFracJpsiJet", &jpsi_jetPtFrac_m, "PtFracJpsiJet/F");
  _t_pairingStudies_m->Branch("PtJetJpsi", &jetJpsi_pt_m, "PtJetJpsi/F");
  _t_pairingStudies_m->Branch("CsvJetJpsi", &jetJpsi_csv_m, "CsvJetJpsi/F");
  _t_pairingStudies_m->Branch("ChMuEFracJetJpsi", &jetJpsi_chMuEFrac_m, "ChMuEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("ChEMEFracJetJpsi", &jetJpsi_chEMEFrac_m, "ChEMEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("ChHadEFracJetJpsi", &jetJpsi_chHadEFrac_m, "ChHadEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("ChEFracJetJpsi", &jetJpsi_chEFrac_m, "ChEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("NEMEFracJetJpsi", &jetJpsi_nEMEFrac_m, "NEMEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("NHadEFracJetJpsi", &jetJpsi_nHadEFrac_m, "NHadEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("NEFracJetJpsi", &jetJpsi_nEFrac_m, "NEFracJetJpsi/F");
  _t_pairingStudies_m->Branch("PtIsoLept", &isoLept_pt_m, "PtIsoLept/F");
  _t_pairingStudies_m->Branch("EtaIsoLept", &isoLept_eta_m, "EtaIsoLept/F");
  _t_pairingStudies_m->Branch("PhiIsoLept", &isoLept_phi_m, "PhiIsoLept/F");
  _t_pairingStudies_m->Branch("DPhiJpsiIsoLept", &jpsi_dPhiLept_m, "DPhiJpsiIsoLept/F");
  _t_pairingStudies_m->Branch("DRJpsiIsoLept", &jpsi_dRLept_m, "DRJpsiIsoLept/F");
  _t_pairingStudies_m->Branch("MTriLept", &triLept_m_m, "MTriLept/F");
  _t_pairingStudies_m->Branch("PtTriLept", &triLept_pt_m, "PtTriLept/F");

  //================================================================================================
  // Clone the tree
  //================================================================================================

  if (_doSkim) {
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

  TString cutName[100]; for (int i = 0; i < 100; ++i) cutName[i] = "";

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
      _h_PUBefore->Fill((float)nTrueInteractions, _weight);
      int npu = (int) nTrueInteractions;
      if (npu > 79) npu = 79;
      _weight = _weight * myPUReweighter->weight(npu);
      _h_PUAfter->Fill((float)nTrueInteractions, _weight);
    }

    int iCut = 0;
    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = "Starting"; ++iCut; // /!\ no SF 
    _h_iCut->GetXaxis()->SetBinLabel(iCut, "Starting");

    //======================================================
    // LHAPDF 
    //======================================================

    // Using the reweighting method
    // See https://www.hep.ucl.ac.uk/pdf4lhc/PDF4LHC_practical_guide.pdf
    // https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopSystematics#PDF_uncertainties
    // http://cms.cern.ch/iCMS/jsp/openfile.jsp?tp=draft&files=AN2009_048_v1.pdf

    /*
    double xpdf1 = pdfs[0]->xfxQ(pdf_id1, pdf_x1, pdf_scale);
    double xpdf2 = pdfs[0]->xfxQ(pdf_id2, pdf_x2, pdf_scale);
    double w0 = xpdf1 * xpdf2;
    double pdfWeight = 0.;
    unsigned int Nmembers_pdf = set.size();
    unsigned int N_error_pdf = (Nmembers_pdf-1)/2;
    double xpdf1_new = 0.;
    double xpdf2_new = 0.;
    double pdf_weight = 1.;
    vector<double> pdf_weight_down;
    vector<double> pdf_weight_up;
    for (size_t imem = 1; imem < Nmembers_pdf; imem++) {
      xpdf1_new = pdfs[imem]->xfxQ(pdf_id1, pdf_x1, pdf_scale);
      xpdf2_new = pdfs[imem]->xfxQ(pdf_id2, pdf_x2, pdf_scale);
      pdf_weight = xpdf1_new * xpdf2_new / w0;
      if (imem % 2 == 0) {
        // up case
        pdf_weight_down.push_back(pdf_weight); 
      } else {
        // down case
        pdf_weight_up.push_back(pdf_weight); 
      }
    }
    double cfac = 1.;
    if (setname.find("CT10") != std::string::npos || setname.find("CT14") != std::string::npos) 
      cfac = 1./1.64485;
    if (devUp) {
      for (unsigned int iev = 0; iev < N_error_pdf; iev++) {
        double max = std::max(std::max(pdf_weight_up[iev]-1.,pdf_weight_down[iev]-1.),0.);
        pdfWeight += max * max;  
      }
      pdfWeight = 1. + cfac * sqrt(pdfWeight);
    }
    else {
      for (unsigned int iev = 0; iev < N_error_pdf; iev++) {
        double max = std::max(std::max(1.-pdf_weight_up[iev],1.-pdf_weight_down[iev]),0.);
        pdfWeight += max * max;  
      }
      pdfWeight = 1. - cfac * sqrt(pdfWeight);
    }
    if (_debug) cout << "pdfWeight = " << pdfWeight << endl;
    _weight = _weight*pdfWeight;
    */

    //======================================================
    // Trigger
    //======================================================

    bool passTrigger = false;

    if (!_isMC) {
      for ( unsigned int i=0; i<HLT_vector->size(); ++i){
        TString ThistrigName= (TString) HLT_vector->at(i);        
        if (ThistrigName.Contains("HLT_IsoMu24_eta2p1")) passTrigger = true;
      }
    }	

    if (!passTrigger && !_isMC) continue;  
    ++counter[0];
    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Trigger"; ++iCut; // /!\ no SF 
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Trigger");

    //================================================================================================
    // Objects selection 
    //================================================================================================

    vector<unsigned int> indgoodmu;
    vector<unsigned int> indsoftel;
    vector<unsigned int> indsoftmu;
    vector<unsigned int> indgoodjet;
    vector<unsigned int> indgoodver;
    vector<unsigned int> indgoodjpsi;

    //======================================================
    // Good muons selection
    //======================================================

    if (_debug) cout <<" -> loose muons size "<< n_muonsloose << endl;

    for (unsigned int i = 0; i < n_muonsloose; ++i) {

      float muPt = GetP4(muonloose_4vector,i)->Pt();
      float muEta = GetP4(muonloose_4vector,i)->Eta();

      if (!muonloose_isGlobal[i]) continue;
      if (muPt <= 26) continue;
      if (fabs(muEta) >= 2.1) continue;
      if (muonloose_normChi2[i] >= 10) continue;
      if (muonloose_trackerLayersWithMeasurement[i] <= 5) continue;
      if (muonloose_globalTrackNumberOfValidHits[i] <= 0) continue;
      if (muonloose_nMatchedStations[i] <= 1) continue;
      if (muonloose_dB[i] >= 0.2) continue;
      if (muonloose_dZ[i] >= 0.5) continue;
      if (muonloose_nValPixelHits[i] <= 0) continue; 
      if (muonloose_deltaBetaCorrectedRelIsolation[i] >= 0.12) continue;

      indgoodmu.push_back(i);
    }
    unsigned int ngoodmuon = indgoodmu.size();

    _h_cuts_muons_n->Fill((float)ngoodmuon, _weight);

    if (_debug) cout << "Number of good muons = " << ngoodmuon << endl;

    if (ngoodmuon < 1) continue;
    ++counter[1];
    if (_isMC) {
      // Trigger scalefactors
      _weight = _weight*weight_provider->get_weight_isomu(GetP4(muonloose_4vector, indgoodmu[0])->Pt(), GetP4(muonloose_4vector, indgoodmu[0])->Eta()); 
    }

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = ">=1 isolated #mu"; ++iCut; 
    _h_iCut->GetXaxis()->SetBinLabel(iCut, ">=1 isolated #mu");

    //======================================================
    // Soft electrons selection
    //======================================================

    if (_debug) cout << " -> loose electrons size " << n_electronsloose << endl;

    for (unsigned int i = 0; i < n_electronsloose; ++i) {
      float elPt = GetP4(electronloose_4vector,i)->Pt();
      float elEta = GetP4(electronloose_4vector,i)->Eta();
      if (elPt <= 20) continue;
      if (fabs(elEta) >= 2.5) continue;
      if (!electronloose_passVetoID[i]) continue;
      if (electronloose_rhoCorrectedRelIsolation[i] >= 0.15) continue;
      indsoftel.push_back(i);
    }
    unsigned int nsoftelectron = indsoftel.size();

    _h_cuts_electrons_n->Fill((float)nsoftelectron, _weight);

    if (_debug) cout << "Number of soft electrons = " << nsoftelectron << endl;

    //======================================================
    // Soft muons selection
    //======================================================

    if (_debug) cout << " -> loose muons size " << n_muonsloose << endl;

    for (unsigned int i = 0; i < n_muonsloose; ++i) {
      if (i == indgoodmu[0]) continue;
      float muPt = GetP4(muonloose_4vector,i)->Pt();
      float muEta = GetP4(muonloose_4vector,i)->Eta();
      if (!muonloose_isGlobal[i] && !muonloose_isTracker[i]) continue;
      if (muPt <= 10) continue;
      if (fabs(muEta) >= 2.5) continue;
      if (muonloose_deltaBetaCorrectedRelIsolation[i] >= 0.2) continue;
      indsoftmu.push_back(i);
    }
    unsigned int nsoftmuon = indsoftmu.size();

    _h_cuts_muons_n->Fill((float)nsoftmuon, _weight);

    if (_debug) cout << "Number of soft muons = " << nsoftmuon << endl;

    //======================================================
    // Vertices
    //======================================================

    if (_debug) cout << " -> vertices size " << n_vertices << endl;

    for (unsigned int i = 0; i < n_vertices; ++i) {
      if (vertex_isFake[i]) continue;
      if (vertex_ndof[i] <= 4) continue;   
      indgoodver.push_back(i);
    }
    unsigned int nvtx = indgoodver.size();

    if (_debug) cout << "Number of good vertices " << nvtx << endl;

    //======================================================
    // Good jet selection
    //======================================================

    int njet30 = 0;
    int njet40 = 0;
    int njet50 = 0;
    int nbjet  = 0;

    if (_debug) cout << " -> jets size " << n_jets << endl;

    for (unsigned int i = 0; i < n_jets; ++i) {
      float jetPt = GetP4(jet_4vector,i)->Pt();
      float jetEta = GetP4(jet_4vector,i)->Eta();
      if (jetPt <= 20.) continue;
      if (fabs(jetEta) >= 2.4) continue;
      if (jetPt >= 30.) ++njet30;
      if (jetPt >= 40.) ++njet40;
      if (jetPt >= 50.) ++njet50;

      if (jet_btag_CSV[i] > 0.814) ++nbjet; 

      indgoodjet.push_back(i);
    }
    unsigned int ngoodjet = indgoodjet.size();

    _h_cuts_jet20_n->Fill((float)ngoodjet, _weight);
    _h_cuts_jet30_n->Fill((float)njet30, _weight);
    _h_cuts_jet40_n->Fill((float)njet40, _weight);
    _h_cuts_jet50_n->Fill((float)njet50, _weight);
    _h_cuts_csvJet20_n->Fill((float)nbjet, _weight);

    if (_debug) cout << "Number of good jets = " << ngoodjet << endl;

    if (njet40 < 2) continue;
    ++counter[2];

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = ">=2 jets with p_{T}>40 GeV"; ++iCut;  
    _h_iCut->GetXaxis()->SetBinLabel(iCut, ">=2 jets with p_{T}>40 GeV");

    //======================================================
    // MET
    //======================================================

    float MET_Pt = 0.;
    float MET_Phi = 0.;

    if (met_4vector->GetSize() == 0) { 
      cout << "WARNING : no Met in this event !!!" << endl;
    } else {
      MET_Pt= GetP4(met_4vector,0)->Pt();
      MET_Phi= GetP4(met_4vector,0)->Phi();
    }

    //======================================================
    // Apply veto
    //======================================================
    
    bool isSemiLept = false;
    bool isDiLept = false;
    bool isDiLept_same = false;

    if (ngoodmuon == 1 && nsoftmuon == 0 && nsoftelectron == 0) {
      isSemiLept = true;
      ++counter[3];
    }
    else { // if (MET_Pt > 40) {
      for (unsigned int imu = 0; imu < nsoftmuon; imu++) {
        float muPt = GetP4(muonloose_4vector,indsoftmu[imu])->Pt();
        float muEta = GetP4(muonloose_4vector,indsoftmu[imu])->Eta();
        if (!muonloose_isGlobal[indsoftmu[imu]] && !muonloose_isTracker[indsoftmu[imu]]) continue;
        if (muPt <= 20) continue;
        if (fabs(muEta) >= 2.4) continue;
        if (muonloose_deltaBetaCorrectedRelIsolation[indsoftmu[imu]] >= 0.2) continue;
        if (muonloose_charge[indgoodmu[0]]*muonloose_charge[indsoftmu[imu]] >= 0) continue;
        TLorentzVector *sum1 = GetP4(muonloose_4vector,indgoodmu[0]); 
        TLorentzVector *sum2 = GetP4(muonloose_4vector,indsoftmu[imu]);
        TLorentzVector sum = *sum1 + *sum2;
        if (sum.M() > 20 && (sum.M() <= 76 || sum.M() > 106)) {
          isDiLept = true;
          isDiLept_same = true;
          break;
        }
      }
      for (unsigned int iel = 0; iel < nsoftelectron; iel++) {
        float elPt = GetP4(electronloose_4vector,indsoftel[iel])->Pt();
        float elEta = GetP4(electronloose_4vector,indsoftel[iel])->Eta();
        if (elPt <= 20) continue;
        if (fabs(elEta) >= 2.5) continue;
        if (!electronloose_passTightID[indsoftel[iel]]) continue;
        if (electronloose_rhoCorrectedRelIsolation[indsoftel[iel]] >= 0.15) continue;
        if (muonloose_charge[indgoodmu[0]]*electronloose_charge[indsoftel[iel]] >= 0) continue;
        if (elPt > GetP4(muonloose_4vector, indgoodmu[0])->Pt()) continue;
        TLorentzVector *sum1 = GetP4(muonloose_4vector,indgoodmu[0]);
        TLorentzVector *sum2 = GetP4(electronloose_4vector,indsoftel[iel]);
        TLorentzVector sum = *sum1 + *sum2;
        if (sum.M() > 20) {
          isDiLept = true;
          break;
        }
      }
      if (isDiLept) ++counter[4];
    }

    // if (!isSemiLept) continue;
    // if (!isDiLept) continue;
    if (!isSemiLept && !isDiLept) continue;

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = "e/#mu veto"; ++iCut; 
    _h_iCut->GetXaxis()->SetBinLabel(iCut, "e/#mu veto");

    //======================================================
    // J/psi
    //======================================================

    // Mass
    for (int j = 0; j < n_jpsi; ++j) {
      if (GetP4(jpsi_4vector, j)->M() >= 3. && GetP4(jpsi_4vector, j)->M() <= 3.2) {
        _h_cuts_jpsi_m->Fill(GetP4(jpsi_4vector,j)->M(), _weight);
        indgoodjpsi.push_back(j);
      }
    }
    unsigned int njpsi = indgoodjpsi.size();

    if (_debug) cout << " Number of J/Psi candidate = " << njpsi << endl;

    _h_cuts_jpsi_n->Fill((float)njpsi, _weight);
    
    // Mass spectrum with sidebands
    if (njpsi < 2) {
      for (int j = 0; j < n_jpsi; ++j) {
        if (jpsi_vtxchi2[j] > 5.) continue;
        if (jpsi_L3DoverSigmaL3D[j] < 20.) continue;
        if (GetP4(jpsi_4vector, j)->M() >= 2.8 && GetP4(jpsi_4vector, j)->M() <= 3.4) {
          // Jpsi reweighting
          /*
          if (_isMC)
            _h_large_jpsi_m->Fill(GetP4(jpsi_4vector,j)->M(), _weight*myJpsiReweighter->getEventWeight(GetP4(jpsi_4vector, j)->M()));
          else
          */
            _h_large_jpsi_m->Fill(GetP4(jpsi_4vector,j)->M(), _weight);
        }
      }
    }

    if (njpsi > 1 && _debug) cout << "! More than one J/psi (" << njpsi << ") !" << endl;
    if (njpsi != 1) continue;
    ++counter[5];

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = "Exactly 1 J/psi"; ++iCut; 
    _h_iCut->GetXaxis()->SetBinLabel(iCut, "Exactly 1 J/psi");

    // Chi2
    _h_cuts_jpsi_chi2->Fill(jpsi_vtxchi2[indgoodjpsi[0]], _weight);
    if (jpsi_vtxchi2[indgoodjpsi[0]] > 5.) continue;
    ++counter[6];

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = "... with #chi2<5"; ++iCut; 
    _h_iCut->GetXaxis()->SetBinLabel(iCut, "... with #chi2<5");

    // ctau
    _h_cuts_jpsi_l->Fill(jpsi_L3D[indgoodjpsi[0]], _weight);
    _h_cuts_jpsi_l_zoom->Fill(jpsi_L3D[indgoodjpsi[0]], _weight);
    /*
    if (jpsi_L3D[indgoodjpsi[0]] <= 0.005) continue; 
    ++counter[7];

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = "... and c#tau>0.005 cm"; ++iCut;  
    _h_iCut->GetXaxis()->SetBinLabel(iCut, "... and c#tau>0.005 cm"); 
    */
    // ctau/sigma
    _h_cuts_jpsi_lOverSig->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]], _weight);
    _h_cuts_jpsi_lOverSig_zoom->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]], _weight);

    if (jpsi_L3DoverSigmaL3D[indgoodjpsi[0]] < 20.) continue;
    ++counter[7];

    _h_iCut->Fill((float)iCut, _weight); cutName[iCut] = "... and #Delta(c#tau)/c#tau>20"; ++iCut;  
    _h_iCut->GetXaxis()->SetBinLabel(iCut, "... and #Delta(c#tau)/c#tau>20"); 

    // dR with lepton
    _h_cuts_jpsi_dRLept->Fill(kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(muonloose_4vector,indgoodmu[0])->Eta(),GetP4(muonloose_4vector,indgoodmu[0])->Phi()), _weight);

    //======================================================
    //Isolation from muons
    //======================================================
    // not meaningfull as we reconstruct J/psi within jets now
    /*
    float dR1 = kinem::delta_R(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Eta(), GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Phi(), 
        GetP4(muonloose_4vector,indgoodmu[0])->Eta(), GetP4(muonloose_4vector,indgoodmu[0])->Phi());
    float dR2 = kinem::delta_R(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Eta(), GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Phi(), 
        GetP4(muonloose_4vector,indgoodmu[0])->Eta(), GetP4(muonloose_4vector,indgoodmu[0])->Phi());
    if (dR1 < 0.005 || dR2 < 0.005) continue;

    float isolike = 0;
    if (dR1 < 0.4 || dR2 < 0.4) {
      isolike = (muonloose_deltaBetaCorrectedRelIsolation[indgoodmu[0]]*GetP4(muonloose_4vector, indgoodmu[0])->Pt() 
          + GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Pt() + GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Pt()) / GetP4(muonloose_4vector, indgoodmu[0])->Pt();
      cout << "isolike calculation... before = " << muonloose_deltaBetaCorrectedRelIsolation[indgoodmu[0]] << " after = " << isolike << endl;
    } 
    else 
      isolike = muonloose_deltaBetaCorrectedRelIsolation[indgoodmu[0]];

    if (isolike <= 0.12) 
    ++counter[8];
    */
    //======================================================
    // Scale factors
    //======================================================

    if (_isMC) {
      // Trigger scalefactors
      /*
       * already applied after lepton selection
      HiggsTriggerEfficiencyProvider *weight_provider = new HiggsTriggerEfficiencyProvider();
      _weight = _weight*weight_provider->get_weight_isomu(GetP4(muonloose_4vector, indgoodmu[0])->Pt(), GetP4(muonloose_4vector, indgoodmu[0])->Eta()); 
      */
      // Muon scalefactor
      /*
      _weight = _weight*(*muonloose_scaleFactor_tighteff_tightiso)[indgoodmu[0]][0]; // 0 for central, 1 for up, 2 for down
      */
      // Jet scalefactors
      /*
      _weight = _weight*(*jet_scaleFactor)[indgoodjet[0]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jet_scaleFactor)[indgoodjet[1]][0]; // 0 for central, 1 for up, 2 for down
      */
      // Jpsi scalefactors
      /*
      _weight = _weight*(*jpsi_mu1_muon_scaleFactor_looseeff_looseiso)[indgoodjpsi[0]][0]; // 0 for central, 1 for up, 2 for down
      _weight = _weight*(*jpsi_mu2_muon_scaleFactor_looseeff_looseiso)[indgoodjpsi[0]][0]; // 0 for central, 1 for up, 2 for down
      */
      // Top-pt 
      /*
      if (_isTTbar) {
        float topPtWeight = 1.;
        for (int iMC = 0; iMC < n_MCs; iMC++) {
          if (abs(MC_type[iMC]) != 6) continue;
          if (GetP4(MC_4vector, iMC)->Pt() > 400.) continue;
          topPtWeight = topPtWeight*std::exp(0.159-0.00141*GetP4(MC_4vector, iMC)->Pt());
        }
        _weight = _weight*sqrt(topPtWeight);
      }
      */
      // Jpsi reweighting
      /*
      _weight = _weight*myJpsiReweighter->getEventWeight(GetP4(jpsi_4vector, indgoodjpsi[0])->M());
      */
      // Pt(J/psi)/Pt(b jet)
      double xJpsi = -1.;
      double dRJpsibjetmin = 200.;
      for (int igenpart = 0; igenpart < n_MCs; igenpart++) {
        if (GetP4(MC_JPsi_4vector,igenpart)->Pt() < 1e-4 || GetP4(MC_JPsi_4vector,igenpart)->Pt() != GetP4(MC_JPsi_4vector,igenpart)->Pt() || fabs(GetP4(MC_JPsi_4vector,igenpart)->CosTheta()) > 0.999 || fabs(GetP4(MC_JPsi_4vector,igenpart)->CosTheta()) < 1e-3) continue;
        for (unsigned int igenjet = 0; igenjet < n_jets; igenjet++) {
          if (GetP4(genjet_4vector,igenjet)->Pt() != GetP4(genjet_4vector,igenjet)->Pt() || fabs(GetP4(genjet_4vector,igenjet)->CosTheta()) > 0.999 || fabs(GetP4(genjet_4vector,igenjet)->CosTheta()) < 1e-3) continue;
          // if (abs(jet_physics_parton_pdgid[igenjet]) != 5) continue;
          if (abs(jet_algo_parton_flavor[igenjet]) != 5) continue;
          double dRJpsibjet = GetP4(genjet_4vector,igenjet)->DeltaR(*GetP4(MC_JPsi_4vector,igenpart)); 
          if (dRJpsibjet < dRJpsibjetmin) {
            dRJpsibjetmin = dRJpsibjet;
            xJpsi = GetP4(MC_JPsi_4vector,igenpart)->Pt()/GetP4(genjet_4vector,igenjet)->Pt();
          }
        }
      }
      // Bfrag reweighting
      /*
      _weight = _weight*myBfragReweighter->getEventWeight(xJpsi);
      */
      _h_dRJpsibjet_gen->Fill(dRJpsibjetmin, _weight);
      _h_pTJpsiOverpTbjet_gen->Fill(xJpsi, _weight);
      // Pt(J/psi)/Pt(B had)
      double xJpsixB = -1.;
      double dRJpsiBhadmin = 200.;
      for (int igenpart = 0; igenpart < n_MCs; igenpart++) {
        if (GetP4(MC_JPsi_4vector,igenpart)->Pt() < 1e-4 || GetP4(MC_JPsi_4vector,igenpart)->Pt() != GetP4(MC_JPsi_4vector,igenpart)->Pt() || fabs(GetP4(MC_JPsi_4vector,igenpart)->CosTheta()) > 0.999 || fabs(GetP4(MC_JPsi_4vector,igenpart)->CosTheta()) < 1e-3) continue;
        for (int jgenpart = 0; jgenpart < n_MCs; jgenpart++) {
          if (GetP4(MC_Bhad_4vector,jgenpart)->Pt() < 1e-4 || GetP4(MC_Bhad_4vector,jgenpart)->Pt() != GetP4(MC_Bhad_4vector,jgenpart)->Pt() || fabs(GetP4(MC_Bhad_4vector,jgenpart)->CosTheta()) > 0.999 || fabs(GetP4(MC_Bhad_4vector,jgenpart)->CosTheta()) < 1e-3) continue;
          double dRJpsiBhad = GetP4(MC_Bhad_4vector,jgenpart)->DeltaR(*GetP4(MC_JPsi_4vector,igenpart)); 
          if (dRJpsiBhad < dRJpsiBhadmin) {
            dRJpsiBhadmin = dRJpsiBhad;
            xJpsixB = GetP4(MC_JPsi_4vector,igenpart)->Pt()/GetP4(MC_Bhad_4vector,jgenpart)->Pt();
          }
        }
      }
      // Bfrag reweighting
      /*
      _weight = _weight*myBfragReweighter->getEventWeight(xJpsiB);
      */
      _h_dRJpsiBhad_gen->Fill(dRJpsiBhadmin, _weight);
      _h_pTJpsiOverpTBhad_gen->Fill(xJpsixB, _weight);
      // Pt(B had)/Pt(b jet)
      double xB = -1.;
      double dRBhadbjetmin = 200.;
      for (int igenpart = 0; igenpart < n_MCs; igenpart++) {
        if (GetP4(MC_Bhad_4vector,igenpart)->Pt() < 1e-4 || GetP4(MC_Bhad_4vector,igenpart)->Pt() != GetP4(MC_Bhad_4vector,igenpart)->Pt() || fabs(GetP4(MC_Bhad_4vector,igenpart)->CosTheta()) > 0.999 || fabs(GetP4(MC_Bhad_4vector,igenpart)->CosTheta()) < 1e-3) continue;
        for (unsigned int igenjet = 0; igenjet < n_jets; igenjet++) {
          if (GetP4(genjet_4vector,igenjet)->Pt() != GetP4(genjet_4vector,igenjet)->Pt() || fabs(GetP4(genjet_4vector,igenjet)->CosTheta()) > 0.999 || fabs(GetP4(genjet_4vector,igenjet)->CosTheta()) < 1e-3) continue;
          // if (abs(jet_physics_parton_pdgid[igenjet]) != 5) continue;
          if (abs(jet_algo_parton_flavor[igenjet]) != 5) continue;
          double dRBhadbjet = GetP4(genjet_4vector,igenjet)->DeltaR(*GetP4(MC_Bhad_4vector,igenpart)); 
          if (dRBhadbjet < dRBhadbjetmin) {
            dRBhadbjetmin = dRBhadbjet;
            xB = GetP4(MC_Bhad_4vector,igenpart)->Pt()/GetP4(genjet_4vector,igenjet)->Pt();
          }
        }
      }
      // Bfrag reweighting
      /*
      _weight = _weight*myBfragReweighter->getEventWeight(xB);
      */
      _h_dRBhadbjet_gen->Fill(dRBhadbjetmin, _weight);
      _h_pTBhadOverpTbjet_gen->Fill(xB, _weight);
    }

    _h_iCut->Fill((float)iCut,_weight); cutName[iCut] = "Event selection"; ++iCut; 
    _h_iCut->GetXaxis()->SetBinLabel(iCut,"Event selection");

    //======================================================
    // Plots
    //======================================================

    if (isSemiLept) {
      _h_decay->Fill(0.5, _weight);
      _h_decay_part->Fill(0.5, _weight);
    }
    if (isDiLept) {
      if (isDiLept_same) {
        _h_decay->Fill(1.5, _weight);
        _h_decay_part->Fill(1.5, _weight);
      } else {
        _h_decay->Fill(2.5, _weight);
        _h_decay_part->Fill(2.5, _weight);
      }
    }

    if (_isMC)
      _h_weight->Fill(_weight);

    // jets :
    //-------

    for(unsigned int j=0; j < ngoodjet; ++j) {
      _h_jet20_pt->Fill(GetP4(jet_4vector,indgoodjet[j])->Pt(), _weight);
      _h_jet20_eta->Fill(GetP4(jet_4vector,indgoodjet[j])->Eta(), _weight);
      _h_jet20_phi->Fill(GetP4(jet_4vector,indgoodjet[j])->Phi(), _weight);
      _h_jet20_csv->Fill(jet_btag_CSV[indgoodjet[j]], _weight);
      _h_jet20_chmult->Fill(jet_chmult[indgoodjet[j]], _weight);
    }

    _h_jet20_n->Fill((float)ngoodjet, _weight);
    _h_jet30_n->Fill((float)njet30, _weight);
    _h_jet40_n->Fill((float)njet40, _weight);
    _h_jet50_n->Fill((float)njet50, _weight);
    _h_csvJet20_n->Fill((float)nbjet, _weight);

    if (ngoodjet > 0) {
      _h_leadJet1_pt->Fill(GetP4(jet_4vector,indgoodjet[0])->Pt(), _weight);
      _h_leadJet1_eta->Fill(GetP4(jet_4vector,indgoodjet[0])->Eta(), _weight);
      _h_leadJet1_phi->Fill(GetP4(jet_4vector,indgoodjet[0])->Phi(), _weight);
      if (ngoodjet > 1) {
        _h_leadJet2_pt->Fill(GetP4(jet_4vector,indgoodjet[1])->Pt(), _weight);
        _h_leadJet2_eta->Fill(GetP4(jet_4vector,indgoodjet[1])->Eta(), _weight);
        _h_leadJet2_phi->Fill(GetP4(jet_4vector,indgoodjet[1])->Phi(), _weight);
        if (ngoodjet > 2) {
          _h_leadJet3_pt->Fill(GetP4(jet_4vector,indgoodjet[2])->Pt(), _weight);
          _h_leadJet3_eta->Fill(GetP4(jet_4vector,indgoodjet[2])->Eta(), _weight);
          _h_leadJet3_phi->Fill(GetP4(jet_4vector,indgoodjet[2])->Phi(), _weight);
          if (ngoodjet > 3) {
            _h_leadJet4_pt->Fill(GetP4(jet_4vector,indgoodjet[3])->Pt(), _weight);
            _h_leadJet4_eta->Fill(GetP4(jet_4vector,indgoodjet[3])->Eta(), _weight);
            _h_leadJet4_phi->Fill(GetP4(jet_4vector,indgoodjet[3])->Phi(), _weight);
          }
        }
      }
    }

    // iso lepton :
    //--------

    _h_isoLept_pt->Fill(GetP4(muonloose_4vector,indgoodmu[0])->Pt(), _weight);
    _h_isoLept_eta->Fill(GetP4(muonloose_4vector,indgoodmu[0])->Eta(), _weight);
    _h_isoLept_phi->Fill(GetP4(muonloose_4vector,indgoodmu[0])->Phi(), _weight);
    _h_isoLept_pfiso->Fill(muonloose_deltaBetaCorrectedRelIsolation[indgoodmu[0]], _weight);
    _h_isoLept_n->Fill((float)ngoodmuon, _weight);

    // MET :
    //------

    _h_met_met->Fill(MET_Pt, _weight);
    _h_met_phi->Fill(MET_Phi, _weight);

    float Delta_Phi_mu_met = kinem::delta_phi(GetP4(muonloose_4vector,indgoodmu[0])->Phi(), MET_Phi);     
    float wmt = sqrt(2. * MET_Pt * GetP4(muonloose_4vector,indgoodmu[0])->Pt() * (1.-cos(Delta_Phi_mu_met)));
    _h_W_mt->Fill(wmt, _weight);    

    // Vertices :
    //-----------

    for (unsigned int j = 0; j < nvtx; ++j) {
      _h_vertex_x->Fill(vertex_vx[indgoodver[j]], _weight);
      _h_vertex_y->Fill(vertex_vy[indgoodver[j]], _weight);
      _h_vertex_z->Fill(vertex_vz[indgoodver[j]], _weight);
      _h_vertex_ndof->Fill(vertex_ndof[indgoodver[j]], _weight);
      _h_vertex_chi2Norm->Fill(vertex_normChi2[indgoodver[j]], _weight);
      _h_vertex_isFake->Fill((float)vertex_isFake[indgoodver[j]], _weight);
      _h_vertex_nTracks->Fill((float)vertex_ntracks[indgoodver[j]], _weight);

      if (j == 0) {
        _h_leadVertex_x->Fill(vertex_vx[indgoodver[j]], _weight);
        _h_leadVertex_y->Fill(vertex_vy[indgoodver[j]], _weight);
        _h_leadVertex_z->Fill(vertex_vz[indgoodver[j]], _weight);
        _h_leadVertex_ndof->Fill(vertex_ndof[indgoodver[j]], _weight);
        _h_leadVertex_chi2Norm->Fill(vertex_normChi2[indgoodver[j]], _weight);
        _h_leadVertex_isFake->Fill((float)vertex_isFake[indgoodver[j]], _weight);
        _h_leadVertex_nTracks->Fill((float)vertex_ntracks[indgoodver[j]], _weight);
      }
    }
    _h_vertex_n->Fill((float)nvtx, _weight);    

    // Jpsi analysis :
    //----------------

    _h_jpsi_n->Fill((float)njpsi, _weight);     
    _h_jpsi_m->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->M(), _weight);
    _h_jpsi_pt->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_jpsi_eta->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(), _weight);
    _h_jpsi_phi->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(), _weight);

    _h_muJpsi_pt->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_muJpsi_pt_zoom->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_muJpsi_eta->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Eta(), _weight);
    _h_muJpsi_phi->Fill(GetP4(jpsi_mu1_4vector,indgoodjpsi[0])->Phi(), _weight);

    _h_muJpsi_pt->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_muJpsi_pt_zoom->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_muJpsi_eta->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Eta(), _weight);
    _h_muJpsi_phi->Fill(GetP4(jpsi_mu2_4vector,indgoodjpsi[0])->Phi(), _weight);

    _h_jpsi_l->Fill(jpsi_L3D[indgoodjpsi[0]], _weight);
    _h_jpsi_l_zoom->Fill(jpsi_L3D[indgoodjpsi[0]], _weight);
    _h_jpsi_sigmaL->Fill(jpsi_sigmaL3D[indgoodjpsi[0]], _weight);
    _h_jpsi_lOverSigma->Fill(jpsi_L3DoverSigmaL3D[indgoodjpsi[0]], _weight);
    _h_jpsi_chi2->Fill(jpsi_vtxchi2[indgoodjpsi[0]], _weight);
    _h_jpsi_jetPtFrac->Fill(GetP4(jpsi_4vector,indgoodjpsi[0])->Pt()/GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_jpsiraw_jetPtFrac->Fill(GetP4(jpsi_raw_4vector,indgoodjpsi[0])->Pt()/GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Pt(), _weight);

    // min_ijet == jpsi_indjet[indgoodjpsi[0]]
    double min_dRjet = 200.;
    unsigned int min_ijet = 0;
    for (unsigned int ijet = 0; ijet < n_jets; ijet++) {
      double tmp_dRjet = kinem::delta_R(GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Eta(), GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Phi(), GetP4(jet_4vector,ijet)->Eta(), GetP4(jet_4vector,ijet)->Phi());
      if (tmp_dRjet < min_dRjet) {
        min_dRjet = tmp_dRjet;
        min_ijet = ijet;
      }
    }
    _h_jetJpsi_pt->Fill(GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Pt(), _weight);
    _h_jetJpsi_csv->Fill(jpsi_jet_btag_CSV[indgoodjpsi[0]], _weight);
    _h_jetJpsi_chmult->Fill(jet_chmult[min_ijet], _weight);
    _h_jetJpsi_chMuEFrac->Fill(jet_chmuEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    _h_jetJpsi_chEMEFrac->Fill(jet_chemEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    _h_jetJpsi_chHadEFrac->Fill(jet_chhadEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    _h_jetJpsi_chEFrac->Fill((jet_chmuEfrac[min_ijet]+jet_chemEfrac[min_ijet]+jet_chhadEfrac[min_ijet])/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    _h_jetJpsi_nEMEFrac->Fill(jet_nemEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    _h_jetJpsi_nHadEFrac->Fill(jet_nhadEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    _h_jetJpsi_nEFrac->Fill((jet_nemEfrac[min_ijet]+jet_nhadEfrac[min_ijet])/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(), _weight);
    
    // Angular analysis :
    //-------------------

    float dR = 0.;
    float dPhi = 0.;
    dR = kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(),GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(muonloose_4vector,indgoodmu[0])->Eta(),GetP4(muonloose_4vector,indgoodmu[0])->Phi());
    _h_jpsi_dRLept->Fill(dR, _weight);
    dPhi = kinem::delta_phi(GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),GetP4(muonloose_4vector,indgoodmu[0])->Phi());
    _h_jpsi_dPhiLept->Fill(dPhi, _weight);

    // Jpsi - iso mu association :
    //----------------------------

    float px_reco = 0.;
    float py_reco = 0.;
    float pz_reco = 0.;
    float e_reco = 0.;

    px_reco = GetP4(jpsi_4vector,indgoodjpsi[0])->Px() + GetP4(muonloose_4vector,indgoodmu[0])->Px();
    py_reco = GetP4(jpsi_4vector,indgoodjpsi[0])->Py() + GetP4(muonloose_4vector,indgoodmu[0])->Py();
    pz_reco = GetP4(jpsi_4vector,indgoodjpsi[0])->Pz() + GetP4(muonloose_4vector,indgoodmu[0])->Pz();
    e_reco  = GetP4(jpsi_4vector,indgoodjpsi[0])->E()  + GetP4(muonloose_4vector,indgoodmu[0])->E();

    float p_reco  = sqrt(pow(px_reco, 2.) + pow(py_reco, 2.) + pow(pz_reco, 2.));
    float pt_reco = sqrt(pow(px_reco, 2.) + pow(py_reco, 2.));
    float m_reco  = pow(e_reco, 2.) - pow(p_reco, 2.);
    if (m_reco >= 0) m_reco = sqrt(m_reco);
    else             m_reco = 0.;

    _h_triLept_m->Fill(m_reco, _weight);

    if (_isMC && _isSIG) {
      bool goodpaired = false;
      int indJPsi = 0;
      int indLepton = 0;

      bool JPsiMatched = false;
      float dr_jpsi = 100.;
      float dpt_jpsi = 100.;
      for ( int i = 0; i < n_MCs; ++i) {
        if (MC_type[i] == 443){
          float dr_jpsi_tmp = kinem::delta_R(GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(), GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(),
              MC_eta[i], MC_phi[i]);
          float MC_pt = sqrt(MC_px[i] * MC_px[i] + MC_py[i] * MC_py[i]);
          float dpt_jpsi_tmp = fabs(GetP4(jpsi_4vector,indgoodjpsi[0])->Pt() - MC_pt) / fabs(MC_pt);
          if (dpt_jpsi_tmp < dpt_jpsi && dr_jpsi_tmp < dr_jpsi) {
            dr_jpsi = dr_jpsi_tmp;
            dpt_jpsi = dpt_jpsi_tmp;
            indJPsi = i;
          }
        }
      }
      _h_jpsi_resR->Fill(dr_jpsi, _weight);  
      _h_jpsi_resPt->Fill(dpt_jpsi, _weight);  
      if (dr_jpsi < 0.05) JPsiMatched = true;

      bool LeptonMatched = false;
      float dr_l = 100.;
      float dpt_l = 100.;
      for ( int i = 0; i < n_MCs; ++i) {
        if(fabs(MC_type[i]) == 13){
          float dr_l_tmp = kinem::delta_R(GetP4(muonloose_4vector,indgoodmu[0])->Eta(),GetP4(muonloose_4vector,indgoodmu[0])->Phi(),MC_eta[i],MC_phi[i]);
          float MC_pt = sqrt( MC_px[i] * MC_px[i] + MC_py[i] * MC_py[i] );
          float dpt_l_tmp = fabs(GetP4(muonloose_4vector,indgoodmu[0])->Pt()-MC_pt)/fabs(MC_pt);
          if (dpt_l_tmp < dpt_l && dr_l_tmp < dr_l) {
            dr_l = dr_l_tmp;
            dpt_l = dpt_l_tmp;
            indLepton = i;
          }
        }
      }  
      _h_isoLept_resR->Fill(dr_l, _weight);  
      _h_isoLept_resPt->Fill(dpt_l, _weight);  
      if (dr_l < 0.05) LeptonMatched = true;

      if (_debug) {
        cout << "J/psi... " 
          << "from top : " << MC_JPsiFromTop[indJPsi]
          << "... from antitop : " << MC_JPsiFromAntiTop[indJPsi]
          << endl;
        cout << "muon... " 
          << "from top : " << MC_LeptonFromTop[indLepton]
          << "... from antitop : " << MC_LeptonFromAntiTop[indLepton]
          << endl;
      }     
      if (MC_JPsiFromTop[indJPsi] && MC_LeptonFromTop[indLepton]) goodpaired = true;
      if (MC_JPsiFromAntiTop[indJPsi] && MC_LeptonFromAntiTop[indLepton]) goodpaired = true;
      if (_debug) cout << "good paired : " << goodpaired << endl;

      if (JPsiMatched)
        ++counter[8];
      if (JPsiMatched && LeptonMatched) {
        ++counter[9];
        if (goodpaired) {
          pairing_m = 1.; // PairingStudies
          _h_triLept_goodPair_m->Fill(m_reco, _weight);
          ++counter[10];
        } else {
          pairing_m = -1.; // PairingStudies
          _h_triLept_wrongPair_m->Fill(m_reco, _weight);
          ++counter[11];
        }
        // PairingStudies
        weight_m = _weight; 
        jet20_n_m = (float)ngoodjet;
        jpsi_m_m = GetP4(jpsi_4vector,indgoodjpsi[0])->M(); 
        jpsi_pt_m = GetP4(jpsi_4vector,indgoodjpsi[0])->Pt(); 
        jpsi_eta_m = GetP4(jpsi_4vector,indgoodjpsi[0])->Eta(); 
        jpsi_phi_m = GetP4(jpsi_4vector,indgoodjpsi[0])->Phi(); 
        jpsi_chi2_m = jpsi_vtxchi2[indgoodjpsi[0]]; 
        jpsi_l_m = jpsi_L3D[indgoodjpsi[0]]; 
        jpsi_sigmaL_m = jpsi_sigmaL3D[indgoodjpsi[0]]; 
        jpsi_lOverSig_m = jpsi_L3DoverSigmaL3D[indgoodjpsi[0]]; 
        jpsi_jetPtFrac_m = GetP4(jpsi_4vector,indgoodjpsi[0])->Pt()/GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Pt(); 
        jetJpsi_pt_m = GetP4(jpsi_jet_4vector,indgoodjpsi[0])->Pt(); 
        jetJpsi_csv_m = jpsi_jet_btag_CSV[indgoodjpsi[0]]; 
        jetJpsi_chMuEFrac_m = jet_chmuEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        jetJpsi_chEMEFrac_m = jet_chemEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        jetJpsi_chHadEFrac_m = jet_chhadEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        jetJpsi_chEFrac_m = (jet_chmuEfrac[min_ijet]+jet_chemEfrac[min_ijet]+jet_chhadEfrac[min_ijet])/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        jetJpsi_nEMEFrac_m = jet_nemEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        jetJpsi_nHadEFrac_m = jet_nhadEfrac[min_ijet]/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        jetJpsi_nEFrac_m = (jet_nemEfrac[min_ijet]+jet_nhadEfrac[min_ijet])/GetP4(rawjet_4vector,min_ijet)->E()*GetP4(jet_4vector,min_ijet)->E(); 
        isoLept_pt_m = GetP4(muonloose_4vector,indgoodmu[0])->Pt(); 
        isoLept_eta_m = GetP4(muonloose_4vector,indgoodmu[0])->Eta(); 
        isoLept_phi_m = GetP4(muonloose_4vector,indgoodmu[0])->Phi(); 
        jpsi_dPhiLept_m = dPhi; 
        jpsi_dRLept_m = dR; 
        triLept_m_m = m_reco; 
        triLept_pt_m = pt_reco; 
        _t_pairingStudies_m->Fill();
      }  
    }

    _h_triLept_pt->Fill(pt_reco, _weight);
    triLept_mass = m_reco;
    triLept_weight = _weight;
    _t_triLept_m->Fill();

    // Top mass reconstruction :
    //--------------------------

    std::vector<TLorentzVector> jjcomb;
    std::vector<unsigned int> jjcombind1;
    std::vector<unsigned int> jjcombind2;

    for(unsigned int j = 0; j < indgoodjet.size(); ++j) {
      if (jet_btag_CSV[indgoodjet[j]] > 0.814) continue; 
      TLorentzVector j1(GetP4(jet_4vector,indgoodjet[j])->Px(),GetP4(jet_4vector,indgoodjet[j])->Py(),GetP4(jet_4vector,indgoodjet[j])->Pz(),GetP4(jet_4vector,indgoodjet[j])->E());

      for(unsigned int k = j+1; k < indgoodjet.size(); ++k ) {
        if (jet_btag_CSV[indgoodjet[k]] > 0.814) continue; 
        TLorentzVector j2(GetP4(jet_4vector,indgoodjet[k])->Px(),GetP4(jet_4vector,indgoodjet[k])->Py(),GetP4(jet_4vector,indgoodjet[k])->Pz(),GetP4(jet_4vector,indgoodjet[k])->E());

        TLorentzVector jj;
        jj = j1 + j2;

        if (jj.M() > 50. && jj.M() < 110.) {
          jjcomb.push_back(jj);
          jjcombind1.push_back(j);
          jjcombind2.push_back(k);
        }
      }
    }

    if (_debug) cout << " Number of combinations for W->jj = " << jjcomb.size() << endl;

    std::vector<TLorentzVector> bjjcomb;

    float ptmax = 0.;
    int indbjj = -1;
    int indjj  = -1;
    int indb   = -1;

    int counter = 0;

    for (unsigned int i = 0; i < jjcomb.size(); ++i) {
      for(unsigned int j = 0; j < indgoodjet.size(); ++j) {

        if (jet_btag_CSV[indgoodjet[j]] < 0.814) continue; 
        if (j == jjcombind1[i] || j == jjcombind2[i]) continue;

        TLorentzVector j3(GetP4(jet_4vector,indgoodjet[j])->Px(),GetP4(jet_4vector,indgoodjet[j])->Py(),GetP4(jet_4vector,indgoodjet[j])->Pz(),GetP4(jet_4vector,indgoodjet[j])->E());

        TLorentzVector bjj;
        bjj = jjcomb[i] + j3;

        bjjcomb.push_back(bjj);

        if (bjj.Pt() > ptmax) {
          ptmax  = bjj.Pt();
          indbjj = counter;
          indjj  = i;
          indb   = j;
        }

        if (_debug) cout << " combination : " << jjcombind1[i] << " " << jjcombind2[i] << " " << j << " - Pt = " << bjj.Pt() << " Mjj=" << jjcomb[i].M() << " Mbjj = " << bjj.M() << endl;

        ++counter;
      }
    }

    if (indjj >= 0 && indbjj >= 0) {
      if (_debug) cout << " Max Pt combination : " << jjcombind1[indjj] << " " << jjcombind2[indjj] << " " << indb << " - Pt = " << bjjcomb[indbjj].Pt() << " Mjj=" << jjcomb[indjj].M() << " Mbjj = " << bjjcomb[indbjj].M() << endl;
      _h_bjj_m->Fill(bjjcomb[indbjj].M(), _weight);
      _h_W_m->Fill(jjcomb[indjj].M(), _weight);
    }

    //======================================================
    // Candidates:    
    //======================================================

    //if (_debug) {
    //  cout << currentfile << " : " 
      cout << run << ":" 
           << lumi << ":" 
           << evtID << endl;
    //}   

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
  if (!_isMC) {
      _h_PUBefore->Scale((float)nselected/_h_PUBefore->Integral());
      _h_PUAfter->Scale((float)nselected/_h_PUAfter->Integral());
  }

  //================================================================================================
  // Delete dynamical objects
  //================================================================================================

  cout << "========================================================================" << endl;
  cout << "Number of events before cut :                                  = " << _h_iCut->GetBinContent(1) << endl;
  cout << "------------------------------------------------------------------------" << endl;
  cout << "Number of events after cut : " << endl;
  for (int i = 1; i < 9; i++){
    cout << "..." << cutName[i] << " = " << _h_iCut->GetBinContent(i+1) << endl;
  }
  cout << "========================================================================" << endl;
  cout << "Total Number of events selected                           = "  << nselected << endl;
  cout << "========================================================================" << endl;
  cout << "Trigger                                                   = " << counter[0] << endl;
  cout << "At least 1 iso muon                                       = " << counter[1] << endl;
  cout << "At least 4 jets pT>55,45,35,20 GeV                        = " << counter[2] << endl;
  //cout << "At least 2 jets pT>40 GeV                                 = " << counter[2] << endl;
  cout << "semi-leptonic                                             = " << counter[3] << endl;
  cout << "dileptonic                                                = " << counter[4] << endl;
  cout << "1 J/psi in [3, 3.2] GeV                                   = " << counter[5] << endl;
  cout << "... with chi2 < 5                                         = " << counter[6] << endl;
  cout << "... and Delta(c.tau) / c.tau > 20                         = " << counter[7] << endl;
//  cout << "Tighter isolated lepton                                   = " << counter[8] << endl;
  if (_isMC && _isSIG) {
    cout << "========================================================================" << endl;
    cout << "J/psi matched to MC truth (DeltaR<0.05)                         = " << counter[8] << endl;
    cout << "========================================================================" << endl;
    cout << "Events matched to MC truth (DeltaR<0.05 for J/psi and lepton)   = " << counter[9] << endl;
    cout << "... good pairing                                                = " << counter[10] << endl;
    cout << "... wrong pairing                                               = " << counter[11] << endl;
  }
  cout << "========================================================================" << endl;
  cout << "Total Number of events skimmed                            = "  << nwrite	 << endl;
  cout << "========================================================================" << endl;

  _newfile->Write();
  _newfile->Close();

}
