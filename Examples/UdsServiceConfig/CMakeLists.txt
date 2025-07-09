set(
    UDS_CONFIG_SOURCE
    Service10_Config.c
    Service11_Config.c
    Service22_Config.c
    Service27_Config.c
    Service28_Config.c
    Service2E_Config.c
    Service31_Config.c
    Service34_Config.c
    Service36_Config.c
    Service37_Config.c
    Service3E_Config.c
    Service85_Config.c
    UdsConfig.cpp
)

add_library(
    UdsCfgLib
    STATIC
    ${UDS_CONFIG_SOURCE}
)

target_include_directories(
    UdsCfgLib
    PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

target_include_directories(
    UdsCfgLib
    PUBLIC
    ${CMAKE_SOURCE_DIR}/UDS
)
