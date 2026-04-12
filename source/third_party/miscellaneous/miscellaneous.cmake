message(STATUS "MISCELLANEOUS_MK_INC=${MISCELLANEOUS_MK_INC}")
if( NOT (MISCELLANEOUS_MK_INC STREQUAL Y))
    set(MISCELLANEOUS_MK_INC Y)

    set(DATA_POC Y)
    set(FLOAT_MISCELLANEOUS Y)

    message(STATUS "+ Utils/miscellaneous")

    set(MISCELLANEOUS_DIR ${WORKSPACE_LOC}/utils)
    message(STATUS "MISCELLANEOUS_DIR=${MISCELLANEOUS_DIR}")
    add_compile_definitions(HAS_MISCELLANEOUS)

    include_directories(${MISCELLANEOUS_DIR})
    target_include_directories(app PUBLIC ${MISCELLANEOUS_DIR})
    target_compile_definitions(app PUBLIC HAS_ARRAY)
    target_compile_definitions(app PUBLIC HAS_MISCELLANEOUS)
    target_compile_definitions(app PUBLIC HAS_BIT_SWAP)

    target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/float_utils.c)

    if (DATA_POC STREQUAL Y)
        message(STATUS "+ DataUtils")
        target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/data_utils.c)
        target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/byte_utils.c)
        target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/bit_utils.c)
        target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/physics_utils.c)
    endif()

    if (FLOAT_MISCELLANEOUS STREQUAL Y)
        message(STATUS "+ FloatUtils")
        target_compile_definitions(app PUBLIC HAS_FLOAT_MISCELLANEOUS)
        target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/float_utils.c)
    endif()

    if (LOG STREQUAL Y)
        message(STATUS "+ DebugInfo")
        target_sources(app PRIVATE ${MISCELLANEOUS_DIR}/debug_info.c)
    endif()

endif()