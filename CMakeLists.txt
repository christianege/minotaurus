cmake_minimum_required(VERSION 2.6)

Project(minotaurus)

include_directories(  
	${minotaurus_SOURCE_DIR}/libscheduler 
	${minotaurus_SOURCE_DIR}/libuart
	${minotaurus_SOURCE_DIR}/librtc/include
	${minotaurus_SOURCE_DIR}/libtwi/include
	)

add_subdirectory(libtwi)
add_subdirectory(librtc)
add_subdirectory(libscheduler)
add_subdirectory(libuart)
add_subdirectory(shutterc)
