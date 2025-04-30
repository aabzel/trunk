#include "pdm_custom_diag.h"

#include "log.h"

bool PdmStaticInfoDiag (const PdmStaticInfo_t* const StaticInfo){
	bool res = false;
	if(StaticInfo) {
		LOG_INFO(PDM, "HandlerAddr 0x%p", StaticInfo->event_handler);
		LOG_INFO(PDM, "RegBaseAddr 0x%p", StaticInfo->registers);
		res = true;
	}
	return res;
}
