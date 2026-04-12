#message(STATUS "CONTROL_CMAKE_INC=${CONTROL_CMAKE_INC}")
if(NOT (CONTROL_MK_INC STREQUAL Y))
    set(CONTROL_MK_INC Y)

    set(CONTROL_DIR "${WORKSPACE_LOC}/control")

    include_directories(${CONTROL_DIR})
    string(APPEND MCAL_OPT " -DHAS_CONTROL")

    if(CONTROL_COMMANDS STREQUAL Y)
        string(APPEND MCAL_OPT " -DHAS_CONTROL_COMMANDS")
    endif()

    if(CLI STREQUAL Y)
        if(CONTROL_COMMANDS STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CONTROL_COMMANDS")
            string(APPEND SOURCES_C " ${CONTROL_DIR}/control_commands.c")
        endif()
    endif()

    if(DIAG STREQUAL Y)
        if(CONTROL_DIAG STREQUAL Y)
            string(APPEND MCAL_OPT " -DHAS_CONTROL_DIAG")
            string(APPEND SOURCES_C " ${CONTROL_DIR}/control_diag.c")
        endif()
    endif()

    if(AUTO_EXIT STREQUAL Y)
        include(${CONTROL_DIR}/auto_exit/auto_exit.cmake)
    endif()

    if(GENERIC STREQUAL Y)
        include(${CONTROL_DIR}/generic/generic.cmake)
    endif()

    if(MBR STREQUAL Y)
        include(${CONTROL_DIR}/mbr/mbr.cmake)
    endif()

    if(BOOTLOADER STREQUAL Y)
        include(${CONTROL_DIR}/bootloader/bootloader.cmake)
    endif()

    if(BUZZER STREQUAL Y)
        include(${CONTROL_DIR}/buzzer/buzzer.cmake)
    endif()

    if(BOOT STREQUAL Y)
        include(${CONTROL_DIR}/boot_drv/boot_drv.cmake)
    endif()

    if(GPIO_DAC STREQUAL Y)
        include(${CONTROL_DIR}/gpio_dac/gpio_dac.cmake)
    endif()

    if(GPIO_PWM STREQUAL Y)
        include(${CONTROL_DIR}/gpio_pwm/gpio_pwm.cmake)
    endif()

    if(DEBUGGER STREQUAL Y)
        include(${CONTROL_DIR}/debugger/debugger.cmake)
    endif()

    if(FREE_RTOS STREQUAL Y)
        include(${CONTROL_DIR}/free_rtos/free_rtos.cmake)
    endif()

    if(INDICATION STREQUAL Y)
        include(${CONTROL_DIR}/indication/indication.cmake)
    endif()

    if(PWM_DAC STREQUAL Y)
        include(${CONTROL_DIR}/pwm_dac/pwm_dac.cmake)
    endif()

    if(DISPLAY STREQUAL Y)
        include(${CONTROL_DIR}/display/display.cmake)
    endif()

    if(LED STREQUAL Y)
        include(${CONTROL_DIR}/led/led.cmake)
    endif()

    if(RGB_LED STREQUAL Y)
        include(${CONTROL_DIR}/rgb_led/rgb_led.cmake)
    endif()

    if(RELAY STREQUAL Y)
        include(${CONTROL_DIR}/relay/relay.cmake)
    endif()

    if(PID STREQUAL Y)
        include(${CONTROL_DIR}/pid/pid.cmake)
    endif()

    if(RTOS STREQUAL Y)
        include(${CONTROL_DIR}/rtos/rtos.cmake)
    endif()

    if(SCRIPT STREQUAL Y)
        include(${CONTROL_DIR}/script/script.cmake)
    endif()

    if(POSTPONE_FUN STREQUAL Y)
        include(${CONTROL_DIR}/postpone_fun/postpone_fun.cmake)
    endif()

    if(SUPER_CYCLE STREQUAL Y)
        include(${CONTROL_DIR}/super_cycle/super_cycle.cmake)
    endif()

    if(SYSTEM STREQUAL Y)
        include(${CONTROL_DIR}/system/system.cmake)
    endif()

    if(SCHEDULER STREQUAL Y)
        include(${CONTROL_DIR}/scheduler/scheduler.cmake)
    endif()

    if(WIN STREQUAL Y)
        include(${CONTROL_DIR}/win/win_utils.cmake)
    endif()

    if(ZEPHYR_RTOS STREQUAL Y)
        #message(STATUS "+  ZEPHYR_RTOS")
        include(${CONTROL_DIR}/zephyr_rtos/zephyr_rtos.cmake)
    endif()
endif()