# TODO
## Versioning.txt
 - Add update instructions for gettext (for windows: Find suitable download URL for new version, update the expected hash and file name in cmake)

## Research
 - Figure out if Linux and Mac require gettext downloads, or if libintl (gettext) comes pre-installed.
 
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
 - add script to auto-compile translation .po files
 
## LoadGetText.h (gettext interface)
 - Create include directory in project root
 - Create include/LoadGetText.h, a cross-platform interface to work with the gettext dynamic library
 - Add default functions in case the gettext dynamic library fails to load.
 - Test the LoadGetText interface on our 3 release OSs (Mac, Linux, Windows)
 - Create documentation for interface (LoadGetText.md)
 
## LoadGetText.md
 - Create docs/static/interfaces/LoadGetText.md
 - Document all functions, returns, and instructions for updating the interface.
 
## Main.cpp
 - Add installation test to display text in a few different languages, either preferrably in console and SFML window.
 - Output to console whether the dynamic library was loaded correctly or not. This should be done in main, not LoadGetText
