$(info LIMITER_MK_INC=$(LIMITER_MK_INC))
ifneq ($(LIMITER_MK_INC),Y)
    LIMITER_MK_INC=Y

    LIMITER_DIR = $(COMPUTING_DIR)/limiter
    # $(error LIMITER_DIR=$(LIMITER_DIR))
    INCDIR += -I$(LIMITER_DIR)

    MCAL_OPT += -DHAS_LIMITER

    ifeq ($(LIMITER_EXT),Y)
        MCAL_OPT += -DHAS_LIMITER_EXT
    endif

    SOURCES_C += $(LIMITER_DIR)/limiter.c

    ifeq ($(LIMITER_DIAG),Y)
          MCAL_OPT += -DHAS_LIMITER_DIAG
          SOURCES_C += $(LIMITER_DIR)/limiter_diag.c
    endif

    ifeq ($(CLI),Y)
        #@echo $(error LIMITER_COMMANDS=$(LIMITER_COMMANDS))
        ifeq ($(LIMITER_COMMANDS),Y)
            MCAL_OPT += -DHAS_LIMITER_COMMANDS
            SOURCES_C += $(LIMITER_DIR)/limiter_commands.c
        endif
    endif
endif
