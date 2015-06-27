#include <string>
#include <iostream>
#include <sstream>

#include "TString.h"
#include "TTree.h"
#include "TFile.h"
#include "TH1F.h"


/*
 * merge signal and backgrounds MC, normalized at xsections
 * t-channel and inclusive ttbar as signal for the central 
 * mass point only
 */

int mergeMCforSys(TString date, TString version, TString channel){

  float lumi;
  // TString dir = date+"/v"+version+"/";
  TString dir = date+"/"+version+"/";
  TString fileData = date+"/Ref/";
  if (channel.Contains("mu", TString::kIgnoreCase)) {
    lumi = 19705.;
    dir += "MyAnaMu/";
    fileData += "MyAnaMu/MuHadASingleMuBCD.root";
  }
  if (channel.Contains("el", TString::kIgnoreCase)) {
    lumi = 19690.;
    dir += "MyAnaEl/";
    fileData += "MyAnaEl/ElectronHadASingleElectronBCD.root";
  }
  TFile *file = TFile::Open(fileData);
  TH1D* h = (TH1D*)file->Get("NJets20");
  double nEvt = h->Integral();
  delete h;
  file->Close(); 
  delete file;

  vector<TString> finames;
  finames.push_back("T_s-channel.root"); 
  finames.push_back("T_tW-channel.root");
  finames.push_back("Tbar_s-channel.root");
  finames.push_back("Tbar_tW-channel.root");
  finames.push_back("TTWJets.root"); 
  finames.push_back("TTWWJets.root");
  finames.push_back("TTZJets.root");
  finames.push_back("WW-incl.root");
  finames.push_back("WZ-incl.root");
  finames.push_back("ZZ-incl.root");
  finames.push_back("DY1JetsToLL_M-50.root"); 
  finames.push_back("DY2JetsToLL_M-50.root");
  finames.push_back("DY3JetsToLL_M-50.root");
  finames.push_back("DY4JetsToLL_M-50.root"); 
  finames.push_back("W1JetsToLNu.root");
  finames.push_back("W2JetsToLNu.root");
  finames.push_back("W3JetsToLNu.root");
  finames.push_back("W4JetsToLNu.root");
  finames.push_back("TTJets_MSDecays_JpsiFilter_172_5.root");
  finames.push_back("T_t-channel.root");
  finames.push_back("Tbar_t-channel.root");
  vector<float> nevts;
  nevts.push_back(259961);
  nevts.push_back(497658);
  nevts.push_back(139974);
  nevts.push_back(493460);
  nevts.push_back(196046);
  nevts.push_back(217820);
  nevts.push_back(210160);
  nevts.push_back(10000431);
  nevts.push_back(10000283);
  nevts.push_back(9799908);
  nevts.push_back(24045248);
  nevts.push_back(21852156);
  nevts.push_back(11015445);
  nevts.push_back(6402827);
  nevts.push_back(23141598);
  nevts.push_back(34044921);
  nevts.push_back(15539503);
  nevts.push_back(13382803);
  nevts.push_back(5380767);
  nevts.push_back(3758227);
  nevts.push_back(1935072);
  vector<float> xsections;
  xsections.push_back(3.79); 
  xsections.push_back(11.1); 
  xsections.push_back(1.76); 
  xsections.push_back(11.1); 
  xsections.push_back(0.2149);
  xsections.push_back(0.0020370);
  xsections.push_back(0.172); 
  xsections.push_back(56.0);
  xsections.push_back(33.6);
  xsections.push_back(7.6); 
  xsections.push_back(66.3);
  xsections.push_back(215.);
  xsections.push_back(60.7);
  xsections.push_back(27.3);
  xsections.push_back(6662.8);
  xsections.push_back(2159.2);
  xsections.push_back(640.4); 
  xsections.push_back(264.0); 
  xsections.push_back(245.8);
  xsections.push_back(56.4);
  xsections.push_back(30.7);

  assert (finames.size() == nevts.size());
  assert (nevts.size() == xsections.size());
  const unsigned int vecsize = finames.size();

  vector<float> prop;
  float norm = 0.;
  for (unsigned int i = 0; i < vecsize; i++){
    TFile *fi = TFile::Open(dir+finames[i]);
    TH1F* hist = (TH1F*) fi->Get("NVertices");
    prop.push_back(lumi*xsections[i]*hist->Integral()/nevts[i]);
    norm += prop[i];
    delete hist; fi->Close(); delete fi;
  }
  float tot = 0.;
  for (unsigned int i = 0; i < vecsize; i++) {
    prop[i] = nEvt*prop[i]/norm;
    //prop[i] = prop[i]/norm;
    tot += prop[i];
  }

  TFile *outfi = TFile::Open(dir+"All_172_5.root","RECREATE");
  TH1F *outhisto = new TH1F("MTriLept-allPair", "MTriLept-allPair", 25, 0., 250.);
  outhisto->SetXTitle("M(J/#psi+l) (GeV/c^{2})");
  outhisto->SetYTitle("Events / 10");
  TTree *outtree = new TTree("MTriLept","MTriLept");
  float mass; float weight;
  outtree->Branch("mass",&mass,"mass/F");
  outtree->Branch("weight",&weight,"weight/F");
  for (unsigned int i = 0; i < vecsize; i++) {
    std::cout << finames[i] << " : " << prop[i] << std::endl;
    TFile *fi = TFile::Open(dir+finames[i]);
    TH1F *histo = (TH1F*) fi->Get("MTriLept-allPair"); 
    outhisto->Add(histo, prop[i]);
    TTree *tree = (TTree*) fi->Get("MTriLept");
    int n_entries = tree->GetEntries();
    float massi; float weighti;
    tree->SetBranchAddress("mass", &massi);
    tree->SetBranchAddress("weight", &weighti);
    for (int j = 0; j < n_entries; j++) {
      tree->GetEntry(j);
      mass = massi;
      weight = weighti*prop[i];
      outtree->Fill();
    }
    delete histo; delete tree; fi->Close(); delete fi;
  }
  std::cout << "total = " << tot << std::endl;
  outfi->Write();
  delete outhisto;
  delete outtree;
  outfi->Close();
  delete outfi;
  return 0;
}
