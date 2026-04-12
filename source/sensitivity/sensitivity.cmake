
if( NOT (SENSITIVITY_CMAKE_INC STREQUAL Y))
    set(SENSITIVITY_MK_INC Y)

    string(APPEND MCAL_OPT " -DHAS_SENSITIVITY")
    set(SENSITIVITY_DIR "${WORKSPACE_LOC}/sensitivity")
    include_directories(${SENSITIVITY_DIR})
    

    if(BUTTON STREQUAL Y)
        include(${SENSITIVITY_DIR}/button_fsm/button.cmake)
    endif()

    if(CROSS_DETECT STREQUAL Y)
        include(${SENSITIVITY_DIR}/cross_detect/cross_detect.cmake)
    endif()

    if(FM_TUNER STREQUAL Y)
        include(${SENSITIVITY_DIR}/fm_tuner/fm_tuner.cmake)
    endif()

    if(GAME_PAD_PS2 STREQUAL Y)
        include(${SENSITIVITY_DIR}/game_pad_ps2/game_pad_ps2.cmake)
    endif()

    if(KEYBOARD STREQUAL Y)
        include(${SENSITIVITY_DIR}/keyboard/keyboard.cmake)
    endif()

    if(DISTANCE STREQUAL Y)
        include(${SENSITIVITY_DIR}/distance/distance.cmake)
    endif()

    if(LIGHT_SENSOR STREQUAL Y)
        include(${SENSITIVITY_DIR}/light_sensor/light_sensor.cmake)
    endif()

    if(HEALTH_MONITOR STREQUAL Y)
        include(${SENSITIVITY_DIR}/health_monitor/health_monitor.cmake)
    endif()

    if(HW_VERSION STREQUAL Y)
        include(${SENSITIVITY_DIR}/hw_version/hw_version.cmake)
    endif()

    if(LOAD_DETECT STREQUAL Y)
        include(${SENSITIVITY_DIR}/load_detect/load_detect.cmake)
    endif()

    if(IR_RECEIVER STREQUAL Y)
        include(${SENSITIVITY_DIR}/ir_receiver/ir_receiver.cmake)
    endif()

    if(PHOTORESISTOR STREQUAL Y)
        include(${SENSITIVITY_DIR}/photoresistor/photoresistor.cmake)
    endif()

    if(TIME STREQUAL Y)
        include(${SENSITIVITY_DIR}/time/time.cmake)
    endif()

    string(APPEND SOURCES_C " ${SENSITIVITY_DIR}/sensitivity.c")

    if(DIAG STREQUAL Y)
        string(APPEND SOURCES_C " ${SENSITIVITY_DIR}/sensitivity_diag.c")
    endif()

    if(SENSITIVITY_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_SENSITIVITY_COMMANDS")
        string(APPEND SOURCES_C " ${SENSITIVITY_DIR}/sensitivity_commands.c")
    endif()
endif()