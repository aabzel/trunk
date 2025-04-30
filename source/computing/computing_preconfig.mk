ifneq ($(COMPUTING_PRECONFIG_MK_INC),Y)
    COMPUTING_PRECONFIG_MK_INC=Y

    COMPUTING_DIR = $(WORKSPACE_LOC)/computing
    #@echo $(error COMPUTING_DIR= $(COMPUTING_DIR))

    include $(COMPUTING_DIR)/interval/interval_preconfig.mk

    ifeq ($(ANALOG_FILTER),Y)
        include $(COMPUTING_DIR)/analog_filter/analog_filter_preconfig.mk
    endif

    ifeq ($(CALCULATOR),Y)
        include $(COMPUTING_DIR)/calculator/calculator_preconfig.mk
    endif

    ifeq ($(CRC),Y)
        include $(COMPUTING_DIR)/crc/crc_preconfig.mk
    endif

    ifeq ($(COMPLEX),Y)
        include $(COMPUTING_DIR)/complex/complex_preconfig.mk
    endif

    ifeq ($(CALENDAR),Y)
        include $(COMPUTING_DIR)/calendar/calendar_preconfig.mk
    endif

    ifeq ($(CONVERTOR),Y)
        include $(COMPUTING_DIR)/convertor/convertor_preconfig.mk
    endif

    ifeq ($(DELTA_SIGMA),Y)
        #@echo $(error DELTA_SIGMA=$(DELTA_SIGMA))
        include $(COMPUTING_DIR)/delta_sigma/delta_sigma_preconfig.mk
    endif

    ifeq ($(DSP),Y)
        include $(COMPUTING_DIR)/dsp/dsp_preconfig.mk
    endif

    ifeq ($(GNSS),Y)
        include $(COMPUTING_DIR)/gnss/gnss_preconfig.mk
    endif

    ifeq ($(IEC16022),Y)
        include $(COMPUTING_DIR)/iec16022/iec16022_preconfig.mk
    endif

	ifeq ($(LIMITER),Y)
        #@echo $(error LIMITER=$(LIMITER))
        include $(COMPUTING_DIR)/limiter/limiter_preconfig.mk
    endif

    ifeq ($(MATH),Y)
        #@echo $(error MATH=$(MATH))
        include $(COMPUTING_DIR)/math/math_preconfig.mk
    endif

    ifeq ($(MODULATOR),Y)
        include $(COMPUTING_DIR)/modulator/modulator_preconfig.mk
    endif

    ifeq ($(PLANETARIUM),Y)
        include $(COMPUTING_DIR)/planetarium/planetarium_preconfig.mk
    endif

    ifeq ($(PLL_CALC),Y)
        #@echo $(error PLL_CALC= $(PLL_CALC))
        include $(COMPUTING_DIR)/pll_calc/pll_calc_preconfig.mk
    endif

    ifeq ($(RLE),Y)
        include $(COMPUTING_DIR)/rle/rle_preconfig.mk
    endif

    ifeq ($(SHA256),Y)
        #@echo $(error SHA256=$(SHA256))
        include $(COMPUTING_DIR)/sha256/sha256_preconfig.mk
    endif

    ifeq ($(SOLVER),Y)
       #@echo $(error SOLVER=$(SOLVER))
       include $(COMPUTING_DIR)/solver/solver_preconfig.mk    
    endif

    ifeq ($(STATISTICS),Y)
        include $(COMPUTING_DIR)/statistics/statistics_preconfig.mk
    endif

    ifeq ($(DDS),Y)
        #@echo $(error DDS=$(DDS))
        include $(COMPUTING_DIR)/dds/dds_preconfig.mk
    endif

    ifeq ($(TIMER_CALC),Y)
        #@echo $(error TIMER_CALC= $(TIMER_CALC))
        include $(COMPUTING_DIR)/timer_calc/timer_calc_preconfig.mk
    endif

    ifeq ($(VOLTAGE_DIVIDER),Y)
        include $(COMPUTING_DIR)/voltage_divider/voltage_divider_preconfig.mk
    endif
endif