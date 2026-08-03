#include "m_seq_commands.h"

#include "convert.h"
#include "log.h"
#include "m_seq_mcal.h"

bool m_seq_diag_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(0 <= argc) {
        res = true;
    }

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(res) {
        res = m_seq_diag_one(num);
        log_info_res(M_SEQ, res, "Diag");
    } else {
        LOG_ERROR(M_SEQ, "Usage: fdat");
    }

    return res;
}

bool m_seq_init_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(0 == argc) {
        res = m_seq_mcal_init();
        log_info_res(M_SEQ, res, "Init");
    }
    return res;
}

bool m_seq_auto_correlation_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t shift_reg_num = 3;
    char CorrelationFileName[80] = {0};

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &shift_reg_num);
        log_info_res(M_SEQ, res, "ShifRegNum");
    }

    if(3 <= argc) {
        strcpy(CorrelationFileName, argv[2]);
    }

    if(res) {
        if(3 == argc) {

            res = m_seq_calc_acf(num, shift_reg_num, CorrelationFileName);
            log_info_res(M_SEQ, res, "AutoCorrelation");
            // res = m_seq_calc_periodic_acf(  num, shift_reg_num ,CorrelationFileName );
            // log_info_res(M_SEQ, res, "PeriodicAutoCorrelation");
        }
    } else {
        LOG_ERROR(M_SEQ, "Usage: msac N ShiftRegNum");
    }
    return res;
}

bool m_seq_generate_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(res) {
        res = m_seq_generate(num);
    } else {
        LOG_ERROR(M_SEQ, "Usage: msg N");
    }

    return res;
}

bool m_seq_feedback_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t offset = 0;
    uint8_t value = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &offset);
        log_info_res(M_SEQ, res, "offset");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &value);
        log_info_res(M_SEQ, res, "value");
    }

    if(res) {
        res = m_seq_feedback(num, offset, value);
    } else {
        LOG_ERROR(M_SEQ, "Usage: msf N Offset Value");
    }

    return res;
}

bool m_seq_seed_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint8_t offset = 0;
    uint8_t value = 0;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint8(argv[1], &offset);
        log_info_res(M_SEQ, res, "offset");
    }

    if(3 <= argc) {
        res = try_str2uint8(argv[2], &value);
        log_info_res(M_SEQ, res, "value");
    }

    if(res) {
        res = m_seq_seed_set(num, offset, value);
    } else {
        LOG_ERROR(M_SEQ, "Usage: msf N Offset Value");
    }

    return res;
}

bool m_seq_size_command(int32_t argc, char* argv[]) {
    bool res = false;
    uint8_t num = 0;
    uint32_t shift_reg_num = 3;

    if(1 <= argc) {
        res = try_str2uint8(argv[0], &num);
        log_info_res(M_SEQ, res, "Num");
    }

    if(2 <= argc) {
        res = try_str2uint32(argv[1], &shift_reg_num);
        log_info_res(M_SEQ, res, "shiftRegNum");
    }

    if(res) {
        res = m_seq_reinit_one(num, shift_reg_num);
    } else {
        LOG_ERROR(M_SEQ, "Usage: msf N Size");
    }

    return res;
}
