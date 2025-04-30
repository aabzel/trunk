message(STATUS "COMPONENTS_MK_INC=${COMPONENTS_MK_INC}")
if( NOT (COMPONENTS_MK_INC STREQUAL Y))
    set(COMPONENTS_MK_INC Y)
    message(STATUS "+  Components")

    set(COMPONENTS_DIR ${WORKSPACE_LOC}/components)
    message(STATUS "COMPONENTS_DIR=${COMPONENTS_DIR}")

    if(ALLOCATOR STREQUAL Y)
        include(${COMPONENTS_DIR}/allocator/allocator.cmake)
    endif()

    if(AUDIO STREQUAL Y)
        message(STATUS "+  AUDIO")
        include(${COMPONENTS_DIR}/audio/audio.cmake)
    endif()

    if(BOARD_INFO STREQUAL Y)
        message(STATUS "+  BOARD_INFO")
        include(${COMPONENTS_DIR}/board_info/board_info.cmake)
    endif()

    include(${COMPONENTS_DIR}/interval/interval.cmake)

    if(CRC STREQUAL Y)
        #message(SEND_ERROR "CRC=${CRC}")
        include(${COMPONENTS_DIR}/crc/crc.cmake)
    endif()

    if(LIMITER STREQUAL Y)
        #message(SEND_ERROR "LIMITER=${LIMITER}")
        include(${COMPONENTS_DIR}/limiter/limiter.cmake)
    endif()

    if(TASK STREQUAL Y)
        include(${COMPONENTS_DIR}/task_drv/task.cmake)
    endif()

    if(MATH STREQUAL Y)
        include(${COMPONENTS_DIR}/math/math.cmake)
    endif()

    if(DEBUGGER STREQUAL Y)
        message(STATUS "+ DEBUGGER")
        include(${COMPONENTS_DIR}/debugger/debugger.cmake)
    endif()

    if(DISTANCE STREQUAL Y)
        message(STATUS "+ DISTANCE")
        include(${COMPONENTS_DIR}/distance/distance.cmake)
    endif()

    if(FIFO STREQUAL Y)
        include(${COMPONENTS_DIR}/fifo/fifo.cmake)
    endif()

    if(FONT STREQUAL Y)
        message(STATUS "+FONT")
        include(${COMPONENTS_DIR}/font/font.cmake)
    endif()

    if(LOG STREQUAL Y)
        message(STATUS "+ log")
        include(${COMPONENTS_DIR}/log/log.cmake)
    endif()

    if(SYSTEM STREQUAL Y)
        include(${COMPONENTS_DIR}/system/system.cmake)
    endif()

    if(SW_DAC STREQUAL Y)
        message(STATUS "+  SW_DAC")
        include(${COMPONENTS_DIR}/sw_dac/sw_dac.cmake)
    endif()

    if(SUPER_CYCLE STREQUAL Y)
        message(STATUS "+  SuperCycle")
        include(${COMPONENTS_DIR}/super_cycle/super_cycle.cmake)
    endif()

    if(STRING STREQUAL Y)
        include(${COMPONENTS_DIR}/string/string.cmake)
    endif()
    
    if(TIME STREQUAL Y)
        include(${COMPONENTS_DIR}/time/time.cmake)
    endif()

    if(ZEPHYR_RTOS STREQUAL Y)
        message(STATUS "+  ZEPHYR_RTOS")
        include(${COMPONENTS_DIR}/zephyr_rtos/zephyr_rtos.cmake)
    endif()
endif()
