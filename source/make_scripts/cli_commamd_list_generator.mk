$(info cli_commamd_list_generator)
$(info MK_PATH=$(MK_PATH))
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))
$(info MK_PATH_WIN=$(MK_PATH_WIN))
ARTEFACTS_DIR=$(MK_PATH_WIN)$(BUILD_DIR)
PREPROC_DIR=$(ARTEFACTS_DIR)/preprocessor/

# https://gcc.gnu.org/onlinedocs/gcc/Preprocessor-Options.html
#$(info SOURCES_C=$(SOURCES_C))

#SOURCES_PP := $(subst .c,.pp, $(SOURCES_C))
#SOURCES_PP := $(subst $(WORKSPACE_LOC),$(PREPROC_DIR), $(SOURCES_PP))
#$(info SOURCES_PP=$(SOURCES_PP))  
PREPROCESSOR_OPT += -E
PREPROCESSOR_OPT += -fmax-include-depth=20
PREPROCESSOR_OPT += -ftabstop=4
PREPROCESSOR_OPT += -P
PREPROCESSOR_OPT += -trigraphs

#CLI_COMMAND_FILE=$(WORKSPACE_LOC)/connectivity/protocols/cli_drv/cli_commands.h
CLI_COMMAND_FILE=$(WORKSPACE_LOC)/connectivity/protocols/cli_drv/cli_general_config.c
#CLI_COMMAND_FILE=C:/1_job/0_NPP_IT_ELMA/code_base_workspace/code_base_firmware/source/projects/ble_audio_evb_v1_nortos_prototype_m/../../connectivity/protocols/cli_drv/cli_commands.h

.PHONY: cli_commamd_list_generator

cli_commamd_list_generator : preprocess_code_base_init  cli_general_config.pp
	$(info PreprocDone)

cli_general_config.pp: $(CLI_COMMAND_FILE)
	$(info Preproc...)
	$(PREPROCESSOR_TOOL) $(PREPROCESSOR_OPT) $(INCDIR) $(OPT) $^ -o $@
	mv $@ $(PREPROC_DIR)

preprocess_code_base_init: 
	$(info PreprocInit)
	mkdir -p $(PREPROC_DIR)