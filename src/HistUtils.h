#ifndef HistUtils_hh
#define HistUtils_hh 1

#include <TH1.h>
#include <TList.h>
#include <TTree.h>

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
   */  TH1* cropHistogram(TH1 *hist, Int_t minBin, Int_t maxBin);
}

#endif
