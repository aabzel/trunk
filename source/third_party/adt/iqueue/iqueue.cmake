message(STATUS "IQUEUE_MK_INC=${IQUEUE_MK_INC}")
if( NOT (IQUEUE_MK_INC  STREQUAL  Y))
    set(IQUEUE_MK_INC Y)
    message(STATUS "+ IQUEUE")

    set(IQUEUE_DIR ${ROOT_DIR}/iqueue)
    message(STATUS "IQUEUE_DIR=${IQUEUE_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_IQUEUE)
    target_compile_definitions(app PUBLIC HAS_IQUEUE)
    target_compile_definitions(app PUBLIC HAS_IQUEUE_PROC)

    target_include_directories(app PUBLIC ${IQUEUE_DIR})
    target_sources(app PRIVATE ${IQUEUE_DIR}/iqueue.c)

    if(DIAG  STREQUAL  Y)
        if(IQUEUE_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_IQUEUE_DIAG)
            target_sources(app PRIVATE ${IQUEUE_DIR}/iqueue_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(IQUEUE_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_IQUEUE_COMMANDS)
            target_sources(app PRIVATE ${IQUEUE_DIR}/iqueue_commands.c)
        endif()
    endif()
endif()
