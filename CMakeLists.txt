cmake_minimum_required(VERSION 3.13)

project("UDS Simulator")

include_directories(includes)
add_definitions(-std=c++11)
add_definitions(-Wall)
add_definitions(-Wextra)

set(EXECUTABLE_OUTPUT_PATH "bin/")
set(INTERACTIVE_SRC "spike/InteractiveMain.cpp")
set(MAIN_SRC "spike/main.cpp")
file(GLOB_RECURSE COMMON_SOURCES "src/*.cpp")
file(GLOB TESTS_SOURCES "tests/*.cpp")


# foreach(test IN LISTS TESTS_SOURCES)
#     add_executable("test" ${COMMON_SOURCES} ${test} "tests/testFramework/TestCase.cpp")
# endforeach()


add_executable("UDS_Interacive" ${COMMON_SOURCES} ${INTERACTIVE_SRC})

