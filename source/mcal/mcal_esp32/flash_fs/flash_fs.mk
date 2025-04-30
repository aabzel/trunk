
mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
$(info Build  $(mkfile_path) )

FLASH_FS_DIR = $(PROJECT_ROOT)bsp_esp32/flash_fs
#@ echo $(error FLASH_FS_DIR = $(FLASH_FS_DIR))
#@ echo $(error CFLAGS = $(CFLAGS)) 

INCDIR += -I$(FLASH_FS_DIR)
