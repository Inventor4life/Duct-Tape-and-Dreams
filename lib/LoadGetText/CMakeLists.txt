# Creates the LoadGetText library
cmake_minimum_required(VERSION 3.10)

add_library(LoadGetText)

target_sources(LoadGetText 
	PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src/LoadGetText.cpp
			${CMAKE_CURRENT_LIST_DIR}/src/InternalLoadGetText.h
			${CMAKE_CURRENT_LIST_DIR}/include/LoadGetText.h
)

target_include_directories(LoadGetText 
	PRIVATE ${CMAKE_CURRENT_LIST_DIR}/src
	PUBLIC ${CMAKE_CURRENT_LIST_DIR}/include
)
