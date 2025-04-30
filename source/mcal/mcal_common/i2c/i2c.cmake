
message(STATUS "I2C_MK_INC=${I2C_MK_INC}")
if( NOT (I2C_MK_INC STREQUAL Y))
    set(I2C_MK_INC Y)
    message(STATUS "Link I2C General")

    set(I2C_GENERAL_DIR ${MCAL_COMMON_DIR}/i2c)
    message(STATUS "I2C_GENERAL_DIR=${I2C_GENERAL_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_I2C)
    target_compile_definitions(app PUBLIC HAS_I2C)

    include_directories(${I2C_GENERAL_DIR})
    target_include_directories(app PUBLIC ${I2C_GENERAL_DIR})
    
    target_sources(app PRIVATE ${I2C_GENERAL_DIR}/i2c_bsp.c)

    if(DIAG STREQUAL Y)
        if(I2C_DIAG STREQUAL Y)
            target_sources(app PRIVATE ${I2C_GENERAL_DIR}/i2c_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(I2C_COMMANDS STREQUAL Y)
            #message( SEND_ERROR I2C_COMMANDS=${I2C_COMMANDS} )
            target_compile_definitions(app PUBLIC HAS_I2C_COMMANDS)
            target_sources(app PRIVATE ${I2C_GENERAL_DIR}/i2c_commands.c)
        endif()
    endif()
endif()

