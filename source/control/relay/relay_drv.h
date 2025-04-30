#ifndef RELAY_DRV_H
#define RELAY_DRV_H

/*RELAY receiver invariant component*/

#ifdef __cplusplus
extern "C" {
#endif

#include <stdbool.h>

#include "relay_constants.h"
#include "relay_types.h"
#include "timer_utils.h"

#ifndef HAS_RELAY
#error "It is needed to add HAS_RELAY option"
#endif

/*
  @details Function returns digital input state based on index value.
  @param [in] index - Digital input index see ::DI_index_ENUM.
  @return Digital input state see ::DI_state_ENUM.
 */
DI_state_E DI_getInputState(DI_index_E index);
bool RelayInit(void);
bool RelayProc(void);

/*
  @details Function sets state on digital output.
  @param [in] index - Digital power output pin index see ::DO_index_ENUM.
  @param [in] state - Digital power output state see ::DO_state_ENUM.
  @return Nothing.
*/
void DO_SetOutputState(DO_index_E index, DO_state_E state);
void DO_SetOutputStateReal(DO_index_E do_index, DO_state_E state);

#ifdef __cplusplus
} /* extern "C" */
#endif

#endif /*RELAY_DRV_H*/
