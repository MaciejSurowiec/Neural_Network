cmake_minimum_required(VERSION 3.24)
set (CMAKE_CXX_STANDARD 20)

project(neuralnetwork)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
if (NOT Qt6_FOUND)
    find_package(Qt5 5.15 REQUIRED COMPONENTS Widgets)
endif()

#qt_standard_project_setup()
set(CMAKE_AUTOMOC ON) 
set(CMAKE_AUTORCC ON) 
set(CMAKE_AUTOUIC ON)
add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)