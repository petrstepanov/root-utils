# Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`namespace `[`FileUtils`](#namespaceFileUtils) | Utility namespace for ROOT files.
`namespace `[`FitUtils`](#namespaceFitUtils) | Utility namespace for ROOT files.
`namespace `[`HistUtils`](#namespaceHistUtils) | 
`namespace `[`StringUtils`](#namespaceStringUtils) | 
`namespace `[`UiUtils`](#namespaceUiUtils) | 

# namespace `FileUtils` 

Utility namespace for ROOT files.

Detailed description follows here. X. XYZ, DESY 

March 2008

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public TList * `[`findFilesInDirectory`](#namespaceFileUtils_1a96a2b93d8699379f78c048e90b4968c9)`(const char * dirPath,const char * extension)`            | Obtain list of file paths in directory (with given extension).
`public TFile * `[`openFile`](#namespaceFileUtils_1a34ac56b2e27b16a4f39c7562083f7967)`(const char * filePathName)`            | Open ROOT file with given absolute path.
`public TTree * `[`getTree`](#namespaceFileUtils_1a8c4d09cff14a6e8961c18e72b014d4dc)`(TFile * file,const char * treeName)`            | Parse absolute file path into path, name and extension.
`public TBranch * `[`getBranch`](#namespaceFileUtils_1a45e68df91807fe034fd708eb008cb7e4)`(TTree * tree,const char * branchName)`            | 
`public Double_t `[`getBranchMinimum`](#namespaceFileUtils_1a5c6c473991d4e7dbe20d50d0f8f5527d)`(TTree * tree,const char * branchName)`            | 
`public Double_t `[`getBranchMaximum`](#namespaceFileUtils_1a3178659d6557381e3ec5145dcf4c5c75)`(TTree * tree,const char * branchName)`            | 
`public Double_t `[`getBranchMaximumInFiles`](#namespaceFileUtils_1ad3eb992a1e5a43ff67c410394c2d0845)`(TList * files,const char * treeName,const char * branchName)`            | 
`public TH1 * `[`getBranchHistogram`](#namespaceFileUtils_1aa15e5724ad5a206fcf80a47ea94cb471)`(TTree * tree,const char * branchName,Int_t nBins)`            | Shortcut to get a histogram from ROOT tree branch.
`public `[`PathComponents`](#structFileUtils_1_1PathComponents)` `[`parseFilePath`](#namespaceFileUtils_1a6c7da44223cc4a1f99f2ec73a3d3c80f)`(const char * filePathName)`            | Parse absolute file path into path, name and extension.
`struct `[`FileUtils::PathComponents`](#structFileUtils_1_1PathComponents) | Struct contains path components parsed by the [parseFilePath()](#namespaceFileUtils_1a6c7da44223cc4a1f99f2ec73a3d3c80f)

## Members

#### `public TList * `[`findFilesInDirectory`](#namespaceFileUtils_1a96a2b93d8699379f78c048e90b4968c9)`(const char * dirPath,const char * extension)` 

Obtain list of file paths in directory (with given extension).

Function returns a TList* of TObjString* with full absolute paths of files in a given directory with given extension. Program exits if directory does not exist or not readable.

#### Parameters
* `dirPath` Directory path. 

* `extension` Optional extension of files to find. 

#### Returns
TList* of TObjString* with full absolute paths.

#### `public TFile * `[`openFile`](#namespaceFileUtils_1a34ac56b2e27b16a4f39c7562083f7967)`(const char * filePathName)` 

Open ROOT file with given absolute path.

Function checks if a file is good and returns a pointer to a ROOT file TFile* with given absolute path.

#### Parameters
* `filePathName` full ROOT file URI. 

#### Returns
Pointer to TFile* object.

#### `public TTree * `[`getTree`](#namespaceFileUtils_1a8c4d09cff14a6e8961c18e72b014d4dc)`(TFile * file,const char * treeName)` 

Parse absolute file path into path, name and extension.

Function parses file path into components: path, basename, name, extension.

#### Parameters
* `filePathName` absolute file path. 

#### Returns
[PathComponents](#structFileUtils_1_1PathComponents) struct with path components.

#### `public TBranch * `[`getBranch`](#namespaceFileUtils_1a45e68df91807fe034fd708eb008cb7e4)`(TTree * tree,const char * branchName)` 

#### `public Double_t `[`getBranchMinimum`](#namespaceFileUtils_1a5c6c473991d4e7dbe20d50d0f8f5527d)`(TTree * tree,const char * branchName)` 

#### `public Double_t `[`getBranchMaximum`](#namespaceFileUtils_1a3178659d6557381e3ec5145dcf4c5c75)`(TTree * tree,const char * branchName)` 

#### `public Double_t `[`getBranchMaximumInFiles`](#namespaceFileUtils_1ad3eb992a1e5a43ff67c410394c2d0845)`(TList * files,const char * treeName,const char * branchName)` 

#### `public TH1 * `[`getBranchHistogram`](#namespaceFileUtils_1aa15e5724ad5a206fcf80a47ea94cb471)`(TTree * tree,const char * branchName,Int_t nBins)` 

Shortcut to get a histogram from ROOT tree branch.

Function automatically determines histogram minimum and maximum.

#### Parameters
* `tree` Pointer to the tree. 

* `branchName` branchName name of a branch. 

* `nBins` number of bins in the histogram. Default is 150. 

#### Returns
TH1* pointer to the histogram.

#### `public `[`PathComponents`](#structFileUtils_1_1PathComponents)` `[`parseFilePath`](#namespaceFileUtils_1a6c7da44223cc4a1f99f2ec73a3d3c80f)`(const char * filePathName)` 

Parse absolute file path into path, name and extension.

Function parses file path into components: path, basename, name, extension.

#### Parameters
* `filePathName` absolute file path. 

#### Returns
[PathComponents](#structFileUtils_1_1PathComponents) struct with path components.

# struct `FileUtils::PathComponents` 

Struct contains path components parsed by the [parseFilePath()](#namespaceFileUtils_1a6c7da44223cc4a1f99f2ec73a3d3c80f)

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public TString `[`path`](#structFileUtils_1_1PathComponents_1a7aca5f41d470ef816c2d9c4862bf7d0a) | Member absolute file path
`public TString `[`base`](#structFileUtils_1_1PathComponents_1a3c7cb0f30b423ed8f85bac1cd020a79b) | Member filename with extension
`public TString `[`name`](#structFileUtils_1_1PathComponents_1a21eddcf7c60f5d124365481e5fc97780) | Member filename only
`public TString `[`extension`](#structFileUtils_1_1PathComponents_1ad83ab03d5481848e1fb98467713ee31d) | Member extension

## Members

#### `public TString `[`path`](#structFileUtils_1_1PathComponents_1a7aca5f41d470ef816c2d9c4862bf7d0a) 

Member absolute file path

#### `public TString `[`base`](#structFileUtils_1_1PathComponents_1a3c7cb0f30b423ed8f85bac1cd020a79b) 

Member filename with extension

#### `public TString `[`name`](#structFileUtils_1_1PathComponents_1a21eddcf7c60f5d124365481e5fc97780) 

Member filename only

#### `public TString `[`extension`](#structFileUtils_1_1PathComponents_1ad83ab03d5481848e1fb98467713ee31d) 

Member extension

# namespace `FitUtils` 

Utility namespace for ROOT files.

Detailed description follows here. X. XYZ, DESY 

March 2008

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public TF1 * `[`fitHistWithROOTCrystalBall`](#namespaceFitUtils_1afbac51c184fac0911488dd489fbd7250)`(TH1 * hist,Bool_t inverted)`            | 
`public TF1 * `[`getCrystalBallFunction`](#namespaceFitUtils_1a82ac01cf47da339477fa1dfa53d4df22)`(TH1 * hist,Bool_t reversed)`            | 
`class `[`FitUtils::CrystalBallFunctionObject`](#classFitUtils_1_1CrystalBallFunctionObject) | 

## Members

#### `public TF1 * `[`fitHistWithROOTCrystalBall`](#namespaceFitUtils_1afbac51c184fac0911488dd489fbd7250)`(TH1 * hist,Bool_t inverted)` 

#### `public TF1 * `[`getCrystalBallFunction`](#namespaceFitUtils_1a82ac01cf47da339477fa1dfa53d4df22)`(TH1 * hist,Bool_t reversed)` 

# class `FitUtils::CrystalBallFunctionObject` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public  `[`CrystalBallFunctionObject`](#classFitUtils_1_1CrystalBallFunctionObject_1a62e6f49f2f1e3954146e614d9243da31)`(Bool_t _isInverted)` | 
`public Double_t `[`operator()`](#classFitUtils_1_1CrystalBallFunctionObject_1a959e5bb14bd74fe547278b23c5ee4e10)`(double * _x,double * par)` | 

## Members

#### `public  `[`CrystalBallFunctionObject`](#classFitUtils_1_1CrystalBallFunctionObject_1a62e6f49f2f1e3954146e614d9243da31)`(Bool_t _isInverted)` 

#### `public Double_t `[`operator()`](#classFitUtils_1_1CrystalBallFunctionObject_1a959e5bb14bd74fe547278b23c5ee4e10)`(double * _x,double * par)` 

# namespace `HistUtils` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public Double_t `[`getMeanY`](#HistUtils_8h_1a0f27f40c41b52b247e12bc24aedc8b09)`(TH1 * hist)`            | 
`public TTree * `[`histsToTreeLin`](#HistUtils_8h_1a7a8faae65df61dc1820c1a1bef06b99a)`(TList * hists,const char * treeName,const char * treeTitle)`            | 
`public TTree * `[`histsToTree`](#HistUtils_8h_1a29f56b6f220137ec5b25b254bd4588fa)`(TList * hists,const char * treeName,const char * treeTitle)`            | 
`public TTree * `[`histsToTreeXY`](#HistUtils_8h_1a7aeb4b8ca3bd3a34da2bcae8675f386e)`(TList * hists,const char * treeName,const char * treeTitle)`            | 
`public void `[`invertHist`](#HistUtils_8h_1a17dac3a36429bbccbc9b7a67d8fb7ea6)`(TH1 * hist)`            | 
`public TH1 * `[`cropHistogram`](#HistUtils_8h_1a5ac85c46fa9ea77f1125c88e3ca21c77)`(TH1 * hist,Double_t minX,Double_t maxX)`            | 
`public TH1 * `[`cropHistogram`](#HistUtils_8h_1a453130b9506397da2e32a3c9932ef744)`(TH1 * hist,Int_t minBin,Int_t maxBin)`            | 

## Members

#### `public Double_t `[`getMeanY`](#HistUtils_8h_1a0f27f40c41b52b247e12bc24aedc8b09)`(TH1 * hist)` 

#### `public TTree * `[`histsToTreeLin`](#HistUtils_8h_1a7a8faae65df61dc1820c1a1bef06b99a)`(TList * hists,const char * treeName,const char * treeTitle)` 

#### `public TTree * `[`histsToTree`](#HistUtils_8h_1a29f56b6f220137ec5b25b254bd4588fa)`(TList * hists,const char * treeName,const char * treeTitle)` 

#### `public TTree * `[`histsToTreeXY`](#HistUtils_8h_1a7aeb4b8ca3bd3a34da2bcae8675f386e)`(TList * hists,const char * treeName,const char * treeTitle)` 

#### `public void `[`invertHist`](#HistUtils_8h_1a17dac3a36429bbccbc9b7a67d8fb7ea6)`(TH1 * hist)` 

#### `public TH1 * `[`cropHistogram`](#HistUtils_8h_1a5ac85c46fa9ea77f1125c88e3ca21c77)`(TH1 * hist,Double_t minX,Double_t maxX)` 

#### `public TH1 * `[`cropHistogram`](#HistUtils_8h_1a453130b9506397da2e32a3c9932ef744)`(TH1 * hist,Int_t minBin,Int_t maxBin)` 

# namespace `StringUtils` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public TString `[`stripExtension`](#StringUtils_8h_1ade13f67dae30a78599d8b42198def8bb)`(const char * str)`            | 
`public void `[`writeProgress`](#StringUtils_8h_1af410ca865b51dbb47e473da94d8412d6)`(const char * s,Int_t nTimes)`            | 

## Members

#### `public TString `[`stripExtension`](#StringUtils_8h_1ade13f67dae30a78599d8b42198def8bb)`(const char * str)` 

#### `public void `[`writeProgress`](#StringUtils_8h_1af410ca865b51dbb47e473da94d8412d6)`(const char * s,Int_t nTimes)` 

# namespace `UiUtils` 

## Summary

 Members                        | Descriptions                                
--------------------------------|---------------------------------------------
`public void `[`msgBoxInfo`](#UiUtils_8h_1ac45aa23c297b08ef04ab850c42dded4a)`(const char * title,const char * text)`            | 
`public TList * `[`getFileNamesList`](#UiUtils_8h_1a7b9a456d0fc715f9617fa47e78bcb067)`(const char * text,Bool_t isMultiple)`            | 

## Members

#### `public void `[`msgBoxInfo`](#UiUtils_8h_1ac45aa23c297b08ef04ab850c42dded4a)`(const char * title,const char * text)` 

#### `public TList * `[`getFileNamesList`](#UiUtils_8h_1a7b9a456d0fc715f9617fa47e78bcb067)`(const char * text,Bool_t isMultiple)` 

Generated by [Moxygen](https://sourcey.com/moxygen)