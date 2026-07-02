if(NOT GPIO_DRV_MK_INC)
    set(GPIO_DRV_MK_INC Y)

    set(GPIO_DIR ${MCAL_CUSTOM_DIR}/gpio)
    include_directories( ${GPIO_DIR})

    string(APPEND MCAL_OPT " -DHAS_GPIO_CUSTOM")

    string(APPEND SOURCES_C " ${GPIO_DIR}/gpio_mcal.c")
    string(APPEND SOURCES_C " ${GPIO_DIR}/gpio_custom_isr.c")

    if(CLI STREQUAL Y)
        if(GPIO_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_GPIO_COMMANDS")
            string(APPEND SOURCES_C " ${GPIO_DIR}/gpio_custom_commands.c")
        endif()
    endif()

    if(DIAG STREQUAL Y)
        if(GPIO_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_GPIO_DIAG")
            string(APPEND SOURCES_DIAG_C " ${GPIO_DIR}/gpio_custom_diag.c")
        endif()
    endif()

endif()