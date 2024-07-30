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
  File "bin\sourcesearch.exe"

  # Create shortcuts in the Start Menu
  CreateDirectory "$SMPROGRAMS\sourcesearch"
  CreateShortCut "$SMPROGRAMS\sourcesearch\sourcesearch.lnk" "$INSTDIR\sourcesearch.exe"

  # Register the uninstaller
  WriteUninstaller "$INSTDIR\Uninstall.exe"

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

  # Remove registry entries for uninstaller
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayName"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "UninstallString"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "InstallLocation"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayVersion"
  DeleteRegValue HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "Publisher"

SectionEnd

# Write registry entries for uninstaller
Function WriteUninstaller
  # Write uninstaller info to the registry
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayName" "sourcesearch"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "UninstallString" "$INSTDIR\Uninstall.exe"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "InstallLocation" "$INSTDIR"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "DisplayVersion" "$VERSION"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\sourcesearch" "Publisher" "YourCompany"

FunctionEnd
