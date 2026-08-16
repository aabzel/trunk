message(STATUS "BACK_COUNT_MK_INC=${BACK_COUNT_MK_INC}")
if( NOT (BACK_COUNT_MK_INC  STREQUAL  Y))
    set(BACK_COUNT_MK_INC Y)
    message(STATUS "+ BACK_COUNT")

    set(BACK_COUNT_DIR ${ROOT_DIR}/back_count)
    message(STATUS "BACK_COUNT_DIR=${BACK_COUNT_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_BACK_COUNT)
    target_compile_definitions(app PUBLIC HAS_BACK_COUNT)
    target_compile_definitions(app PUBLIC HAS_BACK_COUNT_PROC)

    target_include_directories(app PUBLIC ${BACK_COUNT_DIR})
    target_sources(app PRIVATE ${BACK_COUNT_DIR}/back_count.c)

    if(DIAG  STREQUAL  Y)
        if(BACK_COUNT_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BACK_COUNT_DIAG)
            target_sources(app PRIVATE ${BACK_COUNT_DIR}/back_count_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(BACK_COUNT_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BACK_COUNT_COMMANDS)
            target_sources(app PRIVATE ${BACK_COUNT_DIR}/back_count_commands.c)
        endif()
    endif()
endif()
