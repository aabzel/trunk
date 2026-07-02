message(STATUS "TEST_I2S_FULL_DUPLEX_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_I2S_FULL_DUPLEX_MK_INC STREQUAL Y))
    set(TEST_I2S_FULL_DUPLEX_MK_INC Y)
    message(STATUS "Link Test I2S")

    set(TEST_I2S_FULL_DUPLEX_DIR ${TEST_SET_HW_DIR}/test_i2s)

    target_include_directories(app PUBLIC ${TEST_I2S_FULL_DUPLEX_DIR})

    target_compile_definitions(app PUBLIC HAS_TEST_I2S_FULL_DUPLEX)

    target_sources(app PRIVATE ${TEST_I2S_FULL_DUPLEX_DIR}/test_i2s_full_duplex.c)
endif()