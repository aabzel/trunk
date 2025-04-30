
message(STATUS "USB_CMK_INC=${USB_CMK_INC}")
if( NOT (USB_CMK_INC STREQUAL Y))
    set(USB_CMK_INC Y)
    message(STATUS "Link USB General")

    set(USB_GENERAL_DIR ${MCAL_COMMON_DIR}/usb)
    message(STATUS "USB_GENERAL_DIR=${USB_GENERAL_DIR}")

    #message( SEND_ERROR "Check Compile" )

    add_compile_definitions(HAS_USB)
    target_compile_definitions(app PUBLIC HAS_USB)

    include_directories(${USB_GENERAL_DIR})
    target_include_directories(app PUBLIC ${USB_GENERAL_DIR})

    if(DIAG STREQUAL Y)
        if(USB_DIAG STREQUAL Y)

        endif()
    endif()

    if(CLI STREQUAL Y)
        if(USB_COMMANDS STREQUAL Y)

        endif()
    endif()
endif()

