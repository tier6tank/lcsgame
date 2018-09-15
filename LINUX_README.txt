================================================================================
                      Liberal Crime Squad Linux Notes
================================================================================
2004-06-16 - Kevin Sadler

Version 3.08 of Liberal Crime Squad (LCS) has been ported to Linux and compiled 
with the GNU g++ compiler (GCC 3.3.2) and linked with the ncurses library 
(rather than the pdcurses library used on the Windows version).


LCS on UNIX
===========

It is likely that this code will compile on other versions of UNIX, but this
has not been verified yet. Provided you have a g++ compiler and ncurses you
should be in with a fighting chance.


Build
=====

Unpack the tar archive into a suitable directory (e.g. /usr/local/src),
in the examples below assume nnn is the version number, eg 3.08:

  cd /usr/local/src
  tar -zxvf lcs_source_nnn.tgz 

  cd lcs_nnn
  
  make
  
This will compile the crimesquad executable. 


Installation
============

Currently the make file does not install LCS but it is very
simple.

LCS can be installed in two steps:

1. Copy the crimesquad executable to a suitable bin directory that is
   specified in PATH. If you have suitable permissions you may wish
   to copy it to /usr/local/bin, or to a bin directory in your home
   directory.

2. Install the art directory. The source directory has a subdirectory
   called art which contains some files used by the game. The game needs
   to know where these files are and will look in the following
   locations:
   
   /usr/share/lcs
   /usr/local/share/lcs
   
   To install the directory in /usr/local/share do the following:
   
   mkdir -p /usr/local/share/lcs
   cp -R art /usr/local/share/lcs/.
   
   Alternatively LCS will look for art in the current directory, or
   the environment variable LCS_ART_DIR may be set to the directory.
   An example of this using the bash shell:
   
   export LCS_ART_DIR=/usr/local/src/lcs_nnn/art
   
   Typically one would set this in .profile or .bashrc files.
  
Fonts
=====

LCS uses DOS CodePage 437 characters for it's graphics (the flag, the map,
and the newspaper headlines). Linux doesn't support this as is, however
you can download some fonts from Emil Mikulic's website that you can use:

http://dmr.ath.cx/misc/cp437/

http://dmr.ath.cx/misc/cp437/fonts.tar.bz2

It is suggested that they be installed to /usr/share/fonts/cp437

The following line should be added to /etc/X11/XF86Config:

    FontPath   "/usr/share/fonts/cp437"

To run crimesquad in an xterm with these fonts type:

xterm -fn cp437-8x12 -e crimesquad


Why are the fonts different?
----------------------------

In simple terms the graphics characters binary codes lie above the portable
ASCII values and the character set that you are using on Linux renders
this as a different "glyph" to that which appears under DOS using CP437.
The fonts are just a hack - they change the glyphs under Linux to look
like those under DOS.

The "proper" way to fix this is to use unicode, or UTF-8, and ncursesw 
(ncurses for wide characters) and remap the CP437 values to their UTF-8
values. This will mean that LCS could be played on Linux in your favourite
font. The downside, apart from the porting required, is that not all Linux
boxes may be configured with UTF-8 support or have the ncursesw library
installed, though most of the latest distros should be able to cope.


Save Files
==========

The Windows crimesquad save files (save.dat) are binary compatible with
Linux on ix86 (don't expect them to work on PowerPC (eg. Macs, RISC) due
to endianess).

Under Linux/UNIX LCS creates a sub-directory in the user's home directory
called .lcs in which the save.dat file is stored. To transfer your file
just create that directory:

	mkdir ~/.lcs

and copy the file into it.






