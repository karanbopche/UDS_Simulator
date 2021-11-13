cmake_minimum_required(VERSION 3.13)

project("UDS Simulator")

include_directories(includes)
add_definitions(-std=c++11)
add_definitions(-Wall)

set(EXECUTABLE_OUTPUT_PATH "bin/")
set(INTERACTIVE_SRC "spike/InteractiveMain.cpp")
set(MAIN_SRC "spike/main.cpp")
file(GLOB_RECURSE COMMON_SOURCES "src/*.cpp")
file(GLOB TESTS_SOURCES "tests/*.cpp")


add_executable("UDS_Interacive" ${COMMON_SOURCES} ${INTERACTIVE_SRC})

enable_testing()
add_executable(test1 ${COMMON_SOURCES} tests/test_converter.cpp)
set_target_properties(test1 PROPERTIES RUNTIME_OUTPUT_DIRECTORY bin)
add_test("TestConverter" test1 COMMAND test1)

