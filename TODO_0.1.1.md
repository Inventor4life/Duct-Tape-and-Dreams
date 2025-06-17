# TODO
## CMake
 - Update SFML to link dynamically. Our current setup links statically, and some of SFML's external libraries are incompatible with the SteamSDK.
 - Test find_package for major packages (luajit, SFML, box2d, sol2, etc...) and make sure they aren't being re-downloaded if a working copy already exists in /build/

## locale
 - test if gettext support is installed on mac/linux by default.
 - add basic locale support (should be super easy after linking to dynamic library)
 - research license requirements on whether gettext .dll can be shipped with our game, or if we need to make an end-customer install script.

## Other
 - Finish filling out docs/static/BuildingReleases.txt:
	-update Core requirements to include platform-agnostic files (E.g. licenses, assets, lua scripts...)
 - Design development workflow and document it in docs/static/workflow.txt
