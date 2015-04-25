#include "./HiggsTriggerEfficiencyProvider.h"
#include <math.h>

float HiggsTriggerEfficiencyProvider::
get_weight_isomu(float lept_pt, float lept_eta) const {
  float weight=1.;
  int triglin = -1;
  if (lept_pt >= 26 && lept_pt < 27) triglin = 0;
  if (lept_pt >= 27 && lept_pt < 28) triglin = 1;
  if (lept_pt >= 28 && lept_pt < 29) triglin = 2;
  if (lept_pt >= 29 && lept_pt < 30) triglin = 3;
  if (lept_pt >= 30 && lept_pt < 31) triglin = 4;
  if (lept_pt >= 31 && lept_pt < 32) triglin = 5;
  if (lept_pt >= 32 && lept_pt < 33) triglin = 6;
  if (lept_pt >= 33 && lept_pt < 35) triglin = 7;
  if (lept_pt >= 35 && lept_pt < 37) triglin = 8;
  if (lept_pt >= 37 && lept_pt < 39) triglin = 9;
  if (lept_pt >= 39 && lept_pt < 41) triglin = 10;
  if (lept_pt >= 41 && lept_pt < 43) triglin = 11;
  if (lept_pt >= 43 && lept_pt < 45) triglin = 12;
  if (lept_pt >= 45 && lept_pt < 47) triglin = 13;
  if (lept_pt >= 47 && lept_pt < 50) triglin = 14;
  if (lept_pt >= 50 && lept_pt < 55) triglin = 15;
  if (lept_pt >= 55 && lept_pt < 60) triglin = 16;
  if (lept_pt >= 60 && lept_pt < 65) triglin = 17;
  if (lept_pt >= 65 && lept_pt < 70) triglin = 18;
  if (lept_pt >= 70 && lept_pt < 90) triglin = 19;
  if (lept_pt >= 90 ) triglin = 20;
  int trigcol = -1;
  if (fabs(lept_eta) < 0.8) trigcol = 0;
  if (fabs(lept_eta) >= 0.8 && fabs(lept_eta) < 1.2) trigcol = 1;
  if (fabs(lept_eta) >= 1.2 && fabs(lept_eta) < 2.1) trigcol = 2;

  if (triglin!=-1 && trigcol!=-1) 
    weight = TRIGWEIGHTMU[triglin][trigcol];  

  return weight;
};

float HiggsTriggerEfficiencyProvider::
get_weight_isoel(float lept_pt, float lept_eta) const {
  float weight=1.;
  int triglin = -1;
  if (lept_pt >= 30 && lept_pt < 31) triglin = 0;
  if (lept_pt >= 31 && lept_pt < 32) triglin = 1;
  if (lept_pt >= 33 && lept_pt < 35) triglin = 3;
  if (lept_pt >= 32 && lept_pt < 33) triglin = 2;
  if (lept_pt >= 33 && lept_pt < 35) triglin = 3;
  if (lept_pt >= 35 && lept_pt < 37) triglin = 4;
  if (lept_pt >= 37 && lept_pt < 39) triglin = 5;
  if (lept_pt >= 39 && lept_pt < 41) triglin = 6;
  if (lept_pt >= 41 && lept_pt < 43) triglin = 7;
  if (lept_pt >= 43 && lept_pt < 45) triglin = 8;
  if (lept_pt >= 45 && lept_pt < 47) triglin = 9;
  if (lept_pt >= 47 && lept_pt < 50) triglin = 10;
  if (lept_pt >= 50 && lept_pt < 55) triglin = 11;
  if (lept_pt >= 55 && lept_pt < 60) triglin = 12;
  if (lept_pt >= 60 && lept_pt < 65) triglin = 13;
  if (lept_pt >= 65 && lept_pt < 70) triglin = 14;
  if (lept_pt >= 70 && lept_pt < 80) triglin = 15;
  if (lept_pt >= 80 && lept_pt < 90) triglin = 16;
  if (lept_pt >= 90) triglin = 17;
  int trigcol = -1;
  if (fabs(lept_eta) < 1.5) trigcol = 0;
  if (fabs(lept_eta) >= 1.5 && fabs(lept_eta) < 2.5) trigcol = 1;

  if (triglin != -1 && trigcol != -1) 
    weight = TRIGWEIGHTEL[triglin][trigcol];  

  return weight;
};
