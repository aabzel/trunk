$(info CONTROL_MK_INC=$(CONTROL_MK_INC) )
ifneq ($(CONTROL_MK_INC),Y)
    CONTROL_MK_INC=Y

    CONTROL_DIR = $(WORKSPACE_LOC)/control
    # $(error CONTROL_DIR=$(CONTROL_DIR))

    INCDIR += -I$(CONTROL_DIR)
    MCAL_OPT += -DHAS_CONTROL

    ifeq ($(CONTROL_COMMANDS),Y)
        MCAL_OPT += -DHAS_CONTROL_COMMANDS
    endif
    
    ifeq ($(CLI),Y)
        ifeq ($(CONTROL_COMMANDS),Y)
            # $(error CONTROL_COMMANDS=$(CONTROL_COMMANDS))
            MCAL_OPT += -DHAS_CONTROL_COMMANDS
            SOURCES_C += $(CONTROL_DIR)/control_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(CONTROL_DIAG),Y)
            MCAL_OPT += -DHAS_CONTROL_DIAG
            # $(error CONTROL_DIAG=$(CONTROL_DIAG))
            SOURCES_C += $(CONTROL_DIR)/control_diag.c
        endif
    endif

    ifeq ($(AUTO_EXIT),Y)
        include $(CONTROL_DIR)/auto_exit/auto_exit.mk    
    endif
    
    ifeq ($(GENERIC),Y)
        # $(error GENERIC=$(GENERIC))
        include $(CONTROL_DIR)/generic/generic.mk
    endif
    
    ifeq ($(MBR),Y)
        # $(error MBR=$(MBR))
        include $(CONTROL_DIR)/mbr/mbr.mk
    endif

    ifeq ($(BOOTLOADER),Y)
        # $(error BOOTLOADER= $(BOOTLOADER))
        include $(CONTROL_DIR)/bootloader/bootloader.mk
    endif

    ifeq ($(BUZZER),Y)
        # $(error BUZZER= $(BUZZER))
        include $(CONTROL_DIR)/buzzer/buzzer.mk
    endif
    
    ifeq ($(BOOT),Y)
        # $(error BOOT= $(BOOT))
        include $(CONTROL_DIR)/boot_drv/boot_drv.mk
    endif

    ifeq ($(GPIO_DAC),Y)
        # $(error GPIO_DAC=$(GPIO_DAC))
        include $(CONTROL_DIR)/gpio_dac/gpio_dac.mk
    endif

    ifeq ($(GPIO_PWM),Y)
        # $(error GPIO_PWM=$(GPIO_PWM))
        include $(CONTROL_DIR)/gpio_pwm/gpio_pwm.mk
    endif
    
    ifeq ($(DEBUGGER),Y)
        # $(error DEBUGGER=$(DEBUGGER))
        include $(CONTROL_DIR)/debugger/debugger.mk
    endif

    ifeq ($(FREE_RTOS),Y)
        # $(error FREE_RTOS=$(FREE_RTOS))
        include $(CONTROL_DIR)/free_rtos/free_rtos.mk
    endif

    ifeq ($(INDICATION),Y)
        $(info + indication)
        include $(CONTROL_DIR)/indication/indication.mk
    endif

    ifeq ($(PWM_DAC),Y)
        # $(error PWM_DAC=$(PWM_DAC))
        include $(CONTROL_DIR)/pwm_dac/pwm_dac.mk
    endif

    ifeq ($(DISPLAY),Y)
        # $(error DISPLAY=$(DISPLAY))
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
        # $(error RTOS=$(RTOS))
        include $(CONTROL_DIR)/rtos/rtos.mk
    endif

    ifeq ($(SCRIPT),Y)
        # $(error SCRIPT=$(SCRIPT))
        include $(CONTROL_DIR)/script/script.mk
    endif

    ifeq ($(POSTPONE_FUN),Y)
        # $(error SCRIPT=$(SCRIPT))
        include $(CONTROL_DIR)/postpone_fun/postpone_fun.mk
    endif
    
    ifeq ($(SUPER_CYCLE),Y)
        include $(CONTROL_DIR)/super_cycle/super_cycle.mk    
    endif

    ifeq ($(SYSTEM),Y)
        include $(CONTROL_DIR)/system/system.mk    
    endif

    ifeq ($(SCHEDULER),Y)
        include $(CONTROL_DIR)/scheduler/scheduler.mk
    endif

    ifeq ($(WIN),Y)
        # $(error WIN=$(WIN))
        include $(CONTROL_DIR)/win/win_utils.mk
    endif
endif