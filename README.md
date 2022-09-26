ROOT Utils
==========

🏠️ Project homepage: https://petrstepanov.com/root-utils

🐱 Github repository: https://github.com/petrstepanov/root-utils

Shared library for ROOT framework containing list of common functions we use in multiple projects. Library is developed in order to reduce the codebase bloating of each particular ROOT-based program.

* **FileUtils** has shortcuts for opening series of ROOT files in a directory.
* **FitUtils** has implementation of a Crystal Ball function. Regular and reversed.
* **HistUtils** provides easy to access histogram operations: invert, crop etc...
* **StringUtils** will have common string operations: remove extension, print ASCII progress bar.
* **UiUtils** has a wrapper for the ROOT message box and file picker.

Below please find an exemple of fitting a histogram with the Crystal Ball function:

```
#include <FitUtils.h>
...

// Regular Crystal Ball function
TF1 *cBall = FitUtils::getCrystalBallFunction(hist);

// Reversed Crystal Ball function
TF1 *cBallReversed = FitUtils::getCrystalBallFunction(hist, kTRUE);

hist->Fit(cBall);
```

<p align="center">
  <img width="85%" src="https://raw.githubusercontent.com/petrstepanov/root-utils/master/resources/crystal-ball-fit.png" alt="Fitting ROOT histograms with Crystal Ball function" />
</p>

Library namespaces documentation can be found here: https://petrstepanov.com/root-utils/namespaces.html

Installation with CMake
-----------------------

This is the preferred installation option. Installation depends on prerequisites:
* Have `cmake` version 3.XX program installed on computer. Usually CMake is included in Linux "Development Tools" group package. On older distributions CMake v3.XX may be named `cmake3`.
* ROOT environment should be sourced in the current shell. Tested with ROOT v6.26.XX.

First we download the repository and create an out-of-source build folder.

```
mkdir -p ~/Downloads && cd ~/Downloads
git clone https://github.com/petrstepanov/root-utils
mkdir -p ./root-utils-build && cd ./root-utils-build
```

Next we invoke CMake. It ensures that all the dependencies are satisfied and generates GNU `Makefile`. Finally, we execute Makefile's `install` target:

```
cmake ../root-utils
cmake --build . --target install
```

Makefile generates dictionary, builds shared libaray, compiles code into object files, links the executable, and installs corresponding files files in required locations. 

**Tip**. If above command requires administrator privilleges that current user does not have, the install prefix can be changed to a local install:

```
cmake -DCMAKE_INSTALL_PREFIX=$HOME/.local ../root-utils
cmake --build . --target install
```

Additionally, `$PATH`, `$LD_LIBRARY_PATH`, and  `$CPLUS_INCLUDE_PATH` environemnt variables need to be modified for the library to be discoverable. Below please find an example how to do it in BASH and CSH shells:

### BASH Shell
```
echo "export PATH=$HOME/.local/bin:$PATH" >> $HOME/.bashrc
echo "export LD_LIBRARY_PATH=$HOME/.local/lib:$LD_LIBRARY_PATH" >> $HOME/.bashrc
echo "export CPLUS_INCLUDE_PATH=$HOME/.local/include:$CPLUS_INCLUDE_PATH" >> $HOME/.bashrc
```

### CSH-Based Shells
```
echo "setenv PATH $HOME/.local/bin:$PATH" >> $HOME/.cshrc
echo "setenv LD_LIBRARY_PATH $HOME/.local/lib:$LD_LIBRARY_PATH" >> $HOME/.cshrc
echo "setenv CPLUS_INCLUDE_PATH $HOME/.local/include:$CPLUS_INCLUDE_PATH" >> $HOME/.cshrc
```

This should do the trick.