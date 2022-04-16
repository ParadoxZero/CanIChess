# Can I Chess?

| Windows | MacOS | Ubuntu |
| ------- | ----- | ------ |
| [![Windows](https://github.com/ParadoxZero/CanIChess/workflows/Windows/badge.svg)](https://github.com/ParadoxZero/CanIChess/actions/workflows/cmake-windows.yml) | [![MacOS](https://github.com/ParadoxZero/CanIChess/workflows/MacOS/badge.svg)](https://github.com/ParadoxZero/CanIChess/actions/workflows/cmake-macos.yml) | [![Ubuntu](https://github.com/ParadoxZero/CanIChess/workflows/Ubuntu/badge.svg)](https://github.com/ParadoxZero/CanIChess/actions/workflows/cmake-ubuntu.yml) |

A simple local chess game made using C++ and SFML

## Getting Started
This project uses CMake to generate the build file for the base system. The dependencies are added as git submodules. And integrated
into the CMakeLists.txt of the project. But since this uses git submodules, there is an additional step to clone the project.

### Cloning

```
	git clone --recurse-submodules https://github.com/ParadoxZero/CanIChess.git
```

Read more about submodules in this awesome gist - https://gist.github.com/gitaarik/8735255

### Compiling

#### If you are on linux
If you are on linux install the sfml dependencies before building via the following command -
```
	sudo apt-get install libpthread-stubs0-dev libgl1-mesa-dev libx11-dev libxrandr-dev libfreetype6-dev libglew1.5-dev libjpeg8-dev libsndfile1-dev libopenal-dev  libudev-dev
```

Please find the variation of this for whatever distro you are using.

#### Building for windows, linux and Mac

1. Use CMake to generate build files. (you can use your prefered build system instead of ninja by changing the -G option)
	```
	cmake -B out/build/ -G ninja
	cd out/build
	ninja CanIChess
	src\game.exe [or "game" in linux/mac]
	```
