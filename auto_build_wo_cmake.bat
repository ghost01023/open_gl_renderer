@echo off
REM build with G++ compiler

g++ main.cpp C:/msys64/mingw64/lib/glad/glad.c -o OpenGLApp.exe -I"C:/msys64/mingw64/include" -L"C:/msys64/mingw64/lib" -lglfw3 -lopengl32 -lgdi32
IF %ERRORLEVEL% NEQ 0 (
    echo Build failed!
    cd ..
    exit /b 1
)

REM Switch to build directory
cd build
IF %ERRORLEVEL% NEQ 0 (
    echo Build directory not found!
    exit /b 1
)

REM Execute build app
OpenGLApp.exe
IF %ERRORLEVEL% NEQ 0 (
    echo Execution failed!
    cd ..
    exit /b 1
)

REM Return to original directory
cd ..