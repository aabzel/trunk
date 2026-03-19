CSTANDARD = -std=c11
SOURCES_TOTAL_C =
#CSTANDARD = -std=c11 c99
#CSTANDARD = -std=gnu99

mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info mkfile_path:$(mkfile_path) )
#$(info MAKE:$(MAKE))
#$(info MAKEFILE_LIST:$(MAKEFILE_LIST))
MK_PATH:=$(subst /cygdrive/c/,C:/,$(MK_PATH))
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
#$(error SOURCES_C=$(SOURCES_C))
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
include $(WORKSPACE_LOC)/make_scripts/compiler_errors.mk
include $(WORKSPACE_LOC)/make_scripts/warning_options.mk
include $(WORKSPACE_LOC)/make_scripts/linker_options.mk

#OPT_C += -finline-small-functions
#OPT_C += -fmessage-length=0
#OPT_C += -fno-common
#OPT_C += -fsigned-char
#OPT_C += -fstack-usage
#OPT_C += -fzero-initialized-in-bss

MCAL_OPT += $(OPT_C)
CFLAGS += $(MCAL_OPT)

ifeq ($(GCC), Y)
    @echo $(error GCC=$(GCC))
    CFLAGS += $(COMPILE_GCC_OPT)
endif

ASFLAGS += $(MCU)
ASFLAGS += $(AS_DEFS)
ASFLAGS += $(AS_INCLUDES)
ASFLAGS += $(MCAL_OPT)
ASFLAGS += $(COMPILE_OPT)
ASFLAGS += -Wall
ASFLAGS +=-fdata-sections
ASFLAGS += -ffunction-sections


#CFLAGS += $(CSTANDARD)
#CFLAGS += -Wformat-overflow=1
#CFLAGS += $(MCU) $(MCAL_OPT) -fdata-sections -ffunction-sections $(INCDIR)


#CPP_FLAGS += $(CSTANDARD) $(INCDIR)  $(MCAL_OPT)
# LDFLAGS




#@echo $(error LDSCRIPT=$(LDSCRIPT))
LIBDIR = 

ifeq ($(ARCHIVE_ARTIFACTS), Y)
    EXTRA_TARGETS += archive_artifacts
endif

ifeq ($(GENERATE_DEFINITIONS), Y)
    EXTRA_TARGETS += generate_definitions
endif

ifeq ($(AUTO_INIT), Y)
    EXTRA_TARGETS += auto_init
endif

ifeq ($(SORT_CONFIG), Y)
    EXTRA_TARGETS += sort_config
endif

ARTIFACTS += $(BUILD_DIR)/$(TARGET).bin
ARTIFACTS += $(BUILD_DIR)/$(TARGET).hex
ARTIFACTS += $(BUILD_DIR)/$(MAIN_TARGET_FILE)

#@echo $(error ARTIFACTS=$(ARTIFACTS))


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
ifeq ($(GCC),Y)
    OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_ASM:.S=.o)))
    #@echo $(error OBJECTS=$(OBJECTS))
endif


#@echo $(error SOURCES_ASM=$(SOURCES_ASM))
ASM_OBJECTS += $(addprefix $(BUILD_DIR)/,$(notdir $(SOURCES_ASM:.s=.o)))
#@echo $(error ASM_OBJECTS=$(ASM_OBJECTS))
ELF_OBJECTS  += $(OBJECTS)


#@echo $(error ASM_OBJECTS=$(ASM_OBJECTS))
ELF_OBJECTS  += $(ASM_OBJECTS)
#@echo $(error ELF_OBJECTS=$(ELF_OBJECTS))
ifeq ($(GCC),Y)
    vpath %.S $(sort $(dir $(SOURCES_ASM)))
endif

ifeq ($(IAR),Y)
    vpath %.s $(sort $(dir $(SOURCES_ASM)))
endif

TOTAL_FILES := $(words $(OBJECTS))
$(info TOTAL_FILES:$(TOTAL_FILES) )

#@echo $(error CFLAGS=$(CFLAGS))
#@echo $(error COMPILE_GCC_OPT=$(COMPILE_GCC_OPT))
ifeq ($(IAR),Y)
$(BUILD_DIR)/%.o: %.s Makefile | $(BUILD_DIR) 
	@echo Compile Asm $@
	#@ $(CC) -c -MD $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	$(AS) -c  $(ASM_FLAGS)  $< -o $@
endif

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR) 
	$(eval CURRENT_CNT=$(shell echo $$(($(CURRENT_CNT)+1))))
	@echo Compiling $(CURRENT_CNT)/$(TOTAL_FILES) $@
	#@ $(CC) -c -MD $(CFLAGS) -Wa,-a,-ad,-alms=$(BUILD_DIR)/$(notdir $(<:.c=.lst)) $< -o $@
	$(CC) -c  $(CFLAGS)  $< -o $@

$(BUILD_DIR)/%.o: %.S Makefile | $(BUILD_DIR)
	$(AS) -c $(CFLAGS) $< -o $@



#@echo $(error MAIN_TARGET_FILE=$(MAIN_TARGET_FILE))
#@echo $(error LDFLAGS=$(LDFLAGS))
$(BUILD_DIR)/$(MAIN_TARGET_FILE): $(ELF_OBJECTS) Makefile $(BUILD_DIR)
	@echo GenerateMainArtifact $@
	$(LD) $(ELF_OBJECTS) $(LDFLAGS) -o $@
	$(SZ) $@

$(BUILD_DIR)/%.hex: $(BUILD_DIR)/$(MAIN_TARGET_FILE) | $(BUILD_DIR)
	@echo GenerateHex $@
	$(HEX) $< $@

#@echo $(error MAIN_TARGET_FILE=$(MAIN_TARGET_FILE))
$(BUILD_DIR)/%.bin: $(BUILD_DIR)/$(MAIN_TARGET_FILE)   $(BUILD_DIR)
	@echo GenerateBin $@
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

ifeq ($(SORT_CONFIG), Y)
    include $(WORKSPACE_LOC)/make_scripts/sort_config.mk
endif

ifeq ($(ARCHIVE_ARTIFACTS), Y)
    include $(WORKSPACE_LOC)/make_scripts/archive_artifacts.mk
endif

include $(WORKSPACE_LOC)/make_scripts/clang_format.mk
include $(WORKSPACE_LOC)/make_scripts/flash_target.mk

# dependencies
-include $(wildcard $(BUILD_DIR)/*.d)

# *** EOF ***