
message(STATUS "SPI_NRF5340_MK_INC=${SPI_NRF5340_MK_INC}")
if( NOT (Y STREQUAL SPI_NRF5340_MK_INC))
    set(SPI_NRF5340_MK_INC Y)
    message(STATUS "+ SPI nrf5340")

    set(SPI_NRF5340_DIR ${MCAL_NRF5340_DIR}/spi)
    message(STATUS "SPI_NRF5340_DIR=${SPI_NRF5340_DIR}")

    target_compile_definitions(app PUBLIC HAS_SPI)
    target_compile_definitions(app PUBLIC HAS_SPI_NRFX)
    target_compile_definitions(app PUBLIC NRFX_SPIM_ENABLED)

    include_directories(${SPI_NRF5340_DIR})
    target_include_directories(app PUBLIC ${SPI_NRF5340_DIR})

    target_sources(app PRIVATE ${SPI_NRF5340_DIR}/spi_drv.c)

    if(SPI STREQUAL Y)
        target_compile_definitions(app PUBLIC NRFX_SPIM_ENABLED=1)

        if(SPI0 STREQUAL Y)
            message(STATUS "+SPI0")
            target_compile_definitions(app PUBLIC NRFX_SPIM0_ENABLED=1)
            target_compile_definitions(app PUBLIC HAS_SPI0)
        endif()

        if(SPI1 STREQUAL Y)
            message(STATUS "+SPI1")
            target_compile_definitions(app PUBLIC NRFX_SPIM1_ENABLED=1)
            target_compile_definitions(app PUBLIC HAS_SPI1)
        endif()

        if(SPI2 STREQUAL Y)
            message(STATUS "+SPI2")
            target_compile_definitions(app PUBLIC NRFX_SPIM2_ENABLED=1)
            target_compile_definitions(app PUBLIC HAS_SPI2)
        endif()

        if(SPI3 STREQUAL Y)
            message(STATUS "+SPI3")
            target_compile_definitions(app PUBLIC NRFX_SPIM3_ENABLED=1)
            target_compile_definitions(app PUBLIC HAS_SPI3)
        endif()

        if(SPI4 STREQUAL Y)
             message(STATUS "+SPI4")
            target_compile_definitions(app PUBLIC NRFX_SPIM4_ENABLED=1)
            target_compile_definitions(app PUBLIC NRFX_SPIM4_ENABLED)
            target_compile_definitions(app PUBLIC HAS_SPI4)
        endif()  
    endif()

    if(SPI_ISR STREQUAL Y)
        message(STATUS "+SPI ISR")
        target_compile_definitions(app PUBLIC HAS_SPI_ISR)
        target_sources(app PRIVATE ${SPI_NRF5340_DIR}/spi_isr.c)
    endif()

    if(DIAG STREQUAL Y)
        if(SPI_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SPI_DIAG)
            target_sources(app PRIVATE ${SPI_NRF5340_DIR}/spi_nrf_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SPI_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SPI_COMMANDS)
#            target_sources(app PRIVATE ${SPI_NRF5340_DIR}/spi_nrf_commands.c)
        endif()
    endif()
endif()   