#include "test_protocol.h"

#include "log.h"
#include "protocol.h"
#include "system.h"
#include "unit_test_check.h"
#include "protocol_diag.h"

bool test_protocol_types(void) {
    bool res = true;
    LOG_DEBUG(PROTOCOL, "%s():", __FUNCTION__);
    set_log_level(PROTOCOL, LOG_LEVEL_DEBUG);


    set_log_level(PROTOCOL, LOG_LEVEL_INFO);

    return res;
}


bool test_protocol_diag(void){
    bool res = true;
    LOG_DEBUG(PROTOCOL, "%s():", __FUNCTION__);
    Addr32Mask_t Mask;
    char* lText=NULL;

    Mask.size=0;
    Mask.addr=0;
    lText=Mask322Str(&Mask);
    LOG_INFO(PROTOCOL,"%s",lText);
    ASSERT_STREQ("x:0", lText);

    Mask.size=1;
    Mask.addr=1;
    lText=Mask322Str(&Mask);
    LOG_INFO(PROTOCOL,"%s",lText);
    ASSERT_STREQ("x1:1", lText);

    Mask.size=1;
    Mask.addr=0;
    lText=Mask322Str(&Mask);
    LOG_INFO(PROTOCOL,"%s",lText);
    ASSERT_STREQ("x0:1", lText);

    Mask.size=2;
    Mask.addr=3;
    lText=Mask322Str(&Mask);
    LOG_INFO(PROTOCOL,"%s",lText);
    ASSERT_STREQ("x11:2", lText);

    return res;
}


bool test_protocol_flow_ctrl(void) {
    bool res = true;
    LOG_DEBUG(PROTOCOL, "%s():", __FUNCTION__);
    set_log_level(PROTOCOL, LOG_LEVEL_DEBUG);

    set_log_level(PROTOCOL, LOG_LEVEL_INFO);
    return res;
}

bool test_protocol_flow_ctrl2(void) {
    bool res = true;
    LOG_DEBUG(PROTOCOL, "%s():", __FUNCTION__);
    set_log_level(PROTOCOL, LOG_LEVEL_DEBUG);
    set_log_level(PROTOCOL, LOG_LEVEL_INFO);
    return res;
}

