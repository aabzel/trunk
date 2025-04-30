#ifndef BOOT_CONST_H
#define BOOT_CONST_H

#ifdef __cplusplus
extern "C" {
#endif

#define APP_LAYNCH_TRY 7U
#define FINE_START_TIME_OUT_MS 3000U
//#define BOOT_PERIOD_US 2000000

typedef enum  {
    BOOT_CMD_STAY_ON = 1,
    BOOT_CMD_LAUNCH_APP = 2,
    BOOT_CMD_LAUNCH_APP_CRC = 3,
    BOOT_CMD_STACK_ERROR_STAY_ON = 4,
	BOOT_CMD_START_ERROR_STAY_ON = 5,

    BOOT_CMD_ENDEF = 0
} BootCmd_t;

#ifdef __cplusplus
}
#endif

#endif /* BOOT_CONST_H */
