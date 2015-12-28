#ifndef JPSIWEIGHTSPROVIDER_H
#define JPSIWEIGHTSPROVIDER_H

#include "TH1F.h"
#include "TGraph.h"
#include "TFile.h"
#include "TString.h"
#include "TSystem.h"

#include <iostream>
#include <vector>

class JpsiWeightsProvider {
  public: 
    JpsiWeightsProvider(TString date, TString channel) {
      url = "/gridgroup/cms/bouvier/CMSSW_5_3_27/src/UserCode/JpsiAnalysis/"+date+"/Ref/"+channel;
      TString urlMC = url+"/TTJets_SemiLeptMGDecays.root";
      gSystem->ExpandPathName(urlMC);
      TFile *fiMC = TFile::Open(urlMC);
      TString urlData = url;
      if (channel.Contains("MyAnaEl"))
        urlData = urlData + "/ElectronHadASingleElectronBCD.root";
      if (channel.Contains("MyAnaMu"))
        urlData = urlData + "/MuHadASingleMuBCD.root";
      gSystem->ExpandPathName(urlData);
      TFile *fiData = TFile::Open(urlData);
      if (fiData && !fiData->IsZombie() && fiMC && !fiMC->IsZombie()) {
        std::cout << "[JpsiWeightsProvider] will use files stored @ " << url << std::endl;
        TH1F* hData = (TH1F*)fiData->Get("MJpsi-large")->Clone("Data");
        hData->Sumw2();
        hData->SetDirectory(0);
        TH1F* hMC = (TH1F*)fiMC->Get("MJpsi-large")->Clone("MC");
        hMC->Sumw2();
        hMC->Scale(hData->GetMaximum()/hMC->GetMaximum());
        hMC->SetDirectory(0);
        const int npoints = hData->GetNbinsX();
        double x[npoints], y[npoints];
        for (int ipoint = 0; ipoint < npoints; ipoint++) {
          x[ipoint] = hData->GetBinCenter(ipoint+1);
          if (fabs(hData->GetBinContent(ipoint+1)/hMC->GetBinContent(ipoint+1)) < 10) {
            y[ipoint] = hData->GetBinContent(ipoint+1)/hMC->GetBinContent(ipoint+1);
          }  else {
            y[ipoint] = 0.;
          }
        }
        weight_ = new TGraph(npoints, x, y);
        weight_->SetName("Weights");
      }
      fiMC->Close();
      fiData->Close();
    };
    float getEventWeight(float mjpsi) {
      return weight_->Eval(mjpsi);
    };
    ~JpsiWeightsProvider() {};

  private:
    TString url;
    TGraph *weight_;
};

#endif
