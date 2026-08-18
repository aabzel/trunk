#include "ublox_neo_6m.h"

#include "log.h"
#include "code_generator.h"

COMPONENT_GET_NODE(uBloxNeo6m, ublox_neo_6m)
COMPONENT_GET_CONFIG(uBloxNeo6m, ublox_neo_6m)


static bool ublox_neo_6m_init_custom(void){
	bool res = true;
	return res;
}

static bool ublox_neo_6m_init_one(uint8_t num){
	bool res = true;
	return res;
}

static bool ublox_neo_6m_proc_one(uint8_t num){
	bool res = true;
	return res;
}

COMPONENT_INIT_PATTERT(UBLOX_NEO_6M, UBLOX_NEO_6M, ublox_neo_6m)
COMPONENT_PROC_PATTERT(UBLOX_NEO_6M, UBLOX_NEO_6M, ublox_neo_6m)




