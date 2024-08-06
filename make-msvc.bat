@echo off
setlocal

:: Compiler Options
set "CXX=cl"
set "CXXFLAGS=/W4 /EHsc /std:c++17"

:: Directories
set "SRC_DIR=.\src"
set "BIN_DIR=.\bin"

:: Repo Specific Stuff
set "TARGET=sourcesearch.exe"

:: List of source files
set "SRC_FILES=sourcesearch.cpp"

:: Ensure output directory exists
if not exist "%BIN_DIR%" mkdir "%BIN_DIR%"

:: Compile and link sources to create the final executable
echo Compiling and linking source files...
%CXX% %CXXFLAGS% /Fe"%BIN_DIR%\%TARGET%" %SRC_DIR%\%SRC_FILES%

:: Display completion message
echo Build complete. Output is located in %BIN_DIR%.

:: Clean build artifacts if requested
if "%1"=="clean" (
    echo Cleaning build artifacts...
    del /q "%BIN_DIR%\%TARGET%"
    echo Clean complete.
)

endlocal