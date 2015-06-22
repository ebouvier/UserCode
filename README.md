# UserCode
This folder contains the following up-to-date analysis codes (to run after the latest version of the JPsiExtractor):



## D0Analysis


### Run the analysis

Run, for instance, the analysis with:

    ./run_ALL_MyAna.py --filelist filelists_date --version 1 --channel muonic --descr test

It will copy `MyAnaMu.cpp` as `MyAna.cc`, run the analysis for all the files in the filelists repository, and create rootfiles in:

    Date/vX/MyAnaMu/

A log file names `date_version_channel_description.log` is stored in the `LogMyAna` repository.

If you wish to skim the extracted files, run:

    ./run_ALL_MyAna.py --filelist filelists_date --version X --channel skim --descr test

and then:    

    ./createSkimFilelists.py --date 15AprYY --version X


### Get the stacked distributions 

Then, you can run:

    ./plotIt.py --date 15AprYY --version X --channel muonic

Using `configPlotIt.template.yml`, stacked histograms will be stored in:

    Date/vX/PlotItMu/

This also work for the skimmed files.


### Data comparison between both channels 

If you have run the analysis for both semi-e and semi-mu channels, you can compare data with:

    ./xcheckElMu.py --date 15AprYY --version X

Using `configXcheckElMu.yml`, distributions will be stored in:

    Date/vX/XcheckElMu


### Get event yields

You can also get the number of events in:

    Date/vX/NumberOfEvents.tex

after running:

    ./getNumberOfEvents.py --date 15AprYY --version X


### Merge both channels

`hadd` commands (for data, and TTJets* files) are executed when running:

    ./mergeChannels.py --date 15AprYY --version X

Rootfiles are stored in `date/version/MyAnaAll`    


### Apply the sPlot technique

In `root`:

    .L sPlot.C++
    sPlot("date", "version", inBatch)



## JpsiAnalysis


### Run the analysis

Run, for instance, the analysis with:

    ./run_ALL_MyAna.py --filelist filelists_date --version 1 --channel muonic --descr test

It will copy `MyAnaMu.cpp` as `MyAna.cc`, run the analysis for all the files in the filelists repository, and create rootfiles in:

    Date/vX/MyAnaMu/

A log file names `date_version_channel_description.log` is stored in the `LogMyAna` repository.

If you wish to skim the extracted files, run:

    ./run_ALL_MyAna.py --filelist filelists_date --version X --channel skim --descr test

and then:    

    ./createSkimFilelists.py --date 15AprYY --version X


### Get the stacked distributions 

Then, you can run:

    ./plotIt.py --date 15AprYY --version X --channel muonic --decay semi

Using `configPlotIt.template.yml`, stacked histograms will be stored in:

    Date/vX/PlotItMu/

To check the J/&#968; enriched samples, run:

    ./plotItJpsi.py --date 15AprYY --version X --channel muonic --decay semi

Using `configPlotItJpsi.template.yml`, stacked histograms will be stored in:

    Date/vX/PlotItJpsiMu/

This also work for the skimmed files.


### Data comparison between both channels 

If you have run the analysis for both semi-e and semi-mu channels, you can compare data with:

    ./xcheckElMu.py --date 15AprYY --version X --decay semi

Using `configXcheckElMu.template.yml`, distributions will be stored in:

    Date/vX/XcheckElMu


### Get event yields

You can also get the number of events in:

    Date/vX/NumberOfEvents.tex

after running:

    ./getNumberOfEvents.py --date 15AprYY --version X --decay semi


### Add MC background and signal contributions

This can be done in root:

    .L mergeMC.C++
    mergeMC("date", "version", "electron")
    mergeMC("date", "version", "muon")

In the `date/version/MyAnaEl` and `date/version/MyAnaMu` folders, rootfiles named `All_mtop.root` are created. They contain the binned and unbinned trilepton mass distributions, each contribution being normalized at the cross section.


### Merge both channels

`hadd` commands (for data, central J/&#968; enriched, and All* files) are executed when running:

    ./mergeChannels.py --date 15AprYY --version X

Rootfiles are stored in `date/version/MyAnaAll`    


### Perform a simple calibration

This can be done in root:

    .L calib.C++
    calib("date", "version", "decay", binning)

Binning can be 0 for an unbinned fit, 2 for a binned fit, and 1 in between. Results are stored in the `date/version/CalibEl`, `date/version/CalibMu`, and `date/version/CalibAll` folders. Fits can be binned or unbinned.


### Perform a combine template fit

This can be done in root:

    .L simultaneousFit.C++
    simultaneousFit("date", "version", "decay", blind, nEvtEl, nEvtMu)

If the `blind` parameter is set to `false`, the full stat central sample is used instead of data.
If `nEvtEl` or `nEvtEl` is not provided, the number of events in the data samples are automatically used for the toys generation.
Results are stored in the `date/version/SimultaneousFitEl`, `date/version/SimultaneousFitMu`, and `date/version/SimultaneousFitAll` folders.  
The systematic uncertainty that is related to the fit calibration is computed. To compute other systematic uncertainties, run the analysis, `mergeMCforSys.C`, `mergeChannels.py`, and `computeSys.C`.


### Perform a simple template fit (as cross-check)

This can be done in root:

    .L simpleFit.C++
    simpleFit("date", "version", "decay", blind, nEvtEl, nEvtMu)

If the `blind` parameter is set to `false`, the full stat central sample is used instead of data.
If `nEvtEl` or `nEvtEl` is not provided, the number of events in the data samples are automatically used for the toys generation.
Results are stored in the `date/version/SimpleFitEl`, `date/version/SimpleFitMu`, and `date/version/SimpleFitAll` folders.  


### Gaussian fit of the J/&#968; peak in data

In root:
    
    .L fitMJpsi.C++
    fitMJpsi("date","version","channel","decay")

Results are store in the `date/version/MJpsi` directory.

To compare data and MC peak, use `fitJpsiPeaks.C`.


### Pairing studies

After merging channels, in root:

    .L pairingStudies.C++
    pairingStudies("date","version","decay")

Several J/&#968; properties are considered according to their pairing (only matched events) for the central MSDecays sample. Results are stored in the `date/version/PairingStudies` folder.
