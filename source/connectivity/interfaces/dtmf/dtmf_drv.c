#include "dtmf_drv.h"

#include <float.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>

#include "array.h"
#include "code_generator.h"
#include "data_types.h"
#include "dtmf_diag.h"
#include "float_utils.h"
#ifdef HAS_I2S
#include "i2s_drv.h"
#endif
#include "log.h"
#include "none_blocking_pause.h"
#include "sw_dac_diag.h"
#include "sw_dac_drv.h"
#include "utils_math.h"

// https://onlinesound.net/dtmf-generator

static const DtmfKeyPadFreq_t DtmfKeypadFrequencies[] = {
    {
        .code = 0x1,
        .letter = '1',
        .freq_small_hz = 697,
        .freq_big_hz = 1209,
        .min_period_ns = 9968000,
    },
    {
        .code = 0x0,
        .letter = '0',
        .freq_small_hz = 941,
        .freq_big_hz = 1336,
        .min_period_ns = 7465949,
    },
    {
        .code = 0x2,
        .letter = '2',
        .freq_small_hz = 697,
        .freq_big_hz = 1336,
        .min_period_ns = 8362420,
    }, /*8853888fix*/
    {
        .code = 0x3,
        .letter = '3',
        .freq_small_hz = 697,
        .freq_big_hz = 1477,
        .min_period_ns = 8739477,
    },
    {
        .code = 0x4,
        .letter = '4',
        .freq_small_hz = 770,
        .freq_big_hz = 1209,
        .min_period_ns = 9095496,
    },
    {
        .code = 0x5,
        .letter = '5',
        .freq_small_hz = 770,
        .freq_big_hz = 1336,
        .min_period_ns = 9021858,
    },
    {
        .code = 0x6,
        .letter = '6',
        .freq_small_hz = 770,
        .freq_big_hz = 1477,
        .min_period_ns = 9345112,
    }, // 8901002
    {
        .code = 0x7,
        .letter = '7',
        .freq_small_hz = 852,
        .freq_big_hz = 1209,
        .min_period_ns = 8248412,
    },
    {
        .code = 0x8,
        .letter = '8',
        .freq_small_hz = 852,
        .freq_big_hz = 1336,
        .min_period_ns = 8226680,
    },
    {
        .code = 0x9,
        .letter = '9',
        .freq_small_hz = 852,
        .freq_big_hz = 1477,
        .min_period_ns = 9446054,
    },
    {
        .code = 0xA,
        .letter = 'A',
        .freq_small_hz = 697,
        .freq_big_hz = 1633,
        .min_period_ns = 8583695,
    },
    {
        .code = 0xB,
        .letter = 'B',
        .freq_small_hz = 770,
        .freq_big_hz = 1633,
        .min_period_ns = 9155131,
    },
    {
        .code = 0xC,
        .letter = 'C',
        .freq_small_hz = 852,
        .freq_big_hz = 1633,
        .min_period_ns = 9255729,
    },
    {
        .code = 0xD,
        .letter = 'D',
        .freq_small_hz = 941,
        .freq_big_hz = 1633,
        .min_period_ns = 8546970,
    },
    {
        .code = 0xE,
        .letter = '*',
        .freq_small_hz = 941,
        .freq_big_hz = 1209,
        .min_period_ns = 7441866,
    },
    {
        .code = 0xF,
        .letter = '#',
        .freq_small_hz = 941,
        .freq_big_hz = 1477,
        .min_period_ns = 7444171,
    },
};

static const DtmfKeyPadFreq_t* DtmfKeyPadFreqGetNode(char letter) {
    const DtmfKeyPadFreq_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(DtmfKeypadFrequencies); i++) {
        if(DtmfKeypadFrequencies[i].letter == letter) {
            Node = &DtmfKeypadFrequencies[i];
            break;
        }
    }
    return Node;
}

static const DtmfKeyPadFreq_t* DtmfCodeToNode(uint8_t code) {
    const DtmfKeyPadFreq_t* Node = NULL;
    uint8_t i = 0;
    for(i = 0; i < ARRAY_SIZE(DtmfKeypadFrequencies); i++) {
        if(DtmfKeypadFrequencies[i].code == code) {
            Node = &DtmfKeypadFrequencies[i];
            break;
        }
    }
    return Node;
}

/*Compose function DtmfGetNode*/
COMPONENT_GET_NODE(Dtmf, dtmf)

#if 0
DtmfHandle_t* DtmfGetNode(uint8_t num) {
    DtmfHandle_t* Node = NULL;
    uint32_t i = 0;
    for(i = 0; i < dtmf_get_cnt(); i++) {
        if(num == DtmfInstance[i].num) {
            if(DtmfInstance[i].valid) {
                Node = &DtmfInstance[i];
                break;
            }
            break;
        }
    }
    return Node;
}
#endif

/*compose function DtmfGetConfig*/
COMPONENT_GET_CONFIG(Dtmf, dtmf)
#if 0
const DtmfConfig_t* DtmfGetConfig(uint8_t num) {
    const DtmfConfig_t* Config = NULL;
    uint32_t i = 0;
    for(i = 0; i < dtmf_get_cnt(); i++) {
        if(num == DtmfConfig[i].num) {
            if(DtmfConfig[i].valid) {
                Config = &DtmfConfig[i];
                break;
            }
        }
    }
    return Config;
}
#endif

static bool dtmf_send_key_info(uint8_t num, const DtmfKeyPadFreq_t* const CharInfo, uint32_t duration_ms) {
    bool res = false;
    if(CharInfo) {
        DtmfNimbleDiag(CharInfo);
        DtmfHandle_t* DtmfNode = DtmfGetNode(num);
        if(DtmfNode) {
            SwDac_t* SwDacNode = SwDacGetNode(DtmfNode->dac_num);
            if(SwDacNode) {
                if(SwDacNode->amplitude < 100) {
                    SwDacNode->amplitude = 100;
                }
                SwDacNode->frequency = (double)CharInfo->freq_big_hz;
                SwDacNode->frequency2 = (double)CharInfo->freq_small_hz;
                SwDacNode->dac_mode = DAC_MODE_DTMF;

#ifdef HAS_I2S
                I2sHandle_t* I2sNode = I2sGetNode(DtmfNode->i2s_num);
                if(I2sNode) {
                    res = sw_dac_set_array(DtmfNode->dac_num, 1, CharInfo->min_period_ns);
                    if(DtmfNode->debug) {
                        sw_dac_print_track(DtmfNode->dac_num);
                    }
                    if(res) {
                        res = i2s_dma_stop(DtmfNode->i2s_num);
                        res = i2s_play_tx(DtmfNode->i2s_num, DtmfNode->dac_num, true);
                        if(res) {
                            res = wait_in_loop_ms(duration_ms);
                            res = i2s_dma_stop(DtmfNode->i2s_num);
                        }
                    } else {
                        LOG_ERROR(DTMF, "SetArrayErr, Pediod:%u ns", CharInfo->min_period_ns);
                    }
                } else {
                    LOG_ERROR(DTMF, "I2sErr");
                }
#endif
            } else {
                LOG_ERROR(DTMF, "SwDACNodeErr DAC%u", DtmfNode->dac_num);
            }
        } else {
            LOG_ERROR(DTMF, "DtmfNodeErr %u", num);
        }
    }
    return res;
}

bool dtmf_send_char(uint8_t num, char letter, uint32_t duration_ms) {
    bool res = false;
    LOG_INFO(DTMF, "DTMF%u Send [%c], %u ms", num, letter, duration_ms);

    const DtmfKeyPadFreq_t* CharInfo = DtmfKeyPadFreqGetNode(letter);
    if(CharInfo) {
        res = dtmf_send_key_info(num, CharInfo, duration_ms);
    } else {
        LOG_ERROR(DTMF, "UndefLetter [%c]", letter);
    }
    return res;
}

bool dtmf_send_code(uint8_t num, uint8_t code, uint32_t duration_ms) {
    bool res = false;
    LOG_INFO(DTMF, "DTMF%u Send [0x%x], %u ms", num, code, duration_ms);

    const DtmfKeyPadFreq_t* CharInfo = DtmfCodeToNode(code);
    if(CharInfo) {
        res = dtmf_send_key_info(num, CharInfo, duration_ms);
    }
    return res;
}

bool dtmf_send(uint8_t num, const uint8_t* const data, size_t len, uint32_t duration_ms) {
    bool res = false;
    LOG_INFO(DTMF, "DTMF%u SendData size: %u byte, %u ms", num, len, duration_ms);
    size_t i = 0;
    size_t ok = 0;
    for(i = 0; i < len; i++) {
        Type8Union_t Byte;
        Byte.u8 = data[i];
        res = dtmf_send_code(num, Byte.nibble_h, duration_ms);
        if(res) {
            res = dtmf_send_code(num, Byte.nibble_l, duration_ms);
            if(res) {
                ok++;
            }
        }
    }

    if(ok == len) {
        res = true;
    } else {
        res = false;
    }
    return res;
}

bool dtmf_init_one(uint8_t num) {
    bool res = false;
    LOG_WARNING(DTMF, "%u Init..", num);
    const DtmfConfig_t* Config = DtmfGetConfig(num);
    if(Config) {
        DtmfConfigDiag(Config);
        DtmfHandle_t* Node = DtmfGetNode(num);
        if(Node) {
            Node->i2s_num = Config->i2s_num;
            Node->dac_num = Config->dac_num;
            Node->amplitude = Config->amplitude;

            SwDac_t* DacNode = SwDacGetNode(Node->dac_num);
            if(DacNode) {
                DacNode->amplitude = Node->amplitude;
            }
            res = true;
        } else {
            LOG_ERROR(DTMF, "DTMF%u NodeErr", num);
        }
    } else {
        LOG_DEBUG(DTMF, "DTMF%u ConfigErr", num);
    }
    return res;
}

COMPONENT_INIT_PATTERT(DTMF, DTMF, dtmf)

#if 0
bool dtmf_init(void) {
    bool res = true;
    LOG_WARNING(DTMF, "Init..");
    uint8_t num = 0;
    uint32_t ok = 0;
    for(num = 0; num <= dtmf_get_cnt(); num++) {
        res = dtmf_init_one(num);
        if(res) {
            LOG_INFO(DTMF, "DTMF%u InitOk", num);
            ok++;
        } else {
            LOG_DEBUG(DTMF, "DTMF%u InitErr", num);
        }
    }

    if(ok) {
        res = true;
        LOG_INFO(DTMF, "Init %u DTMFs", ok);
    } else {
        res = false;
    }
    return res;
}
#endif

/*dtp 1*/
//#define SIZE_DIM 10

//#define R SIZE_DIM
//#define C SIZE_DIM

static bool isValid(int i, int j, uint32_t RR, uint32_t CC) {
    bool res = false;
    if(0 <= i) {
        if(i < RR) {
            if(0 <= j) {
                if(j < CC) {
                    res = true;
                }
            }
        }
    }
    return res;
}

bool matrix_zigzag_order(uint32_t num, uint32_t RR, uint32_t CC, uint32_t* const x, uint32_t* const y) {
    bool res = false;
    uint32_t cnt = 0;
    int k = 0;
    for(k = 0; k < RR; k++) {
        if(cnt == num) {
            *x = k;
            *y = 0;
            return true;
        }
        // cli_printf(" i:%10u, j:%10u"CRLF, k,0);
        cnt++;

        // set row index for next point in
        // diagonal
        int i = k - 1;

        // set column index for next point in diagonal
        int j = 1;

        /* Print Diagonally upward */
        while(isValid(i, j, RR, CC)) {
            // cout << arr[i][j] << " ";
            if(cnt == num) {
                *x = i;
                *y = j;
                return true;
            }

            // cli_printf(" i:%10u, j:%10u"CRLF, i,j);
            cnt++;
            i--;

            // move in upright direction
            j++;
        }
    }
    return res;
}

//  Letter 1, FreqSmall 697 Hz, FreqBig 1209 Hz  N: 49, M:85, 0.070301 s, 0.070306 s, diff 0.000005 s
typedef struct {
    uint32_t s;
    uint32_t h;
    double period_diff_s;
} DtmfMinError_t;

#define ALLOWABLE_ERROR (1.0 / 1280000.0)
bool dtmf_calc_periods(uint32_t init_i, char letter, uint32_t* const N, uint32_t* const M) {
    bool res = false;
    LOG_INFO(DTMF, "CalcPeriod for %c", letter);
    const DtmfKeyPadFreq_t* Node = DtmfKeyPadFreqGetNode(letter);
    if(Node) {
        LOG_INFO(DTMF, "Letter %c, FreqSmall %u Hz, FreqBig %u Hz", letter, Node->freq_small_hz, Node->freq_big_hz);

        uint32_t s = 0;
        uint32_t h = 0;
        uint32_t i = init_i;
        double period_freq_small = 0.0;
        double period_freq_big = 0.0;
        double period_diff_s = 0.0;
        DtmfMinError_t DtmfMin;
        DtmfMin.period_diff_s = DBL_MAX;
        DtmfMin.s = 0;
        DtmfMin.h = 0;

        uint32_t upper_bound = MAX(Node->freq_small_hz, Node->freq_big_hz);
        LOG_INFO(DTMF, "Find (N,M) in %u x %u space", upper_bound, upper_bound);
        for(i = init_i; i < upper_bound * upper_bound; i++) {
            res = matrix_zigzag_order(i, upper_bound, upper_bound, &s, &h);
            if(res) {
                period_freq_small = ((double)(s + 1)) / ((double)Node->freq_small_hz);
                period_freq_big = ((double)(h + 1)) / ((double)Node->freq_big_hz);
                double max_time = MAX(period_freq_big, period_freq_small);
                if(max_time <= 1.00001) {
                    period_diff_s = fabs(period_freq_small - period_freq_big);
                    // cli_printf("\r N:%10u, M:%10u, %1.6f s, %1.6f s, diff %1.6f s",
                    // n+1,m+1,period_freq_small,period_freq_big,period_diff_s); cli_printf("N:%10u,
                    // M:%10u,PeriodFreqSmall %1.6f s, PeriodFreqBig %1.6f s, Diff %1.6f s"CRLF,
                    // n+1,m+1,period_freq_small,period_freq_big,period_diff_s);
                    cli_printf("\ri:%u, S:%10u, H:%10u,PerFreqSmall %1.6f s, PerFreqBig %1.6f s, Diff %1.6f s; "
                               "CurSol(S:%u, H:%u, Err:%f s)",
                               i, s + 1, h + 1, period_freq_small, period_freq_big, period_diff_s, DtmfMin.s, DtmfMin.h,
                               DtmfMin.period_diff_s);
                    res = is_double_equal_absolute(period_freq_small, period_freq_big, ALLOWABLE_ERROR);
                    if(res) {
                        LOG_INFO(DTMF, "Spot N:%u, M:%u, CommonPeriod %f s", s + 1, h + 1, period_freq_small);
                        *M = h;
                        *N = s;
                        res = true;
                        break;
                    }

                    /*TODO Update min diff*/
                    if(period_diff_s < DtmfMin.period_diff_s) {
                        DtmfMin.period_diff_s = period_diff_s;
                        DtmfMin.s = s + 1;
                        DtmfMin.h = h + 1;
                    }
                }
            }
        }
    }
    return res;
}
// dtp 1 454000
