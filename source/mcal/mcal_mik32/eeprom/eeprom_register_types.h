#ifndef EEPROM_REGISTER_TYPES_H
#define EEPROM_REGISTER_TYPES_H

#include <stdint.h>


/*Table 126 EEDAT Data Read/Write Register */
typedef union {
    uint32_t dword;
    struct {
        uint32_t DATA;      /*  bit 31:0 During reading/writing of this register,
                                          the address (EEA) is automatically incremented.    */
    };
}EepromReg_EEDAT_t;

/*Table 127 EEA Page Address Register */
typedef union {
    uint32_t dword;
    struct{
        uint32_t RES1 :2;       /*  bit 1:0   Reserved    */
        uint32_t DWORD_ADDR :11;      /*  bit 12:2  Address of the dword to perform erase/program/read.
                                              Can address 2048 words (8192 bytes).   */
        uint32_t RES2 :19;      /*  bit 31:13 Reserved    */
    };
}EepromReg_EEA_t;

/*Table 128  EECON Control Register */
typedef union {
    uint32_t dword;
    struct {
        uint32_t EX :1;        /*  bit 0 Starting the procedure    */
        uint32_t OP :2;        /*  bit 2:1 Select procedure    */
        uint32_t WRBEH :2;     /*  bit 4:3  Behavior of the erase/program operation:    */
        uint32_t APBNWS :1;    /*  bit 5 Disabling insertion of wait ticks in APB exchange process when
                                         the write buffer is full    */
        uint32_t DISECC :1;    /*  bit 6 Disabling the error correction circuit
                                         during execution of the requested procedure.    */
        uint32_t BWE :1;       /*  bit 7 Enable writing to the buffer.    */
        uint32_t IESERaR :1;   /*  bit 8 Enable interrupt request when SERR flag is raised:    */
        uint32_t RES :23;      /*  bit 31:9       */
    };
}EepromReg_EECON_t;

/*Table 129 � EESTA Status Register */
typedef union {
    uint32_t dword;
    struct{
        uint32_t BSY :1;       /*  bit 0 Block busy (requested operation in progress)    */
        uint32_t SERR :1;      /*  bit 1 Single (correctable) error indicator.    */
        uint32_t RES :30;      /*  bit 31:2       */
    };
}EepromReg_EESTA_t;


/*Table 130 � EERB Read Word Correction Bit Register */
typedef union {
    uint32_t dword;
    struct{
        uint32_t CORRECT :6;      /*  bit 5:0  Contains 6 bits of correction of the last read word    */
        uint32_t RES :26;         /*  bit 31:6       */
    };
}EepromReg_EERB_t;


/*Table 131 � Hard IP EEADJ Block Settings Register  */
typedef union {
    uint32_t dword;
    struct {
        uint32_t OSCX2 :1;          /*  bit 0 Increasing the clock frequency    */
        uint32_t HivCtl :3;         /*  bit 3:1 Adjusting the level of the internal HIV signal    */
        uint32_t PlusImix :1;       /*  bit 4 Analog signal monitoring unit control signal    */
        uint32_t VboostCtl :2;      /*  bit 6:5 The most significant bit is the adjustment of the
                                                internal signal Vboost, the least significant bit is the control signal of the
                                                analog signal monitoring unit    */
        uint32_t MinusImix :1;      /*  bit 7 Analog signal monitoring unit control signal    */
        uint32_t DummyCtl :2;       /*  bit 9:8 Adjusting the capture moment of the output data    */
        uint32_t VbgCtl :3;         /*  bit 12:10  Adjusting the bandgap reference voltage    */
        uint32_t RefCtl :3;         /*  bit 15:13 Adjusting the current used for reading    */
        uint32_t VcgCtl :3;         /*  bit 18:16  Adjustment of the voltage supplied to the control gates during reading    */
        uint32_t CGSTRICT :1;       /*  bit 19 Enabling fine-tuning of the voltage used when reading    */
        uint32_t VppCtl :2;         /*  bit 21:20  Adjusting the high voltage rise time    */
        uint32_t StrictCtl :3;      /*  bit 24:22  Fine-tuning the current used for reading    */
        uint32_t StopEe :1;         /*  bit 25 Switching Hard IP to low power mode    */
        uint32_t IddqEn :1;         /*  bit 26 Putting Hard IP into quiescent state for Iddq testing    */
        uint32_t RES :5;            /*  bit 31:27       */
    };
}EepromReg_EEADJ_t;


/*Table 132 � Register for adjusting the duration of the read and fill
 * procedures of the NCYCRL write buffer*/
typedef union {
    uint32_t dword;
    struct{
        uint32_t N_LD ;       /*  bit 7:0  xxxxx      */
        uint32_t N_R_1 ;      /*  bit 15:8 xxxxx      */
        uint32_t N_R_2 ;      /*  bit 23:16 xxxxx     */
        uint32_t RES   ;      /*  bit 31:24  xxxxx    */
    };
}EepromReg_NCYCRL_t;


/*Table 133 � Register 1 for adjusting the duration of erase and
 * programming procedures NCYCEP1 */
typedef union {
    uint32_t dword;
    struct {
        uint32_t N_EP_1 :18;      /*  bit 17:0  Duration of the high level of the BUSY signal (Hard IP input) in
                                                clocks.    */
        uint32_t RES :14;         /*  bit 31:18 xxxxx    */
    };
}EepromReg_NCYCEP1_t;


/* Table 134 � Register 2 for adjusting the duration of erase and
   programming procedures NCYCEP2  */
typedef union {
    uint32_t dword;
    struct {
        uint32_t N_EP_2 :11;   /*  bit 10:0   Delay between the falling edges of BUSY
                                              and HvonValid (Hard IP inputs) in clock cycles.    */
        uint32_t RES :21;      /*  bit 31:11  xxxxx    */
    };
}EepromReg_NCYCEP2_t;


#endif /* EEPROM_REGISTER_TYPES_H  */
