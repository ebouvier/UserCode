#! /usr/bin/env python

import math, os, string, sys

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when MyAna was run")
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the day")
(options, args) = parser.parse_args()

if not options.date or not options.version:
    parser.error("you must specify a date and a version")

dir = options.date
if not os.path.isdir(dir):
    parser.error("you must specify a valid date")
#dir = os.path.join(dir, "v"+options.version)
dir = os.path.join(dir, options.version)
if not os.path.isdir(dir):
    parser.error("you must specify a valid version")
dirMu = os.path.join(dir, "MyAnaMu")
dirEl = os.path.join(dir, "MyAnaEl")
dirAll = os.path.join(dir, "MyAnaAll")
if (not os.path.isdir(dirMu) or not os.path.isdir(dirEl)):
    parser.error("you must have run the analysis for both channels")
if not os.path.isdir(dirAll):
    os.mkdir(dirAll)

# Merging data
if (os.path.isfile(dirEl+"/ElectronHadASingleElectronBCD.root") and os.path.isfile(dirMu+"/MuHadASingleMuBCD.root")):
    cmd = "hadd -f "+dirAll+"/Run2012ABCD.root "+dirEl+"/ElectronHadASingleElectronBCD.root "+dirMu+"/MuHadASingleMuBCD.root"
    os.system(cmd)

# Merging central mass point
if (os.path.isfile(dirEl+"/TTJets_MSDecays_JpsiFilter_172_5.root") and os.path.isfile(dirMu+"/TTJets_MSDecays_JpsiFilter_172_5.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_MSDecays_JpsiFilter_172_5.root "+dirEl+"/TTJets_MSDecays_JpsiFilter_172_5.root "+dirMu+"/TTJets_MSDecays_JpsiFilter_172_5.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/T_t-channel.root") and os.path.isfile(dirMu+"/T_t-channel.root")):
    cmd = "hadd -f "+dirAll+"/T_t-channel.root "+dirEl+"/T_t-channel.root "+dirMu+"/T_t-channel.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/Tbar_t-channel.root") and os.path.isfile(dirMu+"/Tbar_t-channel.root")):
    cmd = "hadd -f "+dirAll+"/Tbar_t-channel.root "+dirEl+"/Tbar_t-channel.root "+dirMu+"/Tbar_t-channel.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/T_tW-channel.root") and os.path.isfile(dirMu+"/T_tW-channel.root")):
    cmd = "hadd -f "+dirAll+"/T_tW-channel.root "+dirEl+"/T_tW-channel.root "+dirMu+"/T_tW-channel.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/Tbar_tW-channel.root") and os.path.isfile(dirMu+"/Tbar_tW-channel.root")):
    cmd = "hadd -f "+dirAll+"/Tbar_tW-channel.root "+dirEl+"/Tbar_tW-channel.root "+dirMu+"/Tbar_tW-channel.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/TTJets_MCatNLO.root") and os.path.isfile(dirMu+"/TTJets_MCatNLO.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_MCatNLO.root "+dirEl+"/TTJets_MCatNLO.root "+dirMu+"/TTJets_MCatNLO.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/TTJets_SemiLeptMGDecays_TuneP11.root") and os.path.isfile(dirMu+"/TTJets_SemiLeptMGDecays_TuneP11.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_SemiLeptMGDecays_TuneP11.root "+dirEl+"/TTJets_SemiLeptMGDecays_TuneP11.root "+dirMu+"/TTJets_SemiLeptMGDecays_TuneP11.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/TTJets_SemiLeptMGDecays_TuneP11mpiHi.root") and os.path.isfile(dirMu+"/TTJets_SemiLeptMGDecays_TuneP11mpiHi.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_SemiLeptMGDecays_TuneP11mpiHi.root "+dirEl+"/TTJets_SemiLeptMGDecays_TuneP11mpiHi.root "+dirMu+"/TTJets_SemiLeptMGDecays_TuneP11mpiHi.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/TTJets_SemiLeptMGDecays_TuneP11noCR.root") and os.path.isfile(dirMu+"/TTJets_SemiLeptMGDecays_TuneP11noCR.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_SemiLeptMGDecays_TuneP11noCR.root "+dirEl+"/TTJets_SemiLeptMGDecays_TuneP11noCR.root "+dirMu+"/TTJets_SemiLeptMGDecays_TuneP11noCR.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/TTJets_SemiLeptMGDecays_TuneP11TeV.root") and os.path.isfile(dirMu+"/TTJets_SemiLeptMGDecays_TuneP11TeV.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_SemiLeptMGDecays_TuneP11TeV.root "+dirEl+"/TTJets_SemiLeptMGDecays_TuneP11TeV.root "+dirMu+"/TTJets_SemiLeptMGDecays_TuneP11TeV.root"
    os.system(cmd)
if (os.path.isfile(dirEl+"/TTJets_Powheg.root") and os.path.isfile(dirMu+"/TTJets_Powheg.root")):
    cmd = "hadd -f "+dirAll+"/TTJets_Powheg.root "+dirEl+"/TTJets_Powheg.root "+dirMu+"/TTJets_Powheg.root"
    os.system(cmd)

# Merging tW
files = [name for name in os.listdir(dirEl) if name.startswith("All_") and name.endswith("_5.root")]
for file in files:
    if os.path.isfile(os.path.join(dirMu,file)):
        cmd = "hadd -f "+os.path.join(dirAll,file)+" "+os.path.join(dirEl,file)+" "+os.path.join(dirMu,file)
        os.system(cmd)


# Merging MC
files = [name for name in os.listdir(dirEl) if "tW-channel_mass" in name and name.endswith("_5.root")]
for file in files:
    if os.path.isfile(os.path.join(dirMu,file)):
        cmd = "hadd -f "+os.path.join(dirAll,file)+" "+os.path.join(dirEl,file)+" "+os.path.join(dirMu,file)
        os.system(cmd)

print(dirAll+" has been created")        

