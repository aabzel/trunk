
message(STATUS "SPIFI_GENERAL_MK_INC=${SPIFI_GENERAL_MK_INC}")
if( NOT (Y STREQUAL SPIFI_GENERAL_MK_INC))
    set(SPIFI_GENERAL_MK_INC Y)
    message(STATUS "+ SPI General")

    set(SPIFI_GENERAL_DIR ${MCAL_COMMON_DIR}/spi)
    message(STATUS "SPIFI_GENERAL_DIR=${SPIFI_GENERAL_DIR}")

    add_compile_definitions(HAS_SPI)
    target_compile_definitions(app PUBLIC HAS_SPI)

    include_directories(${SPIFI_GENERAL_DIR})
    target_include_directories(app PUBLIC ${SPIFI_GENERAL_DIR})

    target_sources(app PRIVATE ${SPIFI_GENERAL_DIR}/spifi_general.c)
    target_sources(app PRIVATE ${SPIFI_GENERAL_DIR}/spifi_isr.c)

    if(DIAG STREQUAL Y)
        if(SPIFI_DIAG STREQUAL Y)
            message(STATUS "+ SPI diag")
            target_compile_definitions(app PUBLIC HAS_SPIFI_DIAG)
            target_sources(app PRIVATE ${SPIFI_GENERAL_DIR}/spifi_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SPIFI_COMMANDS STREQUAL Y)
            message(STATUS "+ SPI commands")
            target_compile_definitions(app PUBLIC HAS_SPIFI_COMMANDS)
            target_sources(app PRIVATE ${SPIFI_GENERAL_DIR}/spifi_commands.c)
        endif()
    endif()
endif()
