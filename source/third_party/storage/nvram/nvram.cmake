
message(STATUS "NVRAM_MK_INC=${NVRAM_MK_INC}")
if( NOT (NVRAM_MK_INC STREQUAL Y))
    set(NVRAM_MK_INC Y)
    message(STATUS "+NVRAM")

    set(NVRAM_DIR ${STORAGE_DIR}/nvrams)
    message(STATUS "NVRAM_DIR=${NVRAM_DIR}")
    target_include_directories(app PUBLIC ${NVRAM_DIR})

    add_compile_definitions(HAS_NVRAM)
    target_compile_definitions(app PUBLIC HAS_NVRAM)

    target_sources(app PRIVATE ${NVRAM_DIR}/NVRAM_drv.c)

    if(NVRAM_SET STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_NVRAM_SET)
    endif()

    if(DIAG STREQUAL Y)
        if(NVRAM_DIAG STREQUAL Y)
            message(STATUS "+NVRAM_DIAG")
            target_compile_definitions(app PUBLIC HAS_NVRAM_DIAG)
            target_sources(app PRIVATE ${NVRAM_DIR}/NVRAM_diag.c)
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(NVRAM_COMMANDS STREQUAL Y)
            message(STATUS "+NVRAM_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_NVRAM_COMMANDS)
            target_sources(app PRIVATE ${NVRAM_DIR}/NVRAM_commands.c)
        endif()
    endif()
	
endif()
