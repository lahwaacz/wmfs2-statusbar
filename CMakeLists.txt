cmake_minimum_required(VERSION 2.6)

# define executable output directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
message(STATUS "Executable output directory: " ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}) 

# define default build type
if(NOT DEFINED CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE "Debug")
endif()
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")

project(wmfs2-statusbar)

set(wmfs2-statusbar_SOURCES
    src/main.cpp
    src/ConfigParser.cpp
    src/Xstatus.cpp
    src/PluginDate.cpp
    src/PluginMPD.cpp
    src/PluginRAM.cpp
    src/PluginCPU.cpp
    src/PluginNetwork.cpp
    src/PluginEssid.cpp
    src/PluginIP.cpp
    src/PluginBattery.cpp
    src/PluginVolume.cpp
    src/pulse.cpp
)
add_executable(wmfs2-statusbar ${wmfs2-statusbar_SOURCES})

find_package(PkgConfig)

pkg_check_modules(X11 REQUIRED x11)
pkg_check_modules(MPD REQUIRED libmpdclient)
pkg_check_modules(PULSE REQUIRED libpulse)
target_link_libraries(wmfs2-statusbar ${X11_LIBRARIES})
target_link_libraries(wmfs2-statusbar ${MPD_LIBRARIES})
target_link_libraries(wmfs2-statusbar ${PULSE_LIBRARIES})

set(CMAKE_CXX_FLAGS "-std=c++11 -lstdc++ -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -D DEBUG")

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    find_package(Boost 1.40 COMPONENTS timer system)
    if(Boost_FOUND)
        include_directories(${Boost_INCLUDE_DIR})
        target_link_libraries(wmfs2-statusbar ${Boost_LIBRARIES})
        add_definitions("-D WITH_BOOST")
    endif()
endif()

message(STATUS "Install prefix: " ${CMAKE_INSTALL_PREFIX})
INSTALL(TARGETS wmfs2-statusbar
    RUNTIME DESTINATION bin
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)
