$(info APPS_MK_INC=$(APPS_MK_INC))

ifneq ($(APPS_MK_INC),Y)
    APPS_MK_INC=Y

    APPLICATIONS_DIR = $(WORKSPACE_LOC)/applications
    $(info APPLICATIONS_DIR=$(APPLICATIONS_DIR))

    #@echo $(error APPLICATIONS_DIR=$(APPLICATIONS_DIR))
    APPLICATIONS=Y
    OPT += -DHAS_APP
    OPT += -DHAS_APPLICATIONS
    INCDIR += -I$(APPLICATIONS_DIR)

    ifeq ($(FW_LOADER),Y)
        include $(APPLICATIONS_DIR)/fw_loader/fw_loader.mk
    endif

    ifeq ($(AUTO_BRIGHTNESS),Y)
        include $(APPLICATIONS_DIR)/auto_brightness/auto_brightness.mk
    endif

    ifeq ($(SOUND_LOCALIZATION),Y)
        include $(APPLICATIONS_DIR)/sound_localization/sound_localization.mk
    endif

    ifeq ($(END_OF_BLOCK),Y)
        include $(APPLICATIONS_DIR)/end_of_block/end_of_block.mk
    endif


    ifeq ($(SONAR),Y)
        include $(APPLICATIONS_DIR)/sonar/sonar.mk
    endif


    ifeq ($(CODE_STYLE_CHECKER),Y)
        include $(APPLICATIONS_DIR)/code_style_checker/code_style_checker.mk
    endif

    ifeq ($(AUTO_VERSION),Y)
        include $(APPLICATIONS_DIR)/auto_version/auto_version.mk
    endif

    ifeq ($(AUTO_VOLUME),Y)
        include $(APPLICATIONS_DIR)/auto_volume/auto_volume.mk
    endif

    ifeq ($(C_GENERATOR),Y)
        include $(APPLICATIONS_DIR)/c_generator/c_generator.mk
    endif

    ifeq ($(DASHBOARD),Y)
        include $(APPLICATIONS_DIR)/dashboard/dashboard.mk
    endif

    ifeq ($(GRAPHVIZ_TO_TSORT),Y)
        include $(APPLICATIONS_DIR)/graphviz_to_tsort/graphviz_to_tsort.mk
    endif

    ifeq ($(KEYLOG),Y)
        include $(APPLICATIONS_DIR)/keylog/keylog.mk
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        include $(APPLICATIONS_DIR)/light_navigator/light_navigator.mk
    endif

    ifeq ($(PASTILDA),Y)
        #@echo $(error PASTILDA=$(PASTILDA))
        include $(APPLICATIONS_DIR)/pastilda/pastilda.mk
    endif

    ifeq ($(APPLICATIONS_COMMANDS),Y)
        OPT += -DHAS_APPLICATIONS_COMMANDS
        SOURCES_C += $(APPLICATIONS_DIR)/applications_commands.c
    endif
	
endif
