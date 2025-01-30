# open_gl_renderer

A full-fledged OpenGL Renderer built as per the [https://learnopengl.com/Introduction](OpenGL Reference Book)

As is apparent from the CMakeLists.txt file, the codebase is written in C++ and uses the GLAD and GLFW headers to render graphics via the GPU.

This project is currently being written for Windows.

# Quick Setup

First, download and run the [msys2 Installer](https://www.msys2.org/docs/installer/).

After installation at the default location, run MSYS2 MINGW(32 || 64) based on your system architecture.

First, check for updates:

```
pacman -Syu
```

\
Now, you require the mingw toolchain to - in turn - install glad and GLFW libraries.
\
For 64-bit systems, run:

```
pacman -S mingw-w64-x86_64-toolchain
```

\
For 32-bit systems:

```
pacman -S mingw-w64-i686-toolchain
```

\
To install GLFW, open the relevant MSYS64 MINGW(32||64) terminal and run:

```
pacman -S mingw-w64-x86_64-glfw
```

..for 64-bit systems and...

```
pacman -S mingw-w64-i686-glfw
```

...for 32-bit systems.
\
GLAD needs to be built for your particular system. Luckily, GLAD Generator makes it very easy for us.

Go to [https://gen.glad.sh](GLAD Generator) and configure the following options:

- **API**: OpenGL
- **Profile**: Core
- **Version**: Minimum 3.3
- **Language**: C/C++

_Generate_ and download the zip file.

Extract the contents of the _include_ directory to _/msys64/mingw64/include_ directory and _/src/glad.c_ into _/msys64/mingw64/lib/_.

Make sure you have CMake installed and the CMake executable added to the System PATH.

Finally, clone the project and:

```
cd open_gl_renderer
```

There are 2 methods for building and executing the compiled program.

### Method 1: With CMake

Configure your CMakeLists.txt to point it toward the _/include/_ directory and the _/glad.c_ file in your installed _mingw64-toolchain_ location. The changes are pretty straight-forward.

To setup build configs, run:

```
mkdir build
cd build
cmake .. -G "MinGW Makefiles"
```

\
If you did everything correctly, you should receive a success message from CMake.

cd back into the main directory and run:

```
auto_build_cmake.bat
```

\
It's set up to call CMake and build the project with the relevant libraries and headers.
After a successful execution and closure of the program, it will always cd back into the main directory.

Alternatively, you can manually type:

```
cd build
cmake --build .
OpenGLApp.exe
```

to run the compiled program.
\

### Method 2: Without CMake (sadist version)

Assuming you have compiler paths (specifically g++) added to system PATH, run:

```
auto_build_wo_cmake.bat
```

If you really love pain, you can also build and run via:

```
g++ main.cpp C:/msys64/mingw64/lib/glad/glad.c -o OpenGLApp.exe -I"C:/msys64/mingw64/include" -L"C:/msys64/mingw64/lib" -lglfw3 -lopengl32 -lgdi32
```

## FAQ

### I opened this project in VSCode and there are red squiggles beneath the include header lines

    1. Stop using VSCode.
    2. Also, make sure you have installed the C/C++ Extension Pack and edited the C/C++ Edit Configuration file with include paths and compiler location in case it doesn't automatically detect it.

### What if I have LINUX?

Sorry. Nerds not allowed.
i use arch, btw

### I don't have a GPU. Can I still run this app😊😊?

Bruh💀💀
