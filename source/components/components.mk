ifneq ($(COMPONENTS_MK_INC),Y)
    COMPONENTS_MK_INC=Y

    OPT += -DHAS_COMPONENTS
    COMPONENTS_DIR = $(WORKSPACE_LOC)/components
    #@echo $(error COMPONENTS_DIR= $(COMPONENTS_DIR))

    INCDIR += -I$(COMPONENTS_DIR)

    ifeq ($(AUDIO),Y)
        #@echo $(error AUDIO=$(AUDIO))
        include $(COMPONENTS_DIR)/audio/audio.mk
    endif

    ifeq ($(BOARD_INFO),Y)
        #@echo $(error BOARD_INFO=$(BOARD_INFO))
        include $(COMPONENTS_DIR)/board_info/board_info.mk
    endif

    ifeq ($(DOT),Y)
        include $(COMPONENTS_DIR)/dot/dot.mk
    endif

    ifeq ($(SOFTWARE_TIMER),Y)
        include $(COMPONENTS_DIR)/software_timer/software_timer.mk
    endif

endif