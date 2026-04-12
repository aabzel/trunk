$(info CORE_GENERAL_MK_INC=$(CORE_GENERAL_MK_INC) )

ifneq ($(CORE_GENERAL_MK_INC),Y)
    CORE_GENERAL_MK_INC=Y

    CORE_DIR = $(WORKSPACE_LOC)/core
    # $(error CORE_DIR=$(CORE_DIR))
    INCDIR += -I$(CORE_DIR)

    MCAL_OPT += -DHAS_CORE

    SOURCES_C += $(CORE_DIR)/core_driver.c
    SOURCES_CONFIGURATION_C += $(CORE_DIR)/core_config.c

    ifeq ($(RV32IMC),Y)   
        # $(error RV32IMC=$(RV32IMC))
        include $(CORE_DIR)/rv32imc/rv32imc.mk
    endif

    ifeq ($(CORTEX_M0),Y)   
        # $(error CORTEX_M0=$(CORTEX_M0))
        include $(CORE_DIR)/cortex_m0/cortex_m0.mk
    endif

    ifeq ($(CORTEX_M3),Y)   
        # $(error CORTEX_M3=$(CORTEX_M3))
        include $(CORE_DIR)/cortex_m3/cortex_m3.mk
    endif

    ifeq ($(CORTEX_M4),Y)   
        # $(error CORTEX_M4=$(CORTEX_M4))
        include $(CORE_DIR)/cortex_m4/cortex_m4.mk
    endif

    ifeq ($(CORTEX_M7),Y)   
        # $(error CORTEX_M7=$(CORTEX_M7))
        include $(CORE_DIR)/cortex_m7/cortex_m7.mk
    endif

    ifeq ($(CORTEX_M33),Y)   
        # $(error CORTEX_M33=$(CORTEX_M33))
        include $(CORE_DIR)/cortex_m33/cortex_m33.mk
    endif

    ifeq ($(CORE_EXT),Y)
        # $(error CORE_EXT=$(CORE_EXT))
        MCAL_OPT += -DHAS_CORE_EXT
    endif

    #---------------------------
    
    ifeq ($(MPU),Y)
        # $(error MPU=$(MPU))
        include $(CORE_DIR)/mpu/cortex_mpu.mk
    endif

    ifeq ($(NVIC),Y)
        # $(error NVIC=$(NVIC))
        include $(CORE_DIR)/nvic/nvic.mk
    endif

    ifeq ($(SYSTICK),Y)
        #$(error SYSTICK=$(SYSTICK))
        include $(CORE_DIR)/systick/systick.mk
    endif
    
    ifeq ($(DWT),Y)
        # $(error DWT=$(DWT))
        include $(CORE_DIR)/dwt/dwt.mk
    endif
    #---------------------------------

    ifeq ($(CORE_STACK_MONITOR),Y)
        RATIONAL_NUM_DIAG=Y
        MCAL_OPT += -DHAS_CORE_STACK_MONITOR_PROC
    endif
    
    ifeq ($(CORE_DIAG),Y)
        MCAL_OPT += -DHAS_CORE_DIAG
        SOURCES_C += $(CORE_DIR)/core_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CORE_COMMANDS),Y)
            #$(error CORE_COMMANDS=$(CORE_COMMANDS))
            MCAL_OPT += -DHAS_CORE_COMMANDS
            SOURCES_C += $(CORE_DIR)/core_commands.c
        endif
    endif
endif