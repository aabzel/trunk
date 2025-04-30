message(STATUS "STORAGE_MK_INC=${STORAGE_MK_INC}")
if( NOT (STORAGE_MK_INC STREQUAL Y))
    set(STORAGE_MK_INC Y)
    message(STATUS "+  storage")

    target_compile_definitions(app PUBLIC HAS_STORAGE)

    set(STORAGE_DIR ${WORKSPACE_LOC}/storage)
    message(STATUS "STORAGE_DIR=${STORAGE_DIR}")
    target_include_directories(app PUBLIC ${STORAGE_DIR})

    if(ALLOCATOR STREQUAL Y)
        include(${STORAGE_DIR}/allocator/allocator.cmake)
    endif()

    if(CALIBRATION_DATA STREQUAL Y)
        message(STATUS "+CALIBRATION_DATA")
        include(${STORAGE_DIR}/calibration_data/calibration_data.cmake)
    endif()

    if (FAT_FS STREQUAL Y)
        include(${STORAGE_DIR}/fat_fs/fat_fs.cmake)
     endif()

    if(FONT STREQUAL Y)
        message(STATUS "+FONT")
        include(${STORAGE_DIR}/font/font.cmake)
    endif()

    if (FLASH_FS STREQUAL Y)
        include(${STORAGE_DIR}/flash_fs/flash_fs.cmake)
    endif()

    if (NOR_FLASH STREQUAL Y)
        include(${STORAGE_DIR}/nor_flash/nor_flash.cmake)
    endif()

    if (PARAM STREQUAL Y)
        include(${STORAGE_DIR}/params/param.cmake)
    endif()

    if (SW_NVRAM STREQUAL Y)
        include(${STORAGE_DIR}/sw_nvram/sw_nvram.cmake)
    endif()

    if (XML STREQUAL Y)
        include(${STORAGE_DIR}/xml/xml.cmake)
    endif()

    target_sources(app PRIVATE ${STORAGE_DIR}/proc_storage.c)
    if(STORAGE_COMMANDS STREQUAL Y)
         message(STATUS "+ storage commands")
         target_compile_definitions(app PUBLIC HAS_STORAGE_COMMANDS)
         target_sources(app PRIVATE ${STORAGE_DIR}/storage_commands.c)
    endif()

endif()
