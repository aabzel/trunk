ifneq ($(CRC_MK_INC),Y)
    CRC_MK_INC=Y

    CRC_DIR = $(COMPUTING_DIR)/crc
    #@echo $(error CRC_DIR=$(CRC_DIR))
    INCDIR  += -I$(CRC_DIR)
    OPT += -DHAS_CRC
    #@echo $(error CRC=$(CRC))

    ifeq ($(CRC_DIAG),Y)
        OPT += -DHAS_CRC_DIAG
        SOURCES_C += $(CRC_DIR)/crc_diag.c
    endif

    ifeq ($(CRC8_AUTOSAR),Y)
        OPT += -DHAS_CRC8
        OPT += -DHAS_CRC8_AUTOSAR
        SOURCES_C += $(CRC_DIR)/crc8_autosar.c
    endif

    ifeq ($(CRC8),Y)
        OPT += -DHAS_CRC8
        SOURCES_C += $(CRC_DIR)/crc8_sae_j1850.c
        #SOURCES_C += $(CRC_DIR)/crc8_autosar.c
    endif

    ifeq ($(CRC16),Y)
        OPT += -DHAS_CRC16
        SOURCES_C += $(CRC_DIR)/crc16_ccitt.c
    endif

    ifeq ($(CRC24),Y)
        OPT += -DHAS_CRC24
        SOURCES_C += $(CRC_DIR)/crc24_q.c
    endif

    ifeq ($(CRC32),Y)
        #@echo $(error CRC32=$(CRC32))
        OPT += -DHAS_CRC32
        SOURCES_C += $(CRC_DIR)/crc32.c
    endif

endif

