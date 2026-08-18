#include "sonar_commands.h"

#include "string.h"

#include "convert.h"
#include "log.h"
#include "physics_const.h"
#include "sonar.h"
#include "sonar_diag.h"

/*sonar_chirp_correlation 1 CHIRP_450_10000_dt50_A1000.wav*/
bool sonar_chirp_correlation_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char rec_file_name[150] = "";

    if(0 == argc) {
        res = true;
    } else {
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        strcpy(rec_file_name, argv[1]);
        res = true;
    }

    if(res) {
#ifdef HAS_CORRELATOR_S16
        res = sonar_calc_correlation(num, rec_file_name);
        log_info_res(SONAR, res, "ChirpCorrelation");
#endif
    } else {
        LOG_ERROR(SONAR, "Usage: scc Num RecWavFile");
    }
    return res;
}

bool cmd_sonar_diag(int32_t argc, char* argv[]) {
    bool res = false;
    if(0 == argc) {
        res = true;
    } else {
        LOG_ERROR(SONAR, "Usage: sd");
    }

    res = sonar_diag();
    return res;
}

bool sonar_plot_convolution_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t y_col = 0;
    uint8_t x_col = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &x_col);
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &y_col);
    }

    if(res) {
        res = sonar_plot_convolution(num, x_col, y_col);
        log_info_res(SONAR, res, "PlotConvolution");
    } else {
        LOG_ERROR(SONAR, "Usage: spc Num X Y");
    }
    return res;
}

bool sonar_config_command(int32_t argc, char* argv[]) {
    bool res = false;
    float freq1_hz = 0;
    float amplitude = 0;
    float chirp_duration_s = 0;
    float freq2_hz = 0;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &chirp_duration_s);
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &freq1_hz);
    }

    if(5 <= argc) {
        res = try_str2float(argv[4], &freq2_hz);
    }

    if(res) {
        res = sonar_config_correlator_chirp(num, chirp_duration_s, amplitude, freq1_hz, freq2_hz);
        log_info_res(SONAR, res, "Config");
    } else {
        LOG_ERROR(SONAR, "Usage: scfg Num amplitude chirp_durationS freq1Hz freq2Hz");
    }
    return res;
}

#ifdef HAS_BARKER_CODE
bool sonar_calc_corr_barker_rec_command(int32_t argc, char* argv[]) {
    bool res = false;
    float carrier_frequency_hz = 0;
    float amplitude = 0;
    uint32_t periods_per_chip = 0;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &carrier_frequency_hz);
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &periods_per_chip);
    }

    if(res) {
        if(4 == argc) {
            res = sonar_config_correlator_barker13(num, amplitude, carrier_frequency_hz, periods_per_chip);
            log_info_res(SONAR, res, "Config");
        }
    } else {
        LOG_ERROR(SONAR, "Usage: sccb13r Num amplitude carrier_frequency_hz periods_per_chip Rec");
    }
    return res;
}
#endif

bool sonar_chirp_to_wav_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(res) {
        res = sonar_chirp_to_wav(num);
        log_info_res(SONAR, res, "ProbToWav");
    } else {
        LOG_ERROR(SONAR, "Usage: scw Num");
    }

    return res;
}

bool cmd_sonar_correlation(int32_t argc, char* argv[]) {
    bool res = false;
    bool on_off = false;
    uint8_t num = 0;

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num);
        res = try_str2bool(argv[1], &on_off);
    }

    if(res) {
        res = sonar_correlation_ctrl(num, on_off);
    } else {
        LOG_ERROR(SONAR, "Usage: soco Num OnOff");
    }

    return res;
}

bool cmd_sonar_zonding_signal(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    char rec_file_name[150] = {0};

    if(2 <= argc) {
        res = try_str2uint8(argv[0], &num);
        strcpy(rec_file_name, argv[1]);
        res = true;
    }

    if(res) {
        res = sonar_zonding_signal(num, rec_file_name);
    } else {
        LOG_ERROR(SONAR, "Usage: sozo Num FileName");
    }
    return res;
}

bool sonar_proc_record_command(int32_t argc, char* argv[]) {
    bool res = false;
    float chirp_duration_s = 0;
    float amplitude = 0;
    float freq2_hz = 0;
    float freq1_hz = 0;
    uint8_t num = 0;
    char file_name[120] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &amplitude);
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &chirp_duration_s);
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &freq1_hz);
    }

    if(5 <= argc) {
        res = try_str2float(argv[4], &freq2_hz);
    }

    if(6 <= argc) {
        strcpy(file_name, argv[5]);
        res = true;
    }

    if(res) {
        if(6 == argc) {
            res = sonar_chirp_correlation_record(num, chirp_duration_s, amplitude, freq1_hz, freq2_hz, file_name);
            log_info_res(SONAR, res, "correlation_record");
        }
    } else {
        LOG_ERROR(SONAR, "Usage: sccrec Num amplitude chirp_durationS freq1Hz freq2Hz RecFileName");
    }
    return res;
}

bool sonar_v_sound_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    float v_sound_m_pes_sec = V_SOUND_M_PES_SEC;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        v_sound_m_pes_sec = V_SOUND_M_PES_SEC;
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &v_sound_m_pes_sec);
    }

    if(res) {
        res = sonar_v_sound(num, v_sound_m_pes_sec);
        log_info_res(SONAR, res, "SetVsound");
    } else {
        LOG_ERROR(SONAR, "Usage: svs Num vSound");
    }
    return res;
}

#ifdef HAS_BARKER_CODE
bool sonar_config_correlator_barker_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    float carrier_frequency_hz = 2000.0f;
    float amplitude = 0;
    uint32_t periods_per_chip = 6;
    char rec_file_name[120] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SONAR, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &amplitude);
        log_info_res(SONAR, res, "Amp");
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &carrier_frequency_hz);
        log_info_res(SONAR, res, "CarFreq");
    }

    if(4 <= argc) {
        res = try_str2uint32(argv[3], &periods_per_chip);
        log_info_res(SONAR, res, "PerPerChip");
    }

    if(5 <= argc) {
        strcpy(rec_file_name, argv[4]);
        res = true;
        log_info_res(SONAR, res, "Name");
    }

    if(res) {
        if(5 == argc) {
            res = sonar_barker_calc_correlation_record(num, amplitude, carrier_frequency_hz, periods_per_chip,
                                                       rec_file_name);
            log_info_res(SONAR, res, "BarkerRefCalcCorrelation");
        }
    } else {
        LOG_ERROR(SONAR, "Usage: scb13 Num amplitude carrier_frequency_hz periods_per_chip RecordName");
    }
    return res;
}
#endif

bool sonar_config_correlator_m_seq_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t m_seq_num = 0;
    float carrier_frequency_hz = 2000.0f;
    float amplitude = 0;
    uint32_t periods_per_chip = 1;
    char rec_file_name[120] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SONAR, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &m_seq_num);
        log_info_res(SONAR, res, "Num");
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &amplitude);
        log_info_res(SONAR, res, "Amp");
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &carrier_frequency_hz);
        log_info_res(SONAR, res, "CarFreq");
    }

    if(5 <= argc) {
        res = try_str2uint32(argv[4], &periods_per_chip);
        log_info_res(SONAR, res, "PerPerChip");
    }

    if(6 <= argc) {
        strcpy(rec_file_name, argv[5]);
        res = true;
    }

    if(res) {
        if(6 == argc) {
            res = sonar_m_seq_calc_correlation_record(num, m_seq_num, amplitude, carrier_frequency_hz, periods_per_chip,
                                                      rec_file_name);
            log_info_res(SONAR, res, "M-Seq,RefCalcCorrelation");
        } else {
            LOG_ERROR(SONAR, "Usage: scmseq Num MseqNum amplitude carrierFrequencyHz periodsPerChip RecordName");
        }
    } else {
        LOG_ERROR(SONAR, "Usage: scmseq Num MseqNum amplitude carrierFrequencyHz periodsPerChip RecordName");
    }

    return res;
}



bool sonar_config_correlator_mono_command(int32_t argc, char* argv[]){
    bool res = false;
    uint8_t num = 0;
    float carrier_frequency_hz = 2500.0f;
    float amplitude = 0;
    float signal_duration = 0.01;
    char rec_file_name[120] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SONAR, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &carrier_frequency_hz);
        log_info_res(SONAR, res, "CarFreq");
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &amplitude);
        log_info_res(SONAR, res, "Amp");
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &signal_duration);
        log_info_res(SONAR, res, "SignalDuration");
    }

    if(5 <= argc) {
        strcpy(rec_file_name, argv[4]);
        res = true;
    }

    if(res) {
        if(5 == argc) {
            res = sonar_calc_correlation_mono_record(num, carrier_frequency_hz, amplitude,  signal_duration,
                                                     rec_file_name);
            log_info_res(SONAR, res, "Mono,RefCalcCorrelation");
        }
    }

    if(!res) {
        LOG_ERROR(SONAR, "Usage: scmono Num carrierFrequencyHz amplitude  SignalDurationS RecordName");
    }

    return res;
}
// schcal 1 331 0.05 6000
bool sonar_chirp_calculator_command(int32_t argc, char* argv[]) {
    uint8_t num = 0;
    bool res = false;
    float v_sound_m_pes_sec = V_SOUND_M_PES_SEC;
    float resolution_m = 0.0f;
    float f_central_hz = 0.0f;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(SONAR, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2float(argv[1], &v_sound_m_pes_sec);
        log_info_res(SONAR, res, "v_sound_m_pes_sec");
    }

    if(3 <= argc) {
        res = try_str2float(argv[2], &resolution_m);
        log_info_res(SONAR, res, "resolution_m");
    }

    if(4 <= argc) {
        res = try_str2float(argv[3], &f_central_hz);
        log_info_res(SONAR, res, "f_central_hz");
    }

    if(res) {
        SonarChirpParam_t ChirpParam = {0};
        res = sonar_chirp_calc_bandwith(  v_sound_m_pes_sec,
                                         resolution_m,
                                         f_central_hz,
                                         &ChirpParam);
        log_info_res(SONAR, res, "ChirpCalcBandwith");
        if(res){
            LOG_INFO(SONAR,"%s",SonarChirpParamToStr(&ChirpParam) );
        }
    } else {
        LOG_ERROR(SONAR, "Usage: schcal Num vSound resolutionM fCentralHz");
    }
    return res;
}


/*
 sonar_dft_convolution rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 sonar_dft_convolution rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 */
bool sonar_dft_convolution_command(int32_t argc, char* argv[]) {
    bool res = false;
    char pulse_file_name[120] = {0};
    char rec_file_name[120] = {0};
    if(2 <= argc) {
        LOG_INFO(SONAR, "0:[%s]", argv[0]);
        LOG_INFO(SONAR, "1:[%s]", argv[1]);
        strcpy(pulse_file_name, argv[0]);
        strcpy(rec_file_name, argv[1]);
        res = true;
    }

    if(res) {
        res = false;
        res = sonar_dft_convolution(pulse_file_name, rec_file_name);
        log_res(SONAR, res, "DftConvolution");
    }else {
        LOG_ERROR(SONAR, "Usage: sdftco Rec Pulse");
    }
    return res;
}

/*
 sonar_fft_convolution rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 sonar_fft_convolution rx/OneRecording_30ms_31.wav tx/1Chirp_30ms_F44100Hz_Hamming.wav
 */
bool sonar_fft_convolution_command(int32_t argc, char* argv[]) {
    bool res = false;
    char pulse_file_name[120] = {0};
    char rec_file_name[120] = {0};
    if(2 <= argc) {
        LOG_INFO(SONAR, "0:[%s]", argv[0]);
        LOG_INFO(SONAR, "1:[%s]", argv[1]);
        strcpy(pulse_file_name, argv[0]);
        strcpy(rec_file_name, argv[1]);
        res = true;
    }

    if(res) {
        res = false;
        res = sonar_fft_convolution(pulse_file_name, rec_file_name);
        log_res(SONAR, res, "FftConvolution");
    }else {
        LOG_ERROR(SONAR, "Usage: sfftco Rec Pulse");
    }
    return res;
}


