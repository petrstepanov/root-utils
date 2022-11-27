// My includes
#include "./FileUtils.h"

// ROOT includes
#include <TSystem.h>
#include <TSystemDirectory.h>
#include <TObjString.h>
#include <TError.h>

#include <TH1.h>
#include <TF1.h>
#include <TGraph.h>
#include <TMultiGraph.h>
#include <TSystem.h>

// STD includes
#include <vector>
#include <limits>
#include <iomanip>
#include <fstream>

using namespace FileUtils;

// This function returns a list of filenames in directory with certain extension
TList* FileUtils::findFilesInDirectory(const char *dirPath, const char *extension) {
  // Create list of filenames to return
  TList *filePathNames = new TList();

  // Check directory exists
  TSystemDirectory *dir = new TSystemDirectory(dirPath, dirPath);

  if (!dir->IsDirectory()) {
    Fatal("FileUtils::getFilePathsInDirectory()", "\"%s\" is not a directory", dirPath);
    exit(1);
  }

  // if (!gSystem->AccessPathName(dirPath, EAccessMode::kReadPermission)) {
  //   Fatal("FileUtils::getFilePathsInDirectory()", "\"%s\" directory is not readable", dirPath);
  //   exit(1);
  // }

  // Obtain list of files in the directory
  Info("FileUtils::getFilePathsInDirectory()", "Obtaining files list in \"%s\" folder... ", dirPath);
  TList *listOfFiles = dir->GetListOfFiles();
  listOfFiles->Sort();

  for (TObject *object : *listOfFiles) {
    // Ensure object is of correct type
    TSystemFile *file = (TSystemFile*) object;
    if (file == nullptr)
      continue;

    // Ensure resource is not a directory
    if (file->IsDirectory())
      continue;
    // Compose full absolute file path
    TString fileName = file->GetName();
    TString filePath = file->GetTitle();
    TString filePathName = gSystem->ConcatFileName(filePath.Data(), fileName.Data());

    // Ensure file has given extension
    if (extension != 0 && strlen(extension) > 0 && !fileName.EndsWith(extension))
      continue;

    // Ensure file is readable
    if (gSystem->AccessPathName(filePathName.Data(), EAccessMode::kReadPermission))
      continue;

    // Add file path to the list
    TObjString *objFilePathName = new TObjString(filePathName.Data());
    filePathNames->Add(objFilePathName);
  }
  Info("FileUtils::getFilePathsInDirectory()", "Found %d files with \"%s\" extension (%d total in directory).",
       filePathNames->GetSize(), extension, filePathNames->GetSize());
  return filePathNames;
}

TFile* FileUtils::openFile(const char *filePathName, Option_t *option) {
  Info("FileUtils::openFile()", "Opening file \"%s\"...", filePathName);
  TFile *file = new TFile(filePathName, option);
  if (file->IsZombie()) {
    file->Close();
    Fatal("FileUtils::openFile()", "File is corrupted. Aborting.");
    exit(1);
  }
  Info("FileUtils::openFile()", "File successfully opened.");
  return file;
}

TTree* FileUtils::getTree(TFile *file, const char *treeName) {
  TTree *tree = (TTree*) file->Get(treeName);
  if (!tree) {
    Error("FileUtils::getTree()", "Cannot find tree with name %s", treeName);
    exit(1);
  }
  return tree;
}

TBranch* FileUtils::getBranch(TTree *tree, const char *branchName) {
  TBranch *branch = (TBranch*) tree->FindBranch(branchName);
  if (!branch) {
    Error("FileUtils::getBranch()", "Cannot find branch with name %s", branchName);
    exit(1);
  }
  return branch;
}

Double_t FileUtils::getBranchMinimum(TTree *tree, const char *branchName) {
  TBranch *branch = getBranch(tree, branchName);
  const char *leafName = branch->GetListOfLeaves()->At(0)->GetName();
  TString branchAndLeafName = TString::Format("%s/%s", branchName, leafName);
  return tree->GetMinimum(branchAndLeafName);
}

Double_t FileUtils::getBranchMaximum(TTree *tree, const char *branchName) {
  TBranch *branch = getBranch(tree, branchName);
  const char *leafName = branch->GetListOfLeaves()->At(0)->GetName();
  TString branchAndLeafName = TString::Format("%s/%s", branchName, leafName);
  return tree->GetMaximum(branchAndLeafName);
}

PathComponents FileUtils::parseFilePath(const char *filePathName) {
  // Check file exists
  if (gSystem->AccessPathName(filePathName, EAccessMode::kFileExists)) {
    Error("FileUtils::parseFilePath()", "\"%s\" file does not exist", filePathName);
    exit(1);
  }
  ;

  PathComponents pt;
  // Extract file path file path directory
  TString dirName = gSystem->DirName(filePathName);
  pt.path = dirName;

  // Extract baseName
  TString baseName = gSystem->BaseName(filePathName);
  pt.base = baseName;

  // Extract extension
  Ssiz_t pos = baseName.Last('.');
  if (pos < 0 || pos > baseName.Length()) {
    // If there is no extension
    pt.name = baseName;
    pt.extension = TString("");
  } else {
    // If there is extension - trim string: https://root.cern.ch/root/html303/examples/tstring.C.html
    TString fileName = baseName(0, pos);
    TString extension = baseName(pos, fileName.Length() - 1);
    pt.name = fileName;
    pt.extension = extension;
  }

  return pt;
}

Double_t FileUtils::getBranchMinimumInFiles(TList *filePaths, const char *treeName, const char *branchName) {
  Double_t minimum = DBL_MAX;
  for (TObject *o : *filePaths) {
    // Get file name path
    TObjString *objString = (TObjString*) o;
    TString fileNamePath = objString->GetString();

    // Open ROOT file and get the tree
    TFile *file = openFile(fileNamePath.Data());
    TTree *tree = getTree(file, treeName);

    // Get branch maximum value
    Double_t branchMinimum = getBranchMinimum(tree, branchName);

    minimum = TMath::Min(minimum, branchMinimum);
  }
  return minimum;
}

Double_t FileUtils::getBranchMaximumInFiles(TList *filePaths, const char *treeName, const char *branchName) {
  Double_t maximum = DBL_MIN;
  for (TObject *o : *filePaths) {
    // Get file name path
    TObjString *objString = (TObjString*) o;
    TString fileNamePath = objString->GetString();

    // Open ROOT file and get the tree
    TFile *file = openFile(fileNamePath.Data());
    TTree *tree = getTree(file, treeName);

    // Get branch maximum value
    Double_t branchMaximum = getBranchMaximum(tree, branchName);

    maximum = TMath::Max(maximum, branchMaximum);
  }
  return maximum;
}

TH1* FileUtils::getBranchHistogram(TTree *tree, const char *branchName, Int_t nBins) {
  // Prepare histogram
  TString histogramName = TString::Format("%s-%s", tree->GetName(), branchName);
  Double_t branchMinimum = getBranchMinimum(tree, branchName);
  Double_t branchMaximum = getBranchMaximum(tree, branchName);
  TH1 *hist = new TH1D(histogramName, "", nBins, branchMinimum, branchMaximum);

  // Populate histogram with tree branch values
  TString drawOption = TString::Format("%s >> %s", branchName, histogramName.Data());
  tree->Draw(drawOption, "", "goff");

  return hist;
}

Int_t FileUtils::exportValuesToGnuplot(const char *filename, std::vector<std::string> colNames,
  std::vector<double> values, const char *delimeter) {
  std::ofstream myfile;
  Bool_t fileExisted = kFALSE;
  if (gSystem->AccessPathName(filename, EAccessMode::kFileExists)) {
    // File not exists
    myfile.open(filename);
  } else {
    // File exists
    myfile.open(filename, std::ios_base::app);
    fileExisted = kTRUE;
  }
  // Check file opened successfully
  if (!myfile.is_open()) {
    Error("exportPointToGnuplot()", "Cannot create \"%s\"", filename);
    return 1;
  }

  // Minimum  column width
  int minAsciiColWidth = 10;

  // Write header if file was not existing before
  if (!fileExisted) {
    myfile << "# ";
    for (std::string colName : colNames) {
      myfile << std::setw(std::max(minAsciiColWidth, (int) colName.length())) << std::left << colName << delimeter;
    }
  }

  // Write data
  myfile << std::endl;
  int i = 0;
  myfile << "  ";
  for (double value : values) {
    myfile << std::setw(std::max(minAsciiColWidth, (int) colNames[i++].length())) << std::left << value << delimeter;
  }

  myfile.close();
  return 0;
}

Int_t FileUtils::exportHistToGnuplot(TH1 *hist, const char *baseName, const char *delimeter) {
  TString fileName = TString::Format("%s-%s.dat", baseName, hist->GetName());

  // Delete existing file
  gSystem->Unlink(fileName.Data());

  // Create new file

  // Save single energy resolution point to ASCII
  std::string xLabel = strlen(hist->GetXaxis()->GetTitle()) > 0 ? hist->GetXaxis()->GetTitle() : "Bin center";
  std::string yLabel = strlen(hist->GetYaxis()->GetTitle()) > 0 ? hist->GetXaxis()->GetTitle() : "Bin content";
  for (Int_t i = 1; i <= hist->GetNbinsX(); i++) {
    std::vector<std::string> colNames = { xLabel, yLabel, "Error" };
    std::vector<double> values = { hist->GetBinCenter(i), hist->GetBinContent(i), hist->GetBinError(i) };
    FileUtils::exportValuesToGnuplot(fileName.Data(), colNames, values);
  }

  hist->GetListOfFunctions()->Print();

  // Export list of histogram functions
  for (TObject* object : *(hist->GetListOfFunctions())){
    if (!object->InheritsFrom(TF1::Class())) continue;
    TF1* func = (TF1*)object;
    TString baseName2 = TString::Format("%s-%s", baseName, hist->GetName());
    exportFuncToGnuplot(func, baseName2.Data());
  }

  // Success
  return 1;
}

Int_t FileUtils::exportFuncToGnuplot(TF1 *func, const char *baseName, const char *delimeter) {
  TString fileName = TString::Format("%s-%s.dat", baseName, func->GetName());

  // Delete existing file
  gSystem->Unlink(fileName.Data());

  // Create new file

  // Save single energy resolution point to ASCII
  std::string xLabel = strlen(func->GetXaxis()->GetTitle()) > 0 ? func->GetXaxis()->GetTitle() : "X";
  std::string yLabel = strlen(func->GetYaxis()->GetTitle()) > 0 ? func->GetXaxis()->GetTitle() : "Y";
  for (Int_t i = 0; i<=func->GetNpx(); i++) {
    Double_t x = func->GetXmin() + (func->GetXmax() - func->GetXmin()) / func->GetNpx() * i;
    Double_t y = func->Eval(x);
    std::vector<std::string> colNames = { xLabel, yLabel };
    std::vector<double> values = { x, y };
    FileUtils::exportValuesToGnuplot(fileName.Data(), colNames, values);
  }

  // Success
  return 1;
}

Int_t FileUtils::exportCanvasToGnuplot(TCanvas *canvas, const char *delimeter) {
  Int_t returnValue = 0;

  // Iterate and export all canvas primitives
  for (TObject *object : *(canvas->GetListOfPrimitives())) {
    if (TH1 *hist = dynamic_cast<TH1*>(object)) {
      // returnValue = returnValue && exportHistToGnuplot(hist, canvas->GetName(), delimeter);
      exportHistToGnuplot(hist, canvas->GetName(), delimeter);
    }
    if (TF1 *func = dynamic_cast<TF1*>(object)) {
      // returnValue = returnValue && exportFuncToGnuplot(func, canvas->GetName(), delimeter);
      exportFuncToGnuplot(func, canvas->GetName(), delimeter);
    }
    if (TGraph *graph = dynamic_cast<TGraph*>(object)) {
      // TODO: implement
    }
  }

  return returnValue;
}
