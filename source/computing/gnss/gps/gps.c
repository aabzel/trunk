#include "gps.h"

#include <complex.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "array.h"
#include "code_generator.h"
#include "debug_info.h"
#include "file_pc.h"
#include "float_utils.h"
#include "gnss_diag.h"
#include "gnss_drv.h"
#include "gps_misc_1.h"
#include "log.h"
#include "physics_utils.h"
#include "utils_math.h"
#ifdef HAS_HISTOGRAM
#include "histogram.h"
#endif
#include "vector_math.h"

COMPONENT_GET_NODE(Gps, gps)

COMPONENT_GET_CONFIG(Gps, gps)

GpsSat_t* GpsGetSatConfig(const GpsSat_t* const SatS, uint32_t size, int32_t prn) {
    GpsSat_t* SatConfig = NULL;
    uint32_t i = 0;
    for(i = 0; i < size; i++) {
        if(SatS[i].valid) {
            if(prn == SatS[i].prn) {
                SatConfig = &SatS[i];
            }
        }
    }
    return SatConfig;
}

bool gps_proc_one(uint8_t num) {
    bool res = true;
    LOG_PARN(GPS, "Init %u", num);

    return res;
}

bool gps_generate_prn_samples(int prn, int8_t* const sample, double sample_per_chip) {
    bool res = false;
    uint32_t repeat = (uint32_t)sample_per_chip;
    LOG_DEBUG(GPS, "GeneratePRN%u,Chip:%f samples, %u samp", prn, sample_per_chip, repeat);
    uint8_t PrnCode[PRN_LENGTH] = {0};
    gps_generate_prn(PrnCode, prn);

    uint32_t i = 0;
    for(i = 0; i < PRN_LENGTH; i++) {
        int8_t pattern = 0;
        switch(PrnCode[i]) {
        case 1: {
            pattern = -1;
        } break;
        case 0: {
            pattern = 1;
        } break;
        default:
            break;
        }
        uint32_t j = 0;
        for(j = 0; j < repeat; j++) {
            sample[i * repeat + j] = pattern;
            res = true;
        }
    }

    // LOG_INFO(GNSS, "PrnSamples");
    // array_i8_print(sample,30);
    return res;
}

int32_t gps_correlation_i8(const int8_t* const signal, const int8_t* const SignalI, const int8_t* const SignalQ,
                           size_t size) {
    bool res = false;
    int32_t corr_res = 0;
    LOG_DEBUG(GNSS, "size:%d", size);
    if(signal) {
        if(SignalI) {
            if(SignalQ) {
                if(size) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        int32_t mult_summ_cur_i = 0;
        int32_t mult_summ_cur_q = 0;

        mult_summ_cur_i = array_i8_mult_sum(signal, SignalI, size);
        mult_summ_cur_q = array_i8_mult_sum(signal, SignalQ, size);

        LOG_DEBUG(GNSS, "mult_summ_cur_i:%d", mult_summ_cur_i);
        LOG_DEBUG(GNSS, "mult_summ_cur_q:%d", mult_summ_cur_q);
        if(mult_summ_cur_i < 0) {
            mult_summ_cur_i = 0;
        }

        if(mult_summ_cur_q < 0) {
            mult_summ_cur_q = 0;
        }

        int32_t mult_summ_cur_i_s = mult_summ_cur_i * mult_summ_cur_i;
        int32_t mult_summ_cur_q_s = mult_summ_cur_q * mult_summ_cur_q;

        corr_res = (int32_t)sqrtf((float)mult_summ_cur_i_s + (float)mult_summ_cur_q_s);
    }
    return corr_res;
}

bool gps_mix_lo_signal(GpsHandle_t* const Node, int32_t prn, const int8_t* const sample_data, uint32_t size) {
    bool res = false;
    if(Node) {
        if(sample_data) {
            if(size) {
                // LOG_INFO(GPS, "Data");
                // array_i8_print(sample_data, 50);
                LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(prn);
                if(Oscillator) {
                    res = array_i8_mult(sample_data, Oscillator->if_lo_I, Node->SignalI, size);
                    res = array_i8_mult(sample_data, Oscillator->if_lo_Q, Node->SignalQ, size) && res;
                } else {
                    LOG_ERROR(GPS, "NoLoErr PRN%d", prn);
                }

                // LOG_INFO(GPS, "DataMixI");
                // array_i8_print(Node->SignalI, 50);
                // LOG_INFO(GPS, "DataMixQ");
                // array_i8_print(Node->SignalQ, 50);
            } else {
                LOG_ERROR(GPS, "MixSizeErr");
            }
        } else {
            LOG_ERROR(GPS, "MixDataErr");
        }
    } else {
        LOG_ERROR(GPS, "MixNodeErr");
    }
    return res;
}

/*
 * out offset at whitch corralation max
 */

bool gps_seek_prn_phase(GpsHandle_t* Node, int prn, size_t size, PrnInfo_t* const PrnInfo) {
    bool res = false;
    LOG_PARN(GPS, "gps_seek_prn_phase");
    if(ONE_PRN_SAMPLE_CNT <= (2 * size)) {
        int8_t GeneratedPrnSample[ONE_PRN_SAMPLE_CNT] = {0};
        // memset(GeneratedPrnSample, 0, sizeof(GeneratedPrnSample));
        res = gps_generate_prn_samples(prn, GeneratedPrnSample, Node->sample_per_chip);

        if(res) {
            res = false;
            PrnInfo_t BestPrnInfo = {0};
            memset(&BestPrnInfo, 0, sizeof(PrnInfo_t));
            BestPrnInfo.prn = prn;
            // PrnInfo->prn = prn;

            if(Node->prn_phase_seek_end_sample <= ONE_PRN_SAMPLE_CNT) {
                size_t s = 0; // offset_samples
                // Nattow seek range depended of sat and file
                for(s = Node->prn_phase_seek_start_sample; s < Node->prn_phase_seek_end_sample;
                    s += Node->step_samples) {
                    int32_t corr_res = 0;
                    LOG_PARN(GPS, "phase:%u", s);
                    corr_res = gps_correlation_i8(GeneratedPrnSample, &Node->SignalI[s], &Node->SignalQ[s],
                                                  ONE_PRN_SAMPLE_CNT);

                    if(BestPrnInfo.Max.mult_summ < corr_res) {
                        BestPrnInfo.Max.mult_summ = corr_res;
                        BestPrnInfo.Max.offset_samples = s;
                        res = true;
                    }
                }

            } else {
                LOG_ERROR(GPS, "SeekEndSampleError");
                res = false;
            }

            // PrnInfo->prn = prn;
            memcpy(PrnInfo, &BestPrnInfo, sizeof(PrnInfo_t));

        } else {
            LOG_ERROR(GPS, "GeneratePRNError");
        }
    } else {
        LOG_ERROR(GPS, "SignalChunkError");
    }

    return res;
}

#if 0
static bool gps_is_valid_correlation(const PrnInfo_t * const PrnInfo){
    bool res = false;
    if(PrnInfo){
        if(1<PrnInfo->mult_summ_max){
            res = true;
        }
        if(PrnInfo->mult_summ_min<-1){
            res = true;
        }
    }
    return res;
}
#endif

bool GpsUpdateSatInfo(int32_t doppler_freq_offset_hz, GpsSat_t* const SatS, PrnInfo_t* const PrnInfo) {
    bool res = false;
    if(SatS) {
        if(PrnInfo) {
            PrnInfo->prn = SatS->prn;
            if(SatS->CorrelationMax.mult_summ < PrnInfo->Max.mult_summ) {
                SatS->CorrelationMax.mult_summ = PrnInfo->Max.mult_summ;
                SatS->CorrelationMax.offset_samples = PrnInfo->Max.offset_samples;
                SatS->CorrelationMax.if_corr_hz = doppler_freq_offset_hz;
                cli_printf(CRLF "UpdMax:Step:%u Hz,%s" CRLF, SatS->if_seek_step_hz, PrnInfoToStr(PrnInfo));
                res = true;
            }
        }
    }

    return res;
}

/*
 * PrnInfo -
 *
 *
 * */
bool GpsProcTwoPrn(GpsHandle_t* Node, const int8_t* const sample_data, size_t size, int32_t prn,
                   int32_t doppler_freq_offset_hz, PrnInfo_t* const PrnInfo) {
    bool res = false;
    LOG_DEBUG(GPS, "GpsProcTwoPrn");
    if(TWO_PRN_SAMPLE_CNT <= size) {
        PrnInfo->prn = prn;
        res = gps_mix_lo_signal(Node, prn, sample_data, TWO_PRN_SAMPLE_CNT);
        if(res) {
            res = gps_seek_prn_phase(Node, prn, TWO_PRN_SAMPLE_CNT, PrnInfo);
            if(false == res) {
                LOG_ERROR(GPS, "PRN%d Seek Err", prn);
            }
        } else {
            LOG_ERROR(GPS, "MixErr PRN%d", prn);
        }

    } else {
        LOG_ERROR(GPS, "sizeErr");
    }
    return res;
}

bool gps_proc_data(GpsHandle_t* Node, const int8_t* const sample_data, size_t size) {
    bool res = false;

    if(TWO_PRN_SAMPLE_CNT <= size) {

        LOG_INFO(GPS, "ProcData %u samples,IF:%u Hz,Err %u Hz", size, Node->intermediate_freq_hz, GNSS_ERROR_HZ);
        int32_t lo_fl_freq_hz = Node->intermediate_freq_hz;

        PrnInfo_t PrnInfo = {0};

        uint32_t i = 0;
        uint32_t iterations = Node->SatS[0].doppler_range_hz / Node->SatS[0].if_seek_step_hz;
        LOG_INFO(GPS, "Iterations:%u", iterations);
        for(i = 0; i <= iterations; i++) {
            int32_t doppler_freq_offset_hz = zigzag_traversal(i, Node->SatS[0].if_seek_step_hz);
            lo_fl_freq_hz = Node->intermediate_freq_hz + doppler_freq_offset_hz;

            // memset(Node->if_lo_I, 0, sizeof(Node->if_lo_I));
            // memset(Node->if_lo_Q, 0, sizeof(Node->if_lo_Q));

            LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(14);
            if(Oscillator) {
                Oscillator->frequency_hz = lo_fl_freq_hz;
                res = sdr_generate_local_oscilator_signals(Oscillator);
            }
            // res = gps_generate_local_oscilator_signals(Node, lo_fl_freq_hz, TWO_PRN_SAMPLE_CNT);

            if(res) {
                res = gps_mix_lo_signal(Node, 14, sample_data, TWO_PRN_SAMPLE_CNT);

                if(res) {
                    memset(&PrnInfo, 0, sizeof(PrnInfo));
                    PrnInfo.if_corr_hz = doppler_freq_offset_hz;

                    res = gps_seek_prn_phase(Node, Node->SatS[0].prn, TWO_PRN_SAMPLE_CNT, &PrnInfo);
                    if(res) {
                        GpsUpdateSatInfo(doppler_freq_offset_hz, &Node->SatS[0], &PrnInfo);
                    } else {
                        LOG_ERROR(GPS, "PRN%d SeekErr", Node->SatS[0].prn);
                    }
                } else {
                    LOG_ERROR(GPS, "MultErr");
                }
            } else {
                LOG_DEBUG(GPS, " GenerateLoErr");
            }

            cli_printf("\r DopplerDiff:%6d Hz,Step:%3u Hz,CurCorr:%d", doppler_freq_offset_hz,
                       Node->SatS[0].if_seek_step_hz, PrnInfo.Max.mult_summ);
        }
        cli_printf(CRLF);
        LOG_INFO(GPS, "SatInfo %s", GpsSatToStr(&Node->SatS[0]));
    }
    return res;
}

bool gps_init_one(uint8_t num) {
    bool res = true;
    LOG_WARNING(GPS, "Init %u", num);
    const GpsConfig_t* Config = GpsGetConfig(num);
    if(Config) {
        LOG_WARNING(GPS, "Config:%s", GpsConfigToStr(Config));
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            Node->adc_sample_rate_hz = Config->adc_sample_rate_hz;
            Node->gnss_front_end_lo_freq_hz = Config->gnss_front_end_lo_freq_hz;
            Node->step_samples = Config->step_samples;
            Node->SatS = Config->SatS;
            Node->file_name = Config->file_name;
            Node->sat_cnt = Config->sat_cnt;
            Node->histogram_num = Config->histogram_num;

            Node->adc_sample_time_s = 1.0 / Node->adc_sample_rate_hz;
            Node->adc_sample_len_m = Node->adc_sample_time_s * SPEED_OF_LIGHT_MPS;
            Node->one_prn_sample_cnt = 0.001 / Node->adc_sample_time_s;

            Node->intermediate_freq_hz = FREQ_L1_HZ - Node->gnss_front_end_lo_freq_hz;
            Node->sample_per_chip = ONE_PRN_SAMPLE_CNT / PRN_LENGTH;

            // Node->SatS[0].if_hz = Node->intermediate_freq_hz;
            LOG_INFO(GPS, "%s", GpsNodeToStr(Node));
            res = true;
        }
    }
    set_log_level(GPS, LOG_LEVEL_NOTICE);
    return res;
}

bool gps_init_custom(void) {
    bool res = true;
    set_log_level(GPS, LOG_LEVEL_INFO);
    set_log_level(DLL, LOG_LEVEL_NOTICE);
    set_log_level(FLL, LOG_LEVEL_INFO);
    set_log_level(PLL, LOG_LEVEL_NOTICE);

    LOG_WARNING(GPS, "TRACKING_PLL_PROP_C1:%f", TRACKING_PLL_PROP_C1);
    LOG_WARNING(GPS, "TRACKING_PLL_DIFF_C2:%f", TRACKING_PLL_DIFF_C2);
    return res;
}

bool gps_seek_prn_phase_all(uint8_t num, const char* const file_name, int32_t prn, int32_t doppler_freq_offset_hz,
                            double percent, uint32_t seek_start_sample, uint32_t seek_end_sample

) {
    bool res = false;
    if(file_name) {
        LOG_INFO(GPS, "PostProc File:[%s],PRN:%d,Doppler:%d Hz", file_name, prn, doppler_freq_offset_hz);
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            Node->prn_phase_seek_start_sample = seek_start_sample;
            Node->prn_phase_seek_end_sample = seek_end_sample;
            Node->FilePtr = fopen(file_name, "rb");
            if(Node->FilePtr) {
                LOG_INFO(GPS, "OpenOkFile:[%s]", file_name);
                LOG_INFO(GPS, "intermediate_freq: %d Hz", Node->intermediate_freq_hz);
                Node->size_bytes = file_pc_get_size(file_name);
                Node->sample_cnt = Node->size_bytes;
                uint32_t prn_total_cnt = Node->sample_cnt / ONE_PRN_SAMPLE_CNT;
                uint32_t prn_to_proc = 0;
                uint32_t sample_to_proc = 0;
                sample_to_proc = percent * ((double)Node->sample_cnt) / 100.0;
                prn_to_proc = sample_to_proc / ONE_PRN_SAMPLE_CNT;
                // sample_to_proc =  2000;
                LOG_INFO(GPS, "PRN:%u/%u PRNs", prn_to_proc, prn_total_cnt);
                Node->duration_s = (double)Node->sample_cnt / Node->adc_sample_rate_hz;
                LOG_INFO(GPS, "OpenOkFile:[%s],Size:%d bytes,Samples:%u,Duration:%f s", file_name, Node->size_bytes,
                         Node->sample_cnt, Node->duration_s);
                if(Node->size_bytes) {
                    int8_t TwoPrnSampleData[TWO_PRN_SAMPLE_CNT] = {0};
                    FILE* PhaseFilePtr = NULL;

                    char prn_phase_file[80] = {0};
                    uint32_t duration_ms = (uint32_t)(1000 * sample_to_proc) / ((uint32_t)Node->adc_sample_rate_hz);
                    snprintf(prn_phase_file, sizeof(prn_phase_file),
                             "PRN%d_PhaseDoppler_%d_Hz_%uMs_Step_%d_Samples.csv", prn, doppler_freq_offset_hz,
                             duration_ms, Node->step_samples);
                    PhaseFilePtr = fopen(prn_phase_file, "w");
                    if(PhaseFilePtr) {
                        LOG_INFO(GPS, "OpenOkPRNFile:[%s]", prn_phase_file);
                        size_t offset = 0;

                        PrnInfo_t MaxCorrPrn = {0};
                        MaxCorrPrn.Max.mult_summ = 0;
                        int32_t lo_fl_freq_hz = 0;
                        lo_fl_freq_hz = Node->intermediate_freq_hz + doppler_freq_offset_hz;

                        LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(prn);
                        if(Oscillator) {
                            Oscillator->frequency_hz = lo_fl_freq_hz;
                            res = sdr_generate_local_oscilator_signals(Oscillator);
                        } else {
                            LOG_ERROR(GPS, "NoLoForPRN%d", prn);
                            return false;
                        }

                        for(offset = 0; offset < sample_to_proc; offset += ONE_PRN_SAMPLE_CNT) {

                            res = file_pc_load_to_array_i8_ll(Node->FilePtr, offset, TwoPrnSampleData,
                                                              sizeof(TwoPrnSampleData));
                            if(res) {
                                PrnInfo_t CurPrn = {0};
                                CurPrn.prn = prn;
                                res = GpsProcTwoPrn(Node, TwoPrnSampleData, sizeof(TwoPrnSampleData), prn,
                                                    doppler_freq_offset_hz, &CurPrn);
                                if(res) {
                                    if(MaxCorrPrn.Max.mult_summ < CurPrn.Max.mult_summ) {
                                        LOG_WARNING(GPS, "UpdMax Old %d New:%d", MaxCorrPrn.Max.mult_summ,
                                                    CurPrn.Max.mult_summ);
                                        MaxCorrPrn = CurPrn;
                                        // memcpy(&MaxCorrPrn,&CurPrn,sizeof(PrnInfo_t));
                                    }
                                    // cli_printf("Max:%s", PrnInfoToStr(&MaxCorrPrn));
#ifdef HAS_HISTOGRAM
                                    res = histogram_add(Node->histogram_num, (int32_t)CurPrn.Max.offset_samples);
#endif
                                    LOG_INFO(GPS, "%s,Cur:%s", ProgressToStr(offset, sample_to_proc),
                                             PrnInfoToStr(&CurPrn));
                                    fprintf(PhaseFilePtr, "%u, %u, %u \n", offset, CurPrn.Max.offset_samples,
                                            CurPrn.Max.mult_summ);
                                } else {
                                    LOG_ERROR(GPS, "ProcErr");
                                }
                            } else {
                                LOG_ERROR(GPS, "LoadTwoPRNErr");
                            }
                        }
#ifdef HAS_HISTOGRAM
                        HistogramItem_t Item = {0};
                        res = histogram_get_max(Node->histogram_num, &Item);
                        LOG_WARNING(GPS, "%s", HistogramItemToStr(&Item));
#endif
                        fclose(PhaseFilePtr);

                    } else {
                        LOG_ERROR(GPS, "OpenErrPrnFile:[%s]", prn_phase_file);
                    }
                }
                fclose(Node->FilePtr);
                cli_printf(CRLF);
            } else {
                LOG_ERROR(GPS, "OpenErrFile:[%s]", file_name);
                res = false;
            }
        }
    }
    return res;
}

#define EPL_COEF (6.0)

double pd_regulator(double in_value) {
    double out = 0.0;
    static double in_old = 0.0;
    double diff = in_value - in_old;
    out = diff + in_value * 0.3;

    in_old = in_value;
    return out;
}

double fll_discriminator_rad(SdrCorrRes_t* const New, SdrCorrRes_t* const Old) {
    double freq_diff_rad = 0.0;
    double true_phase_diff_rad = 0.0;

#if 0
    /* FLL discriminator */
    double f1 = (New->correlation_i == 0) ? (M_PI / 2.0) : atan((double)New->correlation_q / (double)New->correlation_i);
    double f2 = (Old->correlation_i == 0) ? (M_PI / 2.0) : atan((double)Old->correlation_q / (double)Old->correlation_i);
    freq_diff_rad = f1 - f2;

    if(freq_diff_rad > (M_PI / 2.0)) {
        freq_diff_rad = M_PI - freq_diff_rad;
    } else {
        if(freq_diff_rad < (-M_PI / 2.0)) {
            freq_diff_rad = -M_PI - freq_diff_rad;
        }
    }
#endif

#if 0
    //my phase detector
    double complex X1 = ((double)Present->correlation_i) + ((double)Present->correlation_q) * I;
    double complex X2 = ((double)OldPresent.correlation_i) + ((double)OldPresent.correlation_q) * I;
    freq_diff_rad = (float)calc_angle_between_complex_rad(&X1, &X2);
#endif

#if 1
    Vector_t v1 = {
        .dx = ((double)New->correlation_i),
        .dy = ((double)New->correlation_q),
        .dz = 0.0,
    };
    Vector_t v2 = {
        .dx = ((double)Old->correlation_i),
        .dy = ((double)Old->correlation_q),
        .dz = 0.0,
    };
    true_phase_diff_rad = calc_angle_between_vectors_rad(&v1, &v2);
    // true_phase_diff_rad = calc_angle_between_vectors_naiv_rad(&v1, &v2);
    freq_diff_rad = -true_phase_diff_rad; /*Fix Phase diff*/
#endif

#if 0
    bool res = false;
    if(0<Old->abs) {
        if(0<New->abs) {
          res = is_double_equal_absolute(((double)freq_diff_rad),(double)true_phase_diff_rad,0.001);
          if (false==res) {
              LOG_DEBUG(FLL,"FLL discriminator error");
              LOG_DEBUG(FLL, "PhaseDiff:%3.2f Deg,PhaseDiffTrue:%3.2f Deg",
                      rad_2_deg(freq_diff_rad),
                      rad_2_deg(true_phase_diff_rad));
              LOG_DEBUG(FLL,"New:%s",SdrCorrToStr(New));
              LOG_DEBUG(FLL,"Old:%s",SdrCorrToStr(Old));
             // exit(1);
          }

        }
    }
    freq_diff_rad = -true_phase_diff_rad;/*Fix Phase diff*/

#endif

    return -freq_diff_rad;
}

double fll_discriminator_deg(SdrCorrRes_t* const New, SdrCorrRes_t* const Old) {
    double freq_diff_rad = 0.0;
    double freq_diff_deg = 0.0;

    freq_diff_rad = (double)fll_discriminator_rad(New, Old);
    freq_diff_deg = rad_2_deg(freq_diff_rad);
    LOG_DEBUG(FLL, "FreqDiff:%f Rad,FreqDiff:%f Deg", freq_diff_rad, freq_diff_deg);
    return freq_diff_deg;
}

// static float carr_phase_err_old = 0.0;
static SdrCorrRes_t PrevPRNPresent = {0}; // TODO move for specific PRN

#define MAX_ALLO_FREQ_STEP (2.0 * MAX_FREQ_SHIFT_HZ_PER_PRN)
bool freq_tune_verify(double freq_tune_hz, double* const out_freq_tune_hz) {
    bool res = false;
    if(MAX_ALLO_FREQ_STEP < freq_tune_hz) {
        *out_freq_tune_hz = MAX_ALLO_FREQ_STEP;
        res = false;
    }

    if(freq_tune_hz < -MAX_ALLO_FREQ_STEP) {
        *out_freq_tune_hz = -MAX_ALLO_FREQ_STEP;
        res = false;
    }

    if(false == res) {
        LOG_DEBUG(FLL, "UnrealFreqIncIn1ms:%f Hz", freq_tune_hz);
    }
    return res;
}

bool fll_loop(SdrCorrRes_t* const Present, SdrCorrRes_t* const Prev, double* const freq_tune_out) {
    bool res = false;
    double freq_diff_deg = 0.0;

    freq_diff_deg = fll_discriminator_deg(Present, Prev);

    // LOG_DEBUG(FLL, "PresentOldPhaseErr:%f deg", freq_diff_deg);
    // LOG_DEBUG(GPS, "PhaseDiff:%3.2f Rad,PhaseDiffTrue:%3.2f Rad", freq_diff_rad, true_phase_diff_rad);

    double if_freq_offset_hz = 0.0;

    // if_freq_offset_hz += TRACKING_PLL1_C1 * (carr_phase_err - carr_phase_err_old) ;
    // if_freq_offset_hz +=   TRACKING_PLL1_C2 * dt_s * carr_phase_err ;
    // if_freq_offset_hz += TRACKING_FLL1 * dt_s * freq_diff_deg;
    if_freq_offset_hz = TRACKING_FLL1 * PRN_TIME_S * deg_to_rad(freq_diff_deg);
    *freq_tune_out = if_freq_offset_hz;

    // memcpy(&OldPresent, Present, sizeof(SdrCorrRes_t));

    LOG_DEBUG(FLL, "FreqDiff:%lf deg,IfFreqOffSet:%lf Hz", freq_diff_deg, if_freq_offset_hz);
    return res;
}

static bool epl_verify(SdrEPL_t* const Node) {
    bool res = false;
    if(Node) {
        double noncoherent = sdr_calc_noncoherent(&Node->Early, &Node->Late);
        LOG_DEBUG(GPS, "NonCoherent: %f", noncoherent);
        if(Node->Present.abs < Node->Early.abs) {
            if(Node->Late.abs < Node->Present.abs) {
                // E>P>L
                LOG_DEBUG(GPS, "EarlyMore!");
            }
            // s--;
        }

        if(Node->Present.abs < Node->Late.abs) {
            if(Node->Early.abs < Node->Present.abs) {
                // E<P<L
                LOG_DEBUG(GPS, "LateMore!");
            }
        }

        if(Node->Early.abs < Node->Present.abs) {
            if(Node->Late.abs < Node->Present.abs) {
                // E<P>L
                LOG_PARN(GPS, "PRN_Escort..");
            }
        }

        if(Node->Present.abs < Node->Early.abs) {
            if(Node->Present.abs < Node->Late.abs) {
                /*E>P<L*/
                LOG_WARNING(GPS, "!!!PRN Lost!");
                res = true;
            }
        }
    }
    return res;
}

static double calc_carrier_phase_err_deg_v1(SdrCorrRes_t* const Present) {
    double carr_phase_err_deg = 0.0;
    if(Present) {
        double carr_phase_err_rad = 0.0;
        carr_phase_err_rad = calc_carrier_phase_err_rad(Present->correlation_i, Present->correlation_q);
        carr_phase_err_deg = rad_2_deg(carr_phase_err_rad);
    }
    return carr_phase_err_deg;
}
static double old = 0.0;
/*LO phase regulator costas_loop*/
bool pll_loop(SdrCorrRes_t* const Present, double* const out_carr_phase_err_deg, double* const carr_phase_tune_deg_i) {
    bool res = false;
    // static float carr_phase_prev_err_deg = 0;
    if(carr_phase_tune_deg_i) {
        double carr_phase_err_deg = 0.0;
        carr_phase_err_deg = calc_carrier_phase_err_deg_v1(Present);
        double carr_phase_err = 0.0;
        carr_phase_err = carr_phase_err_deg / 180.0;
        *out_carr_phase_err_deg = carr_phase_err_deg;

        double tune_lo_freq_hz = 0.0;
        tune_lo_freq_hz += (0.1 / 4.0) * (carr_phase_err - old); // plus from book
        tune_lo_freq_hz += 0.1 * carr_phase_err;
        // tune_lo_freq_hz += carr_phase_diff_err_deg;
        LOG_DEBUG(PLL, "CarrPhaseErr:%f Deg,TuneLoPhase:%f Deg", carr_phase_err_deg, tune_lo_freq_hz);
        *carr_phase_tune_deg_i = tune_lo_freq_hz; // plus or minus?
        old = carr_phase_err;
        // carr_phase_prev_err_deg=carr_phase_err_deg;
    }

    return res;
}

// delay lock loop
static bool dll_loop(SdrEPL_t* CorrCur, int32_t* const tune, double* const non_coherent,
                     double* const filt_non_coherent) {
    bool res = true;
    double noncoherent = sdr_calc_noncoherent(&CorrCur->Early, &CorrCur->Late);
    double filt_noncoherent = 2.0 * noncoherent;
    // filt_noncoherent = pd_regulator( noncoherent);
    // cli_printf("NonCoh:%3.2f",EscortInfo.filt_noncoherent);
    if(0 < filt_noncoherent) {
        *tune = -1;
    } else if(filt_noncoherent < 0.0) {
        *tune = 1;
    }

    // *tune = (int32_t)(-filt_noncoherent);
    *non_coherent = noncoherent;
    *filt_non_coherent = filt_noncoherent;
    LOG_DEBUG(DLL, "NonCoh:%f,NonCohFilt:%f,Tune:%d Sam", noncoherent, filt_noncoherent, *tune);
    return res;
}

static bool gnss_epl_calc(GpsHandle_t* Node, int32_t EplOfftestStep, int8_t* const GeneratedPrnSample,
                          SdrEPL_t* EplNode) {
    bool res = false;
    LOG_DEBUG(GPS, "EPL calc");
    if(Node) {
        if(EplNode) {
            if(GeneratedPrnSample) {
                res = true;
            } else {
                res = false;
                LOG_ERROR(GPS, "GeneratedPrnSampleErr");
            }

        } else {
            res = false;
            LOG_ERROR(GPS, "EplNodeErr");
        }
    } else {
        res = false;
        LOG_ERROR(GPS, "NodeErr");
    }

    if(res) {
        LOG_DEBUG(GPS, "EPL calc in ok");
        uint32_t offset_early = 0;
        uint32_t offset_present = EplOfftestStep;
        uint32_t offset_late = 2 * EplOfftestStep;
        res = gnss_correlation_i8_iq(GeneratedPrnSample, &Node->SignalI[offset_early], &Node->SignalQ[offset_early],
                                     ONE_PRN_SAMPLE_CNT, &EplNode->Early);
        if(false == res) {
            LOG_ERROR(GPS, "EcorrErr");
        }
        res = gnss_correlation_i8_iq(GeneratedPrnSample, &Node->SignalI[offset_present], &Node->SignalQ[offset_present],
                                     ONE_PRN_SAMPLE_CNT, &EplNode->Present) &&
              res;
        if(false == res) {
            LOG_ERROR(GPS, "PcorrErr");
        }
        res = gnss_correlation_i8_iq(GeneratedPrnSample, &Node->SignalI[offset_late], &Node->SignalQ[offset_late],
                                     ONE_PRN_SAMPLE_CNT, &EplNode->Late) &&
              res;
        if(false == res) {
            LOG_ERROR(GPS, "LcorrErr");
        }

        // LOG_DEBUG(DLL, "%s", SdrEplToStr(EplNode));
    } else {
        res = false;
        LOG_ERROR(GPS, "InErr");
    }

    return res;
}

bool gps_calc_best_lo_phase(GpsHandle_t* Node, int prn, LocalOscillatorHandle_t* Oscillator, int32_t lo_fl_freq_hz,
                            int8_t* TwoPrnSampleData, int32_t EplOfftestStep, int8_t* GeneratedPrnSample,
                            SdrEPL_t* CorrBest) {
    bool res = false;
    LOG_DEBUG(GPS, "CalcBestLo");

    if(Node) {
        if(Oscillator) {
            if(TwoPrnSampleData) {
                if(CorrBest) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;

        // GnssEscortInfo_t EscortInfo = { 0 };

        // calc best LO phase

        SdrEPL_t CorrCur = {0};

        CorrCur.carr_phase_err_deg = 0;

        CorrBest->carr_phase_err_deg = 0;

        int32_t lo_phase_deg = 0;
        for(lo_phase_deg = -90; lo_phase_deg <= 270; lo_phase_deg += 90) {
            LOG_DEBUG(DLL, "TryPhase %d deg", lo_phase_deg);
            CorrCur.lo_phase_deg = lo_phase_deg;
            Oscillator->phase_deg = lo_phase_deg;
            Oscillator->frequency_hz = lo_fl_freq_hz;
            Oscillator->size = TWO_PRN_SAMPLE_CNT;

            res = sdr_generate_local_oscilator_signals(Oscillator);
            if(res) {
                res = false;
                res = gps_mix_lo_signal(Node, prn, TwoPrnSampleData, TWO_PRN_SAMPLE_CNT);
                if(res) {
                    res = false;

                    res = gnss_epl_calc(Node, EplOfftestStep, GeneratedPrnSample, &CorrCur);
                    if(res) {
                        res = false;
                        float carr_phase_err_deg = 0.0;
                        float carr_phase_err_rad = 0.0;
                        carr_phase_err_rad = calc_carrier_phase_err_rad(CorrCur.Present.correlation_i,
                                                                        CorrCur.Present.correlation_q); // origin code
                        carr_phase_err_deg = rad_to_deg_f(carr_phase_err_rad);
                        LOG_DEBUG(DLL, "PhaseErr %f Deg", carr_phase_err_deg);
                        if(abs(carr_phase_err_deg) <= abs(CorrBest->carr_phase_err_deg)) {
                            LOG_DEBUG(DLL, "SplotPhaseErr %f Deg", carr_phase_err_deg);
                            memcpy(CorrBest, &CorrCur, sizeof(SdrEPL_t));
                            res = true;
                        }
                    } else {
                        res = false;
                        LOG_ERROR(GPS, "CalcEplErr");
                    }

                } else {
                    LOG_ERROR(GPS, "LoDataMixErr");
                    res = false;
                }
            } else {
                res = false;
                LOG_ERROR(GPS, "LOerr");
            }
        }
        if(false == res) {
            res = true;
            memcpy(CorrBest, &CorrCur, sizeof(SdrEPL_t));
        }
    } else {
        res = false;
        LOG_ERROR(GPS, "InErr");
    }

    return res;
}

static bool gps_calc_epl_v1(GpsHandle_t* Node, int prn, LocalOscillatorHandle_t* Oscillator, double lo_fl_freq_hz,
                            int8_t* TwoPrnSampleData, int32_t EplOfftestStep, int8_t* GeneratedPrnSample,
                            SdrEPL_t* CorrBest) {
    bool res = false;
    LOG_DEBUG(GPS, "CalcBestLo");

    if(Node) {
        if(Oscillator) {
            if(TwoPrnSampleData) {
                if(CorrBest) {
                    res = true;
                }
            }
        }
    }

    if(res) {
        res = false;

        // GnssEscortInfo_t EscortInfo = { 0 };

        // calc best LO phase

        // SdrEPL_t CorrCur = { 0 };

        //    CorrCur.carr_phase_err_deg = 0;

        CorrBest->carr_phase_err_deg = 0;

        CorrBest->lo_phase_deg = Oscillator->phase_deg;
        Oscillator->frequency_hz = lo_fl_freq_hz;
        Oscillator->size = TWO_PRN_SAMPLE_CNT;

        res = sdr_generate_local_oscilator_signals(Oscillator);
        if(res) {
            res = gps_mix_lo_signal(Node, prn, TwoPrnSampleData, TWO_PRN_SAMPLE_CNT);
            if(res) {
                res = false;

                res = gnss_epl_calc(Node, EplOfftestStep, GeneratedPrnSample, CorrBest);
                if(res) {

                } else {
                    res = false;
                    LOG_ERROR(GPS, "CalcEplErr");
                }

            } else {
                LOG_ERROR(GPS, "LoDataMixErr");
                res = false;
            }
        } else {
            res = false;
            LOG_ERROR(GPS, "LOerr");
        }

        res = true;

    } else {
        res = false;
        LOG_ERROR(GPS, "InErr");
    }

    return res;
}

#define PRN_CORRELATION_THRESHOLD 931 // 856 880
bool gps_prn_convolution(uint8_t num, int prn) {
    bool res = false;
    LOG_INFO(GPS, "EscortPRN:%d", prn);
    const GpsConfig_t* Config = GpsGetConfig(num);
    if(Config) {
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            GpsSat_t* SatConfig = GpsGetSatConfig(Config->SatS, Config->sat_cnt, prn);
            if(SatConfig) {
                LOG_INFO(GPS, "EscortSat File:[%s],SamPerChip:%f Sam", Config->file_name, Node->sample_per_chip);
                LOG_INFO(GPS, "%s", GpsSatToStr(SatConfig));

                int8_t GeneratedPrnSample[ONE_PRN_SAMPLE_CNT] = {0};
                // memset(GeneratedPrnSample, 0, sizeof(GeneratedPrnSample));
                res = gps_generate_prn_samples(prn, GeneratedPrnSample, Node->sample_per_chip);

                Node->size_bytes = file_pc_get_size(Config->file_name);

                char conv_file_name[300] = "";
                snprintf(conv_file_name, sizeof(conv_file_name), "Conv_PRN%d_Dopler_%d_Hz_ABS_%u.csv", prn,
                         SatConfig->doppler_offset_hz, PRN_CORRELATION_THRESHOLD);
                FILE* ConvFilePtr = fopen(conv_file_name, "w");
                if(ConvFilePtr) {
                    LOG_INFO(GPS, "OpenOkFile:[%s]", conv_file_name);
                } else {
                    LOG_ERROR(GPS, "OpenFileErr:[%s]", conv_file_name);
                    return false;
                }

                LOG_INFO(GPS, "OpenOkFile:[%s]", Config->file_name);
                Node->sample_cnt = Node->size_bytes;
                uint32_t sample_to_proc = Node->sample_cnt / ONE_PRN_SAMPLE_CNT;
                LOG_INFO(GPS, "PRN:%u PRNs", sample_to_proc);
                Node->duration_s = (double)Node->sample_cnt / Node->adc_sample_rate_hz;
                LOG_INFO(GPS, "Size:%d bytes,Samples:%u,Duration:%f s", Node->size_bytes, Node->sample_cnt,
                         Node->duration_s);

                // int32_t cur_doppler_freq_offset_hz=0;
                LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(prn);
                if(Oscillator) {
                    Oscillator->phase_deg = 0;
                    double lo_fl_freq_hz = 0;
                    lo_fl_freq_hz = (double)(Node->intermediate_freq_hz + SatConfig->doppler_offset_hz);
                    Oscillator->frequency_hz = (int32_t)lo_fl_freq_hz;
                    res = sdr_generate_local_oscilator_signals(Oscillator);
                } else {
                    LOG_ERROR(GPS, "LoErr");
                }

                if(Node->size_bytes) {
                    int8_t PrnSampleData[ONE_PRN_SAMPLE_CNT] = {0};
                    int32_t s = 0;
                    SdrCorrRes_t CorrResPrev = {0};
                    for(s = 0; s < (Node->sample_cnt - ONE_PRN_SAMPLE_CNT); s++) {
                        double up_time_s = ((double)s) / ((double)Node->adc_sample_rate_hz);
                        memset(PrnSampleData, 0, sizeof(PrnSampleData));
                        res = file_pc_load_to_array_i8(Config->file_name, (size_t)s, PrnSampleData, ONE_PRN_SAMPLE_CNT);
                        if(res) {
                            LOG_DEBUG(GPS, "Proc %s", ProgressToStr(s, Node->sample_cnt));
                            res = gps_mix_lo_signal(Node, prn, PrnSampleData, ONE_PRN_SAMPLE_CNT);
                            if(res) {
                                SdrCorrRes_t CorrRes = {0};
                                res = gnss_correlation_i8_iq(GeneratedPrnSample, &Node->SignalI[0], &Node->SignalQ[0],
                                                             ONE_PRN_SAMPLE_CNT, &CorrRes);
                                if(res) {
                                    if(PRN_CORRELATION_THRESHOLD < CorrRes.abs) {
                                        if(CorrRes.abs < CorrResPrev.abs) {
                                            char text[300] = "";
                                            strcpy(text, "");
                                            snprintf(text, sizeof(text), "%s%s,", text,
                                                     ProgressToStr(s, Node->sample_cnt));
                                            snprintf(text, sizeof(text), "%s%s s,", text, DoubleToStr(up_time_s)); // 0
                                            snprintf(text, sizeof(text), "%sS:%5d,", text, s);
                                            snprintf(text, sizeof(text), "%sPha:%5d,", text, s % ONE_PRN_SAMPLE_CNT);
                                            snprintf(text, sizeof(text), "%s%s", text, SdrCorrToStr(&CorrResPrev));

                                            log_level_t level = LOG_LEVEL_INFO;
                                            if(CorrResPrev.abs < CorrRes.abs) {
                                                level = LOG_LEVEL_WARNING;
                                            } else {
                                                level = LOG_LEVEL_NOTICE;
                                            }

                                            log_write(level, GPS, "%s", text);
                                            if(ConvFilePtr) {
                                                strcpy(text, "");
                                                snprintf(text, sizeof(text), "%s%f,", text, up_time_s); // 0
                                                snprintf(text, sizeof(text), "%s%d,", text, s);
                                                snprintf(text, sizeof(text), "%s%d,", text, s % ONE_PRN_SAMPLE_CNT);
                                                snprintf(text, sizeof(text), "%s%d,", text, CorrResPrev.abs);
                                                snprintf(text, sizeof(text), "%s%f,", text, CorrResPrev.arg);
                                                snprintf(text, sizeof(text), "%s%d,", text, CorrResPrev.correlation_i);
                                                snprintf(text, sizeof(text), "%s%d,", text, CorrResPrev.correlation_q);

                                                fprintf(ConvFilePtr, " %s\n", text);
                                            }
                                        }
                                    }

                                    CorrResPrev = CorrRes;
                                }
                            } else {
                                LOG_ERROR(GPS, "%dMixErr", s);
                            }
                        } else {
                            // file_pc_load_to_array_i8_ll
                            LOG_ERROR(GPS, "LoadSamErr Offset:%d byte", s);
                            break;
                        }
                    } // time
                }
                ////
                fclose(ConvFilePtr);
            } else {
                LOG_ERROR(GPS, "PRN%u SatErr", prn);
            }
        } else {
            LOG_ERROR(GPS, "GPS%u NodeErr", num);
        }
    } else {
        LOG_ERROR(GPS, "GPS%u ConfigErr", num);
    }
    return res;
}

#define MAX_PRN_SHIFT_DOPPLER_HZ 200
#define MAX_PRN_SHIFT_PHASE_SAMPLES 60

bool gps_escort_sat(uint8_t num, int prn) {
    bool res = false;
    const GpsConfig_t* Config = GpsGetConfig(num);
    if(Config) {
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            GpsSat_t* SatConfig = GpsGetSatConfig(Config->SatS, Config->sat_cnt, prn);
            if(SatConfig) {
                LOG_INFO(GPS, "EscortSat File:[%s],SamPerChip:%uSam", Config->file_name, Node->sample_per_chip);
                LOG_INFO(GPS, "%s", GpsSatToStr(SatConfig));

                int8_t GeneratedPrnSample[ONE_PRN_SAMPLE_CNT] = {0};
                // memset(GeneratedPrnSample, 0, sizeof(GeneratedPrnSample));
                res = gps_generate_prn_samples(prn, GeneratedPrnSample, Node->sample_per_chip);

                Node->size_bytes = file_pc_get_size(Config->file_name);
                Node->FilePtr = fopen(Config->file_name, "rb");
                if(Node->FilePtr) {
                    LOG_INFO(GPS, "OpenOkFile:[%s]", Config->file_name);
                    Node->sample_cnt = Node->size_bytes;
                    uint32_t sample_to_proc = Node->sample_cnt / ONE_PRN_SAMPLE_CNT;
                    LOG_INFO(GPS, "PRN:%u PRNs", sample_to_proc);
                    Node->duration_s = (double)Node->sample_cnt / Node->adc_sample_rate_hz;
                    LOG_INFO(GPS, "Size:%d bytes,Samples:%u,Duration:%f s", Node->size_bytes, Node->sample_cnt,
                             Node->duration_s);

                    // int32_t cur_doppler_offset=  SatConfig->doppler_offset_hz;
                    // int32_t cur_phase = SatConfig->init_prn_phase_sample;
                    int32_t cur_doppler_freq_offset_hz = 0;
                    int32_t s = 0;
                    if(Node->size_bytes) {
                        int8_t TwoPrnSampleData[TWO_PRN_SAMPLE_CNT] = {0};
                        GnssEscortInfo_t EscortInfo = {0};
                        EscortInfo.doppler_offset_hz = SatConfig->doppler_offset_hz;
                        EscortInfo.prn_phase_sample = SatConfig->init_prn_phase_sample;
                        EscortInfo.prn = prn;
                        size_t t = 0;
                        for(t = 0; t < sample_to_proc; t++) {
                            EscortInfo.correlation_value = 0;
                            size_t offset = 0;
                            EscortInfo.time_sample = offset;
                            offset = t * ONE_PRN_SAMPLE_CNT;
                            res = file_pc_load_to_array_i8_ll(Node->FilePtr, offset, TwoPrnSampleData,
                                                              sizeof(TwoPrnSampleData));
                            if(res) {
                                LOG_DEBUG(GPS, "Proc %u/%u Sam", t, sample_to_proc);
                                int32_t dopp_offset_min = EscortInfo.doppler_offset_hz - MAX_PRN_SHIFT_DOPPLER_HZ;
                                int32_t dopp_offset_max = EscortInfo.doppler_offset_hz + MAX_PRN_SHIFT_DOPPLER_HZ;
                                for(cur_doppler_freq_offset_hz = dopp_offset_min;
                                    cur_doppler_freq_offset_hz <= dopp_offset_max; cur_doppler_freq_offset_hz += 2) {
                                    // LOG_DEBUG(GPS, "Doppler:%d Hz", cur_doppler_freq_offset_hz);

                                    int32_t lo_fl_freq_hz = 0;
                                    lo_fl_freq_hz = Node->intermediate_freq_hz + cur_doppler_freq_offset_hz;

                                    LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(prn);
                                    if(Oscillator) {
                                        Oscillator->frequency_hz = lo_fl_freq_hz;
                                        Oscillator->size = TWO_PRN_SAMPLE_CNT;
                                        res = sdr_generate_local_oscilator_signals(Oscillator);
                                    }

                                    int32_t phase_min = EscortInfo.prn_phase_sample - MAX_PRN_SHIFT_PHASE_SAMPLES;
                                    int32_t phase_max = EscortInfo.prn_phase_sample + MAX_PRN_SHIFT_PHASE_SAMPLES;
                                    for(s = phase_min; s <= phase_max; s += 1) {
                                        // LOG_DEBUG(GPS, "Phase:%d Sam", s);
                                        if(0 < s) {
                                            res = gps_mix_lo_signal(Node, prn, TwoPrnSampleData, TWO_PRN_SAMPLE_CNT);

                                            SdrCorrRes_t Corr = {0};
                                            res = gnss_correlation_i8_iq(GeneratedPrnSample, &Node->SignalI[s],
                                                                         &Node->SignalQ[s], ONE_PRN_SAMPLE_CNT, &Corr);

                                            int32_t corr_res = MAX(abs(Corr.correlation_i), abs(Corr.correlation_q));
                                            if(EscortInfo.correlation_value < corr_res) {
                                                EscortInfo.correlation_value = corr_res;
                                                EscortInfo.doppler_offset_hz = cur_doppler_freq_offset_hz;
                                                EscortInfo.prn_phase_sample = s;
                                            }
                                            // cli_printf("\rDoppler:%d Hz,Phase %u
                                            // Sam,Corr:%d",cur_doppler_freq_offset_hz,s,corr_res);
                                        } else {
                                            LOG_ERROR(GPS, "TryNegativePhaseErr Phase:%s", s);
                                        }
                                    } // phase

                                } // freq
                            } else {
                                // file_pc_load_to_array_i8_ll
                                LOG_ERROR(GPS, "Load2prnErr");
                            }

                            LOG_INFO(GPS, "%u/%u,%s", t, sample_to_proc, EscortInfoToStr(&EscortInfo));
                        } // time
                    }
                    ////
                    fclose(Node->FilePtr);
                } else {
                    LOG_ERROR(GPS, "OpenErrFile:[%s]", Config->file_name);
                    res = false;
                }
            } else {
                LOG_ERROR(GPS, "PRN%u SatErr", prn);
            }
        } else {
            LOG_ERROR(GPS, "GPS%u NodeErr", num);
        }
    } else {
        LOG_ERROR(GPS, "GPS%u ConfigErr", num);
    }
    return res;
}

bool gps_escort_sat_epl(uint8_t num, int prn) {
    bool res = false;
    LOG_INFO(GPS, "EscortPRN:%d", prn);
    const GpsConfig_t* Config = GpsGetConfig(num);
    if(Config) {
        GpsHandle_t* Node = GpsGetNode(num);
        if(Node) {
            GpsSat_t* SatConfig = GpsGetSatConfig(Config->SatS, Config->sat_cnt, prn);
            if(SatConfig) {
                LOG_INFO(GPS, "EscortSat File:[%s],SamPerChip:%f Sam", Config->file_name, Node->sample_per_chip);
                LOG_INFO(GPS, "%s", GpsSatToStr(SatConfig));

                int8_t GeneratedPrnSample[ONE_PRN_SAMPLE_CNT] = {0};
                // memset(GeneratedPrnSample, 0, sizeof(GeneratedPrnSample));
                res = gps_generate_prn_samples(prn, GeneratedPrnSample, Node->sample_per_chip);

                Node->size_bytes = file_pc_get_size(Config->file_name);

                char escort_file_name[300] = "";
                snprintf(escort_file_name, sizeof(escort_file_name), "Track_PRN%d.csv", prn);
                FILE* EscortFilePtr = fopen(escort_file_name, "w");
                if(EscortFilePtr) {
                    LOG_INFO(GPS, "OpenOkFile:[%s]", escort_file_name);
                } else {
                    LOG_ERROR(GPS, "OpenFileErr:[%s]", escort_file_name);
                    return false;
                }

                LOG_INFO(GPS, "OpenOkFile:[%s]", Config->file_name);
                Node->sample_cnt = Node->size_bytes;
                uint32_t sample_to_proc = Node->sample_cnt / ONE_PRN_SAMPLE_CNT;
                LOG_INFO(GPS, "PRN:%u PRNs", sample_to_proc);
                Node->duration_s = (double)Node->sample_cnt / Node->adc_sample_rate_hz;
                LOG_INFO(GPS, "Size:%d bytes,Samples:%u,Duration:%f s", Node->size_bytes, Node->sample_cnt,
                         Node->duration_s);

                // int32_t cur_doppler_freq_offset_hz=0;
                LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(prn);

                if(Node->size_bytes) {
                    int8_t TwoPrnSampleData[TWO_PRN_SAMPLE_CNT] = {0};
                    GnssEscortInfo_t EscortInfo = {0};
                    EscortInfo.adc_sample_rate_hz = Node->adc_sample_rate_hz;
                    EscortInfo.doppler_offset_hz = SatConfig->doppler_offset_hz;
                    EscortInfo.prn_phase_sample = SatConfig->init_prn_phase_sample;
                    EscortInfo.prn = prn;
                    double lo_fl_freq_hz = 0.0;
                    lo_fl_freq_hz = (double)(Node->intermediate_freq_hz + SatConfig->doppler_offset_hz);

                    int32_t s_early = 0;
                    int32_t EplOfftestStep = 8; // 1 15
                    EplOfftestStep = Node->sample_per_chip / 2;
                    LOG_INFO(GPS, "EPLStep:%u Sam", EplOfftestStep);
                    EscortInfo.time_sample = EscortInfo.prn_phase_sample;

                    double prev_lo_phase_deg = 0;
                    s_early = (EscortInfo.prn_phase_sample - EplOfftestStep);

                    int32_t tune_prev = 0;
                    int32_t tune_prev_prev = 0;
                    bool next_prn = false;
                    while((0 <= s_early) && (s_early < Node->sample_cnt)) {
                        next_prn = false;
                        int32_t tune = 0;
                        int32_t tune_best = 0;
                        EscortInfo.correlation_value = 0;
                        EscortInfo.prn_cnt = s_early / ONE_PRN_SAMPLE_CNT;
                        EscortInfo.time_sample = EscortInfo.prn_cnt * ONE_PRN_SAMPLE_CNT;

                        EscortInfo.prn_phase_sample = (s_early + EplOfftestStep) % ONE_PRN_SAMPLE_CNT;
                        // int32_t cur_prn_phase_sample=(s + EplOfftestStep)%ONE_PRN_SAMPLE_CNT;
                        EscortInfo.time_s = ((double)EscortInfo.time_sample) / Node->adc_sample_rate_hz;
                        memset(TwoPrnSampleData, 0, sizeof(TwoPrnSampleData));
                        res = file_pc_load_to_array_i8(Config->file_name, (size_t)s_early, TwoPrnSampleData,
                                                       sizeof(TwoPrnSampleData));
                        if(res) {
                            LOG_DEBUG(GPS, "Proc:%s", ProgressToStr(s_early, Node->sample_cnt));
                            /*Seek doppler offset*/

                            SdrEPL_t CorrBest = {0};
                            CorrBest.carr_phase_err_deg = 180.0;

                            EscortInfo.doppler_offset_hz = lo_fl_freq_hz - Node->intermediate_freq_hz;

                            // cli_printf("NonCohFilt:%3.2f,tune:%d"CRLF,EscortInfo.filt_noncoherent,tune);.
                            /*Tune frequency*/

                            res = gps_calc_epl_v1(Node, prn, Oscillator, lo_fl_freq_hz, TwoPrnSampleData,
                                                  EplOfftestStep, GeneratedPrnSample, &CorrBest);
                            if(false == res) {
                                LOG_ERROR(GPS, "gps_calc_epl_v1Err");
                                break;
                            }

                            res = dll_loop(&CorrBest, &tune, &EscortInfo.noncoherent, &EscortInfo.filt_noncoherent);
                            if(0 != tune) {
                                tune_best = tune;
                            }

                            // EscortInfo.prn_phase_sample += tune_best;
                            EscortInfo.doppler_offset_hz = ((int32_t)lo_fl_freq_hz) - Node->intermediate_freq_hz;
                            EscortInfo.correlation_value = CorrBest.Present.abs;
                            // cli_printf("\r%s,%s",ProgressToStr(s,Node->sample_cnt),EscortInfoToStr(&EscortInfo));

                            res = epl_verify(&CorrBest);
                            if(res) {
                                // double time_s = (((double)s) * 1.0) / Node->adc_sample_rate_hz;
                                LOG_WARNING(GPS, "Time:%f s,LostPRN AtPhase %u Sample", EscortInfo.time_s,
                                            EscortInfo.prn_phase_sample);

                                uint32_t phase_offset_sample_start = 0;
                                uint32_t phase_offset_sample_end = 1023 * 16 - 1;
                                uint32_t phase_offset_sample = 0;
                                res = gps_capture_prn(num, prn, EscortInfo.time_s, phase_offset_sample_start,
                                                      phase_offset_sample_end, &phase_offset_sample,
                                                      (int32_t)EscortInfo.doppler_offset_hz);
                                if(res) {
                                    s_early = EscortInfo.time_sample + phase_offset_sample - EplOfftestStep;
                                    LOG_WARNING(GPS, "Restore Phase %u sample", phase_offset_sample);
                                    EscortInfo.prn_phase_sample = (int32_t)phase_offset_sample;
                                    // lo_fl_freq_hz = Node->intermediate_freq_hz + SatConfig->doppler_offset_hz;
                                } else {
                                    LOG_ERROR(GPS, "RestorePhase Error");
                                    break;
                                }
                            }

                            res = is_double_equal_absolute(EscortInfo.noncoherent, 0.0, HONCOHERENT_ERROR);
                            if(res) {
                                next_prn = true;
                            } else {
                                res = true;
                                if(tune_prev == (-tune_best)) {
                                    if(tune_prev_prev == (-tune_prev)) {
                                        LOG_DEBUG(DLL, "hangOnLoop");
                                        tune_prev = 0;
                                        tune_prev_prev = 0;
                                        res = false;
                                        next_prn = true;
                                    }
                                }

                                if(res) {
                                    tune_prev_prev = tune_prev;
                                    tune_prev = tune_best;
                                }

                                s_early += tune_best;
                            }

                            if(next_prn) {
                                /*Here we have best PRN phase*/
                                char text[200] = "";
                                snprintf(text, sizeof(text), "%s%s,", text, ProgressToStr(s_early, Node->sample_cnt));
                                snprintf(text, sizeof(text), "%s%s", text, EscortInfoToStr(&EscortInfo));
                                // snprintf(text,sizeof(text),"%sI:%3d,",text,CorrBest.Present.correlation_i);
                                // snprintf(text,sizeof(text),"%sQ:%3d,",text,CorrBest.Present.correlation_q);
                                snprintf(text, sizeof(text), "%sA:%4d,", text, CorrBest.Present.abs);
                                snprintf(text, sizeof(text), "%sD:%4d,", text,
                                         (int32_t)rad_2_deg(CorrBest.Present.arg));
                                snprintf(text, sizeof(text), "%sLOP:%3d Deg,", text,
                                         ((int)CorrBest.lo_phase_deg) % 360);
                                float carr_pha_diff_deg = (float)(CorrBest.lo_phase_deg - prev_lo_phase_deg);
                                snprintf(text, sizeof(text), "%sLOphaDiff:%3.0f Deg,", text, carr_pha_diff_deg);
                                /// snprintf(text,sizeof(text),"%sBestDop:%d Hz,",text,EscortInfo.doppler_offset_hz);
                                LOG_INFO(GPS, "%s", text);

                                double up_time_s =
                                    ((double)EscortInfo.time_sample) / ((double)Node->adc_sample_rate_hz);
                                if(EscortFilePtr) {
                                    fprintf(EscortFilePtr, "%f,%f,%d,%d,%d,%d,%f,%f\n", up_time_s,
                                            EscortInfo.doppler_offset_hz, EscortInfo.prn_phase_sample,
                                            CorrBest.Present.abs, CorrBest.Present.correlation_i,
                                            CorrBest.Present.correlation_q, CorrBest.lo_phase_deg, carr_pha_diff_deg);
                                }
                                prev_lo_phase_deg = CorrBest.lo_phase_deg;
                                s_early += ONE_PRN_SAMPLE_CNT;
                                /*PLL*/
                                double carr_freq_tune_hz = 0.0;
                                res = pll_loop(&CorrBest.Present, &CorrBest.carr_phase_err_deg, &carr_freq_tune_hz);
                                LOG_PARN(PLL, "LOphase:%f Deg,CarrPhaErr:%f deg", Oscillator->phase_deg,
                                         CorrBest.carr_phase_err_deg);

                                lo_fl_freq_hz += carr_freq_tune_hz;
                                CorrBest.lo_phase_deg = Oscillator->phase_deg;
                                // lo_fl_freq_hz += PLL_FLL_CONST * CorrBest.carr_phase_err_deg;
                                // Oscillator->phase_deg -= CorrBest.carr_phase_err_deg/2.0 +
                                // rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                double k_rad_m = 2.0 * M_PI / L1_WAVE_LEN;
                                double V_sv_ms = 0.0;

                                double doppler_offset_hz = lo_fl_freq_hz - Node->intermediate_freq_hz;

                                V_sv_ms = FrxToV(FREQ_L1_HZ, doppler_offset_hz);

                                double dist_m = -PRN_DURATION_S * V_sv_ms;
                                double kx_rad = -k_rad_m * dist_m;
                                double kx_deg = rad_2_deg(kx_rad);
                                (void)kx_deg;
                                Oscillator->phase_deg = 0.0;
                                // Oscillator->phase_deg -= carr_phase_tune_deg +
                                // PRN_DURATION_S*lo_fl_freq_hz*rad_2_deg(2.0*M_PI)  +kx_deg;

#if 0
                                //4 dot shape X
                                 //Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + PRN_DURATION_S*lo_fl_freq_hz*rad_2_deg(2.0*M_PI)  +kx_deg;
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg  +kx_deg;
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz)+kx_deg;
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + 1.5*rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
     // 4 dot +
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz)/90.0;
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz)/45.0;
                                Oscillator->phase_deg += carr_phase_tune_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz)+45.0;
                                Oscillator->phase_deg += CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                Oscillator->phase_deg += CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz); // 4 dot
                                //Oscillator->phase_deg += CorrBest.carr_phase_err_deg;// 4 +
#endif

#if 0
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg*2 + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                //circle
                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg/4.0 + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);

                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + PRN_DURATION_S*lo_fl_freq_hz*rad_2_deg(2.0*M_PI)  ;
                                Oscillator->phase_deg += CorrBest.carr_phase_err_deg/10.0 + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                lo_fl_freq_hz += PLL_FLL_CONST * CorrBest.carr_phase_err_deg;


                                Oscillator->phase_deg = CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                lo_fl_freq_hz += PLL_FLL_CONST * CorrBest.carr_phase_err_deg;

                                Oscillator->phase_deg -= CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                Oscillator->phase_deg += -carr_phase_tune_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                Oscillator->phase_deg += carr_phase_tune_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                Oscillator->phase_deg += CorrBest.carr_phase_err_deg/4.0 + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                Oscillator->phase_deg += -CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
                                Oscillator->phase_deg = carr_phase_tune_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);//ci
                                // Oscillator->phase_deg += carr_phase_tune_deg;
                                // CorrBest.carr_phase_err_deg = Oscillator->phase_deg;
                                // Oscillator->phase_deg = CorrBest.carr_phase_err_deg + rad_2_deg(PRN_DURATION_S*2.0*M_PI*lo_fl_freq_hz);
#endif

                                // freq_tune_verify(FLL_CONST * CorrBest.carr_phase_err_deg, &freq_tune_fixed);
                                double freq_tune_hz = 0.0;
                                res = fll_loop(&CorrBest.Present, &PrevPRNPresent, &freq_tune_hz);
                                // freq_tune must be less that 1Hz/s
                                // double freq_tune_fixed = freq_tune;
                                //  freq_tune_verify(freq_tune, &freq_tune_fixed);
                                lo_fl_freq_hz -= freq_tune_hz;
                                memcpy(&PrevPRNPresent, &CorrBest.Present, sizeof(SdrCorrRes_t));
                            }

                        } else {
                            // file_pc_load_to_array_i8_ll
                            LOG_ERROR(GPS, "Load2prnErr Offset:%d byte", s_early);
                            break;
                        }
                        // LOG_INFO(GPS,"%u/%u,%s",s,s<Node->sample_cnt,EscortInfoToStr(&EscortInfo));
                    } // time while(s
                }
                ////
                fclose(EscortFilePtr);
                fclose(Node->FilePtr);

            } else {
                LOG_ERROR(GPS, "PRN%u SatErr", prn);
            }
        } else {
            LOG_ERROR(GPS, "GPS%u NodeErr", num);
        }
    } else {
        LOG_ERROR(GPS, "GPS%u ConfigErr", num);
    }
    return res;
}

#define BITS_IN_PRN (1023 * 16)

bool gps_capture_prn(uint8_t num, int32_t prn, double time_s, uint32_t phase_offset_sample_start,
                     uint32_t phase_offset_sample_end, uint32_t* const phase_offset_sample,
                     int32_t doppler_freq_offset_hz) {
    bool res = false;
    GpsSat_t* SatConfig = NULL;
    LOG_INFO(GPS, "GPS_%u,PRN:%d,Time:%f s", num, prn, time_s);
    const GpsConfig_t* Config = GpsGetConfig(num);
    GpsHandle_t* Node = GpsGetNode(num);
    if(Config) {
        if(Node) {
            SatConfig = GpsGetSatConfig(Config->SatS, Config->sat_cnt, prn);
            if(SatConfig) {
                LOG_INFO(GPS, "%s", GpsSatToStr(SatConfig));
                LOG_INFO(GPS, "SampleRate:%f Hz", Config->adc_sample_rate_hz);
                if(phase_offset_sample) {
                    res = histogram_init_one(Node->histogram_num);
                }
            }
        }
    }

    if(res) {
        Node->FilePtr = fopen(Config->file_name, "rb");
        if(Node->FilePtr) {
            LOG_INFO(GPS, "FileOpen:%s ", Config->file_name);

            // int32_t doppler_freq_offset_hz = SatConfig->doppler_offset_hz;

            int32_t lo_fl_freq_hz = Node->intermediate_freq_hz + doppler_freq_offset_hz;

            int8_t TwoPrnSampleData[TWO_PRN_SAMPLE_CNT] = {0};
            double sample_time = 1.0 / Config->adc_sample_rate_hz;
            LOG_INFO(GPS, "SampleTime:%f s", sample_time);

            int32_t time_range = 0.2 / sample_time;

            int32_t time_middle = time_s / sample_time;
            LOG_INFO(GPS, "Time:%f s=%u Sample,Range:%u sample", time_s, time_middle, time_range);
            Node->prn_phase_seek_start_sample = phase_offset_sample_start;
            Node->prn_phase_seek_end_sample = phase_offset_sample_end;

            int32_t time_start = time_middle - time_range;
            int32_t time_end = time_middle + time_range;
            int32_t time_sample = 0;

            LocalOscillatorHandle_t* Oscillator = LocalOscillatorGetNode(prn);
            if(Oscillator) {
                Oscillator->frequency_hz = lo_fl_freq_hz;
                res = sdr_generate_local_oscilator_signals(Oscillator);
            } else {
                LOG_ERROR(GPS, "NoLoForPRN%d", prn);
                return;
            }

            for(time_sample = time_start; time_sample < time_end; time_sample += sizeof(TwoPrnSampleData)) {
                double cur_time_s = ((double)time_sample) * sample_time;
                res =
                    file_pc_load_to_array_i8_ll(Node->FilePtr, time_sample, TwoPrnSampleData, sizeof(TwoPrnSampleData));
                if(res) {
                    PrnInfo_t CurPrn = {0};
                    CurPrn.prn = prn;
                    res = GpsProcTwoPrn(Node, TwoPrnSampleData, sizeof(TwoPrnSampleData), prn, doppler_freq_offset_hz,
                                        &CurPrn);
                    if(res) {
#ifdef HAS_HISTOGRAM
                        res = histogram_add(Node->histogram_num, (int32_t)CurPrn.Max.offset_samples);
#endif
                    } else {
                        LOG_ERROR(GPS, "ProcErr");
                    }
                } else {
                    LOG_ERROR(GPS, "LoadTwoPRNErr");
                }
                HistogramItem_t Item = {0};
#ifdef HAS_HISTOGRAM
                res = histogram_get_max(Node->histogram_num, &Item);
                LOG_DEBUG(GPS, "Time:%7.3f s,%s", cur_time_s, HistogramItemToStr(&Item));
#endif
                if(2 < Item.frequency) {
                    *phase_offset_sample = Item.index;
                    res = true;
                }
            }
            fclose(Node->FilePtr);
        } else {
            LOG_ERROR(GPS, "FileOpenErr");
        }
    }
    return res;
}

bool gps_prn_autocorrelation(uint8_t num, int prn) {
    bool res = false;

    GpsHandle_t* Node = GpsGetNode(num);
    if(Node) {
        LOG_INFO(GPS, "NodeOk");
        int8_t GeneratedPrnSample[ONE_PRN_SAMPLE_CNT] = {0};
        memset(GeneratedPrnSample, 0, sizeof(GeneratedPrnSample));
        res = gps_generate_prn_samples(prn, GeneratedPrnSample, Node->sample_per_chip);
        int8_t Signal[3 * ONE_PRN_SAMPLE_CNT] = {0};

        memcpy(&Signal[0], GeneratedPrnSample, ONE_PRN_SAMPLE_CNT);
        memcpy(&Signal[ONE_PRN_SAMPLE_CNT], GeneratedPrnSample, ONE_PRN_SAMPLE_CNT);
        memcpy(&Signal[2 * ONE_PRN_SAMPLE_CNT], GeneratedPrnSample, ONE_PRN_SAMPLE_CNT);

        if(res) {
            int32_t s = 0;
            for(s = 0; s <= 2 * ONE_PRN_SAMPLE_CNT; s++) {
                SdrCorrRes_t CorrRes = {0};
                res = gnss_correlation_i8_iq(GeneratedPrnSample, &Signal[s], &Signal[s], ONE_PRN_SAMPLE_CNT, &CorrRes);
                if(res) {
                    char text[300] = "";
                    strcpy(text, "");
                    snprintf(text, sizeof(text), "%sS:%5d,", text, s);
                    snprintf(text, sizeof(text), "%s%s", text, SdrCorrToStr(&CorrRes));
                    log_write(LOG_LEVEL_NOTICE, GPS, "%s", text);
                }
            }
        }
    }
    return res;
}

COMPONENT_INIT_PATTERT(GPS, GPS, gps)

COMPONENT_PROC_PATTERT(GPS, GPS, gps)
