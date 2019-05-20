Cpp-OpenGLRenderer
==

Creating an OpenGl and C++ game rendered.

## Build instructions & concept provided by BennyQBD
- [BennyQBDGithub](https://github.com/BennyQBD)

## Build Dependencies ##
- [CMAKE](http://www.cmake.org/)
- [GLEW](http://glew.sourceforge.net/)
- [SDL2](http://www.libsdl.org/)
- [ASSIMP](http://assimp.sourceforge.net/)
- BUILD TOOLCHAIN (Can be any one of the following, doesn't need to be all of them)
	- WINDOWS
		- [Visual Studio](http://www.visualstudio.com/)

## Simple Build Instructions ##
### Windows ###
- Simply install windows visual studio 2017
- Open the .sln file
- Then run the program with or without the debugger

## Manual Build Instructions ##
### Windows/MinGW ###
- Make sure CMake is both installed and added to the system PATH.
- Open a Terminal and run:
```Shell
# install dependencies
# Install GLEW in %PROGRAMFILES%/GLEW or SET %GLEW_ROOT_DIR% to where GLEW is on your machine (Example: D:\PATH_TO_GLEW)
# Install SDL2 in %PROGRAMFILES%/SDL2 or SET %SDL2_ROOT_DIR% to where SDL2 is on your machine (Example: D:\PATH_TO_SDL2)
# Install ASSIMP in %PROGRAMFILES%/ASSIMP or SET %ASSIMP_ROOT_DIR% to where ASSIMP is on your machine (Example: D:\PATH_TO_ASSIMP)
# BTW VS 10 is VS 2010, VS 11 is VS 2012 and VS 12 is VS 2013, BLAME MicroSoft for the naming! LOL! 
# open the generated SLN file and build!
```
- Copy the DLLs in /Libraries/{Libary}/_bin/ to /Debug/ and /Release/
- In Visual Studio, set the Startup project to 3DEngineCpp
- Move the res folder into the build folder
- Run

## Additional Credits ##
- Etay Meiri, for http://ogldev.atspace.co.uk/ which inspired the base code for this repository.
- Everyone who's created or contributed to issues and pull requests, which make the project better!
