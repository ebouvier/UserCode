#!/usr/bin/env python
#
#==============================================================================#
# Import Modules                                                               #
#==============================================================================#

import sys, os, string, shutil

#outRoot ="MuTagForRivet_El_selection_date"
#outRoot ="MuTagForRivet_Mu_selection_date"
outRoot ="MuTagForRivet_Mu_test"
exe = "./runMyAna"

fileListDir = "filelists_15Apr01"

mkdir="mkdir "+outRoot
os.system(mkdir)

copy = "cp MyAna.cc "+outRoot+"/"
os.system(copy)

filelist = os.popen("ls  "+fileListDir+"/*.list").readlines()

for aFile in filelist:
   
    outRoo1 = outRoot+os.sep+string.split(string.strip(aFile),"/")[-1][:-5]+".root"
    outLog1 = outRoot+os.sep+string.split(string.strip(aFile),"/")[-1][:-5]+".log"
    
    option  = " "
#    option  = " -skim"
    if aFile.count("SingleElectron") != 1 and aFile.count("SingleMu") != 1 and aFile.count("MuHad") != 1 and aFile.count("ElectronHad") != 1 :
        option = option+" -mc"

    if aFile.count("TTJets_FullLeptMGDecays") ==  1 or aFile.count("TTJets_SemiLeptMGDecays") == 1 :
        option = option+" -sig"    
        
    if aFile.count("TTJets") == 1 or aFile.count("TTWJets") == 1 or aFile.count("TTWWJets") == 1 or aFile.count("TTZJets") ==1 :
        option = option+" -ttbar"    
        
    cmd = exe+" -filelist "+string.strip(aFile)+" -out "+outRoo1+" "+option+"  >&  "+outLog1 
    
    print cmd
    os.system(cmd)
    
sys.exit()
