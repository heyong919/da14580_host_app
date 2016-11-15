cmake_minimum_required (VERSION 2.8.11)
project(da14580_host_app)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_C_FLAGS_DEBUG "$ENV{CFLAGS} -O0 -Wall -g -ggdb")
set(CMAKE_C_FLAGS_RELEASE "$ENV{CFLAGS} -O3 -Wall")

# -I"E:\workspace\da14580_host_app\src\inc" -I"D:\cygwin64\usr\include" -O0 -g3 -Wall -c -fmessage-length=0
aux_source_directory(. SRC_LIST)
include_directories("${CMAKE_SOURCE_DIR}/inc")
add_subdirectory(transport)
add_executable(host_app ${SRC_LIST})
target_link_libraries(host_app da_transport)
