#include "test_auto_version.h"

#include "auto_version.h"
#include "unit_test_check.h"

bool test_auto_version_types(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);
    bool res = true;

    return res;
}


bool test_auto_version_parse_line(void) {
    LOG_INFO(TEST, "%s", __FUNCTION__);

	log_level_get_set(LINE,LOG_LEVEL_DEBUG);
	log_level_get_set(AUTO_VERSION,LOG_LEVEL_DEBUG);

    AutoVersionHandle_t Item={0};

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 12\r\n"));
    ASSERT_EQ(12,Item.number_of_builds);

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 12\n\r"));
    ASSERT_EQ(12,Item.number_of_builds);

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 12\r"));
    ASSERT_EQ(12,Item.number_of_builds);

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 12\n"));
    ASSERT_EQ(12,Item.number_of_builds);

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 12"));
    ASSERT_EQ(12,Item.number_of_builds);

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 3"));
    ASSERT_EQ(3,Item.number_of_builds);

    ASSERT_TRUE( auto_version_proc_line(&Item,"#define SUCCESSFUL_BUILD_COUNTER 56 "));
    ASSERT_EQ(56,Item.number_of_builds);


	log_level_get_set(LINE,LOG_LEVEL_INFO);
	log_level_get_set(AUTO_VERSION,LOG_LEVEL_INFO);
    return true;
}

/*
https://www.exploringbinary.com/twos-complement-converter/
*/
