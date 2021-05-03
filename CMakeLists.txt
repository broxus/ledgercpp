cmake_minimum_required(VERSION 3.16)
project(Ledger C CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(hidapi_name)
if (WIN32)
elseif (APPLE)
    set(hidapi_name hidapi)
elseif (UNIX AND NOT APPLE)
    set(hidapi_name hidapi-libusb)
endif()

find_package(PkgConfig REQUIRED)
pkg_check_modules(HIDAPI REQUIRED ${hidapi_name})

set(LEDGERCPP_SOURCE
        ledgercpp/comm.hpp
        ledgercpp/error.cpp
        ledgercpp/error.hpp
        ledgercpp/hid_device.cpp
        ledgercpp/hid_device.hpp
        ledgercpp/ledger.cpp
        ledgercpp/ledger.hpp
        ledgercpp/transport.cpp
        ledgercpp/transport.hpp
        ledgercpp/utils.cpp
        ledgercpp/utils.hpp
        )

add_library(ledgercpp ${LEDGERCPP_SOURCE})
add_library(ledgercpp::ledgercpp ALIAS ledgercpp)

target_include_directories(ledgercpp
        PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        )

file(GLOB_RECURSE EDV_INCLUDE_FILES "ledgercpp/*.hpp*")
set_target_properties(ledgercpp
        PROPERTIES
        PUBLIC_HEADER "${EDV_INCLUDE_FILES}"
        )

include(GNUInstallDirs)
install(TARGETS ledgercpp
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/ledgercpp
        )
