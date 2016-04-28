@echo off
rem
rem Given a directory name, search for a Makefile and run devkitPro's make.
rem This is intended to be used from an editor like Notepad++.
rem
rem The first argument is the directory name.
rem Remaining arguments will be passed to make.
rem
rem For example:
rem   c:\gba700\RunMake.bat m:\myproject\source run
rem
rem Adam Sampson <a.sampson@abertay.ac.uk>

rem This should be the location of the gba700 directory:
set GBADIR=c:\gba700

set ROOTDEV=%GBADIR%\devkitPro
if EXIST %ROOTDEV% goto ok

cls
echo devkitPro isn't where I expected to find it:
echo   %ROOTDEV%
echo.
echo Check that you're using the right copy of RunMake.bat, and
echo that GBADIR is set correctly within it.
echo.
pause
exit 1

:ok

set PATH=%ROOTDEV%\devkitARM\bin;%ROOTDEV%\msys\bin;%ROOTDEV%\emuVBA;%PATH%
set DEVKITPRO=/dev/devkitPro
set DEVKITARM=%DEVKITPRO%/devkitARM

rem PUSHD works with UNC paths by allocating a temporary drive letter.
pushd %1
set TRIES=

:again

if EXIST Makefile goto found

cd ..

set TRIES=%TRIES%x
if NOT "%TRIES%" == "xxxxxxxxxx" goto again

cls
echo I couldn't find a Makefile in %1, or any of its parent folders.
echo.
pause
exit 1

:found

@echo on
make %2 %3 %4 %5 %6 %7 %8 %9
@echo off
popd
pause
