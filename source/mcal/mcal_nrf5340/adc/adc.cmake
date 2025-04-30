message(STATUS "ADC_NRFX_MK_INC=${ADC_NRFX_MK_INC}")
if( NOT (ADC_NRFX_MK_INC STREQUAL Y))
    set(ADC_NRFX_MK_INC Y)
    message(STATUS "+ ADC nrfx")

    set(ADC_NRFX_DIR ${MCAL_NRF5340_DIR}/adc)
    message(STATUS "ADC_NRFX_DIR=${ADC_NRFX_DIR}")

    target_compile_definitions(app PUBLIC HAS_ADC)
    target_compile_definitions(app PUBLIC HAS_ADC1)
    target_compile_definitions(app PUBLIC HAS_ADC_PROC)
    target_compile_definitions(app PUBLIC HAS_ADC_CUSTOM)

    include_directories(${ADC_NRFX_DIR})
    target_include_directories(app PUBLIC ${ADC_NRFX_DIR})

    target_compile_definitions(app PUBLIC NRFX_ADCE_ENABLED)

    if(ADC1 STREQUAL Y)
        target_compile_definitions(app PUBLIC NRFX_ADCE1_ENABLED=1)
    endif()

    target_sources(app PRIVATE ${ADC_NRFX_DIR}/adc_drv.c)

    if(ADC_INTERRUPT STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_ADC_INTERRUPT)
        target_sources(app PRIVATE ${ADC_NRFX_DIR}/adc_isr.c)
    endif()

    if(DIAG STREQUAL Y)
        if(ADC_DIAG STREQUAL Y)
            message(STATUS "Add ADC custon diag")
            target_compile_definitions(app PUBLIC HAS_ADC_DIAG)
            target_sources(app PRIVATE ${ADC_NRF5340_DIR}/adc_custom_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(ADC_COMMANDS STREQUAL Y)
            #message( SEND_ERROR ADC_COMMANDS=${ADC_COMMANDS} )
            message(STATUS "Add ADC custon commands")
            target_compile_definitions(app PUBLIC HAS_ADC_CUSTOM_COMMANDS)
            target_sources(app PRIVATE ${ADC_NRF5340_DIR}/adc_custom_commands.c)
        endif()
    endif()
endif()


