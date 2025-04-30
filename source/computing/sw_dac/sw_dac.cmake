message(STATUS "SW_DAC_MK_INC=${SW_DAC_MK_INC}")
if( NOT (SW_DAC_MK_INC STREQUAL Y))
    set(SW_DAC_MK_INC Y)
    message(STATUS "Add SW DAC")

    set(SW_DAC_DIR ${COMPUTING_DIR}/sw_dac)
    message(STATUS "SW_DAC_DIR=${SW_DAC_DIR}")
    message(STATUS "SW_DAC_DIAG=[${SW_DAC_DIAG}]")
    message(STATUS "SW_DAC_COMMANDS=[${SW_DAC_COMMANDS}]")
    message(STATUS "DIAG=[${DIAG}]")

    add_compile_definitions(HAS_SW_DAC)
    target_compile_definitions(app PUBLIC HAS_SW_DAC)

    include_directories(${SW_DAC_DIR})
    target_include_directories(app PUBLIC ${SW_DAC_DIR})

    target_sources(app PRIVATE ${SW_DAC_DIR}/sw_dac_drv.c)
    target_sources(app PRIVATE ${SW_DAC_DIR}/sw_dac_config.c)

    if(PCM_16_BIT STREQUAL Y)
        message(STATUS "PCM_16_BIT")
        target_compile_definitions(app PUBLIC PCM_SAMPLE_SIZE=2)
        target_compile_definitions(app PUBLIC HAS_PCM_16_BIT)
    endif()

    if(PCM_32_BIT STREQUAL Y)
        message(STATUS "PCM_32_BIT")
        target_compile_definitions(app PUBLIC PCM_SAMPLE_SIZE=4)
        target_compile_definitions(app PUBLIC HAS_PCM_32_BIT)
    endif()

    if(DIAG STREQUAL Y)
        if(SW_DAC_DIAG STREQUAL Y)
            message(STATUS "Add SW_DAC_DIAG")
            target_compile_definitions(app PUBLIC HAS_SW_DAC_DIAG)
            target_sources(app PRIVATE ${SW_DAC_DIR}/sw_dac_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(SW_DAC_COMMANDS STREQUAL Y)
            message(STATUS "Add SW_DAC chars")
            target_compile_definitions(app PUBLIC HAS_SW_DAC_COMMANDS)
            target_sources(app PRIVATE ${SW_DAC_DIR}/sw_dac_commands.c)
        endif()
	endif()

endif()



 
 
 



 