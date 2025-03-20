cmake_minimum_required(VERSION 3.30)
project(Projet_TP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_subdirectory(lib)
add_subdirectory(src)