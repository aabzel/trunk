$(info ArchiveArtifactsScript)

ARTIFACT_BIN = $(BUILD_DIR)/$(TARGET).bin
ARTIFACT_HEX = $(BUILD_DIR)/$(TARGET).hex
ARTIFACT_ELF = $(BUILD_DIR)/$(TARGET).elf
ARTIFACT_MAP = $(BUILD_DIR)/$(TARGET).map

TIME_STAMP_FILE = $(BUILD_DIR)/time_stamp.txt

FILES_TO_PACK += $(TIME_STAMP_FILE)
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).pdf
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).svg
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET).jpeg
FILES_TO_PACK += $(BUILD_DIR)/$(TARGET)_dep.gv
FILES_TO_PACK += $(INIT_ORDER_FILE)
FILES_TO_PACK += $(ARTIFACT_ELF)
FILES_TO_PACK += $(ARTIFACT_HEX)
FILES_TO_PACK += $(ARTIFACT_MAP)
FILES_TO_PACK += $(ARTIFACT_BIN)

ARCHIVE_FILE := $(TARGET).tar


ifeq ($(AUTO_VERSION_BUILD), Y)
     ARCHIVE_DEPENDENCIES += auto_version_target
endif

# bin files can be modified by Tuner PRO. Thats why we put sha256 inside envelop
.PHONY: calc_sha256
calc_sha256: $(ARTIFACT_BIN)
	$(info CalcSha256)
	$(shell sha256sum -b $(ARTIFACT_BIN) >> $(TIME_STAMP_FILE) )
	$(shell sha256sum -b $(ARTIFACT_HEX) >> $(TIME_STAMP_FILE) )
	$(shell sha256sum -b $(ARTIFACT_ELF) >> $(TIME_STAMP_FILE) )
	$(shell sha256sum -b $(ARTIFACT_MAP) >> $(TIME_STAMP_FILE) )

.PHONY: compose_time_stamp
compose_time_stamp:
	$(info ComposeTimeStamp)
	$(info TIME_STAMP_FILE=$(TIME_STAMP_FILE))
	$(shell date >> $(TIME_STAMP_FILE) )


.PHONY: archive_artifacts
archive_artifacts: compose_time_stamp calc_sha256 generate_dep $(ARCHIVE_DEPENDENCIES) auto_init
	$(info BUILD_DIR=$(BUILD_DIR))
	$(info FILES_TO_PACK=$(FILES_TO_PACK))
	$(info ARCHIVE_FILE=$(ARCHIVE_FILE))
	$(info Archive Artifacts...)
	tar.exe -v -f $(ARCHIVE_FILE) -c $(FILES_TO_PACK) --



