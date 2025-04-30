#include "board_layout.h"

#include <stdlib.h>

#include "data_utils.h"
#include "gpio_mcal.h"
#include "sys_config.h"

/*line order does not  matters!*/
const Pin_t PinTable[] = {
		{.level=-1, .pull_mode=PULL_UP, .dir=GPIO_DIR_IN, .dio=38, .mcu_pin=7, .name="BTN"}, //init error
		{.level=1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=18, .mcu_pin=35,.name="LoRaSS"},//ok
		{.level=0, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=4,  .mcu_pin=24,.name="LED"},/*ok*/
		{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=32, .mcu_pin=12,.name="LoRaBusy"}, //ok
		{.level=1,  .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=23, .mcu_pin=36,.name="LoRaRst"}, // ok
		{.level=1,  .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=15, .mcu_pin=21,.name="IO15"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=36, .mcu_pin=5, .name="IO36"},// ok
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=37, .mcu_pin=6, .name="IO37"},// ok
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=34, .mcu_pin=10,.name="TXD1"},// ok
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=35, .mcu_pin=11,.name="IO35"},// ok
		{.level=1, .pull_mode = PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=33, .mcu_pin=13,.name="LoRaIo1"},// ok
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=25, .mcu_pin=14,.name="IO25"},// ok
		{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=26, .mcu_pin=15,.name="LoRaIo0"},// ok
		{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=0,  .mcu_pin=23,.name="IO0"},// ok
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=27, .mcu_pin=16,.name="MOSI/SDI"},// ok
		{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=14, .mcu_pin=17,.name="IO14"},// ok
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=16, .mcu_pin=25,.name="GPIO16"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=2,  .mcu_pin=22,.name="IO2"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=10, .mcu_pin=29,.name="SWP/SD3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=13, .mcu_pin=20,.name="IO13"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=12, .mcu_pin=18,.name="RXD1"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=17, .mcu_pin=27,.name="GPIO17"}, /**/
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=3,  .mcu_pin=40,.name="U0RXD"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=6,  .mcu_pin=31,.name="SCK/CLK"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=5,  .mcu_pin=34,.name="SCK"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=8,  .mcu_pin=33,.name="SDI/SD1"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=39, .mcu_pin=8, .name="IO39"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=22, .mcu_pin=39,.name="IO22"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=9,  .mcu_pin=28,.name="SHD/SD2"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=11, .mcu_pin=30,.name="SCS/CMD"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=21, .mcu_pin=42,.name="IO21"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=19, .mcu_pin=38,.name="MISO/SDO"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=7,  .mcu_pin=32,.name="SDO/SD0"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_INOUT, .dio=-1, .mcu_pin=2, .name="LNA_IN"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=3, .name="VDD3P3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=4, .name="VDD3P3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN,.dio=-1, .mcu_pin=1, .name="3V3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=19,.name="3V3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=9, .name="RST/EN"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=-1, .mcu_pin=26,.name="VDD_SDIO"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=37,.name="3V3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_OUT, .dio=1,  .mcu_pin=41, .name="U0TXD"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=43,.name="3V3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=44,.name="XTAL_N"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=45,.name="XTAL_P"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=46,.name="3V3"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=47,.name="CAP2"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=48,.name="CAP1"},
		//{.level=-1, .pull_mode=PULL_AIR, .dir=GPIO_DIR_IN, .dio=-1, .mcu_pin=49,.name="GND"},
};

uint32_t pin_get_cnt(void){
	uint32_t cnt = ARRAY_SIZE(PinTable);
	return cnt;
}





































