cmake_minimum_required (VERSION 3.4)

project (AsterRenderer)

set (Test_VERSION_MAJOR 1)
set (Test_VERSION_MINOR 0)


link_directories(./lib)

aux_source_directory(./ SRC_DIR)

add_executable(AsterRenderer ${SRC_DIR})

