$(info Flash Artery MCU Script)


ARTERY_DEVICE=AT32F435ZMT7

#FIRMWARE_BINARY_FILE=$(MK_PATH)$(BUILD_DIR)\$(TARGET).bin
FIRMWARE_BINARY_FILE=$(BUILD_DIR)\$(TARGET).bin
VENDOR_FLASH_CLI_TOOL=ATLink_Console.exe
VENDOR_FLASH_CLI_OPTIONS=
VENDOR_FLASH_CLI_OPTIONS += -device $(ARTERY_DEVICE)
VENDOR_FLASH_CLI_OPTIONS += -connect -p --dfap 
VENDOR_FLASH_CLI_OPTIONS += --depp 
VENDOR_FLASH_CLI_OPTIONS += -d --a 08000000 
VENDOR_FLASH_CLI_OPTIONS += --fn $(FIRMWARE_BINARY_FILE) 
VENDOR_FLASH_CLI_OPTIONS += --v  
VENDOR_FLASH_CLI_OPTIONS += -r

.PHONY: flash_artery
flash_artery: $(FIRMWARE_BINARY_FILE)
	$(info Flash File:$(FIRMWARE_BINARY_FILE) ...)
	$(VENDOR_FLASH_CLI_TOOL) $(VENDOR_FLASH_CLI_OPTIONS)
	$(info FlashArteryMCUTargetDone)

#ATLink_Console.exe -device AT32F435ZMT7 -connect -p --dfap  --depp  -d --a 08000000  --fn  C:/projects/code_base_workspace/era_test/source/projects/tera_test_nortos_nau8814_m/build/tera_test_nortos_nau8814_m.bin  --v   -r

# ATLink_Console File format error, please reselect!