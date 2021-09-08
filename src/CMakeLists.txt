cmake_minimum_required(VERSION 3.1.0)

project(Lachs VERSION 1.0.0 LANGUAGES CXX)

add_executable(Lachs main.cpp)


# link qt
set(QT_BASE_DIR "E:/ArtifactCache/Qt/VS15_W64/5.9.1_p3/qtbase")
set(Qt5_DIR "${QT_BASE_DIR}/lib/cmake/Qt5")
find_package(Qt5 COMPONENTS Widgets REQUIRED)
target_link_libraries(Lachs Qt5::Widgets)


# copy qt dlls
message("Copy Qt d-DLLs..")
execute_process(COMMAND cmd /c utils\\2bks "xcopy ${QT_BASE_DIR}/lib/*d.dll ${CMAKE_BINARY_DIR}/Debug/" OUTPUT_VARIABLE xcopy_cmd)
execute_process(COMMAND cmd /c "${xcopy_cmd} /d")
execute_process(COMMAND cmd /c utils\\2bks "xcopy ${QT_BASE_DIR}/plugins/platforms/*d.dll ${CMAKE_BINARY_DIR}/Debug/platforms/" OUTPUT_VARIABLE xcopy_cmd)
execute_process(COMMAND cmd /c "${xcopy_cmd} /d")
message("done")
