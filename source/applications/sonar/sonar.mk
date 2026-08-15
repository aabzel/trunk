ifneq ($(SONAR_MK_INC),Y)
    SONAR_MK_INC=Y

    SONAR_DIR = $(APPLICATIONS_DIR)/sonar

    #@ echo $(error SONAR_DIR = $(SONAR_DIR))
    MCAL_OPT += -DHAS_SONAR
    MCAL_OPT += -DHAS_SONAR_PROC

    INCDIR += -I$(SONAR_DIR)

    SOURCES_C += $(SONAR_DIR)/sonar.c

    ifeq ($(SONAR_DIAG),Y)
        SOURCES_C += $(SONAR_DIR)/sonar_diag.c
    endif
    #SOURCES_C += $(SONAR_DIR)/sonar_config.c

    ifeq ($(CLI),Y)
        ifeq ($(SONAR_COMMANDS),Y)
            MCAL_OPT += -DHAS_SONAR_COMMANDS
            SOURCES_C += $(SONAR_DIR)/sonar_commands.c
        endif
    endif
endif


