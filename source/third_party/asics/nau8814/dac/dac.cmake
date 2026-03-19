message(STATUS "NAU8814_DAC_MK_INC=${NAU8814_DAC_MK_INC}")
if( NOT (NAU8814_DAC_MK_INC STREQUAL Y))
    set(NAU8814_DAC_MK_INC Y)
    message(STATUS "+NAU8814_DAC")

    set(NAU8814_DAC_DIR ${NAU8814_DIR}/dac)
    message(STATUS "NAU8814_DAC_DIR=${NAU8814_DAC_DIR}")

    #add_compile_definitions(HAS_NAU8814_DAC)
    target_compile_definitions(app PUBLIC HAS_NAU8814_DAC)

    target_sources(app PRIVATE ${NAU8814_DAC_DIR}/NAU8814_dac.c)

    target_include_directories(app PUBLIC ${NAU8814_DAC_DIR})

    if(DIAG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_NAU8814_DAC_DIAG)
        target_sources(app PRIVATE ${NAU8814_DAC_DIR}/NAU8814_dac_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(NAU8814_CLI STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_NAU8814_DAC_CLI)
            target_sources(app PRIVATE ${NAU8814_DAC_DIR}/nau8814_dac_cli.c)
        endif()
    endif()
endif()
