message(STATUS "USB_CMAKE_INC=${USB_CMAKE_INC}")
if( NOT (USB_CMAKE_INC STREQUAL Y))
    set(USB_CMAKE_INC Y)
    message(STATUS "set USB_CMAKE_INC=${USB_CMAKE_INC}")
    message(STATUS "Add USB driver")

    set(USB_GENERIC_DIR ${MCAL_ZEPHYR_DIR}/usb)
    message(STATUS "USB_ZEPHYR_DIR=${USB_ZEPHYR_DIR}")

    target_compile_definitions(app PUBLIC HAS_USB)

    include_directories(${USB_ZEPHYR_DIR})
    target_include_directories(app PUBLIC ${USB_GENERIC_DIR})

    target_sources(app PRIVATE ${USB_GENERIC_DIR}/usb_drv.c)

    if (USB_AUDIO STREQUAL Y)
        message(STATUS "Add USB_AUDIO")
        target_compile_definitions(app PUBLIC HAS_AUDIO_USB)
        target_compile_definitions(app PUBLIC HAS_USB_AUDIO)
        target_sources(app PRIVATE ${USB_GENERIC_DIR}/audio_usb.c)
        target_sources(app PRIVATE ${USB_GENERIC_DIR}/audio_usb_config.c)
        if (USB_TO_I2S STREQUAL Y)
            message(STATUS "Add USB_TO_I2S")
            target_compile_definitions(app PUBLIC HAS_USB_TO_I2S)
            target_sources(app PRIVATE ${USB_GENERIC_DIR}/usb_to_i2s_drv.c)
        endif()
    endif()

    if (CLI STREQUAL Y)
        if (AUDIO_USB_COMMANDS STREQUAL Y)
            message(STATUS "Link Audio Usb commands")
            target_compile_definitions(app PUBLIC HAS_AUDIO_USB_COMMANDS)
            target_sources(app PRIVATE ${USB_GENERIC_DIR}/audio_usb_commands.c)
        endif()
    endif()
endif()



