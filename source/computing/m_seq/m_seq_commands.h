#ifndef M_SEQ_COMMANDS_H
#define M_SEQ_COMMANDS_H


#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"

#ifndef HAS_M_SEQ
#error "+ HAS_M_SEQ"
#endif

#ifndef HAS_M_SEQ_COMMANDS
#error "+ HAS_M_SEQ_COMMANDS"
#endif

bool m_seq_size_command(int32_t argc, char* argv[]);
bool m_seq_seed_command(int32_t argc, char* argv[]) ;
bool m_seq_feedback_command(int32_t argc, char* argv[]);
bool m_seq_auto_correlation_command(int32_t argc, char* argv[]);
bool m_seq_diag_command(int32_t argc, char* argv[]);
bool m_seq_generate_command(int32_t argc, char* argv[]);
bool m_seq_init_command(int32_t argc, char* argv[]);
bool m_seq_find_first_feedback_command(int32_t argc, char* argv[]) ;

#define M_SEQ_COMMANDS                                                     \
        SHELL_CMD("m_seq_find_first_feedback", "msfff", m_seq_find_first_feedback_command, "MseqFindFirstFeedBack"),   \
        SHELL_CMD("m_seq_size", "mssz", m_seq_size_command, "MseqSize"),   \
        SHELL_CMD("m_seq_seed", "mss", m_seq_seed_command, "MseqSeed"),    \
        SHELL_CMD("m_seq_feedback", "msf", m_seq_feedback_command, "MseqFeedBack"),   \
        SHELL_CMD("m_seq_generate", "msg", m_seq_generate_command, "MseqGenerate"),   \
        SHELL_CMD("m_seq_diag", "msed", m_seq_diag_command, "MseqDiag"),   \
        SHELL_CMD("m_seq_auto_correlatino", "msac", m_seq_auto_correlation_command, "MseqAutoCorrelation"),   \
        SHELL_CMD("m_seq_init", "msei", m_seq_init_command, "MseqInit"),

#ifdef __cplusplus
}
#endif

#endif /* M_SEQ_COMMANDS_H */
