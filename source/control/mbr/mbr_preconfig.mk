
ifneq ($(MBR_PRECONFIG_INC),Y)
    MBR_PRECONFIG_INC=Y
    # MBR can contain ASICS (XPI MIK32)

    # $(error MBR= $(MBR))
    #PACK_PROGRAM=Y
    MBR=Y
    NORTOS=Y
    MICROCONTROLLER=Y
    #TIME=Y
    #GPIO=Y
    #LIMITER=Y
    #FLASH=Y
    LIBC_NOSYS=Y

    #LED=Y
    #NVS=Y
    #FLASH_FS=Y
    #INTERRUPT=Y
    #PARAM=Y
    #LOG=N

    CLI=N
    CRC8=N
    CRC=N
    LOG=N
    UTILS_EXT=N
    #DEBUGGER=N
    ARRAY=N
 
    UART=N
    CONNECTIVITY=N
endif