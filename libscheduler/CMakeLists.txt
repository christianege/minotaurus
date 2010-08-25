cmake_minimum_required(VERSION 2.6)

Project(libscheduler)

set(LIBRARY_OUTPUT_PATH ${minotaurus_BINARY_DIR}/../lib)

set ( SOURCES  
	getkey.c
	schedule.c
	tov0.c
	libscheduler.h
)

add_library( scheduler STATIC ${SOURCES} )
