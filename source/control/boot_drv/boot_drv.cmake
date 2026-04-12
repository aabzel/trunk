if(NOT BOOT_DRV_MK_INC STREQUAL Y)
    set(BOOT_DRV_MK_INC Y)

    set(BOOT_DRV_DIR "${CONTROL_DIR}/boot_drv")

    include_directories(${BOOT_DRV_DIR})

    string(APPEND MCAL_OPT " -DHAS_BOOT")
    string(APPEND SOURCES_C " ${BOOT_DRV_DIR}/boot_driver.c")

    if(DIAG STREQUAL Y)
        if(BOOT_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_BOOT_DIAG")
            string(APPEND SOURCES_C " ${BOOT_DRV_DIR}/boot_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(BOOT_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_BOOT_COMMANDS")
            string(APPEND SOURCES_C " ${BOOT_DRV_DIR}/boot_commands.c")
        endif()
    endif()
endif()