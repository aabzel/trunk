

COMPILE_IAR_OPT += -DHAS_IAR
#COMPILE_IAR_OPT += -D HAS_IAR
COMPILE_IAR_OPT += -D__ICCARM__=1
#COMPILE_IAR_OPT += -D __ICCARM__

COMPILE_IAR_OPT +=--fpu VFPv4_sp
COMPILE_IAR_OPT +=--cpu=Cortex-M4  
COMPILE_IAR_OPT +=--endian=little 
COMPILE_IAR_OPT +=--debug 
COMPILE_IAR_OPT +=-e 
COMPILE_IAR_OPT +=-On 
COMPILE_IAR_OPT +=--cpu_mode=thumb
COMPILE_IAR_OPT +=--no_inline 

 

# Turn on locale support. 
COMPILE_IAR_OPT += -D_DLIB_FULL_LOCALE_SUPPORT=1

# Turn on FILE descriptor support. 
COMPILE_IAR_OPT += -D_DLIB_FILE_DESCRIPTOR=1

# Turn on multibyte formatting. 
COMPILE_IAR_OPT += -D_DLIB_FORMATTED_MULTIBYTE=1

# Turn on support for hex-floats in strtod. 
COMPILE_IAR_OPT += -D_DLIB_STRTOD_HEX_FLOAT=1




COMPILE_IAR_OPT +=--no_cse 
COMPILE_IAR_OPT +=--no_unroll 
COMPILE_IAR_OPT +=--no_code_motion 
COMPILE_IAR_OPT +=--no_tbaa 
COMPILE_IAR_OPT +=--no_clustering 
COMPILE_IAR_OPT +=--no_scheduling 


COMPILE_IAR_OPT +=--diag_suppress=Pe029
COMPILE_IAR_OPT +=--diag_suppress=Pe1345
COMPILE_IAR_OPT +=--diag_suppress=Pe513
COMPILE_IAR_OPT +=--diag_suppress=Pe144
COMPILE_IAR_OPT +=--diag_suppress=Pe188


#COMPILE_IAR_OPT += --dlib_config C:/Program Files (x86)/IAR Systems/Embedded Workbench 8.1/arm/inc/c/ DLib_Config_Full.h

ASM_FLAGS +=  -s+ 
#ASM_FLAGS += -M<> 
ASM_FLAGS += -w+ 
ASM_FLAGS += -r 
ASM_FLAGS += --cpu Cortex-M4 
ASM_FLAGS += --fpu VFPv4_sp 



#LDFLAGS +=--semihosting 
LDFLAGS +=--semihosting=none
#LDFLAGS +=--entry __iar_program_start 
#LDFLAGS +=--redirect _Printf=_PrintfFull 
#LDFLAGS +=--redirect _Scanf=_ScanfFull 
LDFLAGS +=--entry Reset_Handler 
LDFLAGS +=--text_out locale 
LDFLAGS +=--no_out_extension
LDFLAGS +=--map $(BUILD_DIR)/$(TARGET).map
LDFLAGS +=--config $(LDSCRIPT)
#LDFLAGS +=--semihosting 
#LDFLAGS +=--redirect __iar_sh_stdout=__iar_sh_stdout_swo 
LDFLAGS +=--no_exceptions 
LDFLAGS +=--no_vfe 
LDFLAGS +=--redirect _Printf=_PrintfTiny 
LDFLAGS +=--redirect _Scanf=_ScanfSmall 


CFLAGS += $(COMPILE_IAR_OPT)

