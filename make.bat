@echo off
setlocal

:: Compiler Options
set "CXX=cl"
set "CXXFLAGS=/W4 /EHsc /std:c++17 /nologo /MP"


if "%1"=="clean" (
    echo Cleaning build artifacts...
    del /q "%BIN_DIR%\%TARGET%"
    echo Clean complete.
    exit
)


:: Directories
set "SRC_DIR=.\src"
set "BIN_DIR=.\bin"

:: Repo Specific Stuff
set "TARGET=sourcesearch.exe"

:: List of source files
set "SRC_FILES=sourcesearch.cpp"

:: Ensure output directory exists
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

if "%1"=="full" (
    echo Cleaning build artifacts...
    del /q "%BIN_DIR%\%TARGET%"
)

:: Compile and link sources to create the final executable
echo Building Project...
%CXX% %CXXFLAGS% /Fe"%BIN_DIR%\%TARGET%" %SRC_DIR%\%SRC_FILES%
if "%1"=="run" (
    bin\sourcesearch --version
    exit
)
:: Display completion message
echo Build complete. Binarys are located in %BIN_DIR%.
echo This does not indicate success, as this message will always display.


endlocal
