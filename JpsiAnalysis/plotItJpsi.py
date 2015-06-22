#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when MyAna was run")
parser.add_option("-c", "--channel", dest="channel", type="string", default=False, help="electronic, muonic, or skim")
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the day")
parser.add_option("-t", "--decay", dest="decay", type="string", default=False, help="semi, di, or all leptonic")
(options, args) = parser.parse_args()

if not options.date or not options.channel or not options.version or not options.decay:
    parser.error("you must specify a date, a channel, a version, and a decay type")

dir = options.date
if not os.path.isdir(dir):
    parser.error("you must specify a valid date")
#dir = os.path.join(dir, "v"+options.version)
dir = os.path.join(dir, options.version)
if not os.path.isdir(dir):
    parser.error("you must specify a valid version")
if (not options.channel.lower().count("mu") and not options.channel.lower().count("el") and not options.channel.lower().count("skim")) or (not os.path.isdir(os.path.join(dir, "MyAnaMu")) and not os.path.isdir(os.path.join(dir, "MyAnaEl")) and not os.path.isdir(os.path.join(dir, "MyAnaSkim"))):
    parser.error("you must specify a valid channel")

textChannel = " + Jets channel"

if options.channel.lower().count("mu"):
    outPlot = "PlotItJpsiMu"
    if options.decay.lower().count("semi"):
        textChannel = "#mu"+textChannel
    if options.decay.lower().count("di"):
        textChannel = "#mu#mu\/#mue"+textChannel
    if options.decay.lower().count("all"):
        textChannel = "#mu\/#mu#mu\/#mue"+textChannel
    os.system("sed -e \"s/@root@/MyAnaMu/\" -e \"s/@lumi@/19705/\" -e \"s/@text@/%s/\" configPlotItJpsi.template.yml > configPlotItJpsi.yml" % (textChannel))
if options.channel.lower().count("el"):
    outPlot = "PlotItJpsiEl"
    if options.decay.lower().count("semi"):
        textChannel = "e"+textChannel
    if options.decay.lower().count("di"):
        textChannel = "ee\/e#mu"+textChannel
    if options.decay.lower().count("all"):
        textChannel = "e\/ee\/e#mu"+textChannel
    os.system("sed -e \"s/@root@/MyAnaEl/\" -e \"s/@lumi@/19690/\" -e \"s/@text@/%s/\" configPlotItJpsi.template.yml > configPlotItJpsi.yml" % (textChannel))
if options.channel.lower().count("skim"):
    outPlot = "PlotItJpsiSkim"
    textChannel = "Skim"
    os.system("sed -e \"s/@text@/%s/\" configPlotItJpsiSkim.template.yml > configPlotItJpsi.yml" % (textChannel))

print "/!\\ you should not have sourced cmsenv"

os.chdir(dir)
if not os.path.isdir(outPlot):
    os.mkdir(outPlot)
cmd = "../../../../plotIt/plotIt -o " + outPlot + " ../../configPlotItJpsi.yml"
os.system(cmd)

os.chdir("../../")
os.system("rm -rf configPlotItJpsi.yml")

