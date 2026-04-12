
if(NOT (CORTEX_SELECT_MK_INC STREQUAL Y))
    set(CORTEX_SELECT_MK_INC Y )

    set(CORTEX_SEL_DIR "${CORE_DIR}/cortex_m4")
    include_directories( ${CORTEX_SEL_DIR})
    

    set(MICROCONTROLLER Y)

    string(APPEND SOURCES_C " ${CORTEX_SEL_DIR}/cortex_m4_driver.c")

    string(APPEND MCAL_OPT " -DHAS_ARM")
    string(APPEND MCAL_OPT " -DHAS_CORTEX_M4")
    string(APPEND MCAL_OPT " -DHAS_CORTEX_M")

    if(DIAG STREQUAL Y)
        if(CORTEX_M4_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CORTEX_M4_DIAG")
            string(APPEND SOURCES_C " ${CORTEX_SEL_DIR}/cortex_m4_diag.c")
        endif()
    endif()

    if(CLI STREQUAL Y)
        if(CORTEX_M4_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CORTEX_M4_COMMANDS")
            string(APPEND SOURCES_C " ${CORTEX_SEL_DIR}/cortex_m4_commands.c")
        endif()
    endif()

    string(APPEND MICROPROCESSOR " -mcpu=cortex-m4")
    string(APPEND MICROPROCESSOR " -march=armv7e-m")
    string(APPEND MICROPROCESSOR " -mthumb")
    
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -mcpu=cortex-m4 -march=armv7e-m -mthumb -mfloat-abi=hard -mfpu=fpv4-sp-d16")
    
    #target_link_options(${EXECUTABLE} PRIVATE -mcpu=cortex-m4)
    #target_link_options(${EXECUTABLE} PRIVATE -march=armv7e-m)
    #target_link_options(${EXECUTABLE} PRIVATE -mthumb)

    if(MPU STREQUAL Y)
        string(APPEND MCAL_OPT " -D__MPU_PRESENT=1")
    endif()

    if(FPU STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_FPU")
        string(APPEND MICROPROCESSOR " -mfloat-abi=hard")
        string(APPEND MICROPROCESSOR " -mfpu=fpv4-sp-d16")
        
        #target_link_options(${EXECUTABLE} PRIVATE  -mfloat-abi=hard)
        #target_link_options(${EXECUTABLE} PRIVATE  -mfpu=fpv4-sp-d16)
    else()
        string(APPEND MICROPROCESSOR " -mfloat-abi=soft")
        #target_link_options(${EXECUTABLE} PRIVATE  -mfloat-abi=soft)
    endif()

    string(APPEND MCAL_OPT " ${MICROPROCESSOR}")
endif()
