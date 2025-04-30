PROJECT_PATH:=$(dir $(realpath $(lastword $(MAKEFILE_LIST))))

PROJECT_PATH:=$(subst /cygdrive/c/,C:/,$(PROJECT_PATH))

#$(error PROJECT_PATH=$(PROJECT_PATH))
DOCUMENTATION_DIR:=$(PROJECT_PATH)../../../docs

DOCUMENTATION_DIR:=$(subst /cygdrive/c/,C:/,$(DOCUMENTATION_DIR))

DOCUMENTATION_DIR:= $(realpath $(DOCUMENTATION_DIR))
DOCUMENTATION_DIR := $(subst /cygdrive/c/,C:/, $(DOCUMENTATION_DIR))

#@echo $(error DOCUMENTATION_DIR=$(DOCUMENTATION_DIR))
#@echo $(error PROJECT_PATH=$(PROJECT_PATH))

PROJECT_PATH := $(shell readlink -f $(PROJECT_PATH))
#@echo $(error PROJECT_PATH=$(PROJECT_PATH))
DOCUMENTATION_DIR := $(shell readlink -f $(DOCUMENTATION_DIR))
#@echo $(error DOCUMENTATION_DIR=$(DOCUMENTATION_DIR))
INCLUDE_PATHS += -I$(PROJECT_PATH)


#@echo $(error OPT=$(OPT))

#@echo $(error SOURCES_C=$(SOURCES_C))
include $(PROJECT_PATH)/config.mk


include $(DOCUMENTATION_DIR)/docs.mk
include $(DOCUMENTATION_DIR)/make_scripts/typeset_book.mk
 