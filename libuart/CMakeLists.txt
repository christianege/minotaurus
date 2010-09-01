cmake_minimum_required(VERSION 2.6)

Project(libuart)

set(LIBRARY_OUTPUT_PATH ${minotaurus_BINARY_DIR}/../lib)

set ( SOURCES  
	uart.c
	libuart.h
)

add_library( uart STATIC ${SOURCES} )
