$(info static_analysis_code_base)
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))
ARTEFACTS_DIR=$(MK_PATH_WIN)$(BUILD_DIR)
REPORT_DIR=$(ARTEFACTS_DIR)/static_analysis/


INCDIR := $(subst /cygdrive/c/,C:/, $(INCDIR))
#$(info INCDIR=$(INCDIR))
WORKSPACE_LOC := $(subst /cygdrive/c/,C:/, $(WORKSPACE_LOC))
#$(error WORKSPACE_LOC=$(WORKSPACE_LOC))

STATIC_ANALYSIS_TOOL=splint.exe

SPLINT_OPT += -noeffect
SPLINT_OPT += -retvalbool
SPLINT_OPT += -globstate
SPLINT_OPT += -temptrans
SPLINT_OPT += -mayaliasunique
SPLINT_OPT += -fullinitblock
SPLINT_OPT += -branchstate
SPLINT_OPT += -unrecog
SPLINT_OPT += -nullret
SPLINT_OPT += -predboolint
SPLINT_OPT += -mustfreefresh
SPLINT_OPT += -unsignedcompare
SPLINT_OPT += -compdef
SPLINT_OPT += -immediatetrans
SPLINT_OPT += -exportlocal
SPLINT_OPT += -mustfreeonly
SPLINT_OPT += -type
SPLINT_OPT += -boolops
SPLINT_OPT += -retvalother
SPLINT_OPT += -retvalint
SPLINT_OPT += -paramuse
SPLINT_OPT += -nestcomment
SPLINT_OPT += -nullassign
#$(info SOURCES_C=$(SOURCES_C))

SOURCES_SA := $(subst .c,.sa, $(SOURCES_C))

.PHONY: static_analysis_code_base

static_analysis_code_base : $(SOURCES_SA)

%.sa:  %.c
	cd $(dir $<) && pwd && $(STATIC_ANALYSIS_TOOL) -preproc $(SPLINT_OPT) $(INCDIR) $(OPT) $(notdir $<)


