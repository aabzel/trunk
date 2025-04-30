message(STATUS "CONVERTOR_MK_INC=${CONVERTOR_MK_INC}")
if( NOT (CONVERTOR_MK_INC STREQUAL Y))
    set(CONVERTOR_MK_INC Y)
    message(STATUS "Add SW DAC")

    set(CONVERTOR_DIR ${COMPUTING_DIR}/convertor)
    message(STATUS "CONVERTOR_DIR=${CONVERTOR_DIR}")
    message(STATUS "CONVERTOR_DIAG=[${CONVERTOR_DIAG}]")
    message(STATUS "CONVERTOR_COMMANDS=[${CONVERTOR_COMMANDS}]")
    message(STATUS "DIAG=[${DIAG}]")

    add_compile_definitions(HAS_CONVERTOR)
    target_compile_definitions(app PUBLIC HAS_CONVERTOR)

    include_directories(${CONVERTOR_DIR})
    target_include_directories(app PUBLIC ${CONVERTOR_DIR})

    target_sources(app PRIVATE ${CONVERTOR_DIR}/convertor_drv.c)
    target_sources(app PRIVATE ${CONVERTOR_DIR}/convertor_config.c)

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
        if(CONVERTOR_DIAG STREQUAL Y)
            message(STATUS "Add CONVERTOR_DIAG")
            target_compile_definitions(app PUBLIC HAS_CONVERTOR_DIAG)
            target_sources(app PRIVATE ${CONVERTOR_DIR}/convertor_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(CONVERTOR_COMMANDS STREQUAL Y)
            message(STATUS "Add CONVERTOR chars")
            target_compile_definitions(app PUBLIC HAS_CONVERTOR_COMMANDS)
            target_sources(app PRIVATE ${CONVERTOR_DIR}/convertor_commands.c)
        endif()
	endif()

endif()



 
 
 



 