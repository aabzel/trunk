$(info APPS_PRECONFIG_MK_INC=$(APPS_PRECONFIG_MK_INC))

ifneq ($(APPS_PRECONFIG_MK_INC),Y)
    APPS_PRECONFIG_MK_INC=Y

    APPLICATIONS_DIR = $(WORKSPACE_LOC)/applications

    APPLICATIONS=Y

    ifeq ($(AUTO_BRIGHTNESS),Y)
        include $(APPLICATIONS_DIR)/auto_brightness/auto_brightness_preconfig.mk
    endif
    
    ifeq ($(AUTO_VOLUME),Y)
        include $(APPLICATIONS_DIR)/auto_volume/auto_volume_preconfig.mk
    endif

    ifeq ($(AUTO_VERSION),Y)
        include $(APPLICATIONS_DIR)/auto_version/auto_version_preconfig.mk
    endif

    ifeq ($(DASHBOARD),Y)
        include $(APPLICATIONS_DIR)/dashboard/dashboard_preconfig.mk
    endif

    ifeq ($(END_OF_BLOCK),Y)
        include $(APPLICATIONS_DIR)/end_of_block/end_of_block_preconfig.mk
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        include $(APPLICATIONS_DIR)/light_navigator/light_navigator_preconfig.mk
    endif

    ifeq ($(PASTILDA),Y)
        #@echo $(error PASTILDA=$(PASTILDA))
        include $(APPLICATIONS_DIR)/pastilda/pastilda_preconfig.mk
    endif

    ifeq ($(KEYLOG),Y)
        include $(APPLICATIONS_DIR)/keylog/keylog_preconfig.mk
    endif

    ifeq ($(SONAR),Y)
        include $(APPLICATIONS_DIR)/sonar/sonar_preconfig.mk
    endif
    
    ifeq ($(SOUND_LOCALIZATION),Y)
        include $(APPLICATIONS_DIR)/sound_localization/sound_localization_preconfig.mk
    endif
endif
