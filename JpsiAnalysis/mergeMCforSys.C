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

  TH1::SetDefaultSumw2(kTRUE);

  float lumi;
  // TString dir = date+"/v"+version+"/";
  TString dir = date+"/"+version+"/";
  TString dirRef = date+"/Ref/";
  if (channel.Contains("mu", TString::kIgnoreCase)) {
    lumi = 19705.;
    dir += "MyAnaMu/";
    dirRef += "MyAnaMu/";
  }
  if (channel.Contains("el", TString::kIgnoreCase)) {
    lumi = 19690.;
    dir += "MyAnaEl/";
    dirRef += "MyAnaEl/";
  }

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
  /*
  if (version.Contains("Powheg", TString::kIgnoreCase))
    finames.push_back("TTJets_Powheg.root");
  else if (version.Contains("MCatNLO", TString::kIgnoreCase)) {
    finames.push_back("TTJets_MCatNLO.root");
  }
  */
  if (version.Contains("Powheg", TString::kIgnoreCase)) {
    finames.push_back("TTJets_Powheg_JpsiFilter.root");
  } else {
    if (version.Contains("P12FL", TString::kIgnoreCase)) {
      finames.push_back("TTJets_MSDecays_JpsiFilter_TuneP12FL.root");
    } else {
      if (version.Contains("P12FT", TString::kIgnoreCase)) {
        finames.push_back("TTJets_MSDecays_JpsiFilter_TuneP12FT.root");
      } else {
        if (version.Contains("P12loCR", TString::kIgnoreCase)) {
          finames.push_back("TTJets_MSDecays_JpsiFilter_TuneP12loCR.root");
        } else {
          if (version.Contains("P12ueHi", TString::kIgnoreCase)) {
            finames.push_back("TTJets_MSDecays_JpsiFilter_TuneP12ueHi.root");
          } else {
            if (version.Contains("P12ueLo", TString::kIgnoreCase)) {
              finames.push_back("TTJets_MSDecays_JpsiFilter_TuneP12ueLo.root");
            } else {
              if (version.Contains("P12", TString::kIgnoreCase)) {
                finames.push_back("TTJets_MSDecays_JpsiFilter_TuneP12.root");
              } else {
                finames.push_back("TTJets_MSDecays_JpsiFilter_172_5.root");
              }
            }
          }
        }
      }
    }
  }
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
  if (version.Contains("MatchingDown", TString::kIgnoreCase)) {
    nevts.push_back(2995645);
  } else {
    if (version.Contains("MatchingUp", TString::kIgnoreCase)) {
      nevts.push_back(3653209);
    } else {
      if (version.Contains("ScaleDown", TString::kIgnoreCase)) {
        nevts.push_back(2265684);
      } else {
        if (version.Contains("ScaleUp", TString::kIgnoreCase)) {
          nevts.push_back(7170992);
        } else {
          if (version.Contains("Powheg", TString::kIgnoreCase)) {
            nevts.push_back(8855350);
          } else {
            if (version.Contains("P12FL", TString::kIgnoreCase)) {
              nevts.push_back(10026551);
            } else {
              if (version.Contains("P12FT", TString::kIgnoreCase)) {
                nevts.push_back(9832345);
              } else {
                if (version.Contains("P12loCR", TString::kIgnoreCase)) {
                  nevts.push_back(8379955);
                } else {
                  if (version.Contains("P12ueHi", TString::kIgnoreCase)) {
                    nevts.push_back(10443386);
                  } else {
                    if (version.Contains("P12ueLo", TString::kIgnoreCase)) {
                      nevts.push_back(9172481);
                    } else {
                      if (version.Contains("P12", TString::kIgnoreCase)) {
                        nevts.push_back(10061801);
                        /*
                           else if (version.Contains("Powheg", TString::kIgnoreCase))
                           nevts.push_back(21675970);
                           else if (version.Contains("MCatNLO", TString::kIgnoreCase)) {
                           nevts.push_back(32852589);
                           }
                           */
                      } else {
                        nevts.push_back(5380767);
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
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
  if (version.Contains("BgDown", TString::kIgnoreCase)) { 
    xsections.push_back(0.95*56.0);
    xsections.push_back(0.95*33.6);
    xsections.push_back(0.95*7.6); 
    xsections.push_back(0.8*66.3);
    xsections.push_back(0.8*215.);
    xsections.push_back(0.8*60.7);
    xsections.push_back(0.8*27.3);
    xsections.push_back(0.8*6662.8);
    xsections.push_back(0.8*2159.2);
    xsections.push_back(0.8*640.4); 
    xsections.push_back(0.8*264.0); 
  }
  else if (version.Contains("BgUp", TString::kIgnoreCase)) { 
    xsections.push_back(1.05*56.0);
    xsections.push_back(1.05*33.6);
    xsections.push_back(1.05*7.6); 
    xsections.push_back(1.2*66.3);
    xsections.push_back(1.2*215.);
    xsections.push_back(1.2*60.7);
    xsections.push_back(1.2*27.3);
    xsections.push_back(1.2*6662.8);
    xsections.push_back(1.2*2159.2);
    xsections.push_back(1.2*640.4); 
    xsections.push_back(1.2*264.0); 
  }
  else {
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
  }
  xsections.push_back(245.8);
  xsections.push_back(56.4);
  xsections.push_back(30.7);

  assert (finames.size() == nevts.size());
  assert (nevts.size() == xsections.size());
  const unsigned int vecsize = finames.size();

  vector<float> prop;
  float norm = 0.;
  for (unsigned int i = 0; i < vecsize; i++){
    TString name = dir+finames[i];
    if ((version.Contains("nnpdf30", TString::kIgnoreCase) || 
         version.Contains("mmht2014", TString::kIgnoreCase) || 
         version.Contains("ct14", TString::kIgnoreCase)) 
       && !finames[i].Contains("TTJets_MSDecays_JpsiFilter_172_5.root", TString::kIgnoreCase))
      name = dirRef+finames[i];
    TFile *fi = TFile::Open(name);
    TH1F* hist = (TH1F*) fi->Get("NVertices");
    prop.push_back(lumi*hist->Integral()*xsections[i]/nevts[i]);
    norm += prop[i];
    delete hist; fi->Close(); delete fi;
  }
  for (unsigned int i = 0; i < vecsize; i++) {
    prop[i] = prop[i]/norm;
  }

  TFile *outfi = TFile::Open(dir+"All_172_5.root","RECREATE");
  TH1F *outhisto = new TH1F("MTriLept-allPair", "MTriLept-allPair", 25, 0., 250.);
  outhisto->SetXTitle("M(J/#psi+l) (GeV)");
  outhisto->SetYTitle("Events / 10");
  TTree *outtree = new TTree("MTriLept","MTriLept");
  float mass; float weight;
  outtree->Branch("mass",&mass,"mass/F");
  outtree->Branch("weight",&weight,"weight/F");
  for (unsigned int i = 0; i < vecsize; i++) {
    std::cout << finames[i] << " : " << prop[i] << std::endl;
    TString name = dir+finames[i];
    if ((version.Contains("nnpdf30", TString::kIgnoreCase) || 
         version.Contains("mmht2014", TString::kIgnoreCase) || 
         version.Contains("ct14", TString::kIgnoreCase)) 
       && !finames[i].Contains("TTJets_MSDecays_JpsiFilter_172_5.root", TString::kIgnoreCase))
      name = dirRef+finames[i];
    TFile *fi = TFile::Open(name);
    TTree *tree = (TTree*) fi->Get("MTriLept");
    int n_entries = tree->GetEntries();
    float massi; float weighti;
    tree->SetBranchAddress("mass", &massi);
    tree->SetBranchAddress("weight", &weighti);
    for (int j = 0; j < n_entries; j++) {
      tree->GetEntry(j);
      mass = massi;
      weight = weighti*prop[i];
      if (finames[i].Contains("TTJets_MSDecays_JpsiFilter_"))
        weight = weight*505.;
      outtree->Fill();
      outhisto->Fill(mass, weight);
    }
    delete tree; fi->Close(); delete fi;
  }
  std::cout << "total = " << norm << std::endl;
  outfi->Write();
  delete outhisto;
  delete outtree;
  outfi->Close();
  delete outfi;
  return 0;
}
