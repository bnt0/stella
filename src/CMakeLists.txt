# stellad CMakeList file
# Required Cmake version
cmake_minimum_required(VERSION 3.1.0 FATAL_ERROR)

# Threads
find_package( Threads )

## Stellad
add_executable(stellad KeyHook.cc KeyHook.h Dispatcher.cc Dispatcher.h
MapModel.cc MapModel.h ModularDataModel.cc ModularDataModel.h
JSONFileModel.cc JSONFileModel.h
ShortcutDefinition.cc ShortcutDefinition.h
RobotCommon.cc RobotCommon.h VirtualTyperInterface.h PipeReader.cc
PipeReader.h protoc/command.pb.cc protoc/command.pb.h FUtils.cc FUtils.h)

# Compile for C++11 if req
target_compile_features(stellad PRIVATE cxx_range_for)
target_link_libraries(stellad uiohook jsoncpp X11 Xtst protobuf)
# Add threads to stellad
target_link_libraries(stellad ${CMAKE_THREAD_LIBS_INIT} )

## stella-config
add_executable(stella-config StellaControl.cc StellaControl.h
FUtils.cc FUtils.h
protoc/command.pb.cc protoc/command.pb.h)
target_compile_features(stella-config PRIVATE cxx_range_for)
target_link_libraries(stella-config protobuf)

## Install
install(PROGRAMS stellad stella-config DESTINATION bin)
