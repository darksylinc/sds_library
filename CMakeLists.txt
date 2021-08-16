cmake_minimum_required( VERSION 3.10 )
project( sds_library )

include( CMake/Bootstrap.cmake )

include_directories( "${CMAKE_CURRENT_SOURCE_DIR}/include" )

add_recursive( ${CMAKE_CURRENT_SOURCE_DIR}/src SOURCES )
add_recursive( ${CMAKE_CURRENT_SOURCE_DIR}/include HEADERS )

add_library( ${PROJECT_NAME} ${SOURCES} ${HEADERS} )
