#include "keepass_config.h"

#include "keepass_types.h"

#include "cryp_config.h"

const KeePassConfig_t KeePassConfig = {
    .cryp_num = CRYP_SW_NUM,
    .valid = true,
};

KeePassHandle_t KeePassItem= {
    .valid = true,
    .cryp_num = CRYP_SW_NUM,
};
