cmake_minimum_required(VERSION 3.13)

project("UDS Simulator")

include_directories(includes)
add_definitions(-std=c++11)
add_definitions(-Wall)
add_definitions(-
set(EXECUTABLE_OUTPUT_PATH "bin/")

set(INTERACTIVE_SRC "spike/InteractiveMain.cpp")
set(MAIN_SRC "spike/main.cpp")
file(GLOB_RECURSE COMMON_SOURCES "src/*.cpp")
#add_executable("UDS_Interacive" ${COMMON_SOURCES} ${INTERACTIVE_SRC})


file(GLOB SPIKES "spike/*.cpp")
foreach(SPIKE_PATH ${SPIKES})
    get_filename_component(SPIKE ${SPIKE_PATH} NAME_WE)
    message(STATUS "${SPIKE_PATH} ${SPIKE}")
    add_executable(${SPIKE} ${COMMON_SOURCES} ${SPIKE_PATH})
endforeach()


enable_testing()
#file(GLOB TESTS_SOURCES "tests/*.cpp")
set(TESTS_SOURCES "tests/test_converter.cpp")
foreach(TEST_PATH ${TESTS_SOURCES})
    get_filename_component(TEST ${TEST_PATH}  NAME_WE)
    add_executable(${TEST} ${COMMON_SOURCES} ${TEST_PATH})
endforeach()
