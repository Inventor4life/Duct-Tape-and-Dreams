#3.28 needed for FetchContent (EXCLUDE_FROM_ALL)
cmake_minimum_required(VERSION 3.28)
project(DuctTapeandDreams LANGUAGES CXX)

##############################################################
# Include Required Packages:
#  := (NAME) [VERSION]  [:: Description (why do we use this package?)]
#  - SFML            3.0.0  :: Game Graphics
#  - Steamworks_SDK  1.62   :: Steam API, required to use Steam features
#  - LuaJIT          2.1    :: Run Lua for mods. LuaJIT preffered over Lua for performance
#  - Sol             3.5.0  :: Header Library for Lua, makes integrating Lua API easier
#  - box2d           3.0.0  :: Physics Engine - Required because... Physics?
##############################################################

####              #### Make sure to update package versions above when changing versions below.
## PROJECT SETTINGS ##

set(DTAD_BOX2D_VERSION "3.0.0")

set(DTAD_LUAJIT_VERSION "2.1")

set(DTAD_SOL_VERSION "3.5.0")

set(DTAD_SFML_VERSION "3.0.0") #Make sure to update LinuxDependencyInstaller.sh if needed. Last: 3.0.0

set(DTAD_SteamWorks_VERSION 162) #To update: set required version number, and updated expected MD5 hash. Last: 162
set(DTAD_SteamWorks_HASH_EXPECTED "048fc455d1725da6e25e2ffe4597fd23") #Expected Steamworks .zip MD5 Hash, used to verify that the correct sdk is downloaded.
set(DTAD_STEAM_APPID 3433930) #Duct Tape and Dreams App ID

# END PROJECT SETTINGS
######################


###### Project "Rules" (?) ###### (?): Not sure what to call these.
#                               #      

#Disallow in-source builds
if(NOT ${CMAKE_BINARY_DIR} STREQUAL ${CMAKE_SOURCE_DIR}/build)
	message(FATAL_ERROR "Please build into the /build/ directory at project root.")
endif()

#Keep downloaded packages separate from main script
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

#Create Target
add_executable(main src/main.cpp)
target_compile_features(main PRIVATE cxx_std_17) #Use C++17. C++ standards after 17 have not been tested.

#Sets main target as main project for Visual Studio
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT main)
#
####### END PROJECT RULES #######


##############################################################
# Include Required Packages (SEE TOP OF THIS FILE)
##############################################################

#############
#include SFML
#Note: On linux systems, SFML doesn't auto-install dependencies. Consider using the included
message(STATUS "Checking for SFML ${DTAD_SFML_VERSION} on local machine")
find_package(SFML ${DTAD_SFML_VERSION} COMPONENTS system window graphics audio)

if(NOT SFML_FOUND)
	message(STATUS "SFML not found, installing...")
	if(CMAKE_SYSTEM_NAME MATCHES "Linux")
		message(STATUS "Running on Linux Host. Consider running the LinuxDependencyInstaller.sh script if this fails.")
	endif()
	include(FetchContent)
	FetchContent_Declare(SFML
		GIT_REPOSITORY https://github.com/SFML/SFML.git
		GIT_TAG ${DTAD_SFML_VERSION}
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
if(EXISTS "steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip")
	file(MD5 "steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip" SW_HASH)
endif()
if(NOT SW_HASH STREQUAL DTAD_SteamWorks_HASH_EXPECTED)
	message(STATUS "Invalid steamworks SDK installed. Downloading new SDK...")
	file(
		DOWNLOAD "https://partner.steamgames.com/downloads/steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip" "steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip"
	)
endif()
file(MD5 "steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip" SW_HASH)
if(NOT SW_HASH STREQUAL DTAD_SteamWorks_HASH_EXPECTED)
	message(
		FATAL_ERROR 
		"FAILED Steamworks SDK download. Sign in to Steamworks and try again, or download steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip from https://partner.steamgames.com/downloads/list into the /build/ folder"
	)
endif()

#Extract Steamworks ZIP to similarly named folder
file(MAKE_DIRECTORY "${CMAKE_BINARY_DIR}/steamworks_sdk_${DTAD_SteamWorks_VERSION}")
file(
	ARCHIVE_EXTRACT
	INPUT "steamworks_sdk_${DTAD_SteamWorks_VERSION}.zip"
	DESTINATION ${CMAKE_BINARY_DIR}/steamworks_sdk_${DTAD_SteamWorks_VERSION}
	)

#include steamworks headers
target_include_directories(main PUBLIC ${CMAKE_BINARY_DIR}/steamworks_sdk_${DTAD_SteamWorks_VERSION}/sdk/public/)

#Find and link required libraries by platform
if(NOT (CMAKE_SIZEOF_VOID_P EQUAL 8)) #True if not on 64-bit system
    message(FATAL_ERROR "This project is designed for 64-bit systems only.")
endif()

set(STEAM_LIBRARY_DIR "${CMAKE_BINARY_DIR}/steamworks_sdk_${DTAD_SteamWorks_VERSION}/sdk/redistributable_bin")

if(WIN32)
	file(INSTALL ${STEAM_LIBRARY_DIR}/win64/steam_api64.dll DESTINATION ${CMAKE_BINARY_DIR})
	target_link_libraries(main PUBLIC ${STEAM_LIBRARY_DIR}/win64/steam_api64.lib)
elseif(APPLE)
	#TODO: Test this.
	file(INSTALL ${STEAM_LIBRARY_DIR}/osx/libsteam_api.dylib DESTINATION ${CMAKE_BINARY_DIR})
	target_link_libraries(main PUBLIC ${CMAKE_BINARY_DIR}/libsteam_api.dylib) 
	set_target_properties(main PROPERTIES INSTALL_RPATH "@loader_path/../") #Mac OS checks /build/bin for libsteam_api.dylib instead of /build (issue #11). This should fix it.
elseif(CMAKE_SYSTEM_NAME STREQUAL "Linux")
	file(INSTALL ${STEAM_LIBRARY_DIR}/linux64/libsteam_api.so DESTINATION ${CMAKE_BINARY_DIR})
	target_link_libraries(main PUBLIC ${CMAKE_BINARY_DIR}/libsteam_api.so)
endif()

#Create DTAD_STEAM_APPID.txt, recommended for development only.
file(WRITE ${CMAKE_BINARY_DIR}/steam_appid.txt "${DTAD_STEAM_APPID}")
########## END STEAMWORKS INSTALL


##########
#include Lua
# to install:
#  - sol2
#  - LuaJIT
#  - LuaJIT-cmake (used to implement LuaJIT, since LuaJIT doesn't have a cmake script

## Install Sol2 from https://github.com/ThePHD/sol2.git
message(STATUS "Checking for sol2 version ${DTAD_SOL_VERSION} on local machine...")
find_package(sol2 ${DTAD_SOL_VERSION})
if(NOT sol2_FOUND)
	message(STATUS "sol2 not found, installing...")
	include(FetchContent)
	FetchContent_Declare(sol2
		GIT_REPOSITORY https://github.com/ThePHD/sol2.git
		GIT_TAG v${DTAD_SOL_VERSION}
		GIT_SHALLOW ON
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(sol2)
	target_link_libraries(main PRIVATE sol2)
	
else()
	#not tested.
	message(STATUS "sol2 found. Linking...")
	target_link_libraries(main PRIVATE sol2)
	
endif()

#install LuaJIT from https://luajit.org/git/luajit.git
message(STATUS "Installing luajit v${DTAD_LUAJIT_VERSION}")
include(FetchContent)
FetchContent_Declare(LuaJITsource
	GIT_REPOSITORY https://luajit.org/git/luajit.git
	GIT_TAG v${DTAD_LUAJIT_VERSION}
	#GIT_SHALLOW ON luajit git server doesn't support GIT_SHALLOW
	EXCLUDE_FROM_ALL
	)
FetchContent_MakeAvailable(LuaJITsource)

#install luajit installer from https://github.com/zhaozg/luajit-cmake.git
message(STATUS "Installing luajit installer...")
set(LUAJIT_DIR ${luajitsource_SOURCE_DIR}) #Tells the luajit installer where to find luajit.
set(CMAKE_POLICY_DEFAULT_CMP0077 NEW) #Needed to prevent option() from clearing LUAJIT_DIR env above
include(FetchContent)
FetchContent_Declare(luajit
	GIT_REPOSITORY https://github.com/zhaozg/luajit-cmake.git
	GIT_SHALLOW ON
	EXCLUDE_FROM_ALL
	)
FetchContent_MakeAvailable(luajit)
target_link_libraries(main PRIVATE luajit::lib luajit::header)
target_include_directories(main PRIVATE ${luajit_BINARY_DIR}) # Needed to #include luajit.h
########## END LUA INSTALL

##########
#include box2d

## Install box2d from https://github.com/erincatto/box2d.git
message(STATUS "Checking for box2d version ${DTAD_BOX2D_VERSION} on local machine...")
find_package(box2d ${DTAD_BOX2D_VERSION})
if(NOT box2d_FOUND)
	message(STATUS "box2d not found, installing...")
	include(FetchContent)
	FetchContent_Declare(box2d
		GIT_REPOSITORY https://github.com/erincatto/box2d.git
		GIT_TAG v${DTAD_BOX2D_VERSION}
		GIT_SHALLOW ON
		EXCLUDE_FROM_ALL
	)
	FetchContent_MakeAvailable(box2d)
	target_link_libraries(main PRIVATE box2d)
	
else()
	#not tested.
	message(STATUS "box2d found. Linking...")
	target_link_libraries(main PRIVATE box2d)
	
endif()

########## END BOX2D INSTALL
