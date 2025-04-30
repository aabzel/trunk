message(STATUS "CONTROL_CMAKE_INC=${CONTROL_CMAKE_INC}")
if( NOT (CONTROL_CMAKE_INC STREQUAL Y))
    set(CONTROL_CMAKE_INC Y)

    message(STATUS "+ control")
    set(CONTROL_DIR ${WORKSPACE_LOC}/control)
    
    message(STATUS "CONTROL_DIR=${CONTROL_DIR}")
    include_directories(${CONTROL_DIR})
    target_compile_definitions(app PUBLIC HAS_CONTROL)
    target_compile_definitions(app PUBLIC HAS_CONTROL_COMMANDS)

    if (BOOT STREQUAL Y)
        #@echo ${error BOOT= ${BOOT))
        include(${CONTROL_DIR}/boot_drv/boot_drv.cmake)
    endif()

    if(DEBUGGER STREQUAL Y)
        include(${CONTROL_DIR}/debugger/debugger.cmake)
    endif()

    if(DISPLAY STREQUAL Y)
        include(${CONTROL_DIR}/display/display.cmake)
    endif()

    if(FREE_RTOS STREQUAL Y)
        include(${CONTROL_DIR}/free_rtos/free_rtos.cmake)
    endif()

    if(GPIO_PWM STREQUAL Y)
        include(${CONTROL_DIR}/gpio_pwm/gpio_pwm.cmake)
    endif()

    if(INDICATION STREQUAL Y)
        include(${CONTROL_DIR}/indication/indication.cmake)
    endif()

    if (LED STREQUAL Y)
        include(${CONTROL_DIR}/led/led.cmake)
    endif()

    if(RELAY STREQUAL Y)
        include(${CONTROL_DIR}/relay/relay.cmake)
    endif()

    if(RTOS STREQUAL Y)
        #include(${CONTROL_DIR}/rtos/rtos.cmake)
    endif()

    if(SUPER_CYCLE STREQUAL Y)
        include(${CONTROL_DIR}/super_cycle/super_cycle.cmake)
    endif()

    if(SYSTEM STREQUAL Y)
        include(${CONTROL_DIR}/system/system.cmake)
    endif()

    if(TASK STREQUAL Y)
        include(${CONTROL_DIR}/task/task.cmake)
    endif()

    if(TELEMATIC STREQUAL Y)
        include(${CONTROL_DIR}/telematic/telematic.cmake)
    endif()

    if(WIN STREQUAL Y)
        include(${CONTROL_DIR}/win/win.cmake)
    endif()

    if(ZEPHYR_RTOS STREQUAL Y)
        message(STATUS "+  ZEPHYR_RTOS")
        include(${CONTROL_DIR}/zephyr_rtos/zephyr_rtos.cmake)
    endif()

endif()