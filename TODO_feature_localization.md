# TODO
## CMake
For all:
 - Add included directory (include/) to target Main

## Versioning.txt
 - Add update instructions (similar to steamworks)

## Research
 - Figure out if Linux and Mac require downloads
 
## BuildReleases.txt
For Windows:
 - Add instructions to copy libintl-8.dll and libiconv-2.dll to release directory

For All:
 - Add an instruction to generate translations, telling the reader to refer to Translations.md

## Licensing
 - Add gettext folder in docs/static/licenses
 - Add MIT license from https://github.com/mlocati/gettext-iconv-windows to above folder
 - Add lgpl license from https://www.gnu.org/licenses/lgpl-3.0.en.html to above folder
 - Add Readme.md (contents TBD)
 - Add Installation.md that explains how to install modified versions of the gettext library and details what methods we use.
 
## Translation
 - Add Translation.md to docs/static, containing instructions to generate and install translation .pot, .po, and .mo files
 - Make sure translation files store/present text with UTF-8 encoding.
 ? Add instructions for changing the encoding? (to be discussed, depending on difficulty of switching to UTF-8)
 - Find a way to access this directory from the executable for both development and release versions
 
## LoadGetText.h (gettext interface)
 - Create include directory in project root
 - Create include/LoadGetText.h, a cross-platform interface to work with gettext dynamic library
 - Add default functions in case dynamic loading fails
 - Test this interface on our 3 release OSs (Mac, Linux, Windows)
 - Create documentation for interface
 
## LoadGetText.md
 - Create docs/static/interfaces/LoadGetText.md
 - Document all functions, returns, and instructions for updating the interface.
 
## Main.cpp
 - Add sample test to display text in a few different languages, either in console or SFML window (preferred)
 - Output to console whether the dynamic library was loaded correctly or not.
