/** @brief Utility namespace for ROOT files

 Detailed description follows here.
 @author X. XYZ, DESY
 @date March 2008
 */

#ifndef FileUtils_hh
#define FileUtils_hh 1

#include <TList.h>
#include <TH1.h>
#include <TFile.h>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <vector>

namespace FileUtils {

  /**
   * @brief Obtain list of file paths in directory (with given extension).
   *
   * Function returns a TList* of TObjString* with full absolute paths of files in a given directory with given extension.
   *
   * @return TList* of TObjString* with full absolute paths.
   * @param dirPath Directory path.
   * @param extension Optional extension of files to find.
   */
  TList* findFilesInDirectory(const char *dirPath, const char *extension = 0);

  /**
   * @brief Open ROOT file with given absolute path.
   *
   * Function checks if a file is good and returns a pointer to a ROOT file TFile* with given absolute path.
   *
   * @return Pointer to TFile* object.
   * @param filePathName full ROOT file URI.
   */
  TFile* openFile(const char *filePathName);

  /**
   * @brief Parse absolute file path into path, name and extension.
   *
   * Function checks if file exists, if file is readable and parses path into a TList* containing corresponding path, name and extension.
   *
   * @return TList* of TObjString* objects with full absolute paths.
   * @param filePathName Directory path.
   * @param extension Optional extension of files to find.
   */
  //
  std::vector<TString> parseFilePath(const char *filePathName);

  TFile* openFile(const char *filePathName);

  TTree* getTree(TFile* file, const char *treeName);

  TBranch* getBranch(TTree* tree, const char *branchName);

  Double_t getBranchMinimum(TTree *tree, const char *branchName);

  Double_t getBranchMaximum(TTree *tree, const char *branchName);

//  TH1* getBranchHistogram(TBranch* branch, Int_t nBins);
}

#endif
