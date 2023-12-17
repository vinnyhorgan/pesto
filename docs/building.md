# Building

The Pesto repository is supposed to be used for educational purposes, as such the building process is kept very straight-forward.
Keep in mind this is just for users who wish to tinker with the source code or help with development.
If you just want to use the framework download a binary from the [releases](https://github.com/vinnyhorgan/pesto/releases).

## Prerequisites

Before building Pesto, make sure you have the following installed:

- **Git**: This is the version control system used by Pesto, install it from the [official website](https://git-scm.com/).
- **CMake**: This is Pesto's build system, it allows the project to be built on many different configurations.
Install it from [here](https://cmake.org).
- **Compiler**: Make sure you have a c++ compiler on the system. For Windows, MSVC is suggested, get it by installing [Visual Studio](https://visualstudio.microsoft.com/).
On linux use g++, which you can install from the system package manager.

## Compiling

First of all clone the repository and its submodules with this command:

`git clone https://github.com/vinnyhorgan/pesto --recursive`

Then enter the cloned project and build it with CMake:

```
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

## Notes

On linux you may need to install some development libraries, if you are on Ubuntu or derivatives use this command:

`sudo apt install libasound2-dev libx11-dev libxrandr-dev libxi-dev libgl1-mesa-dev libglu1-mesa-dev libxcursor-dev libxinerama-dev`

You may also need to install Curl development libraries:

`sudo apt install libcurl4-gnutls-dev`
