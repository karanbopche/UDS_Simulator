cmake_minimum_required(VERSION 3.13)

project("UDS Simulator")
include_directories(includes)
file(GLOB SOURCES "src/*.cpp")
add_executable("UDS_Sim" ${SOURCES})
