cmake_minimum_required(VERSION 3.30)

project(practica_1_pvcxx VERSION 1.0 LANGUAGES CXX)

set(CMAKE_EXECUTABLE_SUFFIX ".html")

add_library(target_cxx_flags INTERFACE)
target_compile_features(target_cxx_flags INTERFACE cxx_std_23)

# Si find_package no encuentra SDL2, puede que emscripten no lo haya descargado,
# prueba a compilar un trabajo cualquiera de emscrpiten con "-s USE_SDL=2" para
# que lo descarge y así CMake pueda encontrarlo.
find_package(SDL2 CONFIG REQUIRED)

add_executable(practica_1_pvcxx
    main.cpp
    src/Juego.cpp
    src/Bola.cpp
    src/texturas.cpp
    src/Jugador.cpp
    src/WindowRenderer.cpp
)

target_link_libraries(practica_1_pvcxx PRIVATE ${SDL2_LIBRARIES})