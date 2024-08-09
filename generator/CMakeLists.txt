cmake_minimum_required(VERSION 3.10)
project(generator)

set(CMAKE_CXX_STANDARD 11)

# Añadir todos los archivos fuente
set(SOURCES
        main.cpp
        sorter.cpp
)

# Crear el ejecutable
add_executable(generator ${SOURCES})