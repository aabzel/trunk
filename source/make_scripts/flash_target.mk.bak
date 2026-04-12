$(info FlashTargetScript)

MAKE_SCRIPTS=$(WORKSPACE_LOC)/make_scripts

FLASH_TARGET=

ifeq ($(ARTERY), Y)
    FLASH_TARGET += flash_artery
endif

ifeq ($(CC26X2), Y)
    FLASH_TARGET += flash_cc26x2
endif

ifeq ($(ESP32), Y)
    FLASH_TARGET += flash_esp32
endif

ifeq ($(MIK32), Y)
    FLASH_TARGET += flash_mik32
endif

ifeq ($(MILANDR), Y)
    FLASH_TARGET += flash_mdr32
endif

ifeq ($(NORDIC), Y)
    FLASH_TARGET += flash_nordic
endif

ifeq ($(STM), Y)
    FLASH_TARGET += flash_stm32
endif

# make flash
.PHONY: flash
flash: $(FLASH_TARGET)
	$(info FlashTargetDone)


ifeq ($(ARTERY), Y)
    include $(MAKE_SCRIPTS)/flash_artery.mk
endif

ifeq ($(CC26X2), Y)
    include $(MAKE_SCRIPTS)/flash_cc26x2.mk
endif

ifeq ($(ESP32), Y)
    include $(MAKE_SCRIPTS)/flash_esp32.mk
endif

ifeq ($(MIK32), Y)
    include $(MAKE_SCRIPTS)/flash_mik32.mk
endif

ifeq ($(MILANDR), Y)
    include $(MAKE_SCRIPTS)/flash_mdr32.mk
endif

ifeq ($(NORDIC), Y)
    include $(MAKE_SCRIPTS)/flash_nordic.mk
endif

ifeq ($(STM), Y)
    include $(MAKE_SCRIPTS)/flash_stm32.mk
endif
