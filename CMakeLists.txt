# Lachs Root CMakeLists file
# Tutorial see: https://doc.qt.io/qt-5/cmake-get-started.html

cmake_minimum_required(VERSION 3.1.0)

project(Lachs VERSION 1.0.0 LANGUAGES CXX)

add_subdirectory(src)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


