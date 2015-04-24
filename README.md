# UserCode
Contains the following up-to-date analysis codes (to run after the latest version of the JPsiExtractor):

D0Analysis
==========

## Run the analysis

Modidy MyAnaEl.cpp or MyAnaMu.cpp and copy it into MyAna.cc

Run the analysis with, for instance

    ./run_ALL_MyAna.py --version 1 --channel muonic --descr test

It will run the analysis for all the files in the filelists repository and create rootfiles in

    Date/vX/MyAnaMu/


## Get the stacked distributions 

Then, you can run 

    ./plotIt.py --date 15AprYY --version X --channel muonic

Using configPlotItMu.yml, stacked histograms will be stored in

    Date/vX/PlotItMu/


## Data comparison between both channels 

If you have run the analysis for both semi-e and semi-mu channels, you can compare data with

    ./xcheckElMu.py --date 15AprYY --version X

Using `configXcheckElMu.yml`, distributions will be stored in

    Date/vX/XcheckElMu

## Get event yields

You can also get the number of events in

    Date/vX/NumberOfEvents.tex

after running

    ./getNumberOfEvents.py --date 15AprYY --version X


## Apply the sPlot technique

In `root`:

    .L sPlot.C++
    sPlot("date", "type", inBatch)



JpsiAnalysis
============
