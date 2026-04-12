$(info CONTROL_PRECONFIG_INC=$(CONTROL_PRECONFIG_INC) )
ifneq ($(CONTROL_PRECONFIG_INC),Y)
    CONTROL_PRECONFIG_INC=Y

    CONTROL_DIR = $(WORKSPACE_LOC)/control
    # $(error CONTROL_DIR=$(CONTROL_DIR))

    ifeq ($(MBR),Y)
        # $(error MBR=$(MBR))
        include $(CONTROL_DIR)/mbr/mbr_preconfig.mk
    endif

    ifeq ($(BOOT),Y)
        # $(error BOOT= $(BOOT))
        include $(CONTROL_DIR)/boot_drv/boot_preconfig.mk
    endif

    ifeq ($(BOOTLOADER),Y)
        # $(error BOOTLOADER= $(BOOTLOADER))
        include $(CONTROL_DIR)/bootloader/bootloader_preconfig.mk
    endif

    ifeq ($(BUZZER),Y)
        include $(CONTROL_DIR)/buzzer/buzzer_preconfig.mk
    endif
 
    ifeq ($(PWM_DAC),Y)
        # $(error PWM_DAC= $(PWM_DAC))
        include $(CONTROL_DIR)/pwm_dac/pwm_dac_preconfig.mk
    endif
    
    ifeq ($(GENERIC),Y)
        #@echo $(error GENERIC= $(GENERIC))
        include $(CONTROL_DIR)/generic/generic_preconfig.mk
    endif

    ifeq ($(DEBUGGER),Y)
        # $(error DEBUGGER=$(DEBUGGER))
        include $(CONTROL_DIR)/debugger/debugger_preconfig.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        # $(error FREE_RTOS=$(FREE_RTOS))
        include $(CONTROL_DIR)/free_rtos/free_rtos_preconfig.mk
    endif

    ifeq ($(INDICATION),Y)
        $(info + indication)
        include $(CONTROL_DIR)/indication/indication_preconfig.mk
    endif

    ifeq ($(LED),Y)
        include $(CONTROL_DIR)/led/led_preconfig.mk
    endif

    ifeq ($(RGB_LED),Y)
        include $(CONTROL_DIR)/rgb_led/rgb_led_preconfig.mk
    endif

    ifeq ($(DISPLAY),Y)
        # $(error DISPLAY=$(DISPLAY))
        include $(CONTROL_DIR)/display/display_preconfig.mk
    endif
    
    ifeq ($(SUPER_CYCLE),Y)
        include $(CONTROL_DIR)/super_cycle/super_cycle_preconfig.mk    
    endif

    ifeq ($(POSTPONE_FUN),Y)
        include $(CONTROL_DIR)/postpone_fun/postpone_fun_preconfig.mk    
    endif

    ifeq ($(SYSTEM),Y)
        include $(CONTROL_DIR)/system/system_preconfig.mk    
    endif

    ifeq ($(SCHEDULER),Y)
        include $(CONTROL_DIR)/scheduler/scheduler_preconfig.mk
    endif

    ifeq ($(WIN),Y)
        # $(error WIN=$(WIN))
        include $(CONTROL_DIR)/win/win_utils_preconfig.mk
    endif
endif