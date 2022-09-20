#ifndef UiUtils_hh
#define UiUtils_hh 1

#include <TH1.h>
#include <TTree.h>
#include <TCanvas.h>

namespace UiUtils {

  void msgBoxInfo(const char *title, const char *text);

  // GUI specify a directory path
  TList* getFileNamesList(const char *text, Bool_t isMultiple);
}

#endif
