# Multi-Tetris
A simple Tetris game based on SDL2

Under Constructing ...

## Dependencies
Obviously, you need SDL2 and its extension. 
### Mac OS
~~~shell
$ brew install sdl2
$ brew install sdl2_img
$ brew install zlib
$ brew install libpng
~~~
### Linux
~~~shell
$ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-mixer-dev
$ sudo apt install zlib1g libpng-dev
~~~

## Build
You can use cmake on Mac and Linux to build Unix Excutable
~~~
$ chmod +x ./build.sh
$ ./build.sh
~~~

## Setup on Visual Studio
Download SDL2 release for VC from [SDL2 GitHub](https://github.com/libsdl-org/SDL/releases/tag/release-2.24.0)

You can easily setup the project on Visual Studio. 

1. Create a new project and import source code and assets
2. Navigate "Project" -> "Properties"
3. In C/C++ > General, add your SDL2/include directory into Additional Include Directories
4. In Linker > General, add your SDL2/lib/x86 or x64 into Additional Library Directories
5. In Linker > Input, edit Additional Dependencies, add SDL2.lib SDL2main.lib
6. Copy and Paste .dll files to the project directory

Also remember to configurate SDL2 extension as above.