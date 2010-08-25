cmake_minimum_required(VERSION 2.6)

Project(shutterc)


set ( SOURCES 
       main.c
)

include_directories(${libscheduler_SOURCE_DIR})

LINK_DIRECTORIES(${minotaurus_BINARY_DIR}/../lib)


add_executable(shutterc  ${SOURCES})       
target_link_libraries(shutterc scheduler )
