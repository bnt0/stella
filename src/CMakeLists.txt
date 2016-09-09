# stellad CMakeList file
# Required Cmake version
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall")

# Write binaries to bin/
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin/lib)

# Threads
find_package( Threads )

## Stellad
set(stellad_src 
    KeyHook.cc
    Dispatcher.cc
    MapModel.cc
    ModularDataModel.cc
    JSONFileModel.cc
    ShortcutDefinition.cc
    RobotCommon.cc
    PipeReader.cc
    protoc/command.pb.cc
    FUtils.cc)

add_library(Stella ${stellad_src})
target_link_libraries(Stella uiohook jsoncpp X11 Xtst protobuf)
target_link_libraries(Stella ${CMAKE_THREAD_LIBS_INIT} ) # Add threads to stella

add_executable(stellad Daemon.cc)
target_link_libraries(stellad Stella)
set_property(TARGET stellad PROPERTY CXX_STANDARD 11)
set_property(TARGET stellad PROPERTY CXX_STANDARD_REQUIRED ON)


## stella-config
add_executable(stella-config StellaControl.cc)
set_property(TARGET stella-config PROPERTY CXX_STANDARD 11)
set_property(TARGET stella-config PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(stella-config Stella)
target_link_libraries(stella-config protobuf)

## Install
install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stellad 
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stella-config DESTINATION bin)
