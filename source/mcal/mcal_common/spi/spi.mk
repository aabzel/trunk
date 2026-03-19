$(info SPI_COMMON_MCAL_MK_INC=$(SPI_COMMON_MCAL_MK_INC) )

ifneq ($(SPI_COMMON_MCAL_MK_INC),Y)
    SPI_COMMON_MCAL_MK_INC=Y

    SPI_COMMON_MCAL_DIR = $(MCAL_COMMON_DIR)/spi
    #  $(error SPI_COMMON_MCAL_DIR=$(SPI_COMMON_MCAL_DIR))

    INCDIR += -I$(SPI_COMMON_MCAL_DIR)
    MCAL_OPT += -DHAS_SPI

    SOURCES_C += $(SPI_COMMON_MCAL_DIR)/spi_general.c
    ifeq ($(SPI_PROC),Y)
        MCAL_OPT += -DHAS_SPI_PROC
    endif

    ifeq ($(SPI_INTERRUPT),Y)
        # $(error SPI_COMMON_MCAL_DIR=$(SPI_COMMON_MCAL_DIR))
        MCAL_OPT += -DHAS_SPI_INTERRUPT
        SOURCES_C += $(SPI_COMMON_MCAL_DIR)/spi_isr.c
    endif


    ifeq ($(DIAG),Y)
        ifeq ($(SPI_DIAG),Y)
            MCAL_OPT += -DHAS_SPI_DIAG
            SOURCES_C += $(SPI_COMMON_MCAL_DIR)/spi_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SPI_COMMANDS),Y)
            MCAL_OPT += -DHAS_SPI_COMMANDS
            SOURCES_C += $(SPI_COMMON_MCAL_DIR)/spi_commands.c
        endif
    endif    
endif