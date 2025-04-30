
if( NOT (MICROCONTROLLER_MK_INC STREQUAL Y))
    set(MICROCONTROLLER_MK_INC Y)

    set(MICROCONTROLLER_DIR ${WORKSPACE_LOC}/microcontroller)
    message(STATUS "Link MCU")
    message(STATUS "MICROCONTROLLER_DIR=${MICROCONTROLLER_DIR}")

    target_compile_definitions(app PUBLIC HAS_MICROCONTROLLER)
    target_include_directories(app PUBLIC ${MICROCONTROLLER_DIR})

    if(NRF5340 STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/nRF5340/nrf5340.cmake)
    endif()

endif()