#ifndef HistUtils_hh
#define HistUtils_hh 1

#include <TH1.h>
#include <TH2.h>
#include <TList.h>
#include <TTree.h>

/**
 * @namespace HistUtils
 * Useful histogram operations.
 */

namespace HistUtils {
  /**
   * @brief Get histogram mean value along Y axis.
   *
   * Function returns an average value of counts across all the bins.
   *
   * @param hist histogram.
   * @return double value of mean counts.
   */
  Double_t getMeanY(TH1 *hist);

  /**
   * @brief Invert histogram.
   *
   * Function inverts histogram values in each bin.
   *
   * @param hist histogram.
   */
  void invertHist(TH1 *hist);

  /**
   * @brief Crop histogram to a given range.
   *
   * Function finds corresponding bins and returns cropped histogram with bins including the given range.
   *
   * @param hist histogram.
   * @param minX minimum value along X axis of the new histogram.
   * @param maxX maximum value along X axis of the new histogram.
   * @return new TH1 histogram.
   */
  TH1* cropHistogram(TH1 *hist, Double_t minX, Double_t maxX);

  /**
   * @brief Crop histogram to a given bin range.
   *
   * Function returns cropped histogram with bin numbers between minBin and maxBin.
   *
   * @param hist histogram.
   * @param minBin minimum bin number.
   * @param maxBin maximum bin number.
   * @return new TH1 histogram.
   */
  TH1* cropHistogram(TH1 *hist, Int_t minBin, Int_t maxBin);

  /**
   * @brief Make 3D histogram stack.
   *
   * A list of TH1 histograms are aligned one after another in a 3D stack way
   *
   * @param histList TList of histograms.
   * @param axisMin minimum new axis number.
   * @param axisMax maximum new axis number.
   * @param name name of returned histogram
   * @return new TH2* histogram.
   */
   TH2* makeHistStack(TList* histList, Double_t axisMin = 0, Double_t axisMax = 1, const char* name="");
}

#endif
