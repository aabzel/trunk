message(STATUS "SW_NVRAM_MK_INC=${SW_NVRAM_MK_INC}")
if( NOT (SW_NVRAM_MK_INC  STREQUAL Y))
    set(SW_NVRAM_MK_INC Y)
    message(STATUS "Add SW NVRAM")

    set(SW_NVRAM_DIR ${STORAGE_DIR}/sw_nvram)
    message(STATUS "SW_NVRAM_DIR=${SW_NVRAM_DIR}")
    message(STATUS "SW_NVRAM_DIAG=[${SW_NVRAM_DIAG}]")
    message(STATUS "SW_NVRAM_COMMANDS=[${SW_NVRAM_COMMANDS}]")
    message(STATUS "DIAG=[${DIAG}]")

    add_compile_definitions(HAS_SW_NVRAM)
    target_compile_definitions(app PUBLIC HAS_SW_NVRAM)

    include_directories(${SW_NVRAM_DIR})
    target_include_directories(app PUBLIC ${SW_NVRAM_DIR})

    target_sources(app PRIVATE ${SW_NVRAM_DIR}/sw_nvram_drv.c)
    target_sources(app PRIVATE ${SW_NVRAM_DIR}/sw_nvram_config.c)

    if(DIAG  STREQUAL Y)
        if(SW_NVRAM_DIAG  STREQUAL Y)
            message(STATUS "Add SW_NVRAM_DIAG")
            target_compile_definitions(app PUBLIC HAS_SW_NVRAM_DIAG)
            target_sources(app PRIVATE ${SW_NVRAM_DIR}/sw_nvram_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL Y)
        if(SW_NVRAM_COMMANDS  STREQUAL Y)
            message(STATUS "Add SW_NVRAM chars")
            target_compile_definitions(app PUBLIC HAS_SW_NVRAM_COMMANDS)
            target_sources(app PRIVATE ${SW_NVRAM_DIR}/sw_nvram_commands.c)
        endif()
	endif()

endif()



 
 
 



 