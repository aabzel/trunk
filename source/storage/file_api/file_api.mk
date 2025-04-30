

FILE_API_DIR = $(STORAGE_DIR)/file_api
#@echo $(error FILE_DIR=$(FILE_DIR))
#@echo $(error CFLAGS= $(CFLAGS))

INCDIR += -I$(FILE_API_DIR)
OPT += -DHAS_FILE_API

SOURCES_C += $(FILE_API_DIR)/file_api.c
SOURCES_C += $(FILE_API_DIR)/file_api_diag.c
SOURCES_C += $(FILE_API_DIR)/file_api_commands.c

