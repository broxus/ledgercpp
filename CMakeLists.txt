cmake_minimum_required(VERSION 3.16)
project(Ledger C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(UDEV REQUIRED libudev)
pkg_check_modules(USB-1.0 REQUIRED libusb-1.0)

set(LEDGERCPP_SOURCE
        ledgercpp/error.cpp
        ledgercpp/hid_device.cpp
        ledgercpp/ledger.cpp
        ledgercpp/transport.cpp
        ledgercpp/utils.cpp
        ledgercpp/hidapi/hid.c

        ledgercpp/comm.hpp
        ledgercpp/error.hpp
        ledgercpp/hid_device.hpp
        ledgercpp/ledger.hpp
        ledgercpp/transport.hpp
        ledgercpp/utils.hpp
        ledgercpp/hidapi/hidapi.h
        )

add_library(ledgercpp ${LEDGERCPP_SOURCE})
add_library(ledgercpp::ledgercpp ALIAS ledgercpp)

target_include_directories(ledgercpp
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )

target_link_libraries(ledgercpp PULIC
        ${UDEV_LIBRARIES}
        ${USB-1.0_LIBRARIES}
        )
