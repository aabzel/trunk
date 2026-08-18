#include "si4737_config.h"
#include "si4737_types.h"
#include "radio_stations_rus.h"

const Si4737Config_t Si4737Config={
 .PwgUpArg1.func=0,
 .rds_int_fifo_cnt=1,
 .PwgUpArg1.xoscen=USE_EXTERNAL_RCLK, /**/
 .PwgUpArg1.patch=PATCH_BOOT_NORM,
 .PwgUpArg1.gpo2oen=GPO2_OUT_DISABLED,
 .PwgUpArg1.cts_ien=CTS_INT_DISABLED,
 .OpMode=OP_MODE_ANALOG_AUDIO_OUTPUT,
 .valid=true,
 .fm_freq_mhz=RADIO_BUSINESS,
 .rds_en= true,
};

Si4737Handler_t Si4737Handler;
