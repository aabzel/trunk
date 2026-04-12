message(STATUS "STORAGE_MK_INC=${STORAGE_MK_INC}")
if(NOT (STORAGE_MK_INC STREQUAL Y))
    set(STORAGE_MK_INC Y)

    string(APPEND MCAL_OPT " -DHAS_STORAGE")
    set(STORAGE_DIR "${WORKSPACE_LOC}/storage")
    include_directories(${STORAGE_DIR})

    if(HEX_BIN STREQUAL Y)
        include(${STORAGE_DIR}/hex_bin/hex_bin.cmake)
    endif()

    if(ALLOCATOR STREQUAL Y)
        include(${STORAGE_DIR}/allocator/allocator.cmake)
    endif()

    if(BLACK_BOX STREQUAL Y)
        include(${STORAGE_DIR}/black_box/black_box.cmake)
    endif()

    if(CALIBRATION_DATA STREQUAL Y)
        include(${STORAGE_DIR}/calibration_data/calibration_data.cmake)
    endif()

    if(DISK STREQUAL Y)
        include(${STORAGE_DIR}/disk/disk.cmake)
    endif()

    if(LITTLE_FS STREQUAL Y)
        include(${STORAGE_DIR}/little_fs/little_fs.cmake)
    endif()

    if(FLASH_FS STREQUAL Y)
        include(${STORAGE_DIR}/flash_fs/flash_fs.cmake)
    endif()

    if(STORE_FS STREQUAL Y)
        include(${STORAGE_DIR}/store_fs/store_fs.cmake)
    endif()

    if(NOR_FLASH_OFF_CHIP STREQUAL Y)
        include(${STORAGE_DIR}/nor_flash_off_chip/nor_flash_off_chip.cmake)
    endif()

    if(FILE_API STREQUAL Y)
        include(${STORAGE_DIR}/file_api/file_api.cmake)
    endif()

    if(FAT_FS STREQUAL Y)
        include(${STORAGE_DIR}/fat_fs/fat_fs.cmake)
    endif()

    if(FONT STREQUAL Y)
        include(${STORAGE_DIR}/font/font.cmake)
    endif()

    if(FILE_PC STREQUAL Y)
        include(${STORAGE_DIR}/file_pc/file_pc.cmake)
    endif()

    if(NOR_FLASH STREQUAL Y)
        include(${STORAGE_DIR}/nor_flash/nor_flash.cmake)
    endif()

    if(PARAM STREQUAL Y)
        include(${STORAGE_DIR}/params/param.cmake)
    endif()

    if(RUNNING_LINE STREQUAL Y)
        include(${STORAGE_DIR}/running_line/running_line.cmake)
    endif()

    if(SW_NOR_FLASH STREQUAL Y)
        include(${STORAGE_DIR}/sw_nor_flash/sw_nor_flash.cmake)
    endif()

    if(SW_NVRAM STREQUAL Y)
        include(${STORAGE_DIR}/sw_nvram/sw_nvram.cmake)
    endif()

    if(SW_SD_CARD STREQUAL Y)
        include(${STORAGE_DIR}/sw_sd_card/sw_sd_card.cmake)
    endif()

    if(XML STREQUAL Y)
        include(${STORAGE_DIR}/xml/xml.cmake)
    endif()

    if(WAV STREQUAL Y)
        include(${STORAGE_DIR}/wav/wav.cmake)
    endif()

    string(APPEND SOURCES_C " ${STORAGE_DIR}/storage.c")

    if(DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_STORAGE_DIAG")
        string(APPEND SOURCES_DIAG_C " ${STORAGE_DIR}/storage_diag.c")
    endif()

    if(STORAGE_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_STORAGE_COMMANDS")
        string(APPEND SOURCES_C " ${STORAGE_DIR}/storage_commands.c")
    endif()
endif()
