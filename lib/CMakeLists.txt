cmake_minimum_required(VERSION 3.26)
project(Projet_TP)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(Qt5  COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_library(lib1 jeu.cpp)
add_library(lib2 snakewindow.cpp)

#if the header in the inclide the directories will be wrtitten like this
target_include_directories(lib1 PUBLIC
        ${CMAKE_SOURCE_DIR}/include)
target_include_directories(lib2 PUBLIC
        ${CMAKE_SOURCE_DIR}/include
)

target_link_libraries(lib1
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)
target_link_libraries(lib2
        Qt5::Core
        Qt5::Gui
        Qt5::Widgets)
