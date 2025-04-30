$(info CORE_GENERAL_MK_INC=$(CORE_GENERAL_MK_INC) )

ifneq ($(CORE_GENERAL_MK_INC),Y)
    CORE_GENERAL_MK_INC=Y

    CORE_DIR = $(WORKSPACE_LOC)/core
    # $(error CORE_DIR=$(CORE_DIR))
    INCDIR += -I$(CORE_DIR)

    OPT += -DHAS_CORE

    SOURCES_C += $(CORE_DIR)/core_driver.c

    ifeq ($(RV32IMC),Y)   
        # $(error RV32IMC=$(RV32IMC))
        include $(CORE_DIR)/rv32imc/rv32imc.mk
    endif

    ifeq ($(CORTEX_M0),Y)   
        #@echo $(error CORTEX_M0=$(CORTEX_M0))
        include $(CORE_DIR)/cortex_m0/cortex_m0.mk
    endif

    ifeq ($(CORTEX_M3),Y)   
        #@echo $(error CORTEX_M3=$(CORTEX_M3))
        include $(CORE_DIR)/cortex_m3/cortex_m3.mk
    endif

    ifeq ($(CORTEX_M4),Y)   
        #@echo $(error CORTEX_M4=$(CORTEX_M4))
        include $(CORE_DIR)/cortex_m4/cortex_m4.mk
    endif

    ifeq ($(CORTEX_M7),Y)   
        #@echo $(error CORTEX_M7=$(CORTEX_M7))
        include $(CORE_DIR)/cortex_m7/cortex_m7.mk
    endif

    ifeq ($(CORTEX_M33),Y)   
        #@echo $(error CORTEX_M33=$(CORTEX_M33))
        include $(CORE_DIR)/cortex_m33/cortex_m33.mk
    endif

    ifeq ($(CORE_EXT),Y)
        #@echo $(error CORE_EXT=$(CORE_EXT))
        OPT += -DHAS_CORE_EXT
    endif

    ifeq ($(CLI),Y)
        ifeq ($(CORE_COMMANDS),Y)
            #@echo $(error CORE_COMMANDS=$(CORE_COMMANDS))
            OPT += -DHAS_CORE_COMMANDS
            SOURCES_C += $(CORE_DIR)/core_commands.c
        endif
    endif
endif