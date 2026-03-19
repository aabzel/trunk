message(STATUS "MPU_MK_INC=${MPU_MK_INC}")
if( NOT (MPU_MK_INC  STREQUAL  Y))
    set(MPU_MK_INC Y)
    message(STATUS "+ MPU")

    set(MPU_DIR ${ROOT_DIR}/mpu)
    message(STATUS "MPU_DIR=${MPU_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_MPU)
    target_compile_definitions(app PUBLIC HAS_MPU)
    target_compile_definitions(app PUBLIC HAS_MPU_PROC)

    target_include_directories(app PUBLIC ${MPU_DIR})
    target_sources(app PRIVATE ${MPU_DIR}/mpu.c)

    if(DIAG  STREQUAL  Y)
        if(MPU_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MPU_DIAG)
            target_sources(app PRIVATE ${MPU_DIR}/mpu_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(MPU_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MPU_COMMANDS)
            target_sources(app PRIVATE ${MPU_DIR}/mpu_commands.c)
        endif()
    endif()
endif()
