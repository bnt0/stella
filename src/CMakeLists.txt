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
add_executable(stellad Daemon.cc)
target_link_libraries(stellad Stella)

target_compile_features(stellad PRIVATE cxx_range_for) # Compile for C++11 if req
target_link_libraries(stellad uiohook jsoncpp X11 Xtst protobuf)
target_link_libraries(stellad ${CMAKE_THREAD_LIBS_INIT} ) # Add threads to stellad

## stella-config
add_executable(stella-config StellaControl.cc)
target_link_libraries(stella-config Stella)

target_compile_features(stella-config PRIVATE cxx_range_for)
target_link_libraries(stella-config protobuf)

## Install
install(PROGRAMS ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stellad 
    ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/stella-config DESTINATION bin)
