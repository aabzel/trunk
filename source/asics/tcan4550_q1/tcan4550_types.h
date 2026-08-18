
#ifndef TCAN4550_TYPES_H
#define TCAN4550_TYPES_H

#include <stdbool.h>
#include <stdint.h>

// 0x10A4 Rx FIFO 0 Status
typedef struct xtCanRegFiFo0Stat_t {
    union {
        uint32_t word;
        struct {
            uint8_t f0fl : 7;  /*0-6 Rx FIFO 0 Fill Level*/
            uint8_t rsvd1 : 1; /*7 Reserved*/
            uint8_t f0gi : 6;  /*8-13 Rx FIFO 0 Get Index*/
            uint8_t rsvd2 : 1; /*14-15 Reserved*/
            uint8_t f0pi : 6;  /*16-21 Rx FIFO 0 Put Index*/
            uint8_t rsvd3 : 2; /*22-23 Reserved*/
            uint8_t f0f : 1;   /*24 Rx FIFO 0 Full*/
            uint8_t rf0l : 1;  /*25 Rx FIFO 0 Message Lost*/
            uint8_t rsvd4 : 6; /*26-31 Reserved*/
        };
    };
} __attribute__((packed)) tCanRegFiFo0Stat_t;

// 0x10B4 Rx FIFO 1 Status
typedef struct xtCanRegFiFo1Stat_t {
    union {
        uint32_t word;
        struct {
            uint8_t f1fl : 7;  /*0-6    Rx FIFO 1 Fill Level*/
            uint8_t rsvd1 : 1; /*7      Reserved*/
            uint8_t f1gi : 6;  /*8-13   Rx FIFO 1 Get Index */
            uint8_t rsvd2 : 2; /*14-15  Reserved*/
            uint8_t f1pi : 6;  /*16-21  Rx FIFO 1 Put Index*/
            uint8_t rsvd3 : 1; /*22     Reserved*/
            uint8_t f1f : 1;   /*24     Rx FIFO 1 Full*/
            uint8_t rf1l : 1;  /*25     Rx FIFO 1 Message Lost*/
            uint8_t rsvd4 : 4; /*26-29  Reserved*/
            uint8_t dms : 2;   /*30-31  Rx FIFO 1 Message Lost*/
        };
    };
} __attribute__((packed)) tCanRegFiFo1Stat_t;

// 0x1044 Protocol Status Register
typedef struct xtCanRegProtStat_t {
    union {
        uint32_t word;
        struct {
            uint8_t lec : 3;    /*0-2   Last Error Code*/
            uint8_t act : 2;    /*3-4   Activity*/
            uint8_t ep : 1;     /*5     Error Passive*/
            uint8_t ew : 1;     /*6     Warning Status*/
            uint8_t bo : 1;     /*7     Bus_Off Status*/
            uint8_t dlec : 3;   /*8-10  Data Phase Last Error Code*/
            uint8_t resi : 1;   /*11    ESI flag of last received CAN FD Message*/
            uint8_t rbrs : 1;   /*12    BRS flag of last received CAN FD Message*/
            uint8_t rfdf : 1;   /*13    Received a CAN FD Message*/
            uint8_t pxe : 1;    /*14    Protocol Exception Event*/
            uint8_t rsvd1 : 1;  /*15    Reserved*/
            uint8_t tdcv : 7;   /*16-22 Transmitter Delay Compensation Value*/
            uint16_t rsvd2 : 9; /*23-31 Reserved*/
        };
    };
} __attribute__((packed)) tCanRegProtStat_t;

// 0x1050 Interrupt Register
typedef struct xCanRegInt_t {
    union {
        uint32_t word;
        struct {
            uint8_t rf0n : 1; /*0 Rx FIFO 0 New Message*/
            uint8_t rf0w : 1; /*1 Rx FIFO 0 Watermark Reached*/
            uint8_t rf0f : 1; /*2 Rx FIFO 0 Full*/
            uint8_t rf0l : 1; /*3 Rx FIFO 0 Message Lost*/
            uint8_t rf1n : 1; /*4 Rx FIFO 1 New Message*/
            uint8_t rf1w : 1; /*5 Rx FIFO 1 Watermark Reached*/
            uint8_t rf1f : 1; /*6 Rx FIFO 1 Full*/
            uint8_t rf1l : 1; /*7 Rx FIFO 1 Message Lost*/
            uint8_t hpm : 1;  /*8 High Priority Message*/
            uint8_t tc : 1;   /*9 Transmission Completed*/
            uint8_t tcf : 1;  /*10 Transmission Cancellation Finished*/
            uint8_t tfe : 1;  /*11 Tx FIFO Empty*/
            uint8_t tefn : 1; /*12 Tx Event FIFO New Entry*/
            uint8_t tefw : 1; /*13 Tx Event FIFO Watermark Reached*/
            uint8_t teff : 1; /*14 Tx Event FIFO Full*/
            uint8_t tefl : 1; /*15 Tx Event FIFO Element Lost*/
            uint8_t tsw : 1;  /*16 Timestamp Wraparound*/
            uint8_t mrf : 1;  /*17 Message RAM Access Failure*/
            uint8_t too : 1;  /*18 Timeout Occurred*/
            uint8_t drx : 1;  /*19 Message stored to Dedicated Rx Buffer*/
            uint8_t bec : 1;  /*20 Bit Error Corrected*/
            uint8_t beu : 1;  /*21 Bit Error Uncorrected*/
            uint8_t elo : 1;  /*22 ELO: Error Logging Overflow*/
            uint8_t ep : 1;   /*23 Error Passive*/
            uint8_t ew : 1;   /*24 Warning Status*/
            uint8_t bo : 1;   /*25 Bus_Off Status*/
            uint8_t wdi : 1;  /*26 Watchdog Interrupt*/
            uint8_t pea : 1;  /*27 Protocol Error in Arbitration Phase*/
            uint8_t ped : 1;  /*28 Protocol Error in Data Phase*/
            uint8_t ara : 1;  /*29 Access to Reserved Address*/
            uint8_t rsvd : 2; /*30*/
        };
    };
} __attribute__((packed)) tCanRegInt_t;

// 0x1018  CCCR "CC Control Register"
typedef struct xtCanRegCCctrl_t {
    union {
        uint32_t word;
        struct {
            uint8_t init : 1;  // 0  Initialization
            uint8_t cce : 1;   // 1  Configuration Change Enable
            uint8_t rom : 1;   // 2  Restricted Operation Mode
            uint8_t csa : 1;   // 3  Clock Stop Acknowledge
            uint8_t csr : 1;   // 4  Clock Stop Request
            uint8_t mon : 1;   // 5  Bus Monitoring Mode is Disabled
            uint8_t dar : 1;   // 6  Disable Automatic Retransmission
            uint8_t test : 1;  // 7  Test Mode Enable
            uint8_t fdoe : 1;  // 8  FD Operation Enable
            uint8_t brse : 1;  // 9  Bit Rate Switch Enable
            uint8_t rsvd1 : 2; // 10-11 Reserved
            uint8_t pxhd : 1;  // 12 Protocol Exception Handling Disable
            uint8_t efbi : 1;  // 13 Edge Filtering during Bus Integration
            uint8_t txp : 1;   // 14 Transmitter Pause
            uint8_t niso : 1;  // 15 Non ISO Operation
            uint16_t rsvd2;    // 16-31 Reserved
        };
    };
} __attribute__((packed)) tCanRegCCctrl_t;

/*0x101C Nominal Bit Timing & Prescaler Register*/
typedef struct xtCanRegBitTime_t {
    union {
        uint32_t word;
        struct {
            uint8_t ntseg2 : 7; // 0-6   Nominal Time Segment After Sample Point
            uint8_t rsvd : 1;   // 7
            uint8_t ntseg1;     // 8-15  Nominal Time Segment Before Sample Point
            uint16_t nbrp : 9;  // 16-24 Nominal Bit Rate Prescaler
            uint8_t nsjw : 7;   // 25-31 Nominal (RE)Synchronization Jump Width
        };
    };
} __attribute__((packed)) tCanRegBitTime_t;

/*0x100C Data Bit Timing & Prescaler */
typedef struct xtCanRegDataBitTime_t {
    union {
        uint32_t word;
        struct {
            uint8_t dsjw : 4;   // 0 data (re)synchronization jump width
            uint8_t dtseg2 : 4; // 4 data time segment After sample point
            uint8_t dtseg1 : 5; // 8  data time segment before sample point
            uint8_t rsvd1 : 3;  // 13
            uint8_t dbrp : 5;   // 16 data bit rate prescaler
            uint8_t rsvd : 2;   // 21
            uint8_t tdc : 1;    // 23 transmitter delay compensation
            uint8_t rsvd2;      // 24
        };
    };
} __attribute__((packed)) tCanRegDataBitTime_t;

// 1080  Global Filter Configuration
typedef struct xtCanRegGloFiltCfg_t {
    union {
        uint32_t word;
        struct {
            uint8_t rrfe : 1;    // 0   Reject Remote Frames Extended
            uint8_t rrfs : 1;    // 1   Reject Remote Frames Standard
            uint8_t anfe : 2;    // 2-3 Accept Non-matching Frames Extended
            uint8_t anfs : 2;    // 4-5 Accept Non-matching Frames Standard
            uint32_t rsrvd : 26; // 6-31
        };
    };
} __attribute__((packed)) tCanRegGloFiltCfg_t;

// 0x1084 Standard ID Filter Configuration
typedef struct xtCanRegStdIdFiltCfg_t {
    union {
        uint32_t word;
        struct {
            uint16_t flssa; // 0  filter list standard start address
            uint8_t lss;    // 16 list size standard
            uint8_t rsvd;   // 24 reserved
        };
    };
} __attribute__((packed)) tCanRegStdIdFiltCfg_t;

// 0x1088 Extended ID Filter Configuration
typedef struct xtCanRegExtIdFiltCfg_t {
    union {
        uint32_t word;
        struct {
            uint16_t flsea;    // 0  filter list extended start address
            uint8_t lse : 7;   // 16 list size extended
            uint16_t rsvd : 9; // 23 reserved
        };
    };
} __attribute__((packed)) tCanRegExtIdFiltCfg_t;

// 0x10A0 Rx FIFO 0 Configuration
typedef struct xtCanRegRxFifo0Cfg_t {
    union {
        uint32_t word;
        struct {
            uint16_t f0sa;    // 0-15  Rx FIFO 0 Start Address
            uint8_t f0s : 7;  // 16-22 Rx FIFO 0 Size
            uint8_t rsvd : 1; // 23
            uint8_t f0wm : 7; // 24-30 Rx FIFO 0 Watermark
            uint8_t f0om : 1; // 31       FIFO 0 Operation Mode
        };
    };
} __attribute__((packed)) tCanRegRxFifo0Cfg_t;

// 0x10B0 Rx FIFO 1 Configuration
typedef struct xtCanRegRxFifo1Cfg_t {
    union {
        uint32_t word;
        struct {
            uint16_t f1sa;   // 0   rx fifo 1 start address
            uint8_t f1s : 7; // 16  rx fifo 1 size
            uint8_t rsvd : 1;
            uint8_t f1wm : 7; // 24  rx fifo 1 watermark
            uint8_t f10m : 1; // 31  fifo 1 operation mode
        };
    };
} __attribute__((packed)) tCanRegRxFifo1Cfg_t;

// 0x0008 Revision
typedef struct xtCanRegRev_t {
    union {
        uint32_t word;
        struct {
            uint8_t minor_id;
            uint8_t major_id;
            uint8_t res;
            uint8_t spi2;
        };
    };
} __attribute__((packed)) tCanRegRev_t;

// 0x1054  Interrupt Enable
typedef struct xtCanRegIntEnable_t {
    union {
        uint32_t word;
        struct {
            uint8_t rf0ne : 1; /*0 rx fifo 0 new message                     */
            uint8_t rf0we : 1; /*1 rx fifo 0 watermark reached               */
            uint8_t rf0fe : 1; /*2 rx fifo 0 full                             */
            uint8_t rf0le : 1; /*3 rx fifo 0 message lost                     */
            uint8_t rf1ne : 1; /*4 rx fifo 1 new message                      */
            uint8_t rf1we : 1; /*5 rx fifo 1 watermark reached               */
            uint8_t rf1fe : 1; /*6 rx fifo 1 full                            */
            uint8_t rf1le : 1; /*7 rx fifo 1 message lost                    */
            uint8_t hpme : 1;  /*8 high priority message                      */
            uint8_t tce : 1;   /*9 transmission completed                      */
            uint8_t tcfe : 1;  /*10 transmission cancellation finished        */
            uint8_t tfee : 1;  /*11 tx fifo empty                             */
            uint8_t tefne : 1; /*12 tx event fifo new entry                  */
            uint8_t tefw : 1;  /*13 tx event fifo watermark reached           */
            uint8_t teffe : 1; /*14 tx event fifo full                       */
            uint8_t tefle : 1; /*15 tx event fifo event lost                 */
            uint8_t tswe : 1;  /*16 timestamp wraparound                      */
            uint8_t mrafe : 1; /*17 message ram access failure               */
            uint8_t tooe : 1;  /*18 timeout occurred                          */
            uint8_t drxe : 1;  /*19 message stored to dedicated rx buffer     */
            uint8_t bece : 1;  /*20 bit error corrected                       */
            uint8_t beue : 1;  /*21 bit error uncorrected                     */
            uint8_t eloe : 1;  /*22 error logging overflow                    */
            uint8_t epe : 1;   /*23 error passive                              */
            uint8_t ewe : 1;   /*24 warning status                             */
            uint8_t boe : 1;   /*25 bus_off status                             */
            uint8_t wdie : 1;  /*26 watchdog                                  */
            uint8_t peae : 1;  /*27 protocol error in arbitration phase enable*/
            uint8_t pede : 1;  /*28 protocol error in data phase enable  */
            uint8_t arae : 1;  /*29 access to reserved address enable*/
            uint8_t rsvd : 2;  /*30 */
        };
    };
} __attribute__((packed)) tCanRegIntEnable_t;

// 0x000C Status
typedef struct xtCanRegStatus_t {
    union {
        uint32_t word;
        struct {
            uint8_t inter : 1;                    // 0     Value of interrupt input level (active high)
            uint8_t spi_error_interrupt : 1;      // 1     Unmasked SPI error set
            uint8_t internal_error_interrupt : 1; // 2     Unmasked Internal error set
            uint8_t internal_access_active : 1;   // 3     Internal Multiple transfer mode access in progress
            uint8_t
                read_fifo_available : 1; // 4     Read fifo entries is greater than or equal to the read_fifo_threshold
            uint8_t write_fifo_available : 1; // 5     write fifo empty entries is greater than or equal to the
                                              // write_fifo_threshold
            uint16_t rsvd1 : 10;              // 6-15  Reserved
            uint8_t read_underflow : 1;       // 16    SPI read sequence ended with less data transferred then requested
            uint8_t read_overflow : 1;   // 17    SPI read sequence had continue requests after the data transfer was
                                         // completed
            uint8_t write_underflow : 1; // 18    SPI write sequence ended with less data transferred then requested
            uint8_t write_overflow : 1;  // 19    SPI write sequence had continue requests after the data transfer was
                                         // completed
            uint8_t invalid_command : 1; // 20    Invalid SPI command received
            uint8_t spi_end_error : 1;   // 21    SPI transfer did not end on a byte boundary
            uint8_t rsvd2 : 2;           // 22-23 Reserved
            uint8_t write_fifo_overflow : 1;      // 24    Write/command FIFO overflow
            uint8_t read_fifo_empty : 1;          // 25    Read FIFO empty for first read data word to return
            uint8_t read_fifo_underflow : 1;      // 26    Read FIFO underflow after 1 or more read data words returned
            uint8_t internal_error_log_write : 1; // 27    Entry written to the Internal error log
            uint8_t internal_write_error : 1;     // 28    Internal write received an error response
            uint8_t internal_read_error : 1;      // 29    Internal read received an error response
            uint8_t rsvd3 : 2;                    // 30-31 Reserved
        };
    };
} __attribute__((packed)) tCanRegStatus_t;

// 0x0800 Modes of Operation and Pin Configurations
typedef struct xtCanRegModeOpPinCfg_t {
    union {
        uint32_t word;
        struct {
            uint8_t test_mode_config : 1; /*0 Test Mode Configuration */
            uint8_t swe_dis : 1;          /*1 Sleep Wake Error Disable: */
            uint8_t device_reset : 1;     /*2  Device Reset*/
            uint8_t wd_en : 1;            /*3  Watchdog Enable*/
            uint8_t rsvd1 : 2;            /*4-5 */
            uint8_t mode_sel : 2;         /*6-7 Mode of operation select*/
            uint8_t nwkrq_config : 1;     /*8  nWKRQ Pin Function */
            uint8_t inh_dis : 1;          /*9  INH Pin Disable*/
            uint8_t gpio1_gpo_config : 2; /*10  GPIO1 pin GPO1 function select*/
            uint8_t rsvd2 : 1;            /*12  */
            uint8_t fail_safe_en : 1;     /*13  Fail safe mode enable: */
            uint8_t gpio1_config : 2;     /*14  GPIO1 Pin Function Select */
            uint8_t wd_action : 2;        /*16  Selected action when WD_TIMER times out*/
            uint8_t wd_bit_set : 1;       /*18  Write a 1 to reset timer*/
            uint8_t nwkrq_voltage : 1;    /*19  nWKRQ Pin GPO buffer voltage rail configuration:*/
            uint8_t rsvd3 : 1;            /*20  */
            uint8_t test_mode_en : 1;     /*21  Test mode enable. */
            uint8_t gpo2_config : 2;      /*22  GPO2 Pin GPO Configuration*/
            uint8_t rsvd4 : 3;            /*24-26  Reserved */
            uint8_t clk_ref : 1;          /*27  CLKIN/Crystal Frequency Reference*/
            uint8_t wd_timer : 2;         /*28  Watchdog timer*/
            uint8_t wake_config : 2;      /*30  Wake pin configuration*/
        };
    };
} __attribute__((packed)) tCanRegModeOpPinCfg_t;

// 0x105C  Interrupt Line Enable
typedef struct xCanRegIntLine_t {
    union {
        uint32_t word;
        struct {
            uint8_t eint0 : 1;  /*0 enable interrupt line 0*/
            uint8_t eint1 : 1;  /*1 enable interrupt line 1*/
            uint32_t rsvd : 30; /*2-31 reserved            */
        };
    };
} __attribute__((packed)) tCanRegIntLine_t;

// 0x0830 Interrupt Enable and
// 0x1054  Interrupt Enable
typedef struct xtCanRegIntEn_t {
    union {
        uint32_t word;
        struct {
            uint8_t rf0ne : 1; /*0 rx fifo 0 new message                         */
            uint8_t rf0we : 1; /*1 rx fifo 0 watermark reached                   */
            uint8_t rf0fe : 1; /*2 rx fifo 0 full                                */
            uint8_t rf0le : 1; /*3 rx fifo 0 message lost                        */
            uint8_t rf1ne : 1; /*4 rx fifo 1 new message                         */
            uint8_t rf1we : 1; /*5 rx fifo 1 watermark reached                   */
            uint8_t rf1fe : 1; /*6 rx fifo 1 full                                */
            uint8_t rf1le : 1; /*7 rx fifo 1 message lost                        */
            uint8_t hpme : 1;  /*8 high priority message                         */
            uint8_t tce : 1;   /*9 transmission completed                        */
            uint8_t tcfe : 1;  /*10 transmission cancellation finished           */
            uint8_t tfee : 1;  /*11 tx fifo empty                                */
            uint8_t tefne : 1; /*12 tx event fifo new entry                      */
            uint8_t tefw : 1;  /*13  tx event fifo watermark reached             */
            uint8_t teffe : 1; /*14 tx event fifo full                           */
            uint8_t tefle : 1; /*15 tx event fifo event lost                     */
            uint8_t tswe : 1;  /*16 timestamp wraparound                         */
            uint8_t mrafe : 1; /*17  message ram access failure                  */
            uint8_t tooe : 1;  /*18 timeout occurred                             */
            uint8_t drxe : 1;  /*19 message stored to dedicated rx buffer        */
            uint8_t bece : 1;  /*20 bit error corrected                          */
            uint8_t beue : 1;  /*21 bit error uncorrected                        */
            uint8_t eloe : 1;  /*22 error logging overflow                       */
            uint8_t epe : 1;   /*23 error passive                                */
            uint8_t ewe : 1;   /*24  warning status                              */
            uint8_t boe : 1;   /*25 bus_off status                               */
            uint8_t wdie : 1;  /*26 watchdog                                     */
            uint8_t peae : 1;  /*27 protocol error in arbitration phase enable   */
            uint8_t pede : 1;  /*28 protocol error in data phase enable          */
            uint8_t arae : 1;  /*29 access to reserved address enable            */
            uint8_t rsvd : 2;  /*30-31                                           */
        };
    };
} __attribute__((packed)) tCanRegIntEn_t;

/*0x0820 Interrupt Flags*/
typedef struct xtCanRegIntFl_t {
    union {
        uint32_t word;
        struct {
            uint8_t vtwd : 1;      // 0 Global Voltage, Temp or WDTO
            uint8_t m_can_int : 1; // 1 M_CAN global INT
            uint8_t rsvd1 : 1;     // 2
            uint8_t spierr : 1;    // 3 SPI Error
            uint8_t rsvd2 : 1;     // 4
            uint8_t canerr : 1;    // 5 CAN Error
            uint8_t wkrq : 1;      // 6 Wake Request
            uint8_t globalerr : 1; // 7 Global Error (Any Fault)
            uint8_t candom : 1;    // 8 CAN Stuck Dominant
            uint8_t rsvd3 : 1;     // 9
            uint8_t canslnt : 1;   // 10 CAN Silent
            uint8_t rsvd4 : 2;     // 11
            uint8_t wkerr : 1;     // 13 Wake Error
            uint8_t lwu : 1;       // 14 Local Wake Up
            uint8_t canint : 1;    // 15 Can Bus Wake Up Interrupt
            uint8_t eccerr : 1;    // 16 Uncorrectable ECC error detected
            uint8_t rsvd5 : 1;     // 17
            uint8_t wdto : 1;      // 18 Watchdog Time Out
            uint8_t tsd : 1;       // 19 Thermal Shutdown
            uint8_t pwron : 1;     // 20 Power ON
            uint8_t uvio : 1;      // 21 Under Voltage VIO
            uint8_t uvsup : 1;     // 22 Under Voltage VSUP and UVCCOUT
            uint8_t sms : 1;       // 23 Sleep Mode Status
            uint8_t rsvd6 : 7;     // 24-30
            uint8_t canbusnom : 1; // 31 CAN Bus normal
        };
    };
} __attribute__((packed)) tCanRegIntFl_t;

// 0x10C0 Tx Buffer Configuration
typedef struct xtCanRegTxBufCfg_t {
    union {
        uint32_t word;
        struct {
            uint16_t tx_buf_start_addr; // 0 Tx Buffers Start Address
            uint8_t ndtb : 6;           // 16-21 Number of Dedicated Transmit Buffers
            uint8_t rsvd1 : 2;          // 22-23 Reserved
            uint8_t tfqs : 6;           // 24-29 Transmit FIFO/Queue Size
            uint8_t tfqm : 1;           // 30 Tx FIFO/Queue Mode
            uint8_t rsvd2 : 1;          // 31  Reserved
        };
    };
} __attribute__((packed)) tCanRegTxBufCfg_t;

// 0x10C8 Tx Buffer Element Size Configuration
typedef struct xTxBufElmSzCfg_t {
    union {
        uint32_t word;
        struct {
            uint8_t tx_buff_data_size : 3; // 0-2  Tx Buffer Data Field Size
            uint32_t rsvd : 29;            // 3-31 Reserved
        };
    };
} __attribute__((packed)) tCanRegTxBufElmSzCfg_t;

/**
 *  CAN message header for transmitted messages
 */
typedef struct xTCanTxHeader_t {
    uint32_t id : 29;     // CAN ID to send
    uint8_t rtr : 1;      // Remote Transmission Request flag
    uint8_t xtd : 1;      // Extended Identifier flag
    uint8_t esi : 1;      // Error state indicator flag
    uint8_t dlc : 4;      // Data length code
    uint8_t brs : 1;      // Bit rate switch used flag
    uint8_t fdf : 1;      // CAN FD Format flag
    uint8_t reserved : 1; // Reserved
    uint8_t efc : 1;      // Event FIFO Control flag, to store tx events or not
    uint8_t mm : 8;       // Message Marker, used if @c EFC is set to 1
} tCanTxHeader_t;

// 0x10AC Rx Buffer Configuration
typedef struct xRxBufCgf_t {
    union {
        uint32_t word;
        struct {
            uint16_t rbsa; // 0-15 Rx Buffer Start Address
            uint16_t rsvd;
        };
    };
} __attribute__((packed)) tCanRegRxBufCgf_t;

// 0x10BC Rx Buffer/FIFO Element Size Configuration
typedef struct xRxBufFiFoElemSzCgf_t {
    union {
        uint32_t word;
        struct {
            uint8_t f0ds : 3;    // 0-2   Rx FIFO 0 Data Field Size
            uint8_t rsvd : 1;    // 3     reserved
            uint8_t f1ds : 3;    // 4-6   Rx FIFO 1 Data Field Size
            uint8_t rsvd1 : 1;   // 7     reserved
            uint8_t rbds : 3;    // 8-10  Rx Buffer Data Field Size
            uint32_t rsvd2 : 21; // 24-31 reserved
        };
    };
} __attribute__((packed)) tCanRegRxBufFiFoElemSzCgf_t;

// 0x10F0  Tx Event FIFO Configuration
typedef struct xTxEventFifoCgf_t {
    union {
        uint32_t word;
        struct {
            uint16_t efsa;     // event fifo start address
            uint8_t efs : 6;   // event fifo size
            uint8_t rsvd1 : 2; // reserved
            uint8_t efwm : 6;  // event fifo watermark
            uint8_t rsvd2 : 2; // reserved
        };
    };
} __attribute__((packed)) tCanRegTxEventFifoCgf_t;

/**
 * @brief Standard ID filter struct
 */
typedef struct xtCan4550SidFilter_t {
    union {
        uint32_t word;
        struct {
            uint16_t sfid2 : 11;  // 0 -10 Standard Filter ID 2
            uint8_t reserved : 5; // 11-15
            uint16_t sfid1 : 11;  // 16-26 Standard Filter ID 1
            uint8_t sfec : 3;     // 27-29 Standard Filter Element Configuration
            uint8_t sft : 2;      // 30-31 Standard Filter Type
        };
    };
} __attribute__((packed)) tCan4550SidFilter_t;

/**
 * @brief Defines the number of MRAM elements and the size of the elements
 */
typedef struct {
    /************************
     *    Filter Elements   *
     ************************/

    //! @brief Standard ID Number of Filter Elements: The number of 11-bit filters the user would like
    //! \n Valid range is: 0 to 128
    uint8_t sid_num_elements : 8;

    //! @brief extended id number of filter elements: the number of 29-bit filters the user would like
    //! \n valid range is: 0 to 64
    uint8_t xid_num_elements : 7;

    /************************
     *  rx fifo elements    *
     ************************/

    //! @brief rx fifo 0 number of elements: the number of elements for the rx fifo 0
    //! \n valid range is: 0 to 64
    uint8_t rx0_num_elements : 7;

    //! @brief rx fifo 0 element size: the number of bytes for the rx 0 fifo (data payload)
    uint8_t rx0_element_size : 3;

    //! @brief rx fifo 1 number of elements: the number of elements for the rx fifo 1
    //!\n valid range is: 0 to 64
    uint8_t rx1_num_elements : 7;

    //! @brief rx fifo 1 element size: the number of bytes for the rx 1 fifo (data payload)
    uint8_t rx1_element_size : 3;

    //! @brief rx buffers number of elements: the number of elements for the rx buffers (not the fifo)
    //! \n valid range is: 0 to 64
    uint8_t rx_buf_num_elements : 7;

    //! @brief rx buffers element size: the number of bytes for the rx buffers (data payload), not the fifo
    uint8_t rx_buf_element_size : 3;

    /************************
     *  tx buffer elements  *
     ************************/

    //! @brief tx event fifo number of elements: the number of elements for the tx event fifo
    //! \n valid range is: 0 to 32
    uint8_t tx_event_fifo_num_elements : 6;

    //! @brief tx buffers number of elements: the number of elements for the tx buffers
    //! \n valid range is: 0 to 32
    uint8_t tx_buffer_num_elements : 6;

    //! @brief tx buffers element size: the number of bytes for the tx buffers (data payload)
    uint8_t tx_buffer_element_size : 3;

} __attribute__((packed)) TCAN4550_MRAM_Config;

// Tx Event FIFO and Tx Buffers
typedef struct xW0_t {
    union {
        uint32_t word;
        struct {
            uint32_t id : 29; // bit 0-28 Identifier
            uint8_t rtr : 1;  // bit 29 Remote Transmission Request
            uint8_t xtd : 1;  // bit 30 Extended Identifier
            uint8_t esi : 1;  // bit 31 Error State Indicator
        };
    };
} __attribute__((packed)) W0_t;

typedef struct xTxBuffW1_t {
    union {
        uint32_t word;
        struct {
            uint16_t res1;    // bits 0-15 reserved
            uint8_t dlc : 4;  // bits 16-19 Data Length Code
            uint8_t brs : 1;  // bit 20 Bit Rate Switch
            uint8_t fdf : 1;  // bit 21 FD Format
            uint8_t res2 : 1; // bit 22 reserved
            uint8_t efc : 1;  // bit 23 event fifo control
            uint8_t mm;       // bits 24-31  message marker
        };
    };
} __attribute__((packed)) TxBuffW1_t;

#endif /* TCAN4550_TYPES_H */
