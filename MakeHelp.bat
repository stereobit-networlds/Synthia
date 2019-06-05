@echo off
REM -- First make map file from Microsoft Visual C++ generated resource.h
echo // MAKEHELP.BAT generated Help Map file.  Used by SYNTH.HPJ. >"hlp\SYNTH.hm"
echo. >>"hlp\SYNTH.hm"
echo // Commands (ID_* and IDM_*) >>"hlp\SYNTH.hm"
makehm ID_,HID_,0x10000 IDM_,HIDM_,0x10000 resource.h >>"hlp\SYNTH.hm"
echo. >>"hlp\SYNTH.hm"
echo // Prompts (IDP_*) >>"hlp\SYNTH.hm"
makehm IDP_,HIDP_,0x30000 resource.h >>"hlp\SYNTH.hm"
echo. >>"hlp\SYNTH.hm"
echo // Resources (IDR_*) >>"hlp\SYNTH.hm"
makehm IDR_,HIDR_,0x20000 resource.h >>"hlp\SYNTH.hm"
echo. >>"hlp\SYNTH.hm"
echo // Dialogs (IDD_*) >>"hlp\SYNTH.hm"
makehm IDD_,HIDD_,0x20000 resource.h >>"hlp\SYNTH.hm"
echo. >>"hlp\SYNTH.hm"
echo // Frame Controls (IDW_*) >>"hlp\SYNTH.hm"
makehm IDW_,HIDW_,0x50000 resource.h >>"hlp\SYNTH.hm"
REM -- Make help for Project SYNTH


echo Building Win32 Help files
start /wait hcrtf -x "hlp\SYNTH.hpj"
echo.
if exist Debug\nul copy "hlp\SYNTH.hlp" Debug
if exist Debug\nul copy "hlp\SYNTH.cnt" Debug
if exist Release\nul copy "hlp\SYNTH.hlp" Release
if exist Release\nul copy "hlp\SYNTH.cnt" Release
echo.


