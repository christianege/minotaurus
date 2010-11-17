cmake_minimum_required(VERSION 2.6)

Project(librtc)

include_directories( 
		${CMAKE_CURRENT_SOURCE_DIR}/include 
		${minotaurus_SOURCE_DIR}/libtwi/include
) 
set(LIBRARY_OUTPUT_PATH ${minotaurus_BINARY_DIR}/../lib)

set ( SOURCES  
	src/ds1337.c
	src/date.c
)

add_library( rtc STATIC ${SOURCES} )
SET_TARGET_PROPERTIES(rtc PROPERTIES COMPILE_FLAGS "-DCONFIG_RTC_DS1337 -DCFG_I2C_RTC_ADDR=0x69")

