#3.28 needed for FetchContent (EXCLUDE_FROM_ALL)
cmake_minimum_required(VERSION 3.28)
project(DuctTapeandDreams LANGUAGES CXX)

####              ####
## PROJECT SETTINGS ##

# END PROJECT SETTINGS
######################


###### Project "Rules" (?) ###### (?): Not sure what to call these.
#                               #      

#Disallow in-source builds
if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR}/build)
	message(FATAL_ERROR "In-source builds not allowed. Please create a build directory and run 'cmake ..' from there.")
endif()

#Keep downloaded packages separate from main script
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Create Target
add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_17) #Use C++17

#Sets main target as main project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
#
####### END PROJECT RULES #######


##############################################################
# Include Required Packages:
#  := (NAME) [VERSION]  [:: Description (why do we use this package?)]
#  - SFML 3.0            :: Game Graphics
#  - Steamworks_SDK 1.61 :: Steam API, required to use Steam features
#  - LuaJIT              :: Run Lua for mods. LuaJIT preffered over Lua for performance
#  - Sol 3               :: Header Library for Lua, makes integrating Lua API easier
#  - box2d               :: Physics Engine - Required because... Physics?
#  - FMOD Studio         :: Audio Engine - Not Tested, maybe not even needed. Could be replaced easily
##############################################################

#############
#include SFML
#Note: On linux systems, SFML doesn't auto-install dependencies. Consider using the included
# LinuxDependencyInstaller.sh ## DependencyInstaller untested...
message(STATUS "Checking for SFML 3.0 on local machine")
find_package(SFML 3.0 COMPONENTS system window graphics audio)

if(NOT SFML_FOUND)
	message(STATUS "SFML not found, installing...")
	if(CMAKE_SYSTEM_NAME MATCHES "Linux")
		message(STATUS "Running on Linux Host. Consider running the LinuxDependencyInstaller.sh script if this fails.")
	endif()
	include(FetchContent)
	FetchContent_Declare(SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG 3.0.0
		GIT_SHALLOW ON
		EXCLUDE_FROM_ALL
		SYSTEM)
	FetchContent_MakeAvailable(SFML)
	target_link_libraries(main PRIVATE SFML::Graphics)
else()
	#not tested.
	message(STATUS "SFML found. Linking...")
	target_link_libraries(main PRIVATE sfml-graphics sfml-system sfml-window sfml-audio)
endif()
############# END SFML INSTALL
