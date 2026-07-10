$(info APPS_PRECONFIG_MK_INC=$(APPS_PRECONFIG_MK_INC))

ifneq ($(APPS_PRECONFIG_MK_INC),Y)
    APPS_PRECONFIG_MK_INC=Y

    APPLICATIONS_DIR = $(WORKSPACE_LOC)/applications

    APPLICATIONS=Y

    ifeq ($(AUTO_BRIGHTNESS),Y)
        include $(APPLICATIONS_DIR)/auto_brightness/auto_brightness_preconfig.mk
    endif

    ifeq ($(AKIP1160),Y)
        include $(APPLICATIONS_DIR)/akip1160/akip1160_preconfig.mk
    endif

    ifeq ($(ENCODER_LAMP),Y)
        include $(APPLICATIONS_DIR)/encoder_lamp/encoder_lamp_preconfig.mk
    endif

    ifeq ($(GNSS_PROVE),Y)
        include $(APPLICATIONS_DIR)/gnss_prove/gnss_prove_preconfig.mk
    endif

    ifeq ($(BPSK_DECODER),Y)
        include $(APPLICATIONS_DIR)/bpsk_decoder/bpsk_decoder_preconfig.mk
    endif

    ifeq ($(BICYCLE_HEADLAMP),Y)
        include $(APPLICATIONS_DIR)/bicycle_headlamp/bicycle_headlamp_preconfig.mk
    endif
    


    ifeq ($(PWM_PHASE_DEMO),Y)
        include $(APPLICATIONS_DIR)/pwm_phase_demo/pwm_phase_demo_preconfig.mk
    endif

    ifeq ($(AUTO_VERSION),Y)
        include $(APPLICATIONS_DIR)/auto_version/auto_version_preconfig.mk
    endif

    ifeq ($(AUTO_VOLUME),Y)
        include $(APPLICATIONS_DIR)/auto_volume/auto_volume_preconfig.mk
    endif

    ifeq ($(CAN_DIFF),Y)
        include $(APPLICATIONS_DIR)/can_diff/can_diff_preconfig.mk
    endif

    ifeq ($(CAN_RX_HIST),Y)
        # $(error CAN_RX_HIST=$(CAN_RX_HIST))
        include $(APPLICATIONS_DIR)/can_rx_hist/can_rx_hist_preconfig.mk
    endif

    ifeq ($(DEMAGNETIZER),Y)
        include $(APPLICATIONS_DIR)/demagnetizer/demagnetizer_preconfig.mk
    endif

    ifeq ($(RC_CAR),Y)
        include $(APPLICATIONS_DIR)/rc_car/rc_car_preconfig.mk
    endif


    ifeq ($(CAN_TX_PLANNER),Y)
        # $(error CAN_TX_PLANNER=$(CAN_TX_PLANNER))
        include $(APPLICATIONS_DIR)/can_tx_planner/can_tx_planner_preconfig.mk
    endif

    ifeq ($(CAN_CAT),Y)
        include $(APPLICATIONS_DIR)/can_cat/can_cat_preconfig.mk
    endif

    ifeq ($(DASHBOARD),Y)
        include $(APPLICATIONS_DIR)/dashboard/dashboard_preconfig.mk
    endif

    ifeq ($(END_OF_BLOCK),Y)
        include $(APPLICATIONS_DIR)/end_of_block/end_of_block_preconfig.mk
    endif

    ifeq ($(GARLAND),Y)
        include $(APPLICATIONS_DIR)/garland/garland_preconfig.mk
    endif

    ifeq ($(LIGHT_NAVIGATOR),Y)
        include $(APPLICATIONS_DIR)/light_navigator/light_navigator_preconfig.mk
    endif

    ifeq ($(PASTILDA),Y)
        # $(error PASTILDA=$(PASTILDA))
        include $(APPLICATIONS_DIR)/pastilda/pastilda_preconfig.mk
    endif

    ifeq ($(REC_PLAY),Y)
        include $(APPLICATIONS_DIR)/rec_play/rec_play_preconfig.mk
    endif

    ifeq ($(IR_FM_RADIO),Y)
        include $(APPLICATIONS_DIR)/ir_fm_radio/ir_fm_radio_preconfig.mk
    endif

    ifeq ($(KEYLOG),Y)
        include $(APPLICATIONS_DIR)/keylog/keylog_preconfig.mk
    endif

    ifeq ($(SONAR),Y)
        include $(APPLICATIONS_DIR)/sonar/sonar_preconfig.mk
    endif

    ifeq ($(SOUND_RECORDER),Y)
        include $(APPLICATIONS_DIR)/sound_recorder/sound_recorder_preconfig.mk
    endif

    ifeq ($(SMOOTH_LAMP),Y)
        include $(APPLICATIONS_DIR)/smooth_lamp/smooth_lamp_preconfig.mk
    endif

    ifeq ($(WAV_PLAYER),Y)
        include $(APPLICATIONS_DIR)/wav_player/wav_player_preconfig.mk
    endif

    ifeq ($(SOUND_LOCALIZATION),Y)
        include $(APPLICATIONS_DIR)/sound_localization/sound_localization_preconfig.mk
    endif

    ifeq ($(TICKET_SET_OPT),Y)
        include $(APPLICATIONS_DIR)/ticket_set_opt/ticket_set_opt_preconfig.mk
    endif
endif
