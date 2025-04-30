#include "uds_config.h"

#include "data_utils.h"
#include "storage_const.h"

extern const RoutineIdentifierConfig_t RoutineIdentifierConfig[] ={
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_KL30_ON, .name="KL30_ON",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_KL15_ON, .name="KL15_ON",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_KL30_OFF, .name="KL30_OFF",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_KL15_OFF, .name="KL15_OFF",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_SOS1_ON, .name="SOS1_ON",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_SOS2_ON, .name="SOS2_ON",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_SERVICE_ON, .name="SERVICE_ON",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_ENS_10HZ, .name="ENS_10HZ",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_ENS_250HZ, .name="ENS_250HZ",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_ENS_500HZ, .name="ENS_500HZ",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_ENS_250HZ_500HZ, .name="250HZ_500HZ",},
    {.valid=true, .routine_identifier=UDS_ROUTINE_ID_ENS_OFF, .name="ENS_OFF",},
};

const DidConfig_t DidConfig[] = {
    {.num=1, .did=UDS_DID_INPUT_STATES,             .nvram=false, .access=ACCESS_READ_ONLY,  .type=TYPE_STRUCT, .size=2, .default_value="-", .name="InputStates", .valid= true,},
    {.num=2, .did=UDS_DID_OUTPUT_STATES,            .nvram=false, .access=ACCESS_READ_ONLY,  .type=TYPE_STRUCT, .size=2, .default_value="-", .name="OutputStates", .valid= true,},
    {.num=3, .did=UDS_DID_BOARD_VOLTAGE,            .nvram=false, .access=ACCESS_READ_ONLY,  .type=TYPE_UINT16, .size=2, .default_value="-", .name="BoardVoltageMv", .valid= true,},
    {.num=4, .did=UDS_DID_SYSTEM_STATE,             .nvram=false, .access=ACCESS_READ_ONLY,  .type=TYPE_STRUCT, .size=4, .default_value="-", .name="SystemState", .valid= true,},
    {.num=5, .did=UDS_DID_TIME_STAMP,               .nvram=false, .access=ACCESS_READ_ONLY,  .type=TYPE_UINT32, .size=4, .default_value="-", .name="Up-TimeMs", .valid= true,},
    {.num=6, .did=UDS_DID_SOS1_BUTTON_HOLD_TIME,    .nvram=true,  .access=ACCESS_READ_WRITE, .type=TYPE_UINT16, .size=2, .default_value="2000", .name="SOS1ButtonHoldTimeMs", .valid= true,},
    {.num=7, .did=UDS_DID_SOS2_BUTTON_HOLD_TIME,    .nvram=true,  .access=ACCESS_READ_WRITE, .type=TYPE_UINT16, .size=2, .default_value="2000", .name="SOS2ButtonHoldTimeMs", .valid= true,},
    {.num=8, .did=UDS_DID_SERVICE_BUTTON_HOLD_TIME, .nvram=true,  .access=ACCESS_READ_WRITE, .type=TYPE_UINT16, .size=2, .default_value="2000", .name="ServiceButtonHoldTimeMs", .valid= true,},
};

DidHandle_t DidInstance[] = {
    {.num=1, .valid= true,},
    {.num=2, .valid= true,},
    {.num=3, .valid= true,},
    {.num=4, .valid= true,},
    {.num=5, .valid= true,},
    {.num=6, .valid= true,},
    {.num=7, .valid= true,},
    {.num=8, .valid= true,},
};

const UdsConfig_t UdsConfig[] = {
    { .num = 1, .valid=true, .iso_tp_num = 1, },
    { .num = 2, .valid=true, .iso_tp_num = 2, }
};

UdsHandle_t UdsInstance[] = {
    {.num=1, .valid=true, },
    {.num=2, .valid=true, }
};

uint32_t uds_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(UdsInstance);
    cnt2 = ARRAY_SIZE(UdsConfig);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}

uint32_t did_get_cnt(void) {
    uint32_t cnt = 0;
    uint32_t cnt1 = 0;
    uint32_t cnt2 = 0;
    cnt1 = ARRAY_SIZE(DidConfig);
    cnt2 = ARRAY_SIZE(DidInstance);
    if(cnt1==cnt2){
        cnt = cnt1;
    }
    return cnt;
}

uint32_t routine_identifier_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(RoutineIdentifierConfig);
    return cnt;
}

