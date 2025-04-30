
ifneq ($(AES256_GENERAL_PRECONFIG_MK_INC),Y)
    AES256_GENERAL_PRECONFIG_MK_INC=Y

    AES256_GENERAL_DIR = $(SECURITY_DIR)/aes256_general

    AES256=Y

    ifeq ($(AES256_V1),Y)
        include $(AES256_GENERAL_DIR)/aes256_v1/aes256_v1_preconfig.mk
    else
        include $(AES256_GENERAL_DIR)/aes256/aes256_preconfig.mk
    endif

endif
