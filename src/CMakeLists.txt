# CMakeLists.txt
cmake_minimum_required(VERSION 3.1.0)

project(Lachs VERSION 0.0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#
#	enable Qt features
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

#
#	specify where Qt is installed
#

message("-- QT_BASE: ${QT_BASE}")
set(Qt5Core_DIR "${QT_BASE}/lib/cmake/Qt5Core")
set(Qt5_DIR "${QT_BASE}/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE "${QT_BASE}/bin/qmake.exe")

#
#	create executable
#

file(GLOB HEADER_FILES
	*.h
)
file(GLOB SOURCE_FILES
	*.cpp
)
add_executable(${PROJECT_NAME} 
	${HEADER_FILES}
	${SOURCE_FILES}
)

#
#	link libraries
#

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)
