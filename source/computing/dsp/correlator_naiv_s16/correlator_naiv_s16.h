#ifndef CORRELATOR_NAIV_S16_H
#define CORRELATOR_NAIV_S16_H

#include "std_includes.h"
#include "correlator_naiv_s16_config.h"
#include "correlator_naiv_s16_types.h"

#ifdef HAS_CORRELATOR_NAIV_S16_DIAG
#include "correlator_naiv_s16_diag.h"
#endif

// API
CorrelatorNaivS16Handle_t* CorrelatorNaivS16GetNode(uint8_t num);
const CorrelatorNaivS16Config_t* CorrelatorNaivS16GetConfig(uint8_t num);

bool correlator_naiv_s16_init_one(uint8_t num);
bool correlator_naiv_s16_mcal_init(void);

bool correlator_naiv_s16_pull_ll(CorrelatorNaivS16Handle_t *Node, int16_t x0, int64_t *const out) ;

bool correlator_naiv_s16_proc_in_out_ll(CorrelatorNaivS16Handle_t *Node, int16_t x, int64_t *const y);
bool correlator_naiv_s16_proc_in_out(uint8_t num, int16_t x0, int64_t* const y);
int64_t correlator_naiv_s16_proc_in_out_short(uint8_t num, int16_t x0);

bool correlator_naiv_s16_proc_in_out_array(uint8_t num,
                                           uint32_t size,
                                           const int16_t* const x,
                                           int64_t* const y);


bool correlator_naiv_s16_reset_one(uint8_t num);
int32_t correlator_naiv_s16_order_get(uint8_t num);
bool correlator_naiv_s16_impulse_response(uint8_t num);
bool correlator_naiv_s16_set_b(uint8_t num, uint32_t k, int16_t b);

/*setter*/
bool correlator_naiv_s16_write_ref_signal(uint8_t num,
                                          const int16_t* const ref_signal,
                                          const uint32_t size );

bool correlator_naiv_s16_write_ref_signal_ll( CorrelatorNaivS16Handle_t* Node,
                                              const int16_t* const ref_signal,
                                              const uint32_t size );

#ifdef HAS_FILE_PC
bool correlator_naiv_s16_save_csv_line(char* file_name_out, double value_x, double value_y);
bool correlator_naiv_s16_proc_file(uint8_t num, char* file_name, uint16_t column_x, uint16_t column_y);
#endif

#endif
