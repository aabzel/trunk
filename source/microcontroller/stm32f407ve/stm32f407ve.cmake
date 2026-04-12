message(STATUS "STM32F407VE_MK_INC=${STM32F407VE_MK_INC}")

if(NOT (STM32F407VE_MK_INC STREQUAL Y))
    set(STM32F407VE_MK_INC Y )

    set(MCU_CUSTOM_DIR "${MICROCONTROLLER_DIR}/stm32f407ve")

    string(APPEND MCAL_OPT " -DHAS_ARM_GCC")
    string(APPEND MCAL_OPT " -DHAS_STM32F407VE")
    string(APPEND MCAL_OPT " -DHAS_STM32")
    string(APPEND MCAL_OPT " -DSTM32F4xxxx")
    string(APPEND MCAL_OPT " -DSTM32F4x")
    string(APPEND MCAL_OPT " -DSTM32F407xx")
    string(APPEND MCAL_OPT " -DSTM32F407x")
    string(APPEND MCAL_OPT " -DSTM32F407VE")
    string(APPEND MCAL_OPT " -DSTM32F407xE")
    string(APPEND MCAL_OPT " -DSTM32F407Vx")
    string(APPEND MCAL_OPT " -DHAS_STM32F407X")

    set(FIRMWARE_TYPE_SELECTED N )
    set(BOARD Y )
    set(CMSIS Y )
    set(MICROCONTROLLER Y )
    set(STM32 Y )
    set(STM32F407VE Y )
    set(STM32F4XX_HAL_DRIVER Y )

    include_directories( ${MCU_CUSTOM_DIR})

    if(BOOT STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/boot_config.c")
    endif()

    if(CLOCK STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/clock_config.c")
    endif()

    if(BOOTLOADER STREQUAL Y)
        set(FIRMWARE_TYPE_SELECTED Y )

        if(BOOTLOADER_MONOLITHIC STREQUAL Y)
            string(APPEND MCAL_OPT " -DBOOT_START_ADDRESS=0x08000000")
            set(LDSCRIPT "${MCU_CUSTOM_DIR}/gcc_arm_bootloader_monolithic.ld" )
        else()
            string(APPEND MCAL_OPT " -DBOOT_START_ADDRESS=0x08060000")
            set(LDSCRIPT "${MCU_CUSTOM_DIR}/gcc_arm_boot.ld" )
        endif()
    endif()

    if(GENERIC STREQUAL Y)
        set(FIRMWARE_TYPE_SELECTED Y )
        if(GENERIC_MONOLITHIC STREQUAL Y)
            string(APPEND MCAL_OPT " -DBOOT_START_ADDRESS=0x08000000")
            string(APPEND MCAL_OPT " -DAPP_START_ADDRESS=0x08000000")
            set(LDSCRIPT "${MCU_CUSTOM_DIR}/gcc_arm_generic_monolithic.ld" )
        else()
            string(APPEND MCAL_OPT " -DAPP_START_ADDRESS=0x08010000")
            string(APPEND MCAL_OPT " -DBOOT_START_ADDRESS=0x08010000")
            set(LDSCRIPT "${MCU_CUSTOM_DIR}/gcc_arm_generic.ld" )
        endif()
    endif()

    string(APPEND MCAL_OPT " -DHAS_LINKER_INFO")

    if(MBR STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/mbr_config.c")
        set(FIRMWARE_TYPE_SELECTED Y )
        string(APPEND MCAL_OPT " -DBOOT_START_ADDRESS=0x08000000")
        string(APPEND MCAL_OPT " -DAPP_START_ADDRESS=0x08000000")
        if(MBR_ADVANCED STREQUAL Y)
            set(LDSCRIPT "${MCU_CUSTOM_DIR}/stm32f407xx_flash.icf" )
        else()
            if(GCC STREQUAL Y)
                set(LDSCRIPT "${MCU_CUSTOM_DIR}/gcc_arm_mbr.ld" )
            endif()
            if(IAR STREQUAL Y)
                set(LDSCRIPT "${MCU_CUSTOM_DIR}/stm32f407xx_flash.icf" )
            endif()
        endif()
    endif()

    if(MPU STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/mpu_config.c")
    endif()

    if(SDIO STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/sdio_config.c")
    endif()

    string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/system_stm32f4xx.c")

    if(INTERRUPT STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/interrupt_config.c")
    endif()

    if(SYSTICK STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/systick_config.c")
    endif()

    if(NVS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/nvs_config.c")
    endif()

    if(SCHEDULER STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/scheduler_config.c")
    endif()

    if(STORAGE STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/storage_config.c")
    endif()

    if(FLASH STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/flash_config.c")
    endif()

    if(FLASH_FS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/flash_fs_config.c")
    endif()

    if(SUPER_CYCLE STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/super_cycle_config.c")
    endif()

    if(WATCHDOG STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/watchdog_config.c")
    endif()

    if(STORE_FS STREQUAL Y)
        string(APPEND SOURCES_CONFIGURATION_C " ${MCU_CUSTOM_DIR}/storage_config.c")
    endif()

    string(APPEND SOURCES_DIAG_C " ${MCU_CUSTOM_DIR}/stm32f407ve_diag.c")

    if(GCC STREQUAL Y)
        string(APPEND SOURCES_ASM " ${MCU_CUSTOM_DIR}/startup_stm32f407xx.S")
    endif()

    if(IAR STREQUAL Y)
        string(APPEND SOURCES_ASM " ${MCU_CUSTOM_DIR}/startup_stm32f407xx_iar.s")
    endif()

    set(MICROCONTROLLER_SELECTED Y)

endif()

