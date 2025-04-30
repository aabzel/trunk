
$(info HEALTH_MONITOR_MK_INC=$(HEALTH_MONITOR_MK_INC) )
ifneq ($(HEALTH_MONITOR_MK_INC),Y)
    HEALTH_MONITOR_MK_INC=Y

    HEALTH_MONITOR_DIR = $(SENSITIVITY_DIR)/health_monitor
    #@echo $(error HEALTH_MONITOR_DIR=$(HEALTH_MONITOR_DIR))

    INCDIR += -I$(HEALTH_MONITOR_DIR)

    OPT += -DHAS_HEALTH_MONITOR
    OPT += -DHAS_HEALTH_MONITOR_PROC
    
    SOURCES_C += $(HEALTH_MONITOR_DIR)/health_monitor.c

    ifeq ($(DIAG),Y)
        ifeq ($(HEALTH_MONITOR_DIAG),Y)
            OPT += -DHAS_HEALTH_MONITOR_DIAG
            #@echo $(error HEALTH_MONITOR_DIAG=$(HEALTH_MONITOR_DIAG))
            SOURCES_C += $(HEALTH_MONITOR_DIR)/health_monitor_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(HEALTH_MONITOR_COMMANDS),Y)
            OPT += -DHAS_HEALTH_MONITOR_COMMANDS
            SOURCES_C += $(HEALTH_MONITOR_DIR)/health_monitor_commands.c
        endif
    endif
endif
