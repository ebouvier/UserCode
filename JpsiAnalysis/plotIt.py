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

os.chdir(dir)

if options.channel.lower().count("mu"):
    outPlot = "PlotItMu"
    ymlFile = "../../configPlotItMu.yml"
if options.channel.lower().count("el"):
    outPlot = "PlotItEl"
    ymlFile = "../../configPlotItEl.yml"
if options.channel.lower().count("all"):
    outPlot = "PlotItAll"
    ymlFile = "../../configPlotItAll.yml"
if options.channel.lower().count("skim"):
    outPlot = "PlotItSkim"
    ymlFile = "../../configPlotItSkim.yml"
if not os.path.isdir(outPlot):
    os.mkdir(outPlot)

print "/!\\ you should not have sourced cmsenv"

cmd = "../../../../plotIt/plotIt -o " + outPlot + " " + ymlFile
os.system(cmd)

os.chdir("../../")
