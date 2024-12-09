cmake_minimum_required(VERSION 3.20)

project(lab_4)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/Main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/AuxiliaryFunctions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/Model.cpp
)

set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/AuxiliaryFunctions.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Controller.h
    ${CMAKE_CURRENT_SOURCE_DIR}/Model.h
)

add_executable(main ${SOURCES} ${HEADERS})
set_property(TARGET main PROPERTY CXX_STANDARD 20)
target_compile_options(main PRIVATE -Wall -Wextra -Werror -Wpedantic)
