message(STATUS "FLASH_FS_MK_INC=${FLASH_FS_MK_INC}")
if( NOT (FLASH_FS_MK_INC STREQUAL Y))

    set(FLASH_FS_MK_INC Y)
    message(STATUS "+FLASH_FS")

    set(FLASH_FS_DIR ${STORAGE_DIR}/flash_fs)
    message(STATUS "FLASH_FS_DIR=${FLASH_FS_DIR}")

    #@ echo ${error FLASH_FS_DIR = ${FLASH_FS_DIR))
    #@ echo ${error CFLAGS = ${CFLAGS)) 
    target_compile_definitions(app PUBLIC HAS_FLASH_FS)
    target_compile_definitions(app PUBLIC HAS_FLASH_FS_PROC)

    target_include_directories(app PUBLIC ${FLASH_FS_DIR})

    set(CRC Y)
    set(CRC8 Y)

    target_sources(app PRIVATE ${FLASH_FS_DIR}/flash_fs.c)
    target_sources(app PRIVATE ${FLASH_FS_DIR}/flash_fs_ll.c)

    if (DIAG STREQUAL Y)
        if (FLASH_FS_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_FLASH_FS_DIAG)
            target_sources(app PRIVATE ${FLASH_FS_DIR}/flash_fs_diag.c)
        endif()
    endif()

    if (FLASH_FS_WRITE STREQUAL Y)
        #@echo ${error FLASH_FS_WRITE = ${FLASH_FS_WRITE)) 
         target_compile_definitions(app PUBLIC HAS_FLASH_FS_WRITE)
    endif()

    if (CLI STREQUAL Y)
        if (FLASH_FS_COMMANDS STREQUAL Y)
             target_compile_definitions(app PUBLIC HAS_FLASH_FS_EXT_COMMANDS)
             target_compile_definitions(app PUBLIC HAS_FLASH_FS_COMMANDS)
            target_sources(app PRIVATE ${FLASH_FS_DIR}/flash_fs_commands.c)
        endif()
    endif()
endif()


