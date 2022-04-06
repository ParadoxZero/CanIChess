# Can I Chess?
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
	```
2. Change to the build dir
	```
	cd out/build
	```
3. Build 
	```
	ninja CanIChess
	```
4. Run
	```
	src\CanIChess.exe
	```
