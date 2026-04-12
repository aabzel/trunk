message(STATUS "HIST_FILTER_MK_INC=${HIST_FILTER_MK_INC}")
if( NOT (HIST_FILTER_MK_INC  STREQUAL  Y))
    set(HIST_FILTER_MK_INC Y)
    message(STATUS "+ HIST_FILTER")

    set(HIST_FILTER_DIR ${ROOT_DIR}/hist_filter)
    message(STATUS "HIST_FILTER_DIR=${HIST_FILTER_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_HIST_FILTER)
    target_compile_definitions(app PUBLIC HAS_HIST_FILTER)
    target_compile_definitions(app PUBLIC HAS_HIST_FILTER_PROC)

    target_include_directories(app PUBLIC ${HIST_FILTER_DIR})
    target_sources(app PRIVATE ${HIST_FILTER_DIR}/hist_filter.c)

    if(DIAG  STREQUAL  Y)
        if(HIST_FILTER_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_HIST_FILTER_DIAG)
            target_sources(app PRIVATE ${HIST_FILTER_DIR}/hist_filter_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(HIST_FILTER_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_HIST_FILTER_COMMANDS)
            target_sources(app PRIVATE ${HIST_FILTER_DIR}/hist_filter_commands.c)
        endif()
    endif()
endif()
