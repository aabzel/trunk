#ifndef SSD1306_COMMANDS_H
#define SSD1306_COMMANDS_H

#include <stdbool.h>
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

#ifndef HAS_SSD1306
#error "+ HAS_SSD1306"
#endif

#ifndef HAS_SSD1306_COMMANDS
#error "+ HAS_SSD1306_COMMANDS"
#endif

bool ssd1306_contrast_set_command(int32_t argc, char* argv[]);
bool ssd1306_diag_command(int32_t argc, char* argv[]);
bool ssd1306_inverse_command(int32_t argc, char* argv[]);
bool ssd1306_init_command(int32_t argc, char* argv[]);
bool ssd1306_reg_read_command(int32_t argc, char* argv[]);
bool ssd1306_sram_clean_command(int32_t argc, char* argv[]);
bool ssd1306_on_off_command(int32_t argc, char* argv[]);
bool ssd1306_page_addr_set_command(int32_t argc, char* argv[]);
bool ssd1306_print_char(int32_t argc, char* argv[]);
bool ssd1306_print_text(int32_t argc, char* argv[]);
bool ssd1306_reg_map_command(int32_t argc, char* argv[]);
bool ssd1306_reset_command(int32_t argc, char* argv[]);

#define SSD1306_COMMANDS                                                                                                \
        SHELL_CMD("ssd1306_clean", "ssdl", ssd1306_sram_clean_command, "Ssd1306Clean"),                                       \
        SHELL_CMD("ssd1306_print_char", "ssdc", ssd1306_print_char, "Ssd1306PrintChar"),                                       \
        SHELL_CMD("ssd1306_print_text", "ssdx", ssd1306_print_text, "Ssd1306PrintText"),                                       \
        SHELL_CMD("ssd1306_diag", "ssdd", ssd1306_diag_command, "Ssd1306Diag"),                                           \
        SHELL_CMD("ssd1306_init", "ssdi", ssd1306_init_command, "Ssd1306Init"),                                           \
        SHELL_CMD("ssd1306_reset", "ssdt", ssd1306_reset_command, "Ssd1306Reset"),

#ifdef __cplusplus
}
#endif

#endif /* SSD1306_COMMANDS_H */
