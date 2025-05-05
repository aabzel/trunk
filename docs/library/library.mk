$(info LIBRARY_MK_INC=$(LIBRARY_MK_INC) )

ifneq ($(LIBRARY_MK_INC),Y)
    LIBRARY_MK_INC=Y

    #$(error DOCUMENTATION_DIR=$(DOCUMENTATION_DIR))
    
    LIBRARY_DIR=$(DOCUMENTATION_DIR)/library
    #@echo $(error LIBRARY_DIR=$(LIBRARY_DIR))

    INCLUDE_PATHS += -I$(LIBRARY_DIR)
    MACRO_OPT += -DHAS_LIBRARY



    ifeq ($(TIMES_NEW_ROMAN),Y)
        MACRO_OPT += -DHAS_TIMES_NEW_ROMAN
    endif

    ifeq ($(MIK32_EEPROM_BOOTLOADER),Y)
        include $(LIBRARY_DIR)/mik32_eeprom_bootloader/mik32_eeprom_bootloader.mk
    endif
    
    ifeq ($(MIK32_BOOTLOADER),Y)
        include $(LIBRARY_DIR)/mik32_bootloader/mik32_bootloader.mk
    endif

    ifeq ($(FW_LOADER),Y)
        include $(LIBRARY_DIR)/fw_loader/fw_loader.mk
    endif

    ifeq ($(MAKE_BASICS),Y)
        include $(LIBRARY_DIR)/make_basics/make_basics.mk
    endif


    ifeq ($(BOOTLOADER),Y)
        include $(LIBRARY_DIR)/bootloader/bootloader.mk
    endif

    ifeq ($(MCU_NVRAM),Y)
        include $(LIBRARY_DIR)/mcu_nvram/mcu_nvram.mk
    endif
    

    ifeq ($(ACRONYMS),Y)
        include $(LIBRARY_DIR)/acronyms/acronyms.mk
    endif

    ifeq ($(UNIT_TESTING),Y)
        include $(LIBRARY_DIR)/unit_testing/unit_testing.mk
    endif

    ifeq ($(TASK_MANAGER),Y)
        include $(LIBRARY_DIR)/task_manager/task_manager.mk
    endif

    ifeq ($(GOOD_REPOSITORY),Y)
        include $(LIBRARY_DIR)/good_repository/good_repository.mk
    endif

    ifeq ($(GOOD_C_CODE),Y)
        include $(LIBRARY_DIR)/good_c_code/good_c_code.mk
    endif

    ifeq ($(DEVOPS),Y)
        include $(LIBRARY_DIR)/devops/devops.mk
    endif

    ifeq ($(FW_DEBUG),Y)
        include $(LIBRARY_DIR)/fw_debug/fw_debug.mk
    endif

    ifeq ($(FSM),Y)
        include $(LIBRARY_DIR)/fsm/fsm.mk
    endif

    ifeq ($(ATTRIBUTES_OF_GOOD_FIRMWARE),Y)
        include $(LIBRARY_DIR)/attributes_of_good_firmware/attributes_of_good_firmware.mk
    endif

    ifeq ($(WHY_UART_CLI),Y)
        include $(LIBRARY_DIR)/why_uart_cli/why_uart_cli.mk
    endif

    ifeq ($(WHY_MAKE),Y)
        include $(LIBRARY_DIR)/why_make/why_make.mk
    endif

    ifeq ($(GOOD_SWC),Y)
        include $(LIBRARY_DIR)/good_swc/good_swc.mk
    endif
    
    ifeq ($(BIBLIOGRAPHY),Y)
        include $(LIBRARY_DIR)/bibliography/bibliography.mk
    endif
endif