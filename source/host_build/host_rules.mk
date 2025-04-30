

#@echo $(error dddd)

#MK_PATH :=$(subst /cygdrive/c/,C:/, $(MK_PATH))
OBJECTS= $(patsubst %.c, %.o, $(SOURCES_C))
OBJECTS= $(subst /cygdrive/c/,C:/, $(OBJECTS))
SOURCES_C := $(subst /cygdrive/c/,C:/, $(SOURCES_C))


INCDIR := $(subst /cygdrive/c/,C:/, $(INCDIR))

SOURCES_TOTAL_C += $(SOURCES_C)
SOURCES_TOTAL_C += $(SOURCES_DIAG_C)
SOURCES_TOTAL_C += $(SOURCES_CONFIGURATION_C)
SOURCES_TOTAL_C += $(SOURCES_THIRD_PARTY_C)
SOURCES_TOTAL_C := $(subst /cygdrive/c/,C:/, $(SOURCES_TOTAL_C))
#@echo  $(error SOURCES_TOTAL_C=$(SOURCES_TOTAL_C))


#@echo $(error MK_PATH=$(MK_PATH))

BUILD_DIR:=build
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_TOTAL_C:.c=.o)))

#vpath pattern path: Specify a search path for files matching a �%� pattern.
vpath %.c $(sort $(dir $(SOURCES_TOTAL_C)))
TOTAL_FILES := $(words $(OBJECTS))
#@echo $(error TOTAL_FILES $(TOTAL_FILES) )

#@echo $(error OBJECTS= $(OBJECTS))

#@echo $(error SOURCES_C= $(SOURCES_C))
#@echo $(error INCDIR= $(INCDIR))

INCDIR += -I$(MK_PATH)
INCDIR += -I$(WORKSPACE_LOC)

WORKSPACE_LOC:= $(realpath $(WORKSPACE_LOC))
WORKSPACE_LOC := $(subst /cygdrive/c/,C:/, $(WORKSPACE_LOC))
$(info  WORKSPACE_LOC= $(WORKSPACE_LOC))

BUILDDIR := $(MK_PATH)/Build

SRC_PATH :=  $(dir $(abspath $(dir $$PWD)))
#@echo $(error SRC_PATH=$(SRC_PATH))

ifeq ($(STATIC_ANALYSIS_SP_LINT), Y)
    EXTRA_TARGETS += static_analysis_sp_lint
endif

ifeq ($(STATIC_ANALYSIS_CPP_CHECK), Y)
    EXTRA_TARGETS += static_analysis_cpp_check
endif

ifeq ($(DEPENDENCIES_GRAPHVIZ), Y)
    EXTRA_TARGETS += generate_dep
endif

ifeq ($(PREPROCESSOR), Y)
    EXTRA_TARGETS += preprocess_code_base
endif

ifeq ($(CLI_COMMAMD_GENERATE), Y)
    EXTRA_TARGETS += cli_commamd_list_generator
endif

ifeq ($(AUTO_VERSION_BUILD), Y)
    EXTRA_TARGETS += auto_version_target
endif

generate_definitions:
	$(info GenerateDefinitions...)
	$(PREPROCESSOR_TOOL) $(CPP_FLAGS) $(WORKSPACE_LOC)/empty_sourse.c -dM -E> c_defines_generated.h
	$(SORTER_TOOL) -u c_defines_generated.h -o c_defines_generated.h


include $(WORKSPACE_LOC)/host_build/host_toolchain.mk
include $(WORKSPACE_LOC)/host_build/host_compile_options.mk

.PHONY:all
all: sort_config  $(TARGET) $(EXTRA_TARGETS)

include $(WORKSPACE_LOC)/host_build/host_linker_rules.mk


#@echo $(error OBJECTS= $(OBJECTS))
#.PHONY: compile_done
#compile_done: $(OBJECTS) 
#	@echo CompileDone...

$(BUILD_DIR)/%.o: %.c Makefile   $(BUILD_DIR) 
	@echo Compile C-file ...
	$(eval CURRENT_CNT=$(shell echo $$(($(CURRENT_CNT)+1))))
	#@echo Compiling $(CURRENT_CNT)/$(TOTAL_FILES) $@
	$(CC) $(CFLAGS) $(INCDIR) $(COMPILE_OPT) $(OPT) -c $< -o $@ 

.PHONY: clean
clean:
	@echo Clean...
	rm -rf $(TARGET) $(OBJECTS)
	rm -fR $(BUILD_DIR)

.PHONY:clean_obj
clean_obj:
	@echo CleanObj...
	rm -r $(OBJECTS)


$(BUILD_DIR):
	@echo Create build dir...
	mkdir -p $@

ifeq ($(AUTO_INIT), Y)
    include $(WORKSPACE_LOC)/make_scripts/auto_init.mk
endif

ifeq ($(CLI_COMMAMD_GENERATE), Y)
    include $(WORKSPACE_LOC)/make_scripts/cli_commamd_list_generator.mk
endif

ifeq ($(PREPROCESSOR), Y)
    include $(WORKSPACE_LOC)/make_scripts/preprocessor_only.mk
endif

ifeq ($(STATIC_ANALYSIS_SP_LINT), Y)
    include $(WORKSPACE_LOC)/make_scripts/static_analysis_sp_lint.mk
endif

ifeq ($(STATIC_ANALYSIS_CPP_CHECK), Y)
    include $(WORKSPACE_LOC)/make_scripts/static_analysis_cpp_check.mk
endif

include $(WORKSPACE_LOC)/make_scripts/archive_artifacts.mk
include $(WORKSPACE_LOC)/make_scripts/sort_config.mk
include $(WORKSPACE_LOC)/make_scripts/clang_format.mk

ifeq ($(AUTO_VERSION_BUILD), Y)
    #$(error AUTO_VERSION_BUILD= $(AUTO_VERSION_BUILD))
    include $(WORKSPACE_LOC)/make_scripts/auto_version_target.mk
endif

ifeq ($(DEPENDENCIES_GRAPHVIZ), Y)
    include $(WORKSPACE_LOC)/make_scripts/generate_dependencies.mk
endif


