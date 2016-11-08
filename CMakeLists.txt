cmake_minimum_required (VERSION 2.8.11)
project(da14580_host_app)

# -I"E:\workspace\da14580_host_app\src\inc" -I"D:\cygwin64\usr\include" -O0 -g3 -Wall -c -fmessage-length=0
aux_source_directory(. SRC_LIST)
include_directories("${CMAKE_SOURCE_DIR}/inc")
add_subdirectory(transport)
add_executable(host_app ${SRC_LIST})
target_link_libraries(host_app da_transport)
