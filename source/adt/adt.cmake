message(STATUS "ADT_CMAKE_INC=${ADT_CMAKE_INC}")
if( NOT (ADT_CMAKE_INC STREQUAL Y))
    set(ADT_CMAKE_INC Y)
    message(STATUS "+ ADT")

    set(ADT_DIR ${WORKSPACE_LOC}/adt)
    message(STATUS "ADT_DIR=${ADT_DIR}")
    include_directories(${ADT_DIR})

    target_compile_definitions(app PUBLIC HAS_ADT)

    target_sources(app PRIVATE ${ADT_DIR}/adt_proc.c)

    if (ADT_COMMANDS STREQUAL Y)
        target_compile_definitions(app PUBLIC HAS_ADT_COMMANDS)
    endif()

    if (ARRAY STREQUAL Y)
        message(STATUS "+ array driver")
        include(${ADT_DIR}/array/array.cmake)
    endif()

    if (SET STREQUAL Y)
        message(STATUS "+ ADT Set")
        include(${ADT_DIR}/set/set.cmake)
    endif()

    if (CIRCULAR_BUFFER STREQUAL Y)
        include(${ADT_DIR}/circular_buffer/circular_buffer.cmake)
    endif()

    if (FIFO STREQUAL Y)
        include(${ADT_DIR}/fifo/fifo.cmake)
    endif()

    if (HASHSET STREQUAL Y)
        include(${ADT_DIR}/hashset/hashset.cmake)
    endif()

    if (LIFO STREQUAL Y)
        include(${ADT_DIR}/lifo/lifo.cmake)
    endif()

endif()