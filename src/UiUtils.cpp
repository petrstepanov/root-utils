#include "./UiUtils.h"
#include "./HistUtils.h"

#include <TGMsgBox.h>
#include <TROOT.h>
#include <TText.h>
#include <TEnv.h>
#include <TSystem.h>
#include <TGFileDialog.h>
#include <TError.h>
#include <TObjString.h>

using namespace UiUtils;

void UiUtils::msgBoxInfo(const char *title, const char *text) {
  new TGMsgBox(gClient->GetRoot(), NULL, title, text, EMsgBoxIcon::kMBIconAsterisk, EMsgBoxButton::kMBOk);
}

TList* UiUtils::getFileNamesList(const char *text, Bool_t isMultiple) {
  // Show information message box
  if (strlen(text)) {
    msgBoxInfo("Open Files", text);
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
