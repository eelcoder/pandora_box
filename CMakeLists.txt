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

project(pandora)

enable_testing()

add_subdirectory(test) 