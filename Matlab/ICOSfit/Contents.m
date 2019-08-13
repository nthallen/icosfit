% ICOSfit Viewing and Fitting
% * Needs to be rewritten for general use.
% 
% Setup Utilities for icosfit and looking at data:
%   load_ICOSfit_cfg.m - loads or creates ICOSfit_Config file for directory locations.
%   edit_ICOSfit_cfg.m - used by load_ICOSfit.cfg to create gui.
%   load_cell_cfg.m - loads or creates Cell_Config file for cell parameters.
%   edit_cell_cfg.m - used by load_cell_cfg to create gui.
%   eng2PT.m - script to read in eng files and create an appropriate PT.mat file.
%   rewrite_spp.m - rewrites spectra. Useful if spectra need inverting.
%   waves_used.m - lists waveforms used in this run and scan numbers.
%   waves_editor.m - gui to edit region of waveform to use for fitting.
%   etln_fit.m - Fits etalon scan to produce tuning rate and create PTE file. 
%   PTE_hack.m - Create a longer PTE file from a short PTE file.
%   PTEfixskips.m - Fixes skips in PTE file nu_Fo so icosfit runs smooth.
%   writebase.m - Write baseline files
%   writeskewbase.m - Write de-skewed baseline files
%   writeetlnbase.m - Write baseline files suing polynomials and/or sine/cosine waves.
%   *pick_regions.m - program to automatically create data and cal regions to fit.
%   *rawview.m - displays and calculates ringdown times. 
%   fitline.m - gui for creating icosfit configuration files. 
%   matchline.m - Create ICOSfit configuration file (called by fitline)
%
% Looking at Raw Data:
%   loadscans.m - read binary data and return data, etalon, and bkgd vectors.
%   scan_viewer.m - called by scanview
%   scanview.m - Program for scanning through raw data.
%   *rawview.m - Review logged RAW ringdown data and compare fits
%     logchi.m - called via fmins() by rawview.m
%     lvoffset.m - Display results of rawview.m
% 
% ICOSfit support (Post fit analysis):
%   diagnose.m - View ICOSfit Details
%   mixlines.m - View ICOSfit mixing ratios
%   dispfix.m - View ICOSfit fix/float status
%   rrfit.m - Display individual fit files
%   rrcompare.m - Plots to compare fit files from two bases
%   rrresid.m - Outputs residuals from fits. Useful with dft.m 
%   allan_var_plot.m - creates a simple Allan Variance plot
% 
% Utilities:
%   fitfringe.m - Locate Diagnostic Etalon fringes
%   find_scans_dir.m - locate where the data LOG files are stored.
%   get_nu.m - Returns relative wavenumber for spectra
%   get_sigma_from_fit.m - Calculates the standard deviation of the residuals
%   laser_drift.m - calculates the laser drift from the PTE file. 
%   readetlnbase.m - reads a baseline files and outputs vectors.
%   scanload.m - locate and load specified ScanNum file
%   loadbin.m - simple binary loader for ScanNum files
%   writebin.m - produce icos-format binary files
%   load_mat_files.m - searches for mat files in the usual directories.
%   ICOSsetup.m - Common utility for locating directories, etc.
%   mlf_path.m - Create path from ScanNum number
%   mlf_mkdir.m - Create directories appropriate for ScanNum
%   peakfind.m - Generic peak finder. Used in matchline5, icosnoise
%   isovals.m - HITRAN values
%   skew_matrix.m - calculates skew matrix and gain factor
%   *archiveICOSdata.m - program to create .WB57 archive files
%   *combineICOSout.m - Combines multiple ICOSout directories into one
%   *combineICOSoutline.m - Reads in multiple regions/suffix into a singles structure.
% 
% Files associate with creating voigt line shape:
%   humlik.m
%   voigt3.m
%   humlicek.for
%   humlik.for
% 
