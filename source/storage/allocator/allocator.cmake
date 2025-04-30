message(STATUS "ALLOCATOR_MK_INC=${ALLOCATOR_MK_INC}")
if( NOT (ALLOCATOR_MK_INC STREQUAL Y))
    set(ALLOCATOR_MK_INC Y)
    message(STATUS "Link Allocator")

    set(ALLOCATOR_DIR ${STORAGE_DIR}/allocator)

    target_include_directories(app PUBLIC ${ALLOCATOR_DIR})

    target_compile_definitions(app PUBLIC HAS_HEAP)
    target_compile_definitions(app PUBLIC HAS_ALLOCATOR)

    target_sources(app PRIVATE ${ALLOCATOR_DIR}/heap_allocator.c)
    if (CLI STREQUAL Y)
        if (ALLOCATOR_COMMANDS STREQUAL Y)
            message(STATUS "Link Allocator commands")
            target_compile_definitions(app PUBLIC HAS_HEAP_COMMANDS)
            target_sources(app PRIVATE ${ALLOCATOR_DIR}/allocator_commands.c)
        endif()
    endif()

    if (GARBAGE_COLLECTOR STREQUAL Y)
        message(STATUS "Link Garbage Collector commands")
        include (${STORAGE_DIR}/allocator/garbage_collector/garbage_collector.cmake)
    endif()
endif()
