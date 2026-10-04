message(STATUS "BTS724G_MK_INC=${BTS724G_MK_INC}")
if( NOT (BTS724G_MK_INC  STREQUAL  Y))
    set(BTS724G_MK_INC Y)
    message(STATUS "+ BTS724G")

    set(BTS724G_DIR ${ROOT_DIR}/bts724g)
    message(STATUS "BTS724G_DIR=${BTS724G_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_BTS724G)
    target_compile_definitions(app PUBLIC HAS_BTS724G)
    target_compile_definitions(app PUBLIC HAS_BTS724G_PROC)

    target_include_directories(app PUBLIC ${BTS724G_DIR})
    target_sources(app PRIVATE ${BTS724G_DIR}/bts724g.c)

    if(DIAG  STREQUAL  Y)
        if(BTS724G_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BTS724G_DIAG)
            target_sources(app PRIVATE ${BTS724G_DIR}/bts724g_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(BTS724G_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_BTS724G_COMMANDS)
            target_sources(app PRIVATE ${BTS724G_DIR}/bts724g_commands.c)
        endif()
    endif()
endif()
