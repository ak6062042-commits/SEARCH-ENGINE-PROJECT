@echo off
REM ===============================
REM Mini Search Engine Build Script
REM ===============================

REM Project root path
set PROJECT_ROOT=C:/Users/Prime/Desktop/SEARCH ENGINE PROJECT

REM Create build directory if it doesn't exist
if not exist "%PROJECT_ROOT%/build" (
    mkdir "%PROJECT_ROOT%/build"
)

REM Compiler settings
set COMPILER=g++
set CFLAGS=-std=c++17 -Wall -Wextra -O2 -g
set INCLUDE=-I"%PROJECT_ROOT%/include"

REM ===============================
REM Compile each .cpp file to .o
REM ===============================

echo Compiling Utils.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/Utils.cpp" -o "%PROJECT_ROOT%/build/Utils.o"

echo Compiling DocumentStore.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/DocumentStore.cpp" -o "%PROJECT_ROOT%/build/DocumentStore.o"

echo Compiling InvertedIndex.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/InvertedIndex.cpp" -o "%PROJECT_ROOT%/build/InvertedIndex.o"

echo Compiling Trie.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/Trie.cpp" -o "%PROJECT_ROOT%/build/Trie.o"

echo Compiling QueryProcessor.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/QueryProcessor.cpp" -o "%PROJECT_ROOT%/build/QueryProcessor.o"

echo Compiling config_debug.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/config_debug.cpp" -o "%PROJECT_ROOT%/build/config_debug.o"

echo Compiling main.cpp...
%COMPILER% %CFLAGS% %INCLUDE% -c "%PROJECT_ROOT%/src/main.cpp" -o "%PROJECT_ROOT%/build/main.o"

REM ===============================
REM Link all object files to exe
REM ===============================

echo Linking object files...
%COMPILER% %CFLAGS% "%PROJECT_ROOT%/build/*.o" -o "%PROJECT_ROOT%/SearchEngine.exe"

echo ===============================
echo Build complete!
echo Output: %PROJECT_ROOT%/SearchEngine.exe
echo ===============================
pause
