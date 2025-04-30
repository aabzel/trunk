$(info CONTROL_MK_INC=$(CONTROL_MK_INC) )
ifneq ($(CONTROL_MK_INC),Y)
    CONTROL_MK_INC=Y

    CONTROL_DIR = $(WORKSPACE_LOC)/control
    #@echo $(error CONTROL_DIR=$(CONTROL_DIR))

    INCDIR += -I$(CONTROL_DIR)
    OPT += -DHAS_CONTROL

    ifeq ($(CONTROL_COMMANDS),Y)
        OPT += -DHAS_CONTROL_COMMANDS
    endif

    ifeq ($(GENERIC),Y)
        #@echo $(error GENERIC=$(GENERIC))
        include $(CONTROL_DIR)/generic/generic.mk
    endif
    
    ifeq ($(MBR),Y)
        #@echo $(error MBR=$(MBR))
        include $(CONTROL_DIR)/mbr/mbr.mk
    endif

    ifeq ($(BOOTLOADER),Y)
        #@echo $(error BOOTLOADER= $(BOOTLOADER))
        include $(CONTROL_DIR)/bootloader/bootloader.mk
    endif

    ifeq ($(BOOT),Y)
        #@echo $(error BOOT= $(BOOT))
        include $(CONTROL_DIR)/boot_drv/boot_drv.mk
    endif

    ifeq ($(DEBUGGER),Y)
        #@echo $(error DEBUGGER=$(DEBUGGER))
        include $(CONTROL_DIR)/debugger/debugger.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        #@echo $(error FREE_RTOS=$(FREE_RTOS))
        include $(CONTROL_DIR)/free_rtos/free_rtos.mk
    endif

    ifeq ($(INDICATION),Y)
        $(info + indication)
        include $(CONTROL_DIR)/indication/indication.mk
    endif

    ifeq ($(PWM_DAC),Y)
        #@echo $(error PWM_DAC=$(PWM_DAC))
        include $(CONTROL_DIR)/pwm_dac/pwm_dac.mk
    endif

    ifeq ($(DISPLAY),Y)
        #@echo $(error DISPLAY=$(DISPLAY))
        include $(CONTROL_DIR)/display/display.mk
    endif

    ifeq ($(LED),Y)
        # @echo $(error LED=$(LED))
        include $(CONTROL_DIR)/led/led.mk
    endif

    ifeq ($(RGB_LED),Y)
        include $(CONTROL_DIR)/rgb_led/rgb_led.mk
    endif

    ifeq ($(RELAY),Y)
        include $(CONTROL_DIR)/relay/relay.mk
    endif

    ifeq ($(PID),Y)
        include $(CONTROL_DIR)/pid/pid.mk
    endif
    
    ifeq ($(RTOS),Y)
        #@echo $(error RTOS=$(RTOS))
        include $(CONTROL_DIR)/rtos/rtos.mk
    endif

    ifeq ($(SCRIPT),Y)
        #@echo $(error SCRIPT=$(SCRIPT))
        include $(CONTROL_DIR)/script/script.mk
    endif

    ifeq ($(SUPER_CYCLE),Y)
        include $(CONTROL_DIR)/super_cycle/super_cycle.mk    
    endif

    ifeq ($(SYSTEM),Y)
        include $(CONTROL_DIR)/system/system.mk    
    endif
    
    ifeq ($(TASK),Y)
        include $(CONTROL_DIR)/task/task.mk
    endif

    ifeq ($(WIN),Y)
        #@echo $(error WIN=$(WIN))
        include $(CONTROL_DIR)/win/win_utils.mk
    endif
endif