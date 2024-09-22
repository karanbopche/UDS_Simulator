enable_testing()

set(
    EMULATOR_SOURCE
    emulator.cpp
)

add_executable(
    UDS_Emulator
    ${EMULATOR_SOURCE}
)

target_link_libraries(
    UDS_Emulator
    UdsLib
)

target_include_directories(
    UDS_Emulator
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
