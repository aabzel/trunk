ifneq ($(AUTO_VERSION_MK_INC),Y)
    AUTO_VERSION_MK_INC=Y

    AUTO_VERSION_DIR = $(APPLICATIONS_DIR)/auto_version
    #@ echo $(error AUTO_VERSION_DIR = $(AUTO_VERSION_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_AUTO_VERSION

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    INCDIR += -I$(AUTO_VERSION_DIR)

    SOURCES_C += $(AUTO_VERSION_DIR)/auto_version.c
    SOURCES_C += $(AUTO_VERSION_DIR)/auto_version_config.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(AUTO_VERSION_DIR)/auto_version_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(AUTO_VERSION_COMMANDS),Y)
            OPT += -DHAS_AUTO_VERSION_COMMANDS
            SOURCES_C += $(AUTO_VERSION_DIR)/auto_version_commands.c
        endif
    endif
endif


