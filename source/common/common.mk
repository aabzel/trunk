$(info COMMON_MK_INC=  $(COMMON_MK_INC) )
ifneq ($(COMMON_MK_INC),Y)
    COMMON_MK_INC=Y

    #@echo $(error COMMON=$(COMMON))

    COMMON_DIR = $(WORKSPACE_LOC)/common
    #@echo $(error COMMON_DIR=$(COMMON_DIR))
    #@echo $(error CFLAGS=$(CFLAGS))
    OPT += -DHAS_COMMON

    INCDIR += -I$(COMMON_DIR)

    ifeq ($(DIAG),Y)
        SOURCES_C += $(COMMON_DIR)/shared_array.c
        SOURCES_C += $(COMMON_DIR)/common_diag.c
    endif

    ifeq ($(SUPER_LOOP),Y)
        OPT += -DHAS_SUPER_LOOP
    endif

    ifeq ($(CORE_EXT),Y)
        OPT += -DHAS_CORE_EXT
    endif

    ifeq ($(SYS_INIT),Y)
        OPT += -DHAS_SYS_INIT
    endif

    SOURCES_C += $(COMMON_DIR)/common_functions.c

    include $(COMMON_DIR)/code_generator/code_generator.mk

    ifeq ($(MULTIMEDIA),Y)
        #@echo $(error MULTIMEDIA=$(MULTIMEDIA))
        OPT += -DHAS_MULTIMEDIA
        INCDIR += -I$(COMMON_DIR)/multimedia
        ifeq ($(MULTIMEDIA_COMMANDS),Y)
            #@echo $(error MULTIMEDIA_COMMANDS=$(MULTIMEDIA_COMMANDS))
            OPT += -DHAS_MULTIMEDIA_COMMANDS
            SOURCES_C += $(COMMON_DIR)/multimedia/multimedia_commands.c
        endif
        SOURCES_C += $(COMMON_DIR)/multimedia/proc_multimedia.c
    endif

endif