
ifneq ($(CONTROL_MBR_MK_INC),Y)
    CONTROL_MBR_MK_INC=Y
    #@echo $(error MBR=$(MBR))
    MBR_DIR = $(CONTROL_DIR)/mbr
    INCDIR += -I$(MBR_DIR)

    MCAL_OPT += -DHAS_MBR
    MCAL_OPT += -DHAS_MBR_PROC
    MCAL_OPT += -DHAS_MBR_INIT
    #MCAL_OPT += -Os
    #PACK_PROGRAM=Y

    # nosys.specs just defines that system calls should be 
    # implemented as stubs that return errors when called (-lnosys). 
    # The choice of libc in this case depends on whether nano should be used. 
    # With %G the libgcc spec-string is processed, which defines the 
    # parameters passed to the linker.

    ifeq ($(GCC), Y)
        LDFLAGS += -specs=nosys.specs
        #LIBS += -lnosys
    endif

    SOURCES_C += $(MBR_DIR)/mbr_drv.c
endif