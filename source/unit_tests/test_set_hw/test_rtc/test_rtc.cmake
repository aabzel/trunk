message(STATUS "TEST_SPI_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_SPI_MK_INC STREQUAL Y))
    set(TEST_SPI_MK_INC Y)
    message(STATUS "+ Test SPI")

    set(TEST_SPI_DIR ${TEST_SET_HW_DIR}/test_spi)

    target_include_directories(app PUBLIC ${TEST_SPI_DIR})

    target_compile_definitions(app PUBLIC HAS_TEST_SPI)

    target_sources(app PRIVATE ${TEST_SPI_DIR}/test_spi.c)
endif()