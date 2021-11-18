# /src CMakeLists.txt

cmake_minimum_required(VERSION 3.1.0)

project(Lachs)


#
#	Enable Qt Auto Moc, Rcc and UIc
#

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
if(CMAKE_VERSION VERSION_LESS "3.7.0")
    set(CMAKE_INCLUDE_CURRENT_DIR ON)
endif()


#
#	Specify where Qt is installed
#

set(QT_BASE_DIR "E:/ArtifactCache/Qt/VS15_W64/5.9.1_p3/qtbase") # change this according to your local installation of Qt
set(Qt5Core_DIR "${QT_BASE_DIR}/lib/cmake/Qt5Core")
set(Qt5_DIR "${QT_BASE_DIR}/lib/cmake/Qt5")
set(QT_QMAKE_EXECUTABLE "${QT_BASE_DIR}/bin/qmake.exe")


#
#	Create Application
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
#	Find and link Qt Modules
#

find_package(Qt5 COMPONENTS Core Widgets REQUIRED)
target_link_libraries(${PROJECT_NAME} Qt5::Core Qt5::Widgets)


#
#	Manually copy Qt DLLs into binary directory (for now)
#	The dlls ending on *d.dll are usually for debug, the others for release. So they will be copied into the corresponding targets binary output directory
#	For operation on a system without MS Visual Studio you also need to copy some of VS's dlls
#	The 2bks tool is required to first convert all QT/CMAKE paths from slashes to backslashes to work on windows (unfortunately)
#

message("-- Copy Qt DLLs into Binary Directory")
# copy debug dlls
execute_process(COMMAND cmd /c utils\\2bks "xcopy ${QT_BASE_DIR}/lib/*d.dll ${CMAKE_BINARY_DIR}/Debug/" OUTPUT_VARIABLE xcopy_cmd) # convert commands '/' to '\'
execute_process(COMMAND cmd /c "${xcopy_cmd} /d /q")
execute_process(COMMAND cmd /c utils\\2bks "xcopy ${QT_BASE_DIR}/plugins/platforms/*d.dll ${CMAKE_BINARY_DIR}/Debug/platforms/" OUTPUT_VARIABLE xcopy_cmd)
execute_process(COMMAND cmd /c "${xcopy_cmd} /d /q")
# copy release dlls
execute_process(COMMAND cmd /c utils\\2bks "xcopy ${QT_BASE_DIR}/lib/*.dll ${CMAKE_BINARY_DIR}/Release/" OUTPUT_VARIABLE xcopy_cmd) # convert commands '/' to '\'
execute_process(COMMAND cmd /c "${xcopy_cmd} /d /q")
execute_process(COMMAND cmd /c utils\\2bks "xcopy ${QT_BASE_DIR}/plugins/platforms/*.dll ${CMAKE_BINARY_DIR}/Release/platforms/" OUTPUT_VARIABLE xcopy_cmd)
execute_process(COMMAND cmd /c "${xcopy_cmd} /d /q")
message("-- done")
