#!/usr/bin/env python

import sys, os, string, shutil, datetime
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date of the skim") 
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the skim for that date")
(options, args) = parser.parse_args()

#if not options.date or not options.version or not os.path.isdir(options.date+"/v"+options.version+"/MyAnaSkim"):
if not options.date or not options.version or not os.path.isdir(options.date+"/"+options.version+"/MyAnaSkim"):
    parser.error("you must specify a valid date and version")

newdir = "filelists_"+options.date
try:    
    os.mkdir(newdir)
except OSError:    
    raise OSError("this directory of file lists already exists")

#dir = options.date+"/v"+options.version+"/MyAnaSkim/"
dir = options.date+"/"+options.version+"/MyAnaSkim/"
lists = [name for name in os.listdir(dir) if name.endswith(".root")]

for list in lists:
    newlist = os.path.join(newdir,list[:-4]+"list")
    file = open(newlist, 'w')
    file.write(os.path.join(os.getcwd(),dir+list))
    file.close()

print newdir+" has been created"
