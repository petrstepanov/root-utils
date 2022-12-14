#ifndef UiUtils_hh
#define UiUtils_hh 1

#include <TList.h>
#include <TGMsgBox.h>

/**
 * @namespace UiUtils
 * Various ROOT GUI shortcuts such as message box, file picker.
 */

namespace UiUtils {
  /**
   * @brief Displays ROOT message box with OK button.
   *
   * @param text Message box text.
   * @param title Optional message box text.
   * @param icon Optional message box icon.*
   * @return TList* of TObjString* with full absolute paths.
   */
  void showMessageBox(const char *text, const char *title = "", EMsgBoxIcon icon = EMsgBoxIcon::kMBIconAsterisk);

  /**
   * @brief Displays ROOT message question box with "Yes" and "No" buttons.
   *
   * @param text Message box text.
   * @param title Optional message box title.
   * @param icon Optional message box icon.*
   * @return Pressed button bit, EMsgBoxButton::kMBNo or EMsgBoxButton::kMBYes.
   */
  Int_t showMessageBoxYesNo(const char *text, const char *title = "", EMsgBoxIcon icon = EMsgBoxIcon::kMBIconQuestion);

  /**
   * @brief File picker dialog.
   *
   * Returns list of TObjStrings containing selected file paths.
   *
   * @param isMultiple Boolean value controls if file selection should be multiple.
   * @param title Optional message to be displayed in a Message Box prior to the file picker.
   * @return TList* of TObjString* with full absolute paths.
   */
  TList* getFilePaths(Bool_t isMultiple = kTRUE);
}

#endif
