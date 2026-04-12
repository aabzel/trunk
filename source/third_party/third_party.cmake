message(STATUS "THIRD_PARTY_MK_INC=${THIRD_PARTY_MK_INC}")
if( NOT (THIRD_PARTY_MK_INC STREQUAL Y))
    set(THIRD_PARTY_MK_INC Y)

    set(THIRD_PARTY_DIR  ${WORKSPACE_LOC}/third_party)
    message(STATUS "THIRD_PARTY_DIR=${THIRD_PARTY_DIR}")
    # $(error THIRD_PARTY_DIR= ${THIRD_PARTY_DIR})
    add_compile_definitions(HAS_THIRD_PARTY)

    include_directories(${THIRD_PARTY_DIR})
    #string(APPEND INCDIR " ${THIRD_PARTY_DIR}")

    if(VENDOR_SDK STREQUAL Y)
        include(${THIRD_PARTY_DIR}/sdk/sdk.cmake)
    endif()

    if(COMPUTING STREQUAL Y)
        # $(error COMPUTING=$(COMPUTING))
        include(${THIRD_PARTY_DIR}/computing/computing.cmake)
    endif()



    if(THIRD_PARTY_ADT STREQUAL Y)
        # $(error THIRD_PARTY_ADT=$(THIRD_PARTY_ADT))
        include(${THIRD_PARTY_DIR}/adt/adt.cmake)
    endif()

    if(THIRD_PARTY_ASICS STREQUAL Y)
        # $(error THIRD_PARTY_ASICS=$(THIRD_PARTY_ASICS))
        include(${THIRD_PARTY_DIR}/asics/asics.cmake)
    endif()
    
    if(THIRD_PARTY_CONNECTIVITY STREQUAL Y)
        # $(error THIRD_PARTY_CONNECTIVITY=$(THIRD_PARTY_CONNECTIVITY))
        include(${THIRD_PARTY_DIR}/connectivity/connectivity.cmake)
    endif()

    if(THIRD_PARTY_COMPUTING STREQUAL Y)
        # $(error THIRD_PARTY_COMPUTING=$(THIRD_PARTY_COMPUTING))
        include(${THIRD_PARTY_DIR}/computing/computing.cmake)
    endif()

    if(THIRD_PARTY_SENSITIVITY STREQUAL Y)
        # $(error THIRD_PARTY_SENSITIVITY=$(THIRD_PARTY_SENSITIVITY))
        include(${THIRD_PARTY_DIR}/sensitivity/sensitivity.cmake)
    endif()

    if(THIRD_PARTY_STORAGE STREQUAL Y)
        # $(error THIRD_PARTY_STORAGE=$(THIRD_PARTY_STORAGE))
        include(${THIRD_PARTY_DIR}/storage/storage.cmake)
    endif()

    if(THIRD_PARTY_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_THIRD_PARTY_COMMANDS")
    endif()

    if(THIRD_PARTY_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_THIRD_PARTY_DIAG")
        set(SOURCES_THIRD_PARTY_C "${SOURCES_THIRD_PARTY_C} ${THIRD_PARTY_DIR}/third_party_diag.c")
    endif()

endif()
