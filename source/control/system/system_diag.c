#include "system_diag.h"

#include <stdbool.h>
#include <string.h>

#include "data_utils.h"
#include "log.h"
#include "system.h"

#ifdef HAS_MATH
#include "utils_math.h"
#endif

#ifdef HAS_AUTO_BRIGHTNESS
#define AUTO_BRIGHTNESS_FACILITY_DIAG                                                                                  \
    {                                                                                                                  \
        .facility = AUTO_BRIGHTNESS,                                                                                   \
        .name = "AutoBrightness",                                                                                      \
    },
#else
#define AUTO_BRIGHTNESS_FACILITY_DIAG
#endif

#ifdef HAS_BLE_AUDIO
#define BLE_AUDIO_FACILITY_DIAG                                                                                        \
    {                                                                                                                  \
        .facility = BLE_AUDIO,                                                                                         \
        .name = "BleAudio",                                                                                            \
    },
#else
#define BLE_AUDIO_FACILITY_DIAG
#endif

#ifdef HAS_CALCULATOR
#define CALCULATOR_FACILITY_DIAG                                                                                       \
    {                                                                                                                  \
        .facility = CALC,                                                                                              \
        .name = "CALC",                                                                                                \
    },
#else
#define CALCULATOR_FACILITY_DIAG
#endif

#ifdef HAS_CALIBRATION_DATA
#define CALIBRATION_DATA_FACILITY_DIAG                                                                                 \
    {                                                                                                                  \
        .facility = CALIBRATION_DATA,                                                                                  \
        .name = "CalibrationData",                                                                                     \
    },
#else
#define CALIBRATION_DATA_FACILITY_DIAG
#endif

#ifdef HAS_STATISTICS
#define STATISTICS_FACILITY_DIAG                                                                                       \
    {                                                                                                                  \
        .facility = STATISTICS,                                                                                        \
        .name = "Statistics",                                                                                          \
    },
#else
#define STATISTICS_FACILITY_DIAG
#endif

#ifdef HAS_BLACK_BOX
#define BLACK_BOX_FACILITY_DIAG                                                                                        \
    {                                                                                                                  \
        .facility = BLACK_BOX,                                                                                         \
        .name = "BlackBox",                                                                                            \
    },
#else
#define BLACK_BOX_FACILITY_DIAG
#endif

#ifdef HAS_MICROCONTROLLER
#define MICROCONTROLLER_FACILITY_DIAG                                                                                  \
    {                                                                                                                  \
        .facility = MICROCONTROLLER,                                                                                   \
        .name = "Mcu",                                                                                                 \
    },
#else
#define MICROCONTROLLER_FACILITY_DIAG
#endif

#ifdef HAS_DECAWAVE
#define DECAWAVE_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = DECAWAVE,                                                                                          \
        .name = "DecaWave",                                                                                            \
    },
#else
#define DECAWAVE_FACILITY_DIAG
#endif

#ifdef HAS_SERIAL_PORT
#define SERIAL_PORT_FACILITY_DIAG                                                                                      \
    {                                                                                                                  \
        .facility = SERIAL_PORT,                                                                                       \
        .name = "SerialPort",                                                                                          \
    },
#else
#define SERIAL_PORT_FACILITY_DIAG
#endif

#ifdef HAS_SOCKET
#define SOCKET_FACILITY_DIAG                                                                                           \
    {                                                                                                                  \
        .facility = LG_SOCKET,                                                                                         \
        .name = "Socket",                                                                                              \
    },                                                                                                                 \
        {                                                                                                              \
            .facility = LG_SOCKET_SERVER,                                                                              \
            .name = "SocketServer",                                                                                    \
        },                                                                                                             \
        {                                                                                                              \
            .facility = LG_SOCKET_CLIENT,                                                                              \
            .name = "SocketClient",                                                                                    \
        },
#else
#define SOCKET_FACILITY_DIAG
#endif

#ifdef HAS_DECAWAVE_NATIVE
#define DECAWAVE_NATIVE_FACILITY_DIAG                                                                                  \
    {                                                                                                                  \
        .facility = DECAWAVE_NATIVE,                                                                                   \
        .name = "DecaWaveNat",                                                                                         \
    },
#else
#define DECAWAVE_NATIVE_FACILITY_DIAG
#endif

#ifdef HAS_HW_CRYP
#define HW_CRYP_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = HW_CRYP,                                                                                           \
        .name = "HwCryp",                                                                                              \
    },
#else
#define HW_CRYP_FACILITY_DIAG
#endif

#ifdef HAS_W25M02GV
#define W25M02GV_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = W25M02GV,                                                                                          \
        .name = "W25M02GV",                                                                                            \
    },
#else
#define W25M02GV_FACILITY_DIAG
#endif

#ifdef HAS_ARRAY
#define ARRAY_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = ARRAY,                                                                                             \
        .name = "Array",                                                                                               \
    },
#else
#define ARRAY_FACILITY_DIAG
#endif

#ifdef HAS_STRING
#define STRING_FACILITY_DIAG                                                                                           \
    {                                                                                                                  \
        .facility = LINE,                                                                                              \
        .name = "String",                                                                                              \
    },
#else
#define STRING_FACILITY_DIAG
#endif

#ifdef HAS_PLL_SIM
#define PLL_SIM_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = PLL_SIM,                                                                                           \
        .name = "PllSim",                                                                                              \
    },
#else
#define PLL_SIM_FACILITY_DIAG
#endif

#ifdef HAS_BOOTLOADER
#define BOOTLOADER_FACILITY_DIAG                                                                                       \
    {                                                                                                                  \
        .facility = BOOTLOADER,                                                                                        \
        .name = "BootLoader",                                                                                          \
    },
#else
#define BOOTLOADER_FACILITY_DIAG
#endif

#ifdef HAS_ISO_TP
#define ISO_TP_FACILITY_DIAG                                                                                           \
    {                                                                                                                  \
        .facility = ISO_TP,                                                                                            \
        .name = "IsoTp",                                                                                               \
    },
#else
#define ISO_TP_FACILITY_DIAG
#endif

#ifdef HAS_COMPLEX
#define COMPLEX_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = COMPLEX,                                                                                           \
        .name = "Complex",                                                                                             \
    },
#else
#define COMPLEX_FACILITY_DIAG
#endif

#ifdef HAS_HEX_BIN
#define HEX_BIN_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = HEX_BIN,                                                                                           \
        .name = "HexBin",                                                                                              \
    },
#else
#define HEX_BIN_FACILITY_DIAG
#endif

#ifdef HAS_FW_LOADER
#define FW_LOADER_FACILITY_DIAG                                                                                        \
    {                                                                                                                  \
        .facility = FW_LOADER,                                                                                         \
        .name = "FwLoader",                                                                                            \
    },
#else
#define FW_LOADER_FACILITY_DIAG
#endif

#ifdef HAS_FILE_PC
#define FILE_PC_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = FILE_PC,                                                                                           \
        .name = "File",                                                                                                \
    },
#else
#define FILE_PC_FACILITY_DIAG
#endif

#ifdef HAS_FILE_API
#define FILE_API_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = FILE_API,                                                                                          \
        .name = "FileAPI",                                                                                             \
    },
#else
#define FILE_API_FACILITY_DIAG
#endif

#ifdef HAS_AUTO_VERSION
#define AUTO_VERSION_FACILITY_DIAG                                                                                     \
    {                                                                                                                  \
        .facility = AUTO_VERSION,                                                                                      \
        .name = "AutoVersion",                                                                                         \
    },
#else
#define AUTO_VERSION_FACILITY_DIAG
#endif

#ifdef HAS_ANALOG_FILTER
#define ANALOG_FILTER_FACILITY_DIAG                                                                                    \
    {                                                                                                                  \
        .facility = ANALOG_FILTER,                                                                                     \
        .name = "AnalogFilter",                                                                                        \
    },
#else
#define ANALOG_FILTER_FACILITY_DIAG
#endif

#ifdef HAS_BOARD
#define BOARD_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = BOARD,                                                                                             \
        .name = "Board",                                                                                               \
    },
#else
#define BOARD_FACILITY_DIAG
#endif

#ifdef HAS_GPS
#define GPS_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = GPS,                                                                                               \
        .name = "GPS",                                                                                                 \
    },
#else
#define GPS_FACILITY_DIAG
#endif

#ifdef HAS_DECIMATOR
#define DECIMATOR_FACILITY_DIAG                                                                                        \
    {                                                                                                                  \
        .facility = DECIMATOR,                                                                                         \
        .name = "Decimator",                                                                                           \
    },
#else
#define DECIMATOR_FACILITY_DIAG
#endif

#ifdef HAS_QUADRATURE_MIXER
#define QUADRATURE_MIXER_FACILITY_DIAG                                                                                 \
    {                                                                                                                  \
        .facility = QUADRATURE_MIXER,                                                                                  \
        .name = "QuadMixer",                                                                                           \
    },
#else
#define QUADRATURE_MIXER_FACILITY_DIAG
#endif

#ifdef HAS_NAU8814
#define NAU8814_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = NAU8814,                                                                                           \
        .name = "Nau8814",                                                                                             \
    },
#else
#define NAU8814_FACILITY_DIAG
#endif

#ifdef HAS_UDS
#define UDS_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = UDS,                                                                                               \
        .name = "UDS",                                                                                                 \
    },                                                                                                                 \
        {                                                                                                              \
            .facility = DID,                                                                                           \
            .name = "DID",                                                                                             \
        },
#else
#define UDS_FACILITY_DIAG
#endif

#ifdef HAS_PLL_CALC
#define PLL_CALC_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = PLL_CALC,                                                                                          \
        .name = "PLL",                                                                                                 \
    },
#else
#define PLL_CALC_FACILITY_DIAG
#endif

#ifdef HAS_RS485
#define RS485_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = RS485,                                                                                             \
        .name = "Rs485",                                                                                               \
    },
#else
#define RS485_FACILITY_DIAG
#endif

#ifdef HAS_LOG
#define LOG_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = LOG,                                                                                               \
        .name = "Log",                                                                                                 \
    },
#else
#define LOG_FACILITY_DIAG
#endif

#ifdef HAS_RUNNING_LINE
#define RUNNING_LINE_FACILITY_DIAG                                                                                     \
    {                                                                                                                  \
        .facility = RUNNING_LINE,                                                                                      \
        .name = "RunningLine",                                                                                         \
    },
#else
#define RUNNING_LINE_FACILITY_DIAG
#endif

#ifdef HAS_PID
#define PID_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = PID,                                                                                               \
        .name = "PID",                                                                                                 \
    },
#else
#define PID_FACILITY_DIAG
#endif

#ifdef HAS_RS232
#define RS232_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = RS232,                                                                                             \
        .name = "Rs232",                                                                                               \
    },
#else
#define RS232_FACILITY_DIAG
#endif

#ifdef HAS_TIMER_CALC
#define TIMER_CALC_FACILITY_DIAG                                                                                       \
    {                                                                                                                  \
        .facility = TIMER_CALC,                                                                                        \
        .name = "TimerCalc",                                                                                           \
    },
#else
#define TIMER_CALC_FACILITY_DIAG
#endif

#ifdef HAS_ECHO_EFFECT
#define ECHO_EFFECT_FACILITY_DIAG                                                                                      \
    {                                                                                                                  \
        .facility = ECHO_EFFECT,                                                                                       \
        .name = "EchoEffect",                                                                                          \
    },
#else
#define ECHO_EFFECT_FACILITY_DIAG
#endif

#ifdef HAS_SA51034
#define SA51034_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = SA51034,                                                                                           \
        .name = "Sa51034",                                                                                             \
    },
#else
#define SA51034_FACILITY_DIAG
#endif

#ifdef HAS_IIR
#define IIR_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = IIR,                                                                                               \
        .name = "IIR",                                                                                                 \
    },
#else
#define IIR_FACILITY_DIAG
#endif

#ifdef HAS_FFT
#define FFT_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = FFT,                                                                                               \
        .name = "FFT",                                                                                                 \
    },
#else
#define FFT_FACILITY_DIAG
#endif

#ifdef HAS_SONAR
#define SONAR_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = SONAR,                                                                                             \
        .name = "SoNaR",                                                                                               \
    },
#else
#define SONAR_FACILITY_DIAG
#endif

#ifdef HAS_STRING_READER
#define STRING_READER_FACILITY_DIAG                                                                                    \
    {                                                                                                                  \
        .facility = STRING_READER,                                                                                     \
        .name = "StringReader",                                                                                        \
    },
#else
#define STRING_READER_FACILITY_DIAG
#endif

#ifdef HAS_LTR390
#define LTR390_FACILITY_DIAG                                                                                           \
    {                                                                                                                  \
        .facility = LTR390,                                                                                            \
        .name = "Ltr390",                                                                                              \
    },                                                                                                                 \
        {                                                                                                              \
            .facility = ALS,                                                                                           \
            .name = "Als",                                                                                             \
        },                                                                                                             \
        {                                                                                                              \
            .facility = UVS,                                                                                           \
            .name = "Uvs",                                                                                             \
        },
#else
#define LTR390_FACILITY_DIAG
#endif

#ifdef HAS_WATCHDOG
#define WATCHDOG_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = WATCHDOG,                                                                                          \
        .name = "WatchDog",                                                                                            \
    },
#else
#define WATCHDOG_FACILITY_DIAG
#endif

#ifdef HAS_W25Q32JV
#define W25Q32JV_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = W25Q32JV,                                                                                          \
        .name = "W25q32jv",                                                                                            \
    },
#else
#define W25Q32JV_FACILITY_DIAG
#endif

#ifdef HAS_HW_VERSION
#define HW_VERSION_FACILITY_DIAG                                                                                       \
    {                                                                                                                  \
        .facility = HW_VERSION,                                                                                        \
        .name = "HwVersion",                                                                                           \
    },
#else
#define HW_VERSION_FACILITY_DIAG
#endif

#ifdef HAS_PWM_DAC
#define PWM_DAC_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = PWM_DAC,                                                                                           \
        .name = "PwmDac",                                                                                              \
    },
#else
#define PWM_DAC_FACILITY_DIAG
#endif

#ifdef HAS_TOPO_SORT
#define TOPO_SORT_FACILITY_DIAG                                                                                        \
    {                                                                                                                  \
        .facility = TOPO_SORT,                                                                                         \
        .name = "TopoSort",                                                                                            \
    },
#else
#define TOPO_SORT_FACILITY_DIAG
#endif

#ifdef HAS_WAV
#define WAV_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = WAV,                                                                                               \
        .name = "WAV",                                                                                                 \
    },
#else
#define WAV_FACILITY_DIAG
#endif

#ifdef HAS_DDS
#define DDS_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = DDS,                                                                                               \
        .name = "DDS",                                                                                                 \
    },
#else
#define DDS_FACILITY_DIAG
#endif

#ifdef HAS_EEPROM
#define EEPROM_FACILITY_DIAG                                                                                           \
    {                                                                                                                  \
        .facility = EEPROM,                                                                                            \
        .name = "EEPROM",                                                                                              \
    },
#else
#define EEPROM_FACILITY_DIAG
#endif

#ifdef HAS_CLOCK_DIVIDER
#define CLOCK_DIVIDER_FACILITY_DIAG                                                                                    \
    {                                                                                                                  \
        .facility = CLOCK_DIVIDER,                                                                                     \
        .name = "ClockDivider",                                                                                        \
    },
#else
#define CLOCK_DIVIDER_FACILITY_DIAG
#endif

#ifdef HAS_C_GENERATOR
#define C_GENERATOR_FACILITY_DIAG                                                                                      \
    {                                                                                                                  \
        .facility = C_GENERATOR,                                                                                       \
        .name = "cGenerator",                                                                                          \
    },
#else
#define C_GENERATOR_FACILITY_DIAG
#endif

#ifdef HAS_CODE_STYLE_CHECKER
#define CODE_STYLE_CHECKER_FACILITY_DIAG                                                                               \
    {                                                                                                                  \
        .facility = CODE_STYLE_CHECKER,                                                                                \
        .name = "CodeStyle",                                                                                           \
    },
#else
#define CODE_STYLE_CHECKER_FACILITY_DIAG
#endif

#ifdef HAS_EXT_INT
#define EXT_INT_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = EXT_INT,                                                                                           \
        .name = "ExtInt",                                                                                              \
    },
#else
#define EXT_INT_FACILITY_DIAG
#endif

#ifdef HAS_GM67
#define GM67_FACILITY_DIAG                                                                                             \
    {                                                                                                                  \
        .facility = GM67,                                                                                              \
        .name = "Gm67",                                                                                                \
    },
#else
#define GM67_FACILITY_DIAG
#endif

#ifdef HAS_KALAH
#define KALAH_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = KALAH,                                                                                             \
        .name = "Kalah",                                                                                               \
    },
#else
#define KALAH_FACILITY_DIAG
#endif

#ifdef HAS_UBLOX_NEO_6M
#define UBLOX_NEO_6M_FACILITY_DIAG                                                                                     \
    {                                                                                                                  \
        .facility = UBLOX_NEO_6M,                                                                                      \
        .name = "uBloxNeo6M",                                                                                          \
    },
#else
#define UBLOX_NEO_6M_FACILITY_DIAG
#endif

#ifdef HAS_PHASE_DETECTOR
#define PHASE_DETECTOR_FACILITY_DIAG                                                                                   \
    {                                                                                                                  \
        .facility = PHASE_DETECTOR,                                                                                    \
        .name = "PhaseDetector",                                                                                       \
    },
#else
#define PHASE_DETECTOR_FACILITY_DIAG
#endif

#ifdef HAS_END_OF_BLOCK
#define END_OF_BLOCK_FACILITY_DIAG                                                                                     \
    {                                                                                                                  \
        .facility = END_OF_BLOCK,                                                                                      \
        .name = "EndOfBlock",                                                                                          \
    },
#else
#define END_OF_BLOCK_FACILITY_DIAG
#endif

#ifdef HAS_DELTA_SIGMA
#define DELTA_SIGMA_FACILITY_DIAG                                                                                      \
    {                                                                                                                  \
        .facility = DELTA_SIGMA,                                                                                       \
        .name = "DeltaSigma",                                                                                          \
    },
#else
#define DELTA_SIGMA_FACILITY_DIAG
#endif

#ifdef HAS_SCAN
#define SCAN_FACILITY_DIAG                                                                                             \
    {                                                                                                                  \
        .facility = SCAN,                                                                                              \
        .name = "Scan",                                                                                                \
    },
#else
#define SCAN_FACILITY_DIAG
#endif

#ifdef HAS_SET_GAME
#define SET_GAME_FACILITY_DIAG                                                                                         \
    {                                                                                                                  \
        .facility = SET_GAME,                                                                                          \
        .name = "SetGame",                                                                                             \
    },
#else
#define SET_GAME_FACILITY_DIAG
#endif

#ifdef HAS_DSP
#define DSP_FACILITY_DIAG                                                                                              \
    {                                                                                                                  \
        .facility = DSP,                                                                                               \
        .name = "DSP",                                                                                                 \
    },
#else
#define DSP_FACILITY_DIAG
#endif

#ifdef HAS_BPSK
#define BPSK_FACILITY_DIAG                                                                                             \
    {                                                                                                                  \
        .facility = BPSK,                                                                                              \
        .name = "Bpsk",                                                                                                \
    },
#else
#define BPSK_FACILITY_DIAG
#endif

#ifdef HAS_CORRELATOR
#define CORRELATOR_FACILITY_DIAG                                                                                       \
    {                                                                                                                  \
        .facility = CORRELATOR,                                                                                        \
        .name = "Correlator",                                                                                          \
    },
#else
#define CORRELATOR_FACILITY_DIAG
#endif

#ifdef HAS_SOUND_LOCALIZATION
#define SOUND_LOCALIZATION_FACILITY_DIAG                                                                               \
    {                                                                                                                  \
        .facility = SOUND_LOCALIZATION,                                                                                \
        .name = "SoundLocalization",                                                                                   \
    },
#else
#define SOUND_LOCALIZATION_FACILITY_DIAG
#endif

#ifdef HAS_SPIFI
#define SPIFI_FACILITY_DIAG                                                                                            \
    {                                                                                                                  \
        .facility = SPIFI,                                                                                             \
        .name = "SPIFI",                                                                                               \
    },
#else
#define SPIFI_FACILITY_DIAG
#endif

#ifdef HAS_STORAGE
#define STORAGE_FACILITY_DIAG                                                                                          \
    {                                                                                                                  \
        .facility = STORAGE,                                                                                           \
        .name = "Storage",                                                                                             \
    },
#else
#define STORAGE_FACILITY_DIAG
#endif

#ifdef HAS_GRAPHVIZ_TO_TSORT
#define GRAPHVIZ_TO_TSORT_FACILITY_DIAG                                                                                \
    {                                                                                                                  \
        .facility = GRAPHVIZ_TO_TSORT,                                                                                 \
        .name = "GraphVizToTsort",                                                                                     \
    },
#else
#define GRAPHVIZ_TO_TSORT_FACILITY_DIAG
#endif

#define ALL_FACILITY_INFO                                                                                              \
    ANALOG_FILTER_FACILITY_DIAG                                                                                        \
    ARRAY_FACILITY_DIAG                                                                                                \
    AUTO_BRIGHTNESS_FACILITY_DIAG                                                                                      \
    DSP_FACILITY_DIAG                                                                                                  \
    AUTO_VERSION_FACILITY_DIAG                                                                                         \
    BLACK_BOX_FACILITY_DIAG                                                                                            \
    BPSK_FACILITY_DIAG                                                                                                 \
    BLE_AUDIO_FACILITY_DIAG                                                                                            \
    BOARD_FACILITY_DIAG                                                                                                \
    STORAGE_FACILITY_DIAG                                                                                              \
    BOOTLOADER_FACILITY_DIAG                                                                                           \
    C_GENERATOR_FACILITY_DIAG                                                                                          \
    CALCULATOR_FACILITY_DIAG                                                                                           \
    CALIBRATION_DATA_FACILITY_DIAG                                                                                     \
    CLOCK_DIVIDER_FACILITY_DIAG                                                                                        \
    CODE_STYLE_CHECKER_FACILITY_DIAG                                                                                   \
    COMPLEX_FACILITY_DIAG                                                                                              \
    CORRELATOR_FACILITY_DIAG                                                                                           \
    END_OF_BLOCK_FACILITY_DIAG                                                                                         \
    DECAWAVE_FACILITY_DIAG                                                                                             \
    DECAWAVE_NATIVE_FACILITY_DIAG                                                                                      \
    DECIMATOR_FACILITY_DIAG                                                                                            \
    DELTA_SIGMA_FACILITY_DIAG                                                                                          \
    DDS_FACILITY_DIAG                                                                                                  \
    EEPROM_FACILITY_DIAG                                                                                               \
    FILE_API_FACILITY_DIAG                                                                                             \
    FILE_PC_FACILITY_DIAG                                                                                              \
    GM67_FACILITY_DIAG                                                                                                 \
    GPS_FACILITY_DIAG                                                                                                  \
    GRAPHVIZ_TO_TSORT_FACILITY_DIAG                                                                                    \
    HEX_BIN_FACILITY_DIAG                                                                                              \
    FW_LOADER_FACILITY_DIAG                                                                                            \
    HW_CRYP_FACILITY_DIAG                                                                                              \
    HW_VERSION_FACILITY_DIAG                                                                                           \
    ISO_TP_FACILITY_DIAG                                                                                               \
    IIR_FACILITY_DIAG                                                                                                  \
    KALAH_FACILITY_DIAG                                                                                                \
    LTR390_FACILITY_DIAG                                                                                               \
    MICROCONTROLLER_FACILITY_DIAG                                                                                      \
    NAU8814_FACILITY_DIAG                                                                                              \
    LOG_FACILITY_DIAG                                                                                                  \
    PLL_CALC_FACILITY_DIAG                                                                                             \
    PWM_DAC_FACILITY_DIAG                                                                                              \
    RS232_FACILITY_DIAG                                                                                                \
    RS485_FACILITY_DIAG                                                                                                \
    RUNNING_LINE_FACILITY_DIAG                                                                                         \
    PHASE_DETECTOR_FACILITY_DIAG                                                                                       \
    PID_FACILITY_DIAG                                                                                                  \
    SA51034_FACILITY_DIAG                                                                                              \
    SOCKET_FACILITY_DIAG                                                                                               \
    SERIAL_PORT_FACILITY_DIAG                                                                                          \
    SOUND_LOCALIZATION_FACILITY_DIAG                                                                                   \
    FFT_FACILITY_DIAG                                                                                                  \
    STRING_READER_FACILITY_DIAG                                                                                        \
    STRING_FACILITY_DIAG                                                                                               \
    SCAN_FACILITY_DIAG                                                                                                 \
    SET_GAME_FACILITY_DIAG                                                                                             \
    STATISTICS_FACILITY_DIAG                                                                                           \
    SONAR_FACILITY_DIAG                                                                                                \
    SPIFI_FACILITY_DIAG                                                                                                \
    QUADRATURE_MIXER_FACILITY_DIAG                                                                                     \
    TIMER_CALC_FACILITY_DIAG                                                                                           \
    TOPO_SORT_FACILITY_DIAG                                                                                            \
    UBLOX_NEO_6M_FACILITY_DIAG                                                                                         \
    UDS_FACILITY_DIAG                                                                                                  \
    PLL_SIM_FACILITY_DIAG                                                                                              \
    WAV_FACILITY_DIAG                                                                                                  \
    W25Q32JV_FACILITY_DIAG                                                                                             \
    WATCHDOG_FACILITY_DIAG

static const FacilityInfo_t FacilityInfo[] = {
    ALL_FACILITY_INFO

    {
        .facility = UNKNOWN_FACILITY,
        .name = "UNKNOWN",
    },

#ifdef HAS_NOR_FLASH
    {
        .facility = NOR_FLASH,
        .name = "NOR_FLASH",
    },
#endif /*HAS_NOR_FLASH*/

#ifdef HAS_AES
    {
        .facility = AES,
        .name = "AES",
    },
#endif /*HAS_AES*/

#ifdef HAS_NVRAM
    {
        .facility = NVRAM,
        .name = "NVRAM",
    },
#endif /*HAS_NVRAM*/

#ifdef HAS_AD9833
    {
        .facility = AD9833,
        .name = "AD9833",
    },
#endif /*HAS_AD9833*/

#ifdef HAS_AES256
    {
        .facility = AES256,
        .name = "AES256",
    },
#endif /*HAS_AES256*/

#ifdef HAS_AT24CXX
    {
        .facility = AT24C,
        .name = "AT24C",
    },
#endif /*HAS_AT24CXX*/
#ifdef HAS_SOLUTION
    {
        .facility = SOLUTION,
        .name = "Solution",
    },
#endif /*HAS_SOLUTION*/

#ifdef HAS_BLUETOOTH
    {
        .facility = BLUETOOTH,
        .name = "BlueTooth",
    },
#endif /*HAS_BLUETOOTH*/

#ifdef HAS_BLE
    {
        .facility = BLE,
        .name = "BLE",
    },
#endif /*HAS_BLE*/

#ifdef HAS_BT1026
    {
        .facility = BT1026,
        .name = "BT1026",
    },
#endif /*HAS_BT1026*/

#ifdef HAS_DFT
    {
        .facility = DFT,
        .name = "DFT",
    },
    {
        .facility = IDFT,
        .name = "iDFT",
    },
#endif /*HAS_DFT*/

#ifdef HAS_CRYP
    {
        .facility = LG_CRYP,
        .name = "CRYP",
    },
#endif /*HAS_CRYP*/

#ifdef HAS_CROSS_DETECT
    {
        .facility = CROSS_DETECT,
        .name = "CrossDetect",
    },
#endif /*HAS_CROSS_DETECT*/

#ifdef HAS_DW1000
    {
        .facility = DW1000,
        .name = "DW1000",
    },
#endif /*HAS_DW1000*/

#ifdef HAS_SCHMITT_TRIGGER
    {
        .facility = SCHMITT_TRIGGER,
        .name = "SchmittTrigger",
    },
#endif /*HAS_SCHMITT_TRIGGER*/

#ifdef HAS_DWM1000
    {
        .facility = DWM1000,
        .name = "DWM1000",
    },
#endif /*HAS_DWM1000*/

#ifdef HAS_DWM3000
    {
        .facility = DWM3000,
        .name = "DWM3000",
    },
#endif /*HAS_DWM3000*/

#ifdef HAS_FONT
    {
        .facility = FONT,
        .name = "Font",
    },
#endif /*HAS_FONT*/

#ifdef HAS_KEYBOARD
    {
        .facility = KEYBOARD,
        .name = "KEYBOARD",
    },
#endif /*HAS_KEYBOARD*/

#ifdef HAS_LOAD_DETECT
    {
        .facility = LOAD_DETECT,
        .name = "LoadDetect",
    },
#endif /*HAS_LOAD_DETECT*/

#ifdef HAS_BQ24079
    {
        .facility = BQ24079,
        .name = "BQ24079",
    },
#endif /*HAS_BQ24079*/

#ifdef HAS_LED_MONO
    {
        .facility = LED_MONO,
        .name = "LedMono",
    },
#endif /*HAS_LED_MONO*/

#ifdef HAS_LED_RGB
    {
        .facility = LED_RGB,
        .name = "RGB",
    },
#endif /*HAS_LED_RGB*/

#ifdef HAS_IEC16022
    {
        .facility = IEC16022,
        .name = "IEC16022",
    },
#endif /*HAS_IEC16022*/

#ifdef HAS_LC3
    {
        .facility = LC3,
        .name = "LC3",
    },
#endif /*HAS_LC3*/

#ifdef HAS_CSV
    {
        .facility = CSV,
        .name = "CSV",
    },
#endif /*HAS_CSV*/

#ifdef HAS_MAX9860
    {
        .facility = MAX9860,
        .name = "MAX9860",
    },
#endif /*HAS_MAX9860*/

#ifdef HAS_HASHSET
    {
        .facility = HASHSET,
        .name = "HashSet",
    },
#endif /*HAS_HASHSET*/

#ifdef HAS_SET
    {
        .facility = SET,
        .name = "Set",
    },
#endif /*HAS_SET*/

#ifdef HAS_SW_NOR_FLASH
    {
        .facility = SW_NOR_FLASH,
        .name = "SwNOR-Flash",
    },
#endif /*HAS_SW_NOR_FLASH*/

#ifdef HAS_HEALTH_MONITOR
    {
        .facility = HMON,
        .name = "HMON",
    },
#endif /*HAS_HEALTH_MONITOR*/

#ifdef HAS_FOURIER_SERIES
    {
        .facility = FOURIER_SERIES,
        .name = "FOURIER_SERIES",
    },
#endif /*HAS_FOURIER_SERIES*/

#ifdef HAS_DECADRIVER
    {
        .facility = DECA,
        .name = "DECA",
    },
#endif /*HAS_DECADRIVER*/

#ifdef HAS_FREE_RTOS
    {
        .facility = FREE_RTOS,
        .name = "FreeRTOS",
    },
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_RTOS
    {
        .facility = RTOS,
        .name = "RTOS",
    },
#endif /*HAS_RTOS*/

#ifdef HAS_BH1750
    {
        .facility = BH1750,
        .name = "bh1750",
    },
#endif /*HAS_BH1750*/

#ifdef HAS_MX25R6435F
    {
        .facility = MX25R6435F,
        .name = "mx25r6435f",
    },
#endif /*HAS_MX25R6435F*/

#ifdef HAS_NVS
    {
        .facility = NVS,
        .name = "NVS",
    },
#endif /*HAS_NVS*/

#ifdef HAS_SERIAL
    {
        .facility = SERIAL,
        .name = "Serial",
    },
    {
        .facility = COM,
        .name = "COM",
    },
#endif /*HAS_SERIAL*/

#ifdef HAS_SOLVER
    {
        .facility = SOLVER,
        .name = "SOLVER",
    },
#endif /*HAS_SOLVER*/

#ifdef HAS_SSD1306
    {
        .facility = SSD1306,
        .name = "Ssd1306",
    },
#endif /*HAS_SSD1306*/

#ifdef HAS_CIRCULAR_BUFFER
    {
        .facility = CIRCULAR_BUFFER,
        .name = "CircularBuffer",
    },
#endif /*HAS_CIRCULAR_BUFFER*/

#ifdef HAS_DISTANCE
    {
        .facility = DISTANCE,
        .name = "Distance",
    },
#endif /*HAS_DISTANCE*/

#ifdef HAS_SWD
    {
        .facility = SWD,
        .name = "SWD",
    },
#endif /*HAS_SWD*/

#ifdef HAS_TPA2013D1
    {
        .facility = TPA2013D1,
        .name = "TPA2013D1",
    },
#endif /*HAS_TPA2013D1*/

#ifdef HAS_USB_AUDIO
    {
        .facility = USB_AUDIO,
        .name = "UsbAudio",
    },
#endif /*HAS_USB_AUDIO*/

#ifdef HAS_FAT_FS
    {
        .facility = FAT_FS,
        .name = "FatFs",
    },
    {
        .facility = DISK,
        .name = "Disk",
    },
#endif /*HAS_FAT_FS*/

#ifdef HAS_RLE
    {
        .facility = RLE,
        .name = "Rle",
    },
#endif /*HAS_RLE*/

#ifdef HAS_USB_HOST
    {
        .facility = USB_HOST,
        .name = "UsbHost",
    },
#endif /*HAS_USB_HOST*/

#ifdef HAS_USB
    {
        .facility = USB,
        .name = "Usb",
    },
#endif /*HAS_USB*/

#ifdef HAS_VOLTAGE_DIVIDER
    {
        .facility = VOLTAGE_DIVIDER,
        .name = "VoltageDivider",
    },
#endif /*HAS_VOLTAGE_DIVIDER*/

#ifdef HAS_ASICS
    {
        .facility = ASICS,
        .name = "ASICS",
    },
#endif /*HAS_ASICS*/

#ifdef HAS_DTMF
    {
        .facility = DTMF,
        .name = "DTMF",
    },
#endif /*HAS_DTMF*/

#ifdef HAS_DASHBOARD
    {
        .facility = DASHBOARD,
        .name = "DashBoard",
    },
#endif /*HAS_DASHBOARD*/

#ifdef HAS_RS2058
    {
        .facility = RS2058,
        .name = "RS2058",
    },
#endif /*HAS_RS2058*/

#ifdef HAS_MODULATOR
    {
        .facility = MODULATOR,
        .name = "MODULATOR",
    },
#endif /*HAS_MODULATOR*/

#ifdef HAS_DISPLAY
    {
        .facility = DISPLAY,
        .name = "DISPLAY",
    },
#endif /*HAS_DISPLAY*/

#ifdef HAS_PC
    {
        .facility = PC,
        .name = "PC",
    },
#endif /*HAS_PC*/

#ifdef HAS_LIGHT_NAVIGATOR
    {
        .facility = LIGHT_NAVIGATOR,
        .name = "LiNav",
    },
#endif /*HAS_LIGHT_NAVIGATOR*/

#ifdef HAS_MAX98357
    {
        .facility = MAX98357,
        .name = "MAX98357",
    },
#endif /*HAS_MAX98357*/

#ifdef HAS_SUPER_CYCLE
    {
        .facility = SUPER_CYCLE,
        .name = "SuperLoop",
    },
#endif /*HAS_SUPER_CYCLE*/

#ifdef HAS_DW1000_GPIO
    {
        .facility = DW1000_GPIO,
        .name = "Dw1kGpio",
    },
#endif /*HAS_DW1000_GPIO*/

#ifdef HAS_SS_TWR
    {
        .facility = SS_TWR,
        .name = "SsTwr",
    },
#endif /*HAS_SS_TWR*/

#ifdef HAS_FIR
    {
        .facility = FIR,
        .name = "FIR",
    },
#endif /*HAS_FIR*/

#ifdef HAS_QSPI
    {
        .facility = QSPI,
        .name = "QSPI",
    },
#endif /*HAS_QSPI*/

#ifdef HAS_PDM
    {
        .facility = PDM,
        .name = "PDM",
    },
#endif /*HAS_PDM*/

#ifdef HAS_LIMITER
    {
        .facility = LIMITER,
        .name = "Limiter",
    },
#endif /*HAS_LIMITER*/

#ifdef HAS_DS_TWR
    {
        .facility = DS_TWR,
        .name = "DsTwr",
    },
#endif /*HAS_DS_TWR*/

#ifdef HAS_SCHEDULER
    {
        .facility = SCHEDULER,
        .name = "Scheduler",
    },
#endif /*HAS_SCHEDULER*/

#ifdef HAS_SW_DAC
    {
        .facility = SW_DAC,
        .name = "SwDAC",
    },
#endif /*HAS_SW_DAC*/

#ifdef HAS_BASE16
    {
        .facility = BASE16,
        .name = "BASE16",
    },
#endif /*HAS_BASE16*/

#ifdef HAS_UWB
    {
        .facility = UWB,
        .name = "UWB",
    },
#endif /*HAS_UWB*/

#ifdef HAS_DS3231
    {
        .facility = DS3231,
        .name = "Ds3231",
    },
#endif /*HAS_DS3231*/

#ifdef HAS_SD_CARD
    {
        .facility = SD_CARD,
        .name = "SdCard",
    },
#endif /*HAS_SD_CARD*/

#ifdef HAS_INTERVAL
    {
        .facility = INTERVAL,
        .name = "Interval",
    },
#endif

#ifdef HAS_PHOTORESISTOR
    {
        .facility = PHOTORESISTOR,
        .name = "PhotoResistor",
    },
#endif /*HAS_PHOTORESISTOR*/

#ifdef HAS_LIGHT_SENSOR
    {
        .facility = LIGHT_SENSOR,
        .name = "LightSensor",
    },
#endif /*HAS_LIGHT_SENSOR*/

#ifdef HAS_PLANETARIUM
    {
        .facility = PLANETARIUM,
        .name = "Planetarium",
    },
#endif /*HAS_PLANETARIUM*/
};

static uint32_t facility_get_cnt(void) { return ARRAY_SIZE(FacilityInfo); }

const char* facility2str_lut(facility_t facility) {
    const char* name = NULL;
    uint8_t i = 0;
    uint32_t cnt = facility_get_cnt();
    for(i = 0; i < cnt; i++) {
        if(facility == FacilityInfo[i].facility) {
            name = FacilityInfo[i].name;
            break;
        }
    }
    return name;
}

#ifdef HAS_LOG_DIAG
const char* Facility2Str(facility_t facility) {
    const char* facility_str = NULL;

    facility_str = facility2str_lut(facility);
    // int ret = strcmp(facility_str, "?");
    if(NULL == facility_str) {

        switch(facility) {

#ifdef HAS_MATH
        case MATH:
            facility_str = "MATH";
            break;
#endif /**/

#ifdef HAS_AUTO_VOLUME
        case AUTO_VOLUME:
            facility_str = "AutoVolume";
            break;
#endif /*HAS_AUTO_VOLUME*/

#ifdef HAS_LIFO
        case LIFO:
            facility_str = "LIFO";
            break;
#endif /*HAS_LIFO*/

#ifdef HAS_XML
        case XML:
            facility_str = "XML";
            break;
#endif /*HAS_XML*/

#ifdef HAS_KEEPASS
        case KEEPASS:
            facility_str = "KEEPASS";
            break;
        case CRY:
            facility_str = "CRY";
            break;
#endif /*HAS_KEEPASS*/

#ifdef HAS_MIC2026
        case MIC2026:
            facility_str = "MIC2026";
            break;
#endif /*HAS_MIC2026*/

#ifdef HAS_FLASH
        case LG_FLASH:
            facility_str = "FLASH";
            break;
#endif /*HAS_FLASH*/

#ifdef HAS_BUTTON
        case BUTTON:
            facility_str = "Button";
            break;
#endif

#ifdef HAS_HID
        case HID:
            facility_str = "HID";
            break;
#endif

#ifdef HAS_SDIO
        case LG_SDIO:
            facility_str = "SDIO";
            break;
#endif /*HAS_SDIO*/

#ifdef HAS_RDS
        case RDS:
            facility_str = "RDS";
            break;
#endif

#ifdef HAS_IPC
        case IPC:
            facility_str = "IPC";
            break;
#endif

#ifdef HAS_HEAP
        case HEAP:
            facility_str = "HEAP";
            break;
#endif

#ifdef HAS_INT
        case LG_INT:
            facility_str = "INT";
            break;
#endif /**/

#ifdef HAS_SI4737
        case SI4737:
            facility_str = "Si4737";
            break;
#endif

#ifdef HAS_DEBUG
        case DBG:
            facility_str = "DBG";
            break;
#endif

#ifdef HAS_RTK
        case RTK:
            facility_str = "RTK";
            break;
#endif

#ifdef HAS_TIMER
        case TIMER:
            facility_str = "Timer";
            break;
#endif

#ifdef HAS_KEYLOG
        case KEYLOG:
            facility_str = "KeyLog";
            break;
#endif

#ifdef HAS_GPIO
        case GPIO:
            facility_str = "GPIO";
            break;
#endif

#ifdef HAS_CLOCK
        case CLK:
            facility_str = "CLK";
            break;
#endif

#ifdef HAS_BC127
        case BC127:
            facility_str = "BC127";
            break;
#endif

#ifdef HAS_DIAG
        case DIAG:
            facility_str = "DIAG";
            break;
#endif /**/

#ifdef HAS_IWDG
        case LG_IWDG:
            facility_str = "IWDG";
            break;
#endif

#ifdef HAS_ADC
        case LG_ADC:
            facility_str = "ADC";
            break;
#endif

#ifdef HAS_DMA
        case DMA:
            facility_str = "DMA";
            break;
#endif /**/

#ifdef HAS_PWM
        case PWM:
            facility_str = "PWM";
            break;
#endif /**/

#ifdef HAS_RELAY
        case RELAY:
            facility_str = "Relay";
            break;
#endif /**/

#ifdef HAS_BATT
        case BATT:
            facility_str = "BATT";
            break;
#endif /**/

#ifdef HAS_SYSTICK
        case LG_SYSTICK:
            facility_str = "SysTick";
            break;
#endif

#ifdef HAS_BOOT
        case BOOT:
            facility_str = "BOOT";
            break;
#endif /**/

#ifdef HAS_FLASH_FS
        case FLASH_FS:
            facility_str = "FLASH_FS";
            break;
#endif /**/

#ifdef HAS_FDA801
        case FDA801:
            facility_str = "FDA801";
            break;
#endif /*HAS_FDA801*/

#ifdef HAS_NMEA
        case NMEA:
            facility_str = "NMEA";
            break;
#endif /**/

#ifdef HAS_ZEPHYR_RTOS
        case ZEPHYR_RTOS:
            facility_str = "ZephyrRtos";
            break;
#endif /*HAS_ZEPHYR_RTOS*/

#ifdef HAS_I2C
        case I2C:
            facility_str = "I2C";
            break;
#endif

#ifdef HAS_MASS_STORAGE_CLASS
        case MSD:
            facility_str = "MSD";
            break;
#endif

#ifdef HAS_SOFTWARE_TIMER
        case SW_TIMER:
            facility_str = "SwTimer";
            break;
#endif

#ifdef HAS_SI4703
        case SI4703:
            facility_str = "Si4703";
            break;
#endif

#ifdef HAS_I2S
        case I2S:
            facility_str = "I2S";
            break;
        case I2S_FULL_DUPLEX:
            facility_str = "I2sFullDuplex";
            break;
#endif

#ifdef HAS_LED
        case LED:
            facility_str = "LED";
            break;
#endif

#ifdef HAS_RTC
        case LG_RTC:
            facility_str = "RTC";
            break;
#endif

#ifdef HAS_RTCM
        case RTCM:
            facility_str = "RTCM";
            break;
#endif
        case SYS:
            facility_str = "SYS";
            break;
#ifdef HAS_UART
        case UART:
            facility_str = "UART";
            break;
#endif

#ifdef HAS_CRC8
        case CRC8:
            facility_str = "CRC8";
            break;
#endif

#ifdef HAS_CRC24
        case CRC24:
            facility_str = "CRC24";
            break;
#endif

#ifdef HAS_CLI
        case CLI:
            facility_str = "CLI";
            break;
#endif

#ifdef HAS_RETX
        case RETX:
            facility_str = "RETX";
            break;
#endif

#ifdef HAS_GNSS
        case GNSS:
            facility_str = "GNSS";
            break;
#endif

#ifdef HAS_UBX
        case UBX:
            facility_str = "UBX";
            break;
#endif

#ifdef HAS_ZED_F9P
        case ZED_F9P:
            facility_str = "ZEDF9P";
            break;
#endif

#ifdef HAS_TIME
        case TIME:
            facility_str = "TIME";
            break;
#endif

#ifdef HAS_TBFP
        case TBFP:
            facility_str = "TBFP";
            break;
#endif

#ifdef HAS_SALSA20
        case SALSA20:
            facility_str = "SALSA20";
            break;
#endif

#ifdef HAS_SX1262
        case SX1262:
            facility_str = "SX1262";
            break;
#endif

#ifdef HAS_PARAM
        case PARAM:
            facility_str = "PARAM";
            break;
#endif

#ifdef HAS_LOAD
        case LOAD:
            facility_str = "LOAD";
            break;
#endif

#ifdef HAS_PMIC
        case PMIC:
            facility_str = "PMIC";
            break;
#endif

#ifdef HAS_GFSK
        case GFSK:
            facility_str = "GFSK";
            break;
#endif

#ifdef HAS_CRC
        case LG_CRC:
            facility_str = "CRC";
            break;
#endif

#ifdef HAS_TEST
        case TEST:
            facility_str = "TEST";
            break;
#endif

#ifdef HAS_SPI
        case SPI:
            facility_str = "SPI";
            break;
#endif

#ifdef HAS_CAN
        case CAN:
            facility_str = "CAN";
            break;
#endif

#ifdef HAS_CALENDAR
        case LG_CAL:
            facility_str = "CALENDAR";
            break;
#endif

#ifdef HAS_COM
        case COM:
            facility_str = "COM";
            break;
#endif

#ifdef HAS_PASTILDA
        case PASTILDA:
            facility_str = "Pas~";
            break;
#endif /*HAS_PASTILDA*/

#ifdef HAS_LORA
        case LORA:
            facility_str = "LoRa";
            break;
#endif

#ifdef HAS_RADIO
        case RADIO:
            facility_str = "Radio";
            break;
#endif

#ifdef HAS_WM8731
        case WM8731:
            facility_str = "WM8731";
            break;
#endif /*HAS_WM8731*/

#ifdef HAS_FIFO
        case FIFO:
            facility_str = "FIFO";
            break;
#endif

        case ALL_FACILITY:
            facility_str = "*";
            break;
        default:
            facility_str = "?";
            break;
        }
    }
    return facility_str;
}
#endif

static const ProgTypeInfo_t ProgTypeInfo[] = {
    {
        .fw_type = BUILD_TYPE_UNDEF,
        .name = "??",
    },
    {
        .fw_type = BUILD_TYPE_MBR,
        .name = "Mbr",
    },
    {
        .fw_type = BUILD_TYPE_BOOTLOADER,
        .name = "BootLoader",
    },
    {
        .fw_type = BUILD_TYPE_GENERIC,
        .name = "Generic",
    },
    {
        .fw_type = BUILD_TYPE_DESKTOP_APP,
        .name = "DesktopApp",
    },
    {
        .fw_type = BUILD_TYPE_GENERIC_APP,
        .name = "GenericApp",
    },
    {
        .fw_type = BUILD_TYPE_GENERIC_NET,
        .name = "GenericNet",
    },
};

const char* ProgType2str(BuildType_t fw_type) {
    const char* name = "??";
    uint8_t i = 0;
    uint32_t cnt = ARRAY_SIZE(ProgTypeInfo);
    for(i = 0; i < cnt; i++) {
        if(fw_type == ProgTypeInfo[i].fw_type) {
            name = ProgTypeInfo[i].name;
            break;
        }
    }
    return name;
}

uint16_t facility_max_name(void) {
    uint16_t max_name = 0;
    uint16_t cur_name_len = 0;
    facility_t facil = UNKNOWN_FACILITY;
    for(facil = UNKNOWN_FACILITY; facil < ALL_FACILITY; facil++) {
        cur_name_len = strlen(Facility2Str(facil));
        max_name = MAX(max_name, cur_name_len);
    }
    return max_name;
}

bool system_diag(void) {
    bool res = false;
    LOG_INFO(SYS, "SwCompCnt:%u", ALL_FACILITY);
    return res;
}
