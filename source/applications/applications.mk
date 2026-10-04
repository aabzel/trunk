$(info APPS_MK_INC=$(APPS_MK_INC))

ifneq ($(APPS_MK_INC),Y)
    APPS_MK_INC=Y

    APPLICATIONS_DIR = $(WORKSPACE_LOC)/applications
    $(info APPLICATIONS_DIR=$(APPLICATIONS_DIR))

    # $(error APPLICATIONS_DIR=$(APPLICATIONS_DIR))
    APPLICATIONS=Y
    MCAL_OPT += -DHAS_APP
    MCAL_OPT += -DHAS_APPLICATIONS
    MCAL_OPT += -DHAS_APPLICATION

    INCDIR += -I$(APPLICATIONS_DIR)

    ifeq ($(AKIP1160),Y)
        # $(error AKIP1160=$(AKIP1160))
        include $(APPLICATIONS_DIR)/akip1160/akip1160.mk
    endif

    ifeq ($(FW_LOADER),Y)
        include $(APPLICATIONS_DIR)/fw_loader/fw_loader.mk
    endif

    ifeq ($(ENCODER_LAMP),Y)
        # $(error ENCODER_LAMP=$(ENCODER_LAMP))
        include $(APPLICATIONS_DIR)/encoder_lamp/encoder_lamp.mk
    endif

    ifeq ($(CAN_TX_PLANNER),Y)
        # $(error CAN_TX_PLANNER=$(CAN_TX_PLANNER))
        include $(APPLICATIONS_DIR)/can_tx_planner/can_tx_planner.mk
    endif

    ifeq ($(CAN_RX_HIST),Y)
        # $(error CAN_RX_HIST=$(CAN_RX_HIST))
        include $(APPLICATIONS_DIR)/can_rx_hist/can_rx_hist.mk
    endif

    ifeq ($(CAN_DIFF),Y)
        # $(error CAN_DIFF=$(CAN_DIFF))
        include $(APPLICATIONS_DIR)/can_diff/can_diff.mk
    endif

    ifeq ($(IR_FM_RADIO),Y)
        include $(APPLICATIONS_DIR)/ir_fm_radio/ir_fm_radio.mk
    endif
    
    
    ifeq ($(AUTO_VERSION),Y)
        include $(APPLICATIONS_DIR)/auto_version/auto_version.mk
    endif

    ifeq ($(AUTO_VOLUME),Y)
        include $(APPLICATIONS_DIR)/auto_volume/auto_volume.mk
    endif

    ifeq ($(AUTO_BRIGHTNESS),Y)
        include $(APPLICATIONS_DIR)/auto_brightness/auto_brightness.mk
    endif

    ifeq ($(LASER_SIGHT),Y)
        include $(APPLICATIONS_DIR)/laser_sight/laser_sight.mk
    endif

    ifeq ($(CAN_CAT),Y)
        include $(APPLICATIONS_DIR)/can_cat/can_cat.mk
    endif

    ifeq ($(C_GENERATOR),Y)
        include $(APPLICATIONS_DIR)/c_generator/c_generator.mk
    endif

    ifeq ($(GARLAND),Y)
        include $(APPLICATIONS_DIR)/garland/garland.mk
    endif

    ifeq ($(DEMAGNETIZER),Y)
        include $(APPLICATIONS_DIR)/demagnetizer/demagnetizer.mk
    endif

    ifeq ($(END_OF_BLOCK),Y)
        include $(APPLICATIONS_DIR)/end_of_block/end_of_block.mk
    endif

    ifeq ($(APP_PCAN_PRO_X),Y)
        include $(APPLICATIONS_DIR)/pcan_pro_x/pcan_pro_x.mk
    endif

    ifeq ($(SED),Y)
        include $(APPLICATIONS_DIR)/sed/sed.mk
    endif

    ifeq ($(SONAR),Y)
        include $(APPLICATIONS_DIR)/sonar/sonar.mk
    endif

    ifeq ($(CODE_STYLE_CHECKER),Y)
        include $(APPLICATIONS_DIR)/code_style_checker/code_style_checker.mk
    endif

    ifeq ($(DASHBOARD),Y)
        include $(APPLICATIONS_DIR)/dashboard/dashboard.mk
    endif

    ifeq ($(GRAPHVIZ_TO_TSORT),Y)
        include $(APPLICATIONS_DIR)/graphviz_to_tsort/graphviz_to_tsort.mk
    endif

    ifeq ($(GEARBOX),Y)
        include $(APPLICATIONS_DIR)/gearbox/gearbox.mk
    endif

    ifeq ($(RC_CAR),Y)
        # $(error RC_CAR=$(RC_CAR))
        include $(APPLICATIONS_DIR)/rc_car/rc_car.mk
    endif

    ifeq ($(BPSK_DECODER),Y)
        include $(APPLICATIONS_DIR)/bpsk_decoder/bpsk_decoder.mk
    endif
    
    ifeq ($(SOUND_LOCALIZATION),Y)
        include $(APPLICATIONS_DIR)/sound_localization/sound_localization.mk
    endif

    ifeq ($(KEYLOG),Y)
        include $(APPLICATIONS_DIR)/keylog/keylog.mk
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        include $(APPLICATIONS_DIR)/light_navigator/light_navigator.mk
    endif

    ifeq ($(BICYCLE_HEADLAMP),Y)
        # $(error BICYCLE_HEADLAMP=$(BICYCLE_HEADLAMP))
        include $(APPLICATIONS_DIR)/bicycle_headlamp/bicycle_headlamp.mk
    endif

    ifeq ($(PASTILDA),Y)
        # $(error PASTILDA=$(PASTILDA))
        include $(APPLICATIONS_DIR)/pastilda/pastilda.mk
    endif

    ifeq ($(PWM_PHASE_DEMO),Y)
        include $(APPLICATIONS_DIR)/pwm_phase_demo/pwm_phase_demo.mk
    endif

    ifeq ($(GNSS_PROVE),Y)
        include $(APPLICATIONS_DIR)/gnss_prove/gnss_prove.mk
    endif

    ifeq ($(WAV_PLAYER),Y)
        include $(APPLICATIONS_DIR)/wav_player/wav_player.mk
    endif

    ifeq ($(LOOPBACK_AUDIO),Y)
        include $(APPLICATIONS_DIR)/loopback_audio/loopback_audio.mk
    endif

    ifeq ($(I2S_ECHO),Y)
        include $(APPLICATIONS_DIR)/i2s_echo/i2s_echo.mk
    endif

    ifeq ($(REC_PLAY),Y)
        include $(APPLICATIONS_DIR)/rec_play/rec_play.mk
    endif

    ifeq ($(SMOOTH_LAMP),Y)
        include $(APPLICATIONS_DIR)/smooth_lamp/smooth_lamp.mk
    endif

    ifeq ($(PROBING_PULSE),Y)
        include $(APPLICATIONS_DIR)/probing_pulse/probing_pulse.mk
    endif

    ifeq ($(SOUND_RECORDER),Y)
        include $(APPLICATIONS_DIR)/sound_recorder/sound_recorder.mk
    endif

    ifeq ($(TICKET_SET_OPT),Y)
        include $(APPLICATIONS_DIR)/ticket_set_opt/ticket_set_opt.mk
    endif

    ifeq ($(APPLICATIONS_COMMANDS),Y)
        MCAL_OPT += -DHAS_APPLICATIONS_COMMANDS
        SOURCES_C += $(APPLICATIONS_DIR)/applications_commands.c
    endif

endif
