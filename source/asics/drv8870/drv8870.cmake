message(STATUS "DRV8870_MK_INC=${DRV8870_MK_INC}")
if( NOT (DRV8870_MK_INC  STREQUAL  Y))
    set(DRV8870_MK_INC Y)
    message(STATUS "+ DRV8870")

    set(DRV8870_DIR ${ROOT_DIR}/drv8870)
    message(STATUS "DRV8870_DIR=${DRV8870_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_DRV8870)
    target_compile_definitions(app PUBLIC HAS_DRV8870)
    target_compile_definitions(app PUBLIC HAS_DRV8870_PROC)

    target_include_directories(app PUBLIC ${DRV8870_DIR})
    target_sources(app PRIVATE ${DRV8870_DIR}/drv8870.c)

    if(DIAG  STREQUAL  Y)
        if(DRV8870_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DRV8870_DIAG)
            target_sources(app PRIVATE ${DRV8870_DIR}/drv8870_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(DRV8870_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DRV8870_COMMANDS)
            target_sources(app PRIVATE ${DRV8870_DIR}/drv8870_commands.c)
        endif()
    endif()
endif()
