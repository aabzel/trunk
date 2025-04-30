ifneq ($(SPI_NRF_PRECONFIG_MK_INC),Y)
    SPI_NRF_PRECONFIG_MK_INC=Y


    SPI_NRF_DIR = $(MCAL_NRF5340_DIR)/spi
    #@echo $(error SPI_NRF_DIR=$(SPI_NRF_DIR))

    GPIO=Y
    SPI=Y
    TIME=Y

endif