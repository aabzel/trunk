#ifndef CORE_SELECT_H
#define CORE_SELECT_H

#include "nrfx_common.h"

#ifdef HAS_CORE_APP
#include "nrf5340_application.h"
#ifdef HAS_NORTOS
#include "nrfx_irqs_nrf5340_application.h"
#endif /*HAS_NORTOS*/
#endif /*HAS_CORE_APP*/

#ifdef HAS_CORE_NET
#include "nrf5340_network.h"
#endif


#endif /* CORE_SELECT_H */

