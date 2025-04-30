message(STATUS "MCAL_MK_INC=${MCAL_MK_INC}")
if( NOT (MCAL_MK_INC STREQUAL Y))
    set(MCAL_MK_INC Y)
    message(STATUS "+ MCAL")

    set(MCAL_DIR ${WORKSPACE_LOC}/mcal)
    message(STATUS "MCAL_DIR=${MCAL_DIR}")
    #add_compile_definitions(HAS_MCAL)

    target_compile_definitions(app PUBLIC HAS_MCAL)
    target_include_directories(app PUBLIC ${MCAL_DIR})

    include(${MCAL_DIR}/mcal_common/mcal_common.cmake)

    if(MCAL_ZEPHYR STREQUAL Y)
        message(STATUS "+ MCAL_ZEPHYR")
        include(${MCAL_DIR}/mcal_zephyr/mcal_zephyr.cmake)
    endif()

    if(MCAL_NRF5340 STREQUAL Y)
        message(STATUS "+ MCAL_NRF5340")
        include(${MCAL_DIR}/mcal_nrf5340/mcal_nrf5340.cmake)
    endif()
endif()
