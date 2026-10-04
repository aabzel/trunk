$(info DASHBOARD_MK_LOG=$(DASHBOARD_MK_LOG))

ifneq ($(DASHBOARD_MK_LOG),Y)
    DASHBOARD_DRV_MK_LOG=Y

    DASHBOARD_DRV_DIR = $(APPLICATIONS_DIR)/dashboard
    # $(error DASHBOARD_DRV_DIR= $(DASHBOARD_DRV_DIR))
    # $(error CFLAGS= $(CFLAGS))

    INCDIR += -I$(DASHBOARD_DRV_DIR)

    DASHBOARD=Y
    MCAL_OPT += -DHAS_DASHBOARD
    MCAL_OPT += -DHAS_DASHBOARD_PROC

    SOURCES_C += $(DASHBOARD_DRV_DIR)/dashboard.c

    ifeq ($(DIAG),Y)
        MCAL_OPT += -DHAS_DASHBOARD_DIAG
        SOURCES_C += $(DASHBOARD_DRV_DIR)/dashboard_diag.c
    endif

    ifeq ($(DASHBOARD_COMMANDS),Y)
        MCAL_OPT += -DHAS_DASHBOARD_COMMANDS
        # $(error DASHBOARD_COMMANDS= $(DASHBOARD_COMMANDS))
        SOURCES_C +=  $(DASHBOARD_DRV_DIR)/dashboard_commands.c
    endif
endif