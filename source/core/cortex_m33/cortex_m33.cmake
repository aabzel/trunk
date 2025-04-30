message(STATUS "CORTEX_M33_CMK_INC=${CORTEX_M33_CMK_INC}")
if( NOT (Y STREQUAL CORTEX_M33_CMK_INC))
    set(CORTEX_M33_CMK_INC Y)
    message(STATUS "+ ARM Cortex-M33")

    set(CORTEX_M33_DIR ${CORE_DIR}/cortex_m33)
    message(STATUS "CORTEX_M33_DIR=${CORTEX_M33_DIR}")

    add_compile_definitions(HAS_NRF5340)
    target_compile_definitions(app PUBLIC HAS_NRF5340)
    target_compile_definitions(app PUBLIC NRFX_CUSTOM_ERROR_CODES=1)

    include_directories(${CORTEX_M33_DIR})
    target_include_directories(app PUBLIC ${CORTEX_M33_DIR})

    if(NVIC STREQUAL Y)
        message(STATUS "+ NVIC")
        include(${CORTEX_M33_DIR}/nvic/nvic.cmake)
    endif()
endif()
