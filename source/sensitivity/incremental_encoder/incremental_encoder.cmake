message(STATUS "INCREMENTAL_ENCODER_MK_INC=${INCREMENTAL_ENCODER_MK_INC}")
if( NOT (INCREMENTAL_ENCODER_MK_INC  STREQUAL  Y))
    set(INCREMENTAL_ENCODER_MK_INC Y)
    message(STATUS "+ INCREMENTAL_ENCODER")

    set(INCREMENTAL_ENCODER_DIR ${ROOT_DIR}/incremental_encoder)
    message(STATUS "INCREMENTAL_ENCODER_DIR=${INCREMENTAL_ENCODER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_INCREMENTAL_ENCODER)
    target_compile_definitions(app PUBLIC HAS_INCREMENTAL_ENCODER)
    target_compile_definitions(app PUBLIC HAS_INCREMENTAL_ENCODER_PROC)

    target_include_directories(app PUBLIC ${INCREMENTAL_ENCODER_DIR})
    target_sources(app PRIVATE ${INCREMENTAL_ENCODER_DIR}/incremental_encoder.c)

    if(DIAG  STREQUAL  Y)
        if(INCREMENTAL_ENCODER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_INCREMENTAL_ENCODER_DIAG)
            target_sources(app PRIVATE ${INCREMENTAL_ENCODER_DIR}/incremental_encoder_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(INCREMENTAL_ENCODER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_INCREMENTAL_ENCODER_COMMANDS)
            target_sources(app PRIVATE ${INCREMENTAL_ENCODER_DIR}/incremental_encoder_commands.c)
        endif()
    endif()
endif()
