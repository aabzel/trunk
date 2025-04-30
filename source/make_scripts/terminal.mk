$(info TERMINAL_MK_INC=$(TERMINAL_MK_INC))

ifneq ($(TERMINAL_MK_INC),Y)
    TERMINAL_MK_INC=Y

    $(info Add Debug CLI Terminal(Shell) )

    #BIN_2_STR=Y
    CLI=Y
    #CLI_CMD_HISTORY=Y
    CLI_NATIVE_COMMANDS=Y
    CONNECTIVITY=Y
    FIFO=Y
    FIFO_CHAR=Y
    FIFO_INDEX=Y
    LOG=Y
    #LOG_COMMANDS=Y
    #Not All builds needs time stamp (e.g. USB HID CLI)
    #LOG_TIME_STAMP=Y
    PROTOCOLS=Y
    STREAM=Y
    STRING=Y
    STRING_PARSER=Y
    SYSTEM=Y
 
    CUSTOM_PRINTF=Y

    #include $(WORKSPACE_LOC)/components/log/log.mk
    #include $(WORKSPACE_LOC)/protocols/cli_drv/cli_drv.mk
endif
