#! /usr/bin/env python

import os, copy, datetime, pwd, re

from optparse import OptionParser
parser = OptionParser()
parser.add_option("-d", "--date", dest="date", type="string", default=False, help="date when the task was submitted")
parser.add_option("", "--submit", action="store_true", dest="submit", default=False, help="submit all tasks")
parser.add_option("", "--status", action="store_true", dest="status", default=False, help="status of all tasks")
parser.add_option("", "--log", action="store_true", dest="log", default=False, help="getlog of all tasks")
parser.add_option("", "--get", action="store_true", dest="get", default=False, help="getoutput of all tasks")
parser.add_option("", "--report", action="store_true", dest="report", default=False, help="report all tasks")
parser.add_option("", "--publish", action="store_true", dest="publish", default=False, help="publish all tasks")
parser.add_option("", "--purge", action="store_true", dest="purge", default=False, help="purge all tasks")
parser.add_option("", "--kill", action="store_true", dest="kill", default=False, help="kill all tasks")
(options, args) = parser.parse_args()

if not options.submit and not options.status and not options.log and not options.get and not options.report and not options.publish and not options.purge and not options.kill:
    parser.error("you must specify a valid action")

if not os.path.isdir("log"):
    os.mkdir("log/")
    
if options.submit:

    if not options.date or not os.path.isdir(options.date):
        parser.error("you must specify a valid date")

    crabCfgs = [name for name in os.listdir(options.date) if (name.startswith('crab_') and name.endswith('.py'))]

    for crabCfg in crabCfgs:
        cmd = "crab submit " + os.path.join(options.date, crabCfg) + " >& log/submit_" + crabCfg[5:-3] + ".log" 
        os.system(cmd)

else:        

    if not options.date or not os.path.isdir(os.path.join("crab_tasks", options.date)):
        parser.error("you must specify a valid date")
    
    rootName = os.path.join("crab_tasks", options.date)
    crabFolders = [name for name in os.listdir(rootName) if (os.path.isdir(os.path.join(rootName, name)) and name.startswith("crab_"))]

    for crabFolder in crabFolders:

        folderName = os.path.join(rootName, crabFolder)

        if options.status:
            cmd = "crab status " + folderName + " >& log/status_" + folderName[24:] + ".log"
        if options.log:
            cmd = "crab getlog " + folderName + " >& log/getlog_" + folderName[24:] + ".log"
        if options.get:
            cmd = "crab getoutput " + folderName + " >& log/getouput_" + folderName[24:] + ".log"
        if options.report:
            cmd = "crab report " + folderName + " >& log/report_" + folderName[24:] + ".log"
        if options.publish:
            cmd = "crab publish " + folderName + " >& log/publish_" + folderName[24:] + ".log"
        if options.purge:
            cmd = "crab purge --cache " + folderName + " >& log/purge_" + folderName[24:] + ".log"
        if options.kill:
            cmd = "crab kill " + folderName + " >& log/kill_" + folderName[24:] + ".log"
        
        os.system(cmd)

