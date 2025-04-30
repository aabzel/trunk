#include "test_socket.h"

#include "socket_if.h"
#include "unit_test_check.h"

bool test_socket(void) {
    bool res = true;
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(LG_SOCKET, LOG_LEVEL_DEBUG);

    uint8_t ip_array[5]={0};
    memset(ip_array,0,sizeof(ip_array));
    ASSERT_FALSE(try_str2ip_v4("999.170.76.224", ip_array));

    memset(ip_array,0,sizeof(ip_array));
    ASSERT_TRUE(try_str2ip_v4("192.168.3.66", ip_array));
    ASSERT_EQ(192,ip_array[0]);
    ASSERT_EQ(168,ip_array[1]);
    ASSERT_EQ(3,ip_array[2]);
    ASSERT_EQ(66,ip_array[3]);

    memset(ip_array,0,sizeof(ip_array));
    ASSERT_TRUE(try_str2ip_v4("185.170.76.224", ip_array));
    ASSERT_EQ(185,ip_array[0]);
    ASSERT_EQ(170,ip_array[1]);
    ASSERT_EQ(76,ip_array[2]);
    ASSERT_EQ(224,ip_array[3]);


    set_log_level(LG_SOCKET, LOG_LEVEL_INFO);
    return res;
}
