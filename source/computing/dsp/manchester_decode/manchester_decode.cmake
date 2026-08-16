message(STATUS "MANCHESTER_DECODE_MK_INC=${MANCHESTER_DECODE_MK_INC}")
if( NOT (MANCHESTER_DECODE_MK_INC  STREQUAL  Y))
    set(MANCHESTER_DECODE_MK_INC Y)
    message(STATUS "+ MANCHESTER_DECODE")

    set(MANCHESTER_DECODE_DIR ${ROOT_DIR}/manchester_decode)
    message(STATUS "MANCHESTER_DECODE_DIR=${MANCHESTER_DECODE_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_MANCHESTER_DECODE)
    target_compile_definitions(app PUBLIC HAS_MANCHESTER_DECODE)
    target_compile_definitions(app PUBLIC HAS_MANCHESTER_DECODE_PROC)

    target_include_directories(app PUBLIC ${MANCHESTER_DECODE_DIR})
    target_sources(app PRIVATE ${MANCHESTER_DECODE_DIR}/manchester_decode.c)

    if(DIAG  STREQUAL  Y)
        if(MANCHESTER_DECODE_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MANCHESTER_DECODE_DIAG)
            target_sources(app PRIVATE ${MANCHESTER_DECODE_DIR}/manchester_decode_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(MANCHESTER_DECODE_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MANCHESTER_DECODE_COMMANDS)
            target_sources(app PRIVATE ${MANCHESTER_DECODE_DIR}/manchester_decode_commands.c)
        endif()
    endif()
endif()
