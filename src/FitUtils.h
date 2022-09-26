#ifndef FitUtils_hh
#define FitUtils_hh 1

#include <RtypesCore.h>
#include <TF1.h>

/**
 * @namespace FitUtils
 * Implementation of a Crystal Ball function in ROOT. Supports regular and reversed crystal ball functions.
 */

namespace FitUtils {

  /**
   * @class CrystalBallFunctionObject
   * ROOT function object for the Crystal Ball function
   */
  class CrystalBallFunctionObject {
    public:
      CrystalBallFunctionObject(Bool_t _isInverted = kFALSE);
      Double_t operator()(double *_x, double *par);

    private:
      Bool_t isReversed;
  };

  /**
   * @brief Obtain a CrystalBall fitting function based on a given histogram.
   *
   * Function sets corresponding Crystal GBall function parameters based on the shape of the histogram. User can immediately do the fit.
   *
   * @param hist histogram to be fitted.
   * @param reversed set if Crystal Ball function is reversed or not. Default is kFALSE.
   * @return ROOT function ready for fitting.
   */
  TF1* getCrystalBallFunction(TH1 *hist, Bool_t reversed = kFALSE);

  // TF1* fitHistWithROOTCrystalBall(TH1 *hist, Bool_t inverted);
}

#endif
