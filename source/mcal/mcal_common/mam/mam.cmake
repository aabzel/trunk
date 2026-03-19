message(STATUS "MAM_MK_INC=${MAM_MK_INC}")
if( NOT (MAM_MK_INC  STREQUAL  Y))
    set(MAM_MK_INC Y)
    message(STATUS "+ MAM")

    set(MAM_DIR ${ROOT_DIR}/mam)
    message(STATUS "MAM_DIR=${MAM_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_MAM)
    target_compile_definitions(app PUBLIC HAS_MAM)
    target_compile_definitions(app PUBLIC HAS_MAM_PROC)

    target_include_directories(app PUBLIC ${MAM_DIR})
    target_sources(app PRIVATE ${MAM_DIR}/mam.c)

    if(DIAG  STREQUAL  Y)
        if(MAM_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MAM_DIAG)
            target_sources(app PRIVATE ${MAM_DIR}/mam_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(MAM_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MAM_COMMANDS)
            target_sources(app PRIVATE ${MAM_DIR}/mam_commands.c)
        endif()
    endif()
endif()
