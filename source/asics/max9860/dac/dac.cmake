message(STATUS "MAX9860_DAC_MK_INC=${MAX9860_DAC_MK_INC}")
if( NOT (MAX9860_DAC_MK_INC STREQUAL Y))
    set(MAX9860_DAC_MK_INC Y)
    message(STATUS "+MAX9860_DAC")

    set(MAX9860_DAC_DIR ${MAX9860_DIR}/dac)
    message(STATUS "MAX9860_DAC_DIR=${MAX9860_DAC_DIR}")

    #add_compile_definitions(HAS_MAX9860_DAC)
    target_compile_definitions(app PUBLIC HAS_MAX9860_DAC)

    target_sources(app PRIVATE ${MAX9860_DAC_DIR}/max9860_dac_drv.c)

    target_include_directories(app PUBLIC ${MAX9860_DAC_DIR})

    if(DIAG STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_MAX9860_DAC_DIAG)
        target_sources(app PRIVATE ${MAX9860_DAC_DIR}/max9860_dac_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(MAX9860_COMMANDS STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_MAX9860_DAC_COMMANDS)
            target_sources(app PRIVATE ${MAX9860_DAC_DIR}/max9860_dac_commands.c)
        endif()
    endif()
endif()
