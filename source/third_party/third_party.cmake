
message(STATUS "THIRD_PARTY_MK_INC=${THIRD_PARTY_MK_INC}")
if( NOT (THIRD_PARTY_MK_INC STREQUAL Y))
    set(THIRD_PARTY_MK_INC Y)
    message(STATUS "+ THIRD_PARTY")
    set(THIRD_PARTY_DIR ${WORKSPACE_LOC}/third_party)
    message(STATUS "THIRD_PARTY_DIR=${THIRD_PARTY_DIR}")

    include_directories(${THIRD_PARTY_DIR})

    if (DECADRIVER STREQUAL Y)
        message(STATUS "+ decadriver original driver")
        include(${THIRD_PARTY_DIR}/decadriver/decadriver.cmake)
    endif()
endif()