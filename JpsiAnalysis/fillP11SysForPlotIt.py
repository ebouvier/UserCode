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
  files = [['TTJets_MSDecays_JpsiFilter_172_5.root','TTJets_Powheg.root','TTJets_ME.root',245.8]]
elif options.out.lower().count('cr'):
  files = [['TTJets_SemiLeptMGDecays_TuneP11.root','TTJets_SemiLeptMGDecays_TuneP11noCR.root','TTJets_SemiLeptMGDecays_CR.root',107.6722], 
          ['TTJets_FullLeptMGDecays_TuneP11.root','TTJets_FullLeptMGDecays_TuneP11noCR.root','TTJets_FullLeptMGDecays_CR.root',25.8031], 
          ['TTJets_HadronicMGDecays_TuneP11.root','TTJets_HadronicMGDecays_TuneP11noCR.root','TTJets_HadronicMGDecays_CR.root',112.325]]
elif options.out.lower().count('ue'):
  files = [['TTJets_SemiLeptMGDecays_TuneP11.root','TTJets_SemiLeptMGDecays_TuneP11mpiHi.root','TTJets_SemiLeptMGDecays_UE.root',107.6722], 
          ['TTJets_FullLeptMGDecays_TuneP11.root','TTJets_FullLeptMGDecays_TuneP11mpiHi.root','TTJets_FullLeptMGDecays_UE.root',25.8031], 
          ['TTJets_HadronicMGDecays_TuneP11.root','TTJets_HadronicMGDecays_TuneP11mpiHi.root','TTJets_HadronicMGDecays_UE.root',112.325]]

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
        in2F = ROOT.TFile.Open(os.path.join(dir2,file[1]), "read",)
        outF = ROOT.TFile.Open(os.path.join(dir0,file[2]), "recreate")
        in1F.cd()
        dirList = ROOT.gDirectory.GetListOfKeys()
        for key in dirList:
            if key.GetClassName() == 'TH1F':
                in1H = key.ReadObj()
                in2H = in2F.Get(in1H.GetName())
                if abs(in1H.Integral()) > 1e-6 :
                    in1H.Scale(1./in1H.Integral())
                if abs(in2H.Integral()) > 1e-6 :
                    in2H.Scale(1./in2H.Integral())
                outH = ROOT.TH1F(in1H.GetName(),in1H.GetTitle(),in1H.GetNbinsX(),in1H.GetXaxis().GetXmin(),in1H.GetXaxis().GetXmax())
                outH.GetXaxis().SetTitle(in1H.GetXaxis().GetTitle())
                for ibin in range(1, outH.GetNbinsX()+1):
                    outH.SetBinContent(ibin, 0.)
                    if in1H.GetBinContent(ibin) + in2H.GetBinContent(ibin) != 0 and in1H.GetBinError(ibin) < 0.4*in1H.GetBinContent(ibin) and in2H.GetBinError(ibin) < 0.4*in2H.GetBinContent(ibin):
                        error = abs(in1H.GetBinContent(ibin) - in2H.GetBinContent(ibin))/(in1H.GetBinContent(ibin) + in2H.GetBinContent(ibin))
                        outH.SetBinError(ibin, error*file[3]/245.8)
                    else:
                        outH.SetBinError(ibin, 0.)
                outF.cd()
                outH.Write()
        outF.Close()
        in2F.Close()
        in1F.Close()
        

