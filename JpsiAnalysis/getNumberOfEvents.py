#! /usr/bin/env python

import math, os, string, sys

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when MyAna was run")
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the day")
(options, args) = parser.parse_args()

from ROOT import *

if not options.date or not options.version:
    parser.error("you must specify a date and a version")

dir = options.date
if not os.path.isdir(dir):
    parser.error("you must specify a valid date")
dir = os.path.join(dir, "v"+options.version)
if not os.path.isdir(dir):
    parser.error("you must specify a valid version")
if (not os.path.isdir(os.path.join(dir, "MyAnaMu")) or not os.path.isdir(os.path.join(dir, "MyAnaEl"))):
    parser.error("you must have run the analysis for both channels")

texFile = os.path.join(dir, "NumberOfEvents.tex")
tex = open(texFile, 'w')

## Input ifos

histname = "NPrimaryVtx"

Lumi = {"mu": 19.705, "el": 19.690} 
dirAna = {"mu": os.path.join(dir, "MyAnaMu"), "el": os.path.join(dir, "MyAnaEl")}

dataset_names = [
    ["mu", "Isolated muon (HLT\\_IsoMu24\\_eta2p1)", "MuHadASingleMuBCD.root"],
    ["el", "Isolated electron (HLT\\_Ele27\\_WP80)", "ElectronHadASingleElectronBCD.root"],
    ]

datasets = [
    ["/MuHad/Run2012A-22Jan2013-v1/AOD", "mu", 0.876],
    ["/SingleMu/Run2012B-22Jan2013-v1/AOD", "mu", 4.411],
    ["/SingleMu/Run2012C-22Jan2013-v1/AOD",	"mu", 7.050],
    ["/SingleMu/Run2012D-22Jan2013-v1/AOD", "mu", 7.368],
    ["/ElectronHad/Run2012A-22Jan2013-v1/AOD", "el", 0.876],
    ["/SingleElectron/Run2012B-22Jan2013-v1/AOD", "el", 4.405],
    ["/SingleElectron/Run2012C-22Jan2013-v1/AOD",	"el", 7.040],
    ["/SingleElectron/Run2012D-22Jan2013-v1/AOD",	"el", 7.369], 
    ]
        
aodsim_names = [
    ["tts", "\\ttbar $\\to \\text{b} \\ell \\nu \\text{bqq}$"],
    ["ttd", "\\ttbar $\\to \\text{b} \\ell \\nu \\text{b} \\ell \\nu$"], 
    ["tth", "\\ttbar $\\to \\text{bqq} \\text{bqq}$"],
    ["tto", "\\ttbar other"],
    ["sto", "single top (t, tW, s channels)"],
    ["zll", "$\\text{Z} / \\gamma^* \\to \\ell^+ \\ell^- + \\text{jets}$, $\\text{M}_{\\ell\\ell} > 50 \\; \\text{GeV/c}^2$"],
    ["wln", "$\\text{W}^\\pm \\to \\ell^\\pm \\nu + \\text{jets}$"],
    ["dib", "WW/WZ/ZZ"],
    ]

aodsims = [
    # Standard ttbar
    ["/TTJets\\_FullLeptMGDecays\\_8TeV-madgraph-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7C-v2/AODSIM", "TTJets_FullLeptMGDecays.root", "ttd", 25.8031, 12011428],
    ["/TTJets\\_SemiLeptMGDecays\\_8TeV-madgraph-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V19\\_ext1-v1/AODSIM", "TTJets_SemiLeptMGDecays.root", "tts", 107.6722, 31004465],
    ["/TTJets\\_HadronicMGDecays\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A\\_ext-v1/AODSIM", "tth", "TTJets_HadronicMGDecays.root", 112.325, 31223821],
    # ttbar other
    ["/TTWJets\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "TTWJets.root", "tto", 0.2149, 196046],
    ["/TTWWJets\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "TTWWJets.root", "tto", 0.002037, 217820],
    ["/TTZJets\\_8TeV-madgraph\\_v2/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "TTZJets.root", "tto", 0.172, 210160],
    # single top 
    ## central
    ["/T\\_s-channel\\_TuneZ2star\\_8TeV-powheg-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "T_s-channel.root", "sto", 3.79, 259961],
    ["/T\\_t-channel\\_TuneZ2star\\_8TeV-powheg-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "T_t-channel.root", "sto", 56.4, 3758227],
    ["/T\\_tW-channel-DR\\_TuneZ2star\\_8TeV-powheg-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "T_tW-channel.root", "sto", 11.1, 497658],
    ["/Tbar\\_s-channel\\_TuneZ2star\\_8TeV-powheg-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "Tbar_s-channel.root", "sto", 1.76, 139974],
    ["/Tbar\\_t-channel\\_TuneZ2star\\_8TeV-powheg-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "Tbar_t-channel.root", "sto", 30.7, 1935072],
    ["/Tbar\\_tW-channel-DR\\_TuneZ2star\\_8TeV-powheg-tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "Tbar_tW-channel.root", "sto", 11.1, 493460], 
    # diboson
    ["/WW\\_TuneZ2star\\_8TeV\\_pythia6\\_tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "WW-incl.root", "dib", 54.838, 10000431],
    ["/WZ\\_TuneZ2star\\_8TeV\\_pythia6\\_tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "WZ-incl.root", "dib", 33.21, 10000283],
    ["/ZZ\\_TuneZ2star\\_8TeV\\_pythia6\\_tauola/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "ZZ-incl.root", "dib", 17.654, 9799908],
    # W + jets
    ["/W1JetsToLNu\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "W1JetsToLNu.root", "wln", 5562.36, 23141598],
    ["/W2JetsToLNu\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "W2JetsToLNu.root", "wln", 1802.62, 34044921],
    ["/W3JetsToLNu\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "W3JetsToLNu.root", "wln", 534.604, 15539503],
    ["/W4JetsToLNu\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "W4JetsToLNu.root", "wln", 220.434, 13382803],
    # Z + jets
    ["/DY1JetsToLL\\_M-50\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "DY1JetsToLL_M-50.root", "zll", 561.0, 24045248],
    ["/DY2JetsToLL\\_M-50\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7C-v1/AODSIM", "DY2JetsToLL_M-50.root", "zll", 181.0, 21852156],
    ["/DY3JetsToLL\\_M-50\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "DY3JetsToLL_M-50.root", "zll", 51.1, 11015445],
    ["/DY4JetsToLL\\_M-50\\_TuneZ2Star\\_8TeV-madgraph/Summer12\\_DR53X-PU\\_S10\\_START53\\_V7A-v1/AODSIM", "DY4JetsToLL_M-50.root", "zll", 23.04, 6402827],
    ] 


## Datasets and AODSIM used with lumi and xsections

tex.write("\\begin{table}[h!]\n")
tex.write("\\begin{center}\n")
tex.write("\\caption{\\label{datasim:tab1}\n")
tex.write("Datasets used in this analysis and their corresponding integrated luminosity ($\\text{fb}^{-1}$).\n")
tex.write("}\n")

nchannel = 0
for dataset_name in dataset_names:
    channel = dataset_name[0]
    title = dataset_name[1]
    
    LumiTot = Lumi[channel] 
    
    tex.write("\\begin{tabular}{|p{10cm}|r|}\n")
    tex.write("\\hline\n")
    tex.write("\\multicolumn{2}{|c|}{"+title+"} \\\\ \n")
    tex.write("\\hline\\hline\n")
    tex.write("Dataset & Luminosity ($\\text{fb}^{-1}$) \\\\ \n")
    tex.write("\\hline\\hline\n")
    
    for dataset in datasets:
        
        dataset_path = dataset[0]
        dataset_channel = dataset[1]
        dataset_lumi = dataset[2]

        if dataset_channel is channel:
            tex.write(dataset_path+" & %.3f \\\\ \n" % dataset_lumi)

    tex.write("\\hline\n")
    tex.write("\\multicolumn{2}{|r|}{%.3f} \\\\ \n" % LumiTot)
    tex.write("\\hline\n")
    tex.write("\\end{tabular}\n")
    if nchannel < 1:
        tex.write("\\vspace{0.5cm} \n")
    nchannel += 1
        
tex.write("\\end{center}\n")
tex.write("\\end{table}\n")

tex.write("\n")

tex.write("\\begin{table}[h!]\n")
tex.write("\\begin{center}\n")
tex.write("\\caption{\label{datasim:tab2}\n")
tex.write("Monte Carlo datasets and their corresponding cross section (pb).\n")
tex.write("}\n")
tex.write("\\begin{tabular}{|p{12cm}|c|}\n")
tex.write("\\hline\n")
tex.write("Dataset & Cross section (pb) \\\\ \n")
tex.write("\\hline\\hline\n")

for aodsim in aodsims:
    aodsim_path = aodsim[0]
    aodsim_xsection = aodsim[3]

    tex.write(aodsim_path+" & %.3f \\\\ \n" % aodsim_xsection)
    tex.write("\\hline\n")
        
tex.write("\\end{tabular}\n")
tex.write("\\end{center}\n")
tex.write("\\end{table}\n")

tex.write("\n")

# Number of events from MC and data

tex.write("\\begin{table}[b!] \n")
tex.write("\\begin{center} \n")
tex.write("\\caption{\label{results:tab1} \n")
tex.write("Final number of events from MC simulations and observed in data for the electron and muon channels; \n")
tex.write("quoted uncertainties are statistical only. \n")
tex.write("} \n")
tex.write("\\begin{tabular}{|l||c|c|} \n")
tex.write("\\hline\n")
tex.write(" & \\multicolumn{2}{c|}{Number of events} \\\\ \n")
tex.write("\\hline\n")
tex.write("Process & $\\mu+\\text{jets}$ channel & $\\text{e}+\\text{jets}$ channel \\\\ \n")
tex.write("\\hline\\hline\n")

NSim = {"mu": 0., "el": 0.}
ErrNSim = {"mu": 0., "el": 0.}
    
for aodsim_name in aodsim_names:
    group = aodsim_name[0]
    text = aodsim_name[1]
    NTot = {"mu": 0., "el": 0.}
    ErrNTot = {"mu": 0., "el": 0.}
    
    for key in Lumi.keys():

        for aodsim in aodsims:
            aodsim_root = aodsim[1]
            aodsim_group = aodsim[2]
            aodsim_xsection = aodsim[3]
            aodsim_ngen = aodsim[4]

            if aodsim_group is group:
                factor = 1e3*Lumi[key] * aodsim_xsection / aodsim_ngen
                file = TFile.Open(os.path.join(dirAna[key], aodsim_root))
                histo = file.Get(histname)
                nentries = histo.Integral()

                NTot[key] += nentries * factor
                NSim[key] += nentries * factor
                ErrNTot[key] += factor * factor * nentries * (1. - nentries/aodsim_ngen)
                ErrNSim[key] += factor * factor * nentries * (1. - nentries/aodsim_ngen)
         
        ErrNTot[key] = math.sqrt(ErrNTot[key])

    tex.write(text+" & $%f \\pm %f$ & $%f \\pm %f$ \\\\ \n" % (NTot["mu"], ErrNTot["mu"], NTot["el"], ErrNTot["el"]))
    tex.write("\\hline\n")

ErrNSim["mu"] = math.sqrt(ErrNSim["mu"])
ErrNSim["el"] = math.sqrt(ErrNSim["el"])

tex.write("\\hline\n")
tex.write("Total from simulations & $%f \\pm %f$ & $%f \\pm %f$ \\\\ \n" % (NSim["mu"], ErrNSim["mu"], NSim["el"], ErrNSim["el"]))
tex.write("\\hline\n")

NData = {"mu": 0., "el": 0.}
ErrNData = {"mu": 0., "el": 0.}

for dataset_name in dataset_names:
    channel = dataset_name[0]
    title = dataset_name[1]
    rootFile = dataset_name[2]

    file = TFile.Open(os.path.join(dirAna[channel], rootFile))
    histo = file.Get(histname)
    NData[channel] = histo.Integral()
    ErrNData[channel] = math.sqrt(NData[channel])

tex.write("Data & $%d \\pm %d$ & $%d \\pm %d$ \\\\ \n" % (NData["mu"], ErrNData["mu"], NData["el"], ErrNData["el"]))
tex.write("\\hline\n")
        
tex.write("\\end{tabular}\n")
tex.write("\\end{center}\n")
tex.write("\\end{table}\n")
    
tex.close()

print texFile+" has been created."

