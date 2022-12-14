#include "./StringUtils.h"

#include <TSystem.h>
#include <TString.h>
#include <TObjString.h>
#include <TObjArray.h>
#include <TPRegexp.h>
#include <TROOT.h>

#include <iostream>
#include <ostream>

using namespace StringUtils;

TString StringUtils::stripExtension(const char *str) {
  TString s = str;
  Ssiz_t pos = s.Last('.');
  // If there is no extension - return filename itself
  if (pos < 0 || pos > s.Length()) {
    return s;
  }
  // If there is extension - trim string: https://root.cern.ch/root/html303/examples/tstring.C.html
  TString s2 = s(0, pos);
  return s2;
}

void StringUtils::writeProgress(const char *s, Int_t nTimes) {
  static Int_t counter = 0;
  Int_t progressPercent = ++counter * 100 / nTimes;

  // Flush cout
  // https://stackoverflow.com/questions/3057977/rewinding-stdcout-to-go-back-to-the-beginning-of-a-line
  std::cout << "\r" << s << ": " << progressPercent << "% (" << counter << "/" << nTimes << ") " << std::flush;
  if (counter == nTimes) {
    counter = 0;
    // writeRewindEnd();
    std::cout << ", done." << std::endl;
  }
}

EnergyValueUnit StringUtils::formatEnergy(Double_t value) {
  EnergyValueUnit evu;
  if (value >= 1E6) {
    evu.unit = "TeV";
    evu.value = value / 1E6;
    return evu;
  }
  if (value >= 1E3) {
    evu.unit = "GeV";
    evu.value = value / 1E3;
    return evu;
  }
  if (value >= 1) {
    evu.unit = "MeV";
    evu.value = value;
    return evu;
  }
  if (value >= 1E-3) {
    evu.unit = "keV";
    evu.value = value*1E3;
    return evu;
  }
  evu.unit = "eV";
  evu.value = value*1E6;
  return evu;
}

std::ostream &operator<<(std::ostream &os, EnergyValueUnit const &evu) {
    return os << evu.value << " " << evu.unit;
}

TString StringUtils::getSafeName(const char* name){
  TString newName = name;
  if (!gROOT->FindObject(name)) return newName;

  Int_t index=1;
  while (gROOT->FindObject(newName.Data())){
    newName = name;
    newName += index++;
  }
  return newName;
}
