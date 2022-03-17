#include "global.h"

GlobalData_t GlobalData;

GlobalData_t::GlobalData_t() {
  BackgroundRegion[0] = 10;
  BackgroundRegion[1] = 200;
  SignalRegion[0] = 350;
  SignalRegion[1] = 1750;
  ScanNumRange[0] = ScanNumRange[1] = 0;
  RestartAt = 0;
  PreserveOutput = 0;
  FitFunction = "func_tau";
  MirrorLoss = 180.e-6;
  EtalonFSR = 0.019805;
  EtalonFeedback = 0.;
  MaxFinePositionOffset = .01; // cm-1
  MaxEnsembleDriftPerScan = 5e-3; // cm-1
  CavityLength = 70.; // cm
  CavityFixedLength = 0.; // cm
  LeftLineMargin = RightLineMargin = .05; // cm-1
  LeftLineMarginMultiplier = RightLineMarginMultiplier = 8;
  LineMarginHysteresis = 1e-6;
  Sigma = 0.; // Repurposed for debugging as dscl for line N
  QCLI_Wave = 0;
  SampleRate = 0.;
  SkewTolerance = 1e-5;
  mu_scale = 1e-3;
  epsilon1 = 1e-17;
  epsilon2 = 1e-17;
  epsilon3 = 1e-17;
  binary = 1;
  ICOSdir = "Scans";
  PTFile = "PTE.txt";
  PTformat = 2;
  PTE_nu_F0_col = 0;
  PTE_MirrorLoss_col = 0;
  PTE_PowerParams_col = 0;
  PTE_Feedback_col = 0;
  BaselineFile = 0;
  ICOSdirFineTuned = 0;
  BaselineInput = 0;
  OutputDir = "ICOSout";
  OutputFile = "ICOSsum.dat";
  LogFile = "ICOSfit.log";
  NoTee = 0;
  MFile = "ICOSconfig.m";
  QTdir = QTDIR_DEFAULT_STR;
  Verbosity = 0;
  absorb = 0;
  N_Passes = 0;
  ConvergenceStep = 1e-3;
  ConvergenceCount = 4;
  MaxIterations = 500;
  last_nu_F0 = 0.;
}
