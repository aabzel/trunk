message(STATUS "FAT_FS_MK_INC=${FAT_FS_MK_INC}")
if( NOT (FAT_FS_MK_INC  STREQUAL  Y))
    set(FAT_FS_MK_INC Y)
    message(STATUS "+ FAT_FS")

    set(FAT_FS_DIR ${ROOT_DIR}/fat_fs)
    message(STATUS "FAT_FS_DIR=${FAT_FS_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_FAT_FS)
    target_compile_definitions(app PUBLIC HAS_FAT_FS)
    target_compile_definitions(app PUBLIC HAS_FAT_FS_PROC)

    target_include_directories(app PUBLIC ${FAT_FS_DIR})
    target_sources(app PRIVATE ${FAT_FS_DIR}/fat_fs.c)

    if(DIAG  STREQUAL  Y)
        if(FAT_FS_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_FAT_FS_DIAG)
            target_sources(app PRIVATE ${FAT_FS_DIR}/fat_fs_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(FAT_FS_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_FAT_FS_COMMANDS)
            target_sources(app PRIVATE ${FAT_FS_DIR}/fat_fs_commands.c)
        endif()
    endif()
endif()
