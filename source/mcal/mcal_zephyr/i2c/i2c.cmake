
message(STATUS "I2C_ZEPHYR_MK_INC=${I2C_ZEPHYR_MK_INC}")
if( NOT (I2C_ZEPHYR_MK_INC STREQUAL Y))
    set(I2C_ZEPHYR_MK_INC Y)

    message(STATUS "set I2C_ZEPHYR_MK_INC=${I2C_ZEPHYR_MK_INC}")
    set(I2C_ZEPHYR_DIR ${MCAL_ZEPHYR_DIR}/i2c)
    message(STATUS "+ I2C Zephyr")
    message(STATUS "I2C_ZEPHYR_DIR=${I2C_ZEPHYR_DIR}")
    target_include_directories(app PUBLIC ${I2C_ZEPHYR_DIR})

    add_compile_definitions(HAS_I2C)
    target_compile_definitions(app PUBLIC HAS_I2C)

    target_sources(app PRIVATE ${I2C_ZEPHYR_DIR}/i2c_drv.c)

    if(I2C0 STREQUAL Y)
        message(STATUS "+ I2C0 Zephyr")
        target_compile_definitions(app PUBLIC HAS_I2C0)
    endif()

    if(I2C1 STREQUAL Y)
        message(STATUS "+ I2C1 Zephyr")
        target_compile_definitions(app PUBLIC HAS_I2C1)
    endif()

    if(I2C2 STREQUAL Y)
        message(STATUS "+ I2C2 Zephyr")
        target_compile_definitions(app PUBLIC HAS_I2C2)
    endif()

    if(I2C3 STREQUAL Y)
        message(STATUS "+ I2C3 Zephyr")
        target_compile_definitions(app PUBLIC HAS_I2C3)
    endif()
endif()