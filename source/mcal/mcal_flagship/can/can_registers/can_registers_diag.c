#include "can_registers_diag.h"

#include "can_custom_diag.h"
#include "can_mcal.h"
#include "can_message_buffer.h"
#include "can_misc.h"
#include "can_register_types.h"
#include "common_diag.h"
#include "data_utils.h"
#include "debugger.h"
#include "log.h"
#include "num_to_str.h"
#include "table_utils.h"
#include "writer_config.h"

static uint16_t DMALastWordToAddress(const uint8_t dmalw) {
    uint16_t address = dmalw * 4;
    return address;
}

#define CAN_FD_REGS                                                                                                    \
    {                                                                                                                  \
        .num = 40,                                                                                                     \
        .offset = 0xc00,                                                                                               \
        .name = "FDCTRL",                                                                                              \
        .access = ACCESS_READ_WRITE,                                                                                   \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .num = 41,                                                                                                 \
            .offset = 0xc04,                                                                                           \
            .name = "FDCBT",                                                                                           \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 42,                                                                                                 \
            .offset = 0xc08,                                                                                           \
            .name = "FDCRC",                                                                                           \
            .access = ACCESS_READ_ONLY,                                                                                \
            .valid = true,                                                                                             \
        },

#define CAN_FIFO_REGS                                                                                                  \
    {                                                                                                                  \
        .num = 43,                                                                                                     \
        .offset = 0xc0c,                                                                                               \
        .name = "ERFCR",                                                                                               \
        .access = ACCESS_READ_WRITE,                                                                                   \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .num = 44,                                                                                                 \
            .offset = 0xc10,                                                                                           \
            .name = "ERFIER",                                                                                          \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 45,                                                                                                 \
            .offset = 0xc14,                                                                                           \
            .name = "ERFSR",                                                                                           \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },

#define CAN_REGS_ERROR                                                                                                 \
    {                                                                                                                  \
        .num = 7,                                                                                                      \
        .offset = 0x1c,                                                                                                \
        .name = "ECR",                                                                                                 \
        .access = ACCESS_READ_ONLY,                                                                                    \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .num = 8,                                                                                                  \
            .offset = 0x20,                                                                                            \
            .name = "ESR1",                                                                                            \
            .access = ACCESS_WRITE_1_CLEAR,                                                                            \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 13,                                                                                                 \
            .offset = 0x38,                                                                                            \
            .name = "ESR2",                                                                                            \
            .access = ACCESS_READ_ONLY,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 19,                                                                                                 \
            .offset = 0xae4,                                                                                           \
            .name = "ERRIAR",                                                                                          \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 20,                                                                                                 \
            .offset = 0xae8,                                                                                           \
            .name = "ERRIDPR",                                                                                         \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 21,                                                                                                 \
            .offset = 0xaec,                                                                                           \
            .name = "ERRIPPR",                                                                                         \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 22,                                                                                                 \
            .offset = 0xaf0,                                                                                           \
            .name = "RERRAR",                                                                                          \
            .access = ACCESS_READ_ONLY,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 23,                                                                                                 \
            .offset = 0xaf4,                                                                                           \
            .name = "RERRDR",                                                                                          \
            .access = ACCESS_READ_ONLY,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 24,                                                                                                 \
            .offset = 0xaf8,                                                                                           \
            .name = "RERRSYNR",                                                                                        \
            .access = ACCESS_READ_ONLY,                                                                                \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 25,                                                                                                 \
            .offset = 0xafc,                                                                                           \
            .name = "ERRSR",                                                                                           \
            .access = ACCESS_WRITE_1_CLEAR,                                                                            \
            .valid = true,                                                                                             \
        },

#define CAN_REGS_CONTROL                                                                                               \
    {                                                                                                                  \
        .num = 2,                                                                                                      \
        .offset = 0x4,                                                                                                 \
        .name = "CTRL1",                                                                                               \
        .access = ACCESS_READ_WRITE,                                                                                   \
        .valid = true,                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .num = 12,                                                                                                 \
            .offset = 0x34,                                                                                            \
            .name = "CTRL2",                                                                                           \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 26,                                                                                                 \
            .offset = 0xb00,                                                                                           \
            .name = "CTRL1_PN",                                                                                        \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 27,                                                                                                 \
            .offset = 0xb04,                                                                                           \
            .name = "CTRL2_PN",                                                                                        \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .num = 46,                                                                                                 \
            .offset = 0x1A00,                                                                                          \
            .name = "GATE_CS",                                                                                         \
            .access = ACCESS_READ_WRITE,                                                                               \
            .valid = true,                                                                                             \
        },

/*
  see page 1386 Rgister Overview - FLEXCAN
  */
const Reg32_t CanReg[] = {{
                              .num = 1,
                              .offset = 0x0,
                              .name = "MCR",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 3,
                              .offset = 0x8,
                              .name = "TIMER",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 6,
                              .offset = 0x10,
                              .name = "RXMGMASK",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 5,
                              .offset = 0x14,
                              .name = "RX14MASK",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 6,
                              .offset = 0x18,
                              .name = "RX15MASK",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 10,
                              .offset = 0x28,
                              .name = "IMASK1",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 11,
                              .offset = 0x30,
                              .name = "IFLAG1",
                              .access = ACCESS_WRITE_1_CLEAR,
                              .valid = true,
                          },
                          {
                              .num = 14,
                              .offset = 0x44,
                              .name = "CRCR",
                              .access = ACCESS_READ_ONLY,
                              .valid = true,
                          },
                          {
                              .num = 15,
                              .offset = 0x48,
                              .name = "RXFGMASK",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 16,
                              .offset = 0x4c,
                              .name = "RXFIR",
                              .access = ACCESS_READ_ONLY,
                              .valid = true,
                          },
                          {
                              .num = 17,
                              .offset = 0x50,
                              .name = "CBT",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 18,
                              .offset = 0xae0,
                              .name = "MECR",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 28,
                              .offset = 0xb08,
                              .name = "WU_MTC",
                              .access = ACCESS_WRITE_1_CLEAR,
                              .valid = true,
                          },
                          {
                              .num = 29,
                              .offset = 0xb0c,
                              .name = "FLT_ID1",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 30,
                              .offset = 0xb10,
                              .name = "FLT_DLC",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 31,
                              .offset = 0xb14,
                              .name = "PL1_LO",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 32,
                              .offset = 0xb18,
                              .name = "PL1_HI",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 33,
                              .offset = 0xb1c,
                              .name = "FLT_ID2_IDMASK",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 34,
                              .offset = 0xb20,
                              .name = "PL2_PLMASK_LO",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 35,
                              .offset = 0xb24,
                              .name = "PL2_PLMASK_HI",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 36,
                              .offset = 0xbf0,
                              .name = "EPRS",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 37,
                              .offset = 0xbf4,
                              .name = "ENCBT",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 38,
                              .offset = 0xbf8,
                              .name = "EDCBT",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          {
                              .num = 39,
                              .offset = 0xbfc,
                              .name = "ETDC",
                              .access = ACCESS_READ_WRITE,
                              .valid = true,
                          },
                          CAN_REGS_ERROR CAN_FD_REGS CAN_FIFO_REGS CAN_REGS_CONTROL};

uint32_t can_reg_cnt(void) {
    uint32_t cnt = ARRAY_SIZE(CanReg);
    return cnt;
}

bool CanDiagRegMCR(const uint32_t dword) {
    bool res = false;
    CanRegMCR_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "MCR :0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "MAXMB:%u", Reg.MAXMB);
    LOG_INFO(CAN, "IDAM:%u", Reg.IDAM);
    LOG_INFO(CAN, "FDEN:%u", Reg.FDEN);
    LOG_INFO(CAN, "AEN:%u", Reg.AEN);
    LOG_INFO(CAN, "LPRIOEN:%u", Reg.LPRIO_EN);
    LOG_INFO(CAN, "PNET_EN:%u", Reg.PNET_EN);
    LOG_INFO(CAN, "DMA:%u", Reg.DMA);
    LOG_INFO(CAN, "IRMQ:%u", Reg.IRMQ);
    LOG_INFO(CAN, "SRXDIS:%u", Reg.SRXDIS);
    LOG_INFO(CAN, "LPMACK:%u", Reg.LPMACK);
    LOG_INFO(CAN, "WRNEN:%u", Reg.WRNEN);
    LOG_INFO(CAN, "SUPV:%u", Reg.SUPV);
    LOG_INFO(CAN, "FRZACK:%u", Reg.FRZACK);
    LOG_INFO(CAN, "SOFTRST:%u", Reg.SOFT_RST);
    LOG_INFO(CAN, "NOTRDY:%u", Reg.NOTRDY);
    LOG_INFO(CAN, "HALT:%u", Reg.HALT);
    LOG_INFO(CAN, "RFEN:%u", Reg.RFEN);
    LOG_INFO(CAN, "FRZ:%u", Reg.FRZ);
    LOG_INFO(CAN, "MDIS:%u", Reg.MDIS);

    res = true;
    return res;
}

bool CanDiagRegEPRS(const uint32_t dword) {
    bool res = false;
    CanRegEPRS_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "CTRL1:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "Extended Data Phase Prescaler Division Factor:%u", Reg.EDPRESDIV);
    LOG_INFO(CAN, "Extended Nominal Prescaler Division Factor:%u", Reg.ENPRESDIV);

    res = true;
    return res;
}

bool CanDiagRegCTRL1(const uint32_t dword) {
    bool res = false;
    CanRegCTRL1_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "CTRL1:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "PROPSEG:%u", Reg.PROPSEG);
    LOG_INFO(CAN, "LOM:%u", Reg.LOM);
    LOG_INFO(CAN, "LBUF:%u", Reg.LBUF);
    LOG_INFO(CAN, "TSYN:%u", Reg.TSYN);
    LOG_INFO(CAN, "BOFFREC:%u", Reg.BOFFREC);
    LOG_INFO(CAN, "SMP:%u", Reg.SMP);
    LOG_INFO(CAN, "RWRNMSK:%u", Reg.RWRNMSK);
    LOG_INFO(CAN, "TWRNMSK:%u", Reg.TWRNMSK);
    LOG_INFO(CAN, "LPB:%u", Reg.LPB);
    LOG_INFO(CAN, "CLKSRC:%u", Reg.CLKSRC);
    LOG_INFO(CAN, "ERRMSK:%u", Reg.ERRMSK);
    LOG_INFO(CAN, "BOFFMSK:%u", Reg.BOFFMSK);
    LOG_INFO(CAN, "PSEG2:%u", Reg.PSEG2);
    LOG_INFO(CAN, "PSEG1:%u", Reg.PSEG1);
    LOG_INFO(CAN, "RJW:%u", Reg.RJW);
    LOG_INFO(CAN, "PRESDIV:%u", Reg.PRESDIV);

    res = true;
    return res;
}

bool CanDiagRegIMASK1(const uint32_t dword) {
    bool res = false;
    CanRegIMASK1_t IMASK1;
    IMASK1.dword = dword;
    LOG_WARNING(CAN, "IMASK1:0x%08X=%s", IMASK1.dword, utoa_bin32(IMASK1.dword));
    res = true;
    return res;
}

bool CanDiagRegCTRL2(const uint32_t dword) {
    bool res = false;
    CanRegCTRL2_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "CTRL2:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "EDFLTDIS:%u", Reg.EDFLTDIS);
    LOG_INFO(CAN, "ISO_CAN_FD_EN:%u", Reg.ISO_CAN_FD_EN);
    LOG_INFO(CAN, "BTE:%u", Reg.BTE);
    LOG_INFO(CAN, "PREXCEN:%u", Reg.PREXCEN);
    LOG_INFO(CAN, "EACE:%u", Reg.EACE);
    LOG_INFO(CAN, "RRS:%u", Reg.RRS);
    LOG_INFO(CAN, "MRP:%u", Reg.MRP);
    LOG_INFO(CAN, "TASD:%u", Reg.TASD);
    LOG_INFO(CAN, "RFFN:%u", Reg.RFFN);
    LOG_INFO(CAN, "WRMFRZ:%u", Reg.WRMFRZ);
    LOG_INFO(CAN, "ECRWRE:%u", Reg.ECRWRE);
    LOG_INFO(CAN, "BOFF_DONE_MSK:%u", Reg.BOFF_DONE_MSK);
    LOG_INFO(CAN, "ERRM:%u", Reg.ERRM);

    res = true;
    return res;
}

bool CanDiagRegTIMER(const uint32_t dword) {
    bool res = false;
    CanRegTIMER_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "TIMER:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "TIMER:%u", Reg.TIMER);

    res = true;
    return res;
}

bool CanDiagRegENCBT(const uint32_t dword) {
    bool res = false;
    CanRegENCBT_t Reg = {0};
    Reg.dword = dword;
    LOG_WARNING(CAN, "ENCBT:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "NRJW:%u,NominalResynchronizationJumpWidth:%u", Reg.NRJW, Reg.NRJW + 1);
    LOG_INFO(CAN, "NTSEG1:%u,NTSEG1:%u", Reg.NTSEG1, Reg.NTSEG1 + 1);
    LOG_INFO(CAN, "NTSEG2:%u,NTSEG2:%u", Reg.NTSEG2, Reg.NTSEG2 + 1);
    res = true;
    return res;
}

bool CanDiagRegCBT(const uint32_t dword) {
    bool res = false;
    CanRegCBT_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "CBT:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "EPSEG2:%u,ExtendedPhaseSegment2:%u", Reg.EPSEG2, Reg.EPSEG2 + 1);
    LOG_INFO(CAN, "EPSEG1:%u,PhaseBufferSegment1:%u", Reg.EPSEG1, Reg.EPSEG1 + 1);
    LOG_INFO(CAN, "EPROPSEG:%u,PropagationSegmentTime:%u", Reg.EPROPSEG, Reg.EPROPSEG + 1);
    LOG_INFO(CAN, "ERJW:%u,ResyncJumpWidth:%u", Reg.ERJW, Reg.ERJW + 1);
    LOG_INFO(CAN, "EPRESDIV:%u->Dev:%u", Reg.EPRESDIV, Reg.EPRESDIV + 1);
    LOG_INFO(CAN, "BTF:%u", Reg.BTF);

    res = true;
    return res;
}

bool CanDiagRegFDCTRL(const uint32_t dword) {
    bool res = false;
    CanRegFDCTRL_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "FDCTRL:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "TDCVAL:%u", Reg.TDCVAL);
    LOG_INFO(CAN, "TDCOFF:%u", Reg.TDCOFF);
    LOG_INFO(CAN, "TDCFAIL:%u", Reg.TDCFAIL);
    LOG_INFO(CAN, "TDCEN:%u", Reg.TDCEN);
    LOG_INFO(CAN, "MBDSR0:%u->MBsize:%u byte", Reg.MBDSR0, can_message_buffer_to_size(Reg.MBDSR0));
    LOG_INFO(CAN, "FDRATE:%u", Reg.FDRATE);

    res = true;
    return res;
}

bool CanDiagRegECR(const uint32_t dword) {
    bool res = false;
    CanRegECR_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "ECR:0x%08X=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "TXERRCNT:%u", Reg.TXERRCNT);
    LOG_INFO(CAN, "RXERRCNT:%u", Reg.RXERRCNT);
    LOG_INFO(CAN, "TXERRCNT_FAST:%u", Reg.TXERRCNT_FAST);
    LOG_INFO(CAN, "RXERRCNT_FAST:%u", Reg.RXERRCNT_FAST);
    res = true;
    return res;
}

bool CanDiagRegESR1(const uint32_t dword) {
    bool res = false;
    CanRegESR1_t ESR1;
    ESR1.dword = dword;
    LOG_WARNING(CAN, "ESR1:0x%08X=%s", ESR1.dword, utoa_bin32(ESR1.dword));
    LOG_INFO(CAN, "ERRINT:%u", ESR1.ERRINT);
    LOG_INFO(CAN, "BOFFINT:%u", ESR1.BOFFINT);
    LOG_INFO(CAN, "RX:%u", ESR1.RX);
    LOG_INFO(CAN, "FLTCONF:%u", ESR1.FLTCONF);
    LOG_INFO(CAN, "TX:%u", ESR1.TX);
    LOG_INFO(CAN, "IDLE:%u", ESR1.IDLE);
    LOG_INFO(CAN, "RXWRN:%u", ESR1.RXWRN);
    LOG_INFO(CAN, "TXWRN:%u", ESR1.TXWRN);
    LOG_INFO(CAN, "STFERR:%u", ESR1.STFERR);
    LOG_INFO(CAN, "FRMERR:%u", ESR1.FRMERR);
    LOG_INFO(CAN, "CRCERR:%u", ESR1.CRCERR);
    LOG_INFO(CAN, "ACKERR:%u", ESR1.ACKERR);
    LOG_INFO(CAN, "BIT0ERR:%u", ESR1.BIT0ERR);
    LOG_INFO(CAN, "BIT1ERR:%u", ESR1.BIT1ERR);
    LOG_INFO(CAN, "RWRNINT:%u", ESR1.RWRNINT);
    LOG_INFO(CAN, "TWRNINT:%u", ESR1.TWRNINT);
    LOG_INFO(CAN, "SYNCH:%u", ESR1.SYNCH);
    LOG_INFO(CAN, "BOFFDONEINT:%u", ESR1.BOFFDONEINT);
    LOG_INFO(CAN, "ERRINT_FAST:%u", ESR1.ERRINT_FAST);
    LOG_INFO(CAN, "ERROVR:%u", ESR1.ERROVR);
    LOG_INFO(CAN, "STFERR_FAST:%u", ESR1.STFERR_FAST);
    LOG_INFO(CAN, "FRMERR_FAST:%u", ESR1.FRMERR_FAST);
    LOG_INFO(CAN, "CRCERR_FAST:%u", ESR1.CRCERR_FAST);
    LOG_INFO(CAN, "BIT0ERR_FAST:%u", ESR1.BIT0ERR_FAST);
    LOG_INFO(CAN, "BIT1ERR_FAST:%u", ESR1.BIT1ERR_FAST);

    res = true;
    return res;
}

bool CanDiagRegIFLAG1(const uint32_t dword) {
    bool res = false;
    CanRegIFLAG1_t Reg;
    Reg.dword = dword;
    LOG_WARNING(CAN, "IFLAG1:0x%x=%s", Reg.dword, utoa_bin32(Reg.dword));
    LOG_INFO(CAN, "BUF0I:%u", Reg.BUF0I);
    LOG_INFO(CAN, "BUF1I:%u", Reg.BUF1I);
    LOG_INFO(CAN, "BUF2I:%u", Reg.BUF2I);
    LOG_INFO(CAN, "BUF3I:%u", Reg.BUF3I);
    LOG_INFO(CAN, "BUF4I:%u", Reg.BUF4I);
    LOG_INFO(CAN, "BUF5I:%u", Reg.BUF5I);
    LOG_INFO(CAN, "BUF6I:%u", Reg.BUF6I);
    LOG_INFO(CAN, "BUF7I:%u", Reg.BUF7I);
    LOG_INFO(CAN, "BUF8I:%u", Reg.BUF8I);
    LOG_INFO(CAN, "BUF9I:%u", Reg.BUF9I);
    LOG_INFO(CAN, "BUF10I:%u", Reg.BUF10I);
    LOG_INFO(CAN, "BUF11I:%u", Reg.BUF11I);
    LOG_INFO(CAN, "BUF12I:%u", Reg.BUF12I);
    LOG_INFO(CAN, "BUF13I:%u", Reg.BUF13I);
    LOG_INFO(CAN, "BUF14I:%u", Reg.BUF14I);
    LOG_INFO(CAN, "BUF15I:%u", Reg.BUF15I);
    LOG_INFO(CAN, "BUF16I:%u", Reg.BUF16I);
    LOG_INFO(CAN, "BUF17I:%u", Reg.BUF17I);
    LOG_INFO(CAN, "BUF18I:%u", Reg.BUF18I);
    LOG_INFO(CAN, "BUF19I:%u", Reg.BUF19I);
    LOG_INFO(CAN, "BUF20I:%u", Reg.BUF20I);
    LOG_INFO(CAN, "BUF21I:%u", Reg.BUF21I);
    LOG_INFO(CAN, "BUF22I:%u", Reg.BUF22I);
    LOG_INFO(CAN, "BUF23I:%u", Reg.BUF23I);
    LOG_INFO(CAN, "BUF24I:%u", Reg.BUF24I);
    LOG_INFO(CAN, "BUF25I:%u", Reg.BUF25I);
    LOG_INFO(CAN, "BUF26I:%u", Reg.BUF26I);
    LOG_INFO(CAN, "BUF27I:%u", Reg.BUF27I);
    LOG_INFO(CAN, "BUF28I:%u", Reg.BUF28I);
    LOG_INFO(CAN, "BUF29I:%u", Reg.BUF29I);
    LOG_INFO(CAN, "BUF30I:%u", Reg.BUF30I);
    LOG_INFO(CAN, "BUF31I:%u", Reg.BUF31I);

    res = true;
    return res;
}

bool CanDiagRegERFCR(const uint32_t dword) {
    bool res = false;
    CanRegERFCR_t ERFCR;
    ERFCR.dword = dword;
    /*FLEXCAN_ERFCR (Enhanced Rx FIFO Control Register)*/
    LOG_WARNING(CAN, "ERFCR:0x%x=%s", ERFCR.dword, utoa_bin32(ERFCR.dword));
    LOG_INFO(CAN, "ERFWM:%u,Enhanced Rx FIFO %s", ERFCR.ERFWM, OnOffToStr(ERFCR.ERFWM));
    LOG_INFO(CAN, "NFE:%u,NumberOfEnhancedRxFIFOFilterElements", ERFCR.NFE);
    LOG_INFO(CAN, "NEXIF:%u,NumberOfExtendedIDFilterElements", ERFCR.NEXIF);
    LOG_INFO(CAN, "DMALW:%u=lastFIFOaddress:0x%x", ERFCR.DMALW, DMALastWordToAddress(ERFCR.DMALW));
    LOG_INFO(CAN, "ERFEN:%u,EnhancedRxFIFOWatermark", ERFCR.ERFEN);
    res = true;
    return res;
}

bool CanDiagRegERFSR(const uint32_t dword) {
    bool res = false;
    CanRegERFSR_t ERFSR;
    ERFSR.dword = dword;
    /* 58.8.50 FLEXCAN_ERFSR (Enhanced Rx FIFO Status Register) Offset: C14h */
    LOG_WARNING(CAN, "ERFSR:0x%x=%s", ERFSR.dword, utoa_bin32(ERFSR.dword));
    LOG_INFO(CAN, "ERFEL:%u", ERFSR.ERFEL);
    LOG_INFO(CAN, "ERFF:%u", ERFSR.ERFF);
    LOG_INFO(CAN, "ERFE:%u", ERFSR.ERFE);
    LOG_INFO(CAN, "ERFCLR:%u", ERFSR.ERFCLR);
    LOG_INFO(CAN, "ERFDA:%u", ERFSR.ERFDA);
    LOG_INFO(CAN, "ERFWMI:%u", ERFSR.ERFWMI);
    LOG_INFO(CAN, "ERFOVF:%u", ERFSR.ERFOVF);
    LOG_INFO(CAN, "ERFUFW:%u", ERFSR.ERFUFW);
    res = true;
    return res;
}

bool can_diag_low_level(uint8_t num, char* const keyword) {
    bool res = false;
    log_level_time_stamp(false);
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        LOG_WARNING(CAN, "CAN%u,0x%08X", num, Info->CANx);
        res = CanDiagRegEPRS(Info->CANx->EPRS);
        res = CanDiagRegIMASK1(Info->CANx->IMASK1);
        res = CanDiagRegMCR(Info->CANx->MCR);
        res = CanDiagRegESR1(Info->CANx->ESR1);
        res = CanDiagRegIFLAG1(Info->CANx->IFLAG1);
        res = CanDiagRegCTRL1(Info->CANx->CTRL1);
        res = CanDiagRegCTRL2(Info->CANx->CTRL2);
        res = CanDiagRegCBT(Info->CANx->CBT);
        res = CanDiagRegENCBT(Info->CANx->ENCBT);
        res = CanDiagRegFDCTRL(Info->CANx->FDCTRL);
        res = CanDiagRegECR(Info->CANx->ECR);
        res = CanDiagRegTIMER(Info->CANx->TIMER);
        res = CanDiagRegERFCR(Info->CANx->ERFCR);
        res = CanDiagRegERFSR(Info->CANx->ERFSR);
    }
    log_level_time_stamp(true);

    CanHandle_t* Node = CanGetNode(num);
    if(Node) {
        res = can_diag_handle(Node->pCanNode->hcan);
    }
    return res;
}

bool can_raw_reg_diag(uint8_t num) {
    bool res = false;
    const CanInfo_t* Info = CanGetInfo(num);
    if(Info) {
        LOG_INFO(CAN, "CAN%u,Base:0x%p", num, Info->CANx);
        uint32_t reg_cnt = can_reg_cnt();
        res = debug_raw_reg_diag(CAN, (uint32_t)Info->CANx, CanReg, reg_cnt);
    }
    return res;
}
