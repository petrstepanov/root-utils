/** @brief Utility namespace for ROOT files

 Detailed description follows here.
 @author X. XYZ, DESY
 @date March 2008
 */

#ifndef FitUtils_hh
#define FitUtils_hh 1

#include <RtypesCore.h>
#include <TF1.h>

class CrystalBallFunctionObject {
  public:
    CrystalBallFunctionObject(Bool_t _isInverted = kFALSE);
    Double_t operator()(double *_x, double *par);

  private:
    Bool_t isReversed;
};

namespace FitUtils {

  TF1* fitHistWithROOTCrystalBall(TH1 *hist, Bool_t inverted);
  TF1* getCrystalBallFunction(TH1 *hist, Bool_t reversed = kFALSE);
}

#endif
