#ifndef TBFP_PROTOCOL_PARSER_H
#define TBFP_PROTOCOL_PARSER_H

/*TBFP Trivial Binary Frame Protocol*/
#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#ifdef HAS_PROTOCOL
#include "protocol_const.h"
#endif
#include "tbfp_const.h"
#include "tbfp_types.h"

//https://docs.google.com/spreadsheets/d/1VAT3Ak7AzcufgvuRHrRVoVfC3nxugFGJR5pyzxL4W7Q/edit#gid=0


#define TBFP_PARSER_VARIABLES                                                            \
     uint32_t load_len;   /*number of bytes downloaded in a packet*/             \
     uint16_t exp_payload_len;                                                   \
     uint16_t s_num;   /*frame serial number   */                                \
     RxState_t rx_state;                                                         \
     FifoChar_t RxFifo;

//bool tbfp_proc_byte(TbfpHandle_t* instance, uint8_t rx_byte) ;


#ifdef __cplusplus
}
#endif

#endif /* TBFP_PROTOCOL_PARSER_H */
