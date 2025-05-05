ifneq ($(GRAPHVIZ_TO_TSORT_MK_INC),Y)
    GRAPHVIZ_TO_TSORT_MK_INC=Y

    GRAPHVIZ_TO_TSORT_DIR = $(APPLICATIONS_DIR)/graphviz_to_tsort
    #@ echo $(error GRAPHVIZ_TO_TSORT_DIR = $(GRAPHVIZ_TO_TSORT_DIR))
    #@ echo $(error CFLAGS = $(CFLAGS)) 
    OPT += -DHAS_GRAPHVIZ_TO_TSORT

    INCDIR += -I$(GRAPHVIZ_TO_TSORT_DIR)

    SOURCES_C += $(GRAPHVIZ_TO_TSORT_DIR)/graphviz_to_tsort.c
    SOURCES_C += $(GRAPHVIZ_TO_TSORT_DIR)/graphviz_to_tsort_config.c

    ifeq ($(DIAG),Y)
        SOURCES_C += $(GRAPHVIZ_TO_TSORT_DIR)/graphviz_to_tsort_diag.c
    endif

    ifeq ($(CLI),Y)
        ifeq ($(GRAPHVIZ_TO_TSORT_COMMANDS),Y)
            OPT += -DHAS_GRAPHVIZ_TO_TSORT_COMMANDS
            SOURCES_C += $(GRAPHVIZ_TO_TSORT_DIR)/graphviz_to_tsort_commands.c
        endif
    endif
endif


