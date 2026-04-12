
if(NOT (CMSIS_MK_INC STREQUAL Y))
    set(CMSIS_MK_INC Y )

    set(CMSIS_DIR "${VENDOR_SDK_DIR}/CMSIS")

    string(APPEND MCAL_OPT " -DHAS_CMSIS")

    #string(APPEND INCDIR " ${CMSIS_DIR}")
    #string(APPEND INCDIR " ${CMSIS_DIR}/Include")
    #string(APPEND INCDIR " ${CMSIS_DIR}/Core/Include")
    #string(APPEND INCDIR " ${CMSIS_DIR}/DSP/Include")

    include_directories( ${CMSIS_DIR})
    include_directories( ${CMSIS_DIR}/Include)
    include_directories( ${CMSIS_DIR}/Core/Include)
    include_directories( ${CMSIS_DIR}/DSP/Include)
 
 
    if(STM32 STREQUAL Y)
        #string(APPEND INCDIR " ${CMSIS_DIR}/Device/ST/STM32F4xx/Include")
        include_directories(${CMSIS_DIR}/Device/ST/STM32F4xx/Include)
    endif()
endif()
