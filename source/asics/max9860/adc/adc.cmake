message(STATUS "MAX9860_ADC_MK_INC=${MAX9860_ADC_MK_INC}")
if( NOT (MAX9860_ADC_MK_INC STREQUAL Y))
    set(MAX9860_ADC_MK_INC Y)
    message(STATUS "+MAX9860_ADC")

    set(MAX9860_ADC_DIR ${MAX9860_DIR}/dac)
    message(STATUS "MAX9860_ADC_DIR=${MAX9860_ADC_DIR}")

    #add_compile_definitions(HAS_MAX9860_ADC)
    target_compile_definitions(app PUBLIC HAS_MAX9860_ADC)

    target_sources(app PRIVATE ${MAX9860_ADC_DIR}/max9860_mic_drv.c)

    target_include_directories(app PUBLIC ${MAX9860_ADC_DIR})

    if(DIAG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_MAX9860_ADC_DIAG)
        target_sources(app PRIVATE ${MAX9860_ADC_DIR}/max9860_adc_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(MAX9860_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MAX9860_ADC_COMMANDS)
            target_sources(app PRIVATE ${MAX9860_ADC_DIR}/max9860_dac_commands.c)
        endif()
    endif()
endif()
