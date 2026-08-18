#ifndef FM_STATIONS_CONFIG_H
#define FM_STATIONS_CONFIG_H

#include "si4737_types.h"

#define RADIO_IZVESTIA 107.0
#define RADIO_LIKE_FM 87.9
#define RADIO_DACHA 92.4
#define RADIO_RETRO 88.3
#define RADIO_HUMMOR 88.7
#define RADIO_CULTURE 91.6
#define RADIO_AUTORATIO 90.3
#define RADIO_SPUTNIK 91.2
#define RADIO_RELAX 90.8
#define RADIO_CHILD 96.8
#define RADIO_BUSINESS 87.5
#define RADIO_POLICE_WAVE 107.8

extern const FmStationInfo_t FmStationInfoLut[];
uint16_t fm_statinos_cnt(void);
bool fm_stations_set(char* station_name);

#endif /* FM_STATIONS_CONFIG_H */
