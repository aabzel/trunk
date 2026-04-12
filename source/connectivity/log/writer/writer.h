#ifndef WRITER_H
#define WRITER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "std_includes.h"
#include "writer_diag.h"
#include "writer_types.h"
#include "writer_config.h"

#define STRING_STREAM(str)                                             \
    { {string_putc, string_puts}, (str), sizeof(str), 0, false }

/*API*/
WriterHandle_t* WriterGetNode(uint8_t num);
const WriterConfig_t* WriterGetConfig(uint8_t num);
WriterHandle_t* WriterGetNodeByInterface(const InterfaceType_t  interface_if);
bool writer_mcal_init(void);
bool writer_proc(void);


#if 0
void writer_putc(void* _s, char ch);
void writer_puts(void* _s, const char* s, int32_t len);
#endif
bool writer_default(void);
void writer_tx_callback(WriterHandle_t* s);
void writer_error_callback(WriterHandle_t* s);
bool writer_clean(const WriterHandle_t* s);
bool writer_half_clean(const WriterHandle_t* s);


bool oputs(ostream_t* const ostream, const char* const str);
void oputs_len(ostream_t* const ostream, const char* const str, int32_t len);
void oputc(ostream_t* const ostream, char c);

/*getters*/
WriterHandle_t* writer_get(void);
InterfaceType_t writer_interface_get(void);

/*setter*/
WriterHandle_t* writer_set_default(void);
bool writer_interface_set(const InterfaceType_t interface_if);
void string_putc(void* const  string_stream, const  char ch);
void string_puts(void* string_stream, const char* str, int32_t len);

#ifdef __cplusplus
}
#endif

#endif /* WRITER_H */
