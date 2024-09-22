
set(
    SOURCE_FILES
    # source files
    Gateway.cpp
)

add_library(
    UdsLib
    STATIC
    ${SOURCE_FILES}
)

target_include_directories(
    UdsLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)
