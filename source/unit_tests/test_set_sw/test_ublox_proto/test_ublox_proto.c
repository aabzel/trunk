#include "test_ublox_proto.h"

#ifdef X86_64
#include "log.h"
#endif

#include "array.h"
#include "ubx_diag.h"
#include "ubx_protocol.h"
#include "ubx_types.h"
#include "ubx_constants.h"
#include "unit_test_check.h"

const uint8_t ubx_baud_115200_message[28] = {
  0xB5, 0x62,
  0x06, 0x00,
  0x14, 0x00,
  0x01, 0x00, 0x00, 0x00, 0xD0,
  0x08, 0x00, 0x00, 0x00, 0xC2,
  0x01, 0x00, 0x03, 0x00, 0x03,
  0x00, 0x00, 0x00, 0x00, 0x00,
  0xBC, 0x5E};

  
/*tsr ublox_proto+*/
bool test_ublox_proto_set_baud  (void) {
   uint8_t i=0;
#ifdef X86_64
   printf("\n%s()",__FUNCTION__);
#endif
   ubx_reset_rx();
   UbloxProtocol.rx_pkt_cnt=0;
   for(i=0; i<sizeof(ubx_baud_115200_message); i++) {
       ubx_proc_byte(ubx_baud_115200_message[i]);
   }

   EXPECT_EQ(1, UbloxProtocol.rx_pkt_cnt);

   return true;
}


bool test_ublox_proto_err_len(void) {
   uint8_t i=0;
#ifdef X86_64
   printf("\n%s()",__FUNCTION__);
#endif

   uint8_t ubx_error_len_message[UBX_RX_FRAME_SIZE*2];
   array_rand(ubx_error_len_message,sizeof(ubx_error_len_message));
   ubx_error_len_message[0]=UBX_SYN_0;
   ubx_error_len_message[1]=UBX_SYN_1;
   ubx_error_len_message[4]=0xff;
   ubx_error_len_message[5]=0xFF;
   ubx_reset_rx();
   UbloxProtocol.rx_pkt_cnt=0;
   for(i=0; i<sizeof(ubx_error_len_message); i++) {
       ubx_proc_byte(ubx_error_len_message[i]);
   }

   EXPECT_EQ(0, UbloxProtocol.rx_pkt_cnt);

   return true;
}
  
bool test_ublox_proto_types(void) {
   LOG_INFO(SYS,"%s()",__FUNCTION__);
   EXPECT_STREQ("CLA:0x01=NAV ID:0x3b=SVIN",ClassId2str(UBX_CLA_NAV,0x3b));
   EXPECT_EQ(40, sizeof(NavSvin_t));
   EXPECT_EQ(3, sizeof(CfgMsg_t));
   EXPECT_EQ(4, sizeof(ConfigurationKeyID_t));
   EXPECT_EQ(13, sizeof(UbxCfgCfg_t));
   EXPECT_EQ(40, sizeof(UbxCfgTmode3Data_t));
   EXPECT_EQ(9, sizeof(SecUniqId_t));
   EXPECT_EQ(28, sizeof(NavPosllh_t));
   EXPECT_EQ(36, sizeof(NavHpPosllh_t));
   EXPECT_EQ(20, sizeof(NavTimeUtc_t));
   EXPECT_EQ(1, sizeof(TimeUtcValidityFlags_t));
   EXPECT_EQ(36, sizeof(NavVelNed_t));
   EXPECT_EQ(92, sizeof(NavPvt_t));
   EXPECT_EQ(1, sizeof(UbxReceiverMode_t));
   EXPECT_EQ(4, sizeof(UbxUartMode_t));
   EXPECT_EQ(20, sizeof(CfgPrt_t));
   EXPECT_EQ(20, sizeof(MgaIniPosXyz_t));

   return true;
}
