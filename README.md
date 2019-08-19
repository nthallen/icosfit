## HAPP fit: Harvard Aeris Post Processing Fit
Date Created: 15-May-2019 (JDS)

If you are considering using HAPP fit for research or related purposes, the ease of using this program will be made easier by contacting Norton Allen (allen@huarp.harvard.edu) or Josh Shutter (shutter@g.harvard.edu). Also, making use of GitHub Issues will help in responding to questions, comments, and requests.

HAPP fit is derived from the greater ICOS fit package, which also has documentation at https://www.arp.harvard.edu/eng/das/manuals/icosfit.html.

### HAPP FIT DIRECTORY STRUCTURE

It is recommended that the following directory structure for your Aeris sensor files is adopted when using HAPP fit. Additionally, the `Data` folder (not subfolders) should always be on to your Matlab path.

Please note: There are additional Matlab scripts that are Aeris specific (in Matlab/HAPPfit) and non-Aeris specific (in Matlab/ICOSfit) which you can access by cloning the HAPPfit branch of this repository. These scripts are part of the greater ICOS fit package from which HAPP fit is derived. These scripts two folders should also be added to your Matlab path

Format of run_date is YYMMDD.n where n is an integer (n = 1, 2, 3)

    Data/
    ├── run_date/ (output directory for each file run through HAPP fit)
    │   ├── HAPPfit.all/ (raw output directory of HAPP fit results; name might vary)
    │   │   ├── Directory contents will vary depending on verbosity in config file. Will contain .dat file with raw output from HAPP fit
    │   ├── default_etln.mat
    │   ├── fitline.mat
    │   ├── HAPPfit.all (config file containing all the necessary inputs into HAPP fit; including spectral lines to be fit; generated by fitline.m)
    │   ├── PT.mat (generated by HAPPfit_InputProcessing.m)
    │   ├── PTE.txt (generated by HAPPfit_InputProcessing.m)
    │   ├── waves.m
    │   └── waves.mat (modified by waves_editor.m)
    ├── RAW/
    │   ├── run_date/ (make a new folder for each raw spectra data file)
    │   │   ├── SSP/
    │   │   │   ├── Nested directories containing binary files from each scan (generated by HAPPfit_InputProcessing.m)
    │   │   └── Pico100007_YYMMDD_HHMMSSspectra.txt
    ├── sbase.cubic.ptb
    ├── sbase.p4e1.ptb
    ├── sbase.p4e2.ptb
    ├── ICOSfit_Config.m
    ├── Cell_Config.m
    ├── fitline.dat
    └── fitline.mat

### PREPARING AERIS RAW SPECTRA FILES FOR HAPP FIT

1. Run **HAPPfit_InputProcessing.m** which will parse each 1 Hz raw spectral scan into its own directory (located in `SSP`) as well as generate a PTE.txt file containing information on scan number, cell pressure, cell temperature, and fitting fringes (caused by etalons in the optical train)

2. In order to view each individual scan (perhaps to see which ones to neglect), run **scanview.m** after navigating to the `Data/RAW/run_date/` directory in Matlab

3. Navigate to the `Data/run_date` directory to run **waves_editor.m**. The syntax is `waves_editor(‘scannum’, n, ‘qclicomp’, 0)` where n is the scan number from scanview that you’d like to view. The primary purpose of waves_editor is to define the _Signal Region_ which generally is from index 300 - 915. As a side note, the _Background Region_ has generally been from index 936 to 1024.

4. In the `Data/run_date` directory, run **fitline.m**. The purpose of this script is to generate the config file that will be the input into the HAPP fit fitting program. For each spectral line to be included in the fit (specified by ‘en’ which is short for enable), the user can specify whether Doppler (fd) and Lorentz (fl) widths should be fixed (they usually all are for the Aeris sensor). The user should also specify the baseline file (`sbase.p4e2.ptb`) at this time and can edit which scan numbers will actually be fit using ‘Edit Regions’. For the Aeris sensor, also click the checkbox under ‘ml’ that corresponds to the HDO line. This will allow the ‘Matchline’ function to approximately obtain the index position of the HDO (or CH4) line, which is crucial since the HCHO line depends on this reference position. The HDO position is allowed to vary in the fit, so getting the approximate position should be sufficient.


### EXAMPLE INPUT CONFIG FILE FOR HAPP FIT

The output of fitline.m is HAPPfit.all (or similar name such as icosfit.all) which contains all the inputs necessary for HAPP fit to fit the raw 1 Hz spectral data. Let’s take a look at an example input file for the Aeris sensor. In fact, you should check whether your input file looks similar to the one below, though keep in mind that Aeris Technologies has since moved to a stronger water line (thus a new spectral region), so the lines used in the manuscript have now changed.

Comments about the input file
* A pound sign (#) at the start of the line tells HAPP fit to ignore that line
* The threshold determines whether a line is allowed to float or not. Raise the threshold if you don’t want lines to float
* Spectral lines can be grouped together by adding _Group HCHO_ (or similar name) at the end of each individual spectral line. This is important since lines not explicitly grouped will be treated as separate species and thus will likely result in differing mixing ratios.
* Double-check to make sure that the directories are correct at the end of the input file
* Note that the position of the HDO line can also be adjusted if you didn’t visually like the results of fitline’s matchline
* In the file below, the output directory was specified as HAPPfit.all and will contain the actual output (HAPPfit.dat) as well as the output messages from the terminal screen (HAPPfit.log)

#### Configuration file for 180629.1 region all line set 
    Verbosity = 1;
    QCLI_Wave = 0; # Waveform default
    ScanNumRange = [ 1, 84211 ];
    SignalRegion = [ 300, 915 ];
    BackgroundRegion = [ 936, 1024 ];
    SampleRate = 2000 Hz;
    Threshold = 1e-02;
    # Fix Doppler;
    # Fix Lorentz;
    nu0 = 2831;
    Lines = {
      6 1  2831.259826  2.863e-22 0.0560   376.7857 0.69 -0.005600 454332, Fix Doppler, Fix Lorentz, Group CH4;  
      6 1  2831.270145  2.308e-25 0.0450  1912.6663 0.75 -0.005700 332333, Fix Doppler, Fix Lorentz, Group CH4; 
     20 1  2831.273670  2.101e-20 0.0991   480.4415 0.75  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO; 
      6 1  2831.278048  2.471e-22 0.0620   293.1644 0.70 -0.005600 454332, Fix Doppler, Fix Lorentz, Group CH4;  
      6 1  2831.280162  3.408e-25 0.0440  1367.7338 0.75 -0.005700 332333, Fix Doppler, Fix Lorentz, Group CH4;
      6 1  2831.316048  3.394e-23 0.0620   293.1264 0.70 -0.005600 444332, Fix Doppler, Fix Lorentz, Group CH4;
     20 1  2831.325890  2.900e-21 0.0991   491.7551 0.81  0.000000 345440, Fix Doppler, Fix Lorentz, Group HCHO;
      6 1  2831.336647  2.603e-25 0.0440  1353.5277 0.75 -0.005700 332333, Fix Doppler, Fix Lorentz, Group CH4;
      6 1  2831.350063  3.240e-25 0.0390  1694.7051 0.75 -0.005700 332333, Fix Doppler, Fix Lorentz, Group CH4;
     20 1  2831.354980  1.420e-20 0.0990   584.6022 0.77  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO;
      6 1  2831.365713  3.587e-25 0.0410  2978.0776 0.75 -0.005700 332333, Fix Doppler, Fix Lorentz, Group CH4; 
      1 4  2831.405530  1.812e-28 0.0680   872.7905 0.63  0.001230 554103, Fix Doppler, Fix Lorentz, Group HDO;
      1 4  2831.409714  1.812e-28 0.0606   872.7905 0.63  0.000418 551103, Fix Doppler, Fix Lorentz, Group HDO;  
      6 1  2831.420934  1.553e-23 0.0530   690.0174 0.64 -0.005600 444332, Fix Doppler, Fix Lorentz, Group CH4;
     20 1  2831.539300  5.622e-21 0.0990   765.5630 0.65  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO;
      6 1  2831.553376  8.870e-25 0.0543  1780.1223 0.63 -0.008800 455343, Fix Doppler, Fix Lorentz, Group CH4; 
     20 1  2831.557600  5.543e-21 0.0990   765.5572 0.65  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO;
      6 1  2831.561634  1.549e-23 0.0530   689.8767 0.64 -0.005600 444332, Fix Doppler, Fix Lorentz, Group CH4;  
      1 4  2831.580147  4.140e-28 0.0279  1745.8966 0.40 -0.009380 464103, Fix Doppler, Fix Lorentz, Group HDO;      
     20 1  2831.641280  5.839e-20 0.1092    98.4197 0.76  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO;
     20 1  2831.687940  1.499e-21 0.0990   960.0683 0.51  0.000000 345440, Fix Doppler, Fix Lorentz, Group HCHO;
     20 1  2831.689180  1.499e-21 0.0990   960.0683 0.53  0.000000 345440, Fix Doppler, Fix Lorentz, Group HCHO;
      6 1  2831.696122  6.671e-25 0.0531  1779.9844 0.63 -0.009460 455343, Fix Doppler, Fix Lorentz, Group CH4;
     20 1  2831.698900  1.410e-20 0.1027   203.2846 0.71  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO;
     20 1  2831.813400  6.509e-21 0.1007   263.4397 0.79  0.000000 455440, Fix Doppler, Fix Lorentz, Group HCHO;
      6 1  2831.821432  3.671e-24 0.0531  1780.7634 0.63 -0.006370 455343, Fix Doppler, Fix Lorentz, Group CH4;  
      1 4  2831.841315  3.014e-24 0.0881   403.5490 0.72 -0.006979 568801, Position=605, Fix Doppler, Fix Lorentz, Group HDO;   
      6 1  2831.851622  1.983e-24 0.0480  1252.0020 0.62 -0.005600 344332, Fix Doppler, Fix Lorentz, Group CH4; 
      1 4  2831.890594  9.812e-28 0.0286  1532.7319 0.41 -0.012980 464103, Fix Doppler, Fix Lorentz, Group HDO;
      1 1  2831.894802  1.595e-28 0.0830  3598.7266 0.69 -0.003776 444223, Fix Doppler, Fix Lorentz; 
      1 4  2831.956883  2.713e-27 0.0861   573.8907 0.63  0.004131 551101, Fix Doppler, Fix Lorentz, Group HDO;  
      6 1  2831.919900  1.622e-21 0.0622    10.4816 0.68 -0.005120 465343, Fix Doppler, Fix Lorentz, Group CH4;
    };

    # DSFRLimits = [ .90, 1.26 ];
    ConvergenceStep = 1e-12;
    ConvergenceCount = 24;
    MaxIterations = 1500;
    LineMargin = 0.10 cm-1;
    LineMarginMultiplier = 8;
    MirrorLoss = 0.0 ppm;
    CavityLength = 1300.000;
    CavityFixedLength = 0.000;
    N_Passes = 1;
    EtalonFSR = 0.021850 cm-1;
    Binary;
    ICOSdir = ../RAW/180629.1/SSP;
    PTEFile = PTE.txt;
    BaselineFile = ../sbase.p4e2.ptb;
    OutputDir = HAPPfit.all;
    OutputFile = HAPPfit.dat;
    LogFile = HAPPfit.log;


### RUNNING HAPP FIT

To actually run HAPP fit, navigate to Cygwin (Windows) or Terminal (Mac), and type in the following command in the directory where HAPPfit.all is located:

`icosfit.exe HAPPfit.all`

Type `CTRL-C` to terminate the program before it finishes


### PROCESSING THE RESULTS FROM HAPP FIT TO OBTAIN HCHO MIXING RATIOS

There’s a nifty Matlab script from ICOS fit (**rrfit.m**) that generates plots to see how each peak was individually fit. 

To process the HAPP fit output, run **HAPPfit_OutputProcessing.m**. The output from HAPP fit is scaled by a user-determined scale factor that should be determined via a stepped calibration with a standard concentration HCHO gas cylinder. This scale factor is mode-dependent in the sense that it has been found to vary slightly between HDO and CH4 modes. Moreover, when determining the scale factor from a stepped calibration, ensure that all the spectral lines that will be used for successive data sets are present in the stepped calibration workup.

The output of HAPPfit_OutputProcessing is a MAT file that contains both a Matlab datetime object and the HCHO mixing ratio.

# Harvard Link Engineering ICOSfit
## Data analysis tools for absorption spectroscopy

ICOSfit is a non-linear least-squares fit algorithm originally developed for processing
data from the [Anderson Group](https://www.arp.harvard.edu/)'s ICOS instruments. It has
since been extended to support other optical configurations, such as Herriott Cells.

The current version of ICOSfit is V4.0.1, released August 19, 2019.

This archive consists of the following:
- **icosfit:** The core ICOSfit fitting program
- **Matlab/ICOSfit:** a suite of Matlab support utilities for working with ICOSfit and scan data

## icosfit
icosfit is a C++ program for fitting spectra from scanning laser spectrometers. In its
ICOS mode, it specifically understands and compensates for the lineshape perturbations
caused by integrated cavity output spectroscopy (ICOS). The [ICOSfit
Manual](https://www.arp.harvard.edu/eng/das/manuals/icosfit.html) describes the data
formats and the syntax required by the icosfit program. Most users will take advantage
of the Matlab support utilites in the Matlab/ICOSfit directory. These can go a long
way toward performing many of the routine operations in setting up your data analysis.

That said, these programs have a large number of options, tweaks, knobs and buttons,
and not all of them have been documented. If you would like help getting started,
please submit an issue.

V4.0.0 represents a significant rewrite from earlier versions in order to take
advantage of a more sophisticated Levenberg-Marquardt library. This version uses
the [levmar](http://users.ics.forth.gr/~lourakis/levmar/) library, developed by
M.I.A. Lourakis ([bibtex entry](http://users.ics.forth.gr/~lourakis/levmar/bibentry.html)).

## Matlab/ICOSfit
The Matlab/ICOSfit routines provide tools for interactively viewing scan data,
analyzing optical etalon data and setting up the configuration files necessary
to run icosfit. It is entirely possible to use icosfit without Matlab. Contact
the author if you are looking for alternatives.

## Installation
Binary packages are available for [Cygwin](https://cygwin.com) and MacOS. Please
contact the author for more information.

## Compiling
Details on compiling icosfit from source can be found in
[BUILD.md](https://github.com/nthallen/icosfit/blob/master/BUILD.md).

## Troubleshooting
If you encounter problems, please consider submitting an
[issue](https://github.com/nthallen/icosfit/issues) on GitHub or send an
email to the author.

## Contact
icosfit was written by [Norton Allen](mailto:allen@huarp.harvard.edu).
