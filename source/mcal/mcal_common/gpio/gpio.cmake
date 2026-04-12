#add_library(gpio)
message(STATUS "GPIO_GENERAL_MK_INC=${GPIO_GENERAL_MK_INC}")
if(NOT (GPIO_GENERAL_MK_INC STREQUAL Y))
    set(GPIO_GENERAL_MK_INC Y)

    set(GPIO_GENERAL_DIR "${MCAL_COMMON_DIR}/gpio")

    include_directories( ${GPIO_GENERAL_DIR})
    
    string(APPEND MCAL_OPT " -DHAS_GPIO")
    string(APPEND SOURCES_C " ${GPIO_GENERAL_DIR}/gpio_general.c")

    if(DIAG STREQUAL Y)
        if(GPIO_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_GPIO_DIAG")
            string(APPEND SOURCES_C " ${GPIO_GENERAL_DIR}/gpio_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(GPIO_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_GPIO_COMMANDS")
            string(APPEND SOURCES_C " ${GPIO_GENERAL_DIR}/gpio_commands.c")
        endif()
    endif()
endif()



