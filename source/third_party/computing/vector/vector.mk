$(info TP_COMPUTING_VECTOR_MK_INC=$(TP_COMPUTING_VECTOR_MK_INC))
ifneq ($(TP_COMPUTING_VECTOR_MK_INC),Y)
    TP_COMPUTING_VECTOR_MK_INC=Y
    $(info Add VECTOR)

    VECTOR_DIRECTORY = $(COMPUTING_DIRECTORY)/vector
    #@echo $(error VECTOR_DIRECTORY=$(VECTOR_DIRECTORY))

    INCDIR += -I$(VECTOR_DIRECTORY)
    
    OPT += -DHAS_VECTOR
    OPT += -DVECTOR_IN_USE
    VECTOR=Y

    ifeq ($(VECTOR_STATIC_SAMPLES),Y)
        OPT += -DVECTOR_IN_USE
    endif

    SOURCES_THIRD_PARTY_C += $(VECTOR_DIRECTORY)/vector.c

    ifeq ($(DIAG),Y)
        ifeq ($(VECTOR_DIAG),Y)
            #@echo $(error VECTOR_DIAG=$(VECTOR_DIAG))
            $(info Add VECTOR DIAG)
            OPT += -DVECTOR_DIAG_IN_USE
            SOURCES_THIRD_PARTY_C += $(VECTOR_DIRECTORY)/vector_diagnostic.c
        endif
    endif

    #@echo $(error VECTOR_DIRECTORY=$(VECTOR_DIRECTORY))

    ifeq ($(CLI),Y)
        ifeq ($(VECTOR_COMMANDS),Y)
            $(info Add VECTOR CLI)
            OPT += -DHAS_VECTOR_CLI
            OPT += -DVECTOR_CLI_IN_USE
            SOURCES_THIRD_PARTY_C += $(VECTOR_DIRECTORY)/vector_cli.c
        endif
    endif


    # Autoformat index
    SOURCES_EHAL_C+= $(VECTOR_DIRECTORY)/vector.c
    SOURCES_EHAL_C+= $(VECTOR_DIRECTORY)/vector_cli.c
    SOURCES_EHAL_C+= $(VECTOR_DIRECTORY)/vector_diagnostic.c

    SOURCES_EHAL_H += $(VECTOR_DIRECTORY)/vector.h
    SOURCES_EHAL_H += $(VECTOR_DIRECTORY)/vector_diagnostic.h
    SOURCES_EHAL_H += $(VECTOR_DIRECTORY)/vector_cli.h

    # code style check index
    #https://habr.com/ru/articles/843746/

    SOURCES_CODE_STYLE_C += $(VECTOR_DIRECTORY)/vector.c
    SOURCES_CODE_STYLE_H += $(VECTOR_DIRECTORY)/vector.h

    SOURCES_CODE_STYLE_H += $(VECTOR_DIRECTORY)/vector_constants.h
    SOURCES_CODE_STYLE_H += $(VECTOR_DIRECTORY)/vector_type.h
    SOURCES_CODE_STYLE_H += $(VECTOR_DIRECTORY)/vector_dependencies.h
    
    
endif
