message(STATUS "LIMITER_CMAKE_INC=${LIMITER_CMAKE_INC}")
if( NOT (Y STREQUAL LIMITER_CMAKE_INC))
    set(LIMITER_CMAKE_INC Y)

    message(STATUS "Add Limiter")

    set(LIMITER_DIR ${COMPUTING_DIR}/limiter)
    #@echo ${error LIMITER_DIR=${LIMITER_DIR))
    target_include_directories(app PUBLIC ${LIMITER_DIR})

    target_compile_definitions(app PUBLIC HAS_LIMITER)

    target_sources(app PRIVATE ${LIMITER_DIR}/limiter.c)

    if (Y STREQUAL CLI)
        #@echo ${error LIMITER_COMMANDS=${LIMITER_COMMANDS))
        if (Y STREQUAL LIMITER_COMMANDS)
            message(STATUS "Add Limiter commands")
            target_compile_definitions(app PUBLIC HAS_LIMITER_COMMANDS)
            target_sources(app PRIVATE ${LIMITER_DIR}/limiter_commands.c)
        endif()
    endif()
endif()
