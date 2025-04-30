
message(STATUS "SPI_GENERAL_MK_INC=${SPI_GENERAL_MK_INC}")
if( NOT (Y STREQUAL SPI_GENERAL_MK_INC))
    set(SPI_GENERAL_MK_INC Y)
    message(STATUS "+ SPI General")

    set(SPI_GENERAL_DIR ${MCAL_COMMON_DIR}/spi)
    message(STATUS "SPI_GENERAL_DIR=${SPI_GENERAL_DIR}")

    add_compile_definitions(HAS_SPI)
    target_compile_definitions(app PUBLIC HAS_SPI)

    include_directories(${SPI_GENERAL_DIR})
    target_include_directories(app PUBLIC ${SPI_GENERAL_DIR})

    target_sources(app PRIVATE ${SPI_GENERAL_DIR}/spi_general.c)
    target_sources(app PRIVATE ${SPI_GENERAL_DIR}/spi_isr.c)

    if(DIAG STREQUAL Y)
        if(SPI_DIAG STREQUAL Y)
            message(STATUS "+ SPI diag")
            target_compile_definitions(app PUBLIC HAS_SPI_DIAG)
            target_sources(app PRIVATE ${SPI_GENERAL_DIR}/spi_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SPI_COMMANDS STREQUAL Y)
            message(STATUS "+ SPI commands")
            target_compile_definitions(app PUBLIC HAS_SPI_COMMANDS)
            target_sources(app PRIVATE ${SPI_GENERAL_DIR}/spi_commands.c)
        endif()
    endif()
endif()
