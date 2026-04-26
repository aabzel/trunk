message(STATUS "GPIO_DAC_MK_INC=${GPIO_DAC_MK_INC}")
if( NOT (GPIO_DAC_MK_INC  STREQUAL  Y))
    set(GPIO_DAC_MK_INC Y)
    message(STATUS "+ GPIO_DAC")

    set(GPIO_DAC_DIR ${ROOT_DIR}/gpio_dac)
    message(STATUS "GPIO_DAC_DIR=${GPIO_DAC_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_GPIO_DAC)
    target_compile_definitions(app PUBLIC HAS_GPIO_DAC)
    target_compile_definitions(app PUBLIC HAS_GPIO_DAC_PROC)

    target_include_directories(app PUBLIC ${GPIO_DAC_DIR})
    target_sources(app PRIVATE ${GPIO_DAC_DIR}/gpio_dac.c)

    if(DIAG  STREQUAL  Y)
        if(GPIO_DAC_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GPIO_DAC_DIAG)
            target_sources(app PRIVATE ${GPIO_DAC_DIR}/gpio_dac_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(GPIO_DAC_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GPIO_DAC_COMMANDS)
            target_sources(app PRIVATE ${GPIO_DAC_DIR}/gpio_dac_commands.c)
        endif()
    endif()
endif()
