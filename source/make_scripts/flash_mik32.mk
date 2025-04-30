$(info Flash Mik32 MCU Script)

FIRMWARE_BINARY_FILE=$(BUILD_DIR)/$(TARGET).hex
#PYTHON_BIN=python.exe
TOOLS_DIR=$(WORKSPACE_LOC)/../tool

TOOLS_DIR:= $(realpath $(TOOLS_DIR))
TOOLS_DIR := $(subst /cygdrive/c/,C:/, $(TOOLS_DIR))
#@echo $(error TOOLS_DIR=$(TOOLS_DIR))

# Probably it will need to disable all apps at port 6666
#   netstat -aon | grep 6666

VENDOR_FLASH_CLI_TOOL:=  $(TOOLS_DIR)/tool_mik32/mik32-uploader/mik32_upload.py
MCU_OPEN_OCD_CONFIG=mik32.cfg
BOARD_OPEN_OCD_CONFIG=start-link.cfg

VENDOR_FLASH_CLI_OPTIONS =
VENDOR_FLASH_CLI_OPTIONS +=  $(FIRMWARE_BINARY_FILE) 
VENDOR_FLASH_CLI_OPTIONS += --run-openocd
VENDOR_FLASH_CLI_OPTIONS += --openocd-exec=openocd.exe
VENDOR_FLASH_CLI_OPTIONS += --openocd-interface=$(BOARD_OPEN_OCD_CONFIG)
VENDOR_FLASH_CLI_OPTIONS += --openocd-target=$(MCU_OPEN_OCD_CONFIG)
VENDOR_FLASH_CLI_OPTIONS += --adapter-speed=3200


.PHONY: flash_mik32
flash_mik32: $(FIRMWARE_BINARY_FILE) $(BOARD_OPEN_OCD_CONFIG) $(MCU_OPEN_OCD_CONFIG)
	$(info Flash File:$(FIRMWARE_BINARY_FILE) ...)
	$(PYTHON_BIN)  $(VENDOR_FLASH_CLI_TOOL) $(VENDOR_FLASH_CLI_OPTIONS)
	$(info Flash Mikron MCU Target Done)

