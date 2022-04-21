# Version History for icosfit.

### V4.3.1 April 21, 2022

  * Added coadd capability:
    * New coadd modifier to PTEFile statement:
      * example: PTEFile = PTE.txt coadd;
      * An additional column is added to the PTEFile format after the first column:
        * Column 1: first scan number
        * Column 2: last  scan number
        * Column 3: Pressure
        * etc.
      * Assumes raw scans are increasing by one, but  tolerates missing scans

### V4.3.0 March 16, 2022

  * Updated Q(T) values from HITRAN and automated the update process, making it much easier to add new isotopologues
  * Added NoTee keyword to write directly to LogFile, suppressing output to the console

### V4.2.8 March 1-8, 2022

  * Added average_spectra2, TuningRateAnalysis
  * PTE_add_nu_F0: added syntax for interpolation
  * Added explicit exit menus for scanview, etln_fit and fitline to run smoothly on the cluster

### V4.2.7 February 7, 2022

  * Added etln_fine_tune to address some types of laser feedback
  * Matchline: Optionally group lines by isotopologue

### V4.2.6 July 5, 2021

  * Fixed improper handling of PTEfile options
  * Renamed parameter TolerableDrift to MaxFinePositionOffset
  * Added parameter MaxEnsembleDriftPerScan

### V4.2.5 June 22, 2020

  * Fixed minor bugs in optimizer utilities
  * Added support for non-pc platforms
  
### V4.2.4 June 16, 2020

  * Fixed parameter scaling bug with line number density
  * Cleaned up optimization tools

### V4.2.3 May 15, 2020

  * Fixed '+ nu_F0' to reset nu_F0 before each scan

### V4.2.2 March 26, 2020

  * Better handling of fixed lines to support outside lines

### V4.2.1 December 1, 2019

  * Re-release to coordinate with Zenodo

### V4.2.0 December 1, 2019

  * New Matlab optimization tools

### V4.1.0 October 23, 2019

  * Fixed off-by-one errors affecting accuracy
  * Exposed levmar options to control termination conditions
  * Added icosfit_survey scripts to evaluate epsilon2 values

### V4.0.1 August 19, 2019

  * Initial Public Release
