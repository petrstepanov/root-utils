#ifndef StringUtils_hh
#define StringUtils_hh 1

#include <TList.h>
#include <TH1.h>

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

}

#endif
