message(STATUS "I2C_NRF5340_MK_INC=${I2C_NRF5340_MK_INC}")
if( NOT (I2C_NRF5340_MK_INC STREQUAL Y))
    set(I2C_NRF5340_MK_INC Y)
    message(STATUS "Link I2C for nrf5340")

    set(I2C_NRF5340_DIR ${MCAL_NRF5340_DIR}/i2c)
    message(STATUS "I2C_NRF5340_DIR=${I2C_NRF5340_DIR}")
    message(STATUS "NRF_SDK_DIR=${NRF_SDK_DIR}")
    add_compile_definitions(HAS_I2C)
    target_compile_definitions(app PUBLIC HAS_I2C)

    if(I2C0 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_I2C0)
    endif()
    
    if(I2C1 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_I2C1)
    endif()

    if(I2C2 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_I2C2)
    endif()
    
    if(I2C3 STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_I2C3)
    endif()

    target_include_directories(app PUBLIC ${I2C_NRF5340_DIR})

    target_sources(app PRIVATE ${I2C_NRF5340_DIR}/i2c_drv.c)
    include_directories(${I2C_NRF5340_DIR})
    include_directories(${NRF_SDK_DIR}/modules/hal/nordic/nrfx/drivers/include)

    message(STATUS "I2C_NRF5340_DIR=${I2C_NRF5340_DIR}")
endif()


