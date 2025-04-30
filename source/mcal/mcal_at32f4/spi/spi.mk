$(info SPI_CUSTOM_MK_INC=$(SPI_CUSTOM_MK_INC) )

ifneq ($(SPI_CUSTOM_MK_INC),Y)
    SPI_CUSTOM_MK_INC=Y


    SPI_CUSTOM_DIR = $(MCAL_AT32F4_DIR)/spi
    #@echo $(error SPI_CUSTOM_DIR=$(SPI_CUSTOM_DIR))

    INCDIR += -I$(SPI_CUSTOM_DIR)

    SOURCES_C += $(SPI_CUSTOM_DIR)/spi_mcal.c
    OPT += -DHAS_SPI

    ifeq ($(SPI_ISR),Y)
        $(info + SPI ISR )
        OPT += -DHAS_SPI_ISR
        SOURCES_C += $(SPI_CUSTOM_DIR)/spi_custom_isr.c
    endif


    ifeq ($(SPI1),Y)
        OPT += -DHAS_SPI1
    endif

    ifeq ($(SPI2),Y)
        OPT += -DHAS_SPI2
    endif

    ifeq ($(SPI3),Y)
        OPT += -DHAS_SPI3
    endif

    ifeq ($(SPI4),Y)
        OPT += -DHAS_SPI4
    endif

    ifeq ($(SPI5),Y)
        OPT += -DHAS_SPI5
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SPI_DIAG),Y)
            OPT += -DHAS_SPI_DIAG
            SOURCES_C += $(SPI_CUSTOM_DIR)/spi_custom_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SPI_COMMANDS),Y)
            OPT += -DHAS_SPI_COMMANDS
            SOURCES_C += $(SPI_CUSTOM_DIR)/spi_custom_commands.c
        endif
    endif
endif