#ifndef PHASE_DETECTOR_COMMANDS_H
#define PHASE_DETECTOR_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_PHASE_DETECTOR_COMMANDS
#error "+HAS_PHASE_DETECTOR_COMMANDS"
#endif

#ifndef HAS_PHASE_DETECTOR
#error "+HAS_PHASE_DETECTOR"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool phase_detector_proc_command(int32_t argc, char* argv[]);
bool phase_detector_half_cos_command(int32_t argc, char* argv[]);
bool phase_detector_init_command(int32_t argc, char* argv[]);
bool phase_detector_diag_command(int32_t argc, char* argv[]);

#define PHASE_DETECTOR_COMMANDS                                                                     \
        SHELL_CMD("phase_detector_half_cos", "padhc", phase_detector_half_cos_command, "PhaseDetectorProcHalfCos"), \
        SHELL_CMD("phase_detector_proc", "padp", phase_detector_proc_command, "PhaseDetectorProc"), \
        SHELL_CMD("phase_detector_diag", "padd", phase_detector_diag_command, "PhaseDetectorDiag"), \
        SHELL_CMD("phase_detector_init", "padi", phase_detector_init_command, "PhaseDetectorInit"),

#ifdef __cplusplus
}
#endif

#endif /* PHASE_DETECTOR_COMMANDS_H */
