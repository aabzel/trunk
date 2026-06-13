message(STATUS "ENCODER_LAMP_MK_INC=${ENCODER_LAMP_MK_INC}")
if( NOT (ENCODER_LAMP_MK_INC  STREQUAL  Y))
    set(ENCODER_LAMP_MK_INC Y)
    message(STATUS "+ ENCODER_LAMP")

    set(ENCODER_LAMP_DIR ${ROOT_DIR}/encoder_lamp)
    message(STATUS "ENCODER_LAMP_DIR=${ENCODER_LAMP_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_ENCODER_LAMP)
    target_compile_definitions(app PUBLIC HAS_ENCODER_LAMP)
    target_compile_definitions(app PUBLIC HAS_ENCODER_LAMP_PROC)

    target_include_directories(app PUBLIC ${ENCODER_LAMP_DIR})
    target_sources(app PRIVATE ${ENCODER_LAMP_DIR}/encoder_lamp.c)

    if(DIAG  STREQUAL  Y)
        if(ENCODER_LAMP_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_ENCODER_LAMP_DIAG)
            target_sources(app PRIVATE ${ENCODER_LAMP_DIR}/encoder_lamp_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(ENCODER_LAMP_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_ENCODER_LAMP_COMMANDS)
            target_sources(app PRIVATE ${ENCODER_LAMP_DIR}/encoder_lamp_commands.c)
        endif()
    endif()
endif()
