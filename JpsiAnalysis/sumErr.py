#! /usr/bin/env python

import math, os, string, sys

statErr = [
        "Statistical Error", -3.013, 3.013
        ]
nEvts = 664
systErr = [
        ["Experimental uncertainties", [
            ["Fit calibration", -0.204, 0.204],
            ["FSR of $\\text{J}/\\psi$ daughters", 2*172.650-172.527, 172.527],
            ["Jet energy scale (JES)", 172.658, 172.667],
            ["Jet energy resolution (JER)", 172.644, 172.656],
            ["Pile up", 172.554, 172.685],
            ["Muon momentum scale", 173.208, 172.092],
            ["Muon momentum resolution", 172.620, 172.662],
            ["Electron momentum scale", 173.353, 172.001],
            ["Electron momentum resolution", 172.979, 172.988],
            ["Trigger scale factors", 172.650, 172.095],
            ["Non-$\\text{t}\\bar{\\text{t}}$ background", 172.669, 172.648]
            ]],
        ["Modeling of perturbative QCD", [
            ["Renormalization scale", 173.122, 172.912],
            ["ME-PS matching threshold", 172.953, 172.517],
            #["Parton density functions", FIXME, FIXME],
            #["ME generator", FIXME, FIXME],
            ["top-quark transverse momentum", 172.650, 171.918]
            ]],
        #["Modeling of soft QCD", [
            #["Underlying event", FIXME, FIXME],
            #["Color reconnection modeling", FIXME, FIXME]
            #]],
        #["Modeling of hadronization", [
            #["b fragmentation", FIXME, FIXME]
            #]]
        ]
dir = os.path.join("15Jun22", "Results")
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
tex.write("nominal PDF, 3000 toys of Poisson(%.0f) events, generated from \n" % nEvts)
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

