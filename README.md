# UserCode
This folder contains the following up-to-date analysis codes (to run after the latest version of the JPsiExtractor):



## D0Analysis


### Run the analysis

Modify `MyAnaEl.cpp` or `MyAnaMu.cpp` and copy it into `MyAna.cc`

Run the analysis with:

    ./run_ALL_MyAna.py --filelist filelists_date --version 1 --channel muonic --descr test

It will run the analysis for all the files in the filelists repository and create rootfiles in:

    Date/vX/MyAnaMu/


### Get the stacked distributions 

Then, you can run:

    ./plotIt.py --date 15AprYY --version X --channel muonic

Using `configPlotItMu.yml`, stacked histograms will be stored in:

    Date/vX/PlotItMu/


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


### Apply the sPlot technique

In `root`:

    .L sPlot.C++
    sPlot("date", "type", inBatch)



## JpsiAnalysis


### Run the analysis

Modify `MyAnaEl.cpp` or `MyAnaMu.cpp` and copy it into `MyAna.cc`

Run the analysis with:

    ./run_ALL_MyAna.py --filelist filelists_date --version 1 --channel muonic --descr test

It will run the analysis for all the files in the filelists repository and create rootfiles in:

    Date/vX/MyAnaMu/


### Get the stacked distributions 

Then, you can run:

    ./plotIt.py --date 15AprYY --version X --channel muonic

Using `configPlotItMu.yml`, stacked histograms will be stored in:

    Date/vX/PlotItMu/

To check the J/#968 enriched samples, run:

    ./plotItJpsi.py --date 15AprYY --version X --channel muonic

Using `configPlotItJpsiMu.yml`, stacked histograms will be stored in:

    Date/vX/PlotItJpsiMu/


### Get event yields

You can also get the number of events in:

    Date/vX/NumberOfEvents.tex

after running:

    ./getNumberOfEvents.py --date 15AprYY --version X


### Add MC background and signal contributions

This can be done in root:

    .L mergeMC.C++
    mergeMC("date", "version", "electron")
    mergeMC("date", "version", "muon")

In the `date/version/MyAnaEl` and `date/version/MyAnaMu` folders, rootfiles named `All_mtop.root` are created. They contain the binned and unbinned trilepton mass distributions, each contribution being normalized at the cross section.


### Merge both channels

`hadd` commands are executed when running:

    ./mergeChannels.py --date 15AprYY --version X

Rootfiles are stored in `date/version/MyAnaAll`    


### Perform a simple calbration

This can be done in root:

    .L calib.C++
    calib("date", "version", 0)
    calib("date", "version", 1)
    calib("date", "version", 2)

Results are stored in the `date/version/CalibEl`, `date/version/CalibMu`, and `date/version/CalibAll` folders. Fits can be binned or unbinned.


### Perform a combine template fit

This can be done in root:

    .L simultaneousFit.C++
    simultaneousFit("date", "version", true)
    simultaneousFit("date", "version", false)

Results are stored in the `date/version/SimultaneousFitEl`, `date/version/SimultaneousFitMu`, and `date/version/SimultaneousFitAll` folders.  


### Perform a simple template fit (as cross-check)

This can be done in root:

    .L simpleFit.C++
    simpleFit("date", "version", true)
    simpleFit("date", "version", false)

Results are stored in the `date/version/SimpleFitEl`, `date/version/SimpleFitMu`, and `date/version/SimpleFitAll` folders.  


### Gaussian fit of the J/&#968 peak in data

In root:
    
    .L fitMJpsi.C++
    fitMJpsi("date","version","muon")
    fitMJpsi("date","version","electron")
    fitMJpsi("date","version","all")

Results are store in the `date/version/MJpsi` directory.


### Pairing studies

After merging channels, in root:

    .L pairingStudies.C++
    pairingStudies("date","version")

Several J/&#968 properties are considered according to their pairing (only matched events) for the central MSDecays sample. Results are stored in the `date/version/PairingStudies` folder.
