#! /usr/bin/env python

import math, os, string, sys

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when MyAna was run")
parser.add_option("-i", "--inf", dest="in1", type="string", default=False, help="version for one extremum")
parser.add_option("-s", "--sup", dest="in2", type="string", default=False, help="version for the other extrmum")
parser.add_option("-o", "--out", dest="out", type="string", default=False, help="kind of systematics")
(options, args) = parser.parse_args()

import ROOT
ROOT.TH1.SetDefaultSumw2(ROOT.kTRUE)

if not options.date or not options.in1 or not options.in2 or not options.out:
    parser.error("you must specify a date, versions for the extrema, and the kind of systematics")

dir = options.date
if not os.path.isdir(dir):
    parser.error("you must specify a valid date")
dirI1 = os.path.join(dir, options.in1)
dirI2 = os.path.join(dir, options.in2)
if not os.path.isdir(dirI1) or not os.path.isdir(dirI2):
    parser.error("you must specify valid versions for the extrema")
dirO = os.path.join(dir, "SysForPlotIt")
if not os.path.isdir(dirO):
    os.mkdir(dirO)
dirO = os.path.join(dirO, options.out)
if not os.path.isdir(dirO):
    os.mkdir(dirO)

if options.out.lower().count('me'):
  files = [['TTJets_MSDecays_JpsiFilter_172_5.root',245.8/5380767.,'TTJets_Powheg.root',245.8/21675970.,'TTJets_ME.root']]
elif options.out.lower().count('cr'):
  files = [['TTJets_SemiLeptMGDecays_TuneP11.root',107.6722/12005805.,'TTJets_SemiLeptMGDecays_TuneP11noCR.root',107.6722/12024653.,'TTJets_SemiLeptMGDecays_CR.root'], 
          ['TTJets_FullLeptMGDecays_TuneP11.root',25.8031/5976484.,'TTJets_FullLeptMGDecays_TuneP11noCR.root',25.8031/5974627.,'TTJets_FullLeptMGDecays_CR.root'], 
          ['TTJets_HadronicMGDecays_TuneP11.root',112.325/11651739.,'TTJets_HadronicMGDecays_TuneP11noCR.root',112.325/11919063.,'TTJets_HadronicMGDecays_CR.root']]
elif options.out.lower().count('ue'):
  files = [['TTJets_SemiLeptMGDecays_TuneP11.root',107.6722/12005805.,'TTJets_SemiLeptMGDecays_TuneP11mpiHi.root',107.6722/7978174.,'TTJets_SemiLeptMGDecays_UE.root'], 
          ['TTJets_FullLeptMGDecays_TuneP11.root',25.8031/5976484.,'TTJets_FullLeptMGDecays_TuneP11mpiHi.root',25.8031/3982409.,'TTJets_FullLeptMGDecays_UE.root'], 
          ['TTJets_HadronicMGDecays_TuneP11.root',112.325/11651739.,'TTJets_HadronicMGDecays_TuneP11mpiHi.root',112.325/7953758.,'TTJets_HadronicMGDecays_UE.root']]

for ch in ['MyAnaEl', 'MyAnaMu']:
    dir1 = os.path.join(dirI1, ch)
    dir2 = os.path.join(dirI2, ch)
    if not os.path.join(dir1) or not os.path.isdir(dir2):
        parser.error(ch + " doesn't exist")
    dir0 = os.path.join(dirO, ch)
    if not os.path.isdir(dir0):
        os.mkdir(dir0)
    for file in files:
        in1F = ROOT.TFile.Open(os.path.join(dir1,file[0]), "read")
        in2F = ROOT.TFile.Open(os.path.join(dir2,file[2]), "read",)
        outF = ROOT.TFile.Open(os.path.join(dir0,file[4]), "recreate")
        in1F.cd()
        dirList = ROOT.gDirectory.GetListOfKeys()
        for key in dirList:
            if key.GetClassName() == 'TH1F':
                in1H = key.ReadObj()
                in2H = in2F.Get(in1H.GetName())
                in1H.Scale(file[1]*5380767./245.8)
                in2H.Scale(file[3]*5380767./245.8)
                outH = ROOT.TH1F(in1H.GetName(),in1H.GetTitle(),in1H.GetNbinsX(),in1H.GetXaxis().GetXmin(),in1H.GetXaxis().GetXmax())
                outH.GetXaxis().SetTitle(in1H.GetXaxis().GetTitle())
                for ibin in range(1, outH.GetNbinsX()+1):
                    outH.SetBinContent(ibin, 0.)
                    if in1H.GetBinContent(ibin) + in2H.GetBinContent(ibin) != 0 and abs(in1H.GetBinContent(ibin) - in2H.GetBinContent(ibin)) < 0.4*(in1H.GetBinContent(ibin) + in2H.GetBinContent(ibin)):
                        outH.SetBinError(ibin, abs(in1H.GetBinContent(ibin) - in2H.GetBinContent(ibin))/(in1H.GetBinContent(ibin) + in2H.GetBinContent(ibin)))
                    else:
                        outH.SetBinError(ibin, 0.)
                    if options.out.lower().count("jpsi"):    
                        outH.SetBinError(ibin, 2.*outH.GetBinError(ibin))
                outF.cd()
                outH.Write()
        outF.Close()
        in2F.Close()
        in1F.Close()
        

