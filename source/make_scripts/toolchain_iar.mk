
# binaries
#IAR_PATH=""
$(info IAR_PATH=$(IAR_PATH))

# The gcc compiler bin path can be either defined in make command via IAR_PATH
# variable (> make IAR_PATH=xxx)
# either it can be added to the PATH environment variable.
ifdef IAR_PATH
    $(info WithPath)
    PREPROCESSOR_TOOL =$(IAR_PATH)/$(PREFIX)iccarm.exe
    CC = $(IAR_PATH)/$(PREFIX)iccarm.exe
    AS = $(IAR_PATH)/$(PREFIX)iasmarm.exe
    ELF_TOOL = $(IAR_PATH)/$(PREFIX)ielftool.exe
    AR = $(IAR_PATH)/$(PREFIX)iarchive.exe
    LD = $(IAR_PATH)/$(PREFIX)ilinkarm.exe
else
    $(info WithOutPath)
    PREPROCESSOR_TOOL = $(PREFIX)iccarm.exe
    CC = $(PREFIX)iccarm.exe
    AS = $(PREFIX)iasmarm.exe
    ELF_TOOL = $(PREFIX)ielftool.exe
    AR = $(PREFIX)iarchive.exe
    LD = $(PREFIX)ilinkarm.exe
endif

MAIN_TARGET_FILE=$(TARGET).out


HEX = $(ELF_TOOL) --ihex --verbose
BIN = $(ELF_TOOL) --bin --verbose  
