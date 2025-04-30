$(info VERIFY_MK_INC=$(VERIFY_MK_INC) )
ifneq ($(VERIFY_MK_INC),Y)
    VERIFY_MK_INC=Y

    ifeq ($(GENERIC),Y)
        ifeq ($(BOOTLOADER),Y)
               $(error Impossible config )
        endif
    endif

    $(info Veryfi build configuretion)
    ifeq ($(GENERIC),Y)
        ifeq ($(MICROCONTROLLER),Y)
        
            ifeq ($(CLI),Y)
                ifneq ($(CONNECTIVITY_COMMANDS),Y)
                    $(error Add CONNECTIVITY_COMMANDS )
                endif
                ifneq ($(STORAGE_COMMANDS),Y)
                    $(error Add STORAGE_COMMANDS )
                endif
            endif
            
            ifneq ($(SUPER_CYCLE),Y)
                $(error Add SUPER_CYCLE)
            endif

            ifneq ($(STORAGE),Y)
                $(error Add STORAGE)
            endif

        endif
    endif
endif
