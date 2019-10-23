#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED
#include "config.h"
#include "funceval.h"

class GlobalData_t {
  public:
    unsigned int BackgroundRegion[2];
    unsigned int SignalRegion[2];
    unsigned int ScanNumRange[2];
    unsigned int RestartAt;
    int PreserveOutput;
    const char *FitFunction;
    ICOS_Float MirrorLoss;
    ICOS_Float EtalonFSR;
    ICOS_Float EtalonFeedback;
    ICOS_Float TolerableDrift;
    ICOS_Float LeftLineMargin;
    ICOS_Float LeftLineMarginMultiplier;
    ICOS_Float RightLineMargin;
    ICOS_Float RightLineMarginMultiplier;
    ICOS_Float LineMarginHysteresis;
    ICOS_Float CavityLength;
    ICOS_Float CavityFixedLength;
    ICOS_Float Sigma;
    ICOS_Float SampleRate;
    ICOS_Float SkewTolerance;
    ICOS_Float mu_scale;
    ICOS_Float epsilon1;
    ICOS_Float epsilon2;
    ICOS_Float epsilon3;
    unsigned short QCLI_Wave;
    int binary;
    const char *ICOSdir;
    const char *PTFile;
    int PTformat;
    int PTE_nu_F0_col;
    int PTE_MirrorLoss_col;
    int PTE_PowerParams_col;
    int PTE_Feedback_col;
    const char *BaselineFile;
    const char *OutputDir;
    const char *OutputFile;
    const char *LogFile;
    const char *MFile;
    const char *QTdir;
    int Verbosity;
    int N_Passes;
    int BaselineInput; // non-zero if column 3 is  a baseline vector
    func_abs_p absorb;
    struct {
      ICOS_Float nu_F0;
      ICOS_Float MirrorLoss;
    } input;
    ICOS_Float ConvergenceStep;
    int ConvergenceCount;
    int MaxIterations;

    GlobalData_t();
};
extern GlobalData_t GlobalData;
#define SetGlobal(x,y) GlobalData.x = y
#define SetGlobalOnce(x,y) (GlobalData.x ? 1 : ((GlobalData.x = y), 0))
#define SetGlobalPair(x,y,z) GlobalData.x[0] = y; GlobalData.x[1] = z
#define SetNu0(x) func_line::nu0 = x
#define Nu0IsSet  (func_line::nu0 != 0)

#define V_CURVES      0x01 /* output curve files for each scan */
#define V_INFO        0x02 /* include info[1:9] in standard output */
#define V_CHKJAC      0x04 /* Check Jacobian and store results in standard output */
#define V_ITERATIONS  0x08 /* output curve files and standard output on each iteration */
#define V_DERIVATIVES 0x10 /* include derivatives in curve files */
#define V_SCALE       0x20 /* include dscl in standard output */
#define V_CHKDER      0x40 /* include finite difference derivative estimates in verbose output */
#define V_VOIGT       0x80 /* include Voigt curve for each line in curve files, X and K in standard files */

extern void ICOS_init();
extern void ICOS_main();

#endif
