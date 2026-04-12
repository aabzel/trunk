ifneq ($(TP_MISCELLANEOUS_MK_INC),Y)
    TP_MISCELLANEOUS_MK_INC=Y

    TP_MISCELLANEOUS_DIR = $(THIRD_PARTY_DIR)/miscellaneous
    # $(error TP_MISCELLANEOUS_DIR= $(TP_MISCELLANEOUS_DIR))

    INCDIR += -I$(TP_MISCELLANEOUS_DIR)
    MCAL_OPT += -DHAS_MISCELLANEOUS
    MCAL_OPT += -DMISCELLANEOUS_IN_USE

    ifeq ($(EHAL_FLOAT),Y)
        # $(error FLOAT=$(FLOAT))
        MCAL_OPT += -DHAS_MISCELLANEOUS_FLOAT
        MCAL_OPT += -DFLOAT_IN_USE
        SOURCES_THIRD_PARTY_C+= $(TP_MISCELLANEOUS_DIR)/miscellaneous_float.c
        SOURCES_EHAL_H += $(TP_MISCELLANEOUS_DIR)/miscellaneous_float.h
        SOURCES_CODE_STYLE_C += $(TP_MISCELLANEOUS_DIR)/miscellaneous_float.c
        SOURCES_EHAL_C+= $(TP_MISCELLANEOUS_DIR)/miscellaneous_float.c
        SOURCES_CODE_STYLE_H += $(TP_MISCELLANEOUS_DIR)/miscellaneous_float.h
    endif

    ifeq ($(UTIL),Y)
        #$(error UTIL=$(UTIL))
        include $(TP_MISCELLANEOUS_DIR)/util/util.mk
    endif

    ifeq ($(EHAL),Y)
        SOURCES_THIRD_PARTY_C+= $(TP_MISCELLANEOUS_DIR)/miscellaneous_ehal.c
    endif
    
    
    # code style check index
    # https://habr.com/ru/articles/843746/
endif
