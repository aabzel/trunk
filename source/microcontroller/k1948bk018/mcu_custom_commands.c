#include "mcu_custom_commands.h"

#include "k1948bk018_diag.h"
#include "microcontroller.h"

bool k1948bk018_diag_command(int32_t argc, char* argv[]){
	bool res = false ;
	res = k1948bk018_diag();
	return res;
}


bool mik32_launch_eeprom_command(int32_t argc, char* argv[]){
	bool res = false;
	res = mik32_launch_eeprom();
	return res;
}
