SORTER_TOOL=C:/cygwin64/bin/sort.exe
$(info Sort Program config)

$(info MK_PATH=$(MK_PATH))
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))

$(info MK_PATH_WIN=$(MK_PATH_WIN))
$(info WORKSPACE_LOC=$(WORKSPACE_LOC))

PROJECT_DIR=$(MK_PATH_WIN)

CONFIG_FILE=$(PROJECT_DIR)/config.mk
$(info CONFIG_FILE=$(CONFIG_FILE))

#CONFIG_FILE:=$(subst /cygdrive/c/,C:/, $(CONFIG_FILE))
#$(info CONFIG_FILE=$(CONFIG_FILE))

.PHONY: sort_config

sort_config: $(CONFIG_FILE)
	$(info SortConfig...)
	$(SORTER_TOOL) -u $(CONFIG_FILE) -o $(CONFIG_FILE)

