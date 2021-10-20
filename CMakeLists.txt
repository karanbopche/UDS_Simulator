project("UDS Simulator")
include_directories(includes)
file(GLOB SOURCES "src/*.cpp")
add_executable("UDS_Sim" ${SOURCES})
