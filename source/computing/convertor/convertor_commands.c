#include "convertor_commands.h"

#include "convert.h"
#include "log.h"
#include "float_types.h"

bool convertor_hex_command(int32_t argc, char* argv[]){
	bool res = false;
	uint32_t  value=0;
	if (1==argc) {
    	res=try_str2uint32_hex(argv[0], &value);
	}

	if (res) {
		cli_printf("Hex: 0x%x, Dec: %d, Bin: 0b%s" CRLF, value, value, utoa_bin32(value));
	}
	return res;
}

bool convertor_dec_command(int32_t argc, char* argv[]){
	bool res = false;
	return res;
}

bool convertor_bin_command(int32_t argc, char* argv[]){
	bool res = false;
	return res;
}

bool convertor_oct_command(int32_t argc, char* argv[]){
	bool res = false;
	return res;
}

static const char* Sign2Str(uint8_t sign){
	const char* name = "?";
	switch(sign){
	case 0: name = "+";break;
	case 1: name = "-";break;
	}
	return name;
}

/*cf 0.15625*/
bool convertor_float_command(int32_t argc, char* argv[]){
	bool res = false;
	float value = 0.0;
	if (1==argc) {
    	res=try_str2float(argv[0], &value);
	}

	if(res){
		FloatUnion_t FltUn;
		(void)FltUn;
		FltUn.flt = value;

		cli_printf("Value:%f,Sign:%u,Significand:%u,Exponent:%u,Bin:0b%s" CRLF,
				FltUn.flt,
				FltUn.sign,
				FltUn.significand,
				FltUn.exponent,
				utoa_bin32(FltUn.u32));

		cli_printf("Sign:%u,%s" CRLF,FltUn.sign, Sign2Str(FltUn.sign));
		cli_printf("Significand:%u,0b%s" CRLF, FltUn.significand, utoa_bin24(FltUn.significand));
		cli_printf("Exponent:%u,0b%s" CRLF,FltUn.exponent, utoa_bin8(FltUn.exponent));

	}
	return res;
}
