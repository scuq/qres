; qres.nsi
!include "MUI.nsh"
; -------------------------------
; Start
 
  !define company "AbyleDotOrg"
  !define icon "qres.ico"
  !define MUI_PRODUCT "qres"
  !define MUI_FILE "qres"
  !define MUI_VERSION "14.0112"
  !define MUI_BRANDINGTEXT "qres"
  CRCCheck On
  



; The name of the installer
Name "qres"

; The file to write
OutFile "qres-14.0901-x64-install.exe"

!define MUI_ICON "qres.ico"
!define MUI_UNICON "qres.ico"

; The default installation directory
InstallDir $PROGRAMFILES64\qres

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page directory
Page instfiles

;--------------------------------

; The stuff to install
Section "install" ;No components page, name is not important



  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File /r *.*

	;create desktop shortcut
	CreateShortCut "$DESKTOP\qres.lnk" "cmd.exe \k $INSTDIR\qres.exe" "" "$INSTDIR\qres.ico"
	
	
	 WriteUninstaller "$INSTDIR\Uninstall.exe"
	 
	 ;write uninstall information to the registry
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "DisplayName" "${MUI_PRODUCT} (remove only)"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}" "UninstallString" "$INSTDIR\Uninstall.exe"
  
SectionEnd ; end the section

;--------------------------------    
;Uninstaller Section  
Section "Uninstall"
 
;Delete Files 
  RMDir /r "$INSTDIR\*.*"    
 
;Remove the installation directory
  RMDir "$INSTDIR"
 
;Delete Start Menu Shortcuts
  Delete "$DESKTOP\qres.lnk"

 
;Delete Uninstaller And Unistall Registry Entries
  DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\${MUI_PRODUCT}"
  DeleteRegKey HKEY_LOCAL_MACHINE "SOFTWARE\Microsoft\Windows\CurrentVersion\Uninstall\${MUI_PRODUCT}"  
 
SectionEnd
