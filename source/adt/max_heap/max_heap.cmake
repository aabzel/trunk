message(STATUS "MAX_HEAP_MK_INC=${MAX_HEAP_MK_INC}")
if( NOT (MAX_HEAP_MK_INC  STREQUAL  Y))
    set(MAX_HEAP_MK_INC Y)
    message(STATUS "+ MAX_HEAP")

    set(MAX_HEAP_DIR ${ROOT_DIR}/max_heap)
    message(STATUS "MAX_HEAP_DIR=${MAX_HEAP_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_MAX_HEAP)
    target_compile_definitions(app PUBLIC HAS_MAX_HEAP)
    target_compile_definitions(app PUBLIC HAS_MAX_HEAP_PROC)

    target_include_directories(app PUBLIC ${MAX_HEAP_DIR})
    target_sources(app PRIVATE ${MAX_HEAP_DIR}/max_heap.c)

    if(DIAG  STREQUAL  Y)
        if(MAX_HEAP_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MAX_HEAP_DIAG)
            target_sources(app PRIVATE ${MAX_HEAP_DIR}/max_heap_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(MAX_HEAP_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MAX_HEAP_COMMANDS)
            target_sources(app PRIVATE ${MAX_HEAP_DIR}/max_heap_commands.c)
        endif()
    endif()
endif()
