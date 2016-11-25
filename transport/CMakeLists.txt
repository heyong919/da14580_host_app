cmake_minimum_required (VERSION 2.8.11)
aux_source_directory(. TANS_SRC)
add_library(da_transport ${TANS_SRC})
