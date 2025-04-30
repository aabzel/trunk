#include "test_keepass.h"

#include <string.h>

#include "keepass.h"
#include "log.h"
#include "unit_test_check.h"
#include "utils_math.h"

bool test_keepass_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(KEEPASS, LOG_LEVEL_DEBUG);
    ASSERT_EQ(12, sizeof(kdbx_header_t));
    ASSERT_EQ(35, sizeof(KdbxHeaderEntry_t));
    ASSERT_EQ(40, sizeof(kdbx_block_header_entry_t));
    set_log_level(KEEPASS, LOG_LEVEL_INFO);
    return true;
}

#ifdef HAS_CRYP_HW
bool test_keepass_decrypt_hw(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);

    set_log_level(KEEPASS, LOG_LEVEL_DEBUG);
    set_log_level(XML, LOG_LEVEL_DEBUG);
    // set_log_level(LG_CRYP,LOG_LEVEL_DEBUG);
    ASSERT_TRUE(keepass_reset(&KeePassItem));
    KeePassItem.cryp_num = CRYP_HW_NUM;
    ASSERT_TRUE(keepass_open(KEEPASS_KDBX_FILE, KEEPASS_KDBX_PASSWORD));
    ASSERT_EQ(7, KeePassItem.cur_entry);
    ASSERT_TRUE(keepass_open(KEEPASS_KDBX_FILE, KEEPASS_KDBX_PASSWORD));
    ASSERT_EQ(7, KeePassItem.cur_entry);

    set_log_level(XML, LOG_LEVEL_INFO);
    set_log_level(KEEPASS, LOG_LEVEL_INFO);
    set_log_level(LG_CRYP, LOG_LEVEL_INFO);

    LOG_INFO(TEST, "%s(): Ok", __FUNCTION__);
    return true;
}
#endif /*HAS_CRYP_HW*/

bool test_keepass_decrypt_sw(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEEPASS, LOG_LEVEL_DEBUG);
    set_log_level(XML, LOG_LEVEL_DEBUG);
    // set_log_level(LG_CRYP,LOG_LEVEL_DEBUG);
    KeePassItem.cryp_num = CRYP_SW_NUM;
    ASSERT_TRUE(keepass_reset(&KeePassItem));
    ASSERT_TRUE(keepass_open(KEEPASS_KDBX_FILE, KEEPASS_KDBX_PASSWORD));
    ASSERT_EQ(7, KeePassItem.cur_entry);
    ASSERT_TRUE(keepass_open(KEEPASS_KDBX_FILE, KEEPASS_KDBX_PASSWORD));
    ASSERT_EQ(7, KeePassItem.cur_entry);

    set_log_level(XML, LOG_LEVEL_INFO);
    set_log_level(KEEPASS, LOG_LEVEL_INFO);
    set_log_level(LG_CRYP, LOG_LEVEL_INFO);

    LOG_INFO(TEST, "%s(): Ok", __FUNCTION__);
    return true;
}

bool test_keepass_idiot_proof(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEEPASS, LOG_LEVEL_DEBUG);

    ASSERT_FALSE(keepass_open(NULL, NULL));
    ASSERT_FALSE(keepass_open("", ""));
    ASSERT_FALSE(keepass_open("db.kdbx", ""));
    ASSERT_FALSE(keepass_open("", "123"));
    return true;
}

bool test_keepass_test_pass_word(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(KEEPASS, LOG_LEVEL_DEBUG);

    ASSERT_FALSE(keepass_check_pass(KEEPASS_KDBX_FILE, "wrongPass"));
    ASSERT_TRUE(keepass_check_pass(KEEPASS_KDBX_FILE, KEEPASS_KDBX_PASSWORD));
    ASSERT_FALSE(keepass_check_pass(KEEPASS_KDBX_FILE, "wrongPass"));
    ASSERT_TRUE(keepass_check_pass(KEEPASS_KDBX_FILE, KEEPASS_KDBX_PASSWORD));
    ASSERT_FALSE(keepass_check_pass(KEEPASS_KDBX_FILE, "wrongPass"));

    ASSERT_FALSE(keepass_check_pass(KEEPASS_KDBX_FILE_1, "wrongPass"));
    ASSERT_TRUE(keepass_check_pass(KEEPASS_KDBX_FILE_1, KEEPASS_KDBX_PASSWORD_1));
    ASSERT_FALSE(keepass_check_pass(KEEPASS_KDBX_FILE_1, "wrongPass"));
    ASSERT_TRUE(keepass_check_pass(KEEPASS_KDBX_FILE_1, KEEPASS_KDBX_PASSWORD_1));
    ASSERT_FALSE(keepass_check_pass(KEEPASS_KDBX_FILE_1, "wrongPass"));

    set_log_level(KEEPASS, LOG_LEVEL_INFO);
    return true;
}
