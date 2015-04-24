#! /usr/bin/env python

import os, copy, datetime, pwd, re

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
dir = os.path.join(dir, "v"+options.version)
if not os.path.isdir(dir):
    parser.error("you must specify a valid version")

os.chdir(dir)

outPlot = "XcheckElMu"
ymlFile = "../../configXcheckElMu.yml"

if not os.path.isdir(outPlot):
    os.mkdir(outPlot)

print "/!\\ you should not have sourced cmsenv"
cmd = "../../../../plotIt/setup_lyoserv_sl6_env.sh"
os.system(cmd)

cmd = "../../../../plotIt/plotIt -o " + outPlot + " " + ymlFile
os.system(cmd)

os.chdir("../../")
