message(STATUS "SMOOTH_LAMP_MK_INC=${SMOOTH_LAMP_MK_INC}")
if( NOT (SMOOTH_LAMP_MK_INC  STREQUAL  Y))
    set(SMOOTH_LAMP_MK_INC Y)
    message(STATUS "+ SMOOTH_LAMP")

    set(SMOOTH_LAMP_DIR ${ROOT_DIR}/smooth_lamp)
    message(STATUS "SMOOTH_LAMP_DIR=${SMOOTH_LAMP_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SMOOTH_LAMP)
    target_compile_definitions(app PUBLIC HAS_SMOOTH_LAMP)
    target_compile_definitions(app PUBLIC HAS_SMOOTH_LAMP_PROC)

    target_include_directories(app PUBLIC ${SMOOTH_LAMP_DIR})
    target_sources(app PRIVATE ${SMOOTH_LAMP_DIR}/smooth_lamp.c)

    if(DIAG  STREQUAL  Y)
        if(SMOOTH_LAMP_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SMOOTH_LAMP_DIAG)
            target_sources(app PRIVATE ${SMOOTH_LAMP_DIR}/smooth_lamp_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SMOOTH_LAMP_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SMOOTH_LAMP_COMMANDS)
            target_sources(app PRIVATE ${SMOOTH_LAMP_DIR}/smooth_lamp_commands.c)
        endif()
    endif()
endif()
