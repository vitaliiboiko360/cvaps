cmake_minimum_required(VERSION 2.8)


project( app1 )

set( OpenCV_DIR "../build" )
find_package( OpenCV REQUIRED )


include_directories( ${OpenCV_INCLUDE_DIRS} )


add_executable( app1 main.cpp )


target_link_libraries( app1 ${OpenCV_LIBS} )