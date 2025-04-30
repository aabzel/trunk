message(STATUS "PROTOCOLS_MK_INC=${PROTOCOLS_MK_INC}")
if( NOT (PROTOCOLS_MK_INC STREQUAL Y))
    set(PROTOCOLS_MK_INC Y)

    set(PROTOCOLS_DIR ${CONNECTIVITY_DIR}/protocols)
    message(STATUS "+ Components")
    message(STATUS "PROTOCOLS_DIR=${PROTOCOLS_DIR}")

    target_include_directories(app PUBLIC ${PROTOCOLS_DIR})

    target_compile_definitions(app PUBLIC HAS_PROTOCOLS)

    include(${PROTOCOLS_DIR}/protocol/protocol.cmake)

    if (AT_COMMANDS STREQUAL Y)
        include(${PROTOCOLS_DIR}/at_commands/at_commands.cmake)
    endif()

    if (CLI STREQUAL Y)
        include(${PROTOCOLS_DIR}/cli_drv/cli_drv.cmake)
    endif()

    if (DECAWAVE STREQUAL Y)
        include(${PROTOCOLS_DIR}/decawave/decawave.cmake)
    endif()

    if (ISO_TP STREQUAL Y)
        include(${PROTOCOLS_DIR}/iso_tp/iso_tp.cmake)
    endif()

    if (DS_TWR STREQUAL Y)
        include(${PROTOCOLS_DIR}/ds_twr/ds_twr.cmake)
    endif()

    if (NMEA STREQUAL Y)
        include(${PROTOCOLS_DIR}/nmea_protocol/nmea_protocol.cmake)
    endif()

    if (RDS STREQUAL Y)
        include(${PROTOCOLS_DIR}/rds_protocol/rds_protocol.cmake)
    endif()

    if (RTCM3 STREQUAL Y)
        include(${PROTOCOLS_DIR}/rtcm3_protocol/rtcm3_protocol.cmake)
    endif()

    if (TBFP STREQUAL Y)
        include(${PROTOCOLS_DIR}/tbfp_protocol/tbfp_protocol.cmake)
    endif()

    if (UBX STREQUAL Y)
        include(${PROTOCOLS_DIR}/ubx_protocol/ubx_protocol.cmake)
    endif()

    if (UDS STREQUAL Y)
        include(${PROTOCOLS_DIR}/uds/uds.cmake)
    endif()
endif()
