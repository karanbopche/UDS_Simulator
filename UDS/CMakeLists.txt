
set(
    SOURCE_FILES
    UdsServices/Service10.c
    UdsServices/Service11.c
    UdsServices/Service22.c
    UdsServices/Service27.c
    UdsServices/Service28.c
    UdsServices/Service2E.c
    UdsServices/Service31.c
    UdsServices/Service34.c
    UdsServices/Service36.c
    UdsServices/Service37.c
    UdsServices/Service3E.c
    UdsServices/Service85.c
    UdsGateway.c
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
