#include "jumper_code_config.h"

#include "data_utils.h"

//https://stm32-base.org/boards/STM32F407ZGT6-STM32F4XX.html
static const JumperCodePosition_t JumperCodePosition[]={
/*3   -   -   PD10 set
 4   -   -   PD9  get */
        {    .code = 0, .valid = true, .set={.port=PORT_D, .pin=10,}, .get={.port=PORT_D, .pin=9,},},

/*5   -   -   PD8 set
  6   -   -   PE15  get*/
        {    .code = 1, .valid = true, .set={.port=PORT_D, .pin=8,}, .get={.port=PORT_E, .pin=15,},},


/*7   -   -   PE14 set
  8   -   -   PE13  get*/
        {    .code = 2, .valid = true, .set={.port=PORT_E, .pin=14,}, .get={.port=PORT_E, .pin=13,},},


/*9   -   -   PE12 set
  10  -   -   PE11  get*/
        {    .code = 3, .valid = true, .set={.port=PORT_E, .pin=12,}, .get={.port=PORT_E, .pin=11,},},


/*11  -   -   PE10 set
  12  -   -   PE9  get*/
        {    .code = 4, .valid = true, .set={.port=PORT_E, .pin=10,}, .get={.port=PORT_E, .pin=9,},},

/*13  -   -   PE8 set
  14  -   -   PE7  get*/
        {    .code = 5, .valid = true, .set={.port=PORT_E, .pin=8,}, .get={.port=PORT_E, .pin=7,},},

/*15  -   -   PD1 set
  16  -   -   PD0  get*/
        {    .code = 6, .valid = true, .set={.port=PORT_D, .pin=1,}, .get={.port=PORT_D, .pin=0,},},

/*17  -   -   PD15 set
  18  -   -   PD14  get*/
        {    .code = 7, .valid = true, .set={.port=PORT_D, .pin=15,}, .get={.port=PORT_D, .pin=14,},},

/*19  -   -   PD4 set
  20  -   -   PD5  get*/
        {    .code = 8, .valid = true, .set={.port=PORT_D, .pin=4,}, .get={.port=PORT_D, .pin=5,},},

/*21  -   -   PF12 set
  22  -   -   PG12  get*/
        {    .code = 9, .valid = true, .set={.port=PORT_F, .pin=12,}, .get={.port=PORT_G, .pin=12,},},

/*23  -   -   PB0 set
  24  -   -   PC13  get*/
        {    .code = 10, .valid = true, .set={.port=PORT_B, .pin=0,}, .get={.port=PORT_C, .pin=13,},},

/*25  -   -   PF11 set
  26  -   -   PB2  get*/
        {    .code = 11, .valid = true, .set={.port=PORT_F, .pin=11,}, .get={.port=PORT_B, .pin=2,},},


/*27  -   -   PB1 set
  28  -   -   PB15  get*/
        {    .code = 12, .valid = true, .set={.port=PORT_B, .pin=1,}, .get={.port=PORT_B, .pin=15,},},
};


const JumperCodeConfig_t JumperCodeConfig[] = {
    {
        .num = 1,
        .Position = JumperCodePosition,
        .position_cnt = ARRAY_SIZE(JumperCodePosition),
        .valid = true,
        .name = "JUMPER_CODE1",
    },

};



JumperCodeHandle_t JumperCodeInstance[] = {
    {
        .num = 1,
        .valid = true,
    },
};

COMPONENT_GET_CNT(JumperCode, jumper_code)


