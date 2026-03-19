message(STATUS "COMPUTING_MK_INC=${COMPUTING_MK_INC}")
if( NOT (COMPUTING_MK_INC STREQUAL Y))
    set(COMPUTING_MK_INC Y)
    message(STATUS "+  computing")

    set(COMPUTING_DIRECTORY ${WORKSPACE_LOC}/computing)
    message(STATUS "COMPUTING_DIRECTORY=${COMPUTING_DIRECTORY}")


    target_include_directories(app PUBLIC ${COMPUTING_DIRECTORY})

    target_compile_definitions(app PUBLIC HAS_COMPUTING)
    target_compile_definitions(app PUBLIC HAS_COMPUTING_COMMANDS)


endif()
