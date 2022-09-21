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
   * Program exits if directory does not exist or not readable.
   *
   * @param dirPath Directory path.
   * @param extension Optional extension of files to find.
   * @return TList* of TObjString* with full absolute paths.
   */
  TList* findFilesInDirectory(const char *dirPath, const char *extension = 0);

  /**
   * @brief Open ROOT file with given absolute path.
   *
   * Function checks if a file is good and returns a pointer to a ROOT file TFile* with given absolute path.
   *
   * @param filePathName full ROOT file URI.
   * @return Pointer to TFile* object.
   */
  TFile* openFile(const char *filePathName);

  /**
   * @brief Parse absolute file path into path, name and extension.
   *
   * Function parses file path into components: path, basename, name, extension.
   *
   * @param filePathName absolute file path.
   * @return PathComponents struct with path components.
   */
  TTree* getTree(TFile* file, const char *treeName);

  TBranch* getBranch(TTree* tree, const char *branchName);

  Double_t getBranchMinimum(TTree *tree, const char *branchName);

  Double_t getBranchMaximum(TTree *tree, const char *branchName);

  Double_t getBranchMaximumInFiles(TList* files, const char* treeName, const char* branchName);

  /**
   * @brief Shortcut to get a histogram from ROOT tree branch.
   *
   * Function automatically determines histogram minimum and maximum.
   *
   * @param tree Pointer to the tree.
   * @param branchName branchName name of a branch.
   * @param nBins number of bins in the histogram. Default is 150.
   * @return TH1* pointer to the histogram.
   */
  TH1* getBranchHistogram(TTree *tree, const char *branchName, Int_t nBins=150);

  /** @struct PathComponents
   *  @brief This structure contains parsed file path components
   */
  /** @var PathComponents::path
   *  Member 'path' contains absolute file path
   */
  /** @var PathComponents::base
   *  Member 'base' contains filename with extension
   */
  /** @var PathComponents::name
   *  Member 'name' contains filename only
   */
  /** @var PathComponents::extension
   *  Member 'extension' contains extension
   */
  struct PathComponents {
      TString path;
      TString base;
      TString name;
      TString extension;
  };

  /**
   * @brief Parse absolute file path into path, name and extension.
   *
   * Function parses file path into components: path, basename, name, extension.
   *
   * @param filePathName absolute file path.
   * @return PathComponents struct with path components.
   */
  PathComponents parseFilePath(const char *filePathName);
}

#endif
