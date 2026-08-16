
$(info TOPO_SORT_MK_INC=$(TOPO_SORT_MK_INC))

ifneq ($(TOPO_SORT_MK_INC),Y)
    TOPO_SORT_MK_INC=Y

    TOPO_SORT_DIR = $(COMPUTING_DIR)/topo_sort
    #@echo $(error TOPO_SORT_DIR = $(TOPO_SORT_DIR))

    MCAL_OPT += -DHAS_TOPO_SORT
    MCAL_OPT += -DHAS_TOPO_SORT_PROC
    
    INCDIR += -I$(TOPO_SORT_DIR)

    SOURCES_C += $(TOPO_SORT_DIR)/topo_sort.c


    ifeq ($(DIAG),Y)
        ifeq ($(TOPO_SORT_DIAG),Y)
            MCAL_OPT += -DHAS_TOPO_SORT_DIAG
            SOURCES_C += $(TOPO_SORT_DIR)/topo_sort_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(TOPO_SORT_COMMANDS),Y)
            #@echo $(error TOPO_SORT_COMMANDS = $(TOPO_SORT_COMMANDS))
            MCAL_OPT += -DHAS_TOPO_SORT_COMMANDS
            SOURCES_C += $(TOPO_SORT_DIR)/topo_sort_commands.c
        endif
    endif
endif
