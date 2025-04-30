ifneq ($(COMPILER_MK_INC),Y)
    COMPILER_MK_INC=Y
    OPT += -DHAS_COMPILER
    COMPILER_DIR = $(WORKSPACE_LOC)/compiler
    #@echo $(error COMPILER_DIR= $(COMPILER_DIR))

    OPT += -DHAS_GCC
    INCDIR += -I$(COMPILER_DIR)


endif