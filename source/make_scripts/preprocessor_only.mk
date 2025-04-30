$(info preprocess_code_base)
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))
ARTEFACTS_DIR=$(MK_PATH_WIN)$(BUILD_DIR)
PREPROC_DIR=$(ARTEFACTS_DIR)/preprocessor/

#$(info SOURCES_C=$(SOURCES_C))

SOURCES_PP := $(subst .c,.pp, $(SOURCES_C))
#SOURCES_PP := $(subst $(WORKSPACE_LOC),$(PREPROC_DIR), $(SOURCES_PP))
#$(info SOURCES_PP=$(SOURCES_PP))  
CPP_OPT += -E

.PHONY: preprocess_code_base

preprocess_code_base : preprocess_code_base_init $(SOURCES_PP)
	$(info PreprocDone)


%.pp:  %.c
	$(info Preproc...)
	$(PREPROCESSOR_TOOL) -E $(INCDIR) $(OPT) $< -o $@
	mv $@ $(PREPROC_DIR)

.PHONY: preprocess_code_base_init

preprocess_code_base_init: 
	$(info PreprocInit)
	mkdir -p $(PREPROC_DIR)