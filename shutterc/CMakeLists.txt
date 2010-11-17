cmake_minimum_required(VERSION 2.6)

set ( SOURCES 
       main.c
	   shutter.c
)

include_directories(${libscheduler_SOURCE_DIR} ${libuart_SOURCE_DIR} .)

LINK_DIRECTORIES(${minotaurus_BINARY_DIR}/../lib)
add_executable(shutterc  ${SOURCES})       
target_link_libraries(shutterc scheduler uart )

set(AVR_OBJ_COPY /usr/bin/avr-objcopy )
message(  ${CMAKE_PROJECT_NAME}  )

ADD_CUSTOM_COMMAND(
   OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/shutterc.hex
   COMMAND ${AVR_OBJ_COPY} -j .text -j .data -O ihex ${CMAKE_CURRENT_BINARY_DIR}/shutterc ${CMAKE_CURRENT_BINARY_DIR}/shutterc.hex 
   DEPENDS shutterc 
   )

ADD_CUSTOM_TARGET(intel_hex ALL DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/shutterc.hex )
