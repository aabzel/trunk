
if(NOT (UTILS_MK_INC STREQUAL Y))
    set(UTILS_MK_INC Y)

    set(MISCELLANEOUS_DIR "${WORKSPACE_LOC}/miscellaneous")

    include_directories(${MISCELLANEOUS_DIR})
    string(APPEND MCAL_OPT " -DHAS_REPLACE_FORMATTER_CHARACTERS")
    string(APPEND MCAL_OPT " -DHAS_BIT_SWAP")
    string(APPEND MCAL_OPT " -DHAS_MISCELLANEOUS")
    string(APPEND MCAL_OPT " -DHAS_MISC")

    if(BIT_UTILS STREQUAL Y)
        include(${MISCELLANEOUS_DIR}/bit_utils/bit_utils.cmake)
    endif()

    if(UTILS_EXT STREQUAL Y)
        include(${MISCELLANEOUS_DIR}/byte_misc/byte_misc.cmake)
    endif()

    if(DATA_UTILS_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_DATA_UTILS_EXT")
    endif()

    if(DATA_MISC STREQUAL Y)
        include(${MISCELLANEOUS_DIR}/data_misc/data_misc.cmake)
    endif()

    if(UTILS_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_UTILS_EXT")
        string(APPEND SOURCES_C " ${MISCELLANEOUS_DIR}/helper.c")
    endif()

    if(PHYSICS STREQUAL Y)
        include(${MISCELLANEOUS_DIR}/physics/physics.cmake)
    endif()

    if(FLOAT STREQUAL Y)
        include(${MISCELLANEOUS_DIR}/float_utils/float_utils.cmake)
    endif()

    if(TEST_FIRMWARE STREQUAL Y)
        set(WRITE_ADDR Y)
    endif()

    if(STREAM STREQUAL Y)
        string(APPEND SOURCES_C " ${MISCELLANEOUS_DIR}/debug_info.c")
    endif()
endif()
