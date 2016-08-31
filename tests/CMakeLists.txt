include_directories(${CMAKE_BINARY_DIR}/src)
set(testSources 
    testmapmodel.cc)
set(src 
    ../src/MapModel.h
    ../src/MapModel.cc
    ../src/ShortcutDefinition.h
    ../src/ShortcutDefinition.cc)
add_executable(tests ${testSources} ${src})

target_link_libraries(tests UnitTest++)

# Run tests automatically after build
add_custom_command(
    TARGET tests
    POST_BUILD
    COMMAND ./tests)
