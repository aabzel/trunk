// main.c - Bootloader for STM32F407VE
// Jumps to 0x080E0000 after validating vector table

#include <stdint.h>

// Memory addresses
#define APP_BASE        0x08060000UL
#define SRAM_BASE       0x20000000UL
#define SRAM_END        0x2001FFFFUL  // 128KB for STM32F407VE
#define FLASH_BASE      0x08000000UL
#define FLASH_END       0x080FFFFFUL  // 1MB

// Peripherals
#define RCC_BASE        0x40023800UL
#define GPIOE_BASE      0x40021000UL

#define DWT_BASE        0xE0001000UL

#define CoreDebug_BASE      (0xE000EDF0UL)
#define CoreDebug_DEMCR_TRCENA_Pos         24U                                            /*!< CoreDebug DEMCR: TRCENA Position */
#define CoreDebug_DEMCR_TRCENA_Msk         (1UL << CoreDebug_DEMCR_TRCENA_Pos)

typedef struct {
  volatile uint32_t DHCSR;                  /*!< Offset: 0x000 (R/W)  Debug Halting Control and Status Register */
  volatile uint32_t DCRSR;                  /*!< Offset: 0x004 ( /W)  Debug Core Register Selector Register */
  volatile uint32_t DCRDR;                  /*!< Offset: 0x008 (R/W)  Debug Core Register Data Register */
  volatile uint32_t DEMCR;                  /*!< Offset: 0x00C (R/W)  Debug Exception and Monitor Control Register */
} CoreDebug_Type;

#define CoreDebug           ((CoreDebug_Type *)     CoreDebug_BASE)

// Register offsets
#define RCC_AHB1ENR     (*((volatile uint32_t*)(RCC_BASE + 0x30)))
#define GPIOx_MODER     (*((volatile uint32_t*)(GPIOE_BASE + 0x00)))
#define GPIOx_ODR       (*((volatile uint32_t*)(GPIOE_BASE + 0x14)))
#define DWT_CYCCNT      (*((volatile uint32_t*)(DWT_BASE + 0x04)))
#define DWT_CTRL        (*((volatile uint32_t*)(DWT_BASE + 0x00)))

// Vector table entry type
typedef struct {
    uint32_t stack_ptr;
    uint32_t reset_handler;
} VectorTable_t;

// Check if address is in SRAM range
static inline int is_valid_sram(uint32_t addr) {
    return (( SRAM_BASE <= addr) && (addr <= SRAM_END));
}

// Check if address is in Flash range
static inline int is_valid_flash(uint32_t addr) {
    return ((FLASH_BASE <= addr) && (addr <= FLASH_END));
}

// Initialize DWT cycle counter
static void dwt_init(void) {
    // Enable DWT in debug component (optional)
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk; // set bit 24
    DWT_CTRL |= 1;
}

// Delay using DWT (approximate for 168MHz)
static void delay_ms(uint32_t ms) {
    uint32_t start = DWT_CYCCNT;
    uint32_t cycles = ms * 16000;  // 16MHz * 0.001
    while ((DWT_CYCCNT - start) < cycles);
}

// Blink LED on PE13 at 10Hz
static void blink_led(void) __attribute__((noreturn));
static void blink_led(void) {
    // Enable GPIOE clock
    RCC_AHB1ENR |= (1 << 4);
    
    // Configure PE13 as output
    GPIOx_MODER &= ~(3 << 26);
    GPIOx_MODER |= (1 << 26);
    
    dwt_init();
    
    while(1) {
        GPIOx_ODR |= (1 << 13);   // High
        delay_ms(50);
        GPIOx_ODR &= ~(1 << 13);  // Low
        delay_ms(50);
    }
}

static int32_t is_valid_vector_table(const VectorTable_t * const app_vec){
    int32_t res = 1 ;
    // Validate stack pointer
    if (!is_valid_sram(app_vec->stack_ptr)) {
        res = 0 ;
    }
    // Validate reset handler address
    uint32_t reset_addr = app_vec->reset_handler;
    if (!is_valid_flash(reset_addr & ~1)) {
        res = 0 ;
    }

    // Check Thumb mode bit
    if ((reset_addr & 1) == 0) {
        res = 0 ;
    }
    return res;
}

typedef void (*pFunction)(void);
pFunction Jump_To_Code = 0; /*Must not be in stack*/

// Main function - called from startup code
int main(void) {
    const VectorTable_t *app_vec = (const VectorTable_t*) APP_BASE;

    int32_t res = is_valid_vector_table(app_vec);
    if (res) {
        uint32_t reset_addr = app_vec->reset_handler;
        Jump_To_Code = (pFunction)reset_addr;
        // Jump to application
        Jump_To_Code();
    }

    blink_led();
    // Should never reach here
    while (1) {
    };
}
