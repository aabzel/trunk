
if( NOT (MICROCONTROLLER_MK_INC STREQUAL Y))
    set(MICROCONTROLLER_MK_INC Y)
    set(MICROCONTROLLER_SELECTED N)

    set(MICROCONTROLLER_DIR ${WORKSPACE_LOC}/microcontroller)
    
    include_directories( ${MICROCONTROLLER_DIR})
    
    message(STATUS "MICROCONTROLLER_DIR=${MICROCONTROLLER_DIR}")


    set(MICROCONTROLLER Y)
    string(APPEND MCAL_OPT " -DHAS_MICROCONTROLLER")

    string(APPEND SOURCES_C " ${MICROCONTROLLER_DIR}/microcontroller_drv.c")

    if(DIAG STREQUAL Y)
        string(APPEND SOURCES_C " ${MICROCONTROLLER_DIR}/microcontroller_diag.c")
    endif()

    if(CLI STREQUAL Y)
        string(APPEND SOURCES_C " ${MICROCONTROLLER_DIR}/microcontroller_commands.c")
    endif()
    
    if(MCU_X86 STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/x86/cpu_x86.cmake)
    endif()

    if(AT32F413RC STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/at32f413rc/at32f413rc.cmake)
    endif()

    if(K1948BK018 STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/k1948bk018/k1948bk018.cmake)
    endif()

    if(AT32F435ZM STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/at32f435zm/at32f435zm.cmake)
    endif()

    if(AT32F437ZM STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/at32f437zm/at32f437zm.cmake)
    endif()

    if(AT32F4X STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/at32f4x/at32f4x.cmake)
    endif()
    
    if(CC2642R1F STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/cc2642r1f/cc2642r1f.cmake)
    endif()

    if(CC2652R1F STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/cc2652r1f/cc2652r1f.cmake)
    endif()

    if(DUMMY_MCU STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/dummy_mcu/dummy_mcu.cmake)
    endif()

    if(FC7300F8MDT STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/fc7300f8mdt/fc7300f8mdt.cmake)
    endif()

    if(NRF5340 STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/nrf5340/nrf5340.cmake)
    endif()

    if(STM32F401RE STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f401re/stm32f401re.cmake)
    endif()

    if(STM32F407VE STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f407ve/stm32f407ve.cmake)
    endif()

    if(STM32F407VG STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f407vg/stm32f407vg.cmake)
    endif()

    if(STM32F407ZG STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f407zg/stm32f407zg.cmake)
    endif()

    if(STM32F411CE STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f411ce/stm32f411ce.cmake)
    endif()

    if(STM32F413ZH STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f413zh/stm32f413zh.cmake)
    endif()

    if(STM32F415RG STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f415rg/stm32f415rg.cmake)
    endif()

    if(STM32F429ZI STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f429zi/stm32f429zi.cmake)
    endif()

    if(STM32F446RE STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f446re/stm32f446re.cmake)
    endif()

    if(STM32F746ZG STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32f746zg/stm32f746zg.cmake)
    endif()

    if(STM32L073RZ STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/stm32l073rz/stm32l073rz.cmake)
    endif()

    if(X86 STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/x86/cpu_x86.cmake)
        set(MICROCONTROLLER_SELECTED Y)
    endif()

    if(YTM32B1ME05G0MLQ STREQUAL Y)
        include(${MICROCONTROLLER_DIR}/ytm32b1me05g0mlq/ytm32b1me05g0mlq.cmake)
    endif()

    if(NOT MICROCONTROLLER_SELECTED STREQUAL Y)
        message(FATAL_ERROR "Select MCU")
    endif()

endif()