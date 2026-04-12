message(STATUS "SW_COMPONENT_MK_INC=${SW_COMPONENT_MK_INC}")
if( NOT (SW_COMPONENT_MK_INC  STREQUAL  Y))
    set(SW_COMPONENT_MK_INC Y)
    message(STATUS "+ SW_COMPONENT")

    set(SW_COMPONENT_DIR ${ROOT_DIR}/sw_component)
    message(STATUS "SW_COMPONENT_DIR=${SW_COMPONENT_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_SW_COMPONENT)
    target_compile_definitions(app PUBLIC HAS_SW_COMPONENT)
    target_compile_definitions(app PUBLIC HAS_SW_COMPONENT_PROC)

    target_include_directories(app PUBLIC ${SW_COMPONENT_DIR})
    target_sources(app PRIVATE ${SW_COMPONENT_DIR}/sw_component.c)

    if(DIAG  STREQUAL  Y)
        if(SW_COMPONENT_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SW_COMPONENT_DIAG)
            target_sources(app PRIVATE ${SW_COMPONENT_DIR}/sw_component_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(SW_COMPONENT_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_SW_COMPONENT_COMMANDS)
            target_sources(app PRIVATE ${SW_COMPONENT_DIR}/sw_component_commands.c)
        endif()
    endif()
endif()
