ifneq ($(CRC_MK_INC),Y)
    CRC_MK_INC=Y

    CRC_DIR = $(COMPUTING_DIR)/crc
    # $(error CRC_DIR=$(CRC_DIR))
    INCDIR  += -I$(CRC_DIR)
    MCAL_OPT += -DHAS_CRC
    # $(error CRC=$(CRC))

    ifeq ($(CRC_DIAG),Y)
        MCAL_OPT += -DHAS_CRC_DIAG
        SOURCES_C += $(CRC_DIR)/crc_diag.c
    endif

    ifeq ($(CRC8_AUTOSAR),Y)
        MCAL_OPT += -DHAS_CRC8
        MCAL_OPT += -DHAS_CRC8_AUTOSAR
        SOURCES_C += $(CRC_DIR)/crc8_autosar.c
    endif

    ifeq ($(CRC8),Y)
        MCAL_OPT += -DHAS_CRC8
        SOURCES_C += $(CRC_DIR)/crc8_sae_j1850.c
        #SOURCES_C += $(CRC_DIR)/crc8_autosar.c
    endif

    ifeq ($(CRC16),Y)
        MCAL_OPT += -DHAS_CRC16
        SOURCES_C += $(CRC_DIR)/crc16_ccitt.c
        SOURCES_C += $(CRC_DIR)/crc16_ibm.c
    endif

    ifeq ($(CRC24),Y)
        MCAL_OPT += -DHAS_CRC24
        SOURCES_C += $(CRC_DIR)/crc24_q.c
    endif

    ifeq ($(CRC32),Y)
        # $(error CRC32=$(CRC32))
        MCAL_OPT += -DHAS_CRC32
        SOURCES_C += $(CRC_DIR)/crc32.c
    endif

endif

