cmake_minimum_required(VERSION 3.30)

project(practica_1_pvcxx VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_library(target_cxx_flags INTERFACE)
target_compile_features(target_cxx_flags INTERFACE cxx_std_23)

add_executable(practica_1_pvcxx main.cpp src/texturas.cpp)

target_compile_options(practica_1_pvcxx PRIVATE -s USE_SDL=2)
