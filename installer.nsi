# Name of the installer
OutFile "sourcesearch_installer.exe"

# Directory to install to
InstallDir "$PROGRAMFILES\sourcesearch"

# Request application privileges for Windows Vista and later
RequestExecutionLevel user

# Default section
Section "MainSection" SEC01

  # Output path for the installer
  SetOutPath "$INSTDIR"

  # Files to install
  File "bin\*"

  # Create shortcuts in the Start Menu
  CreateDirectory "$SMPROGRAMS\sourcesearch"
  CreateShortCut "$SMPROGRAMS\sourcesearch\sourcesearch.lnk" "$INSTDIR\sourcesearch.exe"

  # Register the uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"
  
  # Add the install directory to the PATH environment variable
  Exec '"$SYSDIR\cmd.exe" /C setx PATH "$INSTDIR;%PATH%"'

SectionEnd

# Uninstall section
Section "Uninstall"

  # Remove shortcuts
  Delete "$SMPROGRAMS\sourcesearch\sourcesearch.lnk"

  # Remove files and directories
  Delete "$INSTDIR\sourcesearch.exe"
  RMDir "$INSTDIR"

  # Unregister the uninstaller
  Delete "$INSTDIR\Uninstall.exe"

  # Remove the install directory from the PATH environment variable
  Exec '"$SYSDIR\cmd.exe" /C setx PATH "%PATH:;$INSTDIR=%"'

  # Remove registry entries for uninstaller
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayName"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "UninstallString"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "InstallLocation"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayVersion"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "Publisher"

SectionEnd

# Function to register uninstaller info in the registry
Function RegisterUninstaller
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayName" "sourcesearch"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayVersion" "1.2.5.0"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "Publisher" "Daniel McGuire"
FunctionEnd
