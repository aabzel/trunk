$(info auto_version_script)
$(info MK_PATH=$(MK_PATH))
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))
$(info MK_PATH_WIN=$(MK_PATH_WIN))

$(info WORKSPACE_LOC=$(WORKSPACE_LOC))
WORKSPACE_LOC := $(subst /cygdrive/c/,C:/, $(WORKSPACE_LOC))
$(info WORKSPACE_LOC=$(WORKSPACE_LOC))
#$(error WORKSPACE_LOC=$(WORKSPACE_LOC))

AUTO_VERSION_TOOL=$(WORKSPACE_LOC)/../tool/auto_version_build.exe
$(info AUTO_VERSION_TOOL=$(AUTO_VERSION_TOOL))

.PHONY: auto_version_target

auto_version_target: $(ARTIFACTS)
	$(info RunAutoVersionTarget)
	cd $(MK_PATH_WIN) && $(AUTO_VERSION_TOOL) avp version_auto.h
