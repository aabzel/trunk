
ifneq ($(TEST_SET_SW_MK_INC),Y)
    TEST_SET_SW_MK_INC=Y

    TEST_SET_SW_DIR=$(UNIT_TESTS_DIR)/test_set_sw
    # $(error TEST_SET_SW_DIR= $(TEST_SET_SW_DIR))
    # $(error TEST_SW=$(TEST_SW))

    INCDIR += -I$(TEST_SET_SW_DIR)

    ifeq ($(MEDIAN_FILTER),Y)
        # $(error MEDIAN_FILTER=$(MEDIAN_FILTER))
        include $(TEST_SET_SW_DIR)/test_median_filter/test_median_filter.mk
    endif

    ifeq ($(TEST_ARRAY),Y)
        # $(error TEST_AES256=$(TEST_AES256))
        include $(TEST_SET_SW_DIR)/test_array/test_array.mk
    endif

    ifeq ($(TEST_DC_CUT_FILTER),Y)
        # $(error DC_CUT_FILTER=$(DC_CUT_FILTER))
        include $(TEST_SET_SW_DIR)/test_dc_cut_filter/test_dc_cut_filter.mk
    endif

    ifeq ($(TEST_BPSK_4FS),Y)
        # $(error BPSK_4FS=$(BPSK_4FS))
        include $(TEST_SET_SW_DIR)/test_bpsk_4fs/test_bpsk_4fs.mk
    endif

    ifeq ($(TEST_TICKET_SET_OPT),Y)
        # $(error TEST_AES256=$(TEST_AES256))
        include $(TEST_SET_SW_DIR)/test_ticket_set_opt/test_ticket_set_opt.mk
    endif

    ifeq ($(TEST_FLASH_FS),Y)
        include $(TEST_SET_SW_DIR)/test_flash_fs/test_flash_fs.mk
    endif
    
    ifeq ($(TEST_AES256),Y)
        # $(error TEST_AES256=$(TEST_AES256))
        include $(TEST_SET_SW_DIR)/test_aes/test_aes.mk
    endif

    ifeq ($(TEST_AUTO_VERSION),Y)
        include $(TEST_SET_SW_DIR)/test_auto_version/test_auto_version.mk
    endif

    ifeq ($(TEST_ALLOCATOR),Y)
        include $(TEST_SET_SW_DIR)/test_allocator/test_allocator.mk
    endif

    ifeq ($(TEST_BPSK),Y)
        # $(error TEST_BPSK=$(TEST_BPSK))
        include $(TEST_SET_SW_DIR)/test_bpsk/test_bpsk.mk
    endif
    
    ifeq ($(TEST_BASE16),Y)
        # $(error TEST_BASE16=$(TEST_BASE16))
        include $(TEST_SET_SW_DIR)/test_base16/test_base16.mk
    endif

    ifeq ($(TEST_CALIBRATION_DATA),Y)
        include $(TEST_SET_SW_DIR)/test_calibration_data/test_calibration_data.mk
    endif

    ifeq ($(TEST_CALCULATOR),Y)
        include $(TEST_SET_SW_DIR)/test_calculator/test_calculator.mk
    endif

    ifeq ($(TEST_CIRCULAR_BUFFER),Y)
        include $(TEST_SET_SW_DIR)/test_circular_buffer/test_circular_buffer.mk
    endif

    ifeq ($(TEST_DFT),Y)
        include $(TEST_SET_SW_DIR)/test_dft/test_dft.mk
    endif

    ifeq ($(TEST_FFT),Y)
        include $(TEST_SET_SW_DIR)/test_fft/test_fft.mk
    endif

    ifeq ($(TEST_BASE64),Y)
        include $(TEST_SET_SW_DIR)/test_base64/test_base64.mk
    endif

    ifeq ($(BIT_FIFO),Y)
        include $(TEST_SET_SW_DIR)/test_bit_fifo/test_bit_fifo.mk
    endif

    ifeq ($(TEST_DDS),Y)
        include $(TEST_SET_SW_DIR)/test_dds/test_dds.mk
    endif


    ifeq ($(TEST_DS_TWR),Y)
        include $(TEST_SET_SW_DIR)/test_ds_twr/test_ds_twr.mk
    endif
    
    ifeq ($(TEST_FIR),Y)
        include $(TEST_SET_SW_DIR)/test_fir/test_fir.mk
    endif

    ifeq ($(TEST_FONT),Y)
        # $(error TEST_FONT=$(TEST_FONT))
        include $(TEST_SET_SW_DIR)/test_font/test_font.mk
    endif

    ifeq ($(TEST_HASH_TABLE),Y)
        include $(TEST_SET_SW_DIR)/test_hash_table/test_hash_table.mk
    endif

    ifeq ($(TEST_HEX_BIN),Y)
        include $(TEST_SET_SW_DIR)/test_hex_bin/test_hex_bin.mk
    endif

    ifeq ($(TEST_HASHSET),Y)
        include $(TEST_SET_SW_DIR)/test_hashset/test_hashset.mk
    endif

    ifeq ($(TEST_KEEPASS),Y)
        include $(TEST_SET_SW_DIR)/test_keepass/test_keepass.mk
    endif

    ifeq ($(TEST_KEYBOARD),Y)
        include $(TEST_SET_SW_DIR)/test_keyboard/test_keyboard.mk
    endif

    ifeq ($(TEST_IQUEUE),Y)
        # $(error TEST_IQUEUE=$(TEST_IQUEUE))
        include $(TEST_SET_SW_DIR)/test_iqueue/test_iqueue.mk
    endif
    
    ifeq ($(TEST_PASTILDA),Y)
        include $(TEST_SET_SW_DIR)/test_pastilda/test_pastilda.mk
    endif

    ifeq ($(TEST_MISCELLANEOUS),Y)
        include $(TEST_SET_SW_DIR)/test_misc/test_misc.mk
    endif

    ifeq ($(TEST_MODULATOR),Y)
        include $(TEST_SET_SW_DIR)/test_modulator/test_modulator.mk
    endif

    ifeq ($(TEST_RLE),Y)
        # $(error TEST_RLE=$(TEST_RLE))
        include $(TEST_SET_SW_DIR)/test_rle/test_rle.mk
    endif

    ifeq ($(TEST_IIR),Y)
        include $(TEST_SET_SW_DIR)/test_iir/test_iir.mk
    endif

    ifeq ($(TEST_SALSA20),Y)
        include $(TEST_SET_SW_DIR)/test_salsa20/test_salsa20.mk
    endif

    ifeq ($(TEST_TIME),Y)
        include $(TEST_SET_SW_DIR)/test_time/test_time.mk
    endif

    ifeq ($(TEST_CORRELATOR_S16),Y)
        include $(TEST_SET_SW_DIR)/test_correlator_s16/test_correlator_s16.mk
    endif

    ifeq ($(TEST_BT1026),Y)
        # $(error TEST_BT1026=$(TEST_BT1026))
        include $(TEST_SET_SW_DIR)/test_bt1026/test_bt1026.mk
    endif

    ifeq ($(TEST_DECAWAVE),Y)
        # $(error TEST_DECAWAVE=$(TEST_DECAWAVE))
        include $(TEST_SET_SW_DIR)/test_decawave_proto/test_decawave_proto.mk
    endif

    ifeq ($(TEST_DECAWAVE_NATIVE),Y)
        # $(error TEST_DECAWAVE_NATIVE=$(TEST_DECAWAVE_NATIVE))
        include $(TEST_SET_SW_DIR)/test_decawave_native/test_decawave_native.mk
    endif

    ifeq ($(TEST_CROSS_DETECT),Y)
        include $(TEST_SET_SW_DIR)/test_cross_detect/test_cross_detect.mk
    endif

    ifeq ($(TEST_SLIDING_INTEGRAL),Y)
        include $(TEST_SET_SW_DIR)/test_sliding_integral/test_sliding_integral.mk
    endif

    ifeq ($(TEST_FLOAT),Y)
        include $(TEST_SET_SW_DIR)/test_float/test_float.mk
    endif

    ifeq ($(TEST_CALENDAR),Y)
        include $(TEST_SET_SW_DIR)/test_calendar/test_calendar.mk
    endif

    ifeq ($(TEST_UDS_SERVER),Y)
        # $(error TEST_UDS_SERVER=$(TEST_UDS_SERVER))
        include $(TEST_SET_SW_DIR)/test_uds_server/test_uds_server.mk
    endif

    ifeq ($(TEST_CLI),Y)
        # $(error TEST_CLI=$(TEST_CLI))
        include $(TEST_SET_SW_DIR)/test_cli/test_cli.mk
    endif

    ifeq ($(TEST_INTERVAL),Y)
        # $(error TEST_INTERVAL=$(TEST_INTERVAL))
        include $(TEST_SET_SW_DIR)/test_interval/test_interval.mk
    endif

    ifeq ($(TEST_LITTLE_FS),Y)
        include $(TEST_SET_SW_DIR)/test_little_fs/test_little_fs.mk
    endif

    ifeq ($(TEST_LC3),Y)
        # $(error TEST_LC3=$(TEST_LC3))
        include $(TEST_SET_SW_DIR)/test_lc3/test_lc3.mk
    endif

    ifeq ($(TEST_MATH),Y)
        # $(error TEST_MATH=$(TEST_MATH))
        include $(TEST_SET_SW_DIR)/test_math/test_math.mk
    endif

    ifeq ($(TEST_RDS),Y)
        include $(TEST_SET_SW_DIR)/test_rds_proto/test_rds_proto.mk
    endif

    ifeq ($(TEST_SW_NVRAM),Y)
        # $(error TEST_SW_NVRAM=$(TEST_SW_NVRAM))
        include $(TEST_SET_SW_DIR)/test_sw_nvram/test_sw_nvram.mk
    endif

    ifeq ($(TEST_SET),Y)
        include $(TEST_SET_SW_DIR)/test_set/test_set.mk
    endif

    ifeq ($(TEST_SHA256),Y)
        # $(error TEST_SHA256=$(TEST_SHA256))
        include $(TEST_SET_SW_DIR)/test_sha256/test_sha256.mk
    endif

    ifeq ($(TEST_SOLVER),Y)
        # $(error TEST_SOLVER=$(TEST_SOLVER))
        include $(TEST_SET_SW_DIR)/test_solver/test_solver.mk
    endif

    ifeq ($(MEDIAN_FILTER_FAST),Y)
        # $(error MEDIAN_FILTER_FAST=$(MEDIAN_FILTER_FAST))
        include $(TEST_SET_SW_DIR)/test_median_filter_fast/test_median_filter_fast.mk
    endif

    ifeq ($(TEST_RATIONAL_NUM),Y)
        # $(error TEST_RATIONAL_NUM=$(TEST_RATIONAL_NUM))
        include $(TEST_SET_SW_DIR)/test_rational_num/test_rational_num.mk
    endif

    ifeq ($(TEST_SOLVER_EXPRESSION),Y)
        # $(error TEST_SOLVER_EXPRESSION=$(TEST_SOLVER_EXPRESSION))
        include $(TEST_SET_SW_DIR)/test_solver_expression/test_solver_expression.mk
    endif

    ifeq ($(TEST_TUNER_PRO),Y)
        include $(TEST_SET_SW_DIR)/test_tuner_pro/test_tuner_pro.mk
    endif

    ifeq ($(TEST_TBFP),Y)
        include $(TEST_SET_SW_DIR)/test_tbfp/test_tbfp.mk
    endif

    ifeq ($(TEST_FAT_FS),Y)
        include $(TEST_SET_SW_DIR)/test_fat_fs/test_fat_fs.mk
    endif

    ifeq ($(TEST_ESP_01),Y)
        include $(TEST_SET_SW_DIR)/test_esp_01/test_esp_01.mk
    endif
    
    ifeq ($(TEST_MEMORY),Y)
        include $(TEST_SET_SW_DIR)/test_memory/test_memory.mk
    endif

    ifeq ($(TEST_RTCM),Y)
        include $(TEST_SET_SW_DIR)/test_rtcm3_proto/test_rtcm3_proto.mk
    endif

    ifeq ($(TEST_CSV),Y)
        include $(TEST_SET_SW_DIR)/test_csv/test_csv.mk
    endif
    
    ifeq ($(TEST_SOCKET),Y)
        include $(TEST_SET_SW_DIR)/test_socket/test_socket.mk
    endif

    ifeq ($(TEST_GNSS),Y)
        include $(TEST_SET_SW_DIR)/test_gnss/test_gnss.mk
    endif

    ifeq ($(TEST_NMEA),Y)
        include $(TEST_SET_SW_DIR)/test_nmea_proto/test_nmea_proto.mk
    endif

    ifeq ($(TEST_LIFO),Y)
        include $(TEST_SET_SW_DIR)/test_lifo/test_lifo.mk
    endif

    ifeq ($(TEST_ISO_TP),Y)
        # $(error TEST_ISO_TP=$(TEST_ISO_TP))
        include $(TEST_SET_SW_DIR)/test_iso_tp/test_iso_tp.mk
    endif

    ifeq ($(TEST_PLANETARIUM),Y)
        include $(TEST_SET_SW_DIR)/test_planetarium/test_planetarium.mk
    endif

    ifeq ($(TEST_PROTOCOL),Y)
        # $(error TEST_PROTOCOL=$(TEST_PROTOCOL))
        include $(TEST_SET_SW_DIR)/test_protocol/test_protocol.mk
    endif

    ifeq ($(TEST_FIFO),Y)
        include $(TEST_SET_SW_DIR)/test_fifo/test_fifo.mk
    endif

    ifeq ($(TEST_STORE_FS),Y)
        include $(TEST_SET_SW_DIR)/test_store_fs/test_store_fs.mk
    endif
    
    ifeq ($(TEST_CRC),Y)
        include $(TEST_SET_SW_DIR)/test_crc/test_crc.mk
    endif

    ifeq ($(AES256),Y)
        $(info + AES256 test cases)
        include $(TEST_SET_SW_DIR)/aes_test_utils/aes_test.mk
    endif

    ifeq ($(TEST_PYRAMID_ACCEL_CALIB),Y)
            include $(TEST_SET_SW_DIR)/test_pyramid_accel_calib/test_pyramid_accel_calib.mk
    endif

    ifeq ($(SOUND_LOCALIZATION),Y)
        include $(TEST_SET_SW_DIR)/test_sound_localization/test_sound_localization.mk
    endif

    ifeq ($(TEST_STRING),Y)
        include $(TEST_SET_SW_DIR)/test_string/test_string.mk
    endif

    ifeq ($(TEST_MAX_HEAP),Y)
        $(info + TEST_MAX_HEAP)
        include $(TEST_SET_SW_DIR)/test_max_heap/test_max_heap.mk
    endif

    ifeq ($(TEST_MIN_HEAP),Y)
        $(info + TEST_MIN_HEAP)
        include $(TEST_SET_SW_DIR)/test_min_heap/test_min_heap.mk
    endif

    ifeq ($(TEST_SOUND_RECORDER),Y)
        # $(error TEST_SOUND_RECORDER=$(TEST_SOUND_RECORDER))
        include $(TEST_SET_SW_DIR)/test_sound_recorder/test_sound_recorder.mk
    endif

    ifeq ($(TEST_SCHMITT_TRIGGER),Y)
        $(info + TEST_SCHMITT_TRIGGER)
        include $(TEST_SET_SW_DIR)/test_schmitt_trigger/test_schmitt_trigger.mk
    endif

    ifeq ($(TEST_PHYSICS),Y)
        $(info Add Utils Test Mk)
        include $(TEST_SET_SW_DIR)/test_physics/test_physics.mk
    endif

    ifeq ($(TEST_TBFP),Y)
        ifeq ($(TEST_RTCM),Y)
            include $(TEST_SET_SW_DIR)/test_tbfp_rtcm_proto/test_tbfp_rtcm_proto.mk
        endif
    endif

    ifeq ($(TEST_SLCAN),Y)
        include $(TEST_SET_SW_DIR)/test_slcan/test_slcan.mk
    endif

    ifeq ($(TEST_UDS_CLIENT),Y)
        include $(TEST_SET_SW_DIR)/test_uds_client/test_uds_client.mk
    endif

    ifeq ($(TEST_UBX),Y)
        include $(TEST_SET_SW_DIR)/test_ublox_proto/test_ublox_proto.mk
    endif

    ifeq ($(TEST_MANCHESTER_DECODE),Y)
        include $(TEST_SET_SW_DIR)/test_manchester_decode/test_manchester_decode.mk
    endif

    ifeq ($(TEST_MISC),Y)
        $(info Add Utils Test Mk)
        include $(TEST_SET_SW_DIR)/test_utils/test_utils.mk
    endif

    include $(TEST_SET_SW_DIR)/test_libc/test_libc.mk

    ifeq ($(TEST_HIST_FILTER),Y)
        include $(TEST_SET_SW_DIR)/test_hist_filter/test_hist_filter.mk
    endif

    ifeq ($(TEST_M_SEQ),Y)
        include $(TEST_SET_SW_DIR)/test_m_seq/test_m_seq.mk
    endif

    ifeq ($(TEST_LOOPBACK_AUDIO),Y)
        include $(TEST_SET_SW_DIR)/test_loopback_audio/test_loopback_audio.mk
    endif

    ifeq ($(TEST_WAV),Y)
        include $(TEST_SET_SW_DIR)/test_wav/test_wav.mk
    endif

    ifeq ($(TEST_WAV_PLAYER),Y)
        # $(error TEST_WAV_PLAYER=$(TEST_WAV_PLAYER))
        include $(TEST_SET_SW_DIR)/test_wav_player/test_wav_player.mk
    endif

    ifeq ($(TEST_XPRINTF),Y)
        # $(error TEST_XPRINTF=$(TEST_XPRINTF))
        include $(TEST_SET_SW_DIR)/test_xprintf/test_xprintf.mk
    endif

    SOURCES_C += $(TEST_SET_SW_DIR)/test_sw_list.c
endif