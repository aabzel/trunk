ifneq ($(COMPUTING_MK_INC),Y)
    COMPUTING_MK_INC=Y

    OPT += -DHAS_COMPUTING
    COMPUTING_DIR = $(WORKSPACE_LOC)/computing
    #@echo $(error COMPUTING_DIR= $(COMPUTING_DIR))

    INCDIR += -I$(COMPUTING_DIR)   

    ifeq ($(INTERVAL),Y)
        include $(COMPUTING_DIR)/interval/interval.mk
    endif

    ifeq ($(ANALOG_FILTER),Y)
        include $(COMPUTING_DIR)/analog_filter/analog_filter.mk
    endif

    ifeq ($(CALCULATOR),Y)
        include $(COMPUTING_DIR)/calculator/calculator.mk
    endif

    ifeq ($(CLOCK_DIVIDER),Y)
        #@echo $(error CLOCK_DIVIDER= $(CLOCK_DIVIDER))
        include $(COMPUTING_DIR)/clock_divider/clock_divider.mk
    endif


    ifeq ($(PLL_CALC),Y)
        #@echo $(error PLL_CALC= $(PLL_CALC))
        include $(COMPUTING_DIR)/pll_calc/pll_calc.mk
    endif

    ifeq ($(PLL_SIM),Y)
        #@echo $(error PLL_SIM= $(PLL_SIM))
        include $(COMPUTING_DIR)/pll_sim/pll_sim.mk
    endif


    ifeq ($(CRC),Y)
        include $(COMPUTING_DIR)/crc/crc.mk
    endif

    ifeq ($(COMPLEX),Y)
        include $(COMPUTING_DIR)/complex/complex.mk
    endif

    ifeq ($(CALENDAR),Y)
        include $(COMPUTING_DIR)/calendar/calendar.mk
    endif

    ifeq ($(CONVERTOR),Y)
        include $(COMPUTING_DIR)/convertor/convertor.mk
    endif

    ifeq ($(DELTA_SIGMA),Y)
        #@echo $(error DELTA_SIGMA=$(DELTA_SIGMA))
        include $(COMPUTING_DIR)/delta_sigma/delta_sigma.mk
    endif

    ifeq ($(DSP),Y)
        include $(COMPUTING_DIR)/dsp/dsp.mk
    endif

    ifeq ($(GNSS),Y)
        include $(COMPUTING_DIR)/gnss/gnss.mk
    endif

    ifeq ($(IEC16022),Y)
        include $(COMPUTING_DIR)/iec16022/iec16022.mk
    endif

	ifeq ($(LIMITER),Y)
        #@echo $(error LIMITER=$(LIMITER))
        include $(COMPUTING_DIR)/limiter/limiter.mk
    endif

    ifeq ($(MATH),Y)
        #@echo $(error MATH=$(MATH))
        include $(COMPUTING_DIR)/math/math.mk
    endif

    ifeq ($(MODULATOR),Y)
        include $(COMPUTING_DIR)/modulator/modulator.mk
    endif

    ifeq ($(PLANETARIUM),Y)
        include $(COMPUTING_DIR)/planetarium/planetarium.mk
    endif

    ifeq ($(RLE),Y)
        include $(COMPUTING_DIR)/rle/rle.mk
    endif

    ifeq ($(SHA256),Y)
        #@echo $(error SHA256=$(SHA256))
        include $(COMPUTING_DIR)/sha256/sha256.mk
    endif

    ifeq ($(SOLVER),Y)
        include $(COMPUTING_DIR)/solver/solver.mk    
    endif

    ifeq ($(DDS),Y)
        #@echo $(error DDS=$(DDS))
        include $(COMPUTING_DIR)/dds/dds.mk
    endif

    ifeq ($(STATISTICS),Y)
        include $(COMPUTING_DIR)/statistics/statistics.mk
    endif

    ifeq ($(TIMER_CALC),Y)
        #@echo $(error TIMER_CALC= $(TIMER_CALC))
        include $(COMPUTING_DIR)/timer_calc/timer_calc.mk
    endif

    ifeq ($(VOLTAGE_DIVIDER),Y)
        include $(COMPUTING_DIR)/voltage_divider/voltage_divider.mk
    endif

    #@echo $(error COMPUTING_DIR=$(COMPUTING_DIR))

    SOURCES_C += $(COMPUTING_DIR)/computing.c

    ifeq ($(CLI),Y)
        ifeq ($(COMPUTING_COMMANDS),Y)
            OPT += -DHAS_COMPUTING_COMMANDS
            SOURCES_C += $(COMPUTING_DIR)/computing_commands.c
        endif
    endif

    ifeq ($(DIAG),Y)
        ifeq ($(COMPUTING_DIAG),Y)
            OPT += -DHAS_COMPUTING_DIAG
            #@echo $(error COMPUTING_DIAG=$(COMPUTING_DIAG))
            SOURCES_C += $(COMPUTING_DIR)/computing_diag.c
        endif
    endif
endif