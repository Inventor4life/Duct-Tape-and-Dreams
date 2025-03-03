#3.28 needed for FetchContent (EXCLUDE_FROM_ALL)
cmake_minimum_required(VERSION 3.28)
project(DuctTapeandDreams LANGUAGES CXX)

####              ####
## PROJECT SETTINGS ##

set(SW_V 161) #SW_V: Steamworks Version
set(SW_HASH_EXPECTED "ddca256529c5dd0fefa9f8afbb0ab15f") #Expected Steamworks Hash, used to verify that the correct sdk is downloaded.
set(STEAM_APPID 3433930) #Duct Tape and Dreams App ID

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


#############
#include Steamworks SDK

#Validates steamworks ZIP installation, reinstalls if necessary
if(EXISTS "steamworks_sdk_${SW_V}.zip")
	file(MD5 "steamworks_sdk_${SW_V}.zip" SW_HASH)
endif()
if(NOT SW_HASH STREQUAL SW_HASH_EXPECTED)
	message(STATUS "Invalid steamworks SDK installed. Downloading new SDK...")
	file(
		DOWNLOAD "https://partner.steamgames.com/downloads/steamworks_sdk_${SW_V}.zip" "steamworks_sdk_${SW_V}.zip"
	)
endif()
file(MD5 "steamworks_sdk_${SW_V}.zip" SW_HASH)
if(NOT SW_HASH STREQUAL SW_HASH_EXPECTED)
	message(
		FATAL_ERROR 
		"FAILED Steamworks SDK download. Sign in to Steamworks and try again, or download steamworks_sdk_${SW_V}.zip from https://partner.steamgames.com/downloads/list into the /build/ folder"
	)
endif()

#Extract Steamworks ZIP to similarly named folder
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/steamworks_sdk_${SW_V}")
file(
	ARCHIVE_EXTRACT
	INPUT "steamworks_sdk_${SW_V}.zip"
	DESTINATION ${CMAKE_BINARY_DIR}/steamworks_sdk_${SW_V}
	)
file(REMOVE "steamworks_sdk_${SW_V}.zip") 

#include steamworks headers
target_include_directories(main PUBLIC ${CMAKE_BINARY_DIR}/steamworks_sdk_${SW_V}/sdk/public/)

#Find and link required libraries by platform
if(CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "This project is designed for 64-bit systems only.")
endif()

set(STEAM_LIBRARY_DIR "${CMAKE_BINARY_DIR}/steamworks_sdk_${SW_V}/sdk/redistributable_bin")

if(WIN32)
	target_link_libraries(main PUBLIC ${STEAM_LIBRARY_DIR}/win64/steam_api64.lib)
	file(INSTALL ${STEAM_LIBRARY_DIR}/win64/steam_api64.dll DESTINATION ${CMAKE_BINARY_DIR})
elseif(APPLE)
	target_link_libraries(main PUBLIC ${STEAM_LIBRARY_DIR}/osx/libsteam_api.dylib) #Untested
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	target_link_libraries(main PUBLIC ${STEAM_LIBRARY_DIR}/linux64/libsteam_api.so) #Untested
endif()

#Create steam_appid.txt, recommended for development only.
file(WRITE ${CMAKE_BINARY_DIR}/steam_appid.txt "${STEAM_APPID}")
########## END STEAMWORKS INSTALL

#TODO: #include sol3

#TODO: #include LuaJIT

#TODO: #include box2d