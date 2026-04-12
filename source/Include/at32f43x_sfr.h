//**************************************************************************************************
// @Module        Special Function Registers file
// @Filename      at32f43x_sfr.h
//--------------------------------------------------------------------------------------------------
// @Platform      Artery AT32F4 (AT32F435/437)
//--------------------------------------------------------------------------------------------------
// @Description   Register definitions. Based on AT32F435/437 Series Reference Manual v2.01
//                Example instantiation and use:
//                 <MODULE>.<REGISTER>.B.<BIT> = 1;
//                 <MODULE>.<REGISTER>.R       = 0x10000000;
//--------------------------------------------------------------------------------------------------
// @Version       1.7.0
//--------------------------------------------------------------------------------------------------
// @Date          10.03.2023
//--------------------------------------------------------------------------------------------------
// @History       Version  Author      Comment
// 20.06.2022     1.0.0    MAV         First version.
// 22.06.2022     1.1.0    MAV         Fix DAC.CTRL and USART.CTRL2 registers. Replace non-ASCII
//                                     characters in comments. Add reserved word to DMA channels array
// 29.06.2022     1.2.0    MAV         Added RTC module. Refactoring TIM registers. Change timers names
// 29.06.2022     1.3.0    MAV         Fixed some errors in the ADC and DMA registers. Added 2-nd DMA
// 04.07.2022     1.4.0    MAV         Bit fields type changed from vuint32_t to "volatile U32"
// 18.07.2022     1.5.0    MAV         Fixed base address of the DMA2 module
// 06.03.2023     1.6.0    MAV         Added QSPI module registers
// 10.03.2023     1.7.0    MAV         Added some fixes in QSPI registers
// 30.10.2023     1.7.1    LSD         Added DEBUG register
//**************************************************************************************************

#ifndef AT32F43X_SFR_H
#define AT32F43X_SFR_H

#include "compiler.h"



/******************************************************************************/
/*                Analog-to-Digital converter (ADC) memory map                */
/******************************************************************************/
struct ADC_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 VMOR :1;              // Voltage monitoring out of range flag
            volatile U32 OCCE :1;              // End of conversion flag
            volatile U32 PCCE :1;              // Preempted channel end of conversion flag
            volatile U32 PCCS :1;              // Preempted channel conversion start flag
            volatile U32 OCCS :1;              // Ordinary channel conversion start flag
            volatile U32 OCCO :1;              // Ordinary channel conversion overflow flag
            volatile U32 RDY  :1;              // ADC conversion ready flag
            volatile U32      :25;
        } B;
    } STS; // ADC status register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 VMCSEL   :5;          // Voltage monitoring channel select
            volatile U32 CCEIEN   :1;          // Channel conversion end interrupt enable
            volatile U32 VMORIEN  :1;          // Voltage monitoring out of range interrupt enable
            volatile U32 PCCEIEN  :1;          // Conversion end interrupt enable on Preempted channels
            volatile U32 SQEN     :1;          // Sequence mode enable
            volatile U32 VMSGEN   :1;          // Voltage monitoring enable on a single channel
            volatile U32 PCAUTOEN :1;          // Preempted group automatic conversion enable after ordinary group
            volatile U32 OCPEN    :1;          // Partitioned mode enable on ordinary channels
            volatile U32 PCPEN    :1;          // Partitioned mode enable on preempted channels
            volatile U32 OCPCNT   :3;          // Partitioned mode conversion count of ordinary channels
            volatile U32          :6;
            volatile U32 PCVMEN   :1;          // Voltage monitoring enable on preempted channels
            volatile U32 OCVMEN   :1;          // Voltage monitoring enable on ordinary channels
            volatile U32 CRSEL    :2;          // Conversion resolution select
            volatile U32 OCCOIE   :1;          // Ordinary channel conversion overflow interrupt enable)
            volatile U32          :5;
        } B;
    } CTRL1; // ADC control register 1 (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ADCEN     :1;         // A/D converter enable
            volatile U32 RPEN      :1;         // Repition mode enable
            volatile U32 ADCAL     :1;         // A/D Calibration
            volatile U32 ADCALINIT :1;         // Initialize A/D calibration
            volatile U32           :4;
            volatile U32 OCDMAEN   :1;         // DMA transfer enable of ordinary channels
            volatile U32 OCDRCEN   :1;         // Ordinary channel DMA request continue enable for independent mode
            volatile U32 EOCSFEN   :1;         // Each ordinary channel conversion OCCE flag enable
            volatile U32 DTALIGN   :1;         // Data alignment
            volatile U32           :4;
            volatile U32 PCTESEL   :4;         // Preempted channel conversion trigger event select
            volatile U32 PCETE     :2;         // Preempted channel external trigger edge select
            volatile U32 PCSWTRG   :1;         // Conversion of preempted channels triggered by software
            volatile U32 PCTESEL5  :1;         // MSB of the PCTESEL
            volatile U32 OCTESEL   :4;         // Ordinary channel conversion trigger event select
            volatile U32 OCETE     :2;         // Ordinary channel external trigger edge select
            volatile U32 OCSWTRG   :1;         // Conversion of ordinary channels triggered by software
            volatile U32 OCTESEL5  :1;         // MSB of the OCTESEL
        } B;
    } CTRL2; // ADC control register 2 (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CSPT10 :3;            // Sample time selection of channel ADC_IN10
            volatile U32 CSPT11 :3;            // Sample time selection of channel ADC_IN11
            volatile U32 CSPT12 :3;            // Sample time selection of channel ADC_IN12
            volatile U32 CSPT13 :3;            // Sample time selection of channel ADC_IN13
            volatile U32 CSPT14 :3;            // Sample time selection of channel ADC_IN14
            volatile U32 CSPT15 :3;            // Sample time selection of channel ADC_IN15
            volatile U32 CSPT16 :3;            // Sample time selection of channel ADC_IN16
            volatile U32 CSPT17 :3;            // Sample time selection of channel ADC_IN17
            volatile U32 CSPT18 :3;            // Sample time selection of channel ADC_IN18
            volatile U32        :5;
        } B;
    } SPT1; // ADC sampling time register 1 (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CSPT0 :3;             // Sample time selection of channel ADC_IN0
            volatile U32 CSPT1 :3;             // Sample time selection of channel ADC_IN1
            volatile U32 CSPT2 :3;             // Sample time selection of channel ADC_IN2
            volatile U32 CSPT3 :3;             // Sample time selection of channel ADC_IN3
            volatile U32 CSPT4 :3;             // Sample time selection of channel ADC_IN4
            volatile U32 CSPT5 :3;             // Sample time selection of channel ADC_IN5
            volatile U32 CSPT6 :3;             // Sample time selection of channel ADC_IN6
            volatile U32 CSPT7 :3;             // Sample time selection of channel ADC_IN7
            volatile U32 CSPT8 :3;             // Sample time selection of channel ADC_IN8
            volatile U32 CSPT9 :3;             // Sample time selection of channel ADC_IN9
            volatile U32       :2;
        } B;
    } SPT2; // ADC sampling time register 2 (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 PCDTO :12;            // Data offset for Preempted channel x
            volatile U32       :20;
        } B;
    } PCDTO[4]; // ADC preempted channel data offset registers (Offset: 0x14-0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 VMHB :16;             // Voltage monitoring high boundary
            volatile U32      :16;
        } B;
    } VMHB; // ADC voltage monitor high threshold register (Offset: 0x24; Reset: 0x0000.FFFF)

    union {
        volatile U32 R;
        struct {
            volatile U32 VMLB :16;             // Voltage monitoring low boundary
            volatile U32      :16;
        } B;
    } VMLB; // ADC voltage monitor low threshold register (Offset: 0x28; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 OSN13 :5;             // Number of 13th conversion in ordinary sequence
            volatile U32 OSN14 :5;             // Number of 14th conversion in ordinary sequence
            volatile U32 OSN15 :5;             // Number of 15th conversion in ordinary sequence
            volatile U32 OSN16 :5;             // Number of 16th conversion in ordinary sequence
            volatile U32 OCLEN :4;             // Ordinary conversion sequence length
            volatile U32       :8;
        } B;
    } OSQ1; // ADC ordinary sequence register 1(Offset: 0x2C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 OSN7  :5;             // Number of 7th conversion in ordinary sequence
            volatile U32 OSN8  :5;             // Number of 8th conversion in ordinary sequence
            volatile U32 OSN9  :5;             // Number of 9th conversion in ordinary sequence
            volatile U32 OSN10 :5;             // Number of 10th conversion in ordinary sequence
            volatile U32 OSN11 :5;             // Number of 11th conversion in ordinary sequence
            volatile U32 OSN12 :5;             // Number of 12th conversion in ordinary sequence
            volatile U32       :2;
        } B;
    } OSQ2; // ADC ordinary sequence register 2(Offset: 0x30; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 OSN1 :5;              // Number of 1st conversion in ordinary sequence
            volatile U32 OSN2 :5;              // Number of 2nd conversion in ordinary sequence
            volatile U32 OSN3 :5;              // Number of 3rd conversion in ordinary sequence
            volatile U32 OSN4 :5;              // Number of 4th conversion in ordinary sequence
            volatile U32 OSN5 :5;              // Number of 5th conversion in ordinary sequence
            volatile U32 OSN6 :5;              // Number of 6th conversion in ordinary sequence
            volatile U32      :2;
        } B;
    } OSQ3; // ADC ordinary sequence register 3(Offset: 0x34; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 PSN1  :5;             // Number of 1st conversion in preempted sequence
            volatile U32 PSN2  :5;             // Number of 2nd conversion in preempted sequence
            volatile U32 PSN3  :5;             // Number of 3rd conversion in preempted sequence
            volatile U32 PSN4  :5;             // Number of 4th conversion in preempted sequence
            volatile U32 PCLEN :2;             // Preempted conversion sequence length
            volatile U32       :10;
        } B;
    } PSQ; // ADC preempted sequence register (Offset: 0x38; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 PDT :16;              // Conversion data from preempted channel
            volatile U32     :16;
        } B;
    } PDT[4]; // ADC preempted data registers (Offset: 0x3C-0x48; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ODT     :16;          // Conversion data of ordinary channel
            volatile U32 ADC2ODT :16;          // ADC2 conversion data of ordinary channel
        } B;
    } ODT; // ADC ordinary data register (Offset: 0x4C; Reset: 0x0000.0000)

    U32 ADC_Reserved0[12U];                    // Reserved: 0x0050-0x007F

    union {
        volatile U32 R;
        struct {
            volatile U32 OOSEN   :1;           // Ordinary oversampling enable
            volatile U32 POSEN   :1;           // Preempted oversampling enable
            volatile U32 OSRSEL  :3;           // Oversampling ratio select
            volatile U32 OSSSEL  :4;           // Oversampling shift select
            volatile U32 OOSTREN :1;           // Ordinary oversampling trigger mode enable
            volatile U32 OOSRSEL :1;           // Ordinary oversampling restart mode select
            volatile U32         :21;
        } B;
    } OVSP; // ADC oversampling register (Offset: 0x80; Reset: 0x0000.0000)

    U32 ADC_Reserved1[12U];                    // Reserved: 0x0084-0x00B3

    union {
        volatile U32 R;
        struct {
            volatile U32 CALVAL :7;            // A/D Calibration
            volatile U32        :25;
        } B;
    } CALVAL; // ADC calibration value register (Offset: 0xB4; Reset: 0x0000.0000)

}; // end of ADC_tag



/******************************************************************************/
/*      Analog-to-Digital converter common registers memory map (ADC_COM)     */
/******************************************************************************/
struct ADC_COM_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 VMOR1 :1;             // ADC1 voltage monitoring out of range flag
            volatile U32 OCCE1 :1;             // ADC1 ordinary channels conversion end flag
            volatile U32 PCCE1 :1;             // ADC1 preempted channels conversion end flag
            volatile U32 PCCS1 :1;             // ADC1 Preempted channel conversion start flag
            volatile U32 OCCS1 :1;             // ADC1 ordinary channel conversion start flag
            volatile U32 OCCO1 :1;             // ADC1 ordinary channel conversion overflow flag
            volatile U32 RDY1  :1;             // ADC1 conversion ready flag
            volatile U32       :1;
            volatile U32 VMOR2 :1;             // ADC2 voltage monitoring out of range flag
            volatile U32 OCCE2 :1;             // ADC2 ordinary channels conversion end flag
            volatile U32 PCCE2 :1;             // ADC2 preempted channels conversion end flag
            volatile U32 PCCS2 :1;             // ADC2 Preempted channel conversion start flag
            volatile U32 OCCS2 :1;             // ADC2 ordinary channel conversion start flag
            volatile U32 OCCO2 :1;             // ADC2 ordinary channel conversion overflow flag
            volatile U32 RDY2  :1;             // ADC2 conversion ready flag
            volatile U32       :1;
            volatile U32 VMOR3 :1;             // ADC3 voltage monitoring out of range flag
            volatile U32 OCCE3 :1;             // ADC3 ordinary channels conversion end flag
            volatile U32 PCCE3 :1;             // ADC3 preempted channels conversion end flag
            volatile U32 PCCS3 :1;             // ADC3 Preempted channel conversion start flag
            volatile U32 OCCS3 :1;             // ADC3 ordinary channel conversion start flag
            volatile U32 OCCO3 :1;             // ADC3 ordinary channel conversion overflow flag
            volatile U32 RDY3  :1;             // ADC3 conversion ready flag
            volatile U32       :9;
        } B;
    } CSTS; // ADC common status register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 MSSEL     :5;          // Combined master/slave mode select
            volatile U32           :3;
            volatile U32 ASISEL    :4;          // Adjacent ADC sampling interval select in ordinary shift mode
            volatile U32           :1;
            volatile U32 MSDRCEN   :1;          // Ordinary channel DMA request continuation enable in master/slave mode
            volatile U32 MSDMASEL  :2;          // Ordinary channel DMA transfer mode select in master/slave mode
            volatile U32 ADCDIV    :4;          // ADC division
            volatile U32           :2;
            volatile U32 VBATEN    :1;          // Vbat enable
            volatile U32 ITSRVEN   :1;          // Internal temperature sensor and Vintrv enable
            volatile U32           :4;
            volatile U32 MSDMASEL2 :1;          // MSDMASEL MSB bit
            volatile U32           :3;
        } B;
    } CCTRL; // ADC common control register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CODTL :16;            // Ordinary conversion low halfword data in master slave mode
            volatile U32 CODTH :16;            // Ordinary conversion high halfword data in master slave mode
        } B;
    } CODT; // ADC common data register (Offset: 0x08; Reset: 0x0000.0000)

}; // end of ADC_COM_tag



/******************************************************************************/
/*                  Controller Area Network (CAN) memory map                  */
/******************************************************************************/
struct CAN_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 FZEN   :1;            // Freeze mode enable
            volatile U32 DZEN   :1;            // Doze mode enable
            volatile U32 MMSSR  :1;            // Multiple message transmit sequence rule
            volatile U32 MDRSEL :1;            // Message discard rule select when overflow
            volatile U32 PRSFEN :1;            // Prohibit retransmission enable when sending fails enable
            volatile U32 AEDEN  :1;            // Automatic exit doze mode enable
            volatile U32 AEBOEN :1;            // Automatic exit bus-off enable
            volatile U32 TTCEN  :1;            // Time triggered communication mode enable
            volatile U32        :7;
            volatile U32 SPRST  :1;            // Software partial reset
            volatile U32 PTD    :1;            // Prohibit trans when debug
            volatile U32        :15;
        } B;
    } MCTRL; // CAN master control register (Offset: 0x000; Reset: 0x0001.0002)

    union {
        volatile U32 R;
        struct {
            volatile U32 FZC     :1;           // Freeze mode confirm
            volatile U32 DZC     :1;           // Doze mode acknowledge
            volatile U32 EOIF    :1;           // Error occur interrupt flag
            volatile U32 QDZIF   :1;           // Exit doze mode interrupt flag
            volatile U32 EDZIF   :1;           // Enter doze mode interrupt flag
            volatile U32         :3;
            volatile U32 CUSS    :1;           // Current transmit status
            volatile U32 CURS    :1;           // Current receive status
            volatile U32 LSAMPRX :1;           // Last sample level on RX pin
            volatile U32 REALRX  :1;           // Real time level on RX pin
            volatile U32         :20;
        } B;
    } MSTS; // CAN master status register (Offset: 0x004; Reset: 0x0000.0C02)

    union {
        volatile U32 R;
        struct {
            volatile U32 TM0TCF :1;            // Transmit mailbox 0 transmission completed flag
            volatile U32 TM0TSF :1;            // Transmit mailbox 0 transmission success flag
            volatile U32 TM0ALF :1;            // Transmit mailbox 0 arbitration lost flag
            volatile U32 TM0TEF :1;            // Transmit mailbox 0 transmission error flag
            volatile U32        :3;
            volatile U32 TM0CT  :1;            // Transmit mailbox 0 cancel transmit
            volatile U32 TM1TCF :1;            // Transmit mailbox 1 transmission completed flag
            volatile U32 TM1TSF :1;            // Transmit mailbox 1 transmission success flag
            volatile U32 TM1ALF :1;            // Transmit mailbox 1 arbitration lost flag
            volatile U32 TM1TEF :1;            // Transmit mailbox 1 transmission error flag
            volatile U32        :3;
            volatile U32 TM1CT  :1;            // Transmit mailbox 1 cancel transmit
            volatile U32 TM2TCF :1;            // Transmit mailbox 2 transmission completed flag
            volatile U32 TM2TSF :1;            // Transmit mailbox 2 transmission success flag
            volatile U32 TM2ALF :1;            // Transmit mailbox 2 arbitration lost flag
            volatile U32 TM2TEF :1;            // Transmit mailbox 2 transmission error flag
            volatile U32        :3;
            volatile U32 TM2CT  :1;            // Transmit mailbox 2 cancel transmit
            volatile U32 TMNR   :2;            // Transmit Mailbox number record
            volatile U32 TM0EF  :1;            // Transmit mailbox 0 empty flag
            volatile U32 TM1EF  :1;            // Transmit mailbox 1 empty flag
            volatile U32 TM2EF  :1;            // Transmit mailbox 2 empty flag
            volatile U32 TM0LPF :1;            // Transmit mailbox 0 lowest priority flag
            volatile U32 TM1LPF :1;            // Transmit mailbox 1 lowest priority flag
            volatile U32 TM2LPF :1;            // Transmit mailbox 2 lowest priority flag
        } B;
    } TSTS; // CAN transmit status register (Offset: 0x008; Reset: 0x1C00.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RF0MN :2;             // Receive FIFO 0 message num
            volatile U32       :1;
            volatile U32 RF0FF :1;             // Receive FIFO 0 full flag
            volatile U32 RF0OF :1;             // Receive FIFO 0 overflow flag
            volatile U32 RF0R  :1;             // Receive FIFO 0 release
            volatile U32       :26;
        } B;
    } RF0; // CAN receive FIFO 0 register (Offset: 0x00C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RF1MN :2;             // Receive FIFO 1 message num
            volatile U32       :1;
            volatile U32 RF1FF :1;             // Receive FIFO 1 full flag
            volatile U32 RF1OF :1;             // Receive FIFO 1 overflow flag
            volatile U32 RF1R  :1;             // Receive FIFO 1 release
            volatile U32       :26;
        } B;
    } RF1; // CAN receive FIFO 1 register (Offset: 0x010; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TCIEN   :1;           // Transmit mailbox empty interrupt enable
            volatile U32 RF0MIEN :1;           // FIFO 0 receive message interrupt enable
            volatile U32 RF0FIEN :1;           // Receive FIFO 0 full interrupt enable
            volatile U32 RF0OIEN :1;           // Receive FIFO 0 overflow interrupt enable
            volatile U32 RF1MIEN :1;           // FIFO 1 receive message interrupt enable
            volatile U32 RF1FIEN :1;           // Receive FIFO 1 full interrupt enable
            volatile U32 RF1OIEN :1;           // Receive FIFO 1 overflow interrupt enable
            volatile U32         :1;
            volatile U32 EAIEN   :1;           //  Error active interrupt enable
            volatile U32 EPIEN   :1;           // Error passive interrupt enable
            volatile U32 BOIEN   :1;           // Bus-off interrupt enable
            volatile U32 ETRIEN  :1;           // Error type record interrupt enable
            volatile U32         :3;
            volatile U32 EOIEN   :1;           // Error occur interrupt enable
            volatile U32 QDZIEN  :1;           // Quit doze mode interrupt enable
            volatile U32 EDZIEN  :1;           // Enter doze mode interrupt enable
            volatile U32         :14;
        } B;
    } INTEN; // CAN interrupt enable register (Offset: 0x014; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 EAF :1;               // Error active flag
            volatile U32 EPF :1;               // Error passive flag
            volatile U32 BOF :1;               // Bus-off flag
            volatile U32     :1;
            volatile U32 ETR :3;               // Error type record
            volatile U32     :9;
            volatile U32 TEC :8;               // Transmit error counter
            volatile U32 REC :8;               // Receive error counter
        } B;
    } ESTS; // CAN error status register (Offset: 0x018; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 BRDIV :12;            // Baud rate division
            volatile U32       :4;
            volatile U32 BTS1  :4;             // Bit time segment 1
            volatile U32 BTS2  :3;             // Bit time segment 2
            volatile U32       :1;
            volatile U32 RSAW  :2;             // Resynchronization width
            volatile U32       :4;
            volatile U32 LBEN  :1;             // Loop back mode
            volatile U32 LOEN  :1;             // Listen-Only mode
        } B;
    } BTMG; // CAN bit timing register (Offset: 0x01C; Reset: 0x0123.0000)

    U32 CAN_Reserved0[88U];                    // Reserved: 0x0020-0x017F

    struct {
        union {
            volatile U32 R;
            struct {
                volatile U32 TMSR    :1;       // Transmit mailbox send request
                volatile U32 TMFRSEL :1;       // Transmit mailbox frame type select
                volatile U32 TMIDSEL :1;       // Transmit mailbox identifier type select
                volatile U32 TMEID   :18;      // Transmit mailbox extended identifier
                volatile U32 TMSID   :11;      // Transmit mailbox standard identifier or extended identifier high bytes
            } B;
        } TMI; // CAN TX mailbox identifier register (Offset: 0x180, 0x190, 0x1A0; Reset: 0xXXXX.XXXX, except TXRQ = 0)

        union {
            volatile U32 R;
            struct {
                volatile U32 TMDTBL  :4;       // Transmit mailbox data byte length
                volatile U32         :4;
                volatile U32 TMTSTEN :1;       // Transmit mailbox time stamp transmit enable
                volatile U32         :7;
                volatile U32 TMTS    :16;      // Transmit mailbox time stamp
            } B;
        } TMC; // Transmit mailbox data length and time stamp register (Offset: 0x184, 0x194, 0x1A4; Reset: 0xXXXX.XXXX)

        union {
            volatile U32 R;
            struct {
                volatile U32 TMDT0 :8;         // Transmit mailbox data byte 0
                volatile U32 TMDT1 :8;         // Transmit mailbox data byte 1
                volatile U32 TMDT2 :8;         // Transmit mailbox data byte 2
                volatile U32 TMDT3 :8;         // Transmit mailbox data byte 3
            } B;
        } TMDTL; // Transmit mailbox data low register (Offset: 0x188, 0x198, 0x1A8; Reset: 0xXXXX.XXXX)

        union {
            volatile U32 R;
            struct {
                volatile U32 TMDT4 :8;         // Transmit mailbox data byte 4
                volatile U32 TMDT5 :8;         // Transmit mailbox data byte 5
                volatile U32 TMDT6 :8;         // Transmit mailbox data byte 6
                volatile U32 TMDT7 :8;         // Transmit mailbox data byte 7
            } B;
        } TMDTH; // Transmit mailbox data high register (Offset: 0x18C, 0x19C, 0x1AC; Reset: 0xXXXX.XXXX)
    } TX_mailbox[3U];

    struct {
        union {
            volatile U32 R;
            struct {
                volatile U32       :1;
                volatile U32 RFFRI :1;         // Receive FIFO frame type indication
                volatile U32 RFIDI :1;         // Receive FIFO identifier type indication
                volatile U32 RFEID :18;        // Receive FIFO extended identifier
                volatile U32 RFSID :11;        // Receive FIFO standard identifier or receive FIFO extended identifier
            } B;
        } RFI; // Receive FIFO mailbox identifier register (Offset: 0x1B0, 0x1C0; Reset: 0xXXXX.XXXX)

        union {
            volatile U32 R;
            struct {
                volatile U32 RFDTL :4;         // Receive FIFO data length
                volatile U32       :4;
                volatile U32 RFFMN :8;         // Receive FIFO filter match number
                volatile U32 RFTS  :16;        // Receive FIFO time stamp
            } B;
        } RFC; // Receive FIFO mailbox data length and time stamp register (Offset: 0x1B4, 0x1C4; Reset: 0xXXXX.XXXX)

        union {
            volatile U32 R;
            struct {
                volatile U32 RFDT0 :8;         // Receive FIFO data byte 0
                volatile U32 RFDT1 :8;         // Receive FIFO data byte 1
                volatile U32 RFDT2 :8;         // Receive FIFO data byte 2
                volatile U32 RFDT3 :8;         // Receive FIFO data byte 3
            } B;
        } RFDTL; // Receive FIFO mailbox data low register (Offset: 0x1B8, 0x1C8; Reset: 0xXXXX.XXXX)

        union {
            volatile U32 R;
            struct {
                volatile U32 RFDT4 :8;         // Receive FIFO data byte 4
                volatile U32 RFDT5 :8;         // Receive FIFO data byte 5
                volatile U32 RFDT6 :8;         // Receive FIFO data byte 6
                volatile U32 RFDT7 :8;         // Receive FIFO data byte 7
            } B;
        } RFDTH; // Receive FIFO mailbox data high register (Offset: 0x1BC, 0x1CC; Reset: 0xXXXX.XXXX)
    } RX_FIFO[2U];

    U32 CAN_Reserved1[12U];                    // Reserved: 0x01D0-0x01FF

    union {
        volatile U32 R;
        struct {
            volatile U32 FCS  :1;              // Filter configuration switch
            volatile U32      :31;
        } B;
    } FCTRL; // CAN filter control register (Offset: 0x200; Reset: 0x2A1C.0E01)

    union {
        volatile U32 R;
        struct {
            volatile U32 FMSEL :28;            // Filter mode select
            volatile U32       :4;
        } B;
    } FMCFG; // CAN filter mode configuration register (Offset: 0x204; Reset: 0x0000.0000)

    U32 CAN_Reserved2[1U];                     // Reserved: 0x0208-0x020B

    union {
        volatile U32 R;
        struct {
            volatile U32 FBWSEL :28;           // Filter bit width select
            volatile U32        :4;
        } B;
    } FBWCFG; // CAN filter bit width configuration register (Offset: 0x20C; Reset: 0x0000.0000)

    U32 CAN_Reserved3[1U];                     // Reserved: 0x0210-0x0213

    union {
        volatile U32 R;
        struct {
            volatile U32 FRFSEL :28;           // Filter relation FIFO select
            volatile U32        :4;
        } B;
    } FRF; // CAN filter FIFO association register (Offset: 0x214; Reset: 0x0000.0000)

    U32 CAN_Reserved4[1U];                     // Reserved: 0x0218-0x021B

    union {
        volatile U32 R;
        struct {
            volatile U32 FAEN :28;             // Filter active enable
            volatile U32      :4;
        } B;
    } FACFG; // CAN filter activation control register (Offset: 0x21C; Reset: 0x0000.0000)

    U32 CAN_Reserved5[8U];                     // Reserved: 0x0220-0x023F

    union {
        volatile U32 R;
        struct {
            volatile U32 FFDB :32;             // Filters filter data bit
        } B;
    } FFB[14U][2U]; // CAN filter bank i filter bit register X (Offset: 0x240; Reset: 0xXXXX.XXXX)

}; // end of CAN_tag



/******************************************************************************/
/*          Cyclic redundancy check calculation unit (CRC) memory map         */
/******************************************************************************/
struct CRC_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 DT :32;               // Data value
        } B;
    } DT; // Data register ( Offset: 0x00; Reset: 0xFFFF.FFFF)

    union {
        volatile U32 R;
        struct {
            volatile U32 CDT :8;               // Common 8-bit data value
            volatile U32     :24;
        } B;
    } CDT; // Common data register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RST   :1;             // Reset CRC calculation unit
            volatile U32       :4;
            volatile U32 REVID :2;             // Reverse input data
            volatile U32 REVOD :1;             // Reverse output data
            volatile U32       :24;
        } B;
    } CTRL; // Control register (Offset: 0x08; Reset: 0x0000.0000)

    U32 CRC_Reserved0[1U];                     // Reserved: 0x000C - 0x000F

    union {
        volatile U32 R;
        struct {
            volatile U32 IDT :32;              // Initialization data register
        } B;
    } IDT; // Initialization register (Offset: 0x10; Reset: 0xFFFF.FFFF)

}; // end of CRC_tag



/******************************************************************************/
/*                  Clock and reset manage (CRM) memory map                   */
/******************************************************************************/
struct CRM_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 HICKEN   :1;          // High speed internal clock enable
            volatile U32 HICKSTBL :1;          // High speed internal clock stable
            volatile U32 HICKTRIM :6;          // High speed internal clock trimming
            volatile U32 HICKCAL  :8;          // High speed internal clock calibration
            volatile U32 HEXTEN   :1;          // High speed external crystal enable
            volatile U32 HEXTSTBL :1;          // High speed external crystal stable
            volatile U32 HEXTBYPS :1;          // High speed external crystal bypass
            volatile U32 CFDEN    :1;          // Clock failure detector enable
            volatile U32          :4;
            volatile U32 PLLEN    :1;          // PLL enable
            volatile U32 PLLSTBL  :1;          // PLL clock stable
            volatile U32          :6;
        } B;
    } CTRL; // Clock control register (Offset: 0x00; Reset: 0x0000.xx83)

    union {
        volatile U32 R;
        struct {
            volatile U32 PLL_MS :4;            // PLL pre-division
            volatile U32        :2;
            volatile U32 PLL_NS :9;            // PLL multiplication factor
            volatile U32        :1;
            volatile U32 PLL_FR :3;            // PLL post-division
            volatile U32        :3;
            volatile U32 PLLRCS :1;            // PLL reference clock select
            volatile U32        :9;
        } B;
    } PLLCFG; // PLL clock configuration register (Offset: 0x04; Reset: 0x0003.3002)

    union {
        volatile U32 R;
        struct {
            volatile U32 SCLKSEL      :2;      // System clock select
            volatile U32 SCLKSTS      :2;      // System clock select status
            volatile U32 AHBDIV       :4;      // AHB division
            volatile U32              :2;
            volatile U32 APB1DIV      :3;      // APB1 division
            volatile U32 APB2DIV      :3;      // APB2 division
            volatile U32 ERTCDIV      :5;      // HEXT division for ERTC clock
            volatile U32 CLKOUT1_SEL  :2;      // Clock output 1 selection
            volatile U32              :1;
            volatile U32 CLKOUT1DIV1  :3;      // Clock output 1 division 1
            volatile U32 CLKOUT2DIV1  :3;      // Clock output 2 division 1
            volatile U32 CLKOUT2_SEL1 :2;      // Clock output 2 selection 1
        } B;
    } CFG; // Clock configuration register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 LICKSTBLF   :1;       // LICK stable interrupt flag
            volatile U32 LEXTSTBLF   :1;       // LEXT stable flag
            volatile U32 HICKSTBLF   :1;       // HICK stable flag
            volatile U32 HEXTSTBLF   :1;       // HEXT stable flag
            volatile U32 PLLSTBLF    :1;       // PLL stable flag
            volatile U32             :2;
            volatile U32 CFDF        :1;       // Clock Failure Detection flag
            volatile U32 LICKSTBLIEN :1;       // LICK stable interrupt enable
            volatile U32 LEXTSTBLIEN :1;       // LEXT stable interrupt enable
            volatile U32 HICKSTBLIEN :1;       // HICK stable interrupt enable
            volatile U32 HEXTSTBLIEN :1;       // HEXT stable interrupt enable
            volatile U32 PLLSTBLIEN  :1;       // PLL stable interrupt enable
            volatile U32             :3;
            volatile U32 LICKSTBLFC  :1;       // LICK stable flag clear
            volatile U32 LEXTSTBLFC  :1;       // LEXT stable flag clear
            volatile U32 HICKSTBLFC  :1;       // HICK stable flag clear
            volatile U32 HEXTSTBLFC  :1;       // HEXT stable flag clear
            volatile U32 PLLSTBLFC   :1;       // PLL stable flag clear
            volatile U32             :2;
            volatile U32 CFDFC       :1;       // Clock failure detection flag clear
            volatile U32             :8;
        } B;
    } CLKINT; // Clock interrupt register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 GPIOARST  :1;         // IO port A reset
            volatile U32 GPIOBRST  :1;         // IO port B reset
            volatile U32 GPIOCRST  :1;         // IO port C reset
            volatile U32 GPIODRST  :1;         // IO port D reset
            volatile U32 GPIOERST  :1;         // IO port E reset
            volatile U32 GPIOFRST  :1;         // IO port F reset
            volatile U32 GPIOGRST  :1;         // IO port G reset
            volatile U32 GPIOHRST  :1;         // IO port H reset
            volatile U32           :4;
            volatile U32 CRCRST    :1;         // CRC reset
            volatile U32           :8;
            volatile U32 EDMARST   :1;         // EDMA reset
            volatile U32 DMA1RST   :1;         // DMA1 reset
            volatile U32           :1;
            volatile U32 DMA2RST   :1;         // DMA2 reset
            volatile U32 EMACRST   :1;         // EMAC reset
            volatile U32           :3;
            volatile U32 OTGFS2RST :1;         // OTGFS2 reset
            volatile U32           :2;
        } B;
    } AHBRST1; // AHB peripheral reset register 1 (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DVPRST    :1;         // DVP reset
            volatile U32           :6;
            volatile U32 OTGFS1RST :1;         // OTGFS1 reset
            volatile U32           :7;
            volatile U32 SDIO1RST  :1;         // SDIO1 reset
            volatile U32           :16;
        } B;
    } AHBRST2; // AHB peripheral reset register 2 (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 XMCRST   :1;          // XMC reset
            volatile U32 QSPI1RST :1;          // QSPI1 reset
            volatile U32          :12;
            volatile U32 QSPI2RST :1;          // QSPI2 reset
            volatile U32 SDIO2RST :1;          // SDIO2 reset
            volatile U32          :16;
        } B;
    } AHBRST3; // AHB peripheral reset register 3 (Offset: 0x18; Reset: 0x0000.0000)

    U32 CRM_Reserved0[1U];                     // Reserved :0x001C-0x001F

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR2RST   :1;         // Timer2 reset
            volatile U32 TMR3RST   :1;         // Timer3 reset
            volatile U32 TMR4RST   :1;         // Timer4 reset
            volatile U32 TMR5RST   :1;         // Timer5 reset
            volatile U32 TMR6RST   :1;         // Timer6 reset
            volatile U32 TMR7RST   :1;         // Timer7 reset
            volatile U32 TMR12RST  :1;         // Timer12 reset
            volatile U32 TMR13RST  :1;         // Timer13 reset
            volatile U32 TMR14RST  :1;         // Timer14 reset
            volatile U32           :2;
            volatile U32 WWDTRST   :1;         // Window watchdog reset
            volatile U32           :2;
            volatile U32 SPI2RST   :1;         // SPI3 reset
            volatile U32 SPI3RST   :1;         // SPI3 reset
            volatile U32           :1;
            volatile U32 USART2RST :1;         // USART2 reset
            volatile U32 USART3RST :1;         // USART3 reset
            volatile U32 UART4RST  :1;         // UART4 reset
            volatile U32 UART5RST  :1;         // UART5 reset
            volatile U32 I2C1RST   :1;         // I2C1 reset
            volatile U32 I2C2RST   :1;         // I2C2 reset
            volatile U32 I2C3RST   :1;         // I2C3 reset
            volatile U32           :1;
            volatile U32 CAN1RST   :1;         // CAN1 reset
            volatile U32 CAN2RST   :1;         // CAN2 reset
            volatile U32           :1;
            volatile U32 PWCRST    :1;         // Power interface reset
            volatile U32 DACRST    :1;         // DAC interface reset
            volatile U32 UART7RST  :1;         // UART7 reset
            volatile U32 UART8RST  :1;         // UART8 reset
        } B;
    } APB1RST; // APB1 peripheral reset register (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR1RST   :1;         // TMR1 timer reset
            volatile U32 TMR8RST   :1;         // TMR8 timer reset
            volatile U32           :2;
            volatile U32 USART1RST :1;         // USART1 reset
            volatile U32 USART6RST :1;         // USART6 reset
            volatile U32           :2;
            volatile U32 ADCRST    :1;         // ADC1 interface reset
            volatile U32           :3;
            volatile U32 SPI1RST   :1;         // SPI1 reset
            volatile U32 SPI4RST   :1;         // SPI4 reset
            volatile U32 SCFGRST   :1;         // SCFG reset
            volatile U32           :1;
            volatile U32 TMR9RST   :1;         // Timer9 reset
            volatile U32 TMR10RST  :1;         // Timer10 reset
            volatile U32 TMR11RST  :1;         // Timer11 reset
            volatile U32           :1;
            volatile U32 TMR20RST  :1;         // Timer20 reset
            volatile U32           :8;
            volatile U32 ACCRST    :1;         // ACC reset
            volatile U32           :2;
        } B;
    } APB2RST; // APB2 peripheral reset register (Offset: 0x24; Reset: 0x0000.0000)

    U32 CRM_Reserved1[2U];                     // Reserved :0x0028-0x002F

    union {
        volatile U32 R;
        struct {
            volatile U32 GPIOAEN   :1;         // IO port A clock enable
            volatile U32 GPIOBEN   :1;         // IO port B clock enable
            volatile U32 GPIOCEN   :1;         // IO port C clock enable
            volatile U32 GPIODEN   :1;         // IO port D clock enable
            volatile U32 GPIOEEN   :1;         // IO port E clock enable
            volatile U32 GPIOFEN   :1;         // IO port F clock enable
            volatile U32 GPIOGEN   :1;         // IO port G clock enable
            volatile U32 GPIOHEN   :1;         // IO port H clock enable
            volatile U32           :4;
            volatile U32 CRCEN     :1;         // CRC clock enable
            volatile U32           :8;
            volatile U32 EDMAEN    :1;         // EDMA clock enable
            volatile U32 DMA1EN    :1;         // DMA1 clock enable
            volatile U32           :1;
            volatile U32 DMA2EN    :1;         // DMA2 clock enable
            volatile U32 EMACEN    :1;         // EMAC clock enable
            volatile U32 EMACTXEN  :1;         // EMAC TX clock enable
            volatile U32 EMACRXEN  :1;         // EMAC RX clock enable
            volatile U32 EMACPTPEN :1;         // EMAC PTP clock enable
            volatile U32 OTGFS2EN  :1;         // OTGFS2 clock enable
            volatile U32           :2;
        } B;
    } AHBEN1; // AHB peripheral clock enable register 1 (Offset: 0x30; Reset: 0x0010.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DVPEN    :1;          // DVP clock enable
            volatile U32          :6;
            volatile U32 OTGFS1EN :1;          // OTGFS1 clock enable
            volatile U32          :7;
            volatile U32 SDIO1EN  :1;          // SDIO1 clock enable
            volatile U32          :16;
        } B;
    } AHBEN2; // AHB peripheral clock enable register 2 (Offset: 0x34; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 XMCEN   :1;           // XMC clock enable
            volatile U32 QSPI1EN :1;           // QSPI1 clock enable
            volatile U32         :12;
            volatile U32 QSPI2EN :1;           // QSPI2 clock enable
            volatile U32 SDIO2EN :1;           // SDIO2 clock enable
            volatile U32         :16;
        } B;
    } AHBEN3; // AHB peripheral clock enable register 3 (Offset: 0x38; Reset: 0x0000.0000)

    U32 CRM_Reserved2[1U];                     // Reserved :0x003C-0x003F

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR2EN   :1;          // Timer2 clock enable
            volatile U32 TMR3EN   :1;          // Timer3 clock enable
            volatile U32 TMR4EN   :1;          // Timer4 clock enable
            volatile U32 TMR5EN   :1;          // Timer5 clock enable
            volatile U32 TMR6EN   :1;          // Timer6 clock enable
            volatile U32 TMR7EN   :1;          // Timer7 clock enable
            volatile U32 TMR12EN  :1;          // Timer12 clock enable
            volatile U32 TMR13EN  :1;          // Timer13 clock enable
            volatile U32 TMR14EN  :1;          // Timer14 clock enable
            volatile U32          :2;
            volatile U32 WWDTEN   :1;          // Window watchdog clock enable
            volatile U32          :2;
            volatile U32 SPI2EN   :1;          // SPI2 clock enable
            volatile U32 SPI3EN   :1;          // SPI3 clock enable
            volatile U32          :1;
            volatile U32 USART2EN :1;          // USART2 clock enable
            volatile U32 USART3EN :1;          // USART3 clock enable
            volatile U32 UART4EN  :1;          // UART4 clock enable
            volatile U32 UART5EN  :1;          // UART5 clock enable
            volatile U32 I2C1EN   :1;          // I2C1 clock enable
            volatile U32 I2C2EN   :1;          // I2C2 clock enable
            volatile U32 I2C3EN   :1;          // I2C3 clock enable
            volatile U32          :1;
            volatile U32 CAC1EN   :1;          // CAN1 clock enable
            volatile U32 CAC2EN   :1;          // CAN2 clock enable
            volatile U32          :1;
            volatile U32 PWCEN    :1;          // Power interface clock enable
            volatile U32 DACEN    :1;          // DAC interface clock enable
            volatile U32 UART7EN  :1;          // UART7 clock enable
            volatile U32 UART8EN  :1;          // UART8 clock enable
        } B;
    } APB1EN; // APB1 peripheral clock enable register (Offset: 0x40; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR1EN   :1;          // Timer1 clock enable
            volatile U32 TMR8EN   :1;          // Timer8 clock enable
            volatile U32          :2;
            volatile U32 USART1EN :1;          // USART1 clock enable
            volatile U32 USART6EN :1;          // USART6 clock enable
            volatile U32          :2;
            volatile U32 ADC1EN   :1;          // ADC1 interface clock enable
            volatile U32 ADC2EN   :1;          // ADC2 interface clock enable
            volatile U32 ADC3EN   :1;          // ADC3 interface clock enable
            volatile U32          :1;
            volatile U32 SPI1EN   :1;          // SPI1 clock enable
            volatile U32 SPI4EN   :1;          // SPI4 clock enable
            volatile U32 SCFGEN   :1;          // SCFG clock enable
            volatile U32          :1;
            volatile U32 TMR9EN   :1;          // Timer9 clock enable
            volatile U32 TMR10EN  :1;          // Timer10 clock enable
            volatile U32 TMR11EN  :1;          // Timer11 clock enable
            volatile U32          :1;
            volatile U32 TMR20EN  :1;          // Timer20 clock enable
            volatile U32          :8;
            volatile U32 ACCEN    :1;          // ACC clock enable
            volatile U32          :2;
        } B;
    } APB2EN; // APB2 peripheral clock enable register (Offset: 0x44; Reset: 0x0000.0000)

    U32 CRM_Reserved3[2U];                     // Reserved :0x0048-0x004F

    union {
        volatile U32 R;
        struct {
            volatile U32 GPIOALPEN   :1;       // IO port A clock enable in sleep mode
            volatile U32 GPIOBLPEN   :1;       // IO port B clock enable in sleep mode
            volatile U32 GPIOCLPEN   :1;       // IO port C clock enable in sleep mode
            volatile U32 GPIODLPEN   :1;       // IO port D clock enable in sleep mode
            volatile U32 GPIOELPEN   :1;       // IO port E clock enable in sleep mode
            volatile U32 GPIOFLPEN   :1;       // IO port F clock enable in sleep mode
            volatile U32 GPIOGLPEN   :1;       // IO port G clock enable in sleep mode
            volatile U32 GPIOHLPEN   :1;       // O port H clock enable in sleep mode
            volatile U32             :4;
            volatile U32 CRCLPEN     :1;       // CRC clock enable during sleep mode
            volatile U32             :2;
            volatile U32 FLASHLPEN   :1;       // FLASH clock enable during sleep mode
            volatile U32 SRAM1LPEN   :1;       // SRAM1 clock enable in sleep mode
            volatile U32 SRAM2LPEN   :1;       // SRAM2 clock enable in sleep mode
            volatile U32             :3;
            volatile U32 EDMALPEN    :1;       // EDMA clock enable in sleep mode
            volatile U32 DMA1LPEN    :1;       // DMA1 clock enable in sleep mode
            volatile U32             :1;
            volatile U32 DMA2LPEN    :1;       // DMA2 clock enable in sleep mode
            volatile U32 EMACLPEN    :1;       // EMAC clock enable during sleep mode
            volatile U32 EMACTXLPEN  :1;       // EMAC TX clock enable in sleep mode
            volatile U32 EMACRXLPEN  :1;       // EMAC RX clock enable in sleep mode
            volatile U32 EMACPTPLPEN :1;       // EMAC PTP clock enable in sleep mode
            volatile U32 OTGFS2LPEN  :1;       // OTGFS2 clock enable in sleep mode
            volatile U32             :2;
        } B;
    } AHBLPEN1; // AHB peripheral clock enable in low power mode register 1 (Offset: 0x50; Reset: 0x3F63.90FF)

    union {
        volatile U32 R;
        struct {
            volatile U32 DVPLPEN    :1;        // DVP clock enable in sleep mode
            volatile U32            :6;
            volatile U32 OTGFS1LPEN :1;        // OTGFS1 clock enable in sleep mode
            volatile U32            :7;
            volatile U32 SDIO1LPEN  :1;        // SDIO1 clock enable in sleep mode
            volatile U32            :16;
        } B;
    } AHBLPEN2; // AHB peripheral clock enable in low power mode register 2 (Offset: 0x54; Reset: 0x0000.8081)

    union {
        volatile U32 R;
        struct {
            volatile U32 XMCLPEN   :1;         // XMC clock enable in sleep mode
            volatile U32 QSPI1LPEN :1;         // QSPI1 clock enable in sleep mode
            volatile U32           :12;
            volatile U32 QSPI2LPEN :1;         // QSPI2 clock enable in sleep mode
            volatile U32 SDIO2LPEN :1;         // SDIO2 clock enable in sleep mode
            volatile U32           :16;
        } B;
    } AHBLPEN3; // AHB peripheral clock enable in low power mode register 3 (Offset: 0x58; Reset: 0x0000.C003)

    U32 CRM_Reserved4[1U];                     // Reserved :0x005C-0x005F

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR2LPEN   :1;        // Timer 2 clock enable in sleep mode
            volatile U32 TMR3LPEN   :1;        // Timer 3 clock enable in sleep mode
            volatile U32 TMR4LPEN   :1;        // Timer 4 clock enable in sleep mode
            volatile U32 TMR5LPEN   :1;        // Timer 5 clock enable in sleep mode
            volatile U32 TMR6LPEN   :1;        // Timer 6 clock enable in sleep mode
            volatile U32 TMR7LPEN   :1;        // Timer 7 clock enable in sleep mode
            volatile U32 TMR12LPEN  :1;        // Timer12 clock enable in sleep mode
            volatile U32 TMR13LPEN  :1;        // Timer13 clock enable in sleep mode
            volatile U32 TMR14LPEN  :1;        // Timer14 clock enable in sleep mode
            volatile U32            :2;
            volatile U32 WWDTLPEN   :1;        // Window watchdog clock enable in sleep mode
            volatile U32            :2;
            volatile U32 SPI2LPEN   :1;        // SPI 2 clock enable in sleep mode
            volatile U32 SPI3LPEN   :1;        // SPI3 clock enable in sleep mode
            volatile U32            :1;
            volatile U32 USART2LPEN :1;        // USART2 clock enable in sleep mode
            volatile U32 USART3LPEN :1;        // USART3 clock enable in sleep mode
            volatile U32 UART4LPEN  :1;        // UART4 clock enable in sleep mode
            volatile U32 UART5LPEN  :1;        // UART5 clock enable in sleep mode
            volatile U32 I2C1LPEN   :1;        // I2C1 clock enable in sleep mode
            volatile U32 I2C2LPEN   :1;        // I2C2 clock enable in sleep mode
            volatile U32 I2C3LPEN   :1;        // I2C3 clock enable in sleep mode
            volatile U32            :1;
            volatile U32 CAN1LPEN   :1;        // CAN1 clock enable in sleep mode
            volatile U32 CAN2LPEN   :1;        // CAN2 clock enable in sleep mode
            volatile U32            :1;
            volatile U32 PWCLPEN    :1;        // Power interface clock enable in sleep mode
            volatile U32 DACLPEN    :1;        // DAC interface clock enable in sleep mode
            volatile U32 UART7LPEN  :1;        // UART7 clock enable in sleep mode
            volatile U32 UART8LPEN  :1;        // UART8 clock enable in sleep mode
        } B;
    } APB1LPEN; // APB1 peripheral clock enable in low power mode register (Offset: 0x60; Reset: 0xF6FE.E9FF)

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR1LPEN   :1;        // TMR1 timer clock enable in sleep mode
            volatile U32 TMR8LPEN   :1;        // TMR8 timer clock enable in sleep mode
            volatile U32            :2;
            volatile U32 USART1LPEN :1;        // USART1 clock enable in sleep mode
            volatile U32 USART6LPEN :1;        // USART6 clock enable in sleep mode
            volatile U32            :2;
            volatile U32 ADC1LPEN   :1;        // ADC1 interface clock enable in sleep mode
            volatile U32 ADC2LPEN   :1;        // DC2 interface clock enable in sleep mode
            volatile U32 ADC3LPEN   :1;        // ADC3 interface clock enable in sleep mode
            volatile U32            :1;
            volatile U32 SPI1LPEN   :1;        // SPI1 clock enable in sleep mode
            volatile U32 SPI4LPEN   :1;        // SPI4 clock enable in sleep mode)
            volatile U32 SCFGLPEN   :1;        // SCFG clock enable in sleep mode
            volatile U32            :1;
            volatile U32 TMR9LPEN   :1;        // Timer9 clock enable in sleep mode
            volatile U32 TMR10LPEN  :1;        // Timer10 clock enable in sleep mode
            volatile U32 TMR11LPEN  :1;        // Timer11 clock enable during sleep mode
            volatile U32            :1;
            volatile U32 TMR20LPEN  :1;        // Timer20 clock enable in sleep mode
            volatile U32            :8;
            volatile U32 ACCLPEN    :1;        // ACC clock enable in sleep mode
            volatile U32            :2;
        } B;
    } APB2LPEN; // APB2 peripheral clock enable in low power mode register (Offset: 0x64; Reset: 0x2017.7733)

    U32 CRM_Reserved5[2U];                     // Reserved :0x0068-0x006F

    union {
        volatile U32 R;
        struct {
            volatile U32 LEXTEN   :1;          // External low-speed oscillator enable
            volatile U32 LEXTSTBL :1;          // Low speed external oscillator stable
            volatile U32 LEXTBYPS :1;          // Low speed external crystal bypass
            volatile U32          :5;
            volatile U32 eRTCSEL  :2;          // eRTC clock selection
            volatile U32          :5;
            volatile U32 ERTCEN   :1;          // ERTC clock enable
            volatile U32 BPDRST   :1;          // Battery powered domain software reset
            volatile U32          :15;
        } B;
    } BPDC; // Battery powered domain control register (Offset: 0x70; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 LICKEN   :1;          // LICK enable
            volatile U32 LICKSTBL :1;          // LICK stable
            volatile U32          :22;
            volatile U32 RSTFC    :1;          // Reset flag clear
            volatile U32          :1;
            volatile U32 NRSTF    :1;          // NRST pin reset flag
            volatile U32 PORRSTF  :1;          // POR/LVR reset flag
            volatile U32 SWRSTF   :1;          // Software reset flag
            volatile U32 WDTRSTF  :1;          // Watchdog timer reset flag
            volatile U32 WWDTRSTF :1;          // Window watchdogtimer reset flag
            volatile U32 LPRSTF   :1;          // Low-power reset flag
        } B;
    } CTRLSTS; // Control/status register (Offset: 0x74; Reset: 0x0C00.0000)

    U32 CRM_Reserved6[10U];                    // Reserved :0x0078-0x009F

    union {
        volatile U32 R;
        struct {
            volatile U32 HICKCAL_KEY  :8;      // HICK calibration key
            volatile U32              :4;
            volatile U32 HICKDIV      :1;      // HICK 6 divider selection
            volatile U32 HICK_TO_USB  :1;      // USB 48 MHz clock source select
            volatile U32 HICK_TO_SCLK :1;      // HICK as system clock frequency select
            volatile U32              :1;
            volatile U32 CLKOUT2_SEL2 :4;      // Clock output2 sel2
            volatile U32              :4;
            volatile U32 CLKOUT1DIV2  :4;      // Clock output1 division2
            volatile U32 CLKOUT2DIV2  :4;      // Clock output2 division2
        } B;
    } MISC1; // Additional register 1 (Offset: 0xA0; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32              :4;
            volatile U32 AUTO_STEP_EN :2;      // Auto step-by-step system clock switch enable
            volatile U32              :2;
            volatile U32 CLK1_TO_TMR  :1;      // CLKOUT1 internal connected to timer 10 channel 1
            volatile U32 EMAC_PPS_SEL :1;      // Ethernet pulse width select
            volatile U32              :2;
            volatile U32 USBDIV       :4;      // USB division
            volatile U32              :16;
        } B;
    } MISC2; // Additional register 2 (Offset: 0xA4; Reset: 0x0000.000D)

}; // end of CRM_tag



/******************************************************************************/
/*                Digital-to-Analog converter (DAC) memory map                */
/******************************************************************************/
struct DAC_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 D1EN        :1;       // DAC1 enable
            volatile U32 D1OBDIS     :1;       // DAC1 output buffer disable
            volatile U32 D1TRGEN     :1;       // DAC1 trigger enable
            volatile U32 D1TRGSEL    :3;       // DAC1 trigger select
            volatile U32 D1NM        :2;       // DAC1 noise mode
            volatile U32 D1NBSEL     :4;       // DAC1 noise bit select
            volatile U32 D1DMAEN     :1;       // DAC1 DMA transfer enable
            volatile U32 D1DMAUDRIEN :1;       // DAC1 DMA transfer underrun interrupt enable
            volatile U32             :2;
            volatile U32 D2EN        :1;       // DAC2 enable
            volatile U32 D2OBDIS     :1;       // DAC2 output buffer disable
            volatile U32 D2TRGEN     :1;       // DAC2 trigger enable
            volatile U32 D2TRGSEL    :3;       // DAC2 trigger select
            volatile U32 D2NM        :2;       // DAC2 noise mode
            volatile U32 D2NBSEL     :4;       // DAC2 noise bit select
            volatile U32 D2DMAEN     :1;       // DAC2 DMA transfer enable
            volatile U32 D2DMAUDRIEN :1;       // DAC2 DMA transfer underrun interrupt enable
            volatile U32             :2;
        } B;
    } CTRL; // DAC control register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D1SWTRG :1;           // DAC1 software trigger
            volatile U32 D2SWTRG :1;           // DAC2 software trigger
            volatile U32         :30;
        } B;
    } SWTRG; // DAC software trigger register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D1DT12R :12;          // DAC1 12-bit right-aligned data
            volatile U32         :20;
        } B;
    } D1DTH12R; // DAC1 12-bit right-aligned data holding register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32         :4;
            volatile U32 D1DT12L :12;          // DAC1 12-bit left-aligned data
            volatile U32         :16;
        } B;
    } D1DTH12L; // DAC1 12-bit left-aligned data holding register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D1DT8R :8;            // DAC1 8-bit right-aligned data
            volatile U32        :24;
        } B;
    } D1DTH8R; // DAC1 8-bit right-aligned data holding register (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D2DT12R :12;          // DAC2 12-bit right-aligned data
            volatile U32         :20;
        } B;
    } D2DTH12R; // DAC2 12-bit right-aligned data holding register (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32         :4;
            volatile U32 D2DT12L :12;          // DAC2 12-bit left-aligned data
            volatile U32         :16;
        } B;
    } D2DTH12L; // DAC2 12-bit left-aligned data holding register (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D2DT8R :8;            // DAC2 8-bit right-aligned data
            volatile U32        :24;
        } B;
    } D2DTH8R; // DAC2 8-bit right-aligned data holding register (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DD1DT12R :12;         // DAC1 12-bit right-aligned data
            volatile U32          :4;
            volatile U32 DD2DT12R :12;         // DAC2 12-bit right-aligned data
            volatile U32          :4;
        } B;
    } DDTH12R; // Dual DAC 12-bit right-aligned data holding register (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32          :4;
            volatile U32 DD1DT12L :12;         // DAC1 12-bit left-aligned data
            volatile U32          :4;
            volatile U32 DD2DT12L :12;         // DAC2 12-bit left-aligned data
        } B;
    } DDTH12L; // Dual DAC 12-bit left-aligned data holding register (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DD1DT8R :8;           // DAC1 8-bit right-aligned data
            volatile U32 DD2DT8R :8;           // DAC2 8-bit right-aligned data
            volatile U32         :16;
        } B;
    } DDTH8R; // Dual DAC 8-bit right-aligned data holding register (Offset: 0x28; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D1ODT :12;            // DAC1 output data
            volatile U32       :20;
        } B;
    } D1ODT; // DAC1 data output register (Offset: 0x2C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 D2ODT :12;            // DAC2 output data
            volatile U32       :20;
        } B;
    } D2ODT; // DAC2 data output register (Offset: 0x30; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32           :13;
            volatile U32 D1DMAUDRF :1;         // DAC1 DMA transfer underrun flag
            volatile U32           :15;
            volatile U32 D2DMAUDRF :1;         // DAC2 DMA transfer underrun flag
            volatile U32           :2;
        } B;
    } STS; // DAC status register (Offset: 0x34; Reset: 0x0000.0000)

}; // end of DAC_tag



/******************************************************************************/
/*                    Direct memory access (DMA) memory map                   */
/******************************************************************************/
struct DMA_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 GF1     :1;           // Channel 1 global event flag
            volatile U32 FDTF1   :1;           // Channel 1 transfer complete event flag
            volatile U32 HDTF1   :1;           // Channel 1 half transfer event flag
            volatile U32 DTERRF1 :1;           // Channel 1 data transfer error event flag
            volatile U32 GF2     :1;           // Channel 2 global event flag
            volatile U32 FDTF2   :1;           // Channel 2 transfer complete event flag
            volatile U32 HDTF2   :1;           // Channel 2 half transfer event flag
            volatile U32 DTERRF2 :1;           // Channel 2 data transfer error event flag
            volatile U32 GF3     :1;           // Channel 3 global event flag
            volatile U32 FDTF3   :1;           // Channel 3 transfer complete event flag
            volatile U32 HDTF3   :1;           // Channel 3 half transfer event flag
            volatile U32 DTERRF3 :1;           // Channel 3 data transfer error event flag
            volatile U32 GF4     :1;           // Channel 4 global event flag
            volatile U32 FDTF4   :1;           // Channel 4 transfer complete event flag
            volatile U32 HDTF4   :1;           // Channel 4 half transfer event flag
            volatile U32 DTERRF4 :1;           // Channel 4 data transfer error event flag
            volatile U32 GF5     :1;           // Channel 5 global event flag
            volatile U32 FDTF5   :1;           // Channel 5 transfer complete event flag
            volatile U32 HDTF5   :1;           // Channel 5 half transfer event flag
            volatile U32 DTERRF5 :1;           // Channel 5 data transfer error event flag
            volatile U32 GF6     :1;           // Channel 6 global event flag
            volatile U32 FDTF6   :1;           // Channel 6 transfer complete event flag
            volatile U32 HDTF6   :1;           // Channel 6 half transfer event flag
            volatile U32 DTERRF6 :1;           // Channel 6 data transfer error event flag
            volatile U32 GF7     :1;           // Channel 7 global event flag
            volatile U32 FDTF7   :1;           // Channel 7 transfer complete event flag
            volatile U32 HDTF7   :1;           // Channel 7 half transfer event flag
            volatile U32 DTERRF7 :1;           // Channel 7 data transfer error event flag
            volatile U32         :4;
        } B;
    } STS; // DMA interrupt status register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 GFC1     :1;          // Channel 1 global interrupt flag clear
            volatile U32 FDTFC1   :1;          // Channel 1 transfer complete flag clear
            volatile U32 HDTFC1   :1;          // Channel 1 half transfer flag clear
            volatile U32 DTERRFC1 :1;          // Channel 1 data transfer error flag clear
            volatile U32 GFC2     :1;          // Channel 2 global interrupt flag clear
            volatile U32 FDTFC2   :1;          // Channel 2 transfer complete flag clear
            volatile U32 HDTFC2   :1;          // Channel 2 half transfer flag clear
            volatile U32 DTERRFC2 :1;          // Channel 2 data transfer error flag clear
            volatile U32 GFC3     :1;          // Channel 3 global interrupt flag clear
            volatile U32 FDTFC3   :1;          // Channel 3 transfer complete flag clear
            volatile U32 HDTFC3   :1;          // Channel 3 half transfer flag clear
            volatile U32 DTERRFC3 :1;          // Channel 3 data transfer error flag clear
            volatile U32 GFC4     :1;          // Channel 4 global interrupt flag clear
            volatile U32 FDTFC4   :1;          // Channel 4 transfer complete flag clear
            volatile U32 HDTFC4   :1;          // Channel 4 half transfer flag clear
            volatile U32 DTERRFC4 :1;          // Channel 4 data transfer error flag clear
            volatile U32 GFC5     :1;          // Channel 5 global interrupt flag clear
            volatile U32 FDTFC5   :1;          // Channel 5 transfer complete flag clear
            volatile U32 HDTFC5   :1;          // Channel 5 half transfer flag clear
            volatile U32 DTERRFC5 :1;          // Channel 5 data transfer error flag clear
            volatile U32 GFC6     :1;          // Channel 6 global interrupt flag clear
            volatile U32 FDTFC6   :1;          // Channel 6 transfer complete flag clear
            volatile U32 HDTFC6   :1;          // Channel 6 half transfer flag clear
            volatile U32 DTERRFC6 :1;          // Channel 6 data transfer error flag clear
            volatile U32 GFC7     :1;          // Channel 7 global interrupt flag clear
            volatile U32 FDTFC7   :1;          // Channel 7 transfer complete flag clear
            volatile U32 HDTFC7   :1;          // Channel 7 half transfer flag clear
            volatile U32 DTERRFC7 :1;          // Channel 7 data transfer error flag clear
            volatile U32          :4;
        } B;
    } CLR; // DMA interrupt flag clear register (Offset: 0x04; Reset: 0x0000.0000)

    struct {
        union {
            volatile U32 R;
            struct {
                volatile U32 CHEN     :1;      // Channel enable
                volatile U32 FDTIEN   :1;      // Transfer complete interrupt enable
                volatile U32 HDTIEN   :1;      // Half-transfer interrupt enable
                volatile U32 DTERRIEN :1;      // Data transfer error interrupt enable
                volatile U32 DTD      :1;      // Data transfer direction
                volatile U32 LM       :1;      // Circular mode
                volatile U32 PINCM    :1;      // Peripheral address increment mode
                volatile U32 MINCM    :1;      // Memory address increment mode
                volatile U32 PWIDTH   :2;      // Peripheral data bit width
                volatile U32 MWIDTH   :2;      // Memory data bit width
                volatile U32 CHPL     :2;      // Channel priority level
                volatile U32 M2M      :1;      // Memory to memory mode
                volatile U32          :17;
            } B;
        } CTRL; // DMA channel X configuration register (Offset: 0x08; Reset: 0x0000.0000)

        union {
            volatile U32 R;
            struct {
                volatile U32 CNT :16;          // Number of data to transfer
                volatile U32     :16;
            } B;
        } DTCNT; // DMA channel X number of data register (Offset: 0x0C; Reset: 0x0000.0000)

        union {
            volatile U32 R;
            struct {
                volatile U32 PADDR :32;        // Peripheral base address
            } B;
        } PADDR; // DMA channel X peripheral address register (Offset: 0x10; Reset: 0x0000.0000)

        union {
            volatile U32 R;
            struct {
                volatile U32 MADDR :32;        // Memory base address
            } B;
        } MADDR; // DMA channel X memory address register (Offset: 0x14; Reset: 0x0000.0000)

        U32 DMA_Reserved0[1U];                 // Reserved: 0x0018-0x001B
    } CHANNEL[7]; // DMA channels

    U32 DMA_Reserved1[27U];                    // Reserved: 0x0094 - 0x00FF

    union {
        volatile U32 R;
        struct {
            volatile U32 TBL_SEL :1;           // Multiplexer table select
            volatile U32         :31;
        } B;
    } MUXSEL; // DMAMUX selection register (Offset: 0x100; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REQSEL    :7;         // DMA request select
            volatile U32           :1;
            volatile U32 SYNCOVIEN :1;         // Synchronization overrun interrupt enable
            volatile U32 EVTGEN    :1;         // Event generation enable
            volatile U32           :6;
            volatile U32 SYNCEN    :1;         // Synchronization enable
            volatile U32 SYNCPOL   :2;         // Synchronization polarity
            volatile U32 REQCNT    :5;         // DMA request count
            volatile U32 SYNCSEL   :5;         // Synchronization select
            volatile U32           :3;
        } B;
    } MUXCCTRL[7]; //  (Offset: 0x104; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SIGSEL   :5;          // Signal select
            volatile U32          :3;
            volatile U32 TRGOVIEN :1;          // Trigger overrun interrupt enable
            volatile U32          :7;
            volatile U32 GEN      :1;          // DMA request generation enable
            volatile U32 GPOL     :2;          // DMA request generation polarity
            volatile U32 GREQCNT  :5;          // DMA request generation count
            volatile U32          :8;
        } B;
    } MUXGCTRL[4]; // DMAMUX generator X control register (Offset: 0x120; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SYNCOVF :8;           // Synchronization overrun interrupt flag
            volatile U32         :24;
        } B;
    } MUXSYNCSTS; // DMAMUX channel synchronization status register (Offset: 0x130; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SYNCOVFC :8;          // Synchronization overrun interrupt flag clear
            volatile U32          :24;
        } B;
    } MUXSYNCCLR; // DMAMUX channel interrupt clear flag register (Offset: 0x134; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TRGOVF :4;            // Trigger overrun interrupt flag
            volatile U32        :28;
        } B;
    } MUXGSTS; // DMAMUX generator interrupt status register (Offset: 0x138; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TRGOVFC :4;           // Trigger overrun interrupt flag clear
            volatile U32         :28;
        } B;
    } MUXGCLR; // DMAMUX generator interrupt flga clear register (Offset: 0x13C; Reset: 0x0000.0000)

}; // end of DMA_tag



/******************************************************************************/
/*                Enhanced real-time clock (ERTC) memory maps                 */
/******************************************************************************/
struct ERTC_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 SU   :4;              // Second units in BCD format
            volatile U32 ST   :3;              // Second tens in BCD format
            volatile U32      :1;
            volatile U32 MU   :4;              // Minute units in BCD format
            volatile U32 MT   :3;              // Minute tens in BCD format
            volatile U32      :1;
            volatile U32 HU   :4;              // Hour units in BCD format
            volatile U32 HT   :2;              // Hour tens in BCD format
            volatile U32 AMPM :1;              // AM/PM notation
            volatile U32      :9;
        } B;
    } TIME; // ERTC time register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DU :4;                // Date units in BCD format
            volatile U32 DT :2;                // Date tens in BCD format
            volatile U32    :2;
            volatile U32 MU :4;                // Month units in BCD format
            volatile U32 MT :1;                // Month tens in BCD format
            volatile U32 WK :3;                // Week day units
            volatile U32 YU :4;                // Year units in BCD format
            volatile U32 YT :4;                // Year tens in BCD format
            volatile U32    :8;
        } B;
    } DATE; // ERTC date register (Offset: 0x04; Reset: 0x0000.2101)

    union {
        volatile U32 R;
        struct {
            volatile U32 WATCLK  :3;           // Wakeup clock selection
            volatile U32 TSEDG   :1;           // Timestamp event active edge
            volatile U32 RCDEN   :1;           // Reference clock detection enable (50 or 60 Hz)
            volatile U32 DREN    :1;           // Bypass the shadow registers
            volatile U32 HM      :1;           // Hour format
            volatile U32 CCALEN  :1;           // Coarse digital calibration enable
            volatile U32 ALAEN   :1;           // Alarm A enable
            volatile U32 ALBEN   :1;           // Alarm B enable
            volatile U32 WATEN   :1;           // Wakeup timer enable
            volatile U32 TSEN    :1;           // Time stamp enable
            volatile U32 ALAIEN  :1;           // Alarm A interrupt enable
            volatile U32 ALBIEN  :1;           // Alarm B interrupt enable
            volatile U32 WATIEN  :1;           // Wakeup timer interrupt enable
            volatile U32 TSIEN   :1;           // Timestamp interrupt enable
            volatile U32 ADD1H   :1;           // Add 1 hour (summer time change)
            volatile U32 DEC1H   :1;           // Subtract 1 hour (winter time change)
            volatile U32 BPR     :1;           // Backup
            volatile U32 CALOSEL :1;           // Calibration output selection
            volatile U32 OUTP    :1;           // Output polarity
            volatile U32 OUTSEL  :2;           // Output selection
            volatile U32 CALOEN  :1;           // Calibration output enable
            volatile U32         :8;
        } B;
    } CTRL; // ERTC control register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ALAWF   :1;           // Alarm A write flag
            volatile U32 ALBWF   :1;           // Alarm B write flag
            volatile U32 WATWF   :1;           // Wakeup timer write flag
            volatile U32 TADJF   :1;           // Shift operation pending
            volatile U32 INITF   :1;           // Initialization status flag
            volatile U32 UPDF    :1;           // Registers synchronization flag
            volatile U32 IMF     :1;           // Initialization flag
            volatile U32 IMEN    :1;           // Initialization mode
            volatile U32 ALAF    :1;           // Alarm A flag
            volatile U32 ALBF    :1;           // Alarm B flag
            volatile U32 WATF    :1;           // Wakeup timer flag
            volatile U32 TSF     :1;           // Timestamp flag
            volatile U32 TSOF    :1;           // Timestamp overflow flag
            volatile U32 TP1F    :1;           // Tamper 1 detection flag
            volatile U32 TP2F    :1;           // Tamper 2 detection flag
            volatile U32         :1;
            volatile U32 CALUPDF :1;           // Recalibration pending Flag
            volatile U32         :15;
        } B;
    } STS; // ERTC initialization and status register (Offset: 0x0C; Reset: 0x0000.0007)

    union {
        volatile U32 R;
        struct {
            volatile U32 DIVB :15;             // Synchronous prescaler factor
            volatile U32      :1;
            volatile U32 DIVA :7;              // Asynchronous prescaler factor
            volatile U32      :9;
        } B;
    } DIV; // ERTC divider register (Offset: 0x10; Reset: 0x007F.00FF)

    union {
        volatile U32 R;
        struct {
            volatile U32 VAL :16;              // Wakeup auto-reload value bits
            volatile U32     :16;
        } B;
    } WAT; // ERTC wakeup timer register (Offset: 0x14; Reset: 0x0000.FFFF)

    union {
        volatile U32 R;
        struct {
            volatile U32 CALVAL :5;            // Digital calibration
            volatile U32        :2;
            volatile U32 CALDIR :1;            // Digital calibration sign
            volatile U32        :24;
        } B;
    } CCAL; // ERTC coarse calibration register (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SU    :4;             // Second units in BCD format
            volatile U32 ST    :3;             // Second tens in BCD format
            volatile U32 MASK1 :1;             // Alarm A seconds mask
            volatile U32 MU    :4;             // Minute units in BCD format
            volatile U32 MT    :3;             // Minute tens in BCD format
            volatile U32 MASK2 :1;             // Alarm A minutes mask
            volatile U32 HU    :4;             // Hour units in BCD format
            volatile U32 HT    :2;             // Hour tens in BCD format
            volatile U32 AMPM  :1;             // AM/PM notation
            volatile U32 MASK3 :1;             // Alarm A hours mask
            volatile U32 DU    :4;             // Date units or day in BCD format
            volatile U32 DT    :2;             // Date tens in BCD format
            volatile U32 WKSEL :1;             // Week day selection
            volatile U32 MASK4 :1;             // Alarm A date mask
        } B;
    } ALA; // ERTC alarm clock A register (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SU    :4;             // Second units in BCD format
            volatile U32 ST    :3;             // Second tens in BCD format
            volatile U32 MASK1 :1;             // Alarm B seconds mask
            volatile U32 MU    :4;             // Minute units in BCD format
            volatile U32 MT    :3;             // Minute tens in BCD format
            volatile U32 MASK2 :1;             // Alarm B minutes mask
            volatile U32 HU    :4;             // Hour units in BCD format
            volatile U32 HT    :2;             // Hour tens in BCD format
            volatile U32 AMPM  :1;             // AM/PM notation
            volatile U32 MASK3 :1;             // Alarm B hours mask
            volatile U32 DU    :4;             // Date units or day in BCD format
            volatile U32 DT    :2;             // Date tens in BCD format
            volatile U32 WKSEL :1;             // Week day selection
            volatile U32 MASK4 :1;             // Alarm B date mask
        } B;
    } ALB; // ERTC alarm clock B register (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CMD :8;               // Write protection key
            volatile U32     :24;
        } B;
    } WP; // ERTC write protection register (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SBS :16;              // Sub second value
            volatile U32     :16;
        } B;
    } SBS; // ERTC subsecond register (Offset: 0x28; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DECSBS :15;           // Subtract a fraction of a second
            volatile U32        :16;
            volatile U32 ADD1S  :1;            // Add one second
        } B;
    } TADJ; // ERTC time adjustment register (Offset: 0x30; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SU   :4;              // Second units in BCD format
            volatile U32 ST   :3;              // Second tens in BCD format
            volatile U32      :1;
            volatile U32 MU   :4;              // Minute units in BCD format
            volatile U32 MT   :3;              // Minute tens in BCD format
            volatile U32      :1;
            volatile U32 HU   :4;              // Hour units in BCD format
            volatile U32 HT   :2;              // Hour tens in BCD format
            volatile U32 AMPM :1;              // AM/PM notation
            volatile U32      :9;
        } B;
    } TSTM; // ERTC time stamp time register (Offset: 0x30; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DU :4;                // Date units in BCD format
            volatile U32 DT :2;                // Date tens in BCD format
            volatile U32    :2;
            volatile U32 MU :4;                // Month units in BCD format
            volatile U32 MT :1;                // Month tens in BCD format
            volatile U32 WK :3;                // Week day units
            volatile U32    :16;
        } B;
    } TSDT; // ERTC time stamp date register (Offset: 0x34; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SBS :16;              // Sub second value
            volatile U32     :16;
        } B;
    } TSSBS; // ERTC time stamp subsecond register (Offset: 0x38; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DEC   :9;             // Calibration minus
            volatile U32       :4;
            volatile U32 DEC16 :1;             // Use a 16-second calibration cycle period
            volatile U32 DEC8  :1;             // Use an 8-second calibration cycle period
            volatile U32 ADD   :1;             // Increase frequency of RTC by 488.5 ppm
            volatile U32       :16;
        } B;
    } SCAL; // ERTC smooth calibration register (Offset: 0x3C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TP1EN   :1;           // Tamper 1 detection enable
            volatile U32 TP1EDG  :1;           // Active level for tamper 1
            volatile U32 TPIEN   :1;           // Tamper interrupt enable
            volatile U32 TP2EN   :1;           // Tamper 2 detection enable
            volatile U32 TP2EDG  :1;           // Active level for tamper 2
            volatile U32         :2;
            volatile U32 TPTSEN  :1;           // Activate timestamp on tamper detection event
            volatile U32 TPFREQ  :3;           // Tamper sampling frequency
            volatile U32 TPFLT   :2;           // Tamper filter count
            volatile U32 TPPR    :2;           // Tamper precharge duration
            volatile U32 TPPU    :1;           // Tamper pull-up disable
            volatile U32 TP1IN   :1;           // TAMPER1 mapping
            volatile U32 TSPIN   :1;           // TIMESTAMP mapping
            volatile U32 OUTTYPE :1;           // RTC_ALARM output type
            volatile U32         :13;
        } B;
    } TAMP; // ERTC tamper configuration register (Offset: 0x40; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SBS    :15;           // Sub-seconds value
            volatile U32        :9;
            volatile U32 SBSMSK :4;            // Sub-second mask
            volatile U32        :4;
        } B;
    } ALASBS; // ERTC alarm clock A subsecond register (Offset: 0x44; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SBS    :15;           // Sub-seconds value
            volatile U32        :9;
            volatile U32 SBSMSK :4;            // Sub-second mask
            volatile U32        :4;
        } B;
    } ALBSBS; // ERTC alarm clocl B subsecond register (Offset: 0x48; Reset: 0x0000.0000)

    U32 RTC_Reserved0[1U];                     //  Reserved: 0x004C-0x004F

    volatile U32 BPR[20U];                     //  ERTC battery powered domain data register (Offset: 0x50; Reset: 0x0000.0000)

}; // end of ERTC_tag



/******************************************************************************/
/*          External interrupt / event controller (EXINT) memory map          */
/******************************************************************************/
struct EXINT_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 INTEN0  :1;           // Interrupt enable or disable on line 0
            volatile U32 INTEN1  :1;           // Interrupt enable or disable on line 1
            volatile U32 INTEN2  :1;           // Interrupt enable or disable on line 2
            volatile U32 INTEN3  :1;           // Interrupt enable or disable on line 3
            volatile U32 INTEN4  :1;           // Interrupt enable or disable on line 4
            volatile U32 INTEN5  :1;           // Interrupt enable or disable on line 5
            volatile U32 INTEN6  :1;           // Interrupt enable or disable on line 6
            volatile U32 INTEN7  :1;           // Interrupt enable or disable on line 7
            volatile U32 INTEN8  :1;           // Interrupt enable or disable on line 8
            volatile U32 INTEN9  :1;           // Interrupt enable or disable on line 9
            volatile U32 INTEN10 :1;           // Interrupt enable or disable on line 10
            volatile U32 INTEN11 :1;           // Interrupt enable or disable on line 11
            volatile U32 INTEN12 :1;           // Interrupt enable or disable on line 12
            volatile U32 INTEN13 :1;           // Interrupt enable or disable on line 13
            volatile U32 INTEN14 :1;           // Interrupt enable or disable on line 14
            volatile U32 INTEN15 :1;           // Interrupt enable or disable on line 15
            volatile U32 INTEN16 :1;           // Interrupt enable or disable on line 16
            volatile U32 INTEN17 :1;           // Interrupt enable or disable on line 17
            volatile U32 INTEN18 :1;           // Interrupt enable or disable on line 18
            volatile U32 INTEN19 :1;           // Interrupt enable or disable on line 19
            volatile U32 INTEN20 :1;           // Interrupt enable or disable on line 20
            volatile U32 INTEN21 :1;           // Interrupt enable or disable on line 21
            volatile U32 INTEN22 :1;           // Interrupt enable or disable on line 22
            volatile U32         :9;
        } B;
    } INTEN; // Interrupt enable register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 EVTEN0  :1;           // Event enable or disable on line 0
            volatile U32 EVTEN1  :1;           // Event enable or disable on line 1
            volatile U32 EVTEN2  :1;           // Event enable or disable on line 2
            volatile U32 EVTEN3  :1;           // Event enable or disable on line 3
            volatile U32 EVTEN4  :1;           // Event enable or disable on line 4
            volatile U32 EVTEN5  :1;           // Event enable or disable on line 5
            volatile U32 EVTEN6  :1;           // Event enable or disable on line 6
            volatile U32 EVTEN7  :1;           // Event enable or disable on line 7
            volatile U32 EVTEN8  :1;           // Event enable or disable on line 8
            volatile U32 EVTEN9  :1;           // Event enable or disable on line 9
            volatile U32 EVTEN10 :1;           // Event enable or disable on line 10
            volatile U32 EVTEN11 :1;           // Event enable or disable on line 11
            volatile U32 EVTEN12 :1;           // Event enable or disable on line 12
            volatile U32 EVTEN13 :1;           // Event enable or disable on line 13
            volatile U32 EVTEN14 :1;           // Event enable or disable on line 14
            volatile U32 EVTEN15 :1;           // Event enable or disable on line 15
            volatile U32 EVTEN16 :1;           // Event enable or disable on line 16
            volatile U32 EVTEN17 :1;           // Event enable or disable on line 17
            volatile U32 EVTEN18 :1;           // Event enable or disable on line 18
            volatile U32 EVTEN19 :1;           // Event enable or disable on line 19
            volatile U32 EVTEN20 :1;           // Event enable or disable on line 20
            volatile U32 EVTEN21 :1;           // Event enable or disable on line 21
            volatile U32 EVTEN22 :1;           // Event enable or disable on line 22
            volatile U32         :9;
        } B;
    } EVTEN; // Event enable register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RP0  :1;              // Rising polarity configuration bit on line 0
            volatile U32 RP1  :1;              // Rising polarity configuration bit on line 1
            volatile U32 RP2  :1;              // Rising polarity configuration bit on line 2
            volatile U32 RP3  :1;              // Rising polarity configuration bit on line 3
            volatile U32 RP4  :1;              // Rising polarity configuration bit on line 4
            volatile U32 RP5  :1;              // Rising polarity configuration bit on line 5
            volatile U32 RP6  :1;              // Rising polarity configuration bit on line 6
            volatile U32 RP7  :1;              // Rising polarity configuration bit on line 7
            volatile U32 RP8  :1;              // Rising polarity configuration bit on line 8
            volatile U32 RP9  :1;              // Rising polarity configuration bit on line 9
            volatile U32 RP10 :1;              // Rising polarity configuration bit on line 10
            volatile U32 RP11 :1;              // Rising polarity configuration bit on line 11
            volatile U32 RP12 :1;              // Rising polarity configuration bit on line 12
            volatile U32 RP13 :1;              // Rising polarity configuration bit on line 13
            volatile U32 RP14 :1;              // Rising polarity configuration bit on line 14
            volatile U32 RP15 :1;              // Rising polarity configuration bit on line 15
            volatile U32 RP16 :1;              // Rising polarity configuration bit on line 16
            volatile U32 RP17 :1;              // Rising polarity configuration bit on line 17
            volatile U32 RP18 :1;              // Rising polarity configuration bit on line 18
            volatile U32 RP19 :1;              // Rising polarity configuration bit on line 19
            volatile U32 RP20 :1;              // Rising polarity configuration bit on line 20
            volatile U32 RP21 :1;              // Rising polarity configuration bit on line 21
            volatile U32 RP22 :1;              // Rising polarity configuration bit on line 22
            volatile U32      :9;
        } B;
    } POLCFG1; // Polarity configuration register 1 (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 FP0  :1;              // Falling polarity configuration bit on line 0
            volatile U32 FP1  :1;              // Falling polarity configuration bit on line 1
            volatile U32 FP2  :1;              // Falling polarity configuration bit on line 2
            volatile U32 FP3  :1;              // Falling polarity configuration bit on line 3
            volatile U32 FP4  :1;              // Falling polarity configuration bit on line 4
            volatile U32 FP5  :1;              // Falling polarity configuration bit on line 5
            volatile U32 FP6  :1;              // Falling polarity configuration bit on line 6
            volatile U32 FP7  :1;              // Falling polarity configuration bit on line 7
            volatile U32 FP8  :1;              // Falling polarity configuration bit on line 8
            volatile U32 FP9  :1;              // Falling polarity configuration bit on line 9
            volatile U32 FP10 :1;              // Falling polarity configuration bit on line 10
            volatile U32 FP11 :1;              // Falling polarity configuration bit on line 11
            volatile U32 FP12 :1;              // Falling polarity configuration bit on line 12
            volatile U32 FP13 :1;              // Falling polarity configuration bit on line 13
            volatile U32 FP14 :1;              // Falling polarity configuration bit on line 14
            volatile U32 FP15 :1;              // Falling polarity configuration bit on line 15
            volatile U32 FP16 :1;              // Falling polarity configuration bit on line 16
            volatile U32 FP17 :1;              // Falling polarity configuration bit on line 17
            volatile U32 FP18 :1;              // Falling polarity configuration bit on line 18
            volatile U32 FP19 :1;              // Falling polarity configuration bit on line 19
            volatile U32 FP20 :1;              // Falling polarity configuration bit on line 20
            volatile U32 FP21 :1;              // Falling polarity configuration bit on line 21
            volatile U32 FP22 :1;              // Falling polarity configuration bit on line 22
            volatile U32      :9;
        } B;
    } POLCFG2; // Polarity configuration register 2 (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SWT0  :1;             // Software triggle on line 0
            volatile U32 SWT1  :1;             // Software triggle on line 1
            volatile U32 SWT2  :1;             // Software triggle on line 2
            volatile U32 SWT3  :1;             // Software triggle on line 3
            volatile U32 SWT4  :1;             // Software triggle on line 4
            volatile U32 SWT5  :1;             // Software triggle on line 5
            volatile U32 SWT6  :1;             // Software triggle on line 6
            volatile U32 SWT7  :1;             // Software triggle on line 7
            volatile U32 SWT8  :1;             // Software triggle on line 8
            volatile U32 SWT9  :1;             // Software triggle on line 9
            volatile U32 SWT10 :1;             // Software triggle on line 10
            volatile U32 SWT11 :1;             // Software triggle on line 11
            volatile U32 SWT12 :1;             // Software triggle on line 12
            volatile U32 SWT13 :1;             // Software triggle on line 13
            volatile U32 SWT14 :1;             // Software triggle on line 14
            volatile U32 SWT15 :1;             // Software triggle on line 15
            volatile U32 SWT16 :1;             // Software triggle on line 16
            volatile U32 SWT17 :1;             // Software triggle on line 17
            volatile U32 SWT18 :1;             // Software triggle on line 18
            volatile U32 SWT19 :1;             // Software triggle on line 19
            volatile U32 SWT20 :1;             // Software triggle on line 20
            volatile U32 SWT21 :1;             // Software triggle on line 21
            volatile U32 SWT22 :1;             // Software triggle on line 22
            volatile U32         :9;
        } B;
    } SWTRG; // Software trigger register (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 LINE0  :1;            // Line 0 status bit
            volatile U32 LINE1  :1;            // Line 1 status bit
            volatile U32 LINE2  :1;            // Line 2 status bit
            volatile U32 LINE3  :1;            // Line 3 status bit
            volatile U32 LINE4  :1;            // Line 4 status bit
            volatile U32 LINE5  :1;            // Line 5 status bit
            volatile U32 LINE6  :1;            // Line 6 status bit
            volatile U32 LINE7  :1;            // Line 7 status bit
            volatile U32 LINE8  :1;            // Line 8 status bit
            volatile U32 LINE9  :1;            // Line 9 status bit
            volatile U32 LINE10 :1;            // Line 10 status bit
            volatile U32 LINE11 :1;            // Line 11 status bit
            volatile U32 LINE12 :1;            // Line 12 status bit
            volatile U32 LINE13 :1;            // Line 13 status bit
            volatile U32 LINE14 :1;            // Line 14 status bit
            volatile U32 LINE15 :1;            // Line 15 status bit
            volatile U32 LINE16 :1;            // Line 16 status bit
            volatile U32 LINE17 :1;            // Line 17 status bit
            volatile U32 LINE18 :1;            // Line 18 status bit
            volatile U32 LINE19 :1;            // Line 19 status bit
            volatile U32 LINE20 :1;            // Line 20 status bit
            volatile U32 LINE21 :1;            // Line 21 status bit
            volatile U32 LINE22 :1;            // Line 22 status bit
            volatile U32        :9;
        } B;
    } INTSTS; // Interrupt status register (Offset: 0x14; Reset: 0x0000.0000)

}; // end of EXINT_tag



/******************************************************************************/
/*                 Flash memory controller (FLASH) memory map                 */
/******************************************************************************/
struct FLASH_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32             :12;
            volatile U32 NZW_BST     :1;       // Flash non-zero wait area boost
            volatile U32 NZW_BST_STS :1;       // Flash non-zero wait area boost status
            volatile U32             :18;
        } B;
    } PSR; // Flash performance select register (Offset: 0x00; Reset: 0x0000.0330)

    union {
        volatile U32 R;
        struct {
            volatile U32 UKVAL :32;            // Unlock key value
        } B;
    } UNLOCK; // Flash unlock register (Offset: 0x04; Reset: 0xXXXX.XXXX)

    union {
        volatile U32 R;
        struct {
            volatile U32 USD_UKVAL :32;        // User system data Unlock key value
        } B;
    } USD_UNLOCK; // Flash user system data unlock register (Offset: 0x08; Reset: 0xXXXX.XXXX)

    union {
        volatile U32 R;
        struct {
            volatile U32 OBF     :1;           // Operation busy flag
            volatile U32         :1;
            volatile U32 PRGMERR :1;           // Programming error
            volatile U32         :1;
            volatile U32 EPPERR  :1;           // Erase/program protection error
            volatile U32 ODF     :1;           // Operation done flag
            volatile U32         :26;
        } B;
    } STS; // Flash status register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 FPRGM   :1;           // Flash program
            volatile U32 SECERS  :1;           // Page erase
            volatile U32 BANKERS :1;           // Sector erase
            volatile U32 BLKERS  :1;           // Bank erase
            volatile U32 USDPRGM :1;           // User system data program
            volatile U32 USDERS  :1;           // User system data erase
            volatile U32 ERSTR   :1;           // Erase start
            volatile U32 OPLK    :1;           // Operation lock
            volatile U32         :1;
            volatile U32 USDULKS :1;           // User system data unlock success
            volatile U32 ERRIE   :1;           // Error interrupt enable
            volatile U32         :1;
            volatile U32 ODFIE   :1;           // Operation done flag interrupt enable
            volatile U32         :19;
        } B;
    } CTRL; // Flash control register (Offset: 0x10; Reset: 0x8000.0080)

    union {
        volatile U32 R;
        struct {
            volatile U32 FA :32;               // Flash address
        } B;
    } ADDR; // Flash address register (Offset: 0x14; Reset: 0x0000.0000)

    U32 FLASH_Reserved0[1U];                   // Reserved :0x0018-0x000B

    union {
        volatile U32 R;
        struct {
            volatile U32 USDERR      :1;       // User system data error
            volatile U32 FAP         :1;       // Flash access protection
            volatile U32 nWDT_ATO_EN :1;
            volatile U32 nDEPSLP_RST :1;
            volatile U32 nSTDBY_RST  :1;
            volatile U32 BTOPT       :1;
            volatile U32             :1;
            volatile U32 nWDT_DEPSLP :1;
            volatile U32 nWDT_STDBY  :1;
            volatile U32             :1;
            volatile U32 USER_D0     :8;       // User data 0
            volatile U32 USER_D1     :8;       // User data 1
            volatile U32             :6;
        } B;
    } USD; // User system data register (Offset: 0x1C; Reset: 0x03FF.FFFC)

    union {
        volatile U32 R;
        struct {
            volatile U32 EPPS :32;             // Erase/Program protection status
        } B;
    } EPPS0; // Erase/program protection status register 0 (Offset: 0x20; Reset: 0xFFFF.FFFF)

    U32 FLASH_Reserved1[2U];                   // Reserved :0x0024-0x002B

    union {
        volatile U32 R;
        struct {
            volatile U32 EPPS :32;             // Erase/Program protection status
        } B;
    } EPPS1; // Erase/program protection status register 1 (Offset: 0x2C; Reset: 0xFFFF.FFFF)

    U32 FLASH_Reserved2[5U];                   // Reserved :0x0030-0x0043

    union {
        volatile U32 R;
        struct {
            volatile U32 UKVAL :32;            // Unlock key value
        } B;
    } UNLOCK2; // Flash unlock register 2 (Offset: 0x44; Reset: 0xXXXX.XXXX)

    U32 FLASH_Reserved3[1U];                   // Reserved :0x0048-0x004B

    union {
        volatile U32 R;
        struct {
            volatile U32 OBF     :1;           // Operation busy flag
            volatile U32         :1;
            volatile U32 PRGMERR :1;           // Program error
            volatile U32         :1;
            volatile U32 EPPERR  :1;           // Erase/Program protection error
            volatile U32 ODF     :1;           // Operation done flag
            volatile U32         :26;
        } B;
    } STS2; // Flash status register 2 (Offset: 0x4C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 FPRGM   :1;           // Flash program
            volatile U32 SECERS  :1;           // Page erase
            volatile U32 BANKERS :1;           // Sector erase
            volatile U32 BLKERS  :1;           // Bank erase
            volatile U32         :2;
            volatile U32 ERSTR   :1;           // Erase start
            volatile U32 OPLK    :1;           // Operation lock
            volatile U32         :2;
            volatile U32 ERRIE   :1;           // Error interrupt enable
            volatile U32         :1;
            volatile U32 ODFIE   :1;           // Operation done flag interrupt enable
            volatile U32         :19;
        } B;
    } CTRL2; // Flash control register 2 (Offset: 0x50; Reset: 0x0000.0080)

    union {
        volatile U32 R;
        struct {
            volatile U32 FA :32;               // Flash address
        } B;
    } ADDR2; // Flash address register 2 (Offset: 0x54; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 FCONTR_EN :32;        // Flash continue read enable
        } B;
    } CONTR; // Flash continue read register (Offset: 0x58; Reset: 0x0000.0080)

    U32 FLASH_Reserved4[1U];                   // Reserved :0x005C-0x005F

    union {
        volatile U32 R;
        struct {
            volatile U32 FDIV     :2;          // Flash divider
            volatile U32          :2;
            volatile U32 FDIV_STS :2;          // Flash divider status
            volatile U32          :26;
        } B;
    } DIVR; // Flash divider register (Offset: 0x60; Reset: 0x0000.0022)

    U32 FLASH_Reserved5[26U];                  // Reserved :0x0064-0x00C7

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_ENF :16;         // sLib instruction start page
            volatile U32          :16;
        } B;
    } SLIB_STS2; // Flash security library status register 2 (Offset: 0xC8; Reset: 0x0000.FFFF)

    union {
        volatile U32 R;
        struct {
            volatile U32          :3;
            volatile U32 SLIB_ENF :1;          // sLib enable flag
            volatile U32          :28;
        } B;
    } SLIB_STS0; // Flash security library status register 0 (Offset: 0xCC; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_SS :16;          // Security library start page
            volatile U32 SLIB_ES :16;          // Security library end page
        } B;
    } SLIB_STS1; // Flash security library status register 1 (Offset: 0xD0; Reset: 0xFFFF.FFFF)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_PCLR_VAL :32;    // Security library password clear value
        } B;
    } SLIB_PWD_CLR; // Flash security library password clear register (Offset: 0xD4; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_PWD_ERR :1;      // Security library password error
            volatile U32 SLIB_PWD_OK  :1;      // Security library password ok
            volatile U32 SLIB_ULKF    :1;      // Security library unlock flag
            volatile U32              :13;
            volatile U32 SLIB_RCNT    :9;      // Security library remaining count
            volatile U32              :7;
        } B;
    } SLIB_MISC_STS; // Security library additional status register (Offset: 0xD8; Reset: 0x0100.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_PSET_VAL :32;    // Security library password setting value
        } B;
    } SLIB_SET_PWD; // Security library password setting register (Offset: 0xDC; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_SS_SET :16;      // Security library start page
            volatile U32 SLIB_ES_SET :16;      // Security library end page
        } B;
    } SLIB_SET_RANGE0; // Security library address setting register 0 (Offset: 0xE0; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_SS_SET   :16;    // Security library instruction start page setting
            volatile U32               :15;
            volatile U32 SET_SLIB_STRT :1;     // Setting sLib start
        } B;
    } SLIB_SET_RANGE1; // Security library address setting register 1 (Offset: 0xE4; Reset: 0x0000.0000)

    U32 FLASH_Reserved6[2U];                   // Reserved :0x00E8-0x00EF

    union {
        volatile U32 R;
        struct {
            volatile U32 SLIB_UKVAL :32;       // Security library unlock key value
        } B;
    } SLIB_UNLOCK; // Security library unlock register (Offset: 0xF0; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CRC_SS   :12;         // CRC calibration start page
            volatile U32 CRC_SN   :12;         // CRC page numbler
            volatile U32          :7;
            volatile U32 CRC_STRT :1;          // CRC start
        } B;
    } CRC_CTRL; // Flash CRC calibration control register (Offset: 0xF4; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CRC_CHKR :32;         // CRC check result
        } B;
    } CRC_CHKR; // Flash CRC check result register (Offset: 0xF8; Reset: 0x0000.0000)

}; // end of FLASH_tag



/******************************************************************************/
/*               General Port Input / Output (GPIO) memory map                */
/******************************************************************************/
struct GPIO_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 IOMC0  :2;            // GPIO pin 0 mode configuration
            volatile U32 IOMC1  :2;            // GPIO pin 1 mode configuration
            volatile U32 IOMC2  :2;            // GPIO pin 2 mode configuration
            volatile U32 IOMC3  :2;            // GPIO pin 3 mode configuration
            volatile U32 IOMC4  :2;            // GPIO pin 4 mode configuration
            volatile U32 IOMC5  :2;            // GPIO pin 5 mode configuration
            volatile U32 IOMC6  :2;            // GPIO pin 6 mode configuration
            volatile U32 IOMC7  :2;            // GPIO pin 7 mode configuration
            volatile U32 IOMC8  :2;            // GPIO pin 8 mode configuration
            volatile U32 IOMC9  :2;            // GPIO pin 9 mode configuration
            volatile U32 IOMC10 :2;            // GPIO pin 10 mode configuration
            volatile U32 IOMC11 :2;            // GPIO pin 11 mode configuration
            volatile U32 IOMC12 :2;            // GPIO pin 12 mode configuration
            volatile U32 IOMC13 :2;            // GPIO pin 13 mode configuration
            volatile U32 IOMC14 :2;            // GPIO pin 14 mode configuration
            volatile U32 IOMC15 :2;            // GPIO pin 15 mode configuration
        } B;
    } CFGR; // GPIO configuration register (Offset: 0x00; Reset: 0x0000.0000
            //                             (PA: 0xA800.0000; PB: 0x0000.0280))

    union {
        volatile U32 R;
        struct {
            volatile U32 OM0  :1;              // GPIO pin 0 output mode configuration
            volatile U32 OM1  :1;              // GPIO pin 1 output mode configuration
            volatile U32 OM2  :1;              // GPIO pin 2 output mode configuration
            volatile U32 OM3  :1;              // GPIO pin 3 output mode configuration
            volatile U32 OM4  :1;              // GPIO pin 4 output mode configuration
            volatile U32 OM5  :1;              // GPIO pin 5 output mode configuration
            volatile U32 OM6  :1;              // GPIO pin 6 output mode configuration
            volatile U32 OM7  :1;              // GPIO pin 7 output mode configuration
            volatile U32 OM8  :1;              // GPIO pin 8 output mode configuration
            volatile U32 OM9  :1;              // GPIO pin 9 output mode configuration
            volatile U32 OM10 :1;              // GPIO pin 10 output mode configuration
            volatile U32 OM11 :1;              // GPIO pin 11 output mode configuration
            volatile U32 OM12 :1;              // GPIO pin 12 output mode configuration
            volatile U32 OM13 :1;              // GPIO pin 13 output mode configuration
            volatile U32 OM14 :1;              // GPIO pin 14 output mode configuration
            volatile U32 OM15 :1;              // GPIO pin 15 output mode configuration
            volatile U32      :16;
        } B;
    } OMODER; // GPIO output mode register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ODRV0  :2;            // GPIO pin 0 drive capability
            volatile U32 ODRV1  :2;            // GPIO pin 1 drive capability
            volatile U32 ODRV2  :2;            // GPIO pin 2 drive capability
            volatile U32 ODRV3  :2;            // GPIO pin 3 drive capability
            volatile U32 ODRV4  :2;            // GPIO pin 4 drive capability
            volatile U32 ODRV5  :2;            // GPIO pin 5 drive capability
            volatile U32 ODRV6  :2;            // GPIO pin 6 drive capability
            volatile U32 ODRV7  :2;            // GPIO pin 7 drive capability
            volatile U32 ODRV8  :2;            // GPIO pin 8 drive capability
            volatile U32 ODRV9  :2;            // GPIO pin 9 drive capability
            volatile U32 ODRV10 :2;            // GPIO pin 10 drive capability
            volatile U32 ODRV11 :2;            // GPIO pin 11 drive capability
            volatile U32 ODRV12 :2;            // GPIO pin 12 drive capability
            volatile U32 ODRV13 :2;            // GPIO pin 13 drive capability
            volatile U32 ODRV14 :2;            // GPIO pin 14 drive capability
            volatile U32 ODRV15 :2;            // GPIO pin 15 drive capability
        } B;
    } ODRVR; // GPIO drive capability register (Offset: 0x08; Reset: 0x0000.0000
             //                                (PB: 0x0000.00C0))

    union {
        volatile U32 R;
        struct {
            volatile U32 PULL0  :2;            // GPIO pin 0 pull-up/pull-down configuration
            volatile U32 PULL1  :2;            // GPIO pin 1 pull-up/pull-down configuration
            volatile U32 PULL2  :2;            // GPIO pin 2 pull-up/pull-down configuration
            volatile U32 PULL3  :2;            // GPIO pin 3 pull-up/pull-down configuration
            volatile U32 PULL4  :2;            // GPIO pin 4 pull-up/pull-down configuration
            volatile U32 PULL5  :2;            // GPIO pin 5 pull-up/pull-down configuration
            volatile U32 PULL6  :2;            // GPIO pin 6 pull-up/pull-down configuration
            volatile U32 PULL7  :2;            // GPIO pin 7 pull-up/pull-down configuration
            volatile U32 PULL8  :2;            // GPIO pin 8 pull-up/pull-down configuration
            volatile U32 PULL9  :2;            // GPIO pin 9 pull-up/pull-down configuration
            volatile U32 PULL10 :2;            // GPIO pin 10 pull-up/pull-down configuration
            volatile U32 PULL11 :2;            // GPIO pin 11 pull-up/pull-down configuration
            volatile U32 PULL12 :2;            // GPIO pin 12 pull-up/pull-down configuration
            volatile U32 PULL13 :2;            // GPIO pin 13 pull-up/pull-down configuration
            volatile U32 PULL14 :2;            // GPIO pin 14 pull-up/pull-down configuration
            volatile U32 PULL15 :2;            // GPIO pin 15 pull-up/pull-down configuration
        } B;
    } PULL; // Port pull-up/pull-down register (Offset: 0x0C; Reset: 0x0000.0000;
            //                                 (PA: 0x6400.0000; PB: 0x0000.0100))

    union {
        volatile U32 R;
        struct {
            volatile U32 IDT0  :1;             // GPIO pin 0 input data
            volatile U32 IDT1  :1;             // GPIO pin 1 input data
            volatile U32 IDT2  :1;             // GPIO pin 2 input data
            volatile U32 IDT3  :1;             // GPIO pin 3 input data
            volatile U32 IDT4  :1;             // GPIO pin 4 input data
            volatile U32 IDT5  :1;             // GPIO pin 5 input data
            volatile U32 IDT6  :1;             // GPIO pin 6 input data
            volatile U32 IDT7  :1;             // GPIO pin 7 input data
            volatile U32 IDT8  :1;             // GPIO pin 8 input data
            volatile U32 IDT9  :1;             // GPIO pin 9 input data
            volatile U32 IDT10 :1;             // GPIO pin 10 input data
            volatile U32 IDT11 :1;             // GPIO pin 11 input data
            volatile U32 IDT12 :1;             // GPIO pin 12 input data
            volatile U32 IDT13 :1;             // GPIO pin 13 input data
            volatile U32 IDT14 :1;             // GPIO pin 14 input data
            volatile U32 IDT15 :1;             // GPIO pin 15 input data
            volatile U32       :16;
        } B;
    } IDT; // GPIO input register (Offset: 0x10; Reset: 0x0000.xxxx)

    union {
        volatile U32 R;
        struct {
            volatile U32 ODT0  :1;             // GPIO pin 0 output data
            volatile U32 ODT1  :1;             // GPIO pin 1 output data
            volatile U32 ODT2  :1;             // GPIO pin 2 output data
            volatile U32 ODT3  :1;             // GPIO pin 3 output data
            volatile U32 ODT4  :1;             // GPIO pin 4 output data
            volatile U32 ODT5  :1;             // GPIO pin 5 output data
            volatile U32 ODT6  :1;             // GPIO pin 6 output data
            volatile U32 ODT7  :1;             // GPIO pin 7 output data
            volatile U32 ODT8  :1;             // GPIO pin 8 output data
            volatile U32 ODT9  :1;             // GPIO pin 9 output data
            volatile U32 ODT10 :1;             // GPIO pin 10 output data
            volatile U32 ODT11 :1;             // GPIO pin 11 output data
            volatile U32 ODT12 :1;             // GPIO pin 12 output data
            volatile U32 ODT13 :1;             // GPIO pin 13 output data
            volatile U32 ODT14 :1;             // GPIO pin 14 output data
            volatile U32 ODT15 :1;             // GPIO pin 15 output data
            volatile U32       :16;
        } B;
    } ODT; // GPIO output register (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 IOSB0  :1;            // GPIO pin 0 set bit
            volatile U32 IOSB1  :1;            // GPIO pin 1 set bit
            volatile U32 IOSB2  :1;            // GPIO pin 2 set bit
            volatile U32 IOSB3  :1;            // GPIO pin 3 set bit
            volatile U32 IOSB4  :1;            // GPIO pin 4 set bit
            volatile U32 IOSB5  :1;            // GPIO pin 5 set bit
            volatile U32 IOSB6  :1;            // GPIO pin 6 set bit
            volatile U32 IOSB7  :1;            // GPIO pin 7 set bit
            volatile U32 IOSB8  :1;            // GPIO pin 8 set bit
            volatile U32 IOSB9  :1;            // GPIO pin 9 set bit
            volatile U32 IOSB10 :1;            // GPIO pin 10 set bit
            volatile U32 IOSB11 :1;            // GPIO pin 11 set bit
            volatile U32 IOSB12 :1;            // GPIO pin 12 set bit
            volatile U32 IOSB13 :1;            // GPIO pin 13 set bit
            volatile U32 IOSB14 :1;            // GPIO pin 14 set bit
            volatile U32 IOSB15 :1;            // GPIO pin 15 set bit
            volatile U32 IOCB0  :1;            // GPIO pin 0 clear bit
            volatile U32 IOCB1  :1;            // GPIO pin 1 clear bit
            volatile U32 IOCB2  :1;            // GPIO pin 2 clear bit
            volatile U32 IOCB3  :1;            // GPIO pin 3 clear bit
            volatile U32 IOCB4  :1;            // GPIO pin 4 clear bit
            volatile U32 IOCB5  :1;            // GPIO pin 5 clear bit
            volatile U32 IOCB6  :1;            // GPIO pin 6 clear bit
            volatile U32 IOCB7  :1;            // GPIO pin 7 clear bit
            volatile U32 IOCB8  :1;            // GPIO pin 8 clear bit
            volatile U32 IOCB9  :1;            // GPIO pin 9 clear bit
            volatile U32 IOCB10 :1;            // GPIO pin 10 clear bit
            volatile U32 IOCB11 :1;            // GPIO pin 11 clear bit
            volatile U32 IOCB12 :1;            // GPIO pin 12 clear bit
            volatile U32 IOCB13 :1;            // GPIO pin 13 clear bit
            volatile U32 IOCB14 :1;            // GPIO pin 14 clear bit
            volatile U32 IOCB15 :1;            // GPIO pin 15 clear bit
        } B;
    } SCR; // GPIO set/clear register (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 WPEN0  :1;            // Write protect enable for GPIO pin 0
            volatile U32 WPEN1  :1;            // Write protect enable for GPIO pin 1
            volatile U32 WPEN2  :1;            // Write protect enable for GPIO pin 2
            volatile U32 WPEN3  :1;            // Write protect enable for GPIO pin 3
            volatile U32 WPEN4  :1;            // Write protect enable for GPIO pin 4
            volatile U32 WPEN5  :1;            // Write protect enable for GPIO pin 5
            volatile U32 WPEN6  :1;            // Write protect enable for GPIO pin 6
            volatile U32 WPEN7  :1;            // Write protect enable for GPIO pin 7
            volatile U32 WPEN8  :1;            // Write protect enable for GPIO pin 8
            volatile U32 WPEN9  :1;            // Write protect enable for GPIO pin 9
            volatile U32 WPEN10 :1;            // Write protect enable for GPIO pin 10
            volatile U32 WPEN11 :1;            // Write protect enable for GPIO pin 11
            volatile U32 WPEN12 :1;            // Write protect enable for GPIO pin 12
            volatile U32 WPEN13 :1;            // Write protect enable for GPIO pin 13
            volatile U32 WPEN14 :1;            // Write protect enable for GPIO pin 14
            volatile U32 WPEN15 :1;            // Write protect enable for GPIO pin 15
            volatile U32 WPSEQ  :1;            // Write protect sequence
            volatile U32        :15;
        } B;
    } WPR; // GPIO write protection register (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 MUXL0 :4;             // Multiplexed function select for GPIO pin 0
            volatile U32 MUXL1 :4;             // Multiplexed function select for GPIO pin 1
            volatile U32 MUXL2 :4;             // Multiplexed function select for GPIO pin 2
            volatile U32 MUXL3 :4;             // Multiplexed function select for GPIO pin 3
            volatile U32 MUXL4 :4;             // Multiplexed function select for GPIO pin 4
            volatile U32 MUXL5 :4;             // Multiplexed function select for GPIO pin 5
            volatile U32 MUXL6 :4;             // Multiplexed function select for GPIO pin 6
            volatile U32 MUXL7 :4;             // Multiplexed function select for GPIO pin 7
        } B;
    } MUXL; // GPIO multiplexed function low register (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 MUXH8  :4;            // Multiplexed function select for GPIO pin 8
            volatile U32 MUXH9  :4;            // Multiplexed function select for GPIO pin 9
            volatile U32 MUXH10 :4;            // Multiplexed function select for GPIO pin 10
            volatile U32 MUXH11 :4;            // Multiplexed function select for GPIO pin 11
            volatile U32 MUXH12 :4;            // Multiplexed function select for GPIO pin 12
            volatile U32 MUXH13 :4;            // Multiplexed function select for GPIO pin 13
            volatile U32 MUXH14 :4;            // Multiplexed function select for GPIO pin 14
            volatile U32 MUXH15 :4;            // Multiplexed function select for GPIO pin 15
        } B;
    } MUXH; // GPIO multiplexed function high register (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 IOCB0  :1;            // GPIO pin 0 clear bit
            volatile U32 IOCB1  :1;            // GPIO pin 1 clear bit
            volatile U32 IOCB2  :1;            // GPIO pin 2 clear bit
            volatile U32 IOCB3  :1;            // GPIO pin 3 clear bit
            volatile U32 IOCB4  :1;            // GPIO pin 4 clear bit
            volatile U32 IOCB5  :1;            // GPIO pin 5 clear bit
            volatile U32 IOCB6  :1;            // GPIO pin 6 clear bit
            volatile U32 IOCB7  :1;            // GPIO pin 7 clear bit
            volatile U32 IOCB8  :1;            // GPIO pin 8 clear bit
            volatile U32 IOCB9  :1;            // GPIO pin 9 clear bit
            volatile U32 IOCB10 :1;            // GPIO pin 10 clear bit
            volatile U32 IOCB11 :1;            // GPIO pin 11 clear bit
            volatile U32 IOCB12 :1;            // GPIO pin 12 clear bit
            volatile U32 IOCB13 :1;            // GPIO pin 13 clear bit
            volatile U32 IOCB14 :1;            // GPIO pin 14 clear bit
            volatile U32 IOCB15 :1;            // GPIO pin 15 clear bit
            volatile U32        :16;
        } B;
    } CLR; // GPIO port bit clear register (Offset: 0x28; Reset: 0x0000.0000)

    U32 GPIO_Reserved0[5U];                    // Reserved: 0x002C - 0x003B

    union {
        volatile U32 R;
        struct {
            volatile U32 HDRV0  :1;            // GPIO pin 0 huge sourcing/sinking strength control
            volatile U32 HDRV1  :1;            // GPIO pin 1 huge sourcing/sinking strength control
            volatile U32 HDRV2  :1;            // GPIO pin 2 huge sourcing/sinking strength control
            volatile U32 HDRV3  :1;            // GPIO pin 3 huge sourcing/sinking strength control
            volatile U32 HDRV4  :1;            // GPIO pin 4 huge sourcing/sinking strength control
            volatile U32 HDRV5  :1;            // GPIO pin 5 huge sourcing/sinking strength control
            volatile U32 HDRV6  :1;            // GPIO pin 6 huge sourcing/sinking strength control
            volatile U32 HDRV7  :1;            // GPIO pin 7 huge sourcing/sinking strength control
            volatile U32 HDRV8  :1;            // GPIO pin 8 huge sourcing/sinking strength control
            volatile U32 HDRV9  :1;            // GPIO pin 9 huge sourcing/sinking strength control
            volatile U32 HDRV10 :1;            // GPIO pin 10 huge sourcing/sinking strength control
            volatile U32 HDRV11 :1;            // GPIO pin 11 huge sourcing/sinking strength control
            volatile U32 HDRV12 :1;            // GPIO pin 12 huge sourcing/sinking strength control
            volatile U32 HDRV13 :1;            // GPIO pin 13 huge sourcing/sinking strength control
            volatile U32 HDRV14 :1;            // GPIO pin 14 huge sourcing/sinking strength control
            volatile U32 HDRV15 :1;            // GPIO pin 15 huge sourcing/sinking strength control
            volatile U32        :16;
        } B;
    } HDRV; // GPIO huge current control register (Offset: 0x3C; Reset: 0x0000.0000)

}; // end of GPIO_tag



/******************************************************************************/
/*            Inter-integrated circuit interface (I2C) memory map             */
/******************************************************************************/
struct I2C_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 I2CEN      :1;        // I2C peripheral enable
            volatile U32 TDIEN      :1;        // Data transmit interrupt enable
            volatile U32 RDIEN      :1;        // Data receive interrupt enable
            volatile U32 ADDRIEN    :1;        // Address match interrupt enable
            volatile U32 ACKFAILIEN :1;        // Acknowledge fail interrupt enable
            volatile U32 STOPIEN    :1;        // Stop generation complete interrupt enable
            volatile U32 TDCIEN     :1;        // Data transfer complete interrupt enable
            volatile U32 ERRIEN     :1;        // Error interrupt enable
            volatile U32 DELT       :4;        // Digital filter value
            volatile U32            :2;
            volatile U32 DMATEN     :1;        // DMA Transmit data request enable
            volatile U32 DMAREN     :1;        // DMA receive data request enable
            volatile U32 SCTRL      :1;        // Slave receive data control
            volatile U32 STRETCH    :1;        // Clock stretching mode
            volatile U32            :1;
            volatile U32 GCAEN      :1;        // General call address enable
            volatile U32 HADDREN    :1;        // SMBus host address enable
            volatile U32 DEVADDREN  :1;        // SMBus device default address enable
            volatile U32 SMBALERT   :1;        // SMBus alert enable / pin set
            volatile U32 PECEN      :1;        // PEC calculation enable
            volatile U32            :8;
        } B;
    } CTRL1; // Control register 1 (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SADDR    :10;         // Slave address sent by the master
            volatile U32 DIR      :1;          // Master data transfer direction
            volatile U32 ADDR10   :1;          // Host sends 10-bit address mode enable
            volatile U32 READH10  :1;          // 10-bit address header read enable
            volatile U32 GENSTART :1;          // Generate start condition
            volatile U32 GENSTOP  :1;          // Generate stop condition
            volatile U32 NACKEN   :1;          // Not acknowledge enable
            volatile U32 CNT      :8;          // Transmit data counter
            volatile U32 RLDEN    :1;          // Send data reload mode enable
            volatile U32 ASTOPEN  :1;          // Automatically send stop condition enable
            volatile U32 PECTEN   :1;          // Request PEC transmission enable
            volatile U32          :5;
        } B;
    } CTRL2; // Control register 2 (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ADDR1     :10;        // Own address 2
            volatile U32 ADDR1MODE :1;         // Own address 2-bit mask
            volatile U32           :4;
            volatile U32 ADDR1EN   :1;         // Own address 2 enable
            volatile U32           :16;
        } B;
    } OADDR1; // Address register 1 (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32           :1;
            volatile U32 ADDR2     :7;         // Own address 2
            volatile U32 ADDR2MASK :3;         // Own address 2-bit mask
            volatile U32           :4;
            volatile U32 ADDR2EN   :1;         // Own address 2 enable
            volatile U32           :16;
        } B;
    } OADDR2; // Own address register 2 (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SCLL :8;              // SCL low level
            volatile U32 SCLH :8;              // SCL high level
            volatile U32 SDAD :4;              // SDA output delay
            volatile U32 SCLD :4;              // SCL output delay
            volatile U32 DIVH :4;              // High 4 bits of clock divider value
            volatile U32 DIVL :4;              // Low 4 bits of clock divider value
        } B;
    } CLKCTRL; // Timing register (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TOTIME  :12;          // Clock timeout detection time
            volatile U32 TOMODE  :1;           // Clock timeout detection mode
            volatile U32         :2;
            volatile U32 TOEN    :1;           // Detect clock low/high timeout enable
            volatile U32 EXTTIME :12;          // Cumulative clock low extend timeout value
            volatile U32         :3;
            volatile U32 EXTEN   :1;           // Cumulative clock low extend timeout enable
        } B;
    } TIMEOUT; // Timeout register (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TDBE     :1;          // Transmit data buffer empty flag
            volatile U32 TDIS     :1;          // Transmit data interrupt status
            volatile U32 RDBF     :1;          // Receive data buffer full flag
            volatile U32 ADDRHF   :1;          // 0~7 bit address head match flag
            volatile U32 ACKFAILF :1;          // Acknowledge failure flag
            volatile U32 STOPF    :1;          // Stop condition generation complete flag
            volatile U32 TDC      :1;          // Data transfer complete flag
            volatile U32 TCRLD    :1;          // Data transfer complete, waiting for data load
            volatile U32 BUSERR   :1;          // Bus error flag
            volatile U32 ARLOST   :1;          // Arbitration lost flag
            volatile U32 OUF      :1;          // Overrun or underrun flag
            volatile U32 PECERR   :1;          // PEC receive error flag
            volatile U32 TMOUT    :1;          // SMBus timeout flag
            volatile U32 ALERTF   :1;          // SMBus alert flag
            volatile U32          :1;
            volatile U32 BUSYF    :1;          // Bus busy flag transmission mode
            volatile U32 SDIR     :1;          // Slave data transfer direction
            volatile U32 ADDR     :7;          // Slave address matching value
            volatile U32          :8;
        } B;
    } STS; // Status register (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32          :3;
            volatile U32 ADDRC    :1;          // Clear 0~7 bit address match flag
            volatile U32 ACKFAILC :1;          // Clear acknowledge failure flag
            volatile U32 STOPC    :1;          // Clear stop condition generation complete flag
            volatile U32          :2;
            volatile U32 BUSERRC  :1;          // Clear bus error flag
            volatile U32 ARLOSTC  :1;          // Clear arbitration lost flag
            volatile U32 OUFC     :1;          // Clear overload / underload flag
            volatile U32 PECERRC  :1;          // Clear PEC receive error flag
            volatile U32 TMOUTC   :1;          // Clear SMBus timeout flag
            volatile U32 ALERTC   :1;          // Clear SMBus alert flag
            volatile U32          :18;
        } B;
    } CLR; // Status clear register (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 PECVAL :8;            // PEC value
            volatile U32        :24;
        } B;
    } PEC; // PEC register (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DT :8;                // Receive data register
            volatile U32    :24;
        } B;
    } RXDT; // Receive data register (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DT :8;                // Transmit data register
            volatile U32    :24;
        } B;
    } TXDT; // Transmit data register (Offset: 0x28; Reset: 0x0000.0000)

}; // end of I2C_tag



/******************************************************************************/
/*                        Power control (PWC) memory map                      */
/******************************************************************************/
struct PWC_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 VRSEL  :1;            // LDO state select in deepsleep mode
            volatile U32 LPSEL  :1;            // Low power mode select when Cortex-M4F sleepdeep
            volatile U32 CLSWEF :1;            // Clear SWEF flag
            volatile U32 CLSEF  :1;            // Clear SEF flag
            volatile U32 PVMEN  :1;            // Power voltage monitoring enable
            volatile U32 PVMSEL :3;            // Power voltage monitoring boundary select
            volatile U32 BPWEN  :1;            // Battery powered domain write enable
            volatile U32        :23;
        } B;
    } CTRL; // Control register (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SWEF   :1;            // Standby wake-up event flag
            volatile U32 SEF    :1;            // Standby mode entry flag
            volatile U32 PVMOF  :1;            // Power voltage monitoring output flag
            volatile U32        :5;
            volatile U32 SWPEN1 :1;            // Standby wake-up pin1 enable
            volatile U32 SWPEN2 :1;            // Standby wake-up pin2 enable
            volatile U32        :22;
        } B;
    } CTRLLSTS; // Control/status register (Offset: 0x04; Reset: 0x0000.0000)

    U32 PWC_Reserved0[2U];                     // Reserved :0x0008-0x000F

    union {
        volatile U32 R;
        struct {
            volatile U32 LDOOVSEL :3;          // LDO output voltage select
            volatile U32          :29;
        } B;
    } LDOOV; // LDO output voltage select register (Offset: 0x10; Reset: 0x000X.0X00)

}; // end of PWC_tag



/******************************************************************************/
/*             Quad Serial peripheral interface (QSPI) memory map             */
/******************************************************************************/
struct QSPI_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 SPIADR :32;           // SPI Flash address
        } B;
    } CMD_W0; // Command word 0 (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ADRLEN :3;            // SPI address legnth
            volatile U32        :13;
            volatile U32 DUM2   :8;            // Second dummy state cycle
            volatile U32 INSLEN :2;            // Instruction code length
            volatile U32        :2;
            volatile U32 PEMEN  :1;            // Perfornance enhanced mode enable
            volatile U32        :3;
        } B;
    } CMD_W1; // Command word 1 (Offset: 0x04; Reset: 0x0100.0003)

    union {
        volatile U32 R;
        struct {
            volatile U32 DCNT :32;             // Read/Write data counter
        } B;
    } CMD_W2; // Command word 2 (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32        :1;
            volatile U32 WEN    :1;            // Write data enable
            volatile U32 RSTSEN :1;            // Read SPI status enable
            volatile U32 RSTSC  :1;            // Read SPI status configuration
            volatile U32        :1;
            volatile U32 OPMODE :3;            // SPI Operation mode
            volatile U32        :8;
            volatile U32 PEMOPC :8;            // Performance enhanced mode operation code
            volatile U32 INSC   :8;            // Instruction code
        } B;
    } CMD_W3; // Command word 3 (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CLKDIV   :3;          // Clk divider
            volatile U32          :1;
            volatile U32 SCKMODE  :1;          // Sckout mode
            volatile U32          :2;
            volatile U32 XIPIDLE  :1;          // XIP port idle status
            volatile U32 ABORT    :1;          // Refresh all commands/FIFOs and reset state machine
            volatile U32          :7;
            volatile U32 BUSY     :3;          // Busy bit of SPI status
            volatile U32 XIPRCMDF :1;          // XIP read command flush
            volatile U32 XIPSEL   :1;          // XIP port selection
            volatile U32 KEYEN    :1;          // SPI data encryption key enable
            volatile U32          :10;
        } B;
    } CTRL; // Control register (Offset: 0x10; Reset: 0x0010.0083)

    union {
        volatile U32 R;
        struct {
            volatile U32 CSDLY :4;             // CS delay
            volatile U32       :28;
        } B;
    } ACTR; // AC timing register (Offset: 0x14; Reset: 0x0000.000F)

    union {
        volatile U32 R;
        struct {
            volatile U32 TXFIFORDY :1;         // TxFIFO ready status
            volatile U32 RXFIFORDY :1;         // RxFIFO ready status
            volatile U32           :30;
        } B;
    } FIFOSTS; // FIFO status register (Offset: 0x18; Reset: 0x0000.0001)

    U32 QSPI_Reserved0[1U];                    // Reserved: 0x001C-0x001F

    union {
        volatile U32 R;
        struct {
            volatile U32 DMAEN       :1;       // DMA enable
            volatile U32 CMDIE       :1;       // Command complete Interrupt enable
            volatile U32             :6;
            volatile U32 TXFIFO_THOD :2;       // The trigger value is the data in the TxFIFO
            volatile U32             :2;
            volatile U32 RXFIFO_THOD :2;       // The trigger value is the data in the RxFIFO
            volatile U32             :18;
        } B;
    } CTRL2; // Control register 2 (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CMDSTS :1;            // Command complete status
            volatile U32        :31;
        } B;
    } CMDSTS; // Command status register (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SPISTS :8;            // SPI Read status
            volatile U32        :24;
        } B;
    } RSTS; // Read status register (Offset: 0x28; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SPIFSIZE :32;         // SPI Flash Size
        } B;
    } FSIZE; // Flash size register (Offset: 0x2C; Reset: 0xF000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 XIPR_DUM2   :8;       // XIP Read second dummy cycle
            volatile U32 XIPR_OPMODE :3;       // XIP Read Operation mode
            volatile U32 XIPR_ADRLEN :1;       // XIP Read address length
            volatile U32 INSC        :8;       // XIP Read instruction code
            volatile U32             :12;
        } B;
    } XIP_CMD_W0; // XIP command word 0 (Offset: 0x30; Reset: 0x0000.3000)

    union {
        volatile U32 R;
        struct {
            volatile U32 XIPW_DUM2   :8;       // XIP Write second dummy cycle
            volatile U32 XIPW_OPMODE :3;       // XIP Write operation mode
            volatile U32 XIPW_ADRLEN :1;       // XIP Write address length
            volatile U32 XIPW_INSC   :8;       // XIP Write instruction code
            volatile U32             :12;
        } B;
    } XIP_CMD_W1; // XIP command word 1 (Offset: 0x34; Reset: 0x0000.2000)

    union {
        volatile U32 R;
        struct {
            volatile U32 XIPR_DCNT :6;         // This indicates the time counter that is used to judge the maximum data count in mode D
            volatile U32           :2;
            volatile U32 XIPR_TCNT :7;         // This indicates the time counter that is used to judge time interval in mode T
            volatile U32 XIPR_SEL  :1;         // XIP read mode select
            volatile U32 XIPW_DCNT :6;         // This indicates the time counter that is used to judge the maximum data count in mode D
            volatile U32           :2;
            volatile U32 XIPW_TCNT :7;         // This indicates the time counter that is used to judge time interval in mode T
            volatile U32 XIPW_SEL  :1;         // XIP write mode select
        } B;
    } XIP_CMD_W2; // XIP command word 2 (Offset: 0x38; Reset: 0x0F01.0F01)

    union {
        volatile U32 R;
        struct {
            volatile U32 BYPASSC :1;           // Bypass Cache Function
            volatile U32         :2;
            volatile U32 CSTS    :1;           // Cache Status
            volatile U32         :28;
        } B;
    } XIP_CMD_W3; // XIP command word 3 (Offset: 0x3C; Reset: 0x0000.0000)

    U32 QSPI_Reserved1[4U];                    // Reserved: 0x0040-0x004F

    union {
        volatile U32 R;
        struct {
            volatile U32 REV :32;              // Indicates IP version
        } B;
    } REV; // Revision register (Offset: 0x50; Reset: 0x0001.0500)

    U32 QSPI_Reserved2[43U];                   // Reserved: 0x0054-0x00FF

    union {
        volatile U8  R8;                       // 8-bit width data access
        volatile U16 R16;                      // 16-bit width data access
        volatile U32 R;
        struct {
            volatile U32 DT :32;               // Data port register
        } B;
        struct {
            volatile U32 DT :8;               // Data port register
            volatile U32    :24;
        } B8;
        struct {
            volatile U32 DT :16;               // Data port register
            volatile U32    :16;               // Data port register
        } B16;
    } DT; // Data port register (Offset: 0x100; Reset: 0x0000.0000)

}; // end of QSPI_tag



/******************************************************************************/
/*             System configuration controller (SCFG) memory map              */
/******************************************************************************/
struct SCFG_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 MEM_MAP_SEL :3;       // Memory address mapping selection
            volatile U32             :2;
            volatile U32 IR_POL      :1;       // Infrared output polarity selection
            volatile U32 IR_SRC_SEL  :2;       // Infrared modulation envelope signal source selection
            volatile U32             :2;
            volatile U32 SWAP_XMC    :2;       // XMC address mapping swap
            volatile U32             :20;
        } B;
    } CFG1; // Configuration register 1 (Offset: 0x00; Reset: 0x0000.000X)

    union {
        volatile U32 R;
        struct {
            volatile U32              :23;
            volatile U32 MII_RMII_SEL :1;      // MII or RMII selection
            volatile U32              :8;
        } B;
    } CFG2; // Configuration register 2 (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 EXINT0 :4;            // EXINT0 input source configuration
            volatile U32 EXINT1 :4;            // EXINT1 input source configuration
            volatile U32 EXINT2 :4;            // EXINT2 input source configuration
            volatile U32 EXINT3 :4;            // EXINT3 input source configuration
            volatile U32        :16;
        } B;
    } EXINTC1; // External interrupt configuration register 1 (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 EXINT4 :4;            // EXINT4 input source configuration
            volatile U32 EXINT5 :4;            // EXINT5 input source configuration
            volatile U32 EXINT6 :4;            // EXINT6 input source configuration
            volatile U32 EXINT7 :4;            // EXINT7 input source configuration
            volatile U32        :16;
        } B;
    } EXINTC2; // External interrupt configuration register 2 (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 EXINT8  :4;           // EXINT8 input source configuration
            volatile U32 EXINT9  :4;           // EXINT9 input source configuration
            volatile U32 EXINT10 :4;           // EXINT10 input source configuration
            volatile U32 EXINT11 :4;           // EXINT11 input source configuration
            volatile U32         :16;
        } B;
    } EXINTC3; // External interrupt configuration register 3 (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 EXINT12 :4;           // EXINT12 input source configuration
            volatile U32 EXINT13 :4;           // EXINT13 input source configuration
            volatile U32 EXINT14 :4;           // EXINT14 input source configuration
            volatile U32 EXINT15 :4;           // EXINT15 input source configuration
            volatile U32         :16;
        } B;
    } EXINTC4; // External interrupt configuration register 4 (Offset: 0x14; Reset: 0x0000.0000)

    U32 SCFG_Reserved0[5U];                    // Reserved: 0x0018-0x002B

    union {
        volatile U32 R;
        struct {
            volatile U32 PB3_UH  :1;           // PB3 Ultra high sourcing/sinking strength
            volatile U32 PB9_UH  :1;           // PB9 Ultra high sourcing/sinking strength
            volatile U32 PB10_UH :1;           // PB10 Ultra high sourcing/sinking strength
            volatile U32         :1;
            volatile U32 PB12_UH :1;           // PB12 Ultra high sourcing/sinking strength
            volatile U32 PB13_UH :1;           // PB13 Ultra high sourcing/sinking strength
            volatile U32 PB14_UH :1;           // PB14 Ultra high sourcing/sinking strength
            volatile U32 PB15_UH :1;           // PB15 Ultra high sourcing/sinking strength
            volatile U32 PF14_UH :1;           // PF14 Ultra high sourcing/sinking strength
            volatile U32 PF15_UH :1;           // PF15 Ultra high sourcing/sinking strength
            volatile U32         :22;
        } B;
    } UHDRV; // Ultra high sourcing/sinking strength (Offset: 0x2C; Reset: 0x0000.0000)

}; // end of SCFG_tag



/******************************************************************************/
/*                Serial peripheral interface (SPI) memory map                */
/******************************************************************************/
struct SPI_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 CLKPHA :1;            // Clock phase
            volatile U32 CLKPOL :1;            // Clock polarity
            volatile U32 MSTEN  :1;            // Master enable
            volatile U32 MDIV   :3;            // Master clock frequency division
            volatile U32 SPIEN  :1;            // SPI enable
            volatile U32 LTF    :1;            // LSB transmit first
            volatile U32 SWCSIL :1;            // Software CS internal level
            volatile U32 SWCSEN :1;            // Software CS enable
            volatile U32 ORA    :1;            // Receive-only active
            volatile U32 FBN    :1;            // Frame bit num
            volatile U32 NTC    :1;            // Transmit CRC next
            volatile U32 CCEN   :1;            // RC calculation enable
            volatile U32 SLBTD  :1;            // Single line bidirectional half-duplex transmission direction
            volatile U32 SLBEN  :1;            // Single line bidirectional half-duplex enable
            volatile U32        :16;
        } B;
    } CTRL1; // Control register 1 (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DMAREN  :1;           // DMA receive enable
            volatile U32 DMATEN  :1;           // DMA transmit enable
            volatile U32 HWCSOE  :1;           // Hardware CS output enable
            volatile U32         :1;
            volatile U32 TIEN    :1;           // TI mode enable
            volatile U32 ERRIE   :1;           // Error interrupt enable
            volatile U32 RDBFIE  :1;           // Receive data buffer full interrupt enable
            volatile U32 TDBEIE  :1;           // Transmit data buffer empty interrupt enable
            volatile U32 MDIV3   :1;           // Master clock frequency division
            volatile U32 MDIV3EN :1;           // Master clock frequency divided by 3 enable
            volatile U32         :22;
        } B;
    } CTRL2; // Control register 2 (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RDBF  :1;             // Receive data buffer full
            volatile U32 TDBE  :1;             // Transmit data buffer empty
            volatile U32 ACS   :1;             // Audio channel state
            volatile U32 TUERR :1;             // Transmitter underload error
            volatile U32 CCERR :1;             // CRC error
            volatile U32 MMERR :1;             // Master mode error
            volatile U32 ROERR :1;             // Receiver overflow error
            volatile U32 BF    :1;             // Busy flag
            volatile U32 CSPAS :1;             // CS pulse abnormal setting flag
            volatile U32       :23;
        } B;
    } STS; // Status register (Offset: 0x08; Reset: 0x0000.0002)

    union {
        volatile U32 R;
        struct {
            volatile U32 DT :16;               // Data value
            volatile U32    :16;
        } B;
    } DT; // Data register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CPOLY :16;            // CRC polynomial
            volatile U32       :16;
        } B;
    } CPOLY; // CRC polynomial register (Offset: 0x10; Reset: 0x0000.0007)

    union {
        volatile U32 R;
        struct {
            volatile U32 RCRC :16;             // Receive CRC
            volatile U32      :16;
        } B;
    } RCRC; // Receive CRC register (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TCRC :16;             // Transmit CRC
            volatile U32      :16;
        } B;
    } TCRC; // Transmit CRC register (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 I2SSCBN   :1;         // I2S channel bit num
            volatile U32 I2SDBN    :2;         // I2S data bit num
            volatile U32 I2SCLKPOL :1;         // I2S clock polarity
            volatile U32 STDSEL    :2;         // I2S standard select
            volatile U32           :1;
            volatile U32 PCMFSSEL  :1;         // PCM frame synchronization
            volatile U32 OPERSEL   :2;         // I2S operation mode select
            volatile U32 I2SEN     :1;         // I2S enable
            volatile U32 I2SMSEL   :1;         // I2S mode select
            volatile U32           :20;
        } B;
    } I2SCTRL; // I2S configuration register (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 I2SDIV    :8;         // I2S division
            volatile U32 I2SODD    :1;         // Odd factor for I2S division
            volatile U32 I2SMCLKOE :1;         // I2S Master clock output enable
            volatile U32           :22;
        } B;
    } I2SCLKP; // I2S prescaler register (Offset: 0x20; Reset: 0x0000.0002)

}; // end of SPI_tag



/******************************************************************************/
/*                           Timers (TMR) memory map                          */
/******************************************************************************/
struct TMR_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 TMREN   :1;           // TMR enable
            volatile U32 OVFEN   :1;           // Overflow event enable
            volatile U32 OVFS    :1;           // Overflow event source
            volatile U32 OCMEN   :1;           // One cycle mode enable
            volatile U32 OWCDIR  :1;           // One-way count direction
            volatile U32 TWCMSEL :2;           // Two-way counting mode selection
            volatile U32 PRBEN   :1;           // Period buffer enable
            volatile U32 CLKDIV  :2;           // Clock division
            volatile U32 PMEN    :1;           // Plus Mode Enable
            volatile U32         :21;
        } B;
    } CTRL1; // TMRx control register 1 (Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 CBCTRL    :1;         // Channel buffer control
            volatile U32           :1;
            volatile U32 CCFS      :1;         // Channel control bit flash selection
            volatile U32 DRS       :1;         // DMA request source
            volatile U32 PTOS      :3;         // Master TMR output selection
            volatile U32 C1INSEL   :1;         // C1IN selection
            volatile U32 C1IOS     :1;         // Channel 1 idle output state
            volatile U32 C1CIOS    :1;         // Channel 1 complementary idle output state
            volatile U32 C2IOS     :1;         // Channel 2 idle output state
            volatile U32 C2CIOS    :1;         // Channel 2 complementary idle output state
            volatile U32 C3IOS     :1;         // Channel 3 idle output state
            volatile U32 C3CIOS    :1;         // Channel 3 complementary idle output state
            volatile U32 C4IOS     :1;         // Channel 4 idle output state
            volatile U32           :16;
            volatile U32 TRGOUT2EN :1;         // TRGOUT2 enable
        } B;
    } CTRL2; // TMRx control register 2 (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SMSEL  :3;            // Subordinate TMR mode selection
            volatile U32        :1;
            volatile U32 STIS   :3;            // Subordinate TMR input selection
            volatile U32 STS    :1;            // Subordinate TMR synchronization
            volatile U32 ESF    :4;            // External signal filter
            volatile U32 ESDIV  :2;            // External signal divide
            volatile U32 ECMBEN :1;            // External clock mode B enable
            volatile U32 ESP    :1;            // External signal polarity
            volatile U32        :16;
        } B;
    } STCTRL; // TMRx slave timer control register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 OVFIEN  :1;           // Overflow interrupt enable
            volatile U32 C1IEN   :1;           // Channel 1 interrupt enable
            volatile U32 C2IEN   :1;           // Channel 2 interrupt enable
            volatile U32 C3IEN   :1;           // Channel 3 interrupt enable
            volatile U32 C4IEN   :1;           // Channel 4 interrupt enable
            volatile U32 HALLIEN :1;           // HALL interrupt enable
            volatile U32 TIEN    :1;           // Trigger interrupt enable
            volatile U32 BRKIE   :1;           // Break interrupt enable
            volatile U32 OVFDEN  :1;           // Overflow event DMA request enable
            volatile U32 C1DEN   :1;           // Channel 1 DMA request enable
            volatile U32 C2DEN   :1;           // Channel 2 DMA request enable
            volatile U32 C3DEN   :1;           // Channel 3 DMA request enable
            volatile U32 C4DEN   :1;           // Channel 4 DMA request enable
            volatile U32 HALLDE  :1;           // HALL DMA request enable
            volatile U32 TDEN    :1;           // Trigger DMA request enable
            volatile U32         :17;
        } B;
    } IDEN; // TMRx DMA/Interrupt enable register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 OVFIF  :1;            // Overflow interrupt flag
            volatile U32 C1IF   :1;            // Channel 1 interrupt flag
            volatile U32 C2IF   :1;            // Channel 2 interrupt flag
            volatile U32 C3IF   :1;            // Channel 3 interrupt flag
            volatile U32 C4IF   :1;            // Channel 4 interrupt flag
            volatile U32 HALLIF :1;            // HALL interrupt flag
            volatile U32 TRGIF  :1;            // Trigger interrupt flag
            volatile U32 BRKIF  :1;            // Break interrupt flag
            volatile U32        :1;
            volatile U32 C1RF   :1;            // Channel 1 recapture flag
            volatile U32 C2RF   :1;            // Channel 2 recapture flag
            volatile U32 C3RF   :1;            // Channel 3 recapture flag
            volatile U32 C4RF   :1;            // Channel 4 recapture flag
            volatile U32        :19;
        } B;
    } ISTS; // TMRx interrupt status register (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 OVFSWTR  :1;          // Overflow event triggered by software
            volatile U32 C1SWTR   :1;          // Channel 1 event triggered by software
            volatile U32 C2SWTR   :1;          // Channel 2 event triggered by software
            volatile U32 C3SWTR   :1;          // Channel 3 event triggered by software
            volatile U32 C4SWTR   :1;          // Channel 4 event triggered by software
            volatile U32 HALLSWTR :1;          // HALL event triggered by software
            volatile U32 TRGSWTR  :1;          // Trigger event triggered by software
            volatile U32 BRKSWTR  :1;          // Break event triggered by software
            volatile U32          :24;
        } B;
    } SWEVT; // TMRx software event register (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        union {
            struct {
                volatile U32 C1C     :2;         // Channel 1 configuration
                volatile U32 C1OIEN  :1;         // Channel 1 output enable immediately
                volatile U32 C1OBEN  :1;         // Channel 1 output buffer enable
                volatile U32 C1OCTRL :3;         // Channel 1 output control
                volatile U32 C1OSEN  :1;         // Channel 1 output switch enable
                volatile U32 C2C     :2;         // Channel 2 configuration
                volatile U32 C2OIEN  :1;         // Channel 2 output enable immediately
                volatile U32 C2OBEN  :1;         // Channel 2 output buffer enable
                volatile U32 C2OCTRL :3;         // Channel 2 output control
                volatile U32 C2OSEN  :1;         // Channel 2 output switch enable
                volatile U32         :16;
            } B;
        } COMPARE;
        union {
            struct {
                volatile U32 C1C    :2;        // Channel 1 configuration
                volatile U32 C1IDIV :2;        // Channel 1 input divider
                volatile U32 C1DF   :4;        // Channel 1 digital filter
                volatile U32 C2C    :2;        // Channel 2 configuration
                volatile U32 C2IDIV :2;        // Channel 2 input divider
                volatile U32 C2DF   :4;        // Channel 2 digital filter
                volatile U32        :16;
            } B;
        } CAPTURE;
    } CM1; // TMRx channel mode register 1 (Offset: 0x18; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        union {
            struct {
                volatile U32 C3C     :2;       // Channel 3 configuration
                volatile U32 C3OIEN  :1;       // Channel 3 output enable immediately
                volatile U32 C3OBEN  :1;       // Channel 3 output buffer enable
                volatile U32 C3OCTRL :3;       // Channel 3 output control
                volatile U32 C3OSEN  :1;       // Channel 3 output switch enable
                volatile U32 C4C     :2;       // Channel 4 configuration
                volatile U32 C4OIEN  :1;       // Channel 4 output enable immediately
                volatile U32 C4OBEN  :1;       // Channel 4 output buffer enable
                volatile U32 C4OCTRL :3;       // Channel 4 output control
                volatile U32 C4OSEN  :1;       // Channel 4 output switch enable
                volatile U32         :16;
            } B;
        } COMPARE;
        union {
            struct {
                volatile U32 C3C    :2;        // Channel 3 configuration
                volatile U32 C3IDIV :2;        // Channel 3 input divider
                volatile U32 C3DF   :4;        // Channel 3 digital filter
                volatile U32 C4C    :2;        // Channel 4 configuration
                volatile U32 C4IDIV :2;        // Channel 4 input divider
                volatile U32 C4DF   :4;        // Channel 4 digital filter
                volatile U32        :16;
            } B;
        } CAPTURE;
    } CM2; // TMRx channel mode register 2 (Offset: 0x1C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 C1EN  :1;             // Channel 1 enable
            volatile U32 C1P   :1;             // Channel 1 polarity
            volatile U32 C1CEN :1;             // Channel 1 complementary enable
            volatile U32 C1CP  :1;             // Channel 1 complementary polarity
            volatile U32 C2EN  :1;             // Channel 2 enable
            volatile U32 C2P   :1;             // Channel 2 polarity
            volatile U32 C2CEN :1;             // Channel 2 complementary enable
            volatile U32 C2CP  :1;             // Channel 2 complementary polarity
            volatile U32 C3EN  :1;             // Channel 3 enable
            volatile U32 C3P   :1;             // Channel 3 polarity
            volatile U32 C3CEN :1;             // Channel 3 complementary enable
            volatile U32 C3CP  :1;             // Channel 3 complementary polarity
            volatile U32 C4EN  :1;             // Channel 4 enable
            volatile U32 C4P   :1;             // Channel 4 polarity
            volatile U32       :18;
        } B;
    } CCTRL; // TMRx channel control register (Offset: 0x20; Reset: 0x0000.0000)

    union {
        volatile U32 CVAL32;
        struct {
            volatile U32 CVAL16 :16;           // Counter value
            volatile U32        :16;
        } B;
    } CVAL; // TMRx counter value (Offset: 0x24; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DIV :16;              // Divider value
            volatile U32     :16;
        } B;
    } DIV; // TMRx division value (Offset: 0x28; Reset: 0x0000.0000)

    union {
        volatile U32 PR32;
        struct {
            volatile U32 PR16 :16;             // Period value
            volatile U32      :16;
        } B;
    } PR; // TMRx period register (Offset: 0x2C; Reset: 0xFFFF.FFFF)

    union {
        volatile U32 R;
        struct {
            volatile U32 RPR :16;              // Repetition of period value
            volatile U32     :16;
        } B;
    } RPR; // TMRx repetition counter register (Offset: 0x30; Reset: 0x0000.0000)

    union {
        volatile U32 CDT32;
        struct {
            volatile U32 CDT16 :16;            // Channel x data register
            volatile U32       :16;
        } B;
    } CDT[4]; // TMRx channel 1-4 data register (Offset: 0x34-0x40; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DTC     :8;           // Dead-time configuration
            volatile U32 WPC     :2;           // Write protection configuration
            volatile U32 FCSODIS :1;           // Frozen channel status when holistic output disable
            volatile U32 FCSOEN  :1;           // Frozen channel status when holistic output enable
            volatile U32 BRKEN   :1;           // Break enable
            volatile U32 BRKV    :1;           // Break input validity
            volatile U32 AOEN    :1;           // Automatic output enable
            volatile U32 OEN     :1;           // Output enable
            volatile U32         :16;
        } B;
    } BRK; // TMRx break register (Offset: 0x44; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ADDR :5;              // DMA transfer address offset
            volatile U32      :3;
            volatile U32 DTB  :5;              // DMA transfer bytes
            volatile U32      :19;
        } B;
    } DMACTRL; // TMRx DMA control register (Offset: 0x48; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DMADT :16;            // DMA data register
            volatile U32       :16;
        } B;
    } DMADT; // TMRx DMA data register (Offset: 0x4C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32               :6;
            volatile U32 TMR5_CH4_IRMP :2;     // TMR5 channel 4 input remap
            volatile U32               :2;
            volatile U32 TMR2_IS1_IRMP :2;     // TMR2 IS1 input remap
            volatile U32               :20;
        } B;
    } RMP; // Only TMR2, TMR5 channel input remapping register (Offset: 0x50; Reset: 0x0000.0000)

    U32 TMR_Reserved0[7U];                     // Reserved: 0x0054 - 0x006F

    union {
        volatile U32 R;
        struct {
            volatile U32         :2;
            volatile U32 C5OIEN  :1;           // Channel 5 output immediately enable
            volatile U32 C5OBEN  :1;           // Channel 5 output buffer enable
            volatile U32 C5OCTRL :3;           // Channel 5 output control
            volatile U32 C5OSEN  :1;           // Channel 5 output switch enable
            volatile U32         :24;
        } B;
    } CM3; // TMRx channel mode register 3 (Offset: 0x70; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 C5DT :16;             // Channel 5 data register
            volatile U32      :16;
        } B;
    } C5DT; // TMRx channel 5 data register (Offset: 0x74; Reset: 0x0000.0000)

}; // end of TMR_tag



/******************************************************************************/
/* Universal synchronous/asynchronous receiver transmitter (USART) memory map */
/******************************************************************************/
struct USART_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 PERR  :1;             // Parity error
            volatile U32 FERR  :1;             // Framing error
            volatile U32 NERR  :1;             // Noise error
            volatile U32 ROEER :1;             // Receiver overflow error
            volatile U32 IDLEF :1;             // IDLE flag
            volatile U32 RDBF  :1;             // Receive data buffer full
            volatile U32 TDC   :1;             // Transmit data complete
            volatile U32 TDBE  :1;             // Transmit data buffer empty
            volatile U32 BFF   :1;             // Break frame flag
            volatile U32 CTSCF :1;             // CTS change flag
            volatile U32       :22;
        } B;
    } STS; // Status register (Offset: 0x00; Reset: 0x0000.00C0)

    union {
        volatile U32 R;
        struct {
            volatile U32 DT :9;                // Data value
            volatile U32    :23;
        } B;
    } DT; // Data register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DIV :16;              // Divider
            volatile U32     :16;
        } B;
    } BAUDR; // Baud rate register (Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 SBF     :1;           // Send break frame
            volatile U32 RM      :1;           // Receiver mute
            volatile U32 REN     :1;           // Receiver enable
            volatile U32 TEN     :1;           // Transmitter enable
            volatile U32 IDLEIEN :1;           // IDLE interrupt enable
            volatile U32 RDBFIEN :1;           // RDBF interrupt enable
            volatile U32 TDCIEN  :1;           // TDC interrupt enable
            volatile U32 TDBEIEN :1;           // TDBE interrupt enable
            volatile U32 PERRIEN :1;           // PERR interrupt enable
            volatile U32 PSEL    :1;           // Parity selection
            volatile U32 PEN     :1;           // Parity enable
            volatile U32 WUM     :1;           // Wakeup mode
            volatile U32 DBN0    :1;           // Data bit num
            volatile U32 UEN     :1;           // USART enable
            volatile U32         :2;
            volatile U32 TCDT    :5;           // Transmit complete delay time
            volatile U32 TSDT    :5;           // Transmit start delay time)
            volatile U32         :2;
            volatile U32 DBN1    :1;           // Data bit num
            volatile U32         :3;
        } B;
    } CTRL1; // Control register 1 (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 IDH     :4;           // USART identification high bits
            volatile U32 IDBN    :1;           // Identification bit num
            volatile U32 BFBN    :1;           // Break frame bit num
            volatile U32 BFIEN   :1;           // Break frame interrupt enable
            volatile U32         :1;
            volatile U32 LBCP    :1;           // Last bit clock pulse
            volatile U32 CLKPHA  :1;           // Clock phase
            volatile U32 CLKPOL  :1;           // Clock polarity
            volatile U32 CLKEN   :1;           // Clock enable
            volatile U32 STOPBN  :2;           // STOP bit num
            volatile U32 LINEN   :1;           // LIN mode enable
            volatile U32 TRPSWAP :1;           // Transmit/receive pin swap
            volatile U32         :12;
            volatile U32 IDL     :4;           // USART identification lower bits
        } B;
    } CTRL2; // Control register 2 (Offset: 0x10; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ERRIEN   :1;          // Error interrupt enable
            volatile U32 IRDAEN   :1;          // IrDA enable
            volatile U32 IRDALP   :1;          // IrDA low-power mode
            volatile U32 SLBEN    :1;          // Single-wire bidirectional half-duplex enable
            volatile U32 SCNACKEN :1;          // Smartcard NACK enable
            volatile U32 SCMEN    :1;          // Smartcard mode enable
            volatile U32 DMAREN   :1;          // DMA receiver enable
            volatile U32 DMATEN   :1;          // DMA transmitter enable
            volatile U32 RTSEN    :1;          // RTS enable
            volatile U32 CTSEN    :1;          // CTS enable
            volatile U32 CTSCFIEN :1;          // CTSCF interrupt enable
            volatile U32          :3;
            volatile U32 RS485EN  :1;          // RS485 enable
            volatile U32 DEP      :1;          // DE polarity selection
            volatile U32          :16;
        } B;
    } CTRL3; // Control register 3 (Offset: 0x14; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 ISDIV :8;             // Prescaler value for dividing the system clock
            volatile U32 SCGT  :8;             // Guard time value in smartcard mode
            volatile U32       :16;
        } B;
    } GDIV; // Guard time and divider register (Offset: 0x18; Reset: 0x0000.0000)

}; // end of USART_tag



/******************************************************************************/
/*                       Watchdog timer (WDT) memory map                      */
/******************************************************************************/
struct WDT_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 CMD :16;              // Command register
            volatile U32     :16;
        } B;
    } CMD; // Command register ( Offset: 0x00; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 DIV :3;               // Clock division value
            volatile U32     :29;
        } B;
    } DIV; // Divider register (Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 RLD :12;              // Reload values
            volatile U32     :20;
        } B;
    } RLD; // Reload register (Offset: 0x08; Reset: 0x0000.0FFF)

    union {
        volatile U32 R;
        struct {
            volatile U32 DIVF :1;              // Division value update complete flag
            volatile U32 RLDF :1;              // Reload value update complete flag
            volatile U32      :30;
        } B;
    } STS; // Status register (Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 WIN :12;              // Window value
            volatile U32     :20;
        } B;
    } WIN; // Status register (Offset: 0x10; Reset: 0x0000.0FFF)

}; // end of WDT_tag



/******************************************************************************/
/*                  Window watchdog timer (WWDT) memory map                   */
/******************************************************************************/
struct WWDT_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 CNT    :7;            // Downcounter
            volatile U32 WWDTEN :1;            // Window watchdog enable
            volatile U32        :24;
        } B;
    } CTRL; // Control register ( Offset: 0x00; Reset: 0x0000.007F)

    union {
        volatile U32 R;
        struct {
            volatile U32 WIN    :7;            // Window value
            volatile U32 DIV    :2;            // Clock division value
            volatile U32 RLDIEN :1;            // Reload counter interrupt
            volatile U32        :22;
        } B;
    } CFG; // Configuration register (Offset: 0x04; Reset: 0x0000.007F)

    union {
        volatile U32 R;
        struct {
            volatile U32 RLDF :1;              // Reload counter interrupt flag
            volatile U32      :31;
        } B;
    } STS; // Status register (Offset: 0x08; Reset: 0x0000.0000)

}; // end of WWDT_tag



/******************************************************************************/
/*                  Debug configuration (DEBUG) memory map                    */
/******************************************************************************/
struct DEBUG_tag {
    union {
        volatile U32 R;
        struct {
            volatile U32 PID  :32;              // MCU’s revision code
        } B;
    } IDCODE; // DEBUG device ID ( Offset: 0x00; Reset: 0xXXXX.XXXX)

    union {
        volatile U32 R;
        struct {
            volatile U32 SLEEP_DEBUG        :1;           // Sleep mode control bit
            volatile U32 DEEPSLEEP_DEBUG    :1;           // Deepsleep mode control bit
            volatile U32 STANDBY_DEBUG      :1;           // Standby mode control bit
            volatile U32                    :29;          // reserved
        } B;
    } CTRL; // DEBUG control register ( Offset: 0x04; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR2_PAUSE         :1;           // TMR2 pause control bit
            volatile U32 TMR3_PAUSE         :1;           // TMR3 pause control bit
            volatile U32 TMR4_PAUSE         :1;           // TMR4 pause control bit
            volatile U32 TMR5_PAUSE         :1;           // TMR5 pause control bit
            volatile U32 TMR6_PAUSE         :1;           // TMR6 pause control bit
            volatile U32 TMR7_PAUSE         :1;           // TMR7 pause control bit
            volatile U32 TMR12_PAUSE        :1;           // TMR12 pause control bit
            volatile U32 TMR13_PAUSE        :1;           // TMR13 pause control bit
            volatile U32 TMR14_PAUSE        :1;           // TMR14 pause control bit
            volatile U32                    :1;
            volatile U32 ERTC_PAUSE         :1;           // ERTC pause control bit
            volatile U32 WWDT_PAUSE         :1;           // WWDT pause control bit
            volatile U32 WDT_PAUSE          :1;           // WDT pause control bit
            volatile U32                    :2;
            volatile U32 ERTC_512_PAUSE     :1;           // ERTC 512Hz output clock pause control bit
            volatile U32                    :8;
            volatile U32 I2C1_SMBUS_TIMEOUT :1;           // I2C1 pause control bit
            volatile U32 CAN1_PAUSE         :1;           // CAN1 pause control bit
            volatile U32 CAN2_PAUSE         :1;           // CAN2 pause control bit
            volatile U32 I2C2_SMBUS_TIMEOUT :1;           // I2C2 pause control bit
            volatile U32 I2C3_SMBUS_TIMEOUT :1;           // I2C3 pause control bit
            volatile U32                    :3;
        } B;
    } APB1_PAUSE; // DEBUG APB1 pause register ( Offset: 0x08; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 TMR1_PAUSE         :1;           // TMR1 pause control bit
            volatile U32 TMR8_PAUSE         :1;           // TMR8 pause control bit
            volatile U32                    :4;
            volatile U32 TMR20_PAUSE        :1;           // TMR20 pause control bit
            volatile U32                    :9;
            volatile U32 TMR9_PAUSE         :1;           // TMR9 pause control bit
            volatile U32 TMR10_PAUSE        :1;           // TMR10 pause control bit
            volatile U32 TMR11_PAUSE        :1;           // TMR11 pause control bit
            volatile U32                    :13;
        } B;
    } APB2_PAUSE; // DEBUG APB2 pause register ( Offset: 0x0C; Reset: 0x0000.0000)

    union {
        volatile U32 R;
        struct {
            volatile U32 REV_ID             :3;           // Revision code
            volatile U32                    :5;
            volatile U32 SER_ID             :8;           // MCU part number ID
            volatile U32                    :16;
        } B;
    } SER_ID; // MCU SERIES ID register ( Offset: 0x20; Reset: 0x0000.XX0X)

}; // end of DEBUG_tag



// ADC
#define ADC1                 (*(volatile struct ADC_tag *)           0x40012000UL)
#define ADC2                 (*(volatile struct ADC_tag *)           0x40012100UL)
#define ADC3                 (*(volatile struct ADC_tag *)           0x40012200UL)
#define ADC_COM              (*(volatile struct ADC_COM_tag *)       0x40012300UL)

// CAN
#define CAN1                 (*(volatile struct CAN_tag *)           0x40006400UL)
#define CAN2                 (*(volatile struct CAN_tag *)           0x40006800UL)

// CRC
#define CRC                  (*(volatile struct CRC_tag *)           0x40023000UL)

// CRM
#define CRM                  (*(volatile struct CRM_tag *)           0x40023800UL)

// DAC
#define DAC                  (*(volatile struct DAC_tag *)           0x40007400UL)

// DMA
#define DMA1                 (*(volatile struct DMA_tag *)           0x40026400UL)
#define DMA2                 (*(volatile struct DMA_tag *)           0x40026600UL)

// ERTC
#define ERTC                 (*(volatile struct ERTC_tag *)          0x40002800UL)

// EXINT
#define EXINT                (*(volatile struct EXINT_tag *)         0x40013C00UL)

// FLASH
#define FLASH                (*(volatile struct FLASH_tag *)         0x40023C00UL)

// GPIO
#define GPIOA                (*(volatile struct GPIO_tag *)          0x40020000UL)
#define GPIOB                (*(volatile struct GPIO_tag *)          0x40020400UL)
#define GPIOC                (*(volatile struct GPIO_tag *)          0x40020800UL)
#define GPIOD                (*(volatile struct GPIO_tag *)          0x40020C00UL)
#define GPIOE                (*(volatile struct GPIO_tag *)          0x40021000UL)
#define GPIOF                (*(volatile struct GPIO_tag *)          0x40021400UL)
#define GPIOG                (*(volatile struct GPIO_tag *)          0x40021800UL)
#define GPIOH                (*(volatile struct GPIO_tag *)          0x40021C00UL)

// I2C
#define I2C1                 (*(volatile struct I2C_tag *)           0x40005400UL)
#define I2C2                 (*(volatile struct I2C_tag *)           0x40005800UL)
#define I2C3                 (*(volatile struct I2C_tag *)           0x40005C00UL)

// PWC
#define PWC                  (*(volatile struct PWC_tag *)           0x40007000UL)

// QSPI
#define QSPI1                (*(volatile struct QSPI_tag *)          0xA0001000UL)
#define QSPI2                (*(volatile struct QSPI_tag *)          0xA0002000UL)

// SCFG
#define SCFG                 (*(volatile struct SCFG_tag *)          0x40013800UL)

// SPI
#define SPI1                 (*(volatile struct SPI_tag *)           0x40013000UL)
#define SPI2                 (*(volatile struct SPI_tag *)           0x40003800UL)
#define SPI3                 (*(volatile struct SPI_tag *)           0x40003C00UL)
#define SPI4                 (*(volatile struct SPI_tag *)           0x40013400UL)

// TIMERS
#define TMR1                 (*(volatile struct TMR_tag *)           0x40010000UL)
#define TMR2                 (*(volatile struct TMR_tag *)           0x40000000UL)
#define TMR3                 (*(volatile struct TMR_tag *)           0x40000400UL)
#define TMR4                 (*(volatile struct TMR_tag *)           0x40000800UL)
#define TMR5                 (*(volatile struct TMR_tag *)           0x40000C00UL)
#define TMR6                 (*(volatile struct TMR_tag *)           0x40001000UL)
#define TMR7                 (*(volatile struct TMR_tag *)           0x40001400UL)
#define TMR8                 (*(volatile struct TMR_tag *)           0x40010400UL)
#define TMR9                 (*(volatile struct TMR_tag *)           0x40014000UL)
#define TMR10                (*(volatile struct TMR_tag *)           0x40014400UL)
#define TMR11                (*(volatile struct TMR_tag *)           0x40014800UL)
#define TMR12                (*(volatile struct TMR_tag *)           0x40001800UL)
#define TMR13                (*(volatile struct TMR_tag *)           0x40001C00UL)
#define TMR14                (*(volatile struct TMR_tag *)           0x40002000UL)
#define TMR20                (*(volatile struct TMR_tag *)           0x40014C00UL)

// USART
#define USART1               (*(volatile struct USART_tag *)         0x40011000UL)
#define USART2               (*(volatile struct USART_tag *)         0x40004400UL)
#define USART3               (*(volatile struct USART_tag *)         0x40004800UL)
#define USART4               (*(volatile struct USART_tag *)         0x40004C00UL)
#define USART5               (*(volatile struct USART_tag *)         0x40005000UL)
#define USART6               (*(volatile struct USART_tag *)         0x40011400UL)
#define USART7               (*(volatile struct USART_tag *)         0x40007800UL)
#define USART8               (*(volatile struct USART_tag *)         0x40007C00UL)

// WDT
#define WDT                  (*(volatile struct WDT_tag *)           0x40003000UL)

// WWDT
#define WWDT                 (*(volatile struct WWDT_tag *)          0x40002C00UL)

// DEBUG
#define DEBUG                (*(volatile struct DEBUG_tag *)         0xE0042000UL)



#endif // AT32F43X_SFR_H
