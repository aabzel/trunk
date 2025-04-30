message(STATUS "COMPUTING_MK_INC=${COMPUTING_MK_INC}")
if( NOT (COMPUTING_MK_INC STREQUAL Y))
    set(COMPUTING_MK_INC Y)
    message(STATUS "+  computing")

    set(COMPUTING_DIR ${WORKSPACE_LOC}/computing)
    message(STATUS "COMPUTING_DIR=${COMPUTING_DIR}")

    include(${COMPUTING_DIR}/interval/interval.cmake)

    target_include_directories(app PUBLIC ${COMPUTING_DIR})

    target_compile_definitions(app PUBLIC HAS_COMPUTING)
    target_compile_definitions(app PUBLIC HAS_COMPUTING_COMMANDS)

    if(CRC STREQUAL Y)
        #message(SEND_ERROR "CRC=${CRC}")
        include(${COMPUTING_DIR}/crc/crc.cmake)
    endif()

    if(LIMITER STREQUAL Y)
        #message(SEND_ERROR "LIMITER=${LIMITER}")
        include(${COMPUTING_DIR}/limiter/limiter.cmake)
    endif()

    if(MATH STREQUAL Y)
        include(${COMPUTING_DIR}/math/math.cmake)
    endif()

    if(SCHMITT_TRIGGER STREQUAL Y)
        message(STATUS "+  SCHMITT_TRIGGER")
        include(${COMPUTING_DIR}/schmitt_trigger/schmitt_trigger.cmake)
    endif()
    
    if(SW_DAC STREQUAL Y)
        message(STATUS "+  SW_DAC")
        include(${COMPUTING_DIR}/sw_dac/sw_dac.cmake)
    endif()

    if(STRING STREQUAL Y)
        include(${COMPUTING_DIR}/string/string.cmake)
    endif()
    

endif()
