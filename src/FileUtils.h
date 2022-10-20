#ifndef FileUtils_hh
#define FileUtils_hh 1

#include <TList.h>
#include <TH1.h>
#include <TFile.h>
#include <TString.h>
#include <TFile.h>
#include <TTree.h>
#include <TBranch.h>
#include <TCanvas.h>
#include <vector>

/** @struct PathComponents
 *  @brief Struct contains path components returned by the parseFilePath() method
 */
/** @var PathComponents::path
 *  Absolute path
 */
/** @var PathComponents::base
 *  Filename with extension
 */
/** @var PathComponents::name
 *  Filename only
 */
/** @var PathComponents::extension
 *  Extension
 */
struct PathComponents {
    TString path;
    TString base;
    TString name;
    TString extension;
};

/**
 * @namespace FileUtils
 * Contains useful functions for ROOT file manipulation.
 */

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
   * @param filePathName ROOT option "NEW", "RECREATE", "UPDATE", "READ".. (optional, default is "READ").
   * @return Pointer to TFile* object.
   */
  TFile* openFile(const char *filePathName, Option_t *option = "READ");

  /**
   * @brief Parse absolute file path into path, name and extension.
   *
   * Function parses file path into components: path, basename, name, extension.
   *
   * @param filePathName absolute file path.
   * @return PathComponents struct with path components.
   */
  TTree* getTree(TFile *file, const char *treeName);

  /**
   * @brief Safely get a branch from a ROOT tree.
   *
   * Function will stop program execution if the branch is not found.
   *
   * @param tree pointer to the TTree.
   * @return branchName name of the branch to be found.
   */
  TBranch* getBranch(TTree *tree, const char *branchName);

  /**
   * @brief Get minimum value in a tree branch.
   *
   * @param tree pointer to the TTree.
   * @return branchName name of the branch.
   */
  Double_t getBranchMinimum(TTree *tree, const char *branchName);

  /**
   * @brief Get maximum value in a tree branch.
   *
   * @param tree pointer to the TTree.
   * @return branchName name of the branch.
   */
  Double_t getBranchMaximum(TTree *tree, const char *branchName);

  /**
   * @brief Get minimum value in a tree branch across multiple files.
   *
   * Function is useful when simultaneously plotting a number of ROOT files with the same structure.
   *
   * @param filePaths list of filepaths to be opened (TObjStrings*).
   * @param treeName name of the tree in the ROOT file.
   * @return branchName name of the branch in the tree.
   */
  Double_t getBranchMinimumInFiles(TList *filePaths, const char *treeName, const char *branchName);

  /**
   * @brief Get maximum value in a tree branch across multiple files.
   *
   * Function is useful when simultaneously plotting a number of ROOT files with the same structure.
   *
   * @param filePaths list of filepaths to be opened (TObjStrings*).
   * @param treeName name of the tree in the ROOT file.
   * @return branchName name of the branch in the tree.
   */
  Double_t getBranchMaximumInFiles(TList *filePaths, const char *treeName, const char *branchName);

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
  TH1* getBranchHistogram(TTree *tree, const char *branchName, Int_t nBins = 150);

  /**
   * @brief Parse absolute file path into path, name and extension.
   *
   * Function parses file path into components: path, basename, name, extension.
   *
   * @param filePathName absolute file path.
   * @return PathComponents struct with path components.
   */
  PathComponents parseFilePath(const char *filePathName);

  /**
   * @brief Append or save data to a Gnuplot file.
   *
   * Function creates a new or opens existing ASCII file. Next, it appends a line of values to the file.
   *
   * @param filename absolute file path.
   * @param colNames vector of strings with column names.
   * @param colNames vector of doubles with row values.
   * @param delimeter column delimeter (default "   ").
   * @return 0 if success, 1 if error.
   */
  Int_t exportValuesToGnuplot(const char *filename, std::vector<std::string> colNames, std::vector<double> values,
    const char *delimeter = "   ");

  /**
   * @brief Export ROOT canvas to ASCII file with data columns.
   *
   * Function saves objects on Canvas - histograms, graph, function - to a text file ready to plot in Gnuplot.
   *
   * @param filename absolute file path.
   * @param canvas ROOT canvas to be saved.
   * @param delimeter column delimeter (default "   ").
   * @return 0 if success, 1 if error.
   */
  Int_t exportCanvasToGnuplot(TCanvas *canvas, const char *delimeter = "   ");

  Int_t exportHistToGnuplot(TH1 *hist, const char *canvasName, const char *delimeter = "   ");
  Int_t exportFuncToGnuplot(TF1 *hist, const char *canvasName, const char *delimeter = "   ");
}

#endif
