
message(STATUS "I2S_ZEPHYR_MK_INC=${I2S_ZEPHYR_MK_INC}")
if(NOT (I2S_ZEPHYR_MK_INC STREQUAL Y))
    set(I2S_ZEPHYR_MK_INC Y)
    message(STATUS "set I2S_ZEPHYR_MK_INC=${I2S_ZEPHYR_MK_INC}")
endif()
    set(I2S_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/i2s)

    message(STATUS "Link I2S Zephyr")
    message(STATUS "I2S_ZEPHYR_DIR=${I2S_ZEPHYR_DIR}")
    target_include_directories(app PUBLIC ${I2S_ZEPHYR_DIR})

    add_compile_definitions(HAS_I2S)
    target_compile_definitions(app PUBLIC HAS_I2S)

    target_sources(app PRIVATE ${I2S_ZEPHYR_DIR}/i2s_drv.c)

    if(DIAG STREQUAL Y)
        if(I2S_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_I2S_DIAG)
            target_sources(app PRIVATE ${I2S_ZEPHYR_DIR}/i2s_zephyr_diag.c)
        endif()
    endif()

    if(I2S0 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_I2S0)
    endif()


