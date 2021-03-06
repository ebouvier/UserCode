#! /usr/bin/env python

import math, os, string, sys

statErr = [
        "Statistical Error", -3.008, 3.008
        ]
ref = 172.789
systErr = [
        ["Experimental uncertainties", [
            ["Fit calibration", ref-0.212, ref+0.212],
            ["Muon momentum scale", 172.748, 172.920],
            ["Electron momentum scale", 172.720, 172.941],
            ["Modeling of the $\\text{J}/\\psi$ mass distribution", 172.696, ref],
            ["Jet energy scale", 172.783, 172.788], 
            ["Jet energy resolution", 172.787, 172.792], 
            ["Trigger scale factors", 172.379, ref],
            ["Non-$\\text{t}\\bar{\\text{t}}$ background", 172.785, 172.811], 
            ["Pile up", 172.747, 172.917],
            ]],
        ["Theoretical uncertainties", [
            #["ME generator", FIXME, FIXME],
            ["Renormalization scale", 172.252, 172.873],
            ["ME-PS matching threshold", 172.763, 173.373],
            ["Underlying event", 172.656, 172.863],
            ["Color reconnection modelling", 172.745, 172.811],
            ["top-quark transverse momentum", 172.154, ref],
            ["b fragmentation", 172.430, 173.018],
            ["Parton density functions", 172.397, 172.901],
            ]],
        ]
dir = os.path.join("15Dec15", "Results")
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
tex.write("Statistical and systematic uncertainties ($\\text{GeV}$). \n")
tex.write("Electron and muon channels are summed before fitting. \n")
tex.write("Systematic uncertainties are computed by fitting, with the \n") 
tex.write("nominal PDF, toys of Poisson($N^{\\text{MC}}$) events, generated from \n")
tex.write("the variations for $M_\\text{top}=172.5\\;\\text{GeV}$. \n")
tex.write("} \n")
tex.write("\\begin{tabular}{lc} \n")
tex.write("Source & Value ($\\text{GeV}$) \\\\ \n")
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
        value = 0.
        if (abs(source[2]-ref) < 1e-6 or abs(source[1]-ref) < 1e-6 or abs(abs(source[2]-ref)-abs(source[1]-ref)) < 6e-2):
            value = abs(source[2] - source[1])/2.
            tex.write(name + " & %.3f \\\\ \n" % value)
        else:
            value2 = source[2]-ref
            value1 = source[1]-ref
            value = (abs(value1)+abs(value2))/2.
            tex.write(name + " & $^{+%.3f}_{%.3f}$ \\\\ \n" % (max(value1,value2), min(value1,value2)))
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

