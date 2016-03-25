#ifndef BFRAGWEIGHTSPROVIDER_H
#define BFRAGWEIGHTSPROVIDER_H

#include "TGraphErrors.h"
#include "TFile.h"
#include "TString.h"
#include "TSystem.h"

#include <iostream>
#include <vector>

class BfragWeightsProvider {
  public: 
    BfragWeightsProvider(TString tune = "Z2star") {
      url = "/gridgroup/cms/bouvier/CMSSW_5_3_27/src/UserCode/FragmentationAnalyzer/test/Inclusive_500000evts_AllGood/BfragWeights_xb.root";
      gSystem->ExpandPathName(url);
      TFile *fi = TFile::Open(url);
      if (fi && !fi->IsZombie()) {
        std::cout << "[BfragWeightsProvider] will use " << tune << " weights stored @ " << url << std::endl;
        weight_ = (TGraphErrors*)fi->Get(tune+"_weight");
      }
      fi->Close();
    };
    float getEventWeight(float bptratio) {
      if (bptratio < 0 || bptratio > 2)
        return 1.;
      else
        return weight_->Eval(bptratio);
    };
    ~BfragWeightsProvider() {};

  private:
    TString url;
    TGraphErrors *weight_;
};

#endif
