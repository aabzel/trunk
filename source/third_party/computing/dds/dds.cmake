message(STATUS "DDS_MK_INC=${DDS_MK_INC}")
if( NOT (DDS_MK_INC STREQUAL Y))
    set(DDS_MK_INC Y)
    message(STATUS "Add SW DAC")

    set(DDS_DIR ${COMPUTING_DIRECTORY}/dds)
    message(STATUS "DDS_DIR=${DDS_DIR}")
    message(STATUS "DDS_DIAG=[${DDS_DIAG}]")
    message(STATUS "DDS_CLI=[${DDS_CLI}]")
    message(STATUS "DIAG=[${DIAG}]")

    add_compile_definitions(DDS_IN_USE)
    target_compile_definitions(app PUBLIC DDS_IN_USE)

    include_directories(${DDS_DIR})
    target_include_directories(app PUBLIC ${DDS_DIR})

    target_sources(app PRIVATE ${DDS_DIR}/dds.c)
    target_sources(app PRIVATE ${DDS_DIR}/dds_configuration.c)

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
        if(DDS_DIAG STREQUAL Y)
            message(STATUS "Add DDS_DIAG")
            target_compile_definitions(app PUBLIC DDS_IN_USE_DIAG)
            target_sources(app PRIVATE ${DDS_DIR}/DDS_Diagnostic.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(DDS_CLI STREQUAL Y)
            message(STATUS "Add DDS chars")
            target_compile_definitions(app PUBLIC DDS_CLI_IN_USE)
            target_sources(app PRIVATE ${DDS_DIR}/DDS_commands.c)
        endif()
	endif()

endif()



 
 
 



 