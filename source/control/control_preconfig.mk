$(info CONTROL_PRECONFIG_INC=$(CONTROL_PRECONFIG_INC) )
ifneq ($(CONTROL_PRECONFIG_INC),Y)
    CONTROL_PRECONFIG_INC=Y

    CONTROL_DIR = $(WORKSPACE_LOC)/control
    #@echo $(error CONTROL_DIR=$(CONTROL_DIR))

    ifeq ($(MBR),Y)
        #@echo $(error MBR=$(MBR))
        include $(CONTROL_DIR)/mbr/mbr_preconfig.mk
    endif

    ifeq ($(BOOT),Y)
        #@echo $(error BOOT= $(BOOT))
        include $(CONTROL_DIR)/boot_drv/boot_preconfig.mk
    endif

    ifeq ($(BOOTLOADER),Y)
        #@echo $(error BOOTLOADER= $(BOOTLOADER))
        include $(CONTROL_DIR)/bootloader/bootloader_preconfig.mk
    endif
 
    ifeq ($(PWM_DAC),Y)
        #@echo $(error PWM_DAC= $(PWM_DAC))
        include $(CONTROL_DIR)/pwm_dac/pwm_dac_preconfig.mk
    endif
    
    ifeq ($(GENERIC),Y)
        #@echo $(error GENERIC= $(GENERIC))
        include $(CONTROL_DIR)/generic/generic_preconfig.mk
    endif

    ifeq ($(DEBUGGER),Y)
        #@echo $(error DEBUGGER=$(DEBUGGER))
        include $(CONTROL_DIR)/debugger/debugger_preconfig.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        #@echo $(error FREE_RTOS=$(FREE_RTOS))
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
        #@echo $(error DISPLAY=$(DISPLAY))
        include $(CONTROL_DIR)/display/display_preconfig.mk
    endif
    
    ifeq ($(SUPER_CYCLE),Y)
        include $(CONTROL_DIR)/super_cycle/super_cycle_preconfig.mk    
    endif

    ifeq ($(SYSTEM),Y)
        include $(CONTROL_DIR)/system/system_preconfig.mk    
    endif
    
    ifeq ($(TASK),Y)
        include $(CONTROL_DIR)/task/task_preconfig.mk
    endif

    ifeq ($(WIN),Y)
        #@echo $(error WIN=$(WIN))
        include $(CONTROL_DIR)/win/win_utils_preconfig.mk
    endif
endif