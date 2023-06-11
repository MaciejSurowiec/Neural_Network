cmake_minimum_required(VERSION 3.24)
set (CMAKE_CXX_STANDARD 20)

project(neuronnet)

find_package(Qt6 REQUIRED COMPONENTS Widgets)
qt_standard_project_setup()

add_subdirectory(src)

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
