#!/usr/bin/env python

import sys, os, string, shutil, datetime
from optparse import OptionParser

parser = OptionParser()
parser.add_option("-c", "--channel", dest="channel", type="string", default=False, help="electronic, muonic, or skim")
parser.add_option("-f", "--filelist", dest="filelist", type="string", default=False, help="file list directory")
parser.add_option("-v", "--version", dest="version", type="string", default=False, help="version of the day")
parser.add_option("-d", "--descr", dest="descr", type="string", default=False, help="description of the selection") 
(options, args) = parser.parse_args()

if not options.channel or (not options.channel.lower().count("mu") and not options.channel.lower().count("el") and not options.channel.lower().count("skim")):
    parser.error("you must specify the channel considered")
 
if not options.version:
    parser.error("you must specify the version")

if not options.filelist or not os.path.isdir(options.filelist):
    parser.error("you must specify a file list directory")

date = datetime.datetime.now().strftime("%y%b%d")

outRoot = date
if not os.path.isdir(outRoot):
    os.mkdir(outRoot)
#outRoot = os.path.join(outRoot, "v"+options.version)   
outRoot = os.path.join(outRoot, options.version)   
if not os.path.isdir(outRoot):
    os.mkdir(outRoot)
if options.channel.lower().count("mu"):
    outRoot = os.path.join(outRoot, "MyAnaMu")
if options.channel.lower().count("el"):
    outRoot = os.path.join(outRoot, "MyAnaEl")
if options.channel.lower().count("skim"):
    outRoot = os.path.join(outRoot, "MyAnaSkim")
try:    
    os.mkdir(outRoot)
except OSError:    
    raise OSError("this version for this channel already exists")

if not os.path.isdir("LogMyAna"):
    os.mkdir("LogMyAna/")
logFile = os.path.join("LogMyAna", date)    
#logFile += "_v"+options.version     
logFile += "_"+options.version     
if options.channel.lower().count("mu"):
    logFile += "_Mu"
if options.channel.lower().count("el"):
    logFile += "_El"
if options.channel.lower().count("skim"):
    logFile += "_Skim"
if options.descr:
    logFile += "_"+options.descr
logFile += ".log"
log = open(logFile, 'w')

fileListDir = options.filelist 

os.system("make clean")
if options.channel.lower().count("mu"):
    os.system("cp MyAnaMu.cpp MyAna.cc")
if options.channel.lower().count("el"):
    os.system("cp MyAnaEl.cpp MyAna.cc")
if options.channel.lower().count("skim"):
    os.system("cp MyAnaSkim.cpp MyAna.cc")
os.system("make")

copy = "cp MyAna.cc " + outRoot + "/"
os.system(copy)

filelist = os.popen("ls  "+fileListDir+"/*.list").readlines()

for aFile in filelist:
   
    outRoo1 = outRoot+os.sep+string.split(string.strip(aFile),"/")[-1][:-5]+".root"
    outLog1 = outRoot+os.sep+string.split(string.strip(aFile),"/")[-1][:-5]+".log"
    
    option  = ""
    if options.channel.lower().count("skim"):
        option  = option+" -skim"
    if aFile.count("SingleElectron") != 1 and aFile.count("SingleMu") != 1 and aFile.count("MuHad") != 1 and aFile.count("ElectronHad") != 1 :
        option = option+" -mc"

    if aFile.count("TTJets") == 1 or aFile.count("t-channel_mass") == 1:
        option = option+" -sig"    
        
    if aFile.count("TTJets") == 1 or aFile.count("TTWJets") == 1 or aFile.count("TTWWJets") == 1 or aFile.count("TTZJets") ==1 :
        option = option+" -ttbar"    
        
    cmd = "./runMyAna -filelist "+string.strip(aFile)+" -out "+outRoo1+option+" >& "+outLog1+"\n" 
    
    log.write(cmd)
    os.system(cmd)
    
log.close()
sys.exit()
