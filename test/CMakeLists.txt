###
# pandora project
#
# Usage
#     - cmake .      : generate the makefile
#     - make         : builds pandora project.
#     - make test    : runs the unit tests
#
###

cmake_minimum_required(VERSION 3.0)

project(pandora_unit_tests)

set(testcases_SOURCE_FILES main.cpp gaussian_filter_tests.cpp)

source_group("testcases" FILES ${testcases_SOURCE_FILES})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y") 

## ----------------------------------------------------------------------------
## Targets
## ----------------------------------------------------------------------------
add_executable(pandora_unit_tests ${testcases_SOURCE_FILES})

target_include_directories(pandora_unit_tests PRIVATE . ..)

if (UNIX)
	target_link_libraries(pandora_unit_tests pthread)
endif()

## ----------------------------------------------------------------------------
## Tests
## ----------------------------------------------------------------------------
add_test(
	NAME pandora_unit_tests
	COMMAND $<TARGET_FILE:pandora_unit_tests> WORKING_DIRECTORY $<TARGET_FILE_DIR:pandora_unit_tests>)


