message(STATUS "MIN_HEAP_MK_INC=${MIN_HEAP_MK_INC}")
if( NOT (MIN_HEAP_MK_INC  STREQUAL  Y))
    set(MIN_HEAP_MK_INC Y)
    message(STATUS "+ MIN_HEAP")

    set(MIN_HEAP_DIR ${ROOT_DIR}/min_heap)
    message(STATUS "MIN_HEAP_DIR=${MIN_HEAP_DIR}")

    #message( SEND_ERROR "Check Compile")

    add_compile_definitions(HAS_MIN_HEAP)
    target_compile_definitions(app PUBLIC HAS_MIN_HEAP)
    target_compile_definitions(app PUBLIC HAS_MIN_HEAP_PROC)

    target_include_directories(app PUBLIC ${MIN_HEAP_DIR})
    target_sources(app PRIVATE ${MIN_HEAP_DIR}/min_heap.c)

    if(DIAG  STREQUAL  Y)
        if(MIN_HEAP_DIAG  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MIN_HEAP_DIAG)
            target_sources(app PRIVATE ${MIN_HEAP_DIR}/min_heap_diag.c)
        endif()
    endif()

    if(CLI  STREQUAL  Y)
        if(MIN_HEAP_COMMANDS  STREQUAL  Y)
            target_compile_definitions(app PUBLIC HAS_MIN_HEAP_COMMANDS)
            target_sources(app PRIVATE ${MIN_HEAP_DIR}/min_heap_commands.c)
        endif()
    endif()
endif()
