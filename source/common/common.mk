$(info COMMON_MK_INC=  $(COMMON_MK_INC) )
ifneq ($(COMMON_MK_INC),Y)
    COMMON_MK_INC=Y

    # $(error COMMON=$(COMMON))

    COMMON_DIR = $(WORKSPACE_LOC)/common
    # $(error COMMON_DIR=$(COMMON_DIR))

    MCAL_OPT += -DHAS_COMMON

    INCDIR += -I$(COMMON_DIR)

    ifeq ($(DIAG),Y)
        MCAL_OPT += -DHAS_COMMON_DIAG
        SOURCES_C += $(COMMON_DIR)/shared_array.c
        SOURCES_C += $(COMMON_DIR)/common_diag.c
    endif

    ifeq ($(SUPER_LOOP),Y)
        MCAL_OPT += -DHAS_SUPER_LOOP
    endif

    ifeq ($(CORE_EXT),Y)
        MCAL_OPT += -DHAS_CORE_EXT
    endif

    ifeq ($(SYS_INIT),Y)
        MCAL_OPT += -DHAS_SYS_INIT
    endif

    SOURCES_C += $(COMMON_DIR)/common_functions.c

    ifeq ($(CLI),Y)
        MCAL_OPT += -DHAS_COMMON_COMMANDS
        SOURCES_C += $(COMMON_DIR)/common_commands.c
    endif

    include $(COMMON_DIR)/code_generator/code_generator.mk

    ifeq ($(SW_COMPONENT),Y)
        # $(error SW_COMPONENT=$(SW_COMPONENT))
        include $(COMMON_DIR)/sw_component/sw_component.mk
    endif

    ifeq ($(MULTIMEDIA),Y)
        MCAL_OPT += -DHAS_MULTIMEDIA
        INCDIR += -I$(COMMON_DIR)/multimedia
        ifeq ($(MULTIMEDIA_COMMANDS),Y)
            # $(error MULTIMEDIA_COMMANDS=$(MULTIMEDIA_COMMANDS))
            MCAL_OPT += -DHAS_MULTIMEDIA_COMMANDS
            SOURCES_C += $(COMMON_DIR)/multimedia/multimedia_commands.c
        endif
        SOURCES_C += $(COMMON_DIR)/multimedia/proc_multimedia.c
    endif

endif