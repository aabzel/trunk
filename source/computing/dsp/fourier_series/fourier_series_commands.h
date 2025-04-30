#ifndef FOURIER_SERIES_COMMANDS_H
#define FOURIER_SERIES_COMMANDS_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>
#include <stdint.h>

#ifndef HAS_FOURIER_SERIES
#error "+HAS_FOURIER_SERIES"
#endif /*HAS_FOURIER_SERIES*/

#ifndef HAS_FOURIER_SERIES_COMMANDS
#error "+HAS_FOURIER_SERIES_COMMANDS"
#endif /*HAS_FOURIER_SERIES*/

bool fourier_series_calc_coefficient_command(int32_t argc, char* argv[]);
bool fourier_series_diag_command(int32_t argc, char* argv[]);
bool fourier_series_init_command(int32_t argc, char* argv[]);

#define FOURIER_SERIES_COMMANDS                                                                                                   \
    SHELL_CMD("fourier_series_calc_coefficient", "fscs", fourier_series_calc_coefficient_command, "FourierSeriesCalcCoefficient"),                                              \
        SHELL_CMD("fourier_series_diag", "fsd", fourier_series_diag_command, "FourierSeriesDiag"),                                             \
        SHELL_CMD("fourier_series_init", "fsi", fourier_series_init_command, "FourierSeriesInit"),

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*FOURIER_SERIES_COMMANDS_H*/
