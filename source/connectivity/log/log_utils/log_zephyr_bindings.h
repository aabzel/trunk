#ifndef LOG_ZEPHYR_BINDINGS_H
#define LOG_ZEPHYR_BINDINGS_H

#ifdef __cplusplus
extern "C" {
#endif

#if defined(HAS_CUSTOM_PRINTF) && defined(HAS_ZEPHYR)
#error "In Zephyr we use printk!"
#endif

#include <printk.h>
#include <stdio.h>
//Integration tests showed that Zephyr vprintk distorts Stack RAM (double variables)
#define putstr puts
#define cli_putstr puts
#define cli_printf printf
#define cli_vprintf vprintf



#ifdef __cplusplus
}
#endif

#endif /* LOG_ZEPHYR_BINDINGS_H */
