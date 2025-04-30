message(STATUS "GRAPHIC_DISPLAY_SIMULATOR_MK_INC=${GRAPHIC_DISPLAY_SIMULATOR_MK_INC}")
if( NOT (GRAPHIC_DISPLAY_SIMULATOR_MK_INC  STREQUAL  Y))
    set(GRAPHIC_DISPLAY_SIMULATOR_MK_INC Y)
    message(STATUS "+ GRAPHIC_DISPLAY_SIMULATOR")

    set(GRAPHIC_DISPLAY_SIMULATOR_DIR ${DRIVERS_DIR}/graphic_display_simulator)
    message(STATUS "GRAPHIC_DISPLAY_SIMULATOR_DIR=${GRAPHIC_DISPLAY_SIMULATOR_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_GRAPHIC_DISPLAY_SIMULATOR)
    target_compile_definitions(app PUBLIC HAS_GRAPHIC_DISPLAY_SIMULATOR)

    target_include_directories(app PUBLIC ${GRAPHIC_DISPLAY_SIMULATOR_DIR})
    target_sources(app PRIVATE ${GRAPHIC_DISPLAY_SIMULATOR_DIR}/graphic_display_simulator_drv.c)

    if(DIAG  STREQUAL  Y)
        if(GRAPHIC_DISPLAY_SIMULATOR_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GRAPHIC_DISPLAY_SIMULATOR_DIAG)
            target_sources(app PRIVATE ${GRAPHIC_DISPLAY_SIMULATOR_DIR}/graphic_display_simulator_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(GRAPHIC_DISPLAY_SIMULATOR_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_GRAPHIC_DISPLAY_SIMULATOR_COMMANDS)
            target_sources(app PRIVATE ${GRAPHIC_DISPLAY_SIMULATOR_DIR}/graphic_display_simulator_commands.c)
        endif()
    endif()
endif()
