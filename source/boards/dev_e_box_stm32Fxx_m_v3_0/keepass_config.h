#ifndef KEEPASS_CONFIG_H
#define KEEPASS_CONFIG_H

#include "std_includes.h"
#include "keepass_types.h"
#include "keepass_cfg.h"

#ifndef HAS_KEEPASS
#error "Add HAS_KEEPASS"
#endif /*HAS_KEEPASS*/

extern const KeePassConfig_t KeePassConfig;
extern KeePassHandle_t KeePassItem;

#endif /* KEEPASS_CONFIG_H  */
