message(STATUS "CONNECTIVITY_MK_INC=${CONNECTIVITY_MK_INC}")
if( NOT (CONNECTIVITY_MK_INC STREQUAL Y))
    set(CONNECTIVITY_MK_INC Y)
    message(STATUS "+  connectivity")

    set(CONNECTIVITY_DIR ${WORKSPACE_LOC}/connectivity)
    message(STATUS "CONNECTIVITY_DIR=${CONNECTIVITY_DIR}")
    target_include_directories(app PUBLIC ${CONNECTIVITY_DIR})
    message(STATUS "INTERFACES=${INTERFACES}")
    message(STATUS "PROTOCOLS=${PROTOCOLS}")
    target_compile_definitions(app PUBLIC HAS_CONNECTIVITY)

    if(LOG STREQUAL Y)
        include(${CONNECTIVITY_DIR}/log/log.cmake)
    endif()

    if(INTERFACES STREQUAL Y)
        include(${CONNECTIVITY_DIR}/interfaces/interfaces.cmake)
    endif()

    if(PROTOCOLS STREQUAL Y)
        include(${CONNECTIVITY_DIR}/protocols/protocols.cmake)
    endif()

    target_sources(app PRIVATE ${CONNECTIVITY_DIR}/proc_connectivity.c)
    
    if(CONNECTIVITY_COMMANDS STREQUAL Y)
         message(STATUS "+ connectivity commands")
         target_compile_definitions(app PUBLIC HAS_CONNECTIVITY_COMMANDS)
         target_sources(app PRIVATE ${CONNECTIVITY_DIR}/connectivity_commands.c)
    endif()

endif()
