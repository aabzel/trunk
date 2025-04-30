#ifndef SPIFI_MIK32_REGISTER_TYPES_H
#define SPIFI_MIK32_REGISTER_TYPES_H

#ifdef __cplusplus
extern "C" {
#endif


//Table 104   CTRL control register
typedef union {
    uint32_t dword;
    struct{
        uint32_t res1 :16;/*15:0  Reserved*/
        uint32_t cshigh :4;/*19:16 The number of SPIFI_SCK signal periods minus one that the SPIFI_CS signal remains inactive before the command execution begins*/
        uint32_t cache_en :1;/*20 Cache enable bit*/
        uint32_t d_cache_dis :1;/*21 Data caching disable bit (AHB transactions for which the HPROT[0] signal = 1):*/
        uint32_t inten :1;/*22 Interrupt enable bit when instruction execution is complete*/
        uint32_t mode3 :1;/*23 Mode bit 3*/
        uint32_t sck_div :3;/*26:24 Divider for obtaining the SPIFI_SCK clock signal from the system clock signal HCLK.*/
        uint32_t prftch_dis :1;/*27 Cache Prefetch Enable Bit*/
        uint32_t dual :1;/*28 Protocol Select Bit:*/
        uint32_t rfclk :1;/*29 Active edge selection bit for input data gating:*/
        uint32_t fbclk :1;/*30 Output Clock Buffer Input Strobe Signal Select Bit:*/
        uint32_t dmaen:1;   /*31  SPIFI controller DMA request enable bit*/
    };
} SpiFiRegCtrl_t;

//Table 111   STAT Status Register
typedef union {
    uint32_t dword;
    struct {
        uint32_t mcinit:1 ; /*0 The bit is set to "1" if the software has
        successfully written to the memory command register.
        The bit is cleared by a hardware reset or by setting the RESET bit to "1".*/
        uint32_t cmd:1 ; /*1 The bit is set to '1' if the software has successfully written to the command register.*/
        uint32_t res1:2 ; /*3:2 xxxxx*/
        uint32_t reset:1 ; /*4 The bit is intended to interrupt the current command of the peripheral mode
         or memory mode.
         The bit is cleared when the controller is ready to execute a new command.*/
        uint32_t intrq:1 ; /*5 Writing a "1" to the bit clears the interrupt request from the SPIFI controller.*/
        uint32_t res2:18 ; /*23:6 xxxxx*/
        uint32_t version:8 ; /*31:24 SPIFI controller version (read-only field)*/
    };
} SpiFiRegStat_t;


//Table 105   CMD command register
typedef union {
    uint32_t dword;
    struct{
        uint32_t datalen :14;/*13:0 xxxx*/
        uint32_t poll :1;/*14 xxxx*/
        uint32_t dout :1;/*15 xxxx*/
        uint32_t intlen :3;/*18:16 xxxx*/
        uint32_t fieldform :2;/*20:19 xxxx*/
        uint32_t frameform :3;/*23:21 xxxx*/
        uint32_t opcode :8;/*31:24 xxxx*/
    };
} SpiFiRegCmd_t;

//Table 109   DATA register
typedef union {
    uint32_t dword;
    union {
        uint32_t data32 ; /*31:0 Input or output data*/
        uint8_t data8[4] ; /*31:0 Input or output data*/
        uint16_t data16[2] ; /*31:0 Input or output data*/
    };
} SpiFiRegData_t;


//Table 106   ADDRESS address register
typedef union {
    uint32_t dword;
    struct{
        uint32_t address ;/*31:0 Command execution address*/
    };
} SpiFiRegAddress_t;


//Table 107   Intermediate data register
typedef union {
    uint32_t dword;
    struct {
        uint32_t idata ;/*31:0 Interim data*/
    };
} SpiFiRegIdata_t;

//Table 108   Upper Cache Address Boundary Register
typedef union {
    uint32_t dword;
    struct {
        uint32_t climit ; /*31:0 Upper limit of cached memory*/
    };
} SpiFiRegClimit_t;




typedef union {
      volatile uint8_t  DATA8[4];
      volatile uint16_t DATA16[2];
      volatile uint32_t DATA32;
}SpiFiData_t;


//Table 110   MCMD Memory Command Register
typedef union {
    uint32_t dword;
    struct {
        uint32_t res:14 ; /*13:0 Operation code (not used for some FRAMEFORM field values)*/
        uint32_t poll:1 ; /*14 the bit must be set to "0"*/
        uint32_t dout:1 ; /*15 The bit must be set to "0"*/
        uint32_t intlen:3 ; /*18:16 Number of bytes of intermediate data
        (they are stored in the IDATA register).
        If the number of bytes is greater than the IDATA register can store,
         the remainder is filled with zero values*/
        uint32_t fieldform:2 ; /*20:19 Command field output format*/
        uint32_t frameform:3 ; /*23:21 Command opcode and address field control bit:*/
        uint32_t opcode: 8; /*31:24 xxxxx*/
    };
} SpiFiRegMcmd_t;


#ifdef __cplusplus
}
#endif

#endif /* SPIFI_MIK32_REGISTER_TYPES_H  */
