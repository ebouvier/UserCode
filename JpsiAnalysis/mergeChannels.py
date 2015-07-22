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

# Merging MC
files = [name for name in os.listdir(dirEl) if name.startswith("All_") and name.endswith("_5.root")]
for file in files:
    if os.path.isfile(os.path.join(dirMu,file)):
        cmd = "hadd -f "+os.path.join(dirAll,file)+" "+os.path.join(dirEl,file)+" "+os.path.join(dirMu,file)
        os.system(cmd)

print(dirAll+" has been created")        

