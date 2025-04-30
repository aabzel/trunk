#include "test_rds_proto.h"

#include <assert.h>

#include "log.h"
#include "rds_protocol.h"
#include "unit_test_check.h"

bool test_rds_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    ASSERT_EQ(8, sizeof(RadioText2A_t));
    ASSERT_EQ(8, sizeof(RadioText2B_t));
    ASSERT_EQ(8, sizeof(ClockTimeDate_t));
    ASSERT_EQ(2, sizeof(BlockA_t));
    ASSERT_EQ(2, sizeof(BlockB_t));
    ASSERT_EQ(2, sizeof(BlockC_t));
    ASSERT_EQ(2, sizeof(BlockD_t));
    ASSERT_EQ(2, sizeof(ProgramId_t));
    ASSERT_EQ(8, sizeof(BasicTuning0A_t));
    ASSERT_EQ(8, sizeof(ProgTyteNameA_t));
    ASSERT_EQ(8, sizeof(ProgTyteNameB_t));
    ASSERT_EQ(8, sizeof(BasicTuning0B_t));
    ASSERT_EQ(8, sizeof(RdsMessage_t));

    _Static_assert (8==sizeof(ProgTyteNameB_t), "Err");
    _Static_assert(8==sizeof(BasicTuning0A_t), "Err");
    _Static_assert(8==sizeof(BasicTuning0A_t), "Err");
    _Static_assert(8==sizeof(BasicTuning0B_t), "Err");
    _Static_assert(8==sizeof(RdsMessage_t), "Err");
    return true;
}

bool test_rds_prog_type_name0(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
	set_log_level(RDS,LOG_LEVEL_DEBUG);
	uint16_t words[4]={0x7704, 0xa360, 0x5265, 0x7472};
	ASSERT_TRUE( rds_proc_message(words));
	ASSERT_EQ(0,RdsProtocol.Message.ProgTyteNameA.segment)
	ASSERT_EQ('R',RdsProtocol.Message.ProgTyteNameA.ch1);
	ASSERT_EQ('e',RdsProtocol.Message.ProgTyteNameA.ch2);
	ASSERT_EQ('t',RdsProtocol.Message.ProgTyteNameA.ch3);
	ASSERT_EQ('r',RdsProtocol.Message.ProgTyteNameA.ch4);
	ASSERT_EQ_MEM("Retr",RdsProtocol.ProgTypeName,4);
	set_log_level(RDS,LOG_LEVEL_INFO);
	return true;
}

bool test_rds_prog_type_name1(void){
    LOG_INFO(TEST, "%s():", __FUNCTION__);
	uint16_t words[4]={0x7704, 0xa361, 0x6f20, 0x2020};
	set_log_level(RDS,LOG_LEVEL_DEBUG);
	ASSERT_TRUE( rds_proc_message(words));

	ASSERT_EQ(1,RdsProtocol.Message.ProgTyteNameA.segment)
	ASSERT_EQ('o',RdsProtocol.Message.ProgTyteNameA.ch1);
	ASSERT_EQ(' ',RdsProtocol.Message.ProgTyteNameA.ch2);
	ASSERT_EQ(' ',RdsProtocol.Message.ProgTyteNameA.ch3);
	ASSERT_EQ(' ',RdsProtocol.Message.ProgTyteNameA.ch4);
	ASSERT_EQ_MEM("Retro",RdsProtocol.ProgTypeName,5);
	set_log_level(RDS,LOG_LEVEL_INFO);
	return true;
}

