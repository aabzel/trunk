message(STATUS "CORE_GENERAL_MK_INC=${CORE_GENERAL_MK_INC}")

if(NOT (CORE_GENERAL_MK_INC STREQUAL Y))
    set(CORE_GENERAL_MK_INC Y )

    set(CORE_DIR "${WORKSPACE_LOC}/core")
    include_directories( ${CORE_DIR})
    

    string(APPEND MCAL_OPT " -DHAS_CORE")

    string(APPEND SOURCES_C " ${CORE_DIR}/core_driver.c")
    string(APPEND SOURCES_CONFIGURATION_C " ${CORE_DIR}/core_config.c")

    if(CORE_EXT STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CORE_EXT")
    endif()

    if(RV32IMC STREQUAL Y)
        include(${CORE_DIR}/rv32imc/rv32imc.cmake)
    endif()

    if(CORTEX_M0 STREQUAL Y)
        include(${CORE_DIR}/cortex_m0/cortex_m0.cmake)
    endif()

    if(CORTEX_M3 STREQUAL Y)
        include(${CORE_DIR}/cortex_m3/cortex_m3.cmake)
    endif()

    if(CORTEX_M4 STREQUAL Y)
        include(${CORE_DIR}/cortex_m4/cortex_m4.cmake)
    endif()

    if(CORTEX_M7 STREQUAL Y)
        include(${CORE_DIR}/cortex_m7/cortex_m7.cmake)
    endif()

    if(CORTEX_M33 STREQUAL Y)
        include(${CORE_DIR}/cortex_m33/cortex_m33.cmake)
    endif()

    if(MPU STREQUAL Y)
        include(${CORE_DIR}/mpu/cortex_mpu.cmake)
    endif()

    if(NVIC STREQUAL Y)
        include(${CORE_DIR}/nvic/nvic.cmake)
    endif()

    if(DWT STREQUAL Y)
        include(${CORE_DIR}/dwt/dwt.cmake)
    endif()

    if(SYSTICK STREQUAL Y)
        include(${CORE_DIR}/systick/systick.cmake)
    endif()

    if(CORE_STACK_MONITOR STREQUAL Y)
        set(RATIONAL_NUM_DIAG Y )
        string(APPEND MCAL_OPT " -DHAS_CORE_STACK_MONITOR_PROC")
    endif()

    if(CORE_DIAG STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CORE_DIAG")
        string(APPEND SOURCES_C " ${CORE_DIR}/core_diag.c")
    endif()

    if(CLI STREQUAL Y)
        if(CORE_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CORE_COMMANDS")
            string(APPEND SOURCES_C " ${CORE_DIR}/core_commands.c")
        endif()
    endif()
endif()

