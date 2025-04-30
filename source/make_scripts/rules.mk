CSTANDARD = -std=c99
#CSTANDARD = -std=c11 c99
#CSTANDARD = -std=gnu99

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info mkfile_path:$(mkfile_path) )
#$(info MAKE:$(MAKE))
#$(info MAKEFILE_LIST:$(MAKEFILE_LIST))
MK_PATH := $(subst /cygdrive/c/,C:/, $(MK_PATH))
$(info MK_PATH=$(MK_PATH))

BUILD_DIR=build

EXTRA_TARGETS=

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

#@echo $(error DEPENDENCY_GRAPH=$(DEPENDENCY_GRAPH))

INCDIR := $(subst /cygdrive/c/,C:/, $(INCDIR))
#@echo $(error INCDIR=$(INCDIR))
#$(error SOURCES_DIAG_C=$(SOURCES_DIAG_C))
#$(error SOURCES_THIRD_PARTY_C=$(SOURCES_THIRD_PARTY_C))
SOURCES_TOTAL_C += $(SOURCES_C)
SOURCES_TOTAL_C += $(SOURCES_DIAG_C)
SOURCES_TOTAL_C += $(SOURCES_CONFIGURATION_C)
SOURCES_TOTAL_C += $(SOURCES_THIRD_PARTY_C)
SOURCES_TOTAL_C := $(subst /cygdrive/c/,C:/, $(SOURCES_TOTAL_C))
#@echo $(error SOURCES_TOTAL_C=$(SOURCES_TOTAL_C))

SOURCES_ASM := $(subst /cygdrive/c/,C:/, $(SOURCES_ASM))
#@echo $(error SOURCES_ASM=$(SOURCES_ASM))

LIBS  := $(subst /cygdrive/c/,C:/, $(LIBS))
LDSCRIPT := $(subst /cygdrive/c/,C:/, $(LDSCRIPT))
#@echo $(error SOURCES_ASM=$(SOURCES_ASM))


WORKSPACE_LOC := $(realpath  $(WORKSPACE_LOC))
WORKSPACE_LOC := $(subst /cygdrive/c/,C:/, $(WORKSPACE_LOC))

include $(WORKSPACE_LOC)/make_scripts/toolchain.mk
# CFLAGS
#https://gcc.gnu.org/onlinedocs/gcc/ARM-Options.html
AS_DEFS = 
AS_INCLUDES = 
# OPT_C += -O0

include $(WORKSPACE_LOC)/make_scripts/compiler_options.mk
#include $(WORKSPACE_LOC)/make_scripts/error_options.mk
#include $(WORKSPACE_LOC)/make_scripts/warning_options.mk
include $(WORKSPACE_LOC)/make_scripts/linker_options.mk

#OPT_C += -finline-small-functions
#OPT_C += -fmessage-length=0
#OPT_C += -fno-common
#OPT_C += -fsigned-char
#OPT_C += -fstack-usage
#OPT_C += -fzero-initialized-in-bss

OPT += $(OPT_C)

ASFLAGS += $(MCU)
ASFLAGS += $(AS_DEFS)
ASFLAGS += $(AS_INCLUDES)
ASFLAGS += $(OPT)
ASFLAGS += $(COMPILE_OPT)
ASFLAGS += -Wall
ASFLAGS +=-fdata-sections
ASFLAGS += -ffunction-sections


#CFLAGS += $(CSTANDARD)
#CFLAGS += -Wformat-overflow=1
#CFLAGS += $(MCU) $(OPT) -fdata-sections -ffunction-sections $(INCDIR)


#CPP_FLAGS += $(CSTANDARD) $(INCDIR)  $(OPT)
# LDFLAGS




#@echo $(error LDSCRIPT=$(LDSCRIPT))
LIBDIR = 


EXTRA_TARGETS += sort_config
EXTRA_TARGETS += archive_artifacts
EXTRA_TARGETS += generate_definitions
ifeq ($(AUTO_INIT), Y)
    EXTRA_TARGETS += auto_init
endif

ARTIFACTS += $(BUILD_DIR)/$(TARGET).bin
ARTIFACTS += $(BUILD_DIR)/$(TARGET).hex
ARTIFACTS += $(BUILD_DIR)/$(TARGET).elf

.PHONY: all

# default action: build all 
all: $(EXTRA_TARGETS) $(ARTIFACTS)

.PHONY: generate_definitions

generate_definitions:
	$(info GenerateDefinitions...)
	$(PREPROCESSOR_TOOL) $(CPP_FLAGS) $(WORKSPACE_LOC)/empty_source.c -dM -E> c_defines_generated.h
	$(SORTER_TOOL) -u c_defines_generated.h -o c_defines_generated.h

# build the application
# list of objects
OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_TOTAL_C:.c=.o)))

vpath %.c $(sort $(dir $(SOURCES_TOTAL_C)))

# list of ASM program objects
OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_ASM:.S=.o)))
vpath %.S $(sort $(dir $(SOURCES_ASM)))

TOTAL_FILES := $(words $(OBJECTS))
$(info TOTAL_FILES:$(TOTAL_FILES) )

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(eval CURRENT_CNT=$(shell echo $$(($(CURRENT_CNT)+1))))
	@echo Compiling $(CURRENT_CNT)/$(TOTAL_FILES) $@
	@ $(CC) -c -MD $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	@#$(CC) -c -MD $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@

$(BUILD_DIR)/$(TARGET).elf: $(OBJECTS) Makefile
	$(CC) $(OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(HEX) $< $@
	
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/%.elf | $(BUILD_DIR)
	$(BIN) $< $@	


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
include $(WORKSPACE_LOC)/make_scripts/flash_target.mk


ifeq ($(AUTO_VERSION_BUILD), Y)
    include $(WORKSPACE_LOC)/make_scripts/auto_version_target.mk
endif

ifeq ($(DEPENDENCIES_GRAPHVIZ), Y)
    include $(WORKSPACE_LOC)/make_scripts/generate_dependencies.mk
endif

$(BUILD_DIR):
	mkdir -p $@

# clean up
.PHONY: clean

clean:
	-rm -fR $(BUILD_DIR)

# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***