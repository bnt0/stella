include_directories(${CMAKE_BINARY_DIR}/src)
set(testSources 
    testmapmodel.cc
    testjsonfilemodel.cc)

add_executable(tests ${testSources})
set_property(TARGET tests PROPERTY CXX_STANDARD 11)
set_property(TARGET tests PROPERTY CXX_STANDARD_REQUIRED ON)
target_link_libraries(tests UnitTest++)
target_link_libraries(tests Stella)

# Run tests automatically after build
add_custom_command(
    TARGET tests
    POST_BUILD
    COMMAND ./tests)
