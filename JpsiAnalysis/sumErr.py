#! /usr/bin/env python

import math, os, string, sys

statErr = [
        "Statistical Error", -3.028, 3.028
        ]
systErr = [
        ["Experimental uncertainties", [
            ["Fit calibration", -0.214, 0.214],
            ["FSR of $\\text{J}/\\psi$ daughters", 172.792, 172.594],
            #["Jet energy scale", 172.783-0.002, 172.788+0.002], 
            #["Jet energy resolution", 172.787-0.002, 172.792+0.002], 
            ["Jet energy scale", 172.783, 172.788], 
            ["Jet energy resolution", 172.787, 172.792], 
            ["Pile up", 172.928, 172.758],
            ["Muon momentum scale", 173.274, 172.6324],
            #["Muon momentum resolution", 172.082, 173.537], # not cited in https://twiki.cern.ch/twiki/bin/view/CMS/TopMassSystematics
            ["Electron momentum scale", 173.491, 172.145],
            #["Electron momentum resolution", 171.276, 174.675],# not cited in https://twiki.cern.ch/twiki/bin/view/CMS/TopMassSystematics
            ["Trigger scale factors", 172.792, 172.385],
            #["Non-$\\text{t}\\bar{\\text{t}}$ background", 172.815+0.002, 172.789-0.002] 
            ["Non-$\\text{t}\\bar{\\text{t}}$ background", 172.815, 172.789] 
            ]],
        ["Modeling of perturbative QCD", [
            ["Renormalization scale", 173.263, 172.637],
            ["ME-PS matching threshold", 172.792, 173.334],
            ["Parton density functions", 172.407, 172.909],
            ["ME generator", 172.792, 170.685],
            ["top-quark transverse momentum", 172.792, 172.165]
            ]],
        ["Modeling of soft QCD", [
            ["Underlying event", 170.966, 172.945],
            ["Color reconnection modeling", 170.966, 172.341]
            ]],
        #["Modeling of hadronization", [
            #["b fragmentation", FIXME, FIXME]
            #]]
        ]
dir = os.path.join("15Jul20", "Results")
if not os.path.isdir(dir):
    os.mkdir(dir)


texFile = "Uncertainties.tex"
tex = open(os.path.join(dir,texFile), 'w')

tex.write("\\documentclass[a4paper]{article}\n")
tex.write("\\usepackage{array}\n")
tex.write("\\usepackage{multirow}\n")
tex.write("\\usepackage{amsmath}\n")
tex.write("\\newcommand{\\ttbar}{\\ensuremath{\\text{t}\\bar{\\text{t}}}}\n")
tex.write("\\begin{document}\n")
tex.write("\\begin{center}\n")
tex.write("\n%%%\n")

tex.write("\\begin{table}[b!] \n")
tex.write("\\begin{center} \n")
tex.write("\\caption{\label{results:tab1} \n")
tex.write("Statistical and systematic uncertainties ($\\text{GeV/c}^2$). \n")
tex.write("Electron and muon channels are summed before fitting. \n")
tex.write("Systematic uncertainties are computed by fitting, with the \n") 
tex.write("nominal PDF, toys of Poisson($N^{\\text{MC}}$) events, generated from \n")
tex.write("the variations for $M_\\text{top}=172.5\\;\\text{GeV/c}^2$. \n")
tex.write("} \n")
tex.write("\\begin{tabular}{lc} \n")
tex.write("Source & Value ($\\text{GeV/c}^2$) \\\\ \n")
tex.write("\\hline\n")

# Erreurs syst
systTot = 0.
for sourceSys in systErr:
    cat =sourceSys[0]
    subcat = sourceSys[1]
    tex.write("\\hline\n")
    tex.write("\\multicolumn{2}{c}{\\it " + cat + "} \\\\ \n")
    for source in subcat:
        name = source[0]
        value = abs(source[2] - source[1])/2.
        tex.write(name + " & %.3f \\\\ \n" % value)
        systTot += pow(value, 2.)

tex.write("\\hline\\hline\n")

# Somme des erreurs syst
systTot = pow(systTot, 0.5)
tex.write("Systematic uncertainty & %.3f \\\\ \n" % systTot)

# Erreur stat
statTot = abs(statErr[2]-statErr[1])/2.
tex.write("Statistical uncertainty & %.3f \\\\ \n" % statTot)

tex.write("\\hline\\hline\n")

# Erreur tot
Tot = pow(pow(statTot, 2.)+pow(systTot, 2.), 0.5)
tex.write("Total uncertainty & %.3f \\\\ \n" % Tot)

tex.write("\\end{tabular}\n")
tex.write("\\end{center}\n")
tex.write("\\end{table}\n")

tex.write("\n%%%\n")
tex.write("\\end{center}\n")
tex.write("\n\\end{document}")
    
tex.close()

os.chdir(dir)
cmd = "pdflatex " + texFile
os.system(cmd)
cmd = "rm -f *.aux *.log"
os.system(cmd)
os.chdir("../..")
print "\n"+os.path.join(dir,texFile)+" has been created and compiled."

