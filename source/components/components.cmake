message(STATUS "COMPONENTS_MK_INC=${COMPONENTS_MK_INC}")
if( NOT (COMPONENTS_MK_INC STREQUAL Y))
    set(COMPONENTS_MK_INC Y)
    message(STATUS "+ Components")

    set(COMPONENTS_DIR ${WORKSPACE_LOC}/components)
    message(STATUS "COMPONENTS_DIR=${COMPONENTS_DIR}")

    if(AUDIO STREQUAL Y)
        message(STATUS "+  AUDIO")
        include(${COMPONENTS_DIR}/audio/audio.cmake)
    endif()

    if(BOARD_INFO STREQUAL Y)
        message(STATUS "+  BOARD_INFO")
        include(${COMPONENTS_DIR}/board_info/board_info.cmake)
    endif()

endif()
