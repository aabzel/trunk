#include "test_dw1000.h"

#include <string.h>

#include "dw1000_diag.h"
#include "dw1000_drv.h"
#ifdef HAS_DW1000_OTP
#include "dw1000_otp.h"
#endif
#include "dw1000_registers.h"
#include "log.h"
#include "none_blocking_pause.h"
#include "unit_test_check.h"

bool test_dw1000_types(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    EXPECT_EQ((RX_BUFF_SIZE + 1), sizeof(Dw1000Instance.buff));
    EXPECT_EQ(1, sizeof(Dw1000Header_t));
    EXPECT_EQ(1, sizeof(RegFile_t));
    EXPECT_EQ(1, sizeof(PacSize_t));
    EXPECT_EQ(2, sizeof(Dw1000SubAddrHeader_t));
    EXPECT_EQ(2, sizeof(OffsetsLdeIf_t));
    EXPECT_EQ(2, sizeof(AgcTune1_t));
    EXPECT_EQ(4, sizeof(AgcTune2_t));
    EXPECT_EQ(2, sizeof(LdeCfg2_t)); /* LDE_CFG2 */
#ifdef HAS_DS_TWR
    EXPECT_EQ(16, sizeof(ResponderTiming_t));
#endif

    // EXPECT_EQ(41, sizeof(Dw1000UsrSfd_t));      /* USR_SFD */
    EXPECT_EQ(1, sizeof(Dw1000AonAddr_t));   /* AON_ADDR */
    EXPECT_EQ(1, sizeof(Dw1000AonCtrl_t));   /* AON_CTRL */
    EXPECT_EQ(1, sizeof(Dw1000FsPllTune_t)); /* FS_PLLTUNE */
    EXPECT_EQ(1, sizeof(TxPowerGain_t));     /*   */
    EXPECT_EQ(1, sizeof(Dw1000FsXtalt_t));   /* FS_XTALT */
    EXPECT_EQ(1, sizeof(Dw1000LdeCfg1_t));   /* LDE_CFG1 */
    EXPECT_EQ(1, sizeof(Dw1000OtpSf_t));     /* OTP_SF */
    EXPECT_EQ(1, sizeof(Dw1000PmscSnozt_t)); /* PMSC_SNOZT */
    EXPECT_EQ(1, sizeof(Dw1000RfRxCtrlh_t)); /* RF_RXCTRLH */
    EXPECT_EQ(1, sizeof(Dw1000TcPgCtrl_t));  /* TC_PG_CTRL */
    EXPECT_EQ(1, sizeof(Dw1000TcPgDelay_t)); /* TC_PGDELAY */
    EXPECT_EQ(1, sizeof(PulseRepRate_t));
    EXPECT_EQ(2, sizeof(Dw1000AgcCtrl1_t));   /* AGC_CTRL1 */
    EXPECT_EQ(2, sizeof(Dw1000AgcTune1_t));   /* AGC_TUNE1 */
    EXPECT_EQ(2, sizeof(Dw1000AgcTune3_t));   /* AGC_TUNE3 */
    EXPECT_EQ(2, sizeof(Dw1000AonCfg1_t));    /* AON_CFG1 */
    EXPECT_EQ(2, sizeof(Dw1000AonWcfg_t));    /* AON_WCFG */
    EXPECT_EQ(2, sizeof(Dw1000DiagTmc_t));    /* DIAG_TMC */
    EXPECT_EQ(2, sizeof(Dw1000DrxPreToc_t));  /* DRX_PRETOC */
    EXPECT_EQ(2, sizeof(Dw1000DrxSfdtoc_t));  /* DRX_SFDTOC */
    EXPECT_EQ(2, sizeof(Dw1000DrxTune0b_t));  /* DRX_TUNE0b */
    EXPECT_EQ(2, sizeof(Dw1000DrxTune1a_t));  /* DRX_TUNE1a */
    EXPECT_EQ(2, sizeof(Dw1000DrxTune1b_t));  /* DRX_TUNE1b */
    EXPECT_EQ(2, sizeof(Dw1000DrxTune4h_t));  /* DRX_TUNE4H */
    EXPECT_EQ(2, sizeof(Dw1000EvcFce_t));     /* EVC_FCE */
    EXPECT_EQ(2, sizeof(Dw1000EvcFcg_t));     /* EVC_FCG */
    EXPECT_EQ(2, sizeof(Dw1000EvcFfr_t));     /* EVC_FFR */
    EXPECT_EQ(2, sizeof(Dw1000EvcFwto_t));    /* EVC_FWTO */
    EXPECT_EQ(2, sizeof(Dw1000EvcHpw_t));     /* EVC_HPW */
    EXPECT_EQ(2, sizeof(Dw1000EvcOvr_t));     /* EVC_OVR */
    EXPECT_EQ(2, sizeof(Dw1000EvcPhe_t));     /* EVC_PHE */
    EXPECT_EQ(2, sizeof(Dw1000EvcPto_t));     /* EVC_PTO */
    EXPECT_EQ(2, sizeof(Dw1000EvcRse_t));     /* EVC_RSE */
    EXPECT_EQ(2, sizeof(Dw1000EvcSto_t));     /* EVC_STO */
    EXPECT_EQ(2, sizeof(Dw1000EvcTpw_t));     /* EVC_TPW */
    EXPECT_EQ(2, sizeof(Dw1000EvcTxfs_t));    /* EVC_TXFS */
    EXPECT_EQ(2, sizeof(Dw1000LdeCfg2_t));    /* LDE_CFG2 */
    EXPECT_EQ(2, sizeof(Dw1000LdePpampl_t));  /* LDE_PPAMPL */
    EXPECT_EQ(2, sizeof(Dw1000LdeRepc_t));    /* LDE_REPC */
    EXPECT_EQ(2, sizeof(Dw1000LdeRxAntD_t));  /* LDE_RXANTD */
    EXPECT_EQ(2, sizeof(Dw1000LdeThresh_t));  /* LDE_THRESH */
    EXPECT_EQ(2, sizeof(Dw1000OtpAddr_t));    /* OTP_ADDR */
    EXPECT_EQ(2, sizeof(Dw1000OtpCtrl_t));    /* OTP_CTRL */
    EXPECT_EQ(2, sizeof(Dw1000OtpStat_t));    /* OTP_STAT */
    EXPECT_EQ(2, sizeof(Dw1000TcPgStatus_t)); /* TC_PG_STATUS */
    EXPECT_EQ(2, sizeof(Dw1000TcSarc_t));     /* TC_SARC */
    EXPECT_EQ(2, sizeof(Dw1000TcSarw_t));     /* TC_SARW */
    EXPECT_EQ(3, sizeof(Dw1000AgcStat1_t));   /* AGC_STAT1 */
    EXPECT_EQ(3, sizeof(Dw1000ExtendedSubAddrHeader_t));
    EXPECT_EQ(3, sizeof(Dw1000RfTxCtrl_t)); /* RF_TXCTRL */
    EXPECT_EQ(3, sizeof(Dw1000RfTxCtrl_t)); /*7.2.41.5 Sub-Register 0x28:0C– RF_TXCTRL*/
    EXPECT_EQ(3, sizeof(Dw1000TcSarl_t));   /* TC_SARL */
    EXPECT_EQ(4, sizeof(Dw1000AckResp_t));  /* ACK_RESP_T */
    EXPECT_EQ(4, sizeof(Dw1000AgcTune2_t)); /* AGC_TUNE2 */
    EXPECT_EQ(4, sizeof(Dw1000AonCfg0_t));  /* AON_CFG0 */
    EXPECT_EQ(4, sizeof(Dw1000ChanCtrl_t)); /* CHAN_CTRL */
    EXPECT_EQ(4, sizeof(Dw1000DevId_t));
    EXPECT_EQ(4, sizeof(Dw1000DrxTune2_t));     /* DRX_TUNE2 */
    EXPECT_EQ(4, sizeof(Dw1000EcCtrl_t));       /* EC_CTRL */
    EXPECT_EQ(4, sizeof(Dw1000EcGold_t));       /* EC_GOLP */
    EXPECT_EQ(4, sizeof(Dw1000EcRxtc_t));       /* EC_RXTC */
    EXPECT_EQ(4, sizeof(Dw1000EvcCtrl_t));      /* EVC_CTRL */
    EXPECT_EQ(4, sizeof(Dw1000FsPllCfg_t));     /* FS_PLLCFG */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioDir_t));   /* GPIO_DIR */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioDout_t));  /* GPIO_DOUT */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioIbes_t));  /* GPIO_IBES */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioIclr_t));  /* GPIO_ICLR */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioIdbe_t));  /* GPIO_IDBE */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioImode_t)); /* GPIO_IMODE */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioIrqe_t));  /* GPIO_IRQE */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioIsen_t));  /* GPIO_ISEN */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioMode_t));  /* GPIO_MODE */
    EXPECT_EQ(4, sizeof(Dw1000RegGpioRaw_t));   /* GPIO_RAW */
    EXPECT_EQ(4, sizeof(Dw1000MTxPower_t));     /* 7.2.31.3 Manual Transmit Power Control */
    EXPECT_EQ(4, sizeof(Dw1000OtpRdat_t));      /* OTP_RDAT */
    EXPECT_EQ(4, sizeof(Dw1000OtpWdat_t));      /* OTP_WDAT */
    EXPECT_EQ(4, sizeof(Dw1000PanId_t));        /* PANADR */
    EXPECT_EQ(4, sizeof(Dw1000PmscCtrl0_t));    /* PMSC_CTRL0 */
    EXPECT_EQ(4, sizeof(Dw1000PmscCtrl1_t));    /* PMSC_CTRL1 */
    EXPECT_EQ(4, sizeof(Dw1000PmscLedc_t));     /* PMSC_LEDC */
    EXPECT_EQ(4, sizeof(Dw1000RfConf_t));       /* RF_CONF */
    EXPECT_EQ(4, sizeof(Dw1000RfStatus_t));     /* RF_STATUS */
    EXPECT_EQ(4, sizeof(Dw1000RxFrameInfo_t));  /* RX_FINFO */
    EXPECT_EQ(4, sizeof(Dw1000RxSniff_t));      /* RX_SNIFF */
    EXPECT_EQ(4, sizeof(Dw1000RxTtcki_t));      /* RX_TTCKI */
    EXPECT_EQ(4, sizeof(Dw1000STxPower_t));     /* 7.2.31.2 Smart Transmit Power Control */
    EXPECT_EQ(4, sizeof(Dw1000SysCfg_t));       /* SYS_CFG */
    EXPECT_EQ(4, sizeof(Dw1000SysCtrl_t));      /* SYS_CTRL */
    EXPECT_EQ(4, sizeof(Dw1000RegSysMask_t));   /* SYS_MASK */
    EXPECT_EQ(4, sizeof(Dw1000SysState_t));     /* SYS_STATE */
    EXPECT_EQ(4, sizeof(Dw1000TxPower_t));      /* TX_POWER */
    EXPECT_EQ(5, sizeof(Dw1000DxTime_t));       /* DX_TIME */
    EXPECT_EQ(5, sizeof(Dw1000RxTtcko_t));      /* RX_TTCKO */
    EXPECT_EQ(5, sizeof(Dw1000SysStatus_t));    /* SYS_STATUS */
    EXPECT_EQ(5, sizeof(Dw1000SysTime_t));      /* SYS_TIME */
    EXPECT_EQ(5, sizeof(Dw1000TxFctrl_t));      /* TX_FCTRL */
    EXPECT_EQ(8, sizeof(Dw1000RxFqual_t));      /* RX_FQUAL */
    EXPECT_EQ(8, sizeof(Dw1000Eui_t));          /* EUI */
    EXPECT_EQ(10, sizeof(Dw1000TxTime_t));      /* TX_TIME */
    EXPECT_EQ(14, sizeof(Dw1000RxTimeStamp_t)); /* RX_TIME */
                                                /*   EXPECT_EQ(2, sizeof(Dw1000TxAntd_t));        TX_ANTD */
                                                /*    EXPECT_EQ(2, sizeof(Dw1000RxFwto_t));        RX_FWTO */
                                                /*    EXPECT_EQ(3, sizeof(Dw1000DrxCarInt_t));     DRX_CAR_INT */

    return res;
}

bool test_dw1000_hash_tables(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(DW1000, LOG_LEVEL_DEBUG);

    EXPECT_EQ(BIT_RATE_110_KBPS, BitRate2Dw1000BitRate(110000));
    EXPECT_EQ(BIT_RATE_850_KBPS, BitRate2Dw1000BitRate(850000));
    EXPECT_EQ(BIT_RATE_6800_KBPS, BitRate2Dw1000BitRate(6800000));

    EXPECT_EQ(7, channel_info_get_cnt());

    EXPECT_EQ(4096, dw1000_preamble_len_calc(BIT_RATE_110_KBPS));
    EXPECT_EQ(512, dw1000_preamble_len_calc(BIT_RATE_850_KBPS));
    EXPECT_EQ(128, dw1000_preamble_len_calc(BIT_RATE_6800_KBPS));

    EXPECT_EQ(110000, BitRateCode2BitPerSec(BIT_RATE_110_KBPS));
    EXPECT_EQ(850000, BitRateCode2BitPerSec(BIT_RATE_850_KBPS));
    EXPECT_EQ(6800000, BitRateCode2BitPerSec(BIT_RATE_6800_KBPS));

    EXPECT_EQ(0x00005C40, Dw1000Cha2RfTxCtrlCode(CHANNEL_1));
    EXPECT_EQ(0x00045CA0, Dw1000Cha2RfTxCtrlCode(CHANNEL_2));
    EXPECT_EQ(0x00086CC0, Dw1000Cha2RfTxCtrlCode(CHANNEL_3));
    EXPECT_EQ(0x00045C80, Dw1000Cha2RfTxCtrlCode(CHANNEL_4));
    EXPECT_EQ(0x001E3FE3, Dw1000Cha2RfTxCtrlCode(CHANNEL_5));
    EXPECT_EQ(0x001E7DE0, Dw1000Cha2RfTxCtrlCode(CHANNEL_7));

    EXPECT_EQ(CHANNEL_1, Dw1000Code2Channel(0x00005C40));
    EXPECT_EQ(CHANNEL_2, Dw1000Code2Channel(0x00045CA0));
    EXPECT_EQ(CHANNEL_3, Dw1000Code2Channel(0x00086CC0));
    EXPECT_EQ(CHANNEL_4, Dw1000Code2Channel(0x00045C80));
    EXPECT_EQ(CHANNEL_5, Dw1000Code2Channel(0x001E3FE3));
    EXPECT_EQ(CHANNEL_7, Dw1000Code2Channel(0x001E7DE0));

    EXPECT_EQ(CHANNEL_1, Dw1000Code2Channel(Dw1000Cha2RfTxCtrlCode(CHANNEL_1)));
    EXPECT_EQ(CHANNEL_2, Dw1000Code2Channel(Dw1000Cha2RfTxCtrlCode(CHANNEL_2)));
    EXPECT_EQ(CHANNEL_3, Dw1000Code2Channel(Dw1000Cha2RfTxCtrlCode(CHANNEL_3)));
    EXPECT_EQ(CHANNEL_4, Dw1000Code2Channel(Dw1000Cha2RfTxCtrlCode(CHANNEL_4)));
    EXPECT_EQ(CHANNEL_5, Dw1000Code2Channel(Dw1000Cha2RfTxCtrlCode(CHANNEL_5)));
    EXPECT_EQ(CHANNEL_7, Dw1000Code2Channel(Dw1000Cha2RfTxCtrlCode(CHANNEL_7)));

    EXPECT_EQ(2, Dw1000Set2Pcode(PULSE_REP_RATE_REP_16MHZ, CHANNEL_1));
    EXPECT_EQ(4, Dw1000Set2Pcode(PULSE_REP_RATE_REP_16MHZ, CHANNEL_2));
    EXPECT_EQ(6, Dw1000Set2Pcode(PULSE_REP_RATE_REP_16MHZ, CHANNEL_3));
    EXPECT_EQ(8, Dw1000Set2Pcode(PULSE_REP_RATE_REP_16MHZ, CHANNEL_4));
    EXPECT_EQ(4, Dw1000Set2Pcode(PULSE_REP_RATE_REP_16MHZ, CHANNEL_5));
    EXPECT_EQ(8, Dw1000Set2Pcode(PULSE_REP_RATE_REP_16MHZ, CHANNEL_7));

    EXPECT_EQ(10, Dw1000Set2Pcode(PULSE_REP_RATE_REP_64MHZ, CHANNEL_1));
    EXPECT_EQ(10, Dw1000Set2Pcode(PULSE_REP_RATE_REP_64MHZ, CHANNEL_2));
    EXPECT_EQ(10, Dw1000Set2Pcode(PULSE_REP_RATE_REP_64MHZ, CHANNEL_3));
    EXPECT_EQ(18, Dw1000Set2Pcode(PULSE_REP_RATE_REP_64MHZ, CHANNEL_4));
    EXPECT_EQ(10, Dw1000Set2Pcode(PULSE_REP_RATE_REP_64MHZ, CHANNEL_5));
    EXPECT_EQ(18, Dw1000Set2Pcode(PULSE_REP_RATE_REP_64MHZ, CHANNEL_7));

    /*Table 40: Sub-Register 0x2A:0B – TC_PGDELAY recommended values*/
    EXPECT_EQ(0xC9, Dw1000Channel2TcPgDelayCode(CHANNEL_1));
    EXPECT_EQ(0xC2, Dw1000Channel2TcPgDelayCode(CHANNEL_2));
    EXPECT_EQ(0xC5, Dw1000Channel2TcPgDelayCode(CHANNEL_3));
    EXPECT_EQ(0x95, Dw1000Channel2TcPgDelayCode(CHANNEL_4));
    EXPECT_EQ(0xB5, Dw1000Channel2TcPgDelayCode(CHANNEL_5));
    EXPECT_EQ(0x93, Dw1000Channel2TcPgDelayCode(CHANNEL_7));

    EXPECT_EQ(CHANNEL_1, Dw1000TcPgDelay2Channel(0xC9));
    EXPECT_EQ(CHANNEL_2, Dw1000TcPgDelay2Channel(0xC2));
    EXPECT_EQ(CHANNEL_3, Dw1000TcPgDelay2Channel(0xC5));
    EXPECT_EQ(CHANNEL_4, Dw1000TcPgDelay2Channel(0x95));
    EXPECT_EQ(CHANNEL_5, Dw1000TcPgDelay2Channel(0xB5));
    EXPECT_EQ(CHANNEL_7, Dw1000TcPgDelay2Channel(0x93));

    EXPECT_EQ(0x09000407, Dw1000Channel2FsPllCfgCode(CHANNEL_1));
    EXPECT_EQ(0x08400508, Dw1000Channel2FsPllCfgCode(CHANNEL_2));
    EXPECT_EQ(0x08401009, Dw1000Channel2FsPllCfgCode(CHANNEL_3));
    EXPECT_EQ(0x08400508, Dw1000Channel2FsPllCfgCode(CHANNEL_4));
    EXPECT_EQ(0x0800041D, Dw1000Channel2FsPllCfgCode(CHANNEL_5));
    EXPECT_EQ(0x0800041D, Dw1000Channel2FsPllCfgCode(CHANNEL_7));

    EXPECT_EQ(DRX_TUNE4H_PRE_64, PreambleLen2DrxTune4h(64));
    EXPECT_EQ(DRX_TUNE4H_PRE_128_PLUS, PreambleLen2DrxTune4h(128));
    EXPECT_EQ(DRX_TUNE4H_PRE_128_PLUS, PreambleLen2DrxTune4h(1024));

    EXPECT_EQ(2867, PreambleCode2LdeRepc(BIT_RATE_110_KBPS, 1));
    EXPECT_EQ(1802, PreambleCode2LdeRepc(BIT_RATE_110_KBPS, 24));
    EXPECT_EQ(0x5998, PreambleCode2LdeRepc(BIT_RATE_850_KBPS, 1));
    EXPECT_EQ(0x3850, PreambleCode2LdeRepc(BIT_RATE_850_KBPS, 24));
    EXPECT_EQ(0x5998, PreambleCode2LdeRepc(BIT_RATE_6800_KBPS, 1));
    EXPECT_EQ(0x3850, PreambleCode2LdeRepc(BIT_RATE_6800_KBPS, 24));

    EXPECT_EQ(PAC_SIZE_16, PreambleLength2PacSize(256));
    EXPECT_EQ(PAC_SIZE_16, PreambleLength2PacSize(512));
    EXPECT_EQ(PAC_SIZE_8, PreambleLength2PacSize(64));
    EXPECT_EQ(PAC_SIZE_8, PreambleLength2PacSize(128));
    EXPECT_EQ(PAC_SIZE_32, PreambleLength2PacSize(1024));
    EXPECT_EQ(PAC_SIZE_64, PreambleLength2PacSize(1536));
    EXPECT_EQ(PAC_SIZE_64, PreambleLength2PacSize(2048));
    EXPECT_EQ(PAC_SIZE_64, PreambleLength2PacSize(4096));

    set_log_level(DW1000, LOG_LEVEL_INFO);

    EXPECT_EQ(0x07F00, Pack16BitTo15bit(0x007F));
    EXPECT_EQ(0x07F01, Pack16BitTo15bit(0x00FF));

    return res;
}

bool test_dw1000_tx(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG);

    char buff[6] = "Hello";
    ASSERT_TRUE(dw1000_transmit((uint8_t*)buff, strlen(buff)));
    ASSERT_TRUE(wait_in_loop_ms(700));

    set_log_level(DW1000, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return true;
}

bool test_dw1000_connected(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    bool res = true;
    set_log_level(DW1000, LOG_LEVEL_DEBUG);
    set_log_level(SPI, LOG_LEVEL_DEBUG);

    EXPECT_TRUE(dw1000_is_connected());

    set_log_level(DW1000, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return res;
}

#ifdef HAS_DW1000_OTP
static bool test_dw1000_otp_read_one(uint16_t addr) {
    LOG_INFO(TEST, "%s(): OtpAddr:0x%x", __FUNCTION__, addr);
    uint32_t val = 0;
    val = dw1000_otp_read(addr);
    LOG_INFO(TEST, "Val: 0x%x", val);
    ASSERT_NE(0, val);
    return true;
}
#endif

#ifdef HAS_DW1000_OTP
static bool test_dw1000_otp_test_one(uint16_t addr, uint32_t des_word) {
    LOG_INFO(TEST, "%s(): Addr:0x%04x DesVal 0x%08x", __FUNCTION__, addr, des_word);
    uint32_t real_val = 0;
    ASSERT_TRUE(dw1000_otp_write(addr, des_word));
    wait_ms(100);
    real_val = dw1000_otp_read(addr);
    ASSERT_EQ(des_word, real_val);
    return true;
}
#endif

#ifdef HAS_DW1000_OTP
static bool test_dw1000_otp_write_one(uint16_t addr) {
    LOG_INFO(TEST, "%s(): addr:0x%x", __FUNCTION__, addr);
    uint32_t orig_val = 0;
    orig_val = dw1000_otp_read(addr);
    LOG_INFO(TEST, "Val: 0x%x", orig_val);

    ASSERT_TRUE(test_dw1000_otp_test_one(addr, 0xAAAAAAAA));
    ASSERT_TRUE(test_dw1000_otp_test_one(addr, 0x55555555));

    ASSERT_TRUE(dw1000_otp_write(addr, orig_val));
    return true;
}
#endif

#ifdef HAS_DW1000_OTP
bool test_dw1000_otp_read(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000, LOG_LEVEL_DEBUG);
    bool res = true;
    EXPECT_TRUE(test_dw1000_otp_read_one(0x006));
    EXPECT_TRUE(test_dw1000_otp_read_one(0x007));
    EXPECT_TRUE(test_dw1000_otp_read_one(0x008));
    // EXPECT_TRUE(test_dw1000_otp_read_one(0x010));
    // EXPECT_TRUE(test_dw1000_otp_read_one(0x01C));
    EXPECT_TRUE(test_dw1000_otp_read_one(0x01E));
    set_log_level(DW1000, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return res;
}
#endif

bool test_dw1000_otp_write(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000, LOG_LEVEL_DEBUG);
    bool res = true;
#ifdef HAS_DW1000_OTP
    EXPECT_TRUE(test_dw1000_otp_write_one(0x002));
    // EXPECT_TRUE(test_dw1000_otp_write_one(0x00C));
    // EXPECT_TRUE(test_dw1000_otp_write_one(0x00F));
    // EXPECT_TRUE(test_dw1000_otp_write_one(0x01F));
#endif
    set_log_level(DW1000, LOG_LEVEL_INFO);
    set_log_level(SPI, LOG_LEVEL_INFO);
    return res;
}

static bool test_dw1000_rx_ant_delay_one(uint16_t rx_ant_delay_des) {
    LOG_INFO(TEST, "%s(): RxAntDelayDes:0x%x", __FUNCTION__, rx_ant_delay_des);
    uint16_t rx_ant_delay_read = 0;

    ASSERT_TRUE(dw1000_write_rx_ant_delay(rx_ant_delay_des));
    wait_ms(100);
    rx_ant_delay_read = dw1000_read_rx_ant_delay();

    ASSERT_EQ(rx_ant_delay_des, rx_ant_delay_read);

    return true;
}

bool test_dw1000_rx_ant_delay(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t orig_rx_ant_delay = 0;

    orig_rx_ant_delay = dw1000_read_rx_ant_delay();

    EXPECT_TRUE(test_dw1000_rx_ant_delay_one(0));
    EXPECT_TRUE(test_dw1000_rx_ant_delay_one(10));
    EXPECT_TRUE(test_dw1000_rx_ant_delay_one(0x5555));
    EXPECT_TRUE(test_dw1000_rx_ant_delay_one(0xAAAA));

    ASSERT_TRUE(dw1000_write_rx_ant_delay(orig_rx_ant_delay));

    set_log_level(DW1000, LOG_LEVEL_INFO);
    return res;
}

static bool test_dw1000_tx_ant_delay_one(uint16_t tx_ant_delay_des) {
    LOG_INFO(TEST, "%s(): TxAntDelayDes:0x%x", __FUNCTION__, tx_ant_delay_des);
    uint16_t tx_ant_delay_read = 0;

    ASSERT_TRUE(dw1000_write_tx_ant_delay(tx_ant_delay_des));
    wait_ms(100);
    tx_ant_delay_read = dw1000_read_tx_ant_delay();

    ASSERT_EQ(tx_ant_delay_des, tx_ant_delay_read);

    return true;
}

bool test_dw1000_tx_ant_delay(void) {
    LOG_INFO(TEST, "%s():", __FUNCTION__);
    set_log_level(DW1000, LOG_LEVEL_DEBUG);
    bool res = true;
    uint32_t orig_tx_ant_delay = 0;

    orig_tx_ant_delay = dw1000_read_tx_ant_delay();

    EXPECT_TRUE(test_dw1000_tx_ant_delay_one(0));
    EXPECT_TRUE(test_dw1000_tx_ant_delay_one(10));

    ASSERT_TRUE(dw1000_write_tx_ant_delay(orig_tx_ant_delay));

    set_log_level(DW1000, LOG_LEVEL_INFO);
    return res;
}
