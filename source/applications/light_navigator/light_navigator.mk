ifneq ($(LIGHT_NAVIGATOR_MK_INC),Y)
    LIGHT_NAVIGATOR_MK_INC=Y

    LIGHT_NAVIGATOR_DIR = $(APPLICATIONS_DIR)/light_navigator

    #@ echo $(error LIGHT_NAVIGATOR_DIR = $(LIGHT_NAVIGATOR_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_LIGHT_NAVIGATOR
    OPT += -DHAS_LIGHT_NAVIGATOR_PROC

    INCDIR += -I$(LIGHT_NAVIGATOR_DIR)

    SOURCES_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator.c
    SOURCES_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_diag.c
    #SOURCES_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_config.c

    ifeq ($(CLI),Y)
        ifeq ($(LIGHT_NAVIGATOR_COMMANDS),Y)
            OPT += -DHAS_LIGHT_NAVIGATOR_COMMANDS
            SOURCES_C += $(LIGHT_NAVIGATOR_DIR)/light_navigator_commands.c
        endif
    endif
endif


