message(STATUS "BOARD_INFO_MK_INC=${BOARD_INFO_MK_INC}")
if( NOT (BOARD_INFO_MK_INC STREQUAL Y))
    set(BOARD_INFO_MK_INC Y)

    message(STATUS "+ BOARD_INFO")

    set(BOARD_INFO_DIR ${COMPONENTS_DIR}/board_info)
    message(STATUS "BOARD_INFO_DIR=${BOARD_INFO_DIR}")

    target_compile_definitions(app PUBLIC HAS_BOARD_INFO)

    if(DIAG STREQUAL Y)
        if(BOARD_INFO_DIAG STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_BOARD_INFO_DIAG)
            target_sources(app PRIVATE ${BOARD_INFO_DIR}/board_diag.c)
        endif()
    endif()

    target_sources(app PRIVATE ${BOARD_INFO_DIR}/board_info.c)

    #include_directories(${BOARD_INFO_DIR})
    target_include_directories(app PUBLIC ${BOARD_INFO_DIR})
endif()

