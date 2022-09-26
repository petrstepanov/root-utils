#ifndef StringUtils_hh
#define StringUtils_hh 1

#include <TList.h>
#include <TH1.h>

/** @struct EnergyValueUnit
 *  @brief Struct contains energy value (Double_t) with corresponding unit (TString)
 */
/** @var EnergyValueUnit::value
 *  Double value
 */
/** @var EnergyValueUnit::unit
 *  String unit
 */
struct EnergyValueUnit {
    Double_t value;
    TString unit;
};

/**
 * @namespace StringUtils
 * Useful string operations.
 */
namespace StringUtils {
  /**
   * @brief Remove extension from a file path.
   *
   * @param path File name or path.
   * @return File name or path without extension.
   */
  TString stripExtension(const char *path);

  /**
   * @brief Simple implementation of an ASCII progress bar.
   *
   * @param message String explaining what is happening.
   * @return nTimes How many times writeProgress will be called.
   */
  void writeProgress(const char *message, Int_t nTimes);

  /**
   * @brief Format energy to appropriate unit. Function outputs EnergyValueUnit structure containing energy value converted to the best unit for presenting - TeV, GeV, .. eV.
   *
   * @param value Energy value in default Geant4 unit - MeV.
   * @return EnergyValueUnit Structure containing value (double) and unit (std::string).
   */
  EnergyValueUnit formatEnergy(Double_t value);
}

#endif
