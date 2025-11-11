message(STATUS "NAU8814_ADC_MK_INC=${NAU8814_ADC_MK_INC}")
if( NOT (NAU8814_ADC_MK_INC STREQUAL Y))
    set(NAU8814_ADC_MK_INC Y)
    message(STATUS "+NAU8814_ADC")

    set(NAU8814_ADC_DIR ${NAU8814_DIR}/dac)
    message(STATUS "NAU8814_ADC_DIR=${NAU8814_ADC_DIR}")

    #add_compile_definitions(HAS_NAU8814_ADC)
    target_compile_definitions(app PUBLIC HAS_NAU8814_ADC)

    target_sources(app PRIVATE ${NAU8814_ADC_DIR}/nau8814_adc.c)

    target_include_directories(app PUBLIC ${NAU8814_ADC_DIR})

    if(DIAG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_NAU8814_ADC_DIAG)
        target_sources(app PRIVATE ${NAU8814_ADC_DIR}/nau8814_adcdiag.c)
    endif()

    if(CLI STREQUAL Y)
        if(NAU8814_CLI STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NAU8814_ADC_CLI)
            target_sources(app PRIVATE ${NAU8814_ADC_DIR}/nau8814_dac_cli.c)
        endif()
    endif()
endif()
