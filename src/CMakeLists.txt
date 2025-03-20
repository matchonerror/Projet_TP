cmake_minimum_required(VERSION 3.26)
project(Snake)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_AUTOMOC ON)

find_package(Qt5 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)


add_executable(my_app main.cpp)
target_link_libraries(my_app PRIVATE lib1 lib2)
target_include_directories(my_app PRIVATE ${CMAKE_SOURCE_DIR}/include)

add_custom_command(TARGET my_app POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${CMAKE_SOURCE_DIR}/data
        $<TARGET_FILE_DIR:my_app>/data
)
