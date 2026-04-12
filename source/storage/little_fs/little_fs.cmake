message(STATUS "LITTLE_FS_MK_INC=${LITTLE_FS_MK_INC}")
if( NOT (LITTLE_FS_MK_INC  STREQUAL  Y))
    set(LITTLE_FS_MK_INC Y)
    message(STATUS "+ LITTLE_FS")

    set(LITTLE_FS_DIR ${ROOT_DIR}/little_fs)
    message(STATUS "LITTLE_FS_DIR=${LITTLE_FS_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_LITTLE_FS)
    target_compile_definitions(app PUBLIC HAS_LITTLE_FS)
    target_compile_definitions(app PUBLIC HAS_LITTLE_FS_PROC)

    target_include_directories(app PUBLIC ${LITTLE_FS_DIR})
    target_sources(app PRIVATE ${LITTLE_FS_DIR}/little_fs.c)

    if(DIAG  STREQUAL  Y)
        if(LITTLE_FS_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LITTLE_FS_DIAG)
            target_sources(app PRIVATE ${LITTLE_FS_DIR}/little_fs_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(LITTLE_FS_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_LITTLE_FS_COMMANDS)
            target_sources(app PRIVATE ${LITTLE_FS_DIR}/little_fs_commands.c)
        endif()
    endif()
endif()
