
ifneq ($(ZEPHYR_NVS_MK),Y)
    ZEPHYR_NVS_MK=Y

    ZEPHYR_NVS_DIR = $(BSP_NRF5340_DIR)/nvs
    #@echo $(error ZEPHYR_NVS_DIR=$(ZEPHYR_NVS_DIR))
    
    INCDIR += -I$(ZEPHYR_NVS_DIR)
    OPT += -DHAS_ZEPHYR_NVS
    OPT += -DHAS_NVS

    SOURCES_C += $(ZEPHYR_NVS_DIR)/nvs_drv.c

    ifeq ($(NVS_DIAG),Y)
        #@echo $(error NVS_DIAG=$(NVS_DIAG))
        OPT += -DHAS_NVS_DIAG
        SOURCES_C += $(ZEPHYR_NVS_DIR)/nvs_custom_diag.c
    endif

    ifeq ($(NVS_WRITE),Y)
        #@echo $(error NVS_WRITE=$(NVS_WRITE))
        OPT += -DHAS_NVS_WRITE
    endif

    ifeq ($(CLI),Y)
        ifeq ($(ZEPHYR_NVS_COMMANDS),Y)
            SOURCES_C += $(ZEPHYR_NVS_DIR)/nvs_custom_commands.c
        endif
    endif
endif
