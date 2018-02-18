cmake_minimum_required(VERSION 3.2)
project(learn_vidrone)

# default built type
IF(NOT CMAKE_BUILD_TYPE)
    SET(CMAKE_BUILD_TYPE Release)
ENDIF()

set(CMAKE_CXX_STANDARD 11)

find_package(OpenCV REQUIRED)
find_package(Qt5Gui)
find_package(Qt5Core)
find_package(Qt5Widgets)
find_package(Qt5Test)
find_package(Qt5Concurrent)
find_package(Qt5OpenGL)

set(SOURCE_FILES
        src/autopilot_interface.cpp
        include/autopilot_interface.h
        src/configParam.cpp
        include/configParam.h
        src/main.cpp
        src/mavlink_control.cpp
        include/mavlink_control.h
        src/serial_port.cpp
        include/serial_port.h
        src/camera_recorder.cpp
        include/camera_recorder.h
        src/log.cpp
        include/log.h
        src/imu_recorder.cpp
        include/imu_recorder.h src/stream.cpp include/stream.h)

add_subdirectory(cpr)
add_subdirectory(json)

include_directories(
        ${CMAKE_SOURCE_DIR}/mavlink/include/mavlink/v1.0
        ${CPR_INCLUDE_DIRS}
        ${CMAKE_SOURCE_DIR}/json/single_include/
)

add_executable(learn_vidrone ${SOURCE_FILES})

target_link_libraries(
        learn_vidrone
        pthread

        boost_system
        boost_thread
        boost_filesystem
        boost_date_time
        boost_chrono

        opencv_core
        opencv_highgui
        opencv_calib3d
        ${CMAKE_SOURCE_DIR}/json/single_include/
        ${CPR_LIBRARIES}
)