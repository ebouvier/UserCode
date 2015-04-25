#ifndef MYANA_h
#define MYANA_h

#include <TROOT.h>
#include <TChain.h>
#include <TFile.h>
#include <cmath>
#include <iostream>
#include <sstream>
#include <set>
#include "AnglesUtil.h"
#include "RootTupleDefs.h"
#include "TLorentzVector.h"
#include "TH1F.h"
class MyAna : public RootTupleDefs {

public :
  MyAna(TTree *_muonstree,TTree *_electronstree, TTree *_jetstree, TTree *_METtree, TTree *_verticestree, TTree *_eventstree, TTree *_HLTtree, TTree *_muonsloosetree, TTree *_electronsloosetree, TTree *_jpsitree, TTree *_MCtree);
  ~MyAna();
  
  void   Loop();
  
  void SetDebugMode(bool debug)                 { _debug    = debug;}   
  void SetMCmode(bool isMC)                     { _isMC     = isMC;}
  void SetTTbarmode(bool isTTbar)               { _isTTbar  = isTTbar;}
  void SetSIGmode(bool isSIG)                   { _isSIG    = isSIG;}
  void SetRootName(const std::string& rootName) { _rootName = rootName;}
  void SetDoSkim(bool doSkim)                   { _doSkim   = doSkim;}
  void SetNevent(int nevent)                    { _nevt = nevent;}

  TLorentzVector* GetP4(TClonesArray* _TClonesArray, int _i) {
    return (TLorentzVector*) (*_TClonesArray)[_i];
  }

  double Pt(double _Px,double _Py) {
    return std::sqrt(_Px*_Px+_Py*_Py);
  }
  
  double Eta(double _Px,double _Py,double _Pz) {
    if (_Pz <0) return (-1)*std::acosh(std::sqrt(_Px*_Px+_Py*_Py+_Pz*_Pz)/(std::sqrt(_Px*_Px+_Py*_Py)));
    else return std::acosh(std::sqrt(_Px*_Px+_Py*_Py+_Pz*_Pz)/(std::sqrt(_Px*_Px+_Py*_Py)));
  }

  double Phi(double _Px,double _Py) {
    return kinem::phi(_Py,_Px);
  }
  
private:
  
  TFile* _newfile;

  TTree* _newmuonstree;
  TTree* _newelectronstree;
  TTree* _newjetstree;
  TTree* _newMETtree ;
  TTree* _newverticestree;
  TTree* _neweventstree;
  TTree* _newHLTtree;
  TTree* _newelectronsloosetree;
  TTree* _newmuonsloosetree;
  TTree* _newjpsitree;
  TTree* _newMCtree;
  bool _debug;
  bool _isMC;
  bool _isTTbar;
  bool _isSIG;
  std::string _rootName;
  bool _doSkim;
  int _nevt;
};

#endif
