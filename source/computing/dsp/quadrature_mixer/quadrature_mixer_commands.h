#ifndef QUADRATURE_MIXER_COMMANDS_H
#define QUADRATURE_MIXER_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <std_includes.h>

#include "ostream.h"

#ifndef HAS_QUADRATURE_MIXER_COMMANDS
#error "+HAS_QUADRATURE_MIXER_COMMANDS"
#endif

#ifndef HAS_QUADRATURE_MIXER
#error "+HAS_QUADRATURE_MIXER"
#endif

#ifndef HAS_CLI
#error "+HAS_CLI"
#endif

#ifndef HAS_LOG
#error "+HAS_LOG"
#endif

bool quadrature_mixer_init_command(int32_t argc, char* argv[]);
bool quadrature_mixer_diag_command(int32_t argc, char* argv[]);
bool quadrature_mixer_lpf_iir_command(int32_t argc, char* argv[]);

#define QUADRATURE_MIXER_COMMANDS                                                                 \
        SHELL_CMD("quadrature_mixer_lpf_iir", "qmlps", quadrature_mixer_lpf_iir_command, "QuadratureMixerIirPlf"),                       \
        SHELL_CMD("quadrature_mixer_diag", "qmd", quadrature_mixer_diag_command, "QuadratureMixerDiag"),                       \
        SHELL_CMD("quadrature_mixer_init", "qmi", quadrature_mixer_init_command, "QuadratureMixerInit"),

#ifdef __cplusplus
}
#endif

#endif /* QUADRATURE_MIXER_COMMANDS_H */
