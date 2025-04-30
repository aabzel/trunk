#include "keepass_config.h"

#include "cryp_config.h"

const KeePassConfig_t KeePassConfig = {
    .cryp_num = CRYP_HW_NUM,
	.valid = true,
};

KeePassHandle_t KeePassItem= {
		.valid = true,
};
