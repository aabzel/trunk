$(info QUAD_MIX_4FS_MK_INC=$(QUAD_MIX_4FS_MK_INC) )

ifneq ($(QUAD_MIX_4FS_MK_INC),Y)
    QUAD_MIX_4FS_MK_INC=Y

    QUAD_MIX_4FS_DIR = $(DSP_DIR)/quad_mix_4fs
    #@echo $(error QUAD_MIX_4FS_DIR=[$(QUAD_MIX_4FS_DIR)])
    INCDIR += -I$(QUAD_MIX_4FS_DIR)

    MCAL_OPT += -DHAS_QUAD_MIX_4FS

    SOURCES_C += $(QUAD_MIX_4FS_DIR)/quad_mix_4fs.c

    ifeq ($(IQ_DIAG),Y)
        MCAL_OPT += -DHAS_IQ_DIAG
    endif


    ifeq ($(DIAG),Y)
        ifeq ($(QUAD_MIX_4FS_DIAG),Y)
            MCAL_OPT += -DHAS_QUAD_MIX_4FS_DIAG
            SOURCES_C += $(QUAD_MIX_4FS_DIR)/quad_mix_4fs_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(QUAD_MIX_4FS_COMMANDS),Y)
            #@echo $(error QUAD_MIX_4FS_COMMANDS=[$(QUAD_MIX_4FS_COMMANDS)])
            MCAL_OPT += -DHAS_QUAD_MIX_4FS_COMMANDS
            SOURCES_C += $(QUAD_MIX_4FS_DIR)/quad_mix_4fs_commands.c
        endif
    endif
endif






