#include "dac_mcal.h"

#include <stdbool.h>
#include <string.h>

//#include "c_defines_generated.h"
#include "array_diag.h"
#include "microcontroller_const.h"
#include "artery_at32f4xx.h"
#include "byte_utils.h"
#include "data_types.h"
#include "debug_info.h"
#include "hal_diag.h"
#include "dac_custom_const.h"
#include "microcontrollet_types.h"
#include "dac_custom_diag.h"
#include "dac_custom_drv.h"
#include "dac_types.h"
#include "log.h"
#include "num_to_str.h"
#include "time_mcal.h"

#ifndef ARRAY_SIZE
#define ARRAY_SIZE(x) (sizeof(x) / sizeof((x)[0]))
#endif

const McuReg_t McuReg[] = {
    {
        .valid = true,
        .offset = 0x00,
        .name = "DAC_CTRL",
    },
    {
        .valid = true,
        .offset = 0x04,
        .name = "DAC_SWTRG",
    },
    {
        .valid = true,
        .offset = 0x08,
        .name = "DAC_D1DTH12R",
    },
    {
        .valid = true,
        .offset = 0x0C,
        .name = "DAC_D1DTH12L",
    },
    {
        .valid = true,
        .offset = 0x10,
        .name = "DAC_D1DTH8R",
    },
    {
        .valid = true,
        .offset = 0x14,
        .name = "DAC_D2DTH12R",
    },
    {
        .valid = true,
        .offset = 0x18,
        .name = "DAC_D2DTH12L",
    },
    {
        .valid = true,
        .offset = 0x1C,
        .name = "DAC_D2DTH8R",
    },
    {
        .valid = true,
        .offset = 0x20,
        .name = "DAC_DDTH12R",
    },
    {
        .valid = true,
        .offset = 0x24,
        .name = "DAC_DDTH12L",
    },
    {
        .valid = true,
        .offset = 0x28,
        .name = "DAC_DDTH8R",
    },
    {
        .valid = true,
        .offset = 0x2C,
        .name = "DAC_D1ODT",
    },
    {
        .valid = true,
        .offset = 0x30,
        .name = "DAC_D2ODT",
    },
    {
        .valid = true,
        .offset = 0x34,
        .name = "DAC_STS",
    },
};

uint32_t dac_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(McuReg);
    return cnt;
}

const static DacInfo_t DacInfo[] = {
#ifdef HAS_DAC1
    {
     .num = 1,
     .DACx = DAC1_SELECT,
     .Pad = {.port=PORT_A, .pin=4,},
     .clock_bus = BUS_AHB1,
     .irq_n = TMR6_DAC_GLOBAL_IRQn,
     .valid = true,
 },
#endif

#ifdef HAS_DAC2
    {
     .num = 2,
     .DACx = DAC2_SELECT,
     .Pad = {.port=PORT_A, .pin=5,},
     .valid = true,
     .clock_bus = BUS_AHB1,
     .irq_n = TMR6_DAC_GLOBAL_IRQn,
  },
#endif
};

const DacInfo_t* DacGetInfo(uint8_t num) {
    DacInfo_t* Node = NULL;
    uint32_t i = 0;
    uint32_t cnt = ARRAY_SIZE(DacInfo);
    for(i = 0; i < cnt; i++) {
        if(num == DacInfo[i].num) {
            if(DacInfo[i].valid) {
                Node = &DacInfo[i];
                break;
            }
        }
    }
    return Node;
}

bool dac_code_u16_set(uint8_t num, uint16_t code) {
    bool res = false;
    switch(num) {
    case 1 :{
        dac_1_data_set(DAC1_12BIT_LEFT, code);
        res = true;
    } break;
    case 2 :{
        dac_2_data_set(DAC2_12BIT_LEFT, code);
        res = true;
    } break;
    }

    return res;
}

uint16_t VoltToWord(double voltage) {
	uint16_t code =0;
	code = 4096.0*voltage/3.3;
    return code;
}

bool dac_voltage_set(uint8_t num, double voltage){
	bool res = false;
	uint16_t code = VoltToWord(voltage);
	res= dac_code_u16_set(  num,   code) ;
	return res;
}

bool dac_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(LG_DAC, "DAC%u Init", num);
    const DacConfig_t* Config = DacGetConfig(num);
    if(Config) {
        DacHandle_t* Node = DacGetNode(num);
        if(Node) {
            const DacInfo_t* Info = DacGetInfo(num);
            if(Info) {
                Node->DACx = Info->DACx;

                if(Config->interrupt_on) {
                    LOG_WARNING(LG_DAC, "INT:%u on", Info->irq_n);
                    nvic_irq_enable(Info->irq_n, 3, 3);

                }
//dac_software_trigger_generate
                dac_trigger_select(Node->DACx, DAC_SOFTWARE_TRIGGER);
                dac_trigger_enable(Node->DACx, TRUE);
                dac_wave_generate(Node->DACx, DAC_WAVE_GENERATE_TRIANGLE);
                dac_mask_amplitude_select(Node->DACx, DAC_LSFR_BITB0_AMPLITUDE_4095);
                dac_output_buffer_enable(Node->DACx, TRUE);
                dac_enable((dac_select_type)Node->DACx, TRUE);



                res = true;
                Node->init_done = true;
            } else {
                LOG_ERROR(LG_DAC, "NoInfo");
            }
            /* reset dac peripheral */
        } else {
            LOG_ERROR(LG_DAC, "NoNode");
        }
    } else {
        LOG_DEBUG(LG_DAC, "NoConfig");
    }

    /* dac peripheral enable */
    return res;
}


bool dac_init_custom(void) {
    bool res = false;
    dac_reset();
    nvic_irq_enable(TMR6_DAC_GLOBAL_IRQn, 3, 3);
    crm_periph_clock_enable(CRM_DAC_PERIPH_CLOCK, TRUE);
    return res;
}



bool dac_proc_one(uint8_t num) {
    bool res = false;
    const DacConfig_t* Config = DacGetConfig(num);
    if(Config) {
        LOG_PARN(LG_DAC, "DAC_%u,Proc", num);
        DacHandle_t* Node = DacGetNode(num);
        if(Node) {
        }
    }
    return res;
}

bool dac_code_u16_get(uint8_t num, uint16_t* const code) {
    bool res = false;
	DacHandle_t* Node=DacGetNode(num);
	if(Node){
		*code = dac_data_output_get(Node->DACx);
		res = true;
	}
    return res;

}
