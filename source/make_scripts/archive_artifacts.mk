$(info ArchiveArtifactsScript)


TIME_STAMP_FILE = $(BUILD_DIR)/time_stamp.txt
FILES_TO_PACK += $(TIME_STAMP_FILE)
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).pdf
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).svg
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).jpeg
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET)_dep.gv
FILES_TO_PACK += $(INIT_ORDER_FILE)
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).map
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).elf
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).hex
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).bin

ARCHIVE_FILE := $(TARGET).tar

.PHONY: compose_time_stamp
compose_time_stamp:
	$(info ComposeTimeStamp)
	$(info TIME_STAMP_FILE=$(TIME_STAMP_FILE))
	$(shell date > $(TIME_STAMP_FILE))


.PHONY: archive_artifacts
archive_artifacts: compose_time_stamp generate_dep auto_version_target auto_init
	$(info BUILD_DIR=$(BUILD_DIR))
	$(info FILES_TO_PACK=$(FILES_TO_PACK))
	$(info ARCHIVE_FILE=$(ARCHIVE_FILE))
	$(info Archive Artifacts...)
	tar.exe -v -f $(ARCHIVE_FILE) -c $(FILES_TO_PACK) --



