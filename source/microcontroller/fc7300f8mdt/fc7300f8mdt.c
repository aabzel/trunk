#include "microcontroller.h"

#ifdef HAS_LOG
#include "log.h"
#endif

#include "mcal_init.h"
#include "system.h"
#include "super_cycle.h"
#include "common_functions.h"
#include "fc7300f8mdt.h"
#include "system_init.h"
#include "common_diag.h"

#ifdef HAS_MAILBOX
#include "mailbox_mcal.h"
#endif

#ifdef HAS_MULTICORE
#include "multicore_mcal.h"
#endif



/*Order matters!*/
#define COREx_INIT_FUNCTIONS                                \
    START_PAUSE_INIT                                        \
    FPU_INIT


#ifdef HAS_MULTICORE
#include "multicore_mcal.h"

#ifdef HAS_LOG
#define MULTICORE1_INIT_NAME .name = "MULTICORE1",
#else
#define MULTICORE1_INIT_NAME
#endif

#define MULTICORE1_INIT {.init_function=multicore1_init, MULTICORE1_INIT_NAME},
#else
#define MULTICORE1_INIT
#endif /*HAS_MULTICORE*/


#ifdef HAS_MULTICORE
#include "multicore_mcal.h"

#ifdef HAS_LOG
#define MULTICORE2_INIT_NAME .name = "MULTICORE2",
#define MULTICORE3_INIT_NAME .name = "MULTICORE3",
#else
#define MULTICORE2_INIT_NAME
#endif

#define MULTICORE2_INIT {.init_function=multicore2_init, MULTICORE2_INIT_NAME},
#define MULTICORE3_INIT {.init_function=multicore3_init, MULTICORE3_INIT_NAME},
#else
#define MULTICORE2_INIT
#define MULTICORE3_INIT
#endif /*HAS_MULTICORE*/








/*Order matters!*/
#define CORE1_INIT_FUNCTIONS                                                         \
    COREx_INIT_FUNCTIONS                                 \
    MULTICORE2_INIT                                 \
    MAILBOX2_INIT


/*Order matters!*/
#define CORE2_INIT_FUNCTIONS                                                         \
    COREx_INIT_FUNCTIONS                                 \
    MULTICORE3_INIT                                 \
    MAILBOX3_INIT





/*Order matter!*/
const SystemInitInstance_t Core1InitInstance[] = {CORE1_INIT_FUNCTIONS};
const SystemInitInstance_t Core2InitInstance[] = {CORE2_INIT_FUNCTIONS};

static uint32_t core1_init_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Core1InitInstance);
    return cnt;
}

static uint32_t core2_init_get_cnt(void) {
    uint32_t cnt = 0;
    cnt = ARRAY_SIZE(Core2InitInstance);
    return cnt;
}

static bool core1_init(void) {
    bool res = true;
    uint32_t cnt = core1_init_get_cnt();
    res = system_init_one(Core1InitInstance, cnt);
    return res;
}

static bool core2_init(void) {
    bool res = true;
    uint32_t cnt = core2_init_get_cnt();
    res = system_init_one(Core2InitInstance, cnt);
    return res;
}



static bool core_x_main(const uint8_t core_num) {
    bool res = true;
    (void)res;

#ifdef HAS_MULTICORE
    //res = multicore_init_one(core_num);
#endif

#ifdef HAS_MAILBOX
    //res = mailbox_init_one(1);
#endif

    switch(core_num){
    case 2:res= core1_init(); break;
    case 3:res= core2_init();  break;
    default: break;
    }

#ifdef HAS_STREAM
    LOG_INFO(MICROCONTROLLER, "Core%u,Launched!",core_num);
#endif /*HAS_STREAM*/

#ifdef HAS_FREE_RTOS
    vTaskStartScheduler();
#endif /*HAS_FREE_RTOS*/

#ifdef HAS_NORTOS
#ifdef HAS_SUPER_CYCLE
    super_cycle_start_one(core_num);
#endif /*HAS_SUPER_CYCLE*/
#endif /*HAS_NORTOS*/

#ifdef HAS_LOG
    LOG_ERROR(MICROCONTROLLER, "Unreachable line!");
#endif
    /*Unreachable line*/
    while(true) {
    }
    return res;
} // main


__attribute__((section(".Code_Core1")))  void Core1_main(void){
    bool res = true;
    res = core_x_main(2);
    (void)res;
    return ;
} // main

__attribute__((section(".Code_Core2")))  void Core2_main(void){
    bool res = true;
    res = core_x_main(3);
    (void)res;
    return ;
} // main


#ifdef HAS_WRITER
WriterHandle_t* core_to_writer(int8_t core_num) {
    WriterHandle_t* Writer = NULL;
    Interfaces_t interface_if = IF_UNDEF;
    switch(core_num) {
    case 0:
        interface_if = IF_UART1;
        break;
    case 1:
        interface_if = IF_UART2;
        break;
    case 2:
        interface_if = IF_UART3;
        break;
    default:
        break;
    }

    if(interface_if) {
        Writer = WriterGetNodeByInterface(interface_if);
    }

    return Writer;
}
#endif

#ifdef HAS_WRITER
WriterHandle_t* multicore_get_writer(void) {
    WriterHandle_t* Node = NULL;
    int8_t core_num = 0;
#ifdef HAS_MULTICORE
    core_num = multicore_get_core_num();
#endif
    Node = core_to_writer(core_num);
    return Node;
}
#endif
