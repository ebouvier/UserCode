// -*- C++ -*-
//
// Package:    SumForXsection
// Class:      SumForXsection
// 
/**\class SumForXsection SumForXsection.cc UserCode/SumForXsection/src/SumForXsection.cc

Description: 
Compute the sum of the weights for MC samples

Implementation:
Store the weight sum and the distribution
*/
//
// Original Author:  Elvire Bouvier
//         Created:  Sun Jun 21 21:58:42 CEST 2015
// $Id$
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/EDAnalyzer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"

#include "FWCore/MessageLogger/interface/MessageLogger.h"//
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "SimDataFormats/GeneratorProducts/interface/GenEventInfoProduct.h"
//
// class declaration
//

class SumForXsection : public edm::EDAnalyzer {
  public:
    explicit SumForXsection(const edm::ParameterSet&);
    ~SumForXsection();

    static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


  private:
    virtual void beginJob() ;
    virtual void analyze(const edm::Event&, const edm::EventSetup&);
    virtual void endJob() ;

    virtual void beginRun(edm::Run const&, edm::EventSetup const&);
    virtual void endRun(edm::Run const&, edm::EventSetup const&);
    virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);
    virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&);

    // ----------member data ---------------------------
    double _evtWeight = 0.;
    TH1D* _hWeight;
    TH1D* _hSum;
    double _totWeight = 0.;
};

//
// constants, enums and typedefs
//

//
// static data member definitions
//

//
// constructors and destructor
//
SumForXsection::SumForXsection(const edm::ParameterSet& iConfig)

{
  //now do what ever initialization is needed
  edm::Service<TFileService> fs;
  _hWeight = fs->make<TH1D>("Weight", "Weight", 505, 0., 1.);
  _hSum = fs->make<TH1D>("Sum", "Sum", 1, 0., 1.);
  _totWeight = 0.;

}


SumForXsection::~SumForXsection()
{

  // do anything here that needs to be done at desctruction time
  // (e.g. close files, deallocate resources etc.)
  std::cout << "===================== SumForXsection::~SumForXsection ======================" << std::endl;
  std::cout << " Sum of weights = " << _totWeight << std::endl; 
  std::cout << "===================== SumForXsection::~SumForXsection ======================" << std::endl;


}


//
// member functions
//

// ------------ method called for each event  ------------
  void
SumForXsection::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{
  using namespace edm;
  edm::Handle<GenEventInfoProduct> generatorInfo;
  iEvent.getByLabel("generator", generatorInfo);
  _evtWeight = generatorInfo->weight();

  _hWeight->Fill(_evtWeight);
  _hSum->Fill(0.5, _evtWeight);
  _totWeight += _evtWeight;

}


// ------------ method called once each job just before starting event loop  ------------
  void 
SumForXsection::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
  void 
SumForXsection::endJob() 
{
}

// ------------ method called when starting to processes a run  ------------
  void 
SumForXsection::beginRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a run  ------------
  void 
SumForXsection::endRun(edm::Run const&, edm::EventSetup const&)
{
}

// ------------ method called when starting to processes a luminosity block  ------------
  void 
SumForXsection::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method called when ending the processing of a luminosity block  ------------
  void 
SumForXsection::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
SumForXsection::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(SumForXsection);
