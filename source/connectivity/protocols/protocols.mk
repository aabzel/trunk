ifneq ($(PROTOCOLS_MK),Y)
    PROTOCOLS_MK=Y

    PROTOCOLS_DIR = $(CONNECTIVITY_DIR)/protocols
    #@echo $(error PROTOCOLS_DIR=$(PROTOCOLS_DIR))
    #@echo $(error CFLAGS= $(CFLAGS))
    OPT += -DHAS_PROTOCOLS
    OPT += -DHAS_PROTOCOLS_COMMANDS

    INCDIR += -I$(PROTOCOLS_DIR)

    ifeq ($(BASE16),Y)
        include $(PROTOCOLS_DIR)/base16/base16.mk
    endif

    ifeq ($(BASE64),Y)
        include $(PROTOCOLS_DIR)/base64/base64.mk
    endif

    ifeq ($(PROTOCOLS),Y)
        include $(PROTOCOLS_DIR)/protocol/protocol.mk
    endif
   
    ifeq ($(CLI),Y)
        #@echo $(error CLI=$(CLI))
        include $(PROTOCOLS_DIR)/cli_drv/cli_drv.mk
    endif

    ifeq ($(CSV),Y)
        #@echo $(error CSV=$(CSV))
        include $(PROTOCOLS_DIR)/csv/csv.mk
    endif

    ifeq ($(DECAWAVE),Y)
        #@echo $(error DECAWAVE=$(DECAWAVE))
        include $(PROTOCOLS_DIR)/decawave/decawave.mk
    endif

    ifeq ($(DECAWAVE_NATIVE),Y)
        #@echo $(error DECAWAVE_NATIVE=$(DECAWAVE_NATIVE))
        include $(PROTOCOLS_DIR)/decawave_native/decawave_native.mk
    endif

    ifeq ($(DS_TWR),Y)
        include $(PROTOCOLS_DIR)/ds_twr/ds_twr.mk
    endif

    ifeq ($(ISO_TP),Y)
        include $(PROTOCOLS_DIR)/iso_tp/iso_tp.mk
    endif

    ifeq ($(NMEA),Y)
        #@echo $(error NMEA=$(NMEA))
        include $(PROTOCOLS_DIR)/nmea/nmea.mk
    endif

    ifeq ($(RDS),Y)
        include $(PROTOCOLS_DIR)/rds_protocol/rds_protocol.mk
    endif

    ifeq ($(STACK_FRAME),Y)
        include $(PROTOCOLS_DIR)/stack_frame/stack_frame.mk
    endif

    ifeq ($(RTCM3),Y)
        include $(PROTOCOLS_DIR)/rtcm3_protocol/rtcm3_protocol.mk
    endif

    ifeq ($(STRING_READER),Y)
        include $(PROTOCOLS_DIR)/string_reader/string_reader.mk
    endif

    ifeq ($(TBFP),Y)
        include $(PROTOCOLS_DIR)/tbfp_protocol/tbfp_protocol.mk
    endif

    ifeq ($(UBX),Y)
        include $(PROTOCOLS_DIR)/ubx_protocol/ubx_protocol.mk
    endif

    ifeq ($(UDS),Y)
        include $(PROTOCOLS_DIR)/uds/uds.mk
    endif

endif