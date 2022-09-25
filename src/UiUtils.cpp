#include "./UiUtils.h"
#include "./HistUtils.h"

//#include <TROOT.h>
//#include <TText.h>
//#include <TEnv.h>
#include <TApplication.h>
#include <TSystem.h>
#include <TGFileDialog.h>
#include <TError.h>
#include <TObjString.h>

using namespace UiUtils;

void UiUtils::showMessageBox(const char *text, const char *title, EMsgBoxIcon icon = EMsgBoxIcon::kMBIconAsterisk){
  if (strlen(title) == 0){
    title = gApplication->GetTitle();
  }
  new TGMsgBox(gClient->GetRoot(), NULL, title, text, icon, EMsgBoxButton::kMBOk);
}

TList* UiUtils::getFilePaths(Bool_t isMultiple, const char* message) {
  // Show information message box
  if (strlen(message)) {
    showMessageBox(message, "Open Files");
  }

  // Show file picker
  const char *filetypes[] = { "All files", "*", "ROOT files", "*.root", 0, 0 };
  TGFileInfo fi;
  fi.fFileTypes = filetypes;
  if (isMultiple)
    fi.SetMultipleSelection(kTRUE);

  // Usability: open the dialog in my home directory (if running on my laptop)
  char dir[] = "/home/petrstepanov/Yandex.Disk/20_Tanja_Horn/Data";
  if (!gSystem->AccessPathName(dir)) {
    // Not works wit old farm ROOT
    fi.SetIniDir(dir);
    // Crashes when debuging new root 6.24
    // fi.fIniDir = dir;
  }

  new TGFileDialog(gClient->GetRoot(), 0, kFDOpen, &fi);

  // If selected multiple files then output energy resolution plot
  if (fi.fMultipleSelection && fi.fFileNamesList) {
    TList *fileNamesList = new TList();
    for (TObject *obj : *(fi.fFileNamesList)) {
      if (!obj->InheritsFrom(TObjString::Class()))
        continue;
      TObjString *objString = (TObjString*) obj;
      TObjString *newObjString = new TObjString(objString->GetString().Data());
      fileNamesList->Add(newObjString);
    }
    fileNamesList->Sort(kSortAscending);
    Info("UiUtils::getFileNamesList()", "Selected %d files.", fileNamesList->GetSize());
    return fileNamesList;
  }

  // If one file is selected
  else if (fi.fFilename) {
    TList *fileNamesList = new TList();
    TObjString *fileName = new TObjString(fi.fFilename);
    fileNamesList->Add(fileName);
    Info("UiUtils::getFileNamesList()", "Selected 1 file.");
    fileNamesList->Print();
    return fileNamesList;
  }
  // If no files selected
  Info("UiUtils::getFileNamesList()", "No files selected.");
  return new TList();
}
