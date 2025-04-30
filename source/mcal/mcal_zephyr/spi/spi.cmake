
message(STATUS "SPI_ZEPHYR_MK_INC=${SPI_ZEPHYR_MK_INC}")
if( NOT (Y STREQUAL SPI_ZEPHYR_MK_INC))
    set(SPI_ZEPHYR_MK_INC Y)

    message(STATUS "set SPI_ZEPHYR_MK_INC=${SPI_ZEPHYR_MK_INC}")
    message(STATUS "+ SPI Zephyr")

    set(SPI_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/spi)
    message(STATUS "SPI_ZEPHYR_DIR=${SPI_ZEPHYR_DIR}")

    add_compile_definitions(HAS_SPI)
    target_compile_definitions(app PUBLIC HAS_SPI)

    include_directories(${SPI_ZEPHYR_DIR})
    target_include_directories(app PUBLIC ${SPI_ZEPHYR_DIR})

    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/zephyr/include/zephyr/drivers)

    if(SPI0 STREQUAL Y)
        message(STATUS "+ SPI0")
        target_compile_definitions(app PUBLIC HAS_SPI0)
    endif()

    if(SPI1 STREQUAL Y)
        message(STATUS "+ SPI1")
        target_compile_definitions(app PUBLIC HAS_SPI1)
    endif()

    if(SPI2 STREQUAL Y)
        message(STATUS "+ SPI2")
        target_compile_definitions(app PUBLIC HAS_SPI2)
    endif()

    if(SPI3 STREQUAL Y)
        message(STATUS "+ SPI3")
        target_compile_definitions(app PUBLIC HAS_SPI3)
    endif()

    if(SPI4 STREQUAL Y)
        message(STATUS "+ SPI4")
        target_compile_definitions(app PUBLIC HAS_SPI4)
    endif()

    if(SPI_INTERRUPT STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_SPI_INTERRUPT)
    endif()

    target_sources(app PRIVATE ${SPI_ZEPHYR_DIR}/spi_drv.c)

    if(DIAG STREQUAL Y)
        if(SPI_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_SPI_DIAG)
            target_sources(app PRIVATE ${SPI_ZEPHYR_DIR}/spi_custom_diag.c)
        endif()
    endif()    

endif()   