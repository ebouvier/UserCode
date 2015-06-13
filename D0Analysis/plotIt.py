#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when MyAna was run")
parser.add_option("-c", "--channel", dest="channel", type="string", default=False, help="electronic, muonic, all, or skim")
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the day")
(options, args) = parser.parse_args()

if not options.date or not options.channel or not options.version:
    parser.error("you must specify a date, a channel, and a version")

dir = options.date
if not os.path.isdir(dir):
    parser.error("you must specify a valid date")
dir = os.path.join(dir, "v"+options.version)
if not os.path.isdir(dir):
    parser.error("you must specify a valid version")
if (not options.channel.lower().count("mu") and not options.channel.lower().count("el") and not options.channel.lower().count("all") and not options.channel.lower().count("skim")) or (not os.path.isdir(os.path.join(dir, "MyAnaMu")) and not os.path.isdir(os.path.join(dir, "MyAnaEl")) and not os.path.isdir(os.path.join(dir, "MyAnaAll")) and not os.path.isdir(os.path.join(dir, "MyAnaSkim"))):
    parser.error("you must specify a valid channel")

textChannel = " + Jets channel"

if options.channel.lower().count("mu"):
    outPlot = "PlotItMu"
    textChannel = "#mu"+textChannel
    os.system("sed -e \"s/@root@/MyAnaMu/\" -e \"s/@lumi@/19705/\" -e \"s/@text@/%s/\" -e \"s/@dataFile@/MuHadASingleMuBCD.root/\" configPlotIt.template.yml > configPlotIt.yml" % (textChannel))
if options.channel.lower().count("el"):
    outPlot = "PlotItEl"
    textChannel = "e"+textChannel
    os.system("sed -e \"s/@root@/MyAnaEl/\" -e \"s/@lumi@/19690/\" -e \"s/@text@/%s/\" -e \"s/@dataFile@/ElectronHadASingleElectronBCD.root/\" configPlotIt.template.yml > configPlotIt.yml" % (textChannel))
if options.channel.lower().count("all"):
    outPlot = "PlotItAll"
    textChannel = "e\/#mu"+textChannel
    os.system("sed -e \"s/@text@/%s/\" configPlotItAll.template.yml > configPlotIt.yml" % (textChannel))
if options.channel.lower().count("skim"):
    outPlot = "PlotItSkim"
    textChannel = "Skim"
    os.system("sed -e \"s/@text@/%s/\" configPlotItSkim.template.yml > configPlotIt.yml" % (textChannel))

print "/!\\ you should not have sourced cmsenv"

os.chdir(dir)
if not os.path.isdir(outPlot):
    os.mkdir(outPlot)
cmd = "../../../../plotIt/plotIt -o " + outPlot + " ../../configPlotIt.yml"
os.system(cmd)

os.chdir("../../")
os.system("rm -rf configPlotIt.yml")
