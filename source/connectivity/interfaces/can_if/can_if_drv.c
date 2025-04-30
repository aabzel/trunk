#include "can_if_drv.h"

#include <stdbool.h>
#include <stdint.h>

#ifdef HAS_PARAM
#include "param_drv.h"
#endif

#ifdef HAS_TBFP
#include "tbfp_protocol.h"
#endif /*HAS_TBFP*/
#include "log.h"


bool can_if_send(uint8_t* data, uint16_t len) {
    bool res = false;
    LOG_DEBUG(CAN, "CanSend %u byte", len);

    return res;
}

bool can_if_proc_payload(uint8_t* const rx_payload, uint32_t rx_size) {
    bool res = false;

#ifdef HAS_TBFP
    res = tbfp_proc(rx_payload, rx_size, IF_CAN, false);
#ifdef HAS_LOG
    if(false == res) {
        LOG_ERROR(CAN, "CanProcErr");
    }
#endif
#endif /*HAS_TBFP*/
    return res;
}

bool can_if_proc(void) {
    bool res = false;
#ifdef HAS_TBFP
    /*HeartBeat Frame*/
    res = tbfp_send_ping(FRAME_ID_PONG, IF_CAN);
#endif /*HAS_TBFT*/
    return res;
}

#ifdef HAS_TI_RTOS_CAN_TASK
/*
 *
 * @brief   Application task entry point for the Project Zero.
 *
 * @param   a0, a1 - not used.
 */


#define CAN_TASK_STACK_SIZE 2048
#define CAN_TASK_PRIORITY 2
uint8_t CanTaskStack[CAN_TASK_STACK_SIZE];
Task_Struct canTask;

bool can_if_create_tirtos_task(void) {
    bool res = true;
    Task_Params taskParams;

    Task_Params_init(&taskParams);
    taskParams.stack = CanTaskStack;
    taskParams.stackSize = CAN_TASK_STACK_SIZE;
    taskParams.priority = CAN_TASK_PRIORITY;

    Task_construct(&canTask, can_if_thread, &taskParams, NULL);
    return res;
}
#endif /*HAS_TI_RTOS_CAN_TASK*/

bool can_if_init(void) {
    bool out_res = true;
    (void)out_res;

#ifdef HAS_TI_RTOS_CAN_TASK
    can_if_create_tirtos_task();
#endif /*HAS_TI_RTOS_CAN_TASK*/

    return out_res;
}
