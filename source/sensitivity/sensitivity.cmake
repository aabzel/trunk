message(STATUS "SENSITIVITY_CMAKE_INC=${SENSITIVITY_CMAKE_INC}")
if( NOT (SENSITIVITY_CMAKE_INC STREQUAL Y))
    set(SENSITIVITY_CMAKE_INC Y)
    message(STATUS "+ sensitivity")
    set(SENSITIVITY_DIR ${WORKSPACE_LOC}/sensitivity)

    message(STATUS "SENSITIVITY_DIR=${SENSITIVITY_DIR}")
    include_directories(${SENSITIVITY_DIR})
    target_compile_definitions(app PUBLIC HAS_SENSITIVITY)
    target_include_directories(app PUBLIC ${SENSITIVITY_DIR})

    #if (BUTTON STREQUAL Y)
    #    message(STATUS "+ BUTTON driver")
    #    include(${SENSITIVITY_DIR}/button/button.cmake)
    #endif()

    if (BUTTON STREQUAL Y)
        include(${SENSITIVITY_DIR}/button_fsm/button.cmake)
    endif()

    if (CROSS_DETECT STREQUAL Y)
        include(${SENSITIVITY_DIR}/cross_detect/cross_detect.cmake)
    endif()

    if (DISTANCE STREQUAL Y)
        include(${SENSITIVITY_DIR}/distance/distance.cmake)
    endif()

    if (FM_TUNER STREQUAL Y)
        include(${SENSITIVITY_DIR}/fm_tuner/fm_tuner.cmake)
    endif()

    if (HEALTH_MONITOR STREQUAL Y)
        include(${SENSITIVITY_DIR}/health_monitor/health_monitor.cmake)
    endif()

    if (KEYBOARD STREQUAL Y)
        include(${SENSITIVITY_DIR}/keyboard/keyboard.cmake)
    endif()

    if (LIGHT_SENSOR STREQUAL Y)
        include(${SENSITIVITY_DIR}/light_sensor/light_sensor.cmake)
    endif()

    if (LOAD_DETECT STREQUAL Y)
        include(${SENSITIVITY_DIR}/load_detect/load_detect.cmake)
    endif()

    if (PHOTORESISTOR STREQUAL Y)
        include(${SENSITIVITY_DIR}/photoresistor/photoresistor.cmake)
    endif()

    if (TIME STREQUAL Y)
        include(${SENSITIVITY_DIR}/time/time.cmake)
    endif()

    target_sources(app PRIVATE ${SENSITIVITY_DIR}/proc_sensitivity.c)
    if(SENSITIVITY_COMMANDS STREQUAL Y)
         message(STATUS "+ SENSITIVITY commands")
         target_compile_definitions(app PUBLIC HAS_SENSITIVITY_COMMANDS)
         target_sources(app PRIVATE ${SENSITIVITY_DIR}/sensitivity_commands.c)
    endif()

endif()