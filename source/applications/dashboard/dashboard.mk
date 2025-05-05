$(info DASHBOARD_MK_LOG=$(DASHBOARD_MK_LOG))

ifneq ($(DASHBOARD_MK_LOG),Y)
    DASHBOARD_DRV_MK_LOG=Y

    DASHBOARD_DRV_DIR = $(APPLICATIONS_DIR)/dashboard
    #@echo $(error DASHBOARD_DRV_DIR= $(DASHBOARD_DRV_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))

    INCDIR += -I$(DASHBOARD_DRV_DIR)

    DASHBOARD=Y
    OPT += -DHAS_DASHBOARD
    OPT += -DHAS_DASHBOARD_PROC

    SOURCES_C += $(DASHBOARD_DRV_DIR)/dashboard.c

    ifeq ($(DIAG),Y)
        OPT += -DHAS_DASHBOARD_DIAG
        SOURCES_C += $(DASHBOARD_DRV_DIR)/dashboard_diag.c
    endif

    ifeq ($(DASHBOARD_COMMANDS),Y)
        OPT += -DHAS_DASHBOARD_COMMANDS
        #@echo $(error DASHBOARD_COMMANDS= $(DASHBOARD_COMMANDS))
        SOURCES_C +=  $(DASHBOARD_DRV_DIR)/dashboard_commands.c
    endif
endif