ifneq ($(C_GENERATOR_MK_INC),Y)
    C_GENERATOR_MK_INC=Y

    C_GENERATOR_DIR = $(APPLICATIONS_DIR)/c_generator
    #@ echo $(error C_GENERATOR_DIR = $(C_GENERATOR_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_C_GENERATOR


    INCDIR += -I$(C_GENERATOR_DIR)

    SOURCES_C += $(C_GENERATOR_DIR)/c_generator.c
    SOURCES_C += $(C_GENERATOR_DIR)/c_generator_config.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(C_GENERATOR_DIR)/c_generator_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(C_GENERATOR_COMMANDS),Y)
            OPT += -DHAS_C_GENERATOR_COMMANDS
            SOURCES_C += $(C_GENERATOR_DIR)/c_generator_commands.c
        endif
    endif
endif


