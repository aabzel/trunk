message(STATUS "DC_CUT_FILTER_MK_INC=${DC_CUT_FILTER_MK_INC}")
if( NOT (DC_CUT_FILTER_MK_INC  STREQUAL  Y))
    set(DC_CUT_FILTER_MK_INC Y)
    message(STATUS "+ DC_CUT_FILTER")

    set(DC_CUT_FILTER_DIR ${ROOT_DIR}/dc_cut_filter)
    message(STATUS "DC_CUT_FILTER_DIR=${DC_CUT_FILTER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_DC_CUT_FILTER)
    target_compile_definitions(app PUBLIC HAS_DC_CUT_FILTER)
    target_compile_definitions(app PUBLIC HAS_DC_CUT_FILTER_PROC)

    target_include_directories(app PUBLIC ${DC_CUT_FILTER_DIR})
    target_sources(app PRIVATE ${DC_CUT_FILTER_DIR}/dc_cut_filter.c)

    if(DIAG  STREQUAL  Y)
        if(DC_CUT_FILTER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DC_CUT_FILTER_DIAG)
            target_sources(app PRIVATE ${DC_CUT_FILTER_DIR}/dc_cut_filter_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(DC_CUT_FILTER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_DC_CUT_FILTER_COMMANDS)
            target_sources(app PRIVATE ${DC_CUT_FILTER_DIR}/dc_cut_filter_commands.c)
        endif()
    endif()
endif()
