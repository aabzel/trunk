message(STATUS "UWB_MK_INC=${UWB_MK_INC}")
if( NOT (UWB_MK_INC STREQUAL Y))
    set(UWB_MK_INC Y)
    set(UWB_DIR ${INTERFACES_DIR}/uwb)

    message(STATUS "+ UWB")

    target_include_directories(app PUBLIC ${UWB_DIR})
    #target_compile_definitions(app PUBLIC HAS_UWB_PROC)
    target_compile_definitions(app PUBLIC HAS_UWB)

    target_sources(app PRIVATE ${UWB_DIR}/uwb_if.c)

    if (DIAG STREQUAL Y)
        if (UWB_DIAG STREQUAL Y)
            message(STATUS "+ UWB_DIAG")
            target_compile_definitions(app PUBLIC HAS_UWB_DIAG)
            target_sources(app PRIVATE ${UWB_DIR}/uwb_diag.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (UWB_COMMANDS STREQUAL Y)
            message(STATUS "+ UWB_COMMANDS")
            target_compile_definitions(app PUBLIC HAS_UWB_COMMANDS)
        endif()
    endif()
endif()
