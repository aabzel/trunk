
message(STATUS "NVS_MK_INC=${NVS_MK_INC}")
if( NOT (Y STREQUAL NVS_MK_INC))
    set(NVS_MK_INC Y)
    message(STATUS "+ NVS General")

    set(NVS_DIR ${MCAL_COMMON_DIR}/nvs)
    message(STATUS "NVS_DIR=${NVS_DIR}")
    #include_directories(${NVS_DIR})
    target_include_directories(app PUBLIC ${NVS_DIR})

    #add_compile_definitions(HAS_NVS)

    target_compile_definitions(app PUBLIC HAS_NVS)
    target_sources(app PRIVATE ${NVS_DIR}/nvs_general_drv.c)
    
    if(NVS_WRITE STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_NVS_WRITE)
    endif()
    

    if(NVS_DIAG STREQUAL Y)
        message(STATUS "+ NVS diagnostic")
        target_compile_definitions(app PUBLIC HAS_NVS_DIAG)
        target_sources(app PRIVATE ${NVS_DIR}/nvs_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(NVS_COMMANDS STREQUAL Y)
            message(STATUS "+ NVS Commands")
            target_compile_definitions(app PUBLIC HAS_NVS_COMMANDS)
            target_sources(app PRIVATE ${NVS_DIR}/nvs_commands.c)
        endif()
    endif()
endif()