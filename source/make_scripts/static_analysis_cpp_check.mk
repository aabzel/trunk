$(info static_analysis_code_base)
MK_PATH_WIN := $(subst /cygdrive/c/,C:/, $(MK_PATH))
ARTEFACTS_DIR=$(MK_PATH_WIN)$(BUILD_DIR)
REPORT_DIR=$(ARTEFACTS_DIR)/static_analysis/

# make cpp_check

INCDIR := $(subst /cygdrive/c/,C:/, $(INCDIR))
#$(info INCDIR=$(INCDIR))
$(info WORKSPACE_LOC=$(WORKSPACE_LOC))
WORKSPACE_LOC := $(subst /cygdrive/c/,C:/, $(WORKSPACE_LOC))
$(info WORKSPACE_LOC=$(WORKSPACE_LOC))
#$(error WORKSPACE_LOC=$(WORKSPACE_LOC))

INCDIR += -I$(WORKSPACE_LOC)
    
STATIC_ANALYSIS_TOOL="C:/Program Files/Cppcheck/cppcheck.exe"

#see https://habr.com/ru/articles/210256/
CPP_CHECK_OPT += -q
CPP_CHECK_OPT += --enable=all
CPP_CHECK_OPT += --suppress=sprintfOverlappingData
CPP_CHECK_OPT += --suppress=preprocessorErrorDirective
CPP_CHECK_OPT += --suppress=variableScope
CPP_CHECK_OPT += --suppress=unreadVariable
CPP_CHECK_OPT += --suppress=unmatchedSuppression
CPP_CHECK_OPT += --suppress=missingIncludeSystem
CPP_CHECK_OPT += --suppress=unusedFunction
CPP_CHECK_OPT += --suppress=missingInclude
CPP_CHECK_OPT += --suppress=redundantAssignment
CPP_CHECK_OPT += --suppress=strdupCalled
CPP_CHECK_OPT += --suppress=knownConditionTrueFalse
CPP_CHECK_OPT += --suppress=constParameter
CPP_CHECK_OPT += --suppress=nullPointerRedundantCheck
CPP_CHECK_OPT += --suppress=invalidPrintfArgType_uint

#$(info SOURCES_C=$(SOURCES_C))

SOURCES_SA := $(subst .c,.sa, $(SOURCES_C))

.PHONY: cpp_check

cpp_check: $(SOURCES_SA)
	$(info CppCheckDone!)

%.sa:  %.c
	$(info CppCheckOne...)
	cd $(dir $<) && pwd && $(STATIC_ANALYSIS_TOOL) $(CPP_CHECK_OPT) $(INCDIR) $(OPT) $(notdir $<)


