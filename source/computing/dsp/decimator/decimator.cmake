message(STATUS "DECIMATOR_MK_INC=${DECIMATOR_MK_INC}")
if( NOT (DECIMATOR_MK_INC  STREQUAL Y))
    set(DECIMATOR_MK_INC Y)

    message(STATUS "+ Decimator driver")

    set(DECIMATOR_DIR  ${COMPUTING_DIR}/decimator)

    add_compile_definitions(HAS_DECIMATOR)
    target_compile_definitions(app PUBLIC HAS_DECIMATOR)

    target_include_directories(app PUBLIC ${DECIMATOR_DIR})
    target_sources(app PRIVATE ${DECIMATOR_DIR}/decimator.c)

    if(DIAG  STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_DECIMATOR_DIAG)
        target_sources(app PRIVATE ${DECIMATOR_DIR}/decimator_diag.c)
    endif()

    if(CLI STREQUAL Y)
        if(DECIMATOR_COMMANDS  STREQUAL Y)
            target_compile_definitions(app PUBLIC HAS_DECIMATOR_COMMANDS)
            target_sources(app PRIVATE ${DECIMATOR_DIR}/decimator_commands.c)
        endif()
    endif()
endif()