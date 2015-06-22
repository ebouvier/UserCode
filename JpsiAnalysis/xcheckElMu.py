#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when MyAna was run")
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the day")
parser.add_option("-t", "--decay", dest="decay", type="string", default=False, help="semi, di, or all leptonic")
(options, args) = parser.parse_args()

if not options.date or not options.version or not options.decay:
    parser.error("you must specify a date, a version, and a decay type")

dir = options.date
if not os.path.isdir(dir):
    parser.error("you must specify a valid date")
#dir = os.path.join(dir, "v"+options.version)
dir = os.path.join(dir, options.version)
if not os.path.isdir(dir):
    parser.error("you must specify a valid version")

textChannel = " + Jets channel"
if options.decay.lower().count("semi"):
    muChannel = "#mu"+textChannel
    elChannel = "e"+textChannel
if options.decay.lower().count("di"):
    muChannel = "#mu#mu\/#mue"+textChannel
    elChannel = "ee\/e#mu"+textChannel
if options.decay.lower().count("all"):
    muChannel = "#mu\/#mu#mu\/#mue"+textChannel
    elChannel = "e\/ee\/e#mu"+textChannel

os.system("sed -e \"s/@muChannel@/%s/\" -e \"s/@elChannel@/%s/\" configXcheckElMu.template.yml > configXcheckElMu.yml" % (muChannel, elChannel))

print "/!\\ you should not have sourced cmsenv"

os.chdir(dir)
if not os.path.isdir("XcheckElMu"):
    os.mkdir("XcheckElMu")
os.system("../../../../plotIt/plotIt -o XcheckElMu ../../configXcheckElMu.yml")

os.chdir("../../")
os.system("rm -rf configXcheckElMu.yml")
