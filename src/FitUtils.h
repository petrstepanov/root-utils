#ifndef FitUtils_hh
#define FitUtils_hh 1

#include <RtypesCore.h>
#include <TF1.h>
#include <TVector2.h>

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

  /**
   * @brief Calculate Crystal Ball function mean value.
   *
   * @param cball Crystal ball function.
   * @param reversed type of the crystal ball function.
   * @return TVector2 mean value and error.
   */
  TVector2 getCrystalBallMean(TF1* cball);

  /**
   * @brief Calculate Crystal Ball dispersion (standard deviation) value.
   *
   * @param cball Crystal ball function.
   * @param reversed type of the crystal ball function.
   * @return TVector2 dispersion value and error.
   */
  TVector2 getCrystalBallDispersion(TF1* cball);

  /**
   * @brief Calculate Crystal Ball resolution value (standard deviation / mean).
   *
   * @param cball Crystal ball function.
   * @return TVector2 resolution value and error.
   */
  TVector2 getCrystalBallResolution(TF1* cball);

  /**
   * @brief Calculate resolution of a distribution with given standard deviation and mean.
   *
   * @param mean distribution mean.
   * @param meanErr distribution mean error.
   * @param std distribution standard deviation.
   * @param stdErr distribution standard deviation error.
   * @return TVector2 resolution value and error.
   */
  TVector2 evalResolution(Double_t mean, Double_t meanErr, Double_t std, Double_t stdErr);
}

#endif
