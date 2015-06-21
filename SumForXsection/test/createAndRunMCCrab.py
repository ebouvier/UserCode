#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("", "--run", action="store_true", dest="run", default=False, help="run crab")
(options, args) = parser.parse_args()


datasets = {}
for file in args:
    with open(file) as f:
        datasets.update(json.load(f))
    
# Get username address
#user_name = "\'/store/user/%s\'" % (pwd.getpwuid(os.getuid()).pw_name)
user_name = "\'/store/user/ebouvier\'" 

d = datetime.datetime.now().strftime("%y%b%d")

version = 1

datasets = [
    #Jpsi ttbar samples
    ["/TTJets_MSDecays_JpsiFilter_1665_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v1/AODSIM", "TTJets_MSDecays_JpsiFilter_1665", "4"],
    ["/TTJets_MSDecays_JpsiFilter_1695_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v2/AODSIM", "TTJets_MSDecays_JpsiFilter_1695", "4"],
    ["/TTJets_MSDecays_JpsiFilter_1715_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v2/AODSIM", "TTJets_MSDecays_JpsiFilter_1715", "4"],
    ["/TTJets_MSDecays_JpsiFilter_central_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v2/AODSIM", "TTJets_MSDecays_JpsiFilter_1725", "4"],
    ["/TTJets_MSDecays_JpsiFilter_1735_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v1/AODSIM", "TTJets_MSDecays_JpsiFilter_1735", "4"],
    ["/TTJets_MSDecays_JpsiFilter_1755_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v2/AODSIM", "TTJets_MSDecays_JpsiFilter_1755", "4"],
    ["/TTJets_MSDecays_JpsiFilter_1785_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v1/AODSIM", "TTJets_MSDecays_JpsiFilter_1785", "4"],
    ["/TTJets_MSDecays_JpsiFilter_matchingdown_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v1/AODSIM", "TTJets_MSDecays_JpsiFilter_matchingdown", "4"],
    ["/TTJets_MSDecays_JpsiFilter_matchingup_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v2/AODSIM", "TTJets_MSDecays_JpsiFilter_matchingup", "4"],
    ["/TTJets_MSDecays_JpsiFilter_scaledown_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v1/AODSIM", "TTJets_MSDecays_JpsiFilter_scaledown", "4"],
    ["/TTJets_MSDecays_JpsiFilter_scaleup_TuneZ2star_8TeV-madgraph-tauola/Summer12DR53X-PU_S10_START53_V19-v2/AODSIM", "TTJets_MSDecays_JpsiFilter_scaleup", "4"],
    ]

print("Creating configs for crab. Today is %s, you are %s and it's version %d" % (d, user_name, version))
print("")

if not os.path.exists(d):
    os.mkdir(d)

pset_name = "\'sumforxsection_cfg.py\'"
out_name = "\'histoWeights.root\'"

for dataset in datasets:

    dataset_path = "\'"+dataset[0]+"\'"
    dataset_name = dataset[1]
    dataset_quanta = dataset[2]

    task_name = ("\'MC_SumForXsection_%s\'") % (dataset_name)
    publish_name = "\'%s_%s-v%d\'" % (dataset_name, d, version)
    output_file = "%s/crab_MC_SumForXsection_%s.py" % (d, dataset_name)
    output_dir = ("\'crab_tasks/%s\'") % (d)

    print("\tCreating config file for %s" % (dataset_path))
    print("\t\tName: \'%s\'" % dataset_name)
    print("\t\tPublishing name: %s" % publish_name)
    print("")

    os.system("sed -e \"s#@datasetname@#%s#\" -e \"s#@taskname@#%s#g\" -e \"s#@outputdir@#%s#g\" -e \"s#@username@#%s#g\" -e \"s#@psetname@#%s#g\" -e \"s#@outname@#%s#g\" -e \"s#@publishname@#%s#g\" -e \"s#@datasetquanta@#%s#g\" crab_MC.cfg.template.ipnl > %s" % (dataset_path, task_name, output_dir, user_name, pset_name, out_name, publish_name, dataset_quanta, output_file))
    
    cmd = "crab submit %s" % (output_file)
    if options.run:
        os.system(cmd)

