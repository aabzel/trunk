$(info BASE64_MK_INC=$(BASE64_MK_INC))

ifneq ($(BASE64_MK_INC),Y)
    BASE64_MK_INC=Y


    BASE64_DIR = $(PROTOCOLS_DIR)/base64
    #@echo $(error BASE64_DIR = $(BASE64_DIR))

    MCAL_OPT += -DHAS_BASE64
    INCDIR += -I$(BASE64_DIR)

    SOURCES_C += $(BASE64_DIR)/base64.c
    ifeq ($(DIAG),Y)
        SOURCES_C += $(BASE64_DIR)/base64_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(BASE64_COMMANDS),Y)
            MCAL_OPT += -DHAS_BASE64_COMMANDS
            SOURCES_C += $(BASE64_DIR)/base64_commands.c
        endif
    endif
endif
