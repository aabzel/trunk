ifneq ($(SECURITY_PRECONFIG_MK_INC),Y)
    SECURITY_PRECONFIG_MK_INC=Y

    SECURITY=Y
    SECURITY_DIR = $(WORKSPACE_LOC)/security
    #@echo $(error SECURITY_DIR= $(SECURITY_DIR))

    ifeq ($(AES256),Y)
        #@echo $(error AES256=$(AES256))
        include $(SECURITY_DIR)/aes256_general/aes256_general_preconfig.mk
    endif

    ifeq ($(KEEPASS),Y)
        #@echo $(error KEEPASS=$(KEEPASS))
        include $(SECURITY_DIR)/keepass/keepass_preconfig.mk
    endif

    ifeq ($(SALSA20),Y)
        include $(SECURITY_DIR)/salsa20/salsa20_preconfig.mk
    endif

    ifeq ($(CRYPTO),Y)
        #@echo $(error WIN=$(WIN))
        include $(SECURITY_DIR)/crypto/crypto_preconfig.mk
    endif

endif