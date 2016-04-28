gba700 - GBA cross-development toolchain for AG0700
Version 2013a
Adam Sampson <a.sampson@abertay.ac.uk>

This is a repackaged version of the GBA cross-development toolchain
from devkitPro, based on the GNU tools. See the devkitPro web site
for more information, source code, etc.
  http://devkitpro.org/
 
To build this, I unpacked the following archives.

From <http://sourceforge.net/projects/devkitpro/files/>:
  devkitARM_r41-win32.exe          into devkitPro\devkitARM 
  libgba-20090222.tar.bz2          into devkitPro\libgba
  msys-1.0.17.exe                  into devkitPro\msys
  gba-examples-20090222.tar.bz2    into devkitPro\examples\gba

From <http://sourceforge.net/projects/vba/files/>:
  VisualBoyAdvance-1.7.2.zip       into devkitPro\emuVBA

All of these tools are open source software, and can be freely used,
modified and redistributed.
  
You need to put this directory (gba700) in a location that starts with a
drive letter and doesn't contain any spaces (e.g. C:\gba700), then
edit the file devkitPro\msys\etc\fstab to say where it is, e.g.
  C:/gba700	/dev    (note that's a tab character in the middle, not spaces)
And edit RunMake.bat to set GBADIR to the same directory:
  set GBADIR=C:\gba700

To compile a GBA program, you can then use RunMake.bat, giving it
the directory containing the program as an argument.
For example, in Notepad++, you'd press F5 and use this command:
  C:\gba700\RunMake "$(CURRENT_DIRECTORY)" run
