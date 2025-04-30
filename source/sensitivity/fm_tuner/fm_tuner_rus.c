#include "fm_tuner_rus.h"

#include "str_utils.h"
#include "log.h"
#include "data_utils.h"
#include "fm_tuner_types.h"

static  const FmStationInfo_t FmStationInfoLut[]={
      {.rds=false, .id=1,  .fm_freq_mhz=107.8,  .name="PoliceWave",},
      {.rds=false, .id=2,  .fm_freq_mhz=107.4,  .name="Hit",},
      {.rds=false,  .id=3,  .fm_freq_mhz=107.0,  .name="IZ",},
      {.rds=true,  .id=4,  .fm_freq_mhz=106.6,  .name="Love",},
      {.rds=true,  .id=5,  .fm_freq_mhz=106.2,  .name="EuropPlus",},
      {.rds=true,  .id=6,  .fm_freq_mhz=105.7,  .name="Russian",},
      {.rds=true,  .id=7,  .fm_freq_mhz=105.3,  .name="Capital",},
      {.rds=true,  .id=8,  .fm_freq_mhz=105.0,  .name="BookFM",},
      {.rds=false,  .id=9,  .fm_freq_mhz=104.7,  .name="7Hills",},
      {.rds=true,  .id=10, .fm_freq_mhz=104.2, .name="Energy",},
      {.rds=true,  .id=11, .fm_freq_mhz=103.7, .name="Maximum",},
      {.rds=true,  .id=12, .fm_freq_mhz=103.4, .name="LightHouse",},
      {.rds=false,  .id=13, .fm_freq_mhz=103.0, .name="Shanson",},
      {.rds=true,  .id=14, .fm_freq_mhz=102.5, .name="Comedy",},
      {.rds=true,  .id=15, .fm_freq_mhz=102.1, .name="MonteCarlo",},
      {.rds=true,  .id=16, .fm_freq_mhz=101.7, .name="Our",},
      {.rds=true,  .id=17, .fm_freq_mhz=101.2, .name="DanceFM",},
      {.rds=true,  .id=18, .fm_freq_mhz=100.9, .name="Faith",},
      {.rds=false,  .id=19, .fm_freq_mhz=100.5, .name="heat",},
      {.rds=true,  .id=20, .fm_freq_mhz=100.1, .name="SilverRain",},
      {.rds=false,  .id=21, .fm_freq_mhz=99.6,  .name="RussianHit",},
      {.rds=true,  .id=22, .fm_freq_mhz=99.2,  .name="Orphey",},
      {.rds=false,  .id=23, .fm_freq_mhz=98.8,  .name="Romantica",},
      {.rds=true,  .id=24, .fm_freq_mhz=98.4,  .name="New",},/**/
      {.rds=true,  .id=25, .fm_freq_mhz=98.0,  .name="Chocolate",},
      {.rds=true,  .id=26, .fm_freq_mhz=97.6,  .name="News",},
      {.rds=false,  .id=27, .fm_freq_mhz=97.2,  .name="truth",},
      {.rds=false,  .id=28, .fm_freq_mhz=96.8,  .name="Child",},
      {.rds=false,  .id=29, .fm_freq_mhz=96.4,  .name="Taxi",},
      {.rds=true,  .id=30, .fm_freq_mhz=96.0,  .name="Road",},
      {.rds=false,  .id=31, .fm_freq_mhz=95.6,  .name="Star",},
      {.rds=true,  .id=32, .fm_freq_mhz=95.2,  .name="Rock",},
      {.rds=false, .id=33, .fm_freq_mhz=94.8,  .name="MoscowSpeaks",},
      {.rds=false,  .id=34, .fm_freq_mhz=94.4,  .name="1Sport",},
      {.rds=false,  .id=35, .fm_freq_mhz=94.0,  .name="East",},
      {.rds=false, .id=36, .fm_freq_mhz=93.6,  .name="bussinesperson",},
      {.rds=false,  .id=37, .fm_freq_mhz=93.2,  .name="Studio21",},
      {.rds=false,  .id=38, .fm_freq_mhz=92.8,  .name="Carnaval",},
      {.rds=false, .id=39, .fm_freq_mhz=92.4,  .name="Dacha",},
      {.rds=true,  .id=40, .fm_freq_mhz=92.0,  .name="MoscowFM",},
      {.rds=true,  .id=41, .fm_freq_mhz=91.6,  .name="Culture",},
      {.rds=true,  .id=42, .fm_freq_mhz=91.2,  .name="Sputnick",},
      {.rds=false,  .id=43, .fm_freq_mhz=90.8,  .name="Relax",},
      {.rds=true,  .id=44, .fm_freq_mhz=90.3,  .name="Auto",},
      {.rds=true,  .id=45, .fm_freq_mhz=89.9,  .name="YourWave",},
      {.rds=false,  .id=46, .fm_freq_mhz=89.5,  .name="MegaPolic",},
      {.rds=true,  .id=47, .fm_freq_mhz=89.1,  .name="Jaz",},
      {.rds=false,  .id=48, .fm_freq_mhz=88.7,  .name="Humor",},
      {.rds=true, .id=49, .fm_freq_mhz=88.3,  .name="RertoFM",},
      {.rds=false,  .id=50, .fm_freq_mhz=87.9,  .name="Like",},
      {.rds=true,  .id=51, .fm_freq_mhz=87.5,  .name="Business",},


};

static uint16_t fm_statinos_count(void){
    return ARRAY_SIZE(FmStationInfoLut);
}

const FmStationInfo_t*   FmStationsGetNode(char*  station_name){
    const FmStationInfo_t* Node=NULL;
    uint16_t cnt = fm_statinos_count();
    uint16_t s=0;
    char key_word2[]="";
    for(s=0;s<cnt;s++){
        if(is_contain(FmStationInfoLut[s].name, station_name, key_word2)) {
            Node=&FmStationInfoLut[s];
        }
    }
    return Node;
}

