ifneq ($(PROTOCOLS_PRECONFIG_MK),Y)
    PROTOCOLS_PRECONFIG_MK=Y

    PROTOCOLS_DIR = $(CONNECTIVITY_DIR)/protocols
    #PROTOCOL=Y
    #PROTOCOLS=Y

    include $(PROTOCOLS_DIR)/protocol/protocol_preconfig.mk

    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        include $(PROTOCOLS_DIR)/cli_drv/cli_preconfig.mk
    endif

    ifeq ($(CSV),Y)
        #@echo $(error CSV=$(CSV))
        include $(PROTOCOLS_DIR)/csv/csv_preconfig.mk
    endif

    ifeq ($(DECAWAVE),Y)
        include $(PROTOCOLS_DIR)/decawave/decawave_preconfig.mk
    endif

    ifeq ($(DS_TWR),Y)
        include $(PROTOCOLS_DIR)/ds_twr/ds_twr_preconfig.mk
    endif

    ifeq ($(NMEA),Y)
        include $(PROTOCOLS_DIR)/nmea/nmea_preconfig.mk
    endif 

    ifeq ($(ISO_TP),Y)
        include $(PROTOCOLS_DIR)/iso_tp/iso_tp_preconfig.mk
    endif

    ifeq ($(RDS),Y)
        include $(PROTOCOLS_DIR)/rds_protocol/rds_protocol_preconfig.mk
    endif

    ifeq ($(RTCM3),Y)
        include $(PROTOCOLS_DIR)/rtcm3_protocol/rtcm3_protocol_preconfig.mk
    endif

    ifeq ($(TBFP),Y)
        include $(PROTOCOLS_DIR)/tbfp_protocol/tbfp_protocol_preconfig.mk
    endif

    ifeq ($(UBX),Y)
        include $(PROTOCOLS_DIR)/ubx_protocol/ubx_protocol_preconfig.mk
    endif

    ifeq ($(UDS),Y)
        include $(PROTOCOLS_DIR)/uds/uds_preconfig.mk
    endif
endif