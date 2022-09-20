#include "./FileUtils.h"
#include "./StringUtils.h"

#include <TSystem.h>
#include <TSystemDirectory.h>
//#include <TGClient.h>
#include <TObjString.h>
//#include <TUUID.h>
#include <TError.h>

// #include <TCanvas.h>

//#include <iostream>
//#include <iomanip>
//#include <fstream>

using namespace FileUtils;

// This function returns a list of filenames in directory with certain extension
TList* FileUtils::findFilesInDirectory(const char *dirPath, const char *extension) {
  // Create list of filenames to return
  TList *filePathNames = new TList();

  // Check directory exists
  TSystemDirectory *dir = new TSystemDirectory(dirPath, dirPath);
  if (!dir->IsDirectory()) {
    Error("FileUtils::getFilePathsInDirectory()", "\"%s\" is not a directory", dirPath);
    return filePathNames;
  }

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

TFile* FileUtils::openFile(const char *filePathName) {
  Info("FileUtils::openFile()", "Opening file \"%s\"...", filePathName);
  TFile *file = new TFile(filePathName);
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
  TBranch* branch = getBranch(tree, branchName);
  const char *leafName = branch->GetListOfLeaves()->At(0)->GetName();
  TString branchAndLeafName = TString::Format("%s/%s", branchName, leafName);
  return tree->GetMinimum(branchAndLeafName);
}

Double_t FileUtils::getBranchMaximum(TTree *tree, const char *branchName) {
  TBranch* branch = getBranch(tree, branchName);
  const char *leafName = branch->GetListOfLeaves()->At(0)->GetName();
  TString branchAndLeafName = TString::Format("%s/%s", branchName, leafName);
  return tree->GetMaximum(branchAndLeafName);
}

//TH1* getBranchHistogram(TTree *tree, const char *branchName, Int_t nBins) {
//  TString histogramName = "hist_";
//  histogramName += branch->GetName();
//  Double_t branchMinimum =
//branchMinimum = getBranchMinimum(TTree *tree, const char *branchName) {
//  TH1* hist = new TH1D("histogramName", "", )
//}

std::vector<TString> FileUtils::parseFilePath(const char *filePathName) {
  // Check file exists
  if (gSystem->AccessPathName(filePathName, EAccessMode::kFileExists)) {
    Error("FileUtils::parseFilePath()", "\"%s\" file does not exist", filePathName);
    exit(1);
  };

  std::vector<TString> vector;
  // Extract file path file path directory
  TString dirName = gSystem->DirName(filePathName);
  vector[0] = dirName;

  // Extract baseName
  TString baseName = gSystem->BaseName(filePathName);
  vector[1] = dirName;

  // Extract extension
  Ssiz_t pos = baseName.Last('.');
  if (pos < 0 || pos > baseName.Length()) {
    // If there is no extension
    vector[3] = baseName;
    vector[4] = TString("");
  } else {
    // If there is extension - trim string: https://root.cern.ch/root/html303/examples/tstring.C.html
    TString fileName = baseName(0, pos);
    TString extension = baseName(pos, fileName.Length() - 1);
    vector[3] = fileName;
    vector[4] = extension;
  }

  return vector;
}
