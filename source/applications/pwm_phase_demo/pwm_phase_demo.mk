ifneq ($(PWM_PHASE_DEMO_MK_INC),Y)
    PWM_PHASE_DEMO_MK_INC=Y

    PWM_PHASE_DEMO_DIR = $(APPLICATIONS_DIR)/pwm_phase_demo
    # $(error PWM_PHASE_DEMO_DIR=$(PWM_PHASE_DEMO_DIR))

    INCDIR += -I$(PWM_PHASE_DEMO_DIR)

    MCAL_OPT += -DHAS_PWM_PHASE_DEMO
    MCAL_OPT += -DHAS_PWM_PHASE_DEMO_PROC

    SOURCES_C += $(PWM_PHASE_DEMO_DIR)/pwm_phase_demo_mcal.c

    ifeq ($(DIAG),Y)
        ifeq ($(PWM_PHASE_DEMO_DIAG),Y)
            MCAL_OPT += -DHAS_PWM_PHASE_DEMO_DIAG
            SOURCES_C += $(PWM_PHASE_DEMO_DIR)/pwm_phase_demo_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(PWM_PHASE_DEMO_COMMANDS),Y)
            MCAL_OPT += -DHAS_PWM_PHASE_DEMO_COMMANDS
            SOURCES_C += $(PWM_PHASE_DEMO_DIR)/pwm_phase_demo_commands.c
        endif
    endif
endif
