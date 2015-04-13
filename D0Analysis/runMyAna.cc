#include "MyAna.h"

#include "TROOT.h"
#include "TStyle.h"
#include "TCanvas.h"
#include "TChain.h"
#include "TFile.h"
#include "TString.h"

#include "StdArg.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <sstream>
#include <string>

using namespace std;

void Usage(const char* exename) {
  cout << "Usage : runMyAna -debug -filelist <data.list> -out <output.root> -num <Nevent> -skim" << endl;
}

int main(int argc, char *argv[])
{

// parse executable options :
//___________________________

  StdArg arg(argc,argv);
 
  cout << "======================================================================" << endl;
  for (int i=0;i<argc;i++)
    cout << argv[i] << " ";
  cout << endl;
  cout << "======================================================================" << endl;
   
  // enter all possible flags:
  arg.flags << "-debug" << "-skim" << "-mc"<<"-sig"<<"-ttbar";
 
  // enter all possible keys:
  arg.keys << "-filelist" << "-out" << "-num" << "-mode";
 
  bool debug   = false;
  bool skim    = false;
  bool ismc    = false;
  bool isttbar = false;
  bool issig   = false;
  string input  = "data.list";
  string output = "output_dummy.root";
  int nevent = -1;
  string mode   = "loop";

  try {  // parse command line
    arg.Process();
    debug = arg.Flag("-debug") ? true: false;
    skim  = arg.Flag("-skim")  ? true: false;
    ismc  = arg.Flag("-mc")    ? true: false;
    isttbar  = arg.Flag("-ttbar")    ? true: false;
    issig  = arg.Flag("-sig")  ? true: false;
    if ( arg.Key("-filelist")    ) input  = arg.Get<string>("-filelist");
    if ( arg.Key("-out")         ) output = arg.Get<string>("-out");    
    if ( arg.Key("-num")         ) nevent = arg.Get<int>("-num");
    if ( arg.Key("-mode")        ) mode   = arg.Get<string>("-mode");
 }
  catch (StdArg::BadInput) {
    if (argc > 1) cout<< "Input error" <<endl;
    // usage in case of error or no parameters
    Usage(argv[0]);
    return 1;
  }

//
// Load ntuples or TCHAIN :
//_________________________
 
  TChain *muons = new TChain("muon_PF");
  TChain *electrons = new TChain("electron_PF");
  TChain *vertices = new TChain("Vertices");
  TChain *jets = new TChain("jet_PF");
  TChain *MET = new TChain("MET_PF");
  TChain *events = new TChain("event");
  TChain *HLT = new TChain("HLT");
  TChain *muonsloose = new TChain("muon_loose_PF");
  TChain *electronsloose = new TChain("electron_loose_PF");
  TChain *MC = new TChain("MC");
  TChain* mujets = new TChain("muTaggedJet_PF");
  TString fNameList = input.c_str();
  cout << "=> Load Chain from file: " << fNameList << endl;
  ifstream fList(fNameList.Data());
  if (!fList) {
    cout << "=> Can't open file " << fNameList << endl;
    return 1;
  }
  std::string lineFromFile;
  do {
    std::getline(fList, lineFromFile);
    if (lineFromFile=="") break;
    if(muons->Add(lineFromFile.c_str())) cout << "=>File '"
                                          << lineFromFile
                                          << "' has been loaded" << endl;
    else cout << ">>Can't load file '" << lineFromFile << "'" << endl;
    electrons->Add(lineFromFile.c_str());// read each 5 trees
    vertices->Add(lineFromFile.c_str());
    jets->Add(lineFromFile.c_str());
    MET->Add(lineFromFile.c_str());
    events->Add(lineFromFile.c_str());
    HLT->Add(lineFromFile.c_str());
    muonsloose->Add(lineFromFile.c_str());
    electronsloose->Add(lineFromFile.c_str());
    // datas files does not contain MC branch
    if ( ismc ){
      MC->Add(lineFromFile.c_str());
    }
    else MC=NULL;
    mujets->Add(lineFromFile.c_str());
  } while (fList.good());
  
  
    
  fList.close();

  cout << "======================================================================" << endl;
  cout << "Total Number of events = "  << muons->GetEntries() << endl;//all 7 trees have the same number of entries
  cout << "======================================================================" << endl;
  MyAna ana(muons, electrons, jets, MET, vertices, events, HLT, muonsloose, electronsloose, mujets, MC); //instantiate one MyAna object
  ana.SetNevent(nevent);// configure the object of type MyAna
  ana.SetRootName(output);
  ana.SetDebugMode(debug);
  ana.SetDoSkim(skim);
  ana.SetMCmode(ismc);
  ana.SetTTbarmode(isttbar);
  ana.SetSIGmode(issig);
  cout << "======================================================================" << endl;
  
  //  if ( mode == "loop2" ) {
  cout<<muonsloose<<endl;
  cout << "Calling MyAna::Loop()..." << endl;
  ana.Loop(); //Call the Loop method on the object ana

    //  } else {
    //    cout << "Calling MyAna::Loop()..." << endl;
    //    ana.Loop();
    //  }

  return 0;
}
