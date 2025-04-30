
message(STATUS "GPIO_NRFX_DRV_MK_INC=${GPIO_NRFX_DRV_MK_INC}")
if( NOT (GPIO_NRFX_DRV_MK_INC STREQUAL Y))
    set(GPIO_NRFX_DRV_MK_INC Y)

    message(STATUS "+ GPIO NRFX")

    set(GPIO_NRF_DIR ${MCAL_NRF5340_DIR}/gpio)
    message(STATUS "GPIO_NRF_DIR=${GPIO_NRF_DIR}")

    target_include_directories(app PUBLIC ${NRF_SDK_DIR}/modules/hal/nordic/nrfx/hal)
    target_include_directories(app PUBLIC ${GPIO_NRF_DIR})

    #@echo ${error GPIO_NRF_DIR=${GPIO_NRF_DIR))
    target_compile_definitions(app PUBLIC HAS_GPIO)
    target_compile_definitions(app PUBLIC HAS_GPIO_NRFX)
    target_compile_definitions(app PUBLIC HAS_GPIO_CUSTOM)

    if(PINS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_PINS)
    endif()

    target_sources(app PRIVATE ${GPIO_NRF_DIR}/gpio_drv.c)

    if (CLI STREQUAL Y)
        if (GPIO_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_GPIO_COMMANDS)
            target_sources(app PRIVATE ${GPIO_NRF_DIR}/gpio_custom_commands.c)
        endif()
    endif()

    if (DIAG STREQUAL Y)
        if (GPIO_DIAG STREQUAL Y)
            target_sources(app PRIVATE ${GPIO_NRF_DIR}/gpio_custom_diag.c)
        endif()
    endif()
endif()
