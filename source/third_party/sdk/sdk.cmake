
if( NOT (VENDOR_SDK_CMAKE_INC STREQUAL Y))
    set(VENDOR_SDK_MK_INC Y )

    set(VENDOR_SDK_DIR "${THIRD_PARTY_DIR}/sdk")
    get_filename_component(VENDOR_SDK_DIR "${VENDOR_SDK_DIR}" REALPATH)

   
    include_directories( ${VENDOR_SDK_DIR})
        

    string(APPEND MCAL_OPT " -DHAS_VENDOR_SDK")

    if(CMSIS STREQUAL Y)
        include(${VENDOR_SDK_DIR}/CMSIS/cmsis.cmake)
    endif()

    if(EHAL STREQUAL Y)
        include(${VENDOR_SDK_DIR}/core/core.cmake)
        include(${VENDOR_SDK_DIR}/EHAL_common/EHAL_common.cmake)
        include(${VENDOR_SDK_DIR}/miscellaneous/miscellaneous.cmake)
        if(MICROCONTROLLER STREQUAL Y)
            include(${VENDOR_SDK_DIR}/microcontroller/micro_controller.cmake)
        endif()
    endif()

    if(AT32F413_FIRMWARE_LIBRARY_V2_1_4_EN STREQUAL Y)
        include(${VENDOR_SDK_DIR}/AT32F413_Firmware_Library_V2_1_4_EN/AT32F413_Firmware_Library_V2_1_4_EN.cmake)
    endif()

    if(AT32F435_437_FIRMWARE_LIBRARY_EN_V2_1_5 STREQUAL Y)
        include(${VENDOR_SDK_DIR}/AT32F435_437_Firmware_Library_EN_V2.1.5/AT32F435_437_Firmware_Library_EN_V2_1_5.cmake)
    endif()

    if(FC7300_SDK_V2_3_2 STREQUAL Y)
        include(${VENDOR_SDK_DIR}/FC7300_SDK_V2_3_2/FC7300_SDK_V2_3_2.cmake)
    endif()

    if(FC7300_SDK_V2_4_0 STREQUAL Y)
        include(${VENDOR_SDK_DIR}/FC7300_SDK_V2_4_0/FC7300_SDK_V2_4_0.cmake)
    endif()

    if(MIK32 STREQUAL Y)
        include(${VENDOR_SDK_DIR}/MIK32_HAL/MIK32_SRC.cmake)
    endif()

    if(EHAL_AT32F413X STREQUAL Y)
        include(${VENDOR_SDK_DIR}/EHAL_AT32F413x/EHAL_AT32F413x.cmake)
    endif()

    if(EHAL_AT32F43X STREQUAL Y)
        include(${VENDOR_SDK_DIR}/EHAL_AT32F43x/EHAL_AT32F43x.cmake)
    endif()

    if(EHAL_YTM32B1Mx STREQUAL Y)
        include(${VENDOR_SDK_DIR}/EHAL_YTM32B1Mx/EHAL_YTM32B1Mx.cmake)
    endif()

    if(SIMPLELINK_CC13X2_26X2_SDK STREQUAL Y)
        include(${VENDOR_SDK_DIR}/simplelink_cc13x2_26x2_sdk/simplelink_cc13x2_26x2_sdk.cmake)
    endif()

    if(STM32F4XX_HAL_DRIVER STREQUAL Y)
        include(${VENDOR_SDK_DIR}/STM32F4xx_HAL_Driver/stm32f4xx_hal_driver.cmake)
    endif()

    if(STM32F4XX_HAL_DRIVER_RI STREQUAL Y)
        include(${VENDOR_SDK_DIR}/STM32F4xx_HAL_Driver_RI/stm32f4xx_hal_driver.cmake)
    endif()

    if(STM32 STREQUAL Y)
        if(USB_DEVICE_RI STREQUAL Y)
            include(${VENDOR_SDK_DIR}/STM32_USB_Device_Library_RI/STM32_USB_Device_Library.cmake)
        endif()

        if(USB_DEVICE STREQUAL Y)
            include(${VENDOR_SDK_DIR}/STM32_USB_Device_Library/STM32_USB_Device_Library.cmake)
        endif()

        if(USB_HOST STREQUAL Y)
            include(${VENDOR_SDK_DIR}/STM32_USB_Host_Library/STM32_USB_Host_Library.cmake)
        endif()
    endif()

    if(YTM32B1ME0_1_3_1 STREQUAL Y)
        include(${VENDOR_SDK_DIR}/YTM32B1ME0_1_3_1/YTM32B1ME0_1_3_1.cmake)
    endif()

endif()