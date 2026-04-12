message(STATUS "STORE_FS_MK_INC=${STORE_FS_MK_INC}")
if( NOT (STORE_FS_MK_INC  STREQUAL  Y))
    set(STORE_FS_MK_INC Y)
    message(STATUS "+ STORE_FS")

    set(STORE_FS_DIR ${ROOT_DIR}/store_fs)
    message(STATUS "STORE_FS_DIR=${STORE_FS_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_STORE_FS)
    target_compile_definitions(app PUBLIC HAS_STORE_FS)
    target_compile_definitions(app PUBLIC HAS_STORE_FS_PROC)

    target_include_directories(app PUBLIC ${STORE_FS_DIR})
    target_sources(app PRIVATE ${STORE_FS_DIR}/store_fs.c)

    if(DIAG  STREQUAL  Y)
        if(STORE_FS_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_STORE_FS_DIAG)
            target_sources(app PRIVATE ${STORE_FS_DIR}/store_fs_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(STORE_FS_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_STORE_FS_COMMANDS)
            target_sources(app PRIVATE ${STORE_FS_DIR}/store_fs_commands.c)
        endif()
    endif()
endif()
