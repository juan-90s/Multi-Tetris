# Multi-Tetris
A simple Tetris game based on SDL2

Under Constructing ...

## Dependencies
Obviously, you need SDL2 and its extension SDL2_image, SDL2_ttf
### Mac OS
~~~shell
$ brew install sdl2
$ brew install sdl2_img
$ brew install sdl_ttf
$ brew install sdl2_mixer
$ brew install zlib
$ brew install libpng
~~~
### Linux
#### Ubuntu or Debain
~~~shell
$ sudo apt install libsdl2-dev libsdl2-image-dev libsdl2-ttf-dev libsdl2-mixer-dev
$ sudo apt install zlib1g libpng-dev
~~~

Download FindSDL cmake module from [aminosbh/sdl2-cmake-modules](https://github.com/aminosbh/sdl2-cmake-modules), move the cmake directory into $PROJECT_PATH/cmake/sdl2/ . Make sure the path is correct as CMAKE_MODULE_PATH in Cmakelist.

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
6. In Linker > SubSystem, select **Console**. If you don't need the terminal to observe debug output, then select **Windows**

Also remember to configurate other SDL2 extension as above.

## Credits
[SDL2](https://github.com/libsdl-org)

Amine B. Hassouna [@aminosbh](https://gitlab.com/aminosbh)