ifneq ($(HEX_BIN_PRECONFIG_INC),Y)
    HEX_BIN_PRECONFIG_INC=Y

    #@ echo $(error HEX_BIN_DIR = $(HEX_BIN_DIR))
    HEX_BIN=Y
    FILE_API=Y

endif


