message(STATUS "UTILS_MK_INC=${UTILS_MK_INC}")
if( NOT (UTILS_MK_INC STREQUAL Y))
    set(UTILS_MK_INC Y)

    set(DATA_POC Y)
    set(FLOAT_UTILS Y)

    message(STATUS "+ Utils/miscellaneous")

    set(UTILS_DIR ${WORKSPACE_LOC}/utils)
    message(STATUS "UTILS_DIR=${UTILS_DIR}")
    add_compile_definitions(HAS_UTILS)

    include_directories(${UTILS_DIR})
    target_include_directories(app PUBLIC ${UTILS_DIR})
    target_compile_definitions(app PUBLIC HAS_ARRAY)
    target_compile_definitions(app PUBLIC HAS_UTILS)
    target_compile_definitions(app PUBLIC HAS_BIT_SWAP)

    target_sources(app PRIVATE ${UTILS_DIR}/float_utils.c)

    if (DATA_POC STREQUAL Y)
        message(STATUS "+ DataUtils")
        target_sources(app PRIVATE ${UTILS_DIR}/data_utils.c)
        target_sources(app PRIVATE ${UTILS_DIR}/byte_utils.c)
        target_sources(app PRIVATE ${UTILS_DIR}/bit_utils.c)
        target_sources(app PRIVATE ${UTILS_DIR}/physics_utils.c)
    endif()

    if (FLOAT_UTILS STREQUAL Y)
        message(STATUS "+ FloatUtils")
        target_compile_definitions(app PUBLIC HAS_FLOAT_UTILS)
        target_sources(app PRIVATE ${UTILS_DIR}/float_utils.c)
    endif()

    if (LOG STREQUAL Y)
        message(STATUS "+ DebugInfo")
        target_sources(app PRIVATE ${UTILS_DIR}/debug_info.c)
    endif()

endif()