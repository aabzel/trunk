ifneq ($(SPI_NRF_MK_INC),Y)
    SPI_NRF_MK_INC=Y

    mkfile_path := $(abspath $(lastword $(MAKEFILE_LIST)))
    $(info Build  $(mkfile_path) )

    SPI_NRF_DIR = $(MCAL_NRF5340_DIR)/spi
    #@echo $(error SPI_NRF_DIR=$(SPI_NRF_DIR))

    INCDIR += -I$(SPI_NRF_DIR)
    OPT += -DHAS_SPI

    SOURCES_C += $(SPI_NRF_DIR)/spi_drv.c

    ifeq ($(SPI_ISR),Y)
        SOURCES_C += $(SPI_NRF_DIR)/spi_isr.c
        OPT += -DHAS_SPI_ISR
    endif

    ifeq ($(SPI0),Y)
        OPT += -DHAS_SPI0
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

    ifeq ($(CORE_NET),Y)
        ifeq ($(SPI1),Y)
            @echo $(error Unreal SPI)
        endif
        ifeq ($(SPI2),Y)
            @echo $(error Unreal SPI)
        endif
        ifeq ($(SPI3),Y)
            @echo $(error Unreal SPI)
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(SPI_DIAG),Y)
            $(info SPI nrf diag)
            OPT += -DHAS_SPI_DIAG
            SOURCES_C += $(SPI_NRF_DIR)/spi_nrf_diag.c
        endif
    endif

    ifeq ($(CLI),Y)
        ifeq ($(SPI_COMMANDS),Y)
            OPT += -DHAS_SPI_COMMANDS
            $(info SPI nrf commands)
            SOURCES_C += $(SPI_NRF_DIR)/spi_nrf_commands.c
        endif
    endif
endif