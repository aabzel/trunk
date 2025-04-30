message(STATUS "FIFO_MK_INC=[${FIFO_MK_INC}]")
if( NOT (FIFO_MK_INC STREQUAL Y))
    set(FIFO_MK_INC Y)
    message(STATUS "Link FIFO")

    set(FIFO_DIR ${ADT_DIR}/fifo)
    message(STATUS "FIFO_DIR=${FIFO_DIR}")

    add_compile_definitions(HAS_FIFO)
    target_compile_definitions(app PUBLIC HAS_FIFO)
    
    include_directories(${FIFO_DIR})
    target_include_directories(app PUBLIC ${FIFO_DIR})

    if(FIFO_INDEX STREQUAL Y)
        message(STATUS "Link FIFO indexer")
        target_compile_definitions(app PUBLIC HAS_FIFO_INDEX)
        target_sources(app PRIVATE ${FIFO_DIR}/fifo_index.c)
    endif()

    if(FIFO_ARRAY STREQUAL Y)
        message(STATUS "Link FIFO arrays")
        target_compile_definitions(app PUBLIC HAS_FIFO_ARRAY)
        target_sources(app PRIVATE ${FIFO_DIR}/fifo_array.c)
    endif()
    
    if(FIFO_CHAR STREQUAL Y)
        message(STATUS "Link FIFO chars")
        target_compile_definitions(app PUBLIC HAS_FIFO_CHAR)
        target_sources(app PRIVATE ${FIFO_DIR}/fifo_char.c)
    endif()

endif()
