message(STATUS "JUMPER_CODE_MK_INC=${JUMPER_CODE_MK_INC}")
if( NOT (JUMPER_CODE_MK_INC  STREQUAL  Y))
    set(JUMPER_CODE_MK_INC Y)
    message(STATUS "+ JUMPER_CODE")

    set(JUMPER_CODE_DIR ${ROOT_DIR}/jumper_code)
    message(STATUS "JUMPER_CODE_DIR=${JUMPER_CODE_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_JUMPER_CODE)
    target_compile_definitions(app PUBLIC HAS_JUMPER_CODE)
    target_compile_definitions(app PUBLIC HAS_JUMPER_CODE_PROC)

    target_include_directories(app PUBLIC ${JUMPER_CODE_DIR})
    target_sources(app PRIVATE ${JUMPER_CODE_DIR}/jumper_code.c)

    if(DIAG  STREQUAL  Y)
        if(JUMPER_CODE_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_JUMPER_CODE_DIAG)
            target_sources(app PRIVATE ${JUMPER_CODE_DIR}/jumper_code_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(JUMPER_CODE_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_JUMPER_CODE_COMMANDS)
            target_sources(app PRIVATE ${JUMPER_CODE_DIR}/jumper_code_commands.c)
        endif()
    endif()
endif()
