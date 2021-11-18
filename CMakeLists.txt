# Lachs Root CMakeLists.txt
# Tutorial see: https://doc.qt.io/qt-5/cmake-get-started.html

cmake_minimum_required(VERSION 3.1.0)

project(Lachs VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_subdirectory(src)


