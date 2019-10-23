# Harvard Link Engineering ICOSfit
## Data analysis tools for absorption spectroscopy

ICOSfit is a non-linear least-squares fit algorithm originally developed for processing
data from the [Anderson Group](https://www.arp.harvard.edu/)'s ICOS instruments. It has
since been extended to support other optical configurations, such as Herriott Cells.

The current version of ICOSfit is V4.1.0, released October 23, 2019.

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
