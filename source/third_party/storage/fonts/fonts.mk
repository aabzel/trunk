ifneq ($(TP_FONTS_MK_INC),Y)
    TP_FONTS_MK_INC=Y

    TP_FONTS_DIR += $(THIRD_PARTY_STORAGE_DIR)/fonts
    # $(error TP_FONTS_DIR= $(TP_FONTS_DIR))
    INCDIR += -I$(TP_FONTS_DIR)

    MCAL_OPT += -DHAS_FONTS_ENGLISH
    SOURCES_THIRD_PARTY_C += $(TP_FONTS_DIR)/fonts_english.c
    SOURCES_THIRD_PARTY_C += $(TP_FONTS_DIR)/fonts_russian.c
endif