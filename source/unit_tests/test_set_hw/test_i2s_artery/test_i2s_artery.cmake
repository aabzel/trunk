message(STATUS "TEST_I2S_MK_INC=${BSP_MK_INC}")
if( NOT (TEST_I2S_MK_INC STREQUAL Y))
    set(TEST_I2S_MK_INC Y)
    message(STATUS "Link Test I2S")

    set(TEST_I2S_DIR ${TEST_SET_HW_DIR}/test_i2s)

    target_include_directories(app PUBLIC ${TEST_I2S_DIR})

    target_compile_definitions(app PUBLIC HAS_TEST_I2S)

    target_sources(app PRIVATE ${TEST_I2S_DIR}/test_i2s.c)
endif()