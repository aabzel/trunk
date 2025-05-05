ifneq ($(CODE_STYLE_CHECKER_MK_INC),Y)
    CODE_STYLE_CHECKER_MK_INC=Y

    CODE_STYLE_CHECKER_DIR = $(APPLICATIONS_DIR)/code_style_checker
    #@ echo $(error CODE_STYLE_CHECKER_DIR = $(CODE_STYLE_CHECKER_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_CODE_STYLE_CHECKER


    INCDIR += -I$(CODE_STYLE_CHECKER_DIR)

    SOURCES_C += $(CODE_STYLE_CHECKER_DIR)/code_style_checker.c
    SOURCES_C += $(CODE_STYLE_CHECKER_DIR)/code_style_checker_config.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(CODE_STYLE_CHECKER_DIR)/code_style_checker_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CODE_STYLE_CHECKER_COMMANDS),Y)
            OPT += -DHAS_CODE_STYLE_CHECKER_COMMANDS
            SOURCES_C += $(CODE_STYLE_CHECKER_DIR)/code_style_checker_commands.c
        endif
    endif
endif


