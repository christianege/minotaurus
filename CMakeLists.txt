cmake_minimum_required(VERSION 2.6)

Project(minotaurus)

include_directories(  ${minotaurus_BINARY_DIR}/libscheduler )

add_subdirectory(libscheduler)
add_subdirectory(shutterc)
